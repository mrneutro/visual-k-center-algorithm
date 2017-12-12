#include "BruteForceResolver.h"
#include <QDebug>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

    int width = xmax->x()-xmin->x();
    int height = ymax->y()-ymin->y();

    qDebug() << "W:" << width << " H:" << height;

    char* map = (char*)malloc(width*height+1);
    if(map == NULL){
        qDebug() << "Alloc failed";
    }
    qDebug() << "Size of char is " << sizeof(char);

    memset(map, 'E', width*height);
    memset(map, 'F', _center_count);
    map[width*height-1]=0x00;
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

        printf("%s\n", temp_buff);
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

    qDebug() << "Repetitions counted";

    fill(repetion_of_char,temp_buff);
}
