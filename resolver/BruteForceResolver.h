#ifndef BRUTEFORCERESOLVER_H
#define BRUTEFORCERESOLVER_H
#include "CenterResolver.h"

class BruteForceResolver: public CenterResolver
{
public:
    BruteForceResolver(QList<City *> cities, int center_count);
    ~BruteForceResolver();
    QList<Warehouse *> resolve_immediatly() override;

    void setPrecision(QString precision);

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

    quint64 _possible_solutions = 0;
    int _current_position = 0;
    char *_map = nullptr;
    float _precision = 1;
    int _precision_density = 0;
};

#endif // BRUTEFORCERESOLVER_H
