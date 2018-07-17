#include "ResolverFacade.h"
#include <QDebug>
#include <QtConcurrent>
#include "resolver/BruteForceResolver.h"
#include "resolver/ApproxResolver.h"

ResolverFacade::ResolverFacade(QObject *parent) : QObject(parent)
{

}

void ResolverFacade::init()
{
    foreach(const Warehouse* wh, _solution){
        delete wh;
    }
    foreach(const City* c, _cities){
        delete c;
    }
    _cities.clear();
    _solution.clear();

}

void ResolverFacade::clear_solutions()
{
    foreach(const Warehouse* wh, _solution){
        delete wh;
    }
    _solution.clear();
}

void ResolverFacade::setCity(int x, int y)
{
    City* c = new City(x,y);
    //qDebug() << "New city is: " << x << " " << y;
    _cities.append(c);
}

void ResolverFacade::setCenterCount(int k)
{
    _center_count = k;
}

void ResolverFacade::resolveImmediate(QString algo)
{
    QtConcurrent::run([this, algo] {

        if(this->_resolver != nullptr)
            delete this->_resolver;
        _solution.clear();

        if(algo == "2Approx"){
            this->_resolver = new ApproxResolver(this->_cities, this->_center_count);
        }else{
            this->_resolver = new BruteForceResolver(this->_cities, this->_center_count);
            ((BruteForceResolver*)this->_resolver)->setPrecision(_precision);
        }
        connect(_resolver, SIGNAL(progressUpdate(int)), this, SIGNAL(progressUpdate(int)));
        connect(_resolver, SIGNAL(progressMaxVal(int)), this, SIGNAL(progressMaxVal(int)));
        connect(_resolver, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
        connect(_resolver, SIGNAL(drawLine(int,int,int,int)), this, SIGNAL(drawLine(int,int,int,int)));
        this->_solution = this->_resolver->resolve_immediatly();
        if(this->_solution.length() != 0){
            emit dataAvailable();
        }
        disconnect(_resolver, SIGNAL(progressUpdate(int)), this, SIGNAL(progressUpdate(int)));
        disconnect(_resolver, SIGNAL(progressMaxVal(int)), this, SIGNAL(progressMaxVal(int)));
        disconnect(_resolver, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
        disconnect(_resolver, SIGNAL(drawLine(x,y,toX,toY)), this, SIGNAL(drawLine(x,y,toX,toY)));

    });
}

int ResolverFacade::getX(int item)
{
    if(_solution.length() > item){
        return _solution.at(item)->x();
    }else{
        qWarning() << "OUT OF RANGE";
        return 0;
    }
}

int ResolverFacade::getY(int item)
{
    if(_solution.length() > item){
        return _solution.at(item)->y();
    }else{
        qWarning() << "OUT OF RANGE";
        return 0;
    }
}

int ResolverFacade::getR(int item)
{
    return _solution.at(item)->radius();
}

void ResolverFacade::setPrecision(QString precision)
{
    _precision = precision;
}

double ResolverFacade::last_execution_time()
{
    return this->_resolver->last_execution_time();
}

int ResolverFacade::solution_quality()
{
    return this->_resolver->solution_quality();
}

float ResolverFacade::getPrecitionDensity()
{
    return this->_resolver->precision_density();
}
