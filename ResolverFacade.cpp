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
    _cities.clear();
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
        this->_solution = this->_resolver->resolve_immediatly();
        emit dataAvailable();
        disconnect(_resolver, SIGNAL(progressUpdate(int)), this, SIGNAL(progressUpdate(int)));
        disconnect(_resolver, SIGNAL(progressMaxVal(int)), this, SIGNAL(progressMaxVal(int)));
    });
}

int ResolverFacade::getX(int item)
{
    return _solution.at(item)->x();
}

int ResolverFacade::getY(int item)
{
    return _solution.at(item)->y();
}

int ResolverFacade::getR(int item)
{
    return _solution.at(item)->radius();
}

void ResolverFacade::setPrecision(int precision)
{
    _precision = precision;
}
