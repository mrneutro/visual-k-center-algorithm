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

Warehouse *City::wh() const
{
    return _wh;
}

void City::setWh(Warehouse *wh)
{
    _wh = wh;
}
