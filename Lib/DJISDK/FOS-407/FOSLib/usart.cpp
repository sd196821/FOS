#include "usart.h"
#ifdef STM32F40x
#include "stm32f4xx.h"
#include <stdint.h>
#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#endif

#ifdef STM32F10x
#include "stm32f10x.h"
#include <stdio.h>



#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#endif

USART::usart *usart1Device;
USART::usart *usart2Device;
USART::usart *usart3Device;
USART::usart *uart4Device;

namespace USART
{
Buffer *empty = 0;
USART_InitTypeDef defaultInit = {
    115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    (USART_Mode_Rx | USART_Mode_Tx),
    USART_HardwareFlowControl_None
};
usart::usart(usartPort Port, Buffer *RX, Buffer *TX,Size irqPos,USART_InitTypeDef *Info)
{
    init(Port,RX,TX,irqPos,Info);
}

void usart::init(usartPort Port, Buffer *RX, Buffer *TX, Size irqPos, USART_InitTypeDef *Info)
{
    pos = irqPos;
    irq = 0;
    port = (FOSUSART)Port;
    rx = RX;
    tx = TX;

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;


    GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10x
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO , ENABLE);
#endif
#ifdef STM32F40x
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
#endif

#ifdef STM32F10x
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#endif
#ifdef STM32F40x
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
#endif

    switch(Port) //config TX Port
    {
#ifdef STM32F40x
    //case uart1:
#endif
    case usart1:
        usart1Device = this;
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
#endif
        break;
#ifdef STM32F40x
        //case uart2:
#endif
    case usart2:
        usart2Device = this;
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
#endif
        break;
#ifdef STM32F40x
        //case uart3:
#endif
    case usart3:
        usart3Device = this;
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
#endif
        break;
#ifdef STM32F40x
    case uart4:
        uart4Device = this;
        NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
        break;
#endif
    }
    NVIC_Init(&NVIC_InitStructure);

#ifdef STM32F10x
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif
#ifdef STM32F40x
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
#endif
    switch(Port) //config RX Port
    {
#ifdef STM32F40x
    //case uart1:
#endif
    case usart1:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
#endif
        break;
#ifdef STM32F40x
        //case uart2:
#endif
    case usart2:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
#endif
        break;
#ifdef STM32F40x
        //case uart3:
#endif
    case usart3:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
#ifdef STM32F40x
        GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
#endif
        break;
#ifdef STM32F40x
    case uart4:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
        break;
#endif
    }

    USART_ClearFlag(port, USART_FLAG_TC);
    USART_Init(port,Info);
    USART_Cmd(port, ENABLE);
    USART_ITConfig(port, USART_IT_RXNE, ENABLE);
}

void usart::flush(size_t len)
{
    rx->flush(len);
}

usart::usart(usartPort Port, Size bufferSize, Size irqPos, USART_InitTypeDef *Info)
{
    Buffer* Rxbuf = new Buffer(bufferSize);
    Buffer* Txbuf = new Buffer(bufferSize);
    init(Port,Rxbuf,Txbuf,irqPos,Info);
}

void usart::print(uint8_t Byte) const
{
    if(tx->write(Byte) != true)
        USART_ITConfig(port, USART_IT_TXE, DISABLE);
    else
        USART_ITConfig(port, USART_IT_TXE, ENABLE);
}
void usart::printch(char ch) const
{
    print((uint8_t)ch);
}

void usart::printdec(unsigned int dec) const
{
    if(dec==0)
        return;
    printdec(dec/10);
    printch((char)(dec%10 + '0'));
}

void usart::printdecSigned(int dec) const
{
    if(dec > 0)
        printdec(dec);
    else
    {
        printch('-');
        printdec(-dec);
    }
}

void usart::printflt(double flt) const
{
    int tmpint = 0;
    unsigned int tint = 0;

    tmpint = (int)flt;
    printdecSigned(tmpint);
    printch('.');
    flt = flt - tmpint;
    tint = (flt * 1000000);
    printdec(tint);
}

void usart::printbin(int bin) const
{
    if(bin == 0)
    {
        printstr("0b");
        return;
    }
    printbin(bin/2);
    printch((char)(bin%2+'0'));
}

//int dps = 0;
void usart::printhex(unsigned int hex) const
{
    if(hex == 0)//||(dps>30))
    {
        printstr("0x");
        return;
    }
    printhex(hex>>4);
    if(hex%16 < 10)
        printch((char)(hex%16 + '0'));
    else
        printch((char)(hex%16 - 10 + 'A'));
}

void usart::printstr(char *str) const
{
    while(*str)
        printch(*str++);
}

void usart::defaultIRQHandler(usart *device)
{
    if(USART_GetITStatus(device->port, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(device->port,USART_IT_RXNE);
        uint8_t tmp = (uint8_t)USART_ReceiveData(device->port);
        if(!(device->rx->write(tmp)))
            USART_ITConfig(device->port, USART_IT_RXNE, DISABLE);
        else
            if(((device->rx->length()) >= (device->pos))&&(device->irq != 0))
                (*(device->irq))(device);
        return;
    }
    if(USART_GetITStatus(device->port, USART_IT_TXE) != RESET)
    {
        USART_ClearITPendingBit(device->port,USART_IT_TXE);
        uint8_t tmp = 'c';
        if(device->tx->read(tmp))
            USART_SendData(device->port,tmp);

        else
            USART_ITConfig(device->port, USART_IT_TXE, DISABLE);
        return;
    }
}
Buffer *usart::getRx() const
{
    return rx;
}

Buffer *usart::getTx() const
{
    return tx;
}

void usart::setIRQRunPoint(Size runPos)
{
    pos = runPos;
}

Buffer::Buffer(uint8_t *spacePointer, Size s)
{
    init(spacePointer,s);
}

Buffer::Buffer(Size s)
{
    init(new uint8_t[s],s);
}

void Buffer::init(uint8_t *spacePointer, Size s)
{
    Memory = spacePointer;
    size = s;
    Read = 0;
    Write = 0;
    writeable = true;
    readable = false;
}

bool Buffer::write(uint8_t &data)
{
    if(writeable)
    {
        Memory[Write++] = data;
        if(Write == size)
            Write = 0;
        if(Write == Read)
            writeable = false;
        readable = true;
        return true;
    }
    return false;
}

bool Buffer::writeMultible(uint8_t *data, Size s)
{
    return false;
}

bool Buffer::read(uint8_t &data)
{
    __disable_irq();
    if(readable)
    {
        data = Memory[Read++];
        if(Read == size)
            Read = 0;
        if(Read == Write)
            readable = false;
        writeable = true;
        __enable_irq();
        return true;
    }
    __enable_irq();
    return false;
}

bool Buffer::readMultible(void *data, Size s)
{
    uint8_t tmp;
    if(length() >= s)
    {
        for(int i = 0; i < i; ++i)
            if(read(tmp))
                ((uint8_t *)data)[i] = tmp;
            else
                return false;
        return true;
    }
    return false;
}

bool Buffer::isEmpty()
{
    return ((Read == Write)&&writeable);
}

bool Buffer::isFull()
{
    return ((Read == Write)&&readable);
}

bool Buffer::recallRead()
{
    //!@todo test
    __disable_irq();
    if(writeable)
    {
        if(Read == 0)
            Read = size - 1;
        else
            Read--;
        if(Read == Write)
            writeable = false;
        readable = true;
    }
    __enable_irq();
    return false;
}

Size Buffer::length()
{
    if(Read == Write)
        return 0;
    else
    {
        if(Write > Read)
            return Write - Read;
        else
            return size - Read + Write;
    }
    return 0;
}

void Buffer::flush(int32_t len)
{
    if(abs(len) < length())
    {
        if(len > 0)
        {

            return;
        }
        if(len < 0)
        {
            return;
        }
    }
    else
    {
        //!@note flush all, no matter what position these pointer at.
        Read = Write;
        readable = false;
    }
}

}


#ifdef __cplusplus
extern "C" {
#endif
void USART1_IRQHandler(void)
{
    __disable_irq();
    USART::usart::defaultIRQHandler(usart1Device);
    __enable_irq();
}

void USART2_IRQHandler(void)
{
    __disable_irq();
    USART::usart::defaultIRQHandler(usart2Device);
    __enable_irq();
}

void USART3_IRQHandler(void)
{
    __disable_irq();
    USART::usart::defaultIRQHandler(usart3Device);
    __enable_irq();
}


void UART4_IRQHandler(void)
{
    __disable_irq();
    USART::usart::defaultIRQHandler(uart4Device);
    __enable_irq();
}
#ifdef __cplusplus
}
#endif
