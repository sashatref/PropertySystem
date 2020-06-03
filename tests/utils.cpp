#include "utils.h"



QString Text::getRandomString()
{
    return QUuid::createUuid().toString();
}

double Numerics::getRandomDouble(int max)
{
    return rand() % max + (double)(rand() % 100) / (double)100;
}
