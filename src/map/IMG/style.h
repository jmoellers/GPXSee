#ifndef STYLE_H
#define STYLE_H

#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QTextCodec>
#include "subfile.h"


class Style
{
public:
	class Polygon {
	public:
		Polygon() : _pen(Qt::NoPen), _brush(Qt::NoBrush) {}
		Polygon(const QPen &pen, const QBrush &brush)
		  : _pen(pen), _brush(brush) {}

		const QPen &pen() const {return _pen;}
		const QBrush &brush() const {return _brush;}

	private:
		QPen _pen;
		QBrush _brush;
	};

	class Line {
	public:
		Line() : _foreground(Qt::NoPen), _background(Qt::NoPen) {}
		Line(const QPen &foreground, const QPen &background = Qt::NoPen)
		  : _foreground(foreground), _background(background) {}
		Line(const QImage &img)
		  : _foreground(Qt::NoPen), _background(Qt::NoPen),
		  _img(img.convertToFormat(QImage::Format_ARGB32_Premultiplied)) {}

		const QPen &foreground() const {return _foreground;}
		const QPen &background() const {return _background;}
		const QImage &img() const {return _img;}

	private:
		QPen _foreground, _background;
		QImage _img;
	};

	class Point {
	public:
		Point() {}
		Point(const QImage &img) : _img(img) {}

		const QImage &img() const {return _img;}

	private:
		QImage _img;
	};


	Style(SubFile *typ = 0);

	const Line &line(quint8 type) const;
	const Polygon &polygon(quint8 type) const;
	const Point &point(quint8 type, quint8 subtype) const;
	const QList<quint8> &drawOrder() const {return _drawOrder;}
	const QTextCodec *codec() const {return _codec;}

private:
	struct Section {
		quint32 offset;
		quint32 size;
		quint32 arrayOffset;
		quint32 arraySize;
		quint16 arrayItemSize;
	};

	struct ItemInfo {
		quint32 offset;
		quint8 type;
		quint8 subtype;
	};

	bool parseTYPFile(SubFile *file);
	bool parsePoints(SubFile *file, SubFile::Handle &hdl,
	  const Section &section);
	bool parseLines(SubFile *file, SubFile::Handle &hdl,
	  const Section &section);
	bool parsePolygons(SubFile *file, SubFile::Handle &hdl,
	  const Section &section);
	bool parseDrawOrder(SubFile *file, SubFile::Handle &hdl,
	  const Section &section);
	bool itemInfo(SubFile *file, SubFile::Handle &hdl,
	  const Section &section, ItemInfo &info);
	void defaultPolygonStyle();
	void defaultLineStyle();

	QMap<quint8, Line> _lines;
	QMap<quint8, Polygon> _polygons;
	QMap<quint16, Point> _points;
	QList<quint8> _drawOrder;
	QTextCodec *_codec;
};

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const Style::Polygon &polygon);
QDebug operator<<(QDebug dbg, const Style::Line &line);
#endif // QT_NO_DEBUG

#endif // STYLE_H
