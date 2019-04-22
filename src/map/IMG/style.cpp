#include <QImage>
#include "style.h"


void Style::defaultPolygonStyle()
{
	_polygons[0x01] = Style::Polygon(Qt::NoPen, QBrush("#d2c0c0"));
	_polygons[0x02] = Style::Polygon(Qt::NoPen, QBrush("#fbeab7"));
	_polygons[0x03] = Style::Polygon(Qt::NoPen, QBrush("#a4b094"));
	_polygons[0x04] = Style::Polygon(Qt::NoPen, QBrush("#808080"));
	_polygons[0x05] = Style::Polygon(Qt::NoPen, QBrush("#f0f0f0"));
	_polygons[0x06] = Style::Polygon(Qt::NoPen, QBrush("#cacaca"));
	_polygons[0x07] = Style::Polygon(Qt::NoPen, QBrush("#feebcf"));
	_polygons[0x08] = Style::Polygon(Qt::NoPen, QBrush("#fde8d5"));
	_polygons[0x09] = Style::Polygon(Qt::NoPen, QBrush("#fee8b8"));
	_polygons[0x0a] = Style::Polygon(Qt::NoPen, QBrush("#fdeac6"));
	_polygons[0x0b] = Style::Polygon(Qt::NoPen, QBrush("#fddfbd"));
	_polygons[0x0c] = Style::Polygon(Qt::NoPen, QBrush("#ebeada"));
	_polygons[0x0d] = Style::Polygon(Qt::NoPen, QBrush("#f8e3be"));
	_polygons[0x0e] = Style::Polygon(Qt::NoPen, QBrush("#e0e0e0"));
	_polygons[0x0f] = Style::Polygon(Qt::NoPen, QBrush("#cc9900"));
	_polygons[0x10] = Style::Polygon(Qt::NoPen, QBrush("#cc9900"));
	_polygons[0x11] = Style::Polygon(Qt::NoPen, QBrush("#cc9900"));
	_polygons[0x12] = Style::Polygon(Qt::NoPen, QBrush("#cc9900"));
	_polygons[0x13] = Style::Polygon(Qt::NoPen, QBrush("#cc9900"));
	_polygons[0x14] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x15] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x16] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x17] = Style::Polygon(Qt::NoPen, QBrush("#90be00"));
	_polygons[0x18] = Style::Polygon(Qt::NoPen, QBrush("#00ff00"));
	_polygons[0x19] = Style::Polygon(Qt::NoPen, QBrush("#f8e3be"));
	_polygons[0x1a] = Style::Polygon(Qt::NoPen, QBrush("#d3f5a5"));
	_polygons[0x1e] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x1f] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x20] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x28] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x29] = Style::Polygon(Qt::NoPen, QBrush("#0000ff"));
	_polygons[0x32] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x3b] = Style::Polygon(Qt::NoPen, QBrush("#0000ff"));
	_polygons[0x3c] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x3d] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x3e] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x3f] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x40] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x41] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x42] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x43] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x44] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x45] = Style::Polygon(Qt::NoPen, QBrush("#0000ff"));
	_polygons[0x46] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x47] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x48] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x49] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x4a] = Style::Polygon(QPen("#000000"), QBrush(Qt::NoBrush));
	_polygons[0x4b] = Style::Polygon(QPen("#000000"), QBrush(Qt::NoBrush));
	_polygons[0x4c] = Style::Polygon(Qt::NoPen, QBrush("#f0e68c"));
	_polygons[0x4d] = Style::Polygon(Qt::NoPen, QBrush("#00ffff"));
	_polygons[0x4e] = Style::Polygon(Qt::NoPen, QBrush("#d3f5a5"));
	_polygons[0x4f] = Style::Polygon(Qt::NoPen, QBrush("#d3f5a5"));
	_polygons[0x50] = Style::Polygon(Qt::NoPen, QBrush("#b7e999"));
	_polygons[0x51] = Style::Polygon(Qt::NoPen, QBrush("#0000ff"));
	_polygons[0x52] = Style::Polygon(Qt::NoPen, QBrush("#4aca4a"));
	_polygons[0x53] = Style::Polygon(Qt::NoPen, QBrush("#bcedfa"));
	_polygons[0x54] = Style::Polygon(Qt::NoPen, QBrush("#fde8d5"));
	_polygons[0x59] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));
	_polygons[0x69] = Style::Polygon(Qt::NoPen, QBrush("#0080ff"));

	_drawOrder = _polygons.keys();
}

void Style::defaultLineStyle()
{
	_lines[0x01] = Style::Line(QPen(Qt::red, 6, Qt::SolidLine),
	  QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x02] = Style::Line(QPen(QColor("#cc9900"), 4, Qt::SolidLine),
	  QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x03] = Style::Line(QPen(Qt::yellow, 3, Qt::SolidLine),
	  QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x04] = Style::Line(QPen(QColor("#ffff00"), 3, Qt::SolidLine),
	  QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x05] = Style::Line(QPen(QColor("#dc7c5a"), 2, Qt::SolidLine));
	_lines[0x06] = Style::Line(QPen(Qt::gray, 2, Qt::SolidLine),
	  QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x07] = Style::Line(QPen(QColor("#c46442"), 1, Qt::SolidLine));
	_lines[0x08] = Style::Line(QPen(QColor("#e88866"), 2, Qt::SolidLine));
	_lines[0x09] = Style::Line(QPen(QColor("#e88866"), 2, Qt::SolidLine));
	_lines[0x0A] = Style::Line(QPen(QColor("#808080"), 2, Qt::SolidLine));
	_lines[0x0B] = Style::Line(QPen(QColor("#c46442"), 2, Qt::SolidLine));
	_lines[0x0C] = Style::Line(QPen(QColor("#000000"), 2, Qt::SolidLine));
	_lines[0x14] = Style::Line(QPen(Qt::white, 2, Qt::DotLine),
	  QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	_lines[0x15] = Style::Line(QPen(QColor("#000080"), 2, Qt::SolidLine));
	_lines[0x16] = Style::Line(QPen(QColor("#E0E0E0"), 1, Qt::SolidLine));
	_lines[0x18] = Style::Line(QPen(QColor("#0000ff"), 2, Qt::SolidLine));
	_lines[0x19] = Style::Line(QPen(QColor("#00ff00"), 2, Qt::SolidLine));
	_lines[0x1A] = Style::Line(QPen(QColor("#000000"), 2, Qt::SolidLine));
	_lines[0x1B] = Style::Line(QPen(QColor("#000000"), 2, Qt::SolidLine));
	_lines[0x1C] = Style::Line(QPen(QColor("#00c864"), 2, Qt::DotLine));
	_lines[0x1D] = Style::Line(QPen(QColor("#00c864"), 2, Qt::DotLine));
	_lines[0x1E] = Style::Line(QPen(QColor("#00c864"), 2, Qt::DotLine));
	_lines[0x1F] = Style::Line(QPen(QColor("#0000ff"), 2, Qt::SolidLine));
	_lines[0x20] = Style::Line(QPen(QColor("#b67824"), 1, Qt::SolidLine));
	_lines[0x21] = Style::Line(QPen(QColor("#b67824"), 2, Qt::SolidLine));
	_lines[0x22] = Style::Line(QPen(QColor("#b67824"), 3, Qt::SolidLine));
	_lines[0x23] = Style::Line(QPen(QColor("#b67824"), 1, Qt::SolidLine));
	_lines[0x24] = Style::Line(QPen(QColor("#b67824"), 2, Qt::SolidLine));
	_lines[0x25] = Style::Line(QPen(QColor("#b67824"), 3, Qt::SolidLine));
	_lines[0x26] = Style::Line(QPen(QColor("#0000ff"), 2, Qt::DotLine));
	_lines[0x27] = Style::Line(QPen(QColor("#c46442"), 4, Qt::SolidLine));
	_lines[0x28] = Style::Line(QPen(QColor("#aa0000"), 2, Qt::SolidLine));
	_lines[0x29] = Style::Line(QPen(QColor("#ff0000"), 2, Qt::SolidLine));
	_lines[0x2A] = Style::Line(QPen(QColor("#000000"), 2, Qt::SolidLine));
	_lines[0x2B] = Style::Line(QPen(QColor("#000000"), 2, Qt::SolidLine));
}

static bool readBitmap(SubFile *file, SubFile::Handle &hdl, QImage &img,
  int bpp)
{
	for (int y = 0; y < img.height(); y++) {
		for (int x = 0; x < img.width(); x += 8/bpp) {
			quint8 color;
			if (!file->readByte(hdl, color))
				return false;

			for (int i = 0; i < 8/bpp && x + i < img.width(); i++) {
				int value = (i > 0) ? (color >>= bpp) : color;

				if (bpp == 4)
					value = value & 0xf;
				else if (bpp == 2)
					value = value & 0x3;
				else if (bpp == 1)
					value = value & 0x1;

				img.setPixel(x + i, y, value);
			}
		}
	}

	return true;
}

static bool readColor(SubFile *file, SubFile::Handle &hdl, QColor &color)
{
	quint8 b, g, r;

	if (!(file->readByte(hdl, b) && file->readByte(hdl, g)
	  && file->readByte(hdl, r)))
		return false;

	color = qRgb(r, g, b);

	return true;
}


bool Style::itemInfo(SubFile *file, SubFile::Handle &hdl,
  const Section &section, ItemInfo &info)
{
	quint16 t16_1, t16_2;
	quint8 t8;

	if (section.arrayItemSize == 5) {
		if (!(file->readUInt16(hdl, t16_1) && file->readUInt16(hdl, t16_2)
		  && file->readByte(hdl, t8)))
			return false;
		info.offset = t16_2 | (t8<<16);
	} else if (section.arrayItemSize == 4) {
		if (!(file->readUInt16(hdl, t16_1) && file->readUInt16(hdl, t16_2)))
			return false;
		info.offset = t16_2;
	} else if (section.arrayItemSize == 3) {
		if (!(file->readUInt16(hdl, t16_1) && file->readByte(hdl, t8)))
			return false;
		info.offset = t8;
	} else
		return false;

	t16_2 = (t16_1 >> 5) | (( t16_1 & 0x1f) << 11);
	info.type = t16_2 & 0x7F;
	info.subtype  = t16_1 & 0x1F;

	return true;
}

bool Style::parsePolygons(SubFile *file, SubFile::Handle &hdl,
  const Section &section)
{
	for (quint32 i = 0; i < section.arraySize / section.arrayItemSize; i++) {
		if (!file->seek(hdl, section.arrayOffset + i * section.arrayItemSize))
			return false;
		ItemInfo info;
		if (!itemInfo(file, hdl, section, info))
			return false;
		if (info.subtype)
			continue;

		quint8 t8, flags;
		if (!(file->seek(hdl, section.offset + info.offset)
		  && file->readByte(hdl, t8)))
			return false;
		flags = t8 & 0x0F;

		QColor c1, c2, c3, c4;
		QImage img(32, 32, QImage::Format_Indexed8);

		switch (flags) {
			case 0x01: // day & night brush + pen colors
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3) && readColor(file, hdl, c4)))
					return false;
				_polygons[info.type] = Style::Polygon(QPen(c3, 2), QBrush(c1));
				break;

			case 0x06: // day & night single brush color
			case 0x07: // day single brush color & night single brush color
				if (!readColor(file, hdl, c1))
					return false;
				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(c1));
				break;

			case 0x08: // day & night two brush colors
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)))
					return false;

				img.setColorCount(2);
				img.setColor(0, c2.rgb());
				img.setColor(1, c1.rgb());
				if (!readBitmap(file, hdl, img, 1))
					return false;

				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(img));
				break;

			case 0x09: // day two brush colors & night two brush colors
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3) && readColor(file, hdl, c4)))
					return false;

				img.setColorCount(2);
				img.setColor(0, c2.rgb());
				img.setColor(1, c1.rgb());
				if (!readBitmap(file, hdl, img, 1))
					return false;

				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(img));
				break;

			case 0x0B: // day one brush color, transparent & night two colors
			case 0x0D: // day two brush colors & night one brush color, transparent
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3)))
					return false;

				img.setColorCount(2);
				img.setColor(0, (flags == 0x0B) ? qRgba(255, 255, 255, 0)
				  : c2.rgb());
				img.setColor(1, c1.rgb());
				if (!readBitmap(file, hdl, img, 1))
					return false;

				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(img));
				break;

			case 0x0E: // day & night one color, transparent
				if (!readColor(file, hdl, c1))
					return false;

				img.setColorCount(2);
				img.setColor(0, qRgba(255, 255, 255, 0));
				img.setColor(1, c1.rgb());
				if (!readBitmap(file, hdl, img, 1))
					return false;

				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(img));
				break;

			case 0x0F: // day one color, transparent & night one color, transparent
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)))
					return false;

				img.setColorCount(2);
				img.setColor(0, qRgba(255, 255, 255, 0));
				img.setColor(1, c1.rgb());
				if (!readBitmap(file, hdl, img, 1))
					return false;

				_polygons[info.type] = Style::Polygon(Qt::NoPen, QBrush(img));
				break;

			default:
				qDebug() << info.type << ": unknown polygon color definition type:"
				  << flags;
		}
	}

	return true;
}

bool Style::parseLines(SubFile *file, SubFile::Handle &hdl,
  const Section &section)
{
	for (quint32 i = 0; i < section.arraySize / section.arrayItemSize; i++) {
		if (!file->seek(hdl, section.arrayOffset + i * section.arrayItemSize))
			return false;
		ItemInfo info;
		if (!itemInfo(file, hdl, section, info))
			return false;
		if (info.subtype)
			continue;

		quint8 t8_1, t8_2, flags, rows;
		if (!(file->seek(hdl, section.offset + info.offset)
		  && file->readByte(hdl, t8_1) && file->readByte(hdl, t8_2)))
			return false;
		flags = t8_1 & 0x07;
		rows = t8_1 >> 3;

		QColor c1, c2, c3, c4;
		quint8 w1, w2;

		switch (flags) {
			case 0x00:
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, c2.rgb());
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!(file->readByte(hdl, w1) && file->readByte(hdl, w2)))
						return false;

					_lines[info.type] = (w2 > w1)
					  ? Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin), QPen(c2, w2, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin))
					  : Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin));
				}
				break;

			case 0x01:
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3) && readColor(file, hdl, c4)))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, c2.rgb());
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!(file->readByte(hdl, w1) && file->readByte(hdl, w2)))
						return false;

					_lines[info.type] = (w2 > w1)
					  ? Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin), QPen(c2, w2, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin))
					  : Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin));
				}
				break;

			case 0x03:
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3)))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, qRgba(255, 255, 255, 0));
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!(file->readByte(hdl, w1) && file->readByte(hdl, w2)))
						return false;

					_lines[info.type] = Style::Line(QPen(c1, w1, Qt::SolidLine,
					  Qt::RoundCap, Qt::RoundJoin));
				}
				break;

			case 0x05:
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)
				  && readColor(file, hdl, c3)))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, c2.rgb());
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!(file->readByte(hdl, w1) && file->readByte(hdl, w2)))
						return false;

					_lines[info.type] = (w2 > w1)
					  ? Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin), QPen(c2, w2, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin))
					  : Style::Line(QPen(c1, w1, Qt::SolidLine, Qt::RoundCap,
						Qt::RoundJoin));
				}
				break;

			case 0x06:
				if (!readColor(file, hdl, c1))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, qRgba(255, 255, 255, 0));
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!file->readByte(hdl, w1))
						return false;

					_lines[info.type] = Style::Line(QPen(c1, w1, Qt::SolidLine,
					  Qt::RoundCap, Qt::RoundJoin));
				}
				break;

			case 0x07:
				if (!(readColor(file, hdl, c1) && readColor(file, hdl, c2)))
					return false;

				if (rows) {
					QImage img(32, rows, QImage::Format_Indexed8);
					img.setColorCount(2);
					img.setColor(0, qRgba(255,255,255,0));
					img.setColor(1, c1.rgb());
					if (!readBitmap(file, hdl, img, 1))
						return false;

					_lines[info.type] = Style::Line(img);
				} else {
					if (!file->readByte(hdl, w1))
						return false;

					_lines[info.type] = Style::Line(QPen(c1, w1, Qt::SolidLine,
					  Qt::RoundCap, Qt::RoundJoin));
				}
				break;

			default:
				qDebug() << info.type << ": unknown polyline color definition type:"
				  << flags;
		}
	}

	return true;
}

static int colors2bpp(quint8 colors, quint8 flags)
{
	switch (flags) {
		case 0x00:
			if (colors < 3)
				return colors;
			else if (colors == 3)
				return 2;
			else if (colors < 16)
				return 4;
			else
				return 8;
		case 0x10:
			if (colors == 0)
				return 1;
			else if (colors < 3)
				return 2;
			else if (colors < 15)
				return 4;
			else
				return 8;
		case 0x20:
			if (colors == 0)
				return 16;
			else if (colors < 3)
				return colors;
			else if (colors < 4)
				return 2;
			else if (colors < 16)
				return 4;
			else
				return 8;
		default:
			return -1;
	}
}

static bool readColorTable(SubFile *file, SubFile::Handle &hdl, QImage& img,
  int colors, int bpp, bool transparent)
{
	int i;

	img.setColorCount(colors);

	if (transparent) {
		quint8 byte;
		quint32 bits = 0, reg = 0, mask = 0x000000FF;

		for (i = 0; i < colors; i++) {
			while (bits < 28) {
				if (!file->readByte(hdl, byte))
					return false;

				mask = 0x000000FF << bits;
				reg  = reg  & (~mask);
				reg  = reg  | (byte << bits);
				bits += 8;
			}

			img.setColor(i, qRgba((reg >> 16) & 0x0FF, (reg >> 8) & 0x0FF,
			  reg & 0x0FF, ~((reg >> 24) & 0x0F) << 4));

			reg   = reg >> 28;
			bits -= 28;
		}
		for(; i < 1<<bpp; i++)
			img.setColor(i, qRgba(0, 0, 0, 0));
	} else {
		quint8 r, g, b;

		for (i = 0; i < colors; i++) {
			if (!(file->readByte(hdl, b) && file->readByte(hdl, g)
			  && file->readByte(hdl, r)))
				return false;
			img.setColor(i, qRgb(r, g, b));
		}
		for(; i < 1<<bpp; i++)
			img.setColor(i, qRgba(0, 0, 0, 0));
	}

	return true;
}

bool Style::parsePoints(SubFile *file, SubFile::Handle &hdl,
  const Section &section)
{
	for (quint32 i = 0; i < section.arraySize / section.arrayItemSize; i++) {
		if (!file->seek(hdl, section.arrayOffset + i * section.arrayItemSize))
			return false;
		ItemInfo info;
		if (!itemInfo(file, hdl, section, info))
			return false;

		quint8 t8_1, width, height, numColors, flags;
		if (!(file->seek(hdl, section.offset + info.offset)
		  && file->readByte(hdl, t8_1) && file->readByte(hdl, width)
		  && file->readByte(hdl, height) && file->readByte(hdl, numColors)
		  && file->readByte(hdl, flags)))
			return false;

		int bpp = colors2bpp(numColors, flags);
		QImage img(width, height, QImage::Format_Indexed8);
		if (!readColorTable(file, hdl, img, numColors, bpp, flags == 0x20))
			return false;
		if (!readBitmap(file, hdl, img, bpp))
			return false;

		_points[info.type<<8|info.subtype] = Point(img);
	}

	return true;
}

bool Style::parseDrawOrder(SubFile *file, SubFile::Handle &hdl,
  const Section &order)
{
	if (!file->seek(hdl, order.arrayOffset))
		return false;

	for (quint32 i = 0; i < order.arraySize / order.arrayItemSize; i++) {
		quint8 type;
		quint32 subtype;

		if (!(file->readByte(hdl, type) && file->readUInt32(hdl, subtype)))
			return false;

		if (!subtype && _drawOrder.indexOf(type) == -1)
			_drawOrder.append(type);
	}

	return true;
}

bool Style::parseTYPFile(SubFile *file)
{
	SubFile::Handle hdl;
	Section points, lines, polygons, order;
	quint16 tmp16;

	if (!(file->seek(hdl, 0x17) && file->readUInt32(hdl, points.offset)
	  && file->readUInt32(hdl, points.size)
	  && file->readUInt32(hdl, lines.offset)
	  && file->readUInt32(hdl, lines.size)
	  && file->readUInt32(hdl, polygons.offset)
	  && file->readUInt32(hdl, polygons.size)))
		return false;

	if (!(file->readUInt16(hdl, tmp16) && file->readUInt16(hdl, tmp16)))
		return false;

	if (!(file->readUInt32(hdl, points.arrayOffset)
	  && file->readUInt16(hdl, points.arrayItemSize)
	  && file->readUInt32(hdl, points.arraySize)
	  && file->readUInt32(hdl, lines.arrayOffset)
	  && file->readUInt16(hdl, lines.arrayItemSize)
	  && file->readUInt32(hdl, lines.arraySize)
	  && file->readUInt32(hdl, polygons.arrayOffset)
	  && file->readUInt16(hdl, polygons.arrayItemSize)
	  && file->readUInt32(hdl, polygons.arraySize)
	  && file->readUInt32(hdl, order.arrayOffset)
	  && file->readUInt16(hdl, order.arrayItemSize)
	  && file->readUInt32(hdl, order.arraySize)))
		return false;

	return parsePoints(file, hdl, points) && parseLines(file, hdl, lines)
	  && parsePolygons(file, hdl, polygons) && parseDrawOrder(file, hdl, order);
}

Style::Style(SubFile *typ)
{
	if (!(typ && parseTYPFile(typ))) {
		defaultLineStyle();
		defaultPolygonStyle();
	}
}

const Style::Line &Style::line(quint8 type) const
{
	static Line null;

	QMap<quint8, Line>::const_iterator it = _lines.find(type);
	return (it == _lines.constEnd()) ? null : *it;
}

const Style::Polygon &Style::polygon(quint8 type) const
{
	static Polygon null;

	QMap<quint8, Polygon>::const_iterator it = _polygons.find(type);
	return (it == _polygons.constEnd()) ? null : *it;
}

const Style::Point &Style::point(quint8 type, quint8 subtype) const
{
	static Point null;

	QMap<quint16, Point>::const_iterator it = _points.find(type<<8|subtype);
	return (it == _points.constEnd()) ? null : *it;
}

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const Style::Polygon &polygon)
{
	dbg.nospace() << "Polygon(" << polygon.brush() << ", " << polygon.pen()
	  << ")";
	return dbg.space();
}

QDebug operator<<(QDebug dbg, const Style::Line &line)
{
	dbg.nospace() << "Line(" << line.foreground() << ", " << line.background()
	  << ", " << line.img() << ")";
	return dbg.space();
}
#endif // QT_NO_DEBUG
