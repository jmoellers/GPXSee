#ifndef IMG_H
#define IMG_H

#include <QRect>
#include <QFile>
#include <QByteArray>
#include <QCache>
#include <QDebug>
#include "common/rtree.h"
#include "common/rectc.h"
#include "style.h"

class VectorTile;
class SubFile;

class IMG
{
public:
	struct Poly {
		QVector<Coordinates> points;
		QString label;
		quint8 type;

		bool operator<(const Poly &other) const
		  {return type > other.type;}
	};

	struct Point {
		Coordinates coordinates;
		QString label;
		quint8 type, subtype;
		bool poi;
	};


	IMG(const QString &fileName);
	~IMG();

	const QString &name() const {return _name;}
	const RectC &bounds() const {return _bounds;}
	QList<int> bits() const {return _bits;}

	bool isValid() const {return _valid;}
	const QString &errorString() const {return _errorString;}

	void objects(const RectC &rect, int bits, QList<Poly> &polygons,
	  QList<Poly> &lines, QList<Point> &points) const;

	const Style &style() const {return _style;}

private:
	typedef QMap<QString, VectorTile*> TileMap;
	typedef RTree<VectorTile*, double, 2> TileTree;

	friend QDebug operator<<(QDebug dbg, const TileMap &map);
	friend class SubFile;

	int blockSize() const {return _blockSize;}
	QByteArray readBlock(int blockNum);
	qint64 read(char *data, qint64 maxSize);
	template<class T> bool readValue(T &val);

	QFile _file;
	quint8 _key;
	int _blockSize;
	QCache<int, QByteArray> _blockCache;
	TileMap _tileMap;
	TileTree _tileTree;

	QString _name;
	RectC _bounds;
	QList<int> _bits;
	Style _style;

	bool _valid;
	QString _errorString;
};

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const IMG::TileMap &map);
#endif // QT_NO_DEBUG

#endif // IMG_H
