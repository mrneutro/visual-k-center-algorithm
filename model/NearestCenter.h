#ifndef NEARESTCENTER_H
#define NEARESTCENTER_H
#include "City.h"
#include "Warehouse.h"

class NearestCenter
{
public:
    NearestCenter(const City* _c, const Warehouse* _w, int d);

    City *city;
    Warehouse *warehouse;
    int distance = 0;
};

#endif // NEARESTCENTER_H
