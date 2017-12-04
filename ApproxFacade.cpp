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

QList<int> ApproxFacade::resolveImmediate()
{
    if(_resolver != nullptr)
        delete _resolver;

    _solution.clear();

    _resolver = new ApproxResolver(_cities, _center_count);
    return _solution = _resolver->resolve_immediatly();
}
