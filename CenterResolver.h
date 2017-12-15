#ifndef CENTERRESOLVER_H
#define CENTERRESOLVER_H
#include <QObject>
#include <QList>
#include "model/Warehouse.h"
#include "model/NearestCenter.h"

class CenterResolver : public QObject {
    Q_OBJECT

public:
    virtual QList<Warehouse *> resolve_immediatly() = 0;
    volatile bool stop = false;

private:
signals:
    void progressUpdate(int val);
    void progressMaxVal(int val);
};

#endif // CENTERRESOLVER_H

