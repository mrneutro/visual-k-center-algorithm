#include "Center.h"

Center::Center(int x, int y)
{
    _x = x;
    _y = y;
}

int Center::y() const
{
    return _y;
}

int Center::x() const
{
    return _x;
}
