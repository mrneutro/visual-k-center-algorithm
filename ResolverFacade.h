#ifndef APPROXFACADE_H
#define APPROXFACADE_H
#include <QObject>
#include <QList>

#include "model/City.h"
#include "model/Warehouse.h"
#include "CenterResolver.h"

class ResolverFacade : public QObject
{
    Q_OBJECT
public:
    explicit ResolverFacade(QObject *parent = nullptr);
    Q_INVOKABLE void init();
    Q_INVOKABLE void setCity(int x, int y);
    Q_INVOKABLE void setCenterCount(int k);
    Q_INVOKABLE void resolveImmediate(QString algo);
    Q_INVOKABLE int getX(int item);
    Q_INVOKABLE int getY(int item);
    Q_INVOKABLE int getR(int item);
    Q_INVOKABLE void stop(){
        _resolver->stop = true;
    }
private:
    CenterResolver *_resolver = nullptr;
    QList<City*> _cities;
    int _center_count = 0;
    QList<Warehouse*> _solution;
signals:
    void dataAvailable();
    void progressUpdate(int val);
    void progressMaxVal(int val);
public slots:
};

#endif // APPROXFACADE_H
