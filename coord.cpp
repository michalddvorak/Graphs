#include "coord.h"
#include <iostream>

using namespace std;

ostream &operator <<(ostream &os, coord pd)
{
	return os << "(" << pd.first << ", " << pd.second << ")";
}
