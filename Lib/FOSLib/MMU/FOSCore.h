#ifndef FOSCORE_H
#define FOSCORE_H

#include "FOSType.h"
namespace FOS
{
    void setRandSeed(uint32_t seed);
    uint32_t rand();
    time_t getTime();

}
#endif // FOSCORE_H
