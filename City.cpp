#include "City.h"

City::City(int x, int y)
{
    _x = x;
    _y = y;
}

int City::x() const
{
    return _x;
}

int City::y() const
{
    return _y;
}
