#include "ApproxResolver.h"
#include <math.h>
#include <ctime>
#include <QDebug>
#include "Utils.h"

ApproxResolver::ApproxResolver(QList<City*> cities, int center_count)
{
    qDebug() << "Started ApproxResolver";
    _cities = cities;
    _center_count = center_count;
    std::srand(std::time(0)); // use current time as seed for random generator
}

QList<Warehouse *> ApproxResolver::resolve_immediatly()
{
    start_timer();
    City *current_city = get_random_city();
    while(_wh.count() < _center_count && current_city != nullptr){ // if current_city is -1 we have no choises
        emit progressUpdate(_wh.count());
        Warehouse *wh = new Warehouse(current_city->x(), current_city->y(), 0);
        current_city->setWh(wh);

        _wh.append(wh);
        current_city = fartherst_city_from_centers();
    }
    stop_timer();
    _min_solution = Utils::get_max_dist(_cities, _wh);
    return _wh;
}

City* ApproxResolver::fartherst_city_from_centers()
{
#ifdef DEBUG
    qDebug() << "fartherst_city_from_centers";
    qDebug() << "Wh count " << _wh.size();
#endif
    NearestCenter* more_distanced_city = nullptr;
    for(int city_id = 0; city_id < _cities.length(); city_id++){
        City* curr_city = _cities.at(city_id);
        NearestCenter* nc = nearest_wh_from(curr_city);
        if(more_distanced_city != nullptr){
            if(nc->distance > more_distanced_city->distance){
                more_distanced_city = nc;
            }
        }else{
            more_distanced_city = nc;
        }
    }

    return more_distanced_city->city;
}

int ApproxResolver::dist(const City *c1, const Warehouse* c2)
{
    return sqrt((pow(c2->x()-c1->x(),2) + pow(c2->y()-c1->y(),2)));
}

NearestCenter* ApproxResolver::nearest_wh_from(const City* c)
{
    int minDist = INT_MAX;
    Warehouse* minDistWh = 0;


    for(int i = 0; i< _wh.size(); i++){
        Warehouse *curr_wh = _wh.at(i);
        int curr_dist = dist(c, curr_wh);
        if(curr_dist < minDist){
            minDist = curr_dist;
            minDistWh = curr_wh;
        }
    }

    return new NearestCenter(c, minDistWh, minDist);
}

City *ApproxResolver::get_random_city()
{
    int current_city = std::rand() % _cities.size();
#ifdef _DEBUG
    qDebug() << "Random city is" << current_city;
#endif
    return _cities.at(current_city);
}

