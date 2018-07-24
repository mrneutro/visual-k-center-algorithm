#include "Utils.h"
#include <math.h>
#include <QDebug>

uint Utils::get_max_dist(QList<City *> cities, QList<Warehouse *> wh)
{
    uint maxDist = 0;
    for(int i = 0; i < cities.length(); i++){
        City* victim = cities.at(i);
        uint min_for_victim = INT_MAX;
        for(int j = 0; j < wh.count(); j++){
            uint curr_dist = dist(victim, wh.at(j));
            if(curr_dist < min_for_victim){
                min_for_victim = curr_dist;
            }
        }
        maxDist += min_for_victim;
//        if(min_for_victim > maxDist){
//            maxDist = min_for_victim;
//        }
    }

    return maxDist;
}

uint Utils::dist(const City *c1, const Warehouse *c2)
{
    return sqrt((pow(c2->x()-c1->x(),2) + pow(c2->y()-c1->y(),2)));
}

quint64 Utils::choose(quint64 n, quint64 k)
{
    if (k > n) {
        return 0;
    }
    quint64 r = 1;
    for (quint64 d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}
