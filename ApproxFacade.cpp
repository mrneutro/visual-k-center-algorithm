#include "ApproxFacade.h"
#include <QDebug>
#include <QtConcurrent>

ApproxFacade::ApproxFacade(QObject *parent) : QObject(parent)
{

}

void ApproxFacade::init()
{
    _cities.clear();
}

void ApproxFacade::setCity(int x, int y)
{
    City* c = new City(x,y);
    //qDebug() << "New city is: " << x << " " << y;
    _cities.append(c);
}

void ApproxFacade::setCenterCount(int k)
{
    _center_count = k;
}

void ApproxFacade::resolveImmediate()
{
    QtConcurrent::run([this] {
        if(this->_resolver != nullptr)
            delete this->_resolver;
        _solution.clear();

        this->_resolver = new ApproxResolver(this->_cities, this->_center_count);
        connect(_resolver, SIGNAL(progressUpdate(int)), this, SIGNAL(progressUpdate(int)));
        this->_solution = this->_resolver->resolve_immediatly();
        emit dataAvailable();
        disconnect(_resolver, SIGNAL(progressUpdate(int)), this, SIGNAL(progressUpdate(int)));
    });
}

int ApproxFacade::getX(int item)
{
    return _solution.at(item)->x();
}

int ApproxFacade::getY(int item)
{
    return _solution.at(item)->y();
}

int ApproxFacade::getR(int item)
{
    return _solution.at(item)->radius();
}
