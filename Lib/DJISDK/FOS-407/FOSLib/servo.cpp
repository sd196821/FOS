#include "servo.h"

#ifdef STM32F10x
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"
#endif
#ifdef STM32F40x
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_conf.h"
#endif
Servo::Servo(TIM_TypeDef *TIMx, unsigned char Channel, unsigned int Infimum_us, unsigned int Supremum_us, unsigned char SkipDistance_us)
{
    TIM = TIMx;
    channel = Channel;
    inf = Infimum_us;
    sup = Supremum_us;
    skip = SkipDistance_us;

    TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    if(TIMx == TIM4)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    if(TIMx == TIM3)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_InternalClockConfig(TIMx);
    TIM_BaseInitStructure.TIM_Prescaler = 83;//1MHZ Clock
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStructure.TIM_Period = 1000000/FeqInHz - 1;
    TIM_BaseInitStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIMx,&TIM_BaseInitStructure);


    TIM_OCInitStructure.TIM_OCMode          = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState     = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState    = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity      = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity     = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState     = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState    = TIM_OCNIdleState_Reset;


    switch(channel)
    {
    case 0:
        TIM_OCInitStructure.TIM_Pulse = inf;
        TIM_OC1Init(TIMx,&TIM_OCInitStructure);
        TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
        break;
    case 1:
        TIM_OCInitStructure.TIM_Pulse = inf;
        TIM_OC2Init(TIMx,&TIM_OCInitStructure);
        TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Enable);
        break;
    case 2:
        TIM_OCInitStructure.TIM_Pulse = inf;
        TIM_OC3Init(TIMx,&TIM_OCInitStructure);
        TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Enable);
        break;
    case 3:
        TIM_OCInitStructure.TIM_Pulse = inf;
        TIM_OC4Init(TIMx,&TIM_OCInitStructure);
        TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Enable);
        break;
    default:
        break;
    }

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIMx, ENABLE);
    TIM_CtrlPWMOutputs(TIMx,ENABLE);
}

void Servo::setpos(unsigned int Pos)
{
    switch(channel)
    {
    case 0:
        TIM->CCR1 = convert(Pos);
        break;
    case 1:
        TIM->CCR2 = convert(Pos);
        break;
    case 2:
        TIM->CCR3 = convert(Pos);
        break;
    case 3:
        TIM->CCR4 = convert(Pos);
        break;
    default:
        break;
    }
}

unsigned int Servo::convert(unsigned int pos)
{
    unsigned int ans = inf + (pos*skip);
    return(ans > sup)?sup:ans;
}
