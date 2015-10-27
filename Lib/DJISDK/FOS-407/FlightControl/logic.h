#ifndef LOGIC_H
#define LOGIC_H

#include <stdint.h>

namespace Logic
{
bool offSet();
bool takeOff(int command);
bool toHeight(int command);
bool landIn(int command);
bool delay(int command);
bool angle(int command);
bool moveX(int command);
bool moveY(int command);
bool trackBasket(int command);
bool stop(int command);

bool takeBall(int command);
bool dropBall(int command);
bool moveToCentre(int command);
bool stopMove(int command);
}
namespace Test
{
bool isLowBettery();
bool moveX();
bool moveY();
bool trackBasket();
bool trackLine();
}
namespace offset
{
extern float height;
extern float altitude;
extern float yaw;
extern uint32_t times;
}

namespace TaskList
{
typedef bool (*Task)(int command);
typedef uint32_t TimeOut;
typedef struct
{
    Task task;
    TimeOut timeOut;
    int command;
    int32_t needPoll;
}Play;
typedef struct
{
    Play* List;
    uint32_t len;
}ListSet;

extern uint32_t n;
void init();
bool pollTask();

extern int useless;
extern ListSet* current;
extern ListSet SetTest;
extern ListSet SetMini;
extern ListSet SetLine;
extern ListSet Little1;
extern ListSet Little2;
extern ListSet Little3;
extern ListSet Little4;
extern ListSet SetBack;
extern ListSet SetTake;
extern ListSet SetDrop;
extern ListSet SetTakeOff;
extern ListSet SetLandIn;
extern ListSet SetBasket;
}

#endif // LOGIC_H
