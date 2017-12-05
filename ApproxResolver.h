#ifndef APPROXRESOLVER_H
#define APPROXRESOLVER_H
#include <City.h>
#include <Center.h>
#include <QList>
#include "Warehouse.h"
#include <QHash>

class ApproxResolver
{
public:
    ApproxResolver(QList<City> cities, int center_count);
    //immediate solution
    QList<Warehouse *> resolve_immediatly();

    //
private:
    QList<City> _cities;
    QHash<QString, Warehouse*> _wh_map;
    int _center_count = 0;
    int fartherst_city_from_centers();
    int dist(const City& c1, const Warehouse* c2);
    int radius = 0;
    QString gen_wh_key(const Warehouse* wh);
};

#endif // APPROXRESOLVER_H
