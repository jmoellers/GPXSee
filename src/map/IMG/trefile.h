#ifndef TREFILE_H
#define TREFILE_H

#include <QVector>
#include <QDebug>
#include <QRect>
#include "common/rectc.h"
#include "common/rtree.h"
#include "subfile.h"

class SubDiv;

class TREFile : public SubFile
{
public:
	TREFile(IMG *img, quint32 size) : SubFile(img, size) {}
	~TREFile();

	bool init();

	const RectC &bounds() const {return _bounds;}
	const QList<int> bits() const {return _subdivs.keys();}

	QList<SubDiv*> subdivs(const RectC &rect, int bits) const;

	bool showLine(int type, int bits) const
	  {return _lines.value(type) <= bits;}
	bool showPolygon(int type, int bits) const
	  {return _polygons.value(type) <= bits;}
	bool showPoint(int type, int subtype, int bits) const
	  {return _points.value(type<<8|subtype) <= bits;}

private:
	typedef RTree<SubDiv*, double, 2> SubDivTree;

	bool parsePoly(Handle hdl, quint32 pos, const QMap<int, int> &level2bits,
	  QMap<int, int> &map);
	bool parsePoints(Handle hdl, quint32 pos, const QMap<int, int> &level2bits);

	RectC _bounds;
	QMap<int, SubDivTree*> _subdivs;
	QMap<int, int> _lines, _polygons, _points;
};

#endif // TREFILE_H
