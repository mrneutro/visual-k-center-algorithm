#ifndef BRUTEFORCERESOLVER_H
#define BRUTEFORCERESOLVER_H
#include "CenterResolver.h"

class BruteForceResolver: public CenterResolver
{
public:
    BruteForceResolver(QList<City *> cities, int center_count);
    QList<Warehouse *> resolve_immediatly() override;

private:
    QList<City *> _cities;
    QList<Warehouse*> _solutions;
    int _center_count = 0;
    void fill(int *rep_char,char *temp_buff);
    void calc(const char *str);
    int shiftx=0;
    int shifty=0;
    int width = 0;
    int height = 0;
    void evaluate_solution(const char* solution);
    int min_solution = INT_MAX;
};

#endif // BRUTEFORCERESOLVER_H
