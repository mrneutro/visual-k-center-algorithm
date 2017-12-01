#ifndef APPROXRESOLVER_H
#define APPROXRESOLVER_H
#include <QHash>
#include <City.h>
#include <Center.h>

class ApproxResolver
{
public:
    ApproxResolver(QList<City> cities, int center_count);
    bool resolve();
private:
    QList<City> _cities;
    QList<int> _center_in_city;
    int _center_count = 0;
    int dist(const City& c1, const City& c2);
};

#endif // APPROXRESOLVER_H
