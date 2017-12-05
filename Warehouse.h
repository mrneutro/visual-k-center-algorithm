#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QObject>

class Warehouse : public QObject
{
    Q_OBJECT
public:
    explicit Warehouse(QObject *parent = nullptr);
    Warehouse(const Warehouse& wh);
    Warehouse(int x, int y, int radius);

    Q_INVOKABLE int x() const;

    Q_INVOKABLE int y() const;

    Q_INVOKABLE int radius() const;

private:
    int _x;
    int _y;
    int _radius;
signals:

public slots:
};

#endif // WAREHOUSE_H
