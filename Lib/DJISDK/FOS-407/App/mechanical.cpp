#include "mechanical.h"

mechanical::mechanical()
{
}

void mechanical::init()
{
    take.setpos(100);
    move.setpos(100);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);

    take = Servo(TIM4,2);
    move = Servo(TIM4,3);

    take.setpos(500);
    move.setpos(495);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&GPIO_InitStruct);
}

bool mechanical::back()
{
    if(!(test(GPIO_Pin_12) == SET))
    {
        move.setpos(465);
        return false;
    }
    else
        move.setpos(495);
    return true;
}

bool mechanical::out()
{
    if(!(test(GPIO_Pin_11) == SET))
    {
        move.setpos(525);
        return false;
    }
    else
        move.setpos(495);
    return true;
}

bool mechanical::stop()
{
    move.setpos(495);
    return true;
}

bool mechanical::test(uint16_t port)
{
    return GPIO_ReadInputDataBit(GPIOD,port);
}

bool mechanical::atEnd()
{
    return ((test(GPIO_Pin_11) == SET)||(test(GPIO_Pin_12) == SET));
}

void mechanical::drop(int number)
{
    take.setpos(988-number*197);
}

bool mechanical::hasball()
{
    return ((test(GPIO_Pin_8) == SET)||(test(GPIO_Pin_9) == SET)||(test(GPIO_Pin_10) == SET)||(test(GPIO_Pin_13) == SET)||(test(GPIO_Pin_14) == SET));
}
