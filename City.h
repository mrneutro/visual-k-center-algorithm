#ifndef CITY_H
#define CITY_H


class City
{
public:
    City(int x, int y);

    int x() const;

    int y() const;

private:
    int _x;
    int _y;
};

#endif // CITY_H
