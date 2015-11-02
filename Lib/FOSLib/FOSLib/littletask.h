#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef void (*TaskPointer)(void);
class LittleTask
{
public:
    LittleTask(TaskPointer tp = 0, unsigned int Ticks = 0, unsigned int FrequencyInHZ = 0, int Session = -1);

public:
    static void init();
    static void pollTasks(void);
    void pause() {access = false;}
    void start() {access = true;}
private:
    static const uint16_t taskMaxNumber = 10;
    static LittleTask* list[taskMaxNumber];
    static uint16_t registedTasks;
    TaskPointer run;
    bool access;
    static int tmpTime;
    unsigned int ticks;
    unsigned int period;
    unsigned int session;
};

#endif // TASK_H
