#ifndef DIRCHANGING_H
#define DIRCHANGING_H

#include "direction.h"

class DirChanging
{
public:
    DirChanging(int, int, Direction);
    int x,y;
    Direction dir;
};

#endif // DIRCHANGING_H
