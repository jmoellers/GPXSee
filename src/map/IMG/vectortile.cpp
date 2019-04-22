#include "vectortile.h"


SubFile *VectorTile::file(SubFile::Type type)
{
	switch (type) {
		case SubFile::TRE:
			return _tre;
		case SubFile::RGN:
			return _rgn;
		case SubFile::LBL:
			return _lbl;
		default:
			return 0;
	}
}
SubFile *VectorTile::addFile(SubFile::Type type, quint32 size)
{
	switch (type) {
		case SubFile::TRE:
			_tre = new TREFile(_img, size);
			break;
		case SubFile::RGN:
			_rgn = new RGNFile(_img, size);
			break;
		case SubFile::LBL:
			_lbl = new LBLFile(_img, size);
			break;
		default:
			break;
	}

	return file(type);
}

bool VectorTile::init()
{
	if (!(_tre && _tre->init() && _rgn && _rgn->init(_tre, _lbl)))
		return false;
	if (_lbl && !_lbl->init())
		return false;
	return true;
}

void VectorTile::objects(const RectC &rect, int bits,
  QList<IMG::Poly> &polygons, QList<IMG::Poly> &lines,
  QList<IMG::Point> &points) const
{
	QList<SubDiv*> subdivs = _tre->subdivs(rect, bits);
	for (int i = 0; i < subdivs.size(); i++)
		_rgn->objects(rect, subdivs.at(i), polygons, lines, points);
}

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const VectorTile &tile)
{
	dbg.nospace() << "VectorTile(";
	if (tile._tre)
		dbg << "TRE: " << *(tile._tre);
	if (tile._rgn)
		dbg << ", RGN: " << *(tile._rgn);
	if (tile._lbl)
		dbg << ", LBL: " << *(tile._lbl);
	dbg << ")";

	return dbg.space();
}
#endif // QT_NO_DEBUG
