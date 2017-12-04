#include "ApproxResolver.h"
#include <math.h>
#include <ctime>
#include <QDebug>

ApproxResolver::ApproxResolver(QList<City> cities, int center_count)
{
    _cities = cities;
    _center_count = center_count;
    std::srand(std::time(0)); // use current time as seed for random generator
}

QList<Warehouse*> ApproxResolver::resolve_immediatly()
{
    QList<Warehouse*> wh;
    int current_city = std::rand() % _cities.size();
    int prev_city = current_city;
    while(_center_in_city.count() < _center_count && current_city != -1){ // if current_city is -1 we have no choises
        _center_in_city.append(current_city);
        current_city = fartherst_city_from(current_city);
        auto prev_city_obj = _cities.at(prev_city);
        Warehouse *w = new Warehouse(prev_city_obj.x(), prev_city_obj.y(), radius);
        wh.append(w);
        prev_city=current_city;
    }

    qDebug() << _center_in_city;

    return wh;
}

int ApproxResolver::fartherst_city_from(int indx)
{
    int max_distance = 0;
    int max_distance_cid = -1; // its not a valid city id
    for(int i = 0; i < _cities.length(); i++){
        if(!_center_in_city.contains(i)){
            int distance = dist(_cities.at(indx), _cities.at(i));
            if(distance > max_distance){
                max_distance_cid = i;
                max_distance = distance;
            }
        }
    }
    radius = max_distance;

    return max_distance_cid;
}

int ApproxResolver::dist(const City &c1, const City &c2)
{
    return sqrt((pow(c2.x()-c1.x(),2) + pow(c2.y()-c1.y(),2)));
}
