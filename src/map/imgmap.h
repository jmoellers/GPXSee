#ifndef IMGMAP_H
#define IMGMAP_H

#include "map.h"
#include "projection.h"
#include "transform.h"
#include "common/range.h"
#include "IMG/img.h"


class IMGMap : public Map
{
	Q_OBJECT

public:
	IMGMap(const QString &fileName, QObject *parent = 0);

	QString name() const {return _img.name();}

	QRectF bounds();

	virtual int zoom() const {return _zoom;}
	virtual void setZoom(int zoom) {_zoom = zoom;}
	virtual int zoomFit(const QSize &, const RectC &);
	virtual int zoomIn();
	virtual int zoomOut();

	QPointF ll2xy(const Coordinates &c);
	Coordinates xy2ll(const QPointF &p);

	void draw(QPainter *painter, const QRectF &rect, Flags flags);

	bool isValid() const {return _valid;}
	QString errorString() const {return _errorString;}

private:
	friend class RasterTile;

	void updateTransform();
	void drawBitmapLine(QPainter *painter, const QPolygonF &line,
	  const QImage &img);
	void drawPolygons(QPainter *painter, const QList<IMG::Poly> &polygons);
	void drawLines(QPainter *painter, QList<IMG::Poly> &lines);
	void drawPoints(QPainter *painter, const QList<IMG::Point> &points);

	QString _fileName;
	IMG _img;
	int _zoom;
	Projection _projection;
	Transform _transform;

	bool _valid;
	QString _errorString;

	static QList<int> bits;
};

#endif // IMGMAP_H
