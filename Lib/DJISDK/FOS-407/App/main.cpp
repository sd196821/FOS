/*! @brief *********************************
 *  @file    main.cpp
 *  @version 0.6
 *  @corelib FOSLib
 *           STM32F4xxLib
 * System environment:
 *           STM32F407ZET6 with W25Q32 SPI flash.
 * features:
 * This is a DJI M100 onboard sdk test program.
 * Running in a STM32F407 SCM controller,
 * It used the FOSLib-preopensource demo, written by William Wu in 2014,
 * for the USART driver and a simple multitask operating system.
 *
 * @attention:
 * Project configuration:
 * Addintional defines:
 * STM32
 * STM32F40x
 * USE_STDPERIPH_DRIVER
 * STM32F40_41xxx
 * USE_STM324xG_EVAL
 * __FPU_USED = 1
 * DYNAMIC_MEMORY
 *
 * Operational configuration:
 * Operational defines:
 * -* DEBUG
 *  * inof: more debug data output through USART port debug.
 * @version features:
 * -V0.6
 * -* Modify FOSLib-USART static memory bugs on dynamic memory mod;
 * -* Supply dynamic memory for STM32.
 * -* Add PWM control for RPLIDAR.
 * -* Add fulsh function for FOSLib-USART
 * -* Reconstruct memory distribution for whole system.
 *  * Remove some static memory variables
 *  * Redefine some global variables as a pointer.
 * -V0.5
 * -* Finish RPLIDAR's stability test;
 * -* Add recall function in class Buffer.
 * -* Add tele-control by wireless serial port.
 * -* Add echo for RPLIDAR, so that we can test the SLAM algorithm in upper machine.
 *  * Echo mode for RPLIDAR only can be used to wired serial port,
 *  * because of the offical sdk tool on upper machine is lack of data check.
 * -* Add control task.
 * -* Add open loop control for SDK control.
 * -* Add close loop control for SDK control.
 * -V0.4
 * -* Add UART4 to FOSLib.
 * -* Made a distinction between usart and uart.
 *  * prepare to distinguish these two different device.
 *  * But it failed, because definitions in an enum do not allow to have equal value.
 *  * It should be actulized in an other way.
 * -* Add class RPLIDAR.
 *  * From RPLIDAR, we can get pre-SLAM data.
 * -V0.3
 * -* reconstruct the DJI sdk to a C++ like class,
 *  * so that it can be used as a multi-device controller.
 * -* unified ProHeader and SDKHeader.
 * -* unified Get_Time and Get_Timestamp.
 * -* define send, get, preconvert and getTimestamp as a virtual function.
 * -* Lack of time reconstruct abort, it will rebegin after version 1.0
 * -V0.2
 * -* Stability test;
 * -* Wareless serial port test;
 * -* prereconstruct prepare;
 * -* correct a data size bug in DJI_Pro_App.h line 123.
 * -V0.1
 * -* Test the multitask operating system;
 * -* Transplant the FOSLib from Stm32F1xx to Stm32F4xx.
 * ****************************************** Copyright (c) ******************************************
 * @author: William Wu
 * @e-mail: DJI@justwillim.com
 * @date  : 2015-08-09
 * ****************************************** Copyright (c) ******************************************/
#include "stm32f4xx.h"
#include "n1sdk.h"
#include "usart.h"
#include "rtc.h"
#include "cppforstm32.h"
#include <stdio.h>
#include <string.h>
#include "DJI_Pro_App.h"
#include "DJI_Pro_Codec.h"
#include "DJI_Pro_Test.h"
#include "DJI_Pro_Link.h"
#include "DJI_Pro_Hw.h"
#include "littletask.h"
#include "gpio.h"
#include "spi_flash.h"
#include "flightcontrol.h"
#include "cv.h"
#include "logic.h"
#include "mechanical.h"
#ifdef USE_QT
#include "FOSLib/gpio.h"
#endif
using namespace GPIN;
using namespace USART;



USART_InitTypeDef DJI = {
    230400,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    (USART_Mode_Rx | USART_Mode_Tx),
    USART_HardwareFlowControl_None
};

//! @variable system hardwares
usart *DJIport = new usart(usart1,2048,0,&DJI);
usart debug  = usart(usart2,1024);
usart upper2 = usart(usart3,1024);
usart upper = usart(uart4,1024);

//! @variable test funtions and variables
api_ctrl_without_sensor_data_t controlData;
int activation_callback_flag;
int controlFlag = 0;
int  ctrltime = 0;
mechanical machine;
void testStateMachine();
void ctrl();
void toCVTask();
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
void ECHO_TO_DEBUG_IRQ(usart *device);
void ECHO_TO_UPPER_IRQ(usart *device);
void ECHO_TO_DJIPORT_IRQ(usart *device);
#ifdef __cplusplus
}
#endif //__cplusplus



//! @note waitting to reconstruct.
extern void Send_Poll(void);
extern void spin_callback(void);
extern void CmdRecvThread(void);
extern cmd_handler_table_t cmd_handler_tab[];
extern set_handler_table_t set_handler_tab[];
extern sdk_3_12B_data_t Pos;
extern sdk_3_12B_data_t Agl;
extern volatile uint32_t ms;
extern volatile uint32_t pms;

uint8_t test = 0;


int main(void)
{

    rtc_init();

    machine = mechanical();
    machine.init();

    LittleTask::init();
    FlightControl::init();
    upper.print(0xAA);
    printf("!");



    //upper2.irq = ECHO_TO_DEBUG_IRQ;

    activation_msg.app_id = 0xF7B36;
    activation_msg.app_api_level = 2;
    activation_msg.app_ver = 1;
    memcpy(activation_msg.app_bundle_id,"1234567890123456789012", 32);
    char keydata[] = "821c8c3abeb6e340637b01f908ddeefb6c76d18d5f289e5cdb3cd5756a17bef5";
    key = keydata;

    Pro_Hw = new DJI_Pro_Hw();
    LittleTask stateMacine(testStateMachine,10,25);
    LittleTask control(ctrl,10,25);
    LittleTask toCV(toCVTask,20,4);
    stateMacine.start();
    toCV.start();

    Pro_Link_Setup();
    LittleTask sendPoll(Send_Poll,5,10,0);
    App_Recv_Set_Hook(App_Recv_Req_Data);
    App_Set_Table(set_handler_tab, cmd_handler_tab);
    LittleTask recv(CmdRecvThread,10,10,5);
    LittleTask callback(spin_callback,5,50,15);
    sendPoll.start();
    recv.start();
    callback.start();

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    DJIport->irq = 0;
    DJI_Onboard_API_Activation();
    FlightControl::set(0,0,0,0);

    printf("Hello World!");


    while(1)
    {
        LittleTask::pollTasks();
        Pro_Hw->run();
        if(ms > 10000)
            control.start();
    }
}

uint32_t debugms;
void testStateMachine()
{
    uint8_t data;
    if(debug.getRx()->read(data))
    {
        printf("RECV-DATA!\r\n");
        if(data == '1')
            FlightControl::set(0,0,0,0);
        if(data == '2')
            FlightControl::takeoff();
        if(data == '3')
            DJI_Onboard_API_Landing();
        if(data == '4')
            DJI_Onboard_API_Control(1);
        if(data == '5')
            printf("\r\nRol: %f\r\nPit: %f\r\nYaw: %f \r\n",Agl.x,Agl.y,Agl.z);
        if(data == '6')
            printf("\r\nYaw: %f\r\nHgt: %f\r\nAlt: %f\r\n",Agl.z,recv_sdk_std_msgs.pos.height,recv_sdk_std_msgs.pos.alti);
        if(data == '7')
            FlightControl::set(199,0,0,0);
        if(data == '8')
            FlightControl::set(10,0,0,0);
        if(data == '9')
            FlightControl::set(0,199,0,0);
        if(data == 'A')
            FlightControl::set(0,-199,0,0);
        if(data == 'B')
            FlightControl::set(-199,0,0,0);
        if(data == 'C')
            FlightControl::set(-10,0,0,0);
        if(data == 'D')
            DJI_Onboard_API_Activation();
        if(data == 'E')
        {
            //complex = true;
            printf("Enter complex mod!\r\n");
        }
        if(data == 'F')
        {
            //complex = false;
            printf("Quit complex mod~\r\n");
        }
        if(data == 'G')
            test = 1;
        if(data == 'H')
            test = 0;
        if(data == 'I')
        {
            TaskList::current = &TaskList::Little1;
            TaskList::init();
        }
        if(data == 'J')
        {
            TaskList::current = &TaskList::Little2;
            TaskList::init();
        }
        if(data == 'K')
        {
            TaskList::current = &TaskList::Little3;
            TaskList::init();
        }
        if(data == 'L')
        {
            TaskList::current = &TaskList::Little4;
            TaskList::init();
        }
        if(data == 'M')
            ;
        if(data == 'N')
        {
            TaskList::current = &TaskList::SetTakeOff;
            TaskList::init();
        }
        if(data == 'O')
        {
            TaskList::current = &TaskList::SetTest;
            TaskList::init();
        }
        if(data == 'P')
        {
            TaskList::current = &TaskList::SetLandIn;
            TaskList::init();
        }
        if(data == 'Q')
            ;
        if(data == 'R')
            ;
        if(data == 'S')
            ;
        if(data == 'T')
        {
            TaskList::current = &TaskList::SetBack;
            TaskList::init();
        }
        if(data == 'U')
        {
            TaskList::current = &TaskList::Little1;
            TaskList::init();
        }
        if(data == 'V')
        {
            if(TaskList::current == 0)
            {
                TaskList::current = &TaskList::SetMini;
                TaskList::init();
            }
        }
        if(data == 'W')
        {
            TaskList::current = &TaskList::SetLine;
            TaskList::init();
        }
        if(data == 'X')
        {
            TaskList::current = &TaskList::SetTake;
            TaskList::init();
        }
        if(data == 'Y')
        {
            TaskList::current = &TaskList::SetDrop;
            TaskList::init();
        }
        if(data == 'Z')
        {
            TaskList::current = &TaskList::SetBasket;
            TaskList::init();
        }
    }
}

void ctrl()
{
    static bool initDone = false;
    if(initDone)
    {
        TaskList::pollTask();
        App_Send_Data(0, 0, MY_CTRL_CMD_SET, API_CTRL_REQUEST, (unsigned char*)&command, sizeof(command), NULL, 0, 0);
    }
    else
    {
        initDone = Logic::offSet();
        if(initDone)
        {
            printf("Init done!! data: %f %f %f",offset::height,offset::altitude,offset::yaw);
            FlightControl::set(0,0,0,0);
        }
    }
    //printf("%d",ms);
}
volatile bool needLine = true;
volatile bool needBasket = true;
volatile bool needCirc = false;//true;
volatile bool needGrids = false;//true;
volatile bool needBlack = false;//true;
volatile bool needHeight = false;//true;
volatile bool needBlue = true;

volatile bool lineRefresh = false;
volatile bool basketRefresh = false;
volatile bool blueRefresh = false;
extern sBlue tmpBlue;
void toCVTask()
{
    uint8_t data;
    static volatile bool complex;
    complex = true;
    if(complex)
    {
        bool quit = false;
        while(upper.getRx()->read(data))
            quit = FlightControl::decode(data);
        if(quit)
        {
            printf("\r\nQuit complex mod\r\n");
            while(upper.getRx()->read(data));
            complex = false;
        }
    }
    if(needLine)
        upper<<"line";//0xCC
    if(needBasket)
        upper<<"blac";//0xDD
    if(needCirc)
        upper<<"circ";//0xBB
    if(needGrids)
        upper<<"tags";//0xCC
    if(needHeight)
        upper<<"heig";//0x99
    if(needBlue)
        upper<<"blue";//0xEE
    if(test == 1)
    {
        pms = 0;
        test = 2;
    }
    if(test == 2)
    {
        if(TaskList::current == 0)
        {
            TaskList::current = &TaskList::SetTakeOff;
            TaskList::init();
        }
        if(pms > 10000)
            test = 3;
    }
    if(test == 3)
    {
        if(TaskList::current == 0)
        {
            TaskList::current = &TaskList::Little1;
            TaskList::init();
        }
        if(pms > 17000)
            test = 4;
    }
    if(test == 4)
    {
        if(TaskList::current == 0)
        {
            TaskList::current = &TaskList::SetDrop;
            TaskList::init();
        }
        if(TaskList::current == 0)
        {
            test = 5;
            pms = 0;
        }
    }
    if(test == 5)
    {
        if(TaskList::current == 0)
        {
            TaskList::current = &TaskList::Little2;
            TaskList::init();
        }
        if(pms > 8000)
            test = 5;
    }
    if(test == 6)
    {
        DJI_Onboard_API_Landing();
        //if(pms > 28000)
        test = 0;
    }
    if(test == 7)
    {
        TaskList::current = &TaskList::SetTake;
        TaskList::init();
        if(TaskList::current == 0)
        {

            test = 8;
            pms = 0;
        }
    }
    if(test == 8)
    {
        FlightControl::takeoff();
        TaskList::init();
        if(pms > 8000)
        {
            test = 9;
            pms = 0;
        }
    }
    if(test == 9)
    {
        if(machine.hasball())
        {

        }
    }
    else
    {

    }
    pms = 0;
}



//! @code Echo functions for  port test
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
void ECHO_TO_DEBUG_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        debug.print(data);
    }
}

void ECHO_TO_UPPER_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        upper.print(data);
    }
}
void ECHO_TO_DJIPORT_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        DJIport->print(data);
    }
}

#ifdef __cplusplus
}
#endif //__cplusplus
//! @endcode Echo functions for port test
