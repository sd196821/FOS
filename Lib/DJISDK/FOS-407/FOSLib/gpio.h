#ifndef FOSGPIN_H
#define FOSGPIN_H
#ifdef STM32
#ifdef __cplusplus
extern "C" {
#endif
#ifdef STM32F10x
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#endif
#ifdef STM32F40x
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#endif
#ifdef __cplusplus
}
#endif

namespace GPIN
{
class GPin
{
public:
    GPin(GPIO_TypeDef* GPIOx = 0,GPIO_InitTypeDef* GPIO_InitStruct = 0);
    bool Init(GPIO_InitTypeDef* GPIO_InitStruct = 0);

    bool read();
    void write(bool Value);

private:
    GPIO_TypeDef* port;
    uint16_t pin;

};


}
#endif //STM32
#endif // GPIN_H
