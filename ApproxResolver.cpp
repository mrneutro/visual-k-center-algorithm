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

bool ApproxResolver::resolve()
{
    int random_city_id = std::rand() % _cities.size();
    qDebug() << "Random city is: " << random_city_id;
    int current_city = random_city_id;
    while(_center_in_city.count() < _center_count && current_city != -1){ // if current_city is -1 we have no choises
        _center_in_city.append(random_city_id);
        current_city = fartherst_city_from(random_city_id);
    }

    return true;
}

int ApproxResolver::fartherst_city_from(int indx)
{
    int max_distance = 0;
    int max_distance_cid = -1; // its not a valid city id
    for(int i = 0; i < _cities.length(); i++){
        if(!_center_in_city.contains(i)){
            int distance = dist(_cities.at(indx), _cities.at(i));
            if(distance > max_distance){
                max_distance_cid = j;
            }
        }
    }

    return max_distance_cid;
}

int ApproxResolver::dist(const City &c1, const City &c2)
{
    return round(sqrt((pow(c2.x()-c1.x(),2) + pow(c2.y()-c1.y(),2)))*100)/100;
}
