#ifndef UTILS_H
#define UTILS_H
#include <QList>

#include "model/City.h"
#include "model/Warehouse.h"


class Utils
{
public:
    static uint get_max_dist(QList<City*> cities, QList<Warehouse*> wh);
    static uint dist(const City* c1, const Warehouse* c2);
    static uint combinations(int n, int r);
    static quint64 choose(quint64 n, quint64 k);
};

#endif // UTILS_H
