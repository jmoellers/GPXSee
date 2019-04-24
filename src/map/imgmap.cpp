#include <QFile>
#include <QPainter>
#include <QPixmapCache>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtCore>
#else // QT_VERSION < 5
#include <QtConcurrent>
#endif // QT_VERSION < 5
#include "common/rectc.h"
#include "common/wgs84.h"
#include "pcs.h"
#include "rectd.h"
#include "imgmap.h"


#define TILE_SIZE 512
#define EXTENT 128

class RasterTile {
public:
	RasterTile() : _map(0) {}
	RasterTile(IMGMap *map, const QPoint &xy, const QString &key)
	  : _map(map), _xy(xy), _key(key),
	  _img(TILE_SIZE, TILE_SIZE, QImage::Format_ARGB32_Premultiplied) {}

	const QString &key() const {return _key;}
	const QPoint &xy() const {return _xy;}
	QImage &img() {return _img;}
	QList<IMG::Poly> &polygons() {return _polygons;}
	QList<IMG::Poly> &lines() {return _lines;}
	QList<IMG::Point> &points() {return _points;}

	void load()
	{
		_img.fill(Qt::white);

		QPainter painter(&_img);
		painter.setRenderHint(QPainter::SmoothPixmapTransform);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.translate(-_xy.x(), -_xy.y());

		_map->drawPolygons(&painter, _polygons);
		_map->drawLines(&painter, _lines);
		_map->drawPoints(&painter, _points);
	}

private:
	IMGMap *_map;
	QPoint _xy;
	QString _key;
	QImage _img;
	QList<IMG::Poly> _polygons;
	QList<IMG::Poly> _lines;
	QList<IMG::Point> _points;
};


IMGMap::IMGMap(const QString &fileName, QObject *parent)
  : Map(parent), _fileName(fileName), _img(fileName),
  _projection(PCS::pcs(3857)), _valid(false)
{
	if (!_img.isValid()) {
		_errorString = _img.errorString();
		return;
	}

	_zooms = Range(_img.zooms().min() - 1, 28);
	_zoom = _zooms.min();

	updateTransform();

	_valid = true;
}

QRectF IMGMap::bounds()
{
	RectD prect(_img.bounds(), _projection);
	return QRectF(_transform.proj2img(prect.topLeft()),
	  _transform.proj2img(prect.bottomRight()));
}

int IMGMap::zoomFit(const QSize &size, const RectC &rect)
{
	if (rect.isValid()) {
		QPointF sc((rect.right() - rect.left()) / size.width(),
		  (rect.top() - rect.bottom()) / size.height());
		double resolution = qMax(qAbs(sc.x()), qAbs(sc.y()));

		_zoom = _zooms.min();
		for (int i = _zooms.min(); i <= _zooms.max(); i++) {
			if (360.0 / (1<<i) < resolution)
				break;
			_zoom = i;
		}
	} else
		_zoom = _zooms.max();

	updateTransform();

	return _zoom;
}

int IMGMap::zoomIn()
{
	_zoom = qMin(_zoom + 1, _zooms.max());
	updateTransform();
	return _zoom;
}

int IMGMap::zoomOut()
{
	_zoom = qMax(_zoom - 1, _zooms.min());
	updateTransform();
	return _zoom;
}

static inline double bits2scale(int bits)
{
	return (2.0 * M_PI * WGS84_RADIUS) / (1<<bits);
}

void IMGMap::updateTransform()
{
	double scale = bits2scale(_zoom);
	PointD topLeft(_projection.ll2xy(_img.bounds().topLeft()));
	_transform = Transform(ReferencePoint(PointD(0, 0), topLeft),
	  PointD(scale, scale));
}

QPointF IMGMap::ll2xy(const Coordinates &c)
{
	return _transform.proj2img(_projection.ll2xy(c));
}

Coordinates IMGMap::xy2ll(const QPointF &p)
{
	return _projection.xy2ll(_transform.img2proj(p));
}


void IMGMap::drawPolygons(QPainter *painter, const QList<IMG::Poly> &polygons)
{
	for (int n = 0; n < _img.style().drawOrder().size(); n++) {
		for (int i = 0; i < polygons.size(); i++) {
			const IMG::Poly &p = polygons.at(i);
			if ((p.type & 0x7F) != _img.style().drawOrder().at(n))
				continue;
			const Style::Polygon &style = _img.style().polygon(p.type & 0x7F);

			QPolygonF polygon(p.points.size());
			for (int j = 0; j < p.points.size(); j++)
				polygon[j] = ll2xy(p.points.at(j));

			painter->setPen(style.pen());
			painter->setBrush(style.brush());
			painter->drawPolygon(polygon);
		}
	}
}

static QImage img2line(const QImage &img, int width)
{
	Q_ASSERT(img.format() == QImage::Format_ARGB32_Premultiplied);
	QImage res(width, img.height(), QImage::Format_ARGB32_Premultiplied);
	const int srcBpl = img.bytesPerLine();
	const int dstBpl = res.bytesPerLine();
	const uchar *srcBits = img.bits();
	uchar *dstBits = res.bits();

	for (int i = 0; i < img.height(); i++) {
		const uchar *srcLine = srcBits + srcBpl * i;
		uchar *dstLine = dstBits + dstBpl * i;

		for (int j = dstBpl; j > 0; j -= srcBpl, dstLine += srcBpl)
			memcpy(dstLine, srcLine, qMin(j, srcBpl));
	}

	return res;
}

void IMGMap::drawBitmapLine(QPainter *painter, const QPolygonF &line,
  const QImage &img)
{
	for (int i = 1; i < line.size(); i++) {
		QLineF segment(line.at(i-1).x(), line.at(i-1).y(), line.at(i).x(),
		  line.at(i).y());

		painter->save();
		painter->translate(segment.p1());
		painter->rotate(-segment.angle());
		painter->drawImage(0, -img.height()/2, img2line(img, segment.length()));
		painter->restore();
	}
}

void IMGMap::drawLines(QPainter *painter, QList<IMG::Poly> &lines)
{
	qStableSort(lines);

	painter->setBrush(Qt::NoBrush);

	for (int i = 0; i < lines.size(); i++) {
		const IMG::Poly &l = lines.at(i);
		const Style::Line &style = _img.style().line(l.type & 0x3F);

		if (style.background() == Qt::NoPen)
			continue;

		QPolygonF line(l.points.size());
		for (int j = 0; j < l.points.size(); j++)
			line[j] = ll2xy(l.points.at(j));

		painter->setPen(style.background());
		painter->drawPolyline(line);
	}

	for (int i = 0; i < lines.size(); i++) {
		const IMG::Poly &l = lines.at(i);
		const Style::Line &style = _img.style().line(l.type & 0x3F);

		QPolygonF line(l.points.size());
		for (int j = 0; j < l.points.size(); j++)
			line[j] = ll2xy(l.points.at(j));

		if (style.img().isNull()) {
			painter->setPen(style.foreground());
			painter->drawPolyline(line);
		} else
			drawBitmapLine(painter, line, style.img());
	}
}

#define FLAGS (Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip)

static QRectF textRect(const QString &text, const QFont &font, int maxWidth)
{
	QFontMetrics fm(font);
	int limit = font.pixelSize() * maxWidth;
	return fm.boundingRect(QRect(0, 0, limit, 0), FLAGS, text);
}

static void drawText(QPainter *painter, const QPointF &pos, const QString &text)
{
	QRectF tr(textRect(text, painter->font(), 8));

	painter->setPen(Qt::white);
	tr.moveCenter(QPointF(pos.x()-1, pos.y()-1));
	painter->drawText(tr, FLAGS, text);
	tr.moveCenter(QPointF(pos.x()+1, pos.y()+1));
	painter->drawText(tr, FLAGS, text);
	tr.moveCenter(QPointF(pos.x()-1, pos.y()+1));
	painter->drawText(tr, FLAGS, text);
	tr.moveCenter(QPointF(pos.x()+1, pos.y()-1));
	painter->drawText(tr, FLAGS, text);

	painter->setPen(Qt::black);
	tr.moveCenter(pos);
	painter->drawText(tr, FLAGS, text);
}

void IMGMap::drawPoints(QPainter *painter, const QList<IMG::Point> &points)
{
	QFont font(painter->font());
	font.setPixelSize(16);

	painter->setFont(font);
	const QTextCodec *codec = _img.style().codec();

	for (int i = 0; i < points.size(); i++) {
		const IMG::Point &p = points.at(i);
		const Style::Point &style = _img.style().point(p.type, p.subtype);

		if (!style.img().isNull())
			painter->drawImage(ll2xy(p.coordinates), style.img());
	}

	for (int i = 0; i < points.size(); i++) {
		const IMG::Point &p = points.at(i);

		if (!p.poi && !p.label.isNull()) {
			QString text(codec ? codec->toUnicode(p.label)
			  : QString::fromLatin1(p.label));
			drawText(painter, ll2xy(p.coordinates), text);
		}
	}
}

static void render(RasterTile &tile)
{
	tile.load();
}

void IMGMap::draw(QPainter *painter, const QRectF &rect, Flags flags)
{
	Q_UNUSED(flags);

	QPointF tl(floor(rect.left() / TILE_SIZE)
	  * TILE_SIZE, floor(rect.top() / TILE_SIZE) * TILE_SIZE);
	QSizeF s(rect.right() - tl.x(), rect.bottom() - tl.y());
	int width = ceil(s.width() / TILE_SIZE);
	int height = ceil(s.height() / TILE_SIZE);

	QList<RasterTile> tiles;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			QPixmap pm;
			QPoint ttl(tl.x() + i * TILE_SIZE, tl.y() + j * TILE_SIZE);
			QString key = _fileName + "-" + QString::number(_zoom) + "_"
			  + QString::number(ttl.x()) + "_" + QString::number(ttl.y());
			if (QPixmapCache::find(key, pm))
				painter->drawPixmap(ttl, pm);
			else {
				tiles.append(RasterTile(this, ttl, key));
				RasterTile &tile = tiles.last();
				RectD polyRect(_transform.img2proj(ttl), _transform.img2proj(
				  QPointF(ttl.x() + TILE_SIZE, ttl.y() + TILE_SIZE)));
				_img.objects(polyRect.toRectC(_projection, 4), _zoom,
				  &(tile.polygons()), &(tile.lines()), 0);
				RectD pointRect(_transform.img2proj(QPointF(ttl.x() - EXTENT,
				  ttl.y() - EXTENT)), _transform.img2proj(QPointF(ttl.x()
				  + TILE_SIZE + EXTENT, ttl.y() + TILE_SIZE + EXTENT)));
				_img.objects(pointRect.toRectC(_projection, 4), _zoom,
				  0, 0, &(tile.points()));
			}
		}
	}

	QFuture<void> future = QtConcurrent::map(tiles, render);
	future.waitForFinished();

	for (int i = 0; i < tiles.size(); i++) {
		RasterTile &mt = tiles[i];
		QPixmap pm(QPixmap::fromImage(mt.img()));
		if (pm.isNull())
			continue;

		QPixmapCache::insert(mt.key(), pm);

		painter->drawPixmap(mt.xy(), pm);
	}

/*
	QList<IMG::Poly> polygons, lines;
	QList<IMG::Point> points;

	RectD prect(_transform.img2proj(rect.topLeft()), _transform.img2proj(
	  rect.bottomRight()));
	_img.objects(prect.toRectC(_projection), _zoom, polygons,
	  lines, points);

	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	drawPolygons(painter, polygons);
	drawLines(painter, lines);
	drawPoints(painter, points);
*/
}
