#ifndef FOSUSART_H
#define FOSUSART_H
#ifdef STM32
#ifdef STM32F10x
#include "stm32f10x_usart.h"
#endif
#ifdef STM32F40x
#include "stdint.h"
#include "stm32f4xx_usart.h"
#endif //STM32F40x

#ifdef DYNAMIC_MEMORY
#include "cppforstm32.h"
#endif //DYNAMIC_MEMORY
namespace USART{
class usart;
}
typedef void (*IRQHandler)(USART::usart *device);

/*! @todo move to a new file
 *  @note This is a USART model*/

namespace USART{
typedef USART_TypeDef* FOSUSART;
typedef uint32_t Size;

class Buffer;
extern Buffer *empty;
extern USART_InitTypeDef defaultInit;

enum usartPort
{
    usart1 = USART1_BASE,
    usart2 = USART2_BASE,
    usart3 = USART3_BASE,
#ifdef STM32F40x
//    uart1 = USART1_BASE,
//    uart2 = USART2_BASE,
//    uart3 = USART3_BASE,
    uart4 = UART4_BASE,
#endif
};

/** @brief this is a loop buffer.
 * To achive a loop buffer,we made two pointer, named "Read" and "Write"
 * Pointer "Read" is point to a data, which could be read.
 * Pointer "Write" is point to a data,which could be Write.
 * When these two pointer point to the end of buffer, it will set to '0' automaticly.
 * This feature made class "Buffer" be a loopbuffer.
 * @attention
 * read or wite a buffer might be fail, if it is empty or full;
 * All pointer operation must be controled under two bool variable, named "readable" and "writeable".
 * */
class Buffer
{
public:
    Buffer(uint8_t* spacePointer, Size s);
#ifdef DYNAMIC_MEMORY
    Buffer(Size s);
#endif //DYNAMIC_MEMORY
    void init(uint8_t* spacePointer, Size s);
public:
    bool write(uint8_t& data);
    bool writeMultible(uint8_t* data,Size s);
    bool read(uint8_t &data);
    bool readMultible(void *data, Size s);
    bool isEmpty();
    bool isFull();
    bool recallRead();
    Size length();
    void flush(int32_t len);
private:
    volatile bool readable;
    volatile bool writeable;
    volatile uint8_t* Memory;
    Size size;
    volatile Size Read;
    volatile Size Write;
};

class usart
{
    /*! init and settings*/
public:
#ifdef DYNAMIC_MEMORY
    usart(usartPort Port = usart1, Size bufferSize = 0,Size irqPos = 0,USART_InitTypeDef* Info = &defaultInit);
    usart(usartPort Port, Buffer *RX, Buffer *TX, Size irqPos = 0, USART_InitTypeDef* Info = &defaultInit);
#else
    usart(usartPort Port = usart1, Buffer *RX = empty, Buffer *TX = empty, Size irqPos = 0, USART_InitTypeDef* Info = &defaultInit);
#endif //DYNAMIC_MEMORY
private:
    void init(usartPort Port, Buffer *RX, Buffer *TX, Size irqPos = 0, USART_InitTypeDef* Info = &defaultInit);
    /*! port opreation*/
public:
    void flush(size_t len);
    /*! out stream*/
private:

    void printch(char ch)const;
    void printdec(unsigned int dec)const;
    void printdecSigned(int dec)const;
    void printflt(double flt)const;
    void printbin(int bin)const;
    void printhex(unsigned int hex)const;
    void printstr(char* str)const;
public:
    void print(uint8_t Byte)const;
    const usart &operator<<(unsigned int value)const
    {
        printhex(value);
        return *this;
    }
    const usart &operator<<(int value)const
    {
        printdecSigned(value);
        return *this;
    }
    const usart &operator<<(double value)const
    {
        printflt(value);
        return *this;
    }
    const usart &operator<<(char* value)const
    {
        printstr(value);
        return *this;
    }
    /*! interrupt function pointer*/
public:
    IRQHandler irq;
public:
    static void defaultIRQHandler(usart *device);
    /*! variables*/

public:
    Buffer *getRx() const;
    Buffer *getTx() const;
    void setIRQRunPoint(Size runPos);
private:
    FOSUSART port;
    Size pos;
    Buffer* rx;
    Buffer* tx;
};



}
#endif //STM32
#endif // FOSUSART_H
