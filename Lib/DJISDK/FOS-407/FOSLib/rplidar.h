#ifndef RPLIDAR_H
#define RPLIDAR_H
#include "usart.h"
#include <stdio.h>
using namespace USART;
#pragma pack(1)
typedef struct
{
uint8_t Quality;
uint16_t angle;
uint16_t distance;
} ScanFrame;
#pragma pack()
class RPLIDAR
{
private:
    //!@todo move it to an enum namespace
    enum State
    {
        CheckScanHead,
        Scaning,
        Stop,
        Echo,
        Error
    };
public:
    RPLIDAR(usart *Port = 0);
    void stop();
    void reset();
    void scan();
    void forceScan();
    void getInfo();
    void getHealth();
public:
    void freePoll();
    void setEcho(bool isEcho);
private:
    void restart();
    void sendCommand(uint8_t command);
private:
    usart *port;
    State flag;
    uint32_t time;
    uint32_t period;
    uint32_t test;
private:
    static uint8_t scanHead[];
    static const size_t scanHeadSize = 7;
    static const size_t scanFrameSize = 5;


};

#endif // RPLIDAR_H
