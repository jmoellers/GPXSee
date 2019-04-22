#include "trefile.h"
#include "lblfile.h"
#include "rgnfile.h"


bool RGNFile::BitStream::read(int bits, quint32 &val)
{
	val = 0;

	for (int pos = 0; pos < bits; ) {
		if (!_remaining) {
			if (!_length || !_file.readByte(_hdl, _data))
				return false;
			_remaining = 8;
			_length--;
		}

		quint32 get = bits - pos;
		if (get >= _remaining) {
			val |= _data << pos;
			pos += _remaining;
			_remaining = 0;
		} else {
			quint32 mask = (1<<get) - 1;
			val |= (_data & mask)<<pos;
			_data >>= get;
			_remaining -= get;
			break;
		}
	}

	return true;
}

bool RGNFile::BitStream::readDelta(int bits, int sign, bool extraBit,
  qint32 &delta)
{
	quint32 value;
	int bo = 0;

	if (!read(bits, value))
		return false;

	if (extraBit) {
		value>>=1;
		bo = 1;
	}

	if (!sign) {
		qint32 signMask = 1 << (bits - bo - 1);
		if (value & signMask) {
			qint32 comp = value ^ signMask;
			if (comp)
				delta = comp - signMask;
			else {
				qint32 other;
				if (!readDelta(bits - bo, sign, false, other))
					return false;
				if (other < 0)
					delta = 1 - signMask + other;
				else
					delta = signMask - 1 + other;
			}
		} else {
			delta = value;
		}
	} else {
		delta = value * sign;
	}

	return true;
}

bool RGNFile::BitStream::finish()
{
	while (_length--)
		if (!_file.readByte(_hdl, _data))
			return false;
	return true;
}


bool RGNFile::init(const TREFile *tre, const LBLFile *lbl)
{
	Handle hdl;

	if (!(isValid() && seek(hdl, 0x15) && readUInt32(hdl, _offset)
	  && readUInt32(hdl, _size)))
		return false;

	if (_offset + _size > size())
		return false;

	_tre = tre;
	_lbl = lbl;

	return true;
}

bool RGNFile::sign(BitStream &bs, int &val)
{
	quint32 bit;
	val = 0;

	if (!bs.read(1, bit))
		return false;
	if (bit) {
		if (!bs.read(1, bit))
			return false;
		val = bit ? -1 : 1;
	}

	return true;
}

int RGNFile::bitSize(quint8 baseSize, bool variableSign, bool extraBit)
{
	int bits = 2;
	if (baseSize <= 9)
		bits += baseSize;
	else
		bits += 2 * baseSize - 9;

	if (variableSign)
		bits++;
	if (extraBit)
		bits++;

	return bits;
}

bool RGNFile::polyObjects(const RectC &rect, Handle &hdl, const SubDiv *subdiv,
  const Segment &segment, QList<IMG::Poly> &polys) const
{
	if (!seek(hdl, segment.start()))
		return false;

	quint32 labelPtr;
	quint8 len8, bitstreamInfo;
	qint16 lon, lat;
	quint16 len;

	while (hdl.pos < (int)segment.end()) {
		IMG::Poly poly;

		if (!(readByte(hdl, poly.type) && readUInt24(hdl, labelPtr)
		  && readInt16(hdl, lon) && readInt16(hdl, lat)))
			return false;
		if (poly.type & 0x80) {
			if (!readUInt16(hdl, len))
				return false;
		} else {
			if (!readByte(hdl, len8))
				return false;
			len = len8;
		}

		if (!readByte(hdl, bitstreamInfo))
			return false;

		bool show = segment.type() == Segment::Polygon
		  ? _tre->showPolygon(poly.type & 0x7F, subdiv->bits())
		  : _tre->showLine(poly.type & 0x3F, subdiv->bits());
		if (!show) {
			seek(hdl, hdl.pos + len);
			continue;
		}

		bool extraBit = labelPtr & 0x400000;

		RectC br;
		QPoint pos(subdiv->lon() + (lon<<(24-subdiv->bits())),
		  subdiv->lat() + (lat<<(24-subdiv->bits())));
		Coordinates c(toWGS84(pos.x()), toWGS84(pos.y()));
		br = br.united(c);
		poly.points.append(c);

		BitStream bs(*this, hdl, len);
		int lonSign, latSign;
		if (!sign(bs, lonSign) || !sign(bs, latSign))
			return false;
		int lonBits = bitSize(bitstreamInfo & 0x0F, !lonSign, extraBit);
		int latBits = bitSize(bitstreamInfo >> 4, !latSign, false);

		while (bs.hasNext(lonBits + latBits)) {
			qint32 lonDelta, latDelta;

			if (!(bs.readDelta(lonBits, lonSign, extraBit, lonDelta)
			  &&  bs.readDelta(latBits, latSign, false, latDelta)))
				return false;

			pos.rx() += lonDelta<<(24-subdiv->bits());
			pos.ry() += latDelta<<(24-subdiv->bits());

			Coordinates c(toWGS84(pos.x()), toWGS84(pos.y()));
			poly.points.append(c);
			br = br.united(c);
		}
		if (!bs.finish())
			return false;

		if (!rect.intersects(br))
			continue;

		if (_lbl && !(labelPtr & 0x800000))
			poly.label = _lbl->label(labelPtr & 0x3FFFFF);

		polys.append(poly);
	}

	return true;
}

bool RGNFile::pointObjects(const RectC &rect, Handle &hdl, const SubDiv *subdiv,
  const Segment &segment, QList<IMG::Point> &points) const
{
	qint16 lon, lat;
	quint32 labelPtr;

	if (!seek(hdl, segment.start()))
		return false;

	while (hdl.pos < (int)segment.end()) {
		IMG::Point point;

		if (!(readByte(hdl, point.type) && readUInt24(hdl, labelPtr)
		  && readInt16(hdl, lon) && readInt16(hdl, lat)))
			return false;
		if (labelPtr & 0x800000) {
			if (!readByte(hdl, point.subtype))
				return false;
		} else
			point.subtype = 0;

		qint16 lonOffset = lon<<(24-subdiv->bits());
		qint16 latOffset = lat<<(24-subdiv->bits());
		point.coordinates = Coordinates(toWGS84(subdiv->lon() + lonOffset),
		  toWGS84(subdiv->lat() + latOffset));

		if (!rect.contains(point.coordinates))
			continue;

		if (!_tre->showPoint(point.type, point.subtype, subdiv->bits()))
			continue;

		point.poi = labelPtr & 0x400000;
		if (_lbl)
			point.label = _lbl->label(labelPtr & 0x3FFFFF);

		points.append(point);
	}

	return true;
}

void RGNFile::objects(const RectC &rect, const SubDiv *subdiv,
  QList<IMG::Poly> &polygons, QList<IMG::Poly> &lines,
  QList<IMG::Point> &points) const
{
	Handle hdl;

	QVector<RGNFile::Segment> seg(segments(hdl, subdiv));
	for (int i = 0; i < seg.size(); i++) {
		switch (seg.at(i).type()) {
			case Segment::Point:
			case Segment::IndexedPoint:
				pointObjects(rect, hdl, subdiv, seg.at(i), points);
				break;
			case Segment::Line:
				polyObjects(rect, hdl, subdiv, seg.at(i), lines);
				break;
			case Segment::Polygon:
				polyObjects(rect, hdl, subdiv, seg.at(i), polygons);
				break;
		}
	}
}

QVector<RGNFile::Segment> RGNFile::segments(Handle &hdl, const SubDiv *subdiv)
  const
{
	if (!(subdiv->objects() & 0xF0))
		return QVector<Segment>();

	quint32 offset = _offset + subdiv->offset();

	int no = 0;
	for (quint8 mask = 0x10; mask; mask <<= 1)
		if (subdiv->objects() & mask)
			no++;

	if (!seek(hdl, offset))
		return QVector<Segment>();

	QVector<Segment> ret;
	quint32 start = offset + 2 * (no - 1);
	quint16 po;
	int cnt = 0;

	for (quint8 mask = 0x10; mask; mask <<= 1) {
		if (subdiv->objects() & mask) {
			if (cnt) {
				if (!readUInt16(hdl, po))
					return QVector<Segment>();
				start = offset + po;
			}
			if (!ret.isEmpty())
				ret.last().setEnd(start);
			ret.append(Segment(start, (Segment::Type)mask));
			cnt++;
		}
	}

	ret.last().setEnd(subdiv->end() ? _offset + subdiv->end() : _offset + _size);

	return ret;
}

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const RGNFile::Segment &segment)
{
	dbg.nospace() << "Segment(" << segment.start() << ", " << segment.end()
	  << ", " << segment.type() << ")";
	return dbg.space();
}
#endif // QT_NO_DEBUG
