#ifndef CENTER_H
#define CENTER_H


class Center
{
public:
    Center(int x, int y);
    int y() const;

    int x() const;

private:
    int _x;
    int _y;
};

#endif // CENTER_H
