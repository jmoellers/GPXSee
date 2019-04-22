#ifndef SUBDIV_H
#define SUBDIV_H

#include <QRect>
#include "common/rectc.h"
#include "units.h"

class SubDiv {
public:
	SubDiv(quint32 offset, qint32 lon, qint32 lat, quint16 width,
	  quint16 height, int bits, quint8 objects) : _offset(offset), _end(0),
	  _lon(lon), _lat(lat), _width(width), _height(height), _bits(bits),
	  _objects(objects) {}
	void setEnd(quint32 end) {_end = end;}

	quint32 offset() const {return _offset;}
	quint32 end() const {return _end;}
	qint32 lon() const {return _lon;}
	qint32 lat() const {return _lat;}
	int bits() const {return _bits;}

	const RectC bounds() const
	{
		return RectC(Coordinates(toWGS84(_lon - _width),
		  toWGS84(_lat + _height + 1)), Coordinates(toWGS84(_lon + _width + 1),
		  toWGS84(_lat - _height)));
	}
	quint8 objects() const {return _objects;}

private:
	quint32 _offset;
	quint32 _end;
	qint32 _lon, _lat;
	quint16 _width, _height;
	int _bits;
	quint8 _objects;
};

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const SubDiv &subdiv);
#endif // QT_NO_DEBUG

#endif // SUBDIV_H
