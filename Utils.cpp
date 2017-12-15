#include "Utils.h"
#include <math.h>
#include <QDebug>

Utils::Utils()
{

}

int Utils::get_max_dist(QList<City *> cities, QList<Warehouse *> wh)
{
    int maxDist = 0;
    for(int i = 0; i < cities.length(); i++){
        City* victim = cities.at(i);
        int min_for_victim = INT_MAX;
        for(int j = 0; j < wh.count(); j++){
            int curr_dist = dist(victim, wh.at(j));
            if(curr_dist < min_for_victim){
                min_for_victim = curr_dist;
            }
        }
        if(min_for_victim > maxDist){
            maxDist = min_for_victim;
        }
    }

    return maxDist;
}

int Utils::dist(const City *c1, const Warehouse *c2)
{
    return sqrt((pow(c2->x()-c1->x(),2) + pow(c2->y()-c1->y(),2)));
}

unsigned long long Utils::choose(unsigned long long n, unsigned long long k)
{
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}
