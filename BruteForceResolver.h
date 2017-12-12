#ifndef BRUTEFORCERESOLVER_H
#define BRUTEFORCERESOLVER_H
#include "CenterResolver.h"

class BruteForceResolver: public CenterResolver
{
public:
    BruteForceResolver(QList<City *> cities, int center_count);
    QList<Warehouse *> resolve_immediatly() override;

private:


};

#endif // BRUTEFORCERESOLVER_H
