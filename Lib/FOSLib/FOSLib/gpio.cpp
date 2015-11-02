#include "gpio.h"
#ifdef STM32
namespace GPIN
{

GPin::GPin(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    port = GPIOx;
    pin = GPIO_InitStruct->GPIO_Pin;
    GPIO_Init(GPIOx,GPIO_InitStruct);
}

/*! @note GPIO_InitTypeDef is not necessary after init
 * So GPin will not save this structre any more
 */
bool GPin::Init(GPIO_InitTypeDef *GPIO_InitStruct)
{
    if(GPIO_InitStruct->GPIO_Pin == pin)
    {
        GPIO_Init(port,GPIO_InitStruct);
        return true;
    }
    return false;
}

bool GPin::read()
{
    return((bool)GPIO_ReadInputDataBit(port,pin));
}

void GPin::write(bool Value)
{
    if(Value)
        GPIO_WriteBit(port,pin,Bit_SET);
    else
        GPIO_WriteBit(port,pin,Bit_RESET);
}

}
#endif
