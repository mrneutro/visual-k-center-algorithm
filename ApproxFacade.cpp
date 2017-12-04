#include "ApproxFacade.h"
#include <QDebug>
ApproxFacade::ApproxFacade(QObject *parent) : QObject(parent)
{

}

void ApproxFacade::init()
{
    _cities.clear();
}

void ApproxFacade::setCity(int x, int y)
{
    City c(x,y);
    qDebug() << "New city is: " << x << " " << y;
    _cities.append(c);
}

void ApproxFacade::setCenterCount(int k)
{
    _center_count = k;
}

void ApproxFacade::resolveImmediate()
{
    if(_resolver != nullptr)
        delete _resolver;

    _solution.clear();

    _resolver = new ApproxResolver(_cities, _center_count);
    _solution = _resolver->resolve_immediatly();
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
