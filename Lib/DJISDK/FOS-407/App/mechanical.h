#ifndef MECHANICAL_H
#define MECHANICAL_H

#include "servo.h"
#ifdef USE_QT
#include "FOSLib/gpio.h"
#endif
#include "gpio.h"

class mechanical
{
public:
    mechanical();
    void init();
    bool back();
    bool out();
    bool stop();
    bool test(uint16_t port);
    bool atEnd();
    void drop(int number);
    bool hasball();
private:
    Servo take;
    Servo move;
};

#endif // MECHANICAL_H
