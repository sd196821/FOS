/*! @brief *********************************
 *  @file    flightcontrol.h
 *  @version 0.1
 *  @corelib FOSLib
 *           STM32F4xxLib
 *  System environment:
 *           STM32F407ZET6 with W25Q32 SPI flash.
 * features:
 * This is a DJI M100 flightcontrol system, based on DJI onboard SDK.
 * Running in a STM32F407 SCM controller,
 * It used the FOSLib-preopensource demo, written by William Wu in 2014,
 * for the USART driver and a simple multitask operating system.
 *
 * @abstract System model
 * Consider a DJI-M100 quadrotor the BLDC's bandwidth is 50Hz, Communication delay is 500us at least.
 * So a typical upper-machine controller's bandwidth must not greater than 50Hz, or the control system is diverging.
 * As a concluson we design a 25Hz control system, but resolving control forces depends on communication rate(100 Hz typical).
 *
 * @chapter Command model
 * A command has open loop control(OLC) and close-cycle control(CCC) two type.
 * In OLC, we send a directive and wait until time out.
 * In CCC, we recalculate its time and add artifical excitaion to correct for it.
 * To adjust a close-cycle contol, we give a residual for it to evaluate.
 *
 * @chapter Stability
 * In order to ensure the stability, we restrict the control value and its derivative.
 *
 * @version features:
 * V0.1
 * ****************************************** Copyright (c) ******************************************
 * @author: William Wu
 * @e-mail: DJI@justwillim.com
 * @date  : 2015-08-16
 * ****************************************** Copyright (c) ******************************************/
#ifndef FLIGHTCONTROL_H
#define FLIGHTCONTROL_H

#include "cppforstm32.h"
#include "usart.h"
#include "littletask.h"
#include "spi_flash.h"
#include "DJI_Pro_App.h"

using namespace USART;

typedef struct
{
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t yaw;
}Transform;

typedef api_ctrl_without_sensor_data_t Control;
class FlightControl
{
public:
    static void init();
    static void set(int dx, int dy, int dh, int dyaw);
    static void smooth();
    static bool takeoff();
    static bool Landin();
    static bool decode(uint8_t data);
    static const int criterion = 500;
    static const int angleCriterion = 15;

    static int sgn(int data){return data>0 ? 1 : -1;}
};
extern Control command;


//! @version abrot, lack of time
#if 0
typedef struct
{
    float x;
    float y;
    float z;
}Coordinate;
typedef uint32_t Time;
typedef api_ctrl_without_sensor_data_t Control;
typedef Time (*TimeRemain)(void);
typedef Coordinate (*Residual)(Coordinate);

typedef struct
{
    Control command;
    Time timeout;
    TimeRemain remain;
    Residual test;
    Coordinate target;
}Directive;


class FlightControl;
typedef struct ListStruct
{
    FlightControl *current;
    struct ListStruct *next;
}List;

class FlightControl
{
public:
    FlightControl(Directive Data);
    void start(bool isEmergency = false);
    bool isFinish();
    Control command(){return data.command;}
    void CCCrefresh();
private:
    void run();

public:
    static void init();
    static void freePoll();
    static void taskPoll();
    static bool isFree(){return head == 0 ?true:false;}
private:
    static const Control hover = {0x4B,0,0,0,0};
    static const Time hoverTimeOut = 10000;//10s
private:
    static List *head;
    static List *tail;
private:
    Directive data;
    Time startTime;
};
#endif




#endif // FLIGHTCONTROL_H
