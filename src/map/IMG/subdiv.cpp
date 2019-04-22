#include "subdiv.h"

#ifndef QT_NO_DEBUG
QDebug operator<<(QDebug dbg, const SubDiv &subdiv)
{
	dbg.nospace() << "SubDiv(" << subdiv.bounds() << ", " << subdiv.offset()
	  << ", " << subdiv.end() << ", " << subdiv.objects() << ")";
	return dbg.space();
}
#endif // QT_NO_DEBUG
