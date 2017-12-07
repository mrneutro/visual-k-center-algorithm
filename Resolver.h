#ifndef RESOLVER_H
#define RESOLVER_H

#include <QObject>

class Resolver : public QObject
{
    Q_OBJECT
public:
    explicit Resolver(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RESOLVER_H
