#ifndef FOSERVO_H
#define FOSERVO_H
#ifdef USE_QT
#include "FOSLib/gpio.h"
#endif
#include "gpio.h"
using namespace GPIN;
class Servo
{
public:
    Servo(TIM_TypeDef *TIMx = TIM4,unsigned char Channel = 0, unsigned int Infimum_us = 500,unsigned int Supremum_us = 2500, unsigned char SkipDistance_us = 2);

    void setpos(unsigned int Pos);
private:
    static const int FeqInHz = 50;

    TIM_TypeDef *TIM;

    unsigned char channel;
    unsigned int inf;
    unsigned int sup;
    unsigned char skip;

private:
    unsigned int convert(unsigned int pos);
};

#endif // FOSERVO_H
