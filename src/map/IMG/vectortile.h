#ifndef VECTORTILE_H
#define VECTORTILE_H

#include "subfile.h"
#include "trefile.h"
#include "rgnfile.h"
#include "lblfile.h"

class IMG;

class VectorTile {
public:
	VectorTile(IMG *img) : _img(img), _tre(0), _rgn(0), _lbl(0) {}
	~VectorTile() {delete _tre; delete _rgn; delete _lbl;}

	bool init();

	const RectC &bounds() const {return _tre->bounds();}
	const QList<int> bits() const {return _tre->bits();}

	SubFile *file(SubFile::Type type);
	SubFile *addFile(SubFile::Type type, quint32 size);

	void objects(const RectC &rect, int bits, QList<IMG::Poly> &polygons,
	  QList<IMG::Poly> &lines, QList<IMG::Point> &points) const;

	friend QDebug operator<<(QDebug dbg, const VectorTile &tile);

private:
	IMG *_img;
	TREFile *_tre;
	RGNFile *_rgn;
	LBLFile *_lbl;
};

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const VectorTile &tile);
#endif // QT_NO_DEBUG

#endif // VECTORTILE_H
