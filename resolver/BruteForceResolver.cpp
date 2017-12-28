#include "BruteForceResolver.h"
#include <QDebug>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"
#include <math.h>

unsigned int count = 0;
clock_t start;

BruteForceResolver::BruteForceResolver(QList<City *> cities, int center_count)
{
    qDebug() << "Started ApproxResolver";

    _cities = cities;
    _center_count = center_count;
}

BruteForceResolver::~BruteForceResolver()
{
    if(_map!=nullptr){
        delete _map;
    }
}

QList<Warehouse *> BruteForceResolver::resolve_immediatly()
{
    start_timer();
    optimize_input();

    emit progressMaxVal(_possible_solutions = Utils::choose(_width*_height, _center_count)); // \todo solve implicit conversation from quint64 to int

    _map = (char*)malloc(_width*_height);
    if(!_map){
        qFatal("Cant allocate memory");
    }

    memset(_map, 'E', _width*_height);
    memset(_map, 'F', _center_count);
    _map[_width*_height]=0x00;

    calc(_map);

    free(_map);
    _map = nullptr;
    stop_timer();

    return _solutions;
}

void BruteForceResolver::fill(int *rep_char,char *temp_buff) {
    if(stop) return;

    int z=1;
    //loop on the chars, and check if should use them
    for (int i=0; i<256; i++)
        if (rep_char[i] != 0) {
            int l=strlen(temp_buff);
            //printf("%d\n", l);
            temp_buff[l]=i; // puts i-character(ascii) to output string
            rep_char[i]--; //decrements i-charcter count
            fill(rep_char,temp_buff);

            //restore the situation
            temp_buff[l]=0;
            rep_char[i]++;
            z=0;
        }
    if (z==1){
        //        clock_t end = clock();
        //        float seconds = (float)(end - start) / CLOCKS_PER_SEC;

        //        start = clock();
        evaluate_solution(temp_buff);
        //        printf("%s\n", temp_buff);
    }
}

void BruteForceResolver::calc(const char *str) {
    int repetion_of_char[256]={0};
    int l=strlen(str);
    qDebug() << "Strlen" << l;
    char* temp_buff =(char*)malloc(l+1);
    if(temp_buff == NULL){
        qDebug() << "Allocation 2 failed";
    }
    memset(temp_buff, 0x00, l+1);

    while(*str){
        repetion_of_char[*str++]++; // count how many ripetitions of chars are
    }

    fill(repetion_of_char,temp_buff);
}

void BruteForceResolver::optimize_input()
{
    City* xmin;
    City* xmax;
    City* ymin;
    City* ymax;
    xmin = xmax = ymin = ymax = _cities.at(0);

    for(int i=0; i< _cities.length(); i++){
        auto victim = _cities.at(i);
        if(victim->x() < xmin->x()){
            xmin = victim;
        }
        if(victim->x() > xmax->x()){
            xmax = victim;
        }
        if(victim->y() < ymin->y()){
            ymin = victim;
        }
        if(victim->y() > ymax->y()){
            ymax = victim;
        }
    }

    _shiftx = xmin->x();
    _shifty = ymin->y();

    _width = xmax->x()-xmin->x()+1;
    _height = ymax->y()-ymin->y()+1;

    _height = _height/_precision;
    _width = _width/_precision;
}

void BruteForceResolver::setPrecision(int precision)
{
    _precision = precision*cos(45)*2;
}

void BruteForceResolver::evaluate_solution(const char *solution)
{
    QList<Warehouse*> whs;
    int len = strlen(solution);

    for(int i=0; i < len; i++){
        if(solution[i] == 'F'){
            int x = (i%(_width*_precision))+_shiftx;
            int y = (i/_width*_precision)+_shifty;

            whs.append(new Warehouse(x, y, 0));
        }
    }

    int current_max_dist = Utils::get_max_dist(_cities, whs);
    if(current_max_dist < _min_solution){
        _solutions = whs;
        _min_solution = current_max_dist;
    }else{
        for(int i=0; i<whs.count(); i++){
            delete whs.at(i);
        }
    }
    emit progressUpdate(++_current_position);
}
