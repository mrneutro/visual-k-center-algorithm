#ifndef APPROXFACADE_H
#define APPROXFACADE_H
#include "ApproxResolver.h"
#include <QList>
#include "City.h"

#include <QObject>
#include <Warehouse.h>

class ApproxFacade : public QObject
{
    Q_OBJECT
public:
    explicit ApproxFacade(QObject *parent = nullptr);
    Q_INVOKABLE void init();
    Q_INVOKABLE void setCity(int x, int y);
    Q_INVOKABLE void setCenterCount(int k);
    Q_INVOKABLE void resolveImmediate();
    Q_INVOKABLE int getX(int item);
    Q_INVOKABLE int getY(int item);
    Q_INVOKABLE int getR(int item);
private:
    ApproxResolver *_resolver = nullptr;
    QList<City> _cities;
    int _center_count = 0;
    QList<Warehouse*> _solution;
signals:

public slots:
};

#endif // APPROXFACADE_H
