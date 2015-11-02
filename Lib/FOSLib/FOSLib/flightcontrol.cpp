#include "flightcontrol.h"

#if 0
extern uint32_t ms;
List FlightControl::head = 0;
List FlightControl::tail = 0;

FlightControl::FlightControl(Directive Data)
{
    data = Data;
    startTime = 0;
}

void FlightControl::start(bool isEmergency)
{
    if(isEmergency)
        //! @todo Actrualize
        ;
    else
    {
        List *add = new List();
        add->current = this;
        add->next = 0;
        if(head != 0)
        {
            tail->next = add;
            tail = add;
        }
        else
            head = add;
    }
}

bool FlightControl::isFinish()
{
    if(startTime == 0)
        return false;
    return ((ms - startTime) > data.timeout) ? true : false;
}

void FlightControl::CCCrefresh()
{
    if(data.test == 0)
        return;

}

void FlightControl::run()
{
    Control command = data.command;
    printf("!");
    //App_Send_Data(0, 0, MY_CTRL_CMD_SET, API_CTRL_REQUEST, (unsigned char*)&command, sizeof(command), NULL, 0, 0);
}

void FlightControl::init()
{

}

void FlightControl::freePoll()
{
    if(isFree())
        return;
    if(head->current->isFinish())
    {
        List *tmp = head;
        head = tmp->next;
        tmp->next = 0;
        delete tmp;
        return;
    }
    head->current->CCCrefresh();
}

void FlightControl::taskPoll()
{
    if(isFree())
    {
        //App_Send_Data(0, 0, MY_CTRL_CMD_SET, API_CTRL_REQUEST, (unsigned char*)&hover, sizeof(hover), NULL, 0, 0);
    }
    else
    {
        head->current->run();
    }
}
#endif


Control command;
Control target;
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "DJI_Pro_Test.h"
#include "cv.h"

static float maxSpeed;
static float minSpeed;
static float minPalstance;
void FlightControl::init()
{
    maxSpeed = 0.5;
    minSpeed = 0.1;
    minPalstance = 2;
}

void FlightControl::set(int dx, int dy, int dh, int dyaw)
{
    if((abs(dx) > criterion)||(abs(dy) > criterion))
    {
        command.ctrl_flag = 0x4B;
        if(abs(dx) > criterion)
            command.roll_or_x = maxSpeed*sgn(dx);
        else
        {
            command.roll_or_x = minSpeed*sgn(dx);
            command.yaw = sgn(dx*dy)*minPalstance*-1;
        }
        if(abs(dy) > criterion)
            command.pitch_or_y = maxSpeed*sgn(dy);
        else
        {
            command.pitch_or_y = minSpeed*sgn(dy);
            command.yaw = sgn(dx*dy)*minPalstance;
        }
    }
    else
    {
        command.ctrl_flag = 0x0B;
        command.roll_or_x = dx/100.0;
        command.pitch_or_y = dy/100.0;
    }
    if(abs(dyaw) > angleCriterion)
    {
        command.ctrl_flag &= 0xF7;
        command.yaw = dyaw;
    }
    else
    {
        command.ctrl_flag |= 0x08;
        command.yaw = dyaw;
    }
    if(dh != 0)
        command.thr_z = sgn(dh)*0.1;
    else
        command.thr_z = 0;
}

void FlightControl::smooth()
{
    target = command;
}

bool FlightControl::takeoff()
{
    DJI_Onboard_API_Takeoff();
    return false;
}


uint8_t dataBuf[200];
size_t datapos = 0;


extern volatile bool needLine;
extern uint32_t debugms;
extern uint32_t ms;
extern volatile bool lineRefresh;
Line tmpLine;
extern volatile bool basketRefresh;
Basket tmpBasket;
extern volatile bool blueRefresh;
sBlue tmpBlue;
bool FlightControl::decode(uint8_t data)
{
    bool quit = false;

    dataBuf[datapos] = data;
    datapos++;
    //printf("0x%x ",data);
    switch(dataBuf[0])
    {
    case 0x99:
        if(datapos == sizeof(float)+1)
        {
            float tmp;
            memcpy(&tmp,dataBuf+1,sizeof(float));
            //printf("time used: %d\r\n",ms - debugms);
            debugms = ms;
            //printf("height: %f \r\n",tmp);
            datapos = 0;
        }
        break;
    case 0xAA:
        if(datapos == sizeof(Line)+1)
        {
            memcpy(&tmpLine,dataBuf+1,sizeof(Line));
            //printf("time used: %d\r\n",ms - debugms);
            //printf("Line:\r\n%d\r\n%d\r\n%d\r\n%d\r\n",tmpLine.exist,tmpLine.angle,tmpLine.distance,tmpLine.horizontal);
            if(needLine)
                printf("Line: %d",tmpLine.distance);
            debugms = ms;
            datapos = 0;
            lineRefresh = true;

        }
        break;
    case 0xBB:
        if(datapos == sizeof(Circle)+1)
        {
            Circle tmp;
            memcpy(&tmp,dataBuf+1,sizeof(Circle));
            //printf("time used: %d\r\n",ms - debugms);
            //printf("Circ: %d %d \r\n",tmp.x,tmp.y);
            debugms = ms;
            datapos = 0;
        }
        break;
    case 0xCC:
        if(datapos == sizeof(sGrid)+1)
        {
            sGrid tmp;
            memcpy(&tmp,dataBuf+1,sizeof(sGrid));
            //printf("time used: %d\r\n",ms - debugms);
            //printf("Grid: %d %d %d %d %d \r\n",tmp.color,tmp.exist,tmp.number,tmp.x,tmp.y);
            debugms = ms;
            datapos = 0;
        }
        break;
    case 0xDD:
        if(datapos == sizeof(Basket)+1)
        {
            memcpy(&tmpBasket,dataBuf+1,sizeof(Basket));
            //printf("time used: %d\r\n",ms - debugms);
            //printf("x: %f\r\ny: %f\r\n",tmpBasket.x,tmpBasket.y);
            debugms = ms;
            datapos = 0;
            basketRefresh = true;
        }
        break;
    case 0xEE:
        if(datapos == sizeof(sBlue)+1)
        {
            memcpy(&tmpBlue,dataBuf+1,sizeof(sBlue));
            //printf("time used: %d\r\n",ms - debugms);
            printf("\r\nBlue!!!!!!!!%d %d \r\n",tmpBlue.x,tmpBlue.y);
            debugms = ms;
            datapos = 0;
            blueRefresh = true;
        }
        break;

    case 0x55:
        if(datapos == 2)
            if(dataBuf[1] == 0x01)
            {
                quit = true;
                datapos = 0;
            }
        break;
    default:
        printf("0x%x ",data);
        datapos = 0;
        break;
    }

    return quit;
}
