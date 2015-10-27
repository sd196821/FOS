#ifndef DJI_PRO_HW_H
#define DJI_PRO_HW_H

#include "usart.h"
#define DJI_PRO_HW_BUFFER_SIZE      1024


class DJI_Pro_Hw
{
public:
    explicit DJI_Pro_Hw();
private:
    USART::usart *port;
    unsigned char *pbuffer;
public:
    void Pro_Hw_Send(unsigned char *buf, int len);
    void run();
};

extern DJI_Pro_Hw *Pro_Hw;

#endif // DJI_PRO_HW_H
