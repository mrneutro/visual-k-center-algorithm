#include "BruteForceResolver.h"
#include <QDebug>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"

unsigned int count = 0;
clock_t start;

BruteForceResolver::BruteForceResolver(QList<City *> cities, int center_count)
{
    qDebug() << "Started ApproxResolver";

    _cities = cities;
    _center_count = center_count;
}

QList<Warehouse *> BruteForceResolver::resolve_immediatly()
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

    shiftx = xmin->x();
    shifty = ymin->y();

    width = xmax->x()-xmin->x()+1;
    height = ymax->y()-ymin->y()+1;

    qDebug() << "W:" << width << " H:" << height;
    unsigned long long max_count = Utils::choose(width*height, _center_count);

    qDebug() << max_count;
    possible_solutions = max_count; // \todo fare con questo qualcosa

    qDebug() << "Possible solutions" << possible_solutions;
    emit progressMaxVal(possible_solutions);

    char* map = (char*)malloc(width*height);
    if(map == NULL){
        qDebug() << "Alloc failed";
    }

    memset(map, 'E', width*height);
    memset(map, 'F', _center_count);
    map[width*height]=0x00;
    qDebug() << "Start calc";
    calc(map);

    return _solutions;
}

void BruteForceResolver::fill(int *rep_char,char *temp_buff) {
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

void BruteForceResolver::evaluate_solution(const char *solution)
{
    QList<Warehouse*> whs;
    int len = strlen(solution);
    //qDebug() << QString(solution);

    for(int i=0; i < len; i++){
        if(solution[i] == 'F'){
            int x = (i%width)+shiftx;
            int y = (i/width)+shifty;

            Warehouse *wh = new Warehouse(x, y, 0);
            whs.append(wh);
        }
    }

    int current_max_dist = Utils::get_max_dist(_cities, whs);
    if(current_max_dist < min_solution){
        _solutions = whs;
        min_solution = current_max_dist;
        qDebug() << "Current min solution";
        qDebug() << QString(solution);
    }else{
        for(int i=0; i<whs.count(); i++){
            delete whs.at(i);
        }
    }
    emit progressUpdate(++current_position);
}
