#include "Warehouse.h"

Warehouse::Warehouse(QObject *parent) : QObject(parent)
{

}

Warehouse::Warehouse(const Warehouse &wh)
{
    _x = wh.x();
    _y = wh.y();
    _radius = wh.radius();
}

Warehouse::Warehouse(int x, int y, int radius)
{
    _x = x;
    _y = y;
    _radius = radius;
}

int Warehouse::x() const
{
    return _x;
}

int Warehouse::y() const
{
    return _y;
}

int Warehouse::radius() const
{
    return _radius;
}
