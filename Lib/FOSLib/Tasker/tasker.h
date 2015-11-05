#ifndef TASKER_H
#define TASKER_H

#include <stdint.h>

namespace FOS
{

typedef void (*TaskPointer)(void);
typedef uint32_t Frame;

class Task
{
    enum Status
    {
        StandBy,
        Running,
        Timeout,
        Pause,
    };

public:
    Task(TaskPointer pointer = 0, unsigned int Frames = 0, unsigned int FrequencyInHz = 0);
    void pause();
    void start();
    void setFunction(TaskPointer pinter);
protected:
    virtual void run();
private:
    Status status;
    Frame begin;
    Frame end;
    Frame max;
    unsigned int period;
};

class Tasker:public Task
{
public:
    void init();
    void poll();
    char* status();
protected:
    virtual void run();
private:
    const uint32_t taskMaxNumber = 10;
    Task* list[taskMaxNumber];
    uint32_t registedTasks;
};

}


#endif // TASKER_H
