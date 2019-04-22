#include "subdiv.h"
#include "units.h"
#include "trefile.h"


struct MapLevel {
	quint8 level;
	quint8 bits;
	quint16 subdivs;
};

#ifndef QT_NO_DEBUG
static QDebug operator<<(QDebug dbg, const MapLevel &ml)
{
	bool inherited = ml.level & 0x80 ? true : false;
	dbg.nospace() << "MapLevel(" << (ml.level & 0x7F) << ", " << inherited
	  << ", " << ml.bits << ", " << ml.subdivs << ")";
	return dbg.space();
}
#endif // QT_NO_DEBUG

static void unlock(quint8 *dst, const quint8 *src, quint32 size, quint32 key)
{
	static const unsigned char shuf[] = {
		0xb, 0xc, 0xa, 0x0,
		0x8, 0xf, 0x2, 0x1,
		0x6, 0x4, 0x9, 0x3,
		0xd, 0x5, 0x7, 0xe
	};

	int sum = shuf[((key >> 24) + (key >> 16) + (key >> 8) + key) & 0xf];

	for (quint32 i = 0, ringctr = 16; i < size; i++) {
		quint32 upper = src[i] >> 4;
		quint32 lower = src[i];

		upper -= sum;
		upper -= key >> ringctr;
		upper -= shuf[(key >> ringctr) & 0xf];
		ringctr = ringctr ? ringctr - 4 : 16;

		lower -= sum;
		lower -= key >> ringctr;
		lower -= shuf[(key >> ringctr) & 0xf];
		ringctr = ringctr ? ringctr - 4 : 16;

		dst[i] = ((upper << 4) & 0xf0) | (lower & 0xf);
	}
}

TREFile::~TREFile()
{
	SubDivTree::Iterator jt;

	for (QMap<int, SubDivTree*>::iterator it = _subdivs.begin();
	  it != _subdivs.end(); ++it) {
		SubDivTree *tree = *it;
		for (tree->GetFirst(jt); !tree->IsNull(jt); tree->GetNext(jt))
			delete tree->GetAt(jt);
	}

	for (QMap<int, SubDivTree*>::iterator it = _subdivs.begin();
	  it != _subdivs.end(); ++it)
		delete *it;
}


bool TREFile::parsePoly(Handle hdl, quint32 pos,
  const QMap<int, int> &level2bits, QMap<int, int> &map)
{
	quint32 offset, size;
	quint16 recordSize;

	if (!(seek(hdl, pos) && readUInt32(hdl, offset) && readUInt32(hdl, size)
	 && readUInt16(hdl, recordSize)))
		return false;

	for (quint32 i = 0; i < size; i += recordSize) {
		quint8 type, level;
		if (!(seek(hdl, offset + i) && readByte(hdl, type)
		  && readByte(hdl, level)))
			return false;
		map.insert(type, level2bits.value(level));
	}

	return true;
}

bool TREFile::parsePoints(Handle hdl, quint32 pos,
  const QMap<int, int> &level2bits)
{
	quint32 offset, size;
	quint16 recordSize;

	if (!(seek(hdl, pos) && readUInt32(hdl, offset) && readUInt32(hdl, size)
	 && readUInt16(hdl, recordSize)))
		return false;

	for (quint32 i = 0; i < size; i += recordSize) {
		quint8 type, subtype, level;
		if (!(seek(hdl, offset + i) && readByte(hdl, type)
		  && readByte(hdl, level) && readByte(hdl, subtype)))
			return false;
		_points.insert(type<<8|subtype, level2bits.value(level));
	}

	return true;
}

bool TREFile::init()
{
	Handle hdl;
	quint8 locked;


	if (!isValid() || !seek(hdl, 0x0D) || !readByte(hdl, locked))
		return false;

	// Tile bounds
	if (!seek(hdl, 0x15))
		return false;
	qint32 north, east, south, west;
	if (!(readInt24(hdl, north) && readInt24(hdl, east)
	  && readInt24(hdl, south) && readInt24(hdl, west)))
		return false;
	_bounds = RectC(Coordinates(toWGS84(west), toWGS84(north)),
	  Coordinates(toWGS84(east), toWGS84(south)));

	quint32 levelsOffset, levelsSize, subdivOffset, subdivSize;
	if (!(readUInt32(hdl, levelsOffset) && readUInt32(hdl, levelsSize)
	  && readUInt32(hdl, subdivOffset) && readUInt32(hdl, subdivSize)))
		return false;

	// Tile levels
	if (levelsSize > 64 || !seek(hdl, levelsOffset))
		return false;
	quint8 levels[64];
	for (quint32 i = 0; i < levelsSize; i++)
		if (!readByte(hdl, levels[i]))
			return false;
	if (locked) {
		quint32 key;
		quint8 unlocked[64];
		if (!seek(hdl, 0xAA) || !readUInt32(hdl, key))
			return false;
		unlock(unlocked, levels, levelsSize, key);
		memcpy(levels, unlocked, levelsSize);
	}

	quint32 subdivCount = 0;
	quint32 levelsCount = levelsSize / 4;
	QVector<MapLevel> ml(levelsCount);
	QMap<int, int> level2bits;

	for (quint32 i = 0; i < levelsCount; i++) {
		quint8 *zoom = levels + (i * 4);
		ml[i].level = *zoom;
		ml[i].bits = *(zoom + 1);
		ml[i].subdivs = *(zoom + 2) | (quint16)(*(zoom + 3)) << 8;
		if ((ml[i].level & 0xF) > 15 || ml[i].bits > 24)
			return false;

		subdivCount += ml[i].subdivs;
		level2bits.insert(ml[i].level & 0xF, ml[i].bits);
	}

	// Subdivisions
	if (!seek(hdl, subdivOffset))
		return false;
	SubDiv *s = 0;

	for (int i = 0; i < ml.size(); i++) {
		if (!(ml.at(i).level & 0x80))
			_subdivs.insert(ml.at(i).bits, new SubDivTree());

		for (int j = 0; j < ml.at(i).subdivs; j++) {
			quint32 offset;
			qint32 lon, lat;
			quint8 objects;
			quint16 width, height, nextLevel;

			if (!(readUInt24(hdl, offset) && readByte(hdl, objects)
			  && readInt24(hdl, lon) && readInt24(hdl, lat)
			  && readUInt16(hdl, width) && readUInt16(hdl, height)))
				return false;
			if (i != (int)levelsCount - 1)
				if (!readUInt16(hdl, nextLevel))
					return false;

			if (ml.at(i).level & 0x80)
				continue;

			width &= 0x7FFF;
			width <<= (24 - ml.at(i).bits);
			height <<= (24 - ml.at(i).bits);

			if (s)
				s->setEnd(offset);
			s = new SubDiv(offset, lon, lat, width, height, ml.at(i).bits,
			  objects);

			double min[2], max[2];
			min[0] = s->bounds().left();
			min[1] = s->bounds().bottom();
			max[0] = s->bounds().right();
			max[1] = s->bounds().top();
			_subdivs[ml.at(i).bits]->Insert(min, max, s);
		}
	}

	if (!(parsePoly(hdl, 0x4A, level2bits, _lines)
	  && parsePoly(hdl, 0x58, level2bits, _polygons)
	  && parsePoints(hdl, 0x66, level2bits)))
		return false;

	return true;
}

static bool cb(SubDiv *subdiv, void *context)
{
	QList<SubDiv*> *list = (QList<SubDiv*>*)context;
	list->append(subdiv);
	return true;
}

QList<SubDiv*> TREFile::subdivs(const RectC &rect, int bits) const
{
	QList<SubDiv*> list;
	double min[2], max[2];

	min[0] = rect.left();
	min[1] = rect.bottom();
	max[0] = rect.right();
	max[1] = rect.top();

	_subdivs.value(bits)->Search(min, max, cb, &list);

	return list;
}
