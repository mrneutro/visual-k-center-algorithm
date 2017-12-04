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

QList<int> ApproxResolver::resolve_immediatly()
{
    int current_city = std::rand() % _cities.size();
    while(_center_in_city.count() < _center_count && current_city != -1){ // if current_city is -1 we have no choises
        _center_in_city.append(current_city);
        current_city = fartherst_city_from(current_city);
    }

    qDebug() << _center_in_city;
    return _center_in_city;
}

int ApproxResolver::fartherst_city_from(int indx)
{
    int max_distance = 0;
    int max_distance_cid = -1; // its not a valid city id
    for(int i = 0; i < _cities.length(); i++){
        if(!_center_in_city.contains(i)){
            auto c = _cities.at(indx);
            auto c2 = _cities.at(i);
            int distance = dist(_cities.at(indx), _cities.at(i));
            if(distance > max_distance){
                max_distance_cid = i;
            }
        }
    }

    return max_distance_cid;
}

int ApproxResolver::dist(const City &c1, const City &c2)
{
    return sqrt((pow(c2.x()-c1.x(),2) + pow(c2.y()-c1.y(),2)));
}
