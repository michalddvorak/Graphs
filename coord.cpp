#include "coord.h"

std::ostream &operator <<(std::ostream &os, const coord& pd)
{
	return os << "(" << pd.first << ", " << pd.second << ")";
}
