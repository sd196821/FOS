/*----------------------------------------Copyright (c)---------------------------------------------------                              
*                                       深圳市凯瑞莱科技开发

*
*      深圳市凯瑞莱科技开发提供的所有ST、TI、Freescale、Altera等平台的例程、文档、方案等资料信息旨在为学习者提供学习参考，
若使用者在使用过程中因任何原因造成直接或间接的损失，深圳市凯瑞莱科技开发不承担任何责任。
*  
*
*
*                                                                             深圳市凯瑞莱科技开发*

*
*----------------------------------------------------------------------------------------------------------
* File name:             key.h
* Author:                alvan 
* Version:               V1.0
* Date:                  2014-7-29
* Description:		        
* Function List:		
* History:    		
*-----------------------------------------------------------------------------------------------------------
*/

#ifndef  __KEY_H
#define  __KEY_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
#define GPIO_CTR_Key                         GPIOB
#define GPIO_Pin_CTR_Key                     GPIO_Pin_7
#define RCC_AHB1Periph_GPIO_CTR_Key          RCC_AHB1Periph_GPIOB    
		
#define KEY_VALUE_URSER_BUTTON               0x01
	
    
#define get_key_user_button                  GPIO_ReadInputDataBit(GPIO_CTR_Key, GPIO_Pin_CTR_Key)
    
	
void  key_init (void);

u8  get_key_state (void);

#ifdef __cplusplus
}
#endif

#endif


