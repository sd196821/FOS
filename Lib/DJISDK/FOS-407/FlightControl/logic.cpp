#include "logic.h"

#include <stdio.h>
#include "DJI_Pro_Test.h"
#include "flightcontrol.h"
#include "cv.h"
#include "math.h"
#include "mechanical.h"

extern usart upper2;
extern mechanical machine;
namespace offset
{
float height;
float altitude;
float yaw;
uint32_t times;
}

bool Logic::takeOff(int command)
{
    printf("takeoff\r\n");
    DJI_Onboard_API_Takeoff();
    return true;
}
bool Logic::toHeight(int command)
{
    float error = - recv_sdk_std_msgs.pos.height + command/100;
    if(abs(error) > 0.05)
    {
        FlightControl::set(0,0,FlightControl::sgn(error),0);
        printf("Height error %f",error);
        return false;
    }
    else
    {
        FlightControl::set(0,0,0,0);
        printf("On Height %d\r\n",command);
        return true;
    }
    return false;
}

bool Logic::offSet()
{
    static const uint8_t max = 100;
    offset::height += recv_sdk_std_msgs.pos.height/max;
    offset::altitude += recv_sdk_std_msgs.pos.alti/max;
    offset::yaw += Agl.z/max;
    return offset::times++>(max-2)?true:false;
}


namespace TaskList
{
uint32_t n;
ListSet* current;
int useless = 0;


uint32_t startTime;
int32_t remain;


Play TakeOff[] = {
    {Logic::takeOff,    10000,  0,1},
    {Logic::delay,      5000,   0,1},
    {Logic::delay,      5000,   0,1}
};

Play Land[] = {
    {Logic::toHeight,   30000,  80,-511},
    {Logic::delay,      5000,   0,1},
    {Logic::landIn,     10000,  0,1},
    {Logic::delay,      5000,   0,1}
};



Play MiniTest[] = {
    {Logic::dropBall,       1000,   1,1},
    {Logic::delay,          2000,   0,1},
    {Logic::takeBall,       13000,  0,-511},
    {Logic::delay,          2000,   0,1},
    {Logic::moveToCentre,   13500,  0,-511},
    {Logic::takeBall,       500,  0,-511},
    {Logic::stopMove,       500,  0,1},
    {Logic::takeOff,    8000,  0,1},
    {Logic::delay,      7000,   0,1},
    {Logic::moveX,      7000,  1,-511},
    {Logic::stop,       100,    0,1},
    {Logic::dropBall,       1000,   1,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   2,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   3,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   4,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   5,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   0,1},
    {Logic::moveX,      10000,  -1,-511},
    {Logic::landIn,     10000,  0,1},
};

ListSet SetMini = {MiniTest,24};


Play SelfTest[] = {
    {Logic::angle,      30000,  0,-511},
    {Logic::stop,       100,    0,1},
    {Logic::delay,      5000,   0,1},
    {Logic::angle,      30000,  90,-511},
    {Logic::stop,       100,    0,1},
    {Logic::delay,      5000,   0,1},
    {Logic::angle,      30000,  -90,-511},
    {Logic::stop,       100,    0,1},
    {Logic::delay,      5000,   0,1},
    {Logic::angle,      30000,  180,-511},
    {Logic::stop,       100,    0,1},
};

Play LineTest[] = {
    {Logic::takeOff,    10000,  0,1},
    {Logic::moveX,      3000,   1,-511},
    {Logic::moveX,      3000,   -1,-511},
    {Logic::stop,       1000,   0,1},
    {Logic::delay,      2000,   0,1},
    {Logic::toHeight,   30000,  80,-511},
    {Logic::delay,      5000,   0,1},
    {Logic::landIn,     10000,  0,1}
};

Play MoveLittle[] = {
    {Logic::moveX,      1000,   1,-511},
    {Logic::stop,       100,    0,1}
};

Play MoveLittle2[] = {
    {Logic::moveX,      1000,   -1,-511},
    {Logic::stop,       100,    0,1}
};

Play MoveLittle3[] = {
    {Logic::moveY,      1000,   1,-511},
    {Logic::stop,       100,    0,1}
};

Play MoveLittle4[] = {
    {Logic::moveY,      1000,   -1,-511},
    {Logic::stop,       100,    0,1}
};

Play MoveBack[] = {
    {Logic::moveX,      2000,   -1,-511},
    {Logic::stop,       100,    0,1},
    {Logic::angle,      30000,  180,-511},
    {Logic::stop,       100,    0,1},
    {Logic::delay,      5000,   0,1},
    {Logic::dropBall,   3000,   0,1},
};

Play Take[] = {
    {Logic::dropBall,       1000,   1,1},
    {Logic::delay,          2000,   0,1},
    {Logic::takeBall,       13000,  0,-511},
    {Logic::delay,          2000,   0,1},
    {Logic::moveToCentre,   13500,  0,-511},
    {Logic::takeBall,       500,  0,-511},
    {Logic::stopMove,       500,  0,1},
};
Play Drop[] = {
    {Logic::dropBall,       1000,   1,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   2,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   3,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   4,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   5,1},
    {Logic::delay,          2000,   0,1},
    {Logic::dropBall,       1000,   0,1},
};
Play Basket[] = {
    {Logic::stop,           100,    0,1},
    {Logic::toHeight,       20000,  180,-511},
    {Logic::trackBasket,    3000,   0,-511},
};


ListSet SetTest = {SelfTest,11};
ListSet SetLine = {LineTest,7};
ListSet Little1  = {MoveLittle,2};
ListSet Little2  = {MoveLittle2,2};
ListSet Little3  = {MoveLittle3,2};
ListSet Little4  = {MoveLittle4,2};
ListSet SetBack  = {MoveBack,3};
ListSet SetTake = {Take,7};
ListSet SetDrop = {Drop,11};
ListSet SetTakeOff = {TakeOff,3};
ListSet SetLandIn = {Land,3};
ListSet SetBasket = {Basket,3};
}

extern uint32_t ms;

bool TaskList::pollTask()
{
    if(current != 0)
    {
        Play *list = current->List;
        bool isFinish = false;
        bool isTimeOut = false;
        if(ms - startTime > list[n].timeOut)
            isTimeOut = true;
        if((remain > 0)||(remain == -511))
        {
            //printf("%d\r\n",remain);
            isFinish = list[n].task(list[n].command);
            if(remain > 0)
                remain --;
        }
        if(isFinish||isTimeOut)
        {
            n++;
            startTime = ms;
            TaskList::remain = list[n].needPoll;
            printf("Next Step!%d\r\n",list[n].command);
        }
        if(n == current->len)
        {
            current = 0;
            printf("Finish!!!\r\n");
            return true;
        }
    }
    return false;
}


void TaskList::init()
{
    TaskList::n = 0;
    TaskList::startTime = ms;
    if(TaskList::current != 0)
        TaskList::remain = current->List[0].needPoll;
}





bool Logic::angle(int command)
{
    float error =  command - Agl.z + offset::yaw;
    //printf("%f @ %f\r\n",Agl.z - offset::yaw,error);
    if(abs(error) > 2)
    {
        if(abs(error) > 15)
            FlightControl::set(0,0,0,FlightControl::sgn(error)*15);
        else
            FlightControl::set(0,0,0,FlightControl::sgn(error)*3);
        return false;
    }
    else
        return true;
}


bool Logic::delay(int command)
{
    return false;
}

extern volatile bool lineRefresh;

extern volatile bool needLine;


extern Line tmpLine;
bool Logic::moveX(int command)
{
    needLine = true;
    int correct = 0;
    if(lineRefresh)
    {
        lineRefresh = false;
        if(tmpLine.exist > 1)
            correct = -tmpLine.distance/3;
        if(abs(correct) > 40)
            correct = FlightControl::sgn(correct)*FlightControl::sgn(command)*40;
        printf("\r\ncorrect: %d\r\n",correct);
    }
    FlightControl::set(correct,FlightControl::sgn(command)*199,0,0);
    return false;
}


bool Logic::stop(int command)
{
    FlightControl::set(0,0,0,0);
    return true;
}


bool Logic::landIn(int command)
{
    DJI_Onboard_API_Landing();
    return false;
}


bool Logic::moveY(int command)
{
    FlightControl::set(FlightControl::sgn(command)*199,0,0,0);
    return false;
}


bool Logic::takeBall(int command)
{
    return machine.out();
}


bool Logic::dropBall(int command)
{
    machine.drop(command);
    return true;
}


bool Logic::moveToCentre(int command)
{
    return machine.back();
}

extern volatile bool needBasket;
extern volatile bool basketRefresh;
extern Line tmpLine;
extern Basket tmpBasket;

bool Logic::trackBasket(int command)
{
    needBasket = true;
    float y = tmpBasket.y/3;
    float x = tmpBasket.x/4;
    if(abs(tmpBasket.x/3) > 40)
        x = FlightControl::sgn(tmpBasket.x)*40;
    if(abs(tmpBasket.y/4) > 40)
        y = FlightControl::sgn(tmpBasket.y)*40;
    FlightControl::set(x,y,0,0);
    if((abs(x) < 40)&&(abs(y) < 40))
        return true;
    else
        printf("BASKET!!!!!!!! \r\n\r\n%f %f\r\n\r\n",x,y);
    return false;
}


bool Logic::stopMove(int command)
{
    return machine.stop();
}
