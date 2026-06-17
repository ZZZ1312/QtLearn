#include "counter.h"

Counter::Counter() {}

int Counter::getNextNumber()
{
    if (number > 1000)
        number = 0;
    return ++number;
}
