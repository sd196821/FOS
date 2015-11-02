#include "littletask.h"
#include "stm32f4xx.h"
#include <stdio.h>
volatile uint32_t ms = 0;
volatile uint32_t pms = 0;
uint16_t LittleTask::registedTasks = 0;
LittleTask* LittleTask::list[LittleTask::taskMaxNumber];
volatile bool tickFlag;
int LittleTask::tmpTime = 0;
LittleTask::LittleTask(TaskPointer tp, unsigned int Ticks, unsigned int FrequencyInHZ,int Session)
{
    run = tp;
    ticks = Ticks;
    period = 1000/FrequencyInHZ;
    access = false;
    if(Session == -1)
    {
        //! @note need an algorithm to devide time to all task;
        session = 0;
    }
    else
        session = Session;

    if(registedTasks < taskMaxNumber)
    {
        list[registedTasks] = this;
        registedTasks++;
    }
}

void LittleTask::init()
{
    if(SysTick_Config(168000))
        while(1);//error, but it is not necessary to do any thing.
    for(int i = 0; i < taskMaxNumber; ++i)
        list[i] = 0;
}

void LittleTask::pollTasks()
{
    if(tickFlag)
    {
        tickFlag = false;
        tmpTime = ms;
        for(int i = 0; i < registedTasks; ++i)
        {
            if( (list[i] != 0) && ((tmpTime%(list[i]->period)) == list[i]->session) && list[i]->access )
            {
                (*(list[i]->run))();
                //#define TEST
#ifdef TEST
                printf("Poll Task use Time: %lf \r\nAt %lf \r\n",(ms - tmpTime)/1000.0,ms/1000.0);
#endif
                if((ms - tmpTime) > list[i]->ticks)
                {
                    list[i]->access = false;
#ifdef TEST
                    printf("run out of time\r\n");
#endif
                }
            }
        }
    }
}
#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

void SysTick_Handler(void)
{
    ms++;
    pms++;
    tickFlag = true;
}

#ifdef __cplusplus
}
#endif //__cplusplus
