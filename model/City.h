#ifndef CITY_H
#define CITY_H
#include "Warehouse.h"

class City
{
public:
    City(int x, int y);

    int x() const;

    int y() const;

    Warehouse *wh() const;
    void setWh(Warehouse *wh);

private:
    int _x;
    int _y;
    Warehouse* _wh = nullptr;

};

#endif // CITY_H
