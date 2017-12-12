#include "Utils.h"
#include <math.h>

Utils::Utils()
{

}

int Utils::getMinMaxDistance(QList<City *> cities, QList<Warehouse *> wh)
{
    int maxDist = 0;
    for(int i = 0; i < cities.length(); i++){
        City* victim = cities.at(i);
        for(int j = 0; j < wh.count(); j++){
            int curr_dist = dist(victim, wh.at(j));
            if(curr_dist > maxDist){
                maxDist = curr_dist;
            }
        }
    }
}

int Utils::dist(const City *c1, const Warehouse *c2)
{
    return sqrt((pow(c2->x()-c1->x(),2) + pow(c2->y()-c1->y(),2)));
}
