#include "NearestCenter.h"

NearestCenter::NearestCenter(const City *_c, const Warehouse *_w, int d)
{
    city = (City*)_c;
    warehouse = (Warehouse*)_w;
    distance = d;
}
