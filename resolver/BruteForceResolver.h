#ifndef BRUTEFORCERESOLVER_H
#define BRUTEFORCERESOLVER_H
#include "CenterResolver.h"

class BruteForceResolver: public CenterResolver
{
public:
    BruteForceResolver(QList<City *> cities, int center_count);
    ~BruteForceResolver();
    QList<Warehouse *> resolve_immediatly() override;

private:
    void fill(int *rep_char,char *temp_buff);
    void evaluate_solution(const char* solution);
    void calc(const char *str);
    void optimize_input();

    QList<City*> _cities;
    QList<Warehouse*> _solutions;
    int _center_count = 0;
    int _shiftx=0;
    int _shifty=0;
    int _width = 0;
    int _height = 0;
    int _min_solution = INT_MAX;
    quint64 _possible_solutions = 0;
    int _current_position = 0;
    char *_map = nullptr;
};

#endif // BRUTEFORCERESOLVER_H
