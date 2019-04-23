#ifndef LBLFILE_H
#define LBLFILE_H

#include "subfile.h"

class LBLFile : public SubFile
{
public:
	LBLFile(IMG *img, quint32 size) : SubFile(img, size) {}

	bool init();

	QByteArray label(quint32 offset) const;

private:
	QByteArray label6b(quint32 offset) const;
	QByteArray label8b(quint32 offset) const;

	quint32 _offset;
	quint32 _size;
	quint8 _multiplier;
	quint8 _encoding;
};

#endif // LBLFILE_H
