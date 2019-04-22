#ifndef UNITS_H
#define UNITS_H

inline double toWGS84(qint32 coord)
{
	return coord * 360.0 / (1<<24);
}

#endif // UNITS_H
