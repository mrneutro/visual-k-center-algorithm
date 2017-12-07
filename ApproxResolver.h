#ifndef APPROXRESOLVER_H
#define APPROXRESOLVER_H
#include <QObject>
#include <City.h>
#include <QList>
#include "Warehouse.h"
#include <QHash>
#include "NearestCenter.h"

class ApproxResolver: public QObject
{
    Q_OBJECT
public:
    explicit ApproxResolver(QObject *parent = nullptr);
    ApproxResolver(QList<City *> cities, int center_count);
    //immediate solution
    QList<Warehouse *> resolve_immediatly();

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
signals:
    void progressUpdate(int val);
};

#endif // APPROXRESOLVER_H
