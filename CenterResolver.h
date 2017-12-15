#ifndef CENTERRESOLVER_H
#define CENTERRESOLVER_H
#include <QObject>
#include <QList>
#include "Warehouse.h"
#include "NearestCenter.h"

class CenterResolver : public QObject {
    Q_OBJECT

public:
    virtual QList<Warehouse *> resolve_immediatly() = 0;
signals:
    void progressUpdate(int val);
    void progressMaxVal(int val);
};

#endif // CENTERRESOLVER_H
