#ifndef APPROXRESOLVER_H
#define APPROXRESOLVER_H
#include <City.h>
#include <Center.h>
#include <QList>
#include "Warehouse.h"

class ApproxResolver
{
public:
    ApproxResolver(QList<City> cities, int center_count);
    //immediate solution
    QList<Warehouse *> resolve_immediatly();

    //
private:
    QList<City> _cities;
    QList<int> _center_in_city;
    int _center_count = 0;
    int fartherst_city_from(int indx);
    int dist(const City& c1, const City& c2);
    int radius = 0;
};

#endif // APPROXRESOLVER_H
