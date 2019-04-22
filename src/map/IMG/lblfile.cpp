#include "lblfile.h"

enum Charset {Normal, Symbol, Special};

static quint8 NORMAL_CHARS[] = {
	' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z',  '~', '~', '~', '~', '~',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '~', '~', '~', '~', '~', '~'
};

static quint8 SYMBOL_CHARS[] = {
	'@', '!', '"', '#', '$', '%', '&', '\'',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'~', '~', '~', '~', '~', '~', '~', '~',
	'~', '~', ':', ';', '<', '=', '>', '?',
	'~', '~', '~', '~', '~', '~', '~', '~',
	'~', '~', '~', '[', '\\', ']', '^', '_'
};

static quint8 SPECIAL_CHARS[] = {
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
	'x', 'y', 'z', '~', '~', '~', '~', '~',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '~', '~', '~', '~', '~', '~'
};


bool LBLFile::init()
{
	Handle hdl;

	if (!(seek(hdl, 0x15) && readUInt32(hdl, _offset)
	  && readUInt32(hdl, _size) && readByte(hdl, _multiplier)
	  && readByte(hdl, _encoding)))
		return false;

	_multiplier = 1<<_multiplier;

	return true;
}

QString LBLFile::label6b(quint32 offset) const
{
	Handle hdl;
	QByteArray result;
	Charset curCharSet = Normal;
	quint8 b1, b2, b3;

	if (!seek(hdl, offset))
		return QString();

	while (true) {
		if (!(readByte(hdl, b1) && readByte(hdl, b2) && readByte(hdl, b3)))
			return QString();

		int c[]= {b1>>2, (b1&0x3)<<4|b2>>4, (b2&0xF)<<2|b3>>6, b3&0x3F};

		for (int cpt = 0; cpt < 4; cpt++) {
			if (c[cpt] > 0x2F)
				return QString::fromLatin1(result);
			switch (curCharSet) {
				case Normal:
					if (c[cpt] == 0x1c)
						curCharSet = Symbol;
					else if (c[cpt] == 0x1b)
						curCharSet = Special;
					else if(c[cpt] == 0x1d)
						result.append('|');
					else if (c[cpt] == 0x1f)
						result.append(' ');
					else if (c[cpt] == 0x1e)
						result.append(' ');
					else
						result.append(NORMAL_CHARS[c[cpt]]);
					break;
				case Symbol:
					result.append(SYMBOL_CHARS[c[cpt]]);
					curCharSet = Normal;
					break;
				case Special:
					result.append(SPECIAL_CHARS[c[cpt]]);
					curCharSet = Normal;
					break;
			}
		}
	}
}

QString LBLFile::label8b(quint32 offset) const
{
	Handle hdl;
	QByteArray result;
	quint8 c;

	if (!seek(hdl, offset))
		return QString();

	while (true) {
		if (!readByte(hdl, c))
			return QString();
		if (!c)
			break;
		result.append(c);
	}

	return QString::fromLatin1(result);
}

QString LBLFile::label(quint32 offset) const
{
	if (offset * _multiplier >= _size)
		return QString();

	switch (_encoding) {
		case 6:
			return label6b(_offset + offset * _multiplier);
		case 9:
			return label8b(_offset + offset * _multiplier);
		default:
			return QString();
	}
}
