#ifndef CENTERRESOLVER_H
#define CENTERRESOLVER_H
#include <QObject>
#include <QList>
#include <ctime>

#include "model/Warehouse.h"
#include "model/NearestCenter.h"

class CenterResolver : public QObject {
    Q_OBJECT



public:
    virtual QList<Warehouse *> resolve_immediatly() = 0;
    bool stop = false;
    void start_timer(){
        timer_begin = clock();
    }

    void stop_timer(){
        timer_end = clock();
    }

    double last_execution_time(){
        return double(timer_end - timer_begin) / (CLOCKS_PER_SEC);
    }

    int _min_solution = INT_MAX;
    int solution_quality(){
        return _min_solution;
    }


    float _precision_density = 0;
    float precision_density() {
        return _precision_density;
    }

private:
    clock_t timer_begin = clock();
    clock_t timer_end = clock();
signals:
    void progressUpdate(int val);
    void progressMaxVal(int val);
    void error(QString val);
    void drawLine(int x, int y,int toX, int toY);
};


#endif // CENTERRESOLVER_H
