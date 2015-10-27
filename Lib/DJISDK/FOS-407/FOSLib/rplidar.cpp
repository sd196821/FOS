#include "rplidar.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void RPLIDAR_SCAN_IRQ(usart *device);
void ECHO_IRQ(usart *device);
void ECHO_DEBUG_IRQ(usart *device);
#ifdef __cplusplus
}
#endif //__cplusplus

extern usart debug;
extern volatile uint32_t ms;
uint8_t RPLIDAR::scanHead[]={0xA5,0x5A,0x05,0x00,0x00,0x40,0x81};

RPLIDAR::RPLIDAR(usart *Port)
{
    time = ms;
    test = 0;
    flag = Stop;
    port = Port;
    port->irq =0;// RPLIDAR_SCAN_IRQ;
}

void RPLIDAR::stop()
{
    //!@todo test
    sendCommand(0x25);
}

void RPLIDAR::reset()
{
    /*! @test Class-A pass.
     *  @attention after reset, RPLIDAR will send a string to declear device info,
     *  this feature was not mentioned in RPLIDAR's SDK interface document.
     * */
    sendCommand(0x40);
}

void RPLIDAR::scan()
{
    //!@test Class-A pass.
    flag = CheckScanHead;
    sendCommand(0x20);
}

void RPLIDAR::forceScan()
{
    //!@todo test
    sendCommand(0x21);
}

void RPLIDAR::getInfo()
{
    //!@todo test
    sendCommand(0x50);
}

void RPLIDAR::getHealth()
{
    //!@todo test
    sendCommand(0x51);
}

void RPLIDAR::freePoll()
{
    uint8_t data;
    ScanFrame frame;
    uint8_t *tmp;
    switch(flag)
    {
    case Stop://!@todo actualize
        break;
    case CheckScanHead://!@test Class-A pass
        if(port->getRx()->length() >= scanHeadSize)
        {
            for(int i = 0; i < scanHeadSize; ++i)
            {
                if(port->getRx()->read(data))
                {
                    if(data != scanHead[i])
                    {
                        printf("Scan header missing! %x %x \r\n", data,scanHead[i]);
                        flag = Error;
                        return;
                    }
                }
                else
                {
                    printf("read error!");
                    flag = Error;
                }
            }
            flag = Scaning;
        }
        break;
    case Scaning:/*! @test Class-A pass
         *! @note usart's buffer size has a little problem,
         * it has been solved in an unusual way.
         * So the function of Buffer::length() still has a little bug,
         * we will debug later.
         * @todo debug
         * @bug Buffer::length()
         * */
        if(port->getRx()->length() >= 2*scanFrameSize)
        {
            tmp = (uint8_t*)&frame;
            for(int i = 0; i < scanFrameSize; ++i)
            {
                if(port->getRx()->read(data))
                {
                    tmp[i] = data;
                    //debug.print(data);
                }
                else
                    printf("Lack Data. %d \r\n",i);
            }

            uint8_t check = frame.Quality&0x03;
            if((check == 0x01)||(check == 0x02))
            {
                if(check == 0x01)
                {
                    period = ms - time;
                    time = ms;
                    printf("\r\nPeriod: %d\r\n",period);
                }
                if((frame.angle & 0x0001) == 1)
                {
                    if((frame.distance != 0)&&(debug.getTx()->length()<1800))
                    {
                        printf("Len %f @ %f\r\n",frame.distance/4.0,frame.angle/128.0);
                        test = ms;
                    }
                }
                else
                    printf("Error %d\r\n",__LINE__);
            }
            else
            {
                printf("%x \r\n",frame.Quality);
            }
        }
        break;
    default:
        //!@todo actualize, error state machine.
        break;
    }
}

void RPLIDAR::setEcho(bool isEcho)
{
    if(isEcho)
    {
        flag = Echo;
        port->irq = ECHO_IRQ;
        port->setIRQRunPoint(0);
        debug.irq = ECHO_DEBUG_IRQ;
        debug.setIRQRunPoint(0);
    }
    else
    {
        //!@todo actualize.
    }
}

void RPLIDAR::restart()
{
    //!@todo actualize.
}
void RPLIDAR::sendCommand(uint8_t command)
{
    port->print(0xA5);
    port->print(command);
}

extern usart radarPort;//!@attention for test only
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void RPLIDAR_SCAN_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        debug.print(data);
    }
}
void ECHO_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        debug.print(data);
    }
}
void ECHO_DEBUG_IRQ(usart *device)
{
    uint8_t data;
    while (device->getRx()->read(data))
    {
        radarPort.print(data);
    }
}

#ifdef __cplusplus
}
#endif //__cplusplus
