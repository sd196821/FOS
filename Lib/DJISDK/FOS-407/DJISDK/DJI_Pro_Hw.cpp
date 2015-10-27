#include "DJI_Pro_Hw.h"
#include "DJI_Pro_Codec.h"

#include <string.h>
#include <stdio.h>
#include <string.h>

#include "DJI_Pro_Link.h"
#include "DJI_Pro_Codec.h"
#include "usart.h"

DJI_Pro_Hw *Pro_Hw;
unsigned char DJIbuffer[DJI_PRO_HW_BUFFER_SIZE];
extern USART::usart *DJIport;

DJI_Pro_Hw::DJI_Pro_Hw() :   pbuffer(NULL)
{
    port = DJIport;
    pbuffer = DJIbuffer;
}
void DJI_Pro_Hw::Pro_Hw_Send(unsigned char *buf, int len)
{
    for(int i = 0; i < len; ++i)
    {
        port->print(buf[i]);
    }
}
void DJI_Pro_Hw::run()
{
    uint8_t data;
    while(port->getRx()->read(data))
    {
        sdk_serial_byte_handle(data);
    }
}

