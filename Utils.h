#ifndef UTILS_H
#define UTILS_H
#include <QList>
#include "City.h"
#include "Warehouse.h"


class Utils
{
public:
    Utils();
    static int get_max_dist(QList<City*> cities, QList<Warehouse*> wh);
    static int dist(const City* c1, const Warehouse* c2);
};

#endif // UTILS_H
