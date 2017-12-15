#ifndef APPROXRESOLVER_H
#define APPROXRESOLVER_H
#include <QObject>
#include <QList>
#include <model/City.h>
#include "model/Warehouse.h"
#include "model/NearestCenter.h"
#include "CenterResolver.h"

class ApproxResolver: public CenterResolver
{
public:
    ApproxResolver(QList<City *> cities, int center_count);
    //immediate solution
    QList<Warehouse *> resolve_immediatly() override;

    //
private:
    QList<City*> _cities;
    QList<Warehouse*> _wh;
    int _center_count = 0;
    City *fartherst_city_from_centers();
    int dist(const City* c1, const Warehouse* c2);
    NearestCenter* nearest_wh_from(const City *c);
    int radius = 0;
    City* get_random_city();

};

#endif // APPROXRESOLVER_H
