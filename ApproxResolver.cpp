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

QList<Warehouse *> ApproxResolver::resolve_immediatly()
{

    int current_city = std::rand() % _cities.size();

    while(_wh_map.count() < _center_count && current_city != -1){ // if current_city is -1 we have no choises
        City c = _cities.at(current_city);
        Warehouse *wh = new Warehouse(c.x(), c.y(), 0);
        //qDebug() << "KEY si" << gen_wh_key(wh);
        _wh_map.insert(gen_wh_key(wh), wh);
        current_city = fartherst_city_from_centers();
    }

    QList<Warehouse*> lst;
    QHashIterator<QString, Warehouse*> i(_wh_map);
    while (i.hasNext()) {
        i.next();
        lst.append(i.value());
    }

    return lst;
}

int ApproxResolver::fartherst_city_from_centers()
{
    int max_distance = 0;
    int max_distance_cid = -1; // its not a valid city id
    QHashIterator<QString, Warehouse*> i(_wh_map);
    while (i.hasNext()) {
        i.next();
        Warehouse *curr_wh = i.value();

        for(int city_id = 0; city_id < _cities.length(); city_id++){
            City curr_city = _cities.at(city_id);

            if(!_wh_map.contains(curr_city.x()+"-"+curr_city.y())){
                int distance = dist(curr_city, curr_wh);
                if(distance > max_distance){
                    max_distance_cid = city_id;
                    max_distance = distance;
                }
            }
        }
    }

    radius = max_distance;

    return max_distance_cid;
}

int ApproxResolver::dist(const City &c1, const Warehouse* c2)
{
    return sqrt((pow(c2->x()-c1.x(),2) + pow(c2->y()-c1.y(),2)));
}

QString ApproxResolver::gen_wh_key(const Warehouse* wh)
{
    return QString::number(wh->x())+"-"+QString::number(wh->y());
}

