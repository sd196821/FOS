/*! \cond
 * ==============================================================================
 *
 *                        
 *                          Copyright (C) 2013-2015 YOGITECH S.p.A. 
 *                          PROPRIETARY YOGITECH S.p.A., ALL RIGHTS RESERVED
 *
 *  This file is part of fRSTL_EVAL, an evaluation tool provided by YOGITECH to
 *  prototype the functional integration of YOGITECH’s fRSTL products. 
 *
 *  IMPORTANT SAFETY INFORMATION
 *  
 *  fRSTL_EVAL is an evaluation  version of the YOGITECH fRSTL product. It has
 *  no safety properties at all and it is distributed only to allow early integration
 *  and prototyping of safety applications integrating the fRSTL product. Only the
 *  functionality of the safety fRSTL product is reproduced, but the diagnostic
 *  capability is not in the fRSTL_EVAL code. In any case fRSTL_EVAL shall not be
 *  intended to be used for verification or signoff purpose in place of the fRSTL
 *  full-featured product.
 *  To get a license of fRSTL product and receive the product deliverables including
 *  source code please contact YOGITECH at frstl_stm32@yogitech.com
 *  
 *  LEGAL NOTICE
 *  
 *  This code is proprietary information of YOGITECH, and is supplied subject to, and
 *  may be used, as general reference to YOGITECH fRSTL products.
 *  This code is provided "as is" and is subject to change without notice according to
 *  continuous product development and improvements. All product details and product
 *  usage described in this code are provided by YOGITECH S.p.A. in good faith.
 *  YOGITECH does not make, and expressly disclaims, any representations or warranties
 *  as to the completeness, accuracy, fitness for a particular purpose, or usefulness
 *  of the information contained in this code. 
 *  In no event will YOGITECH be liable for loss of profits, loss of revenues, loss of
 *  savings, loss of use, loss or corruption of data or any indirect, incidental, special,
 *  exemplary, punitive or consequential damages, whether under tort, contract or other
 *  theories of recovery in connection with the application of this code.
 *  YOGITECH does not warrant that use of this code will not infringe any third party
 *  rights.
 *   
 *  Do not reproduce in any form.
 *  This code is proprietary to YOGITECH SPA. Disclosure rights, copies, reproduction
 *  or distribution of this code are subject to specific agreement conditions
 *
 *
 *  Product release:             <_Product_Release_Label_>
 *
 *  Internal Revision Status:    <_Internal_Revision_Status_Label_>
 *
 *  File Revision:               $Revision: X.Y $
 *
 *------------------------------------------------------------------------------
 * \endcond
 */
/*!
 *
 * \file  frstl_peripherals.h
 * \brief this files contains public configuration data
          and function APIs of the peripherals module
 *
 */
#ifndef FRSTL_PERIPH_API_H
#define FRSTL_PERIPH_API_H

#include <frstl_config_PN.h>


 /* Enum type definition for the HW Configuration registers
  * This is specific for F405/F407 PNs.
  * 
  */

typedef enum {

/* DMA */
/* DMA Controller 0 */
/* Channel (stream) 0 */
#ifdef STL_DMA_0_CH_0
   DMA_0_M0AR_0_ID = 0,
   DMA_0_PAR_0_ID,
   DMA_0_CR_0_ID,
#endif /* STL_DMA_0_CH_0 */
/* End of Channel (stream) 0 */

/* Channel (stream) 1 */
#ifdef STL_DMA_0_CH_1
   DMA_0_M0AR_1_ID,
   DMA_0_PAR_1_ID,
   DMA_0_CR_1_ID,
#endif /* STL_DMA_0_CH_1 */
/* End of Channel (stream) 1 */

/* Channel (stream) 2 */
#ifdef STL_DMA_0_CH_2
   DMA_0_M0AR_2_ID,
   DMA_0_PAR_2_ID,
   DMA_0_CR_2_ID,
#endif /* STL_DMA_0_CH_2 */
/* End of Channel (stream) 2 */

/* Channel (stream) 3 */
#ifdef STL_DMA_0_CH_3
   DMA_0_M0AR_3_ID,
   DMA_0_PAR_3_ID,
   DMA_0_CR_3_ID,
#endif /* STL_DMA_0_CH_3 */
/* End of Channel (stream) 3 */

/* Channel (stream) 4 */
#ifdef STL_DMA_0_CH_4
   DMA_0_M0AR_4_ID,
   DMA_0_PAR_4_ID,
   DMA_0_CR_4_ID,
#endif /* STL_DMA_0_CH_4 */
/* End of Channel (stream) 4 */

/* Channel (stream) 5 */
#ifdef STL_DMA_0_CH_5
   DMA_0_M0AR_5_ID,
   DMA_0_PAR_5_ID,
   DMA_0_CR_5_ID,
#endif /* STL_DMA_0_CH_5 */
/* End of Channel (stream) 5 */

/* Channel (stream) 6 */
#ifdef STL_DMA_0_CH_6
   DMA_0_M0AR_6_ID,
   DMA_0_PAR_6_ID,
   DMA_0_CR_6_ID,
#endif /* STL_DMA_0_CH_6 */
/* End of Channel (stream) 6 */

/* Channel (stream) 7 */
#ifdef STL_DMA_0_CH_7
   DMA_0_M0AR_7_ID,
   DMA_0_PAR_7_ID,
   DMA_0_CR_7_ID,
#endif /* STL_DMA_0_CH_7 */
/* End of Channel (stream) 7 */
/* End of DMA Controller 0 */

/* DMA Controller 1 */
/* Channel (stream) 0 */
#ifdef STL_DMA_1_CH_0
   DMA_1_M0AR_0_ID,
   DMA_1_PAR_0_ID,
   DMA_1_CR_0_ID,
#endif /* STL_DMA_1_CH_0 */
/* End of Channel (stream) 0 */

/* Channel (stream) 1 */
#ifdef STL_DMA_1_CH_1
   DMA_1_M0AR_1_ID,
   DMA_1_PAR_1_ID,
   DMA_1_CR_1_ID,
#endif /* STL_DMA_1_CH_1 */
/* End of Channel (stream) 1 */

/* Channel (stream) 2 */
#ifdef STL_DMA_1_CH_2
   DMA_1_M0AR_2_ID,
   DMA_1_PAR_2_ID,
   DMA_1_CR_2_ID,
#endif /* STL_DMA_1_CH_2 */
/* End of Channel (stream) 2 */

/* Channel (stream) 3 */
#ifdef STL_DMA_1_CH_3
   DMA_1_M0AR_3_ID,
   DMA_1_PAR_3_ID,
   DMA_1_CR_3_ID,
#endif /* STL_DMA_1_CH_3 */
/* End of Channel (stream) 3 */

/* Channel (stream) 4 */
#ifdef STL_DMA_1_CH_4
   DMA_1_M0AR_4_ID,
   DMA_1_PAR_4_ID,
   DMA_1_CR_4_ID,
#endif /* STL_DMA_1_CH_4 */
/* End of Channel (stream) 4 */

/* Channel (stream) 5 */
#ifdef STL_DMA_1_CH_5
   DMA_1_M0AR_5_ID,
   DMA_1_PAR_5_ID,
   DMA_1_CR_5_ID,
#endif /* STL_DMA_1_CH_5 */
/* End of Channel (stream) 5 */

/* Channel (stream) 6 */
#ifdef STL_DMA_1_CH_6
   DMA_1_M0AR_6_ID,
   DMA_1_PAR_6_ID,
   DMA_1_CR_6_ID,
#endif /* STL_DMA_1_CH_6 */
/* End of Channel (stream) 6 */

/* Channel (stream) 7 */
#ifdef STL_DMA_1_CH_7
   DMA_1_M0AR_7_ID,
   DMA_1_PAR_7_ID,
   DMA_1_CR_7_ID,
#endif /* STL_DMA_1_CH_7 */
/* End of Channel (stream) 7 */
/* End of DMA Controller 1 */
/* End of DMA */


/* NVIC */
#ifdef STL_NVIC
   NVIC_IPR0_ID,
   NVIC_IPR1_ID,
   NVIC_IPR2_ID,
   NVIC_IPR3_ID,
   NVIC_IPR4_ID,
   NVIC_IPR5_ID,
   NVIC_IPR6_ID,
   NVIC_IPR7_ID,
   NVIC_IPR8_ID,
   NVIC_IPR9_ID,
   NVIC_IPR10_ID,
   NVIC_IPR11_ID,
   NVIC_IPR12_ID,
   NVIC_IPR13_ID,
   NVIC_IPR14_ID,
   NVIC_IPR15_ID,
   NVIC_IPR16_ID,
   NVIC_IPR17_ID,
   NVIC_IPR18_ID,
   NVIC_IPR19_ID,
   NVIC_IPR20_ID,
#endif /* STL_NVIC */
/* End of NVIC */


/* EXTI */
#ifdef STL_EXTI
   EXTI_IMR_ID,
   EXTI_EMR_ID,
   EXTI_RTSR_ID,
   EXTI_FTSR_ID,
#endif /* STL_EXTI */
/* End of EXTI */


/* WWDG */
#ifdef STL_WWDG
   WWDG_CFR_ID,
#endif /* STL_WWDG */
/* End of WWDG */


/* IWDG */
#ifdef STL_IWDG
   IWDG_PR_ID,
   IWDG_RLR_ID,
#endif /* STL_IWDG */
/* End of IWDG */


/* RTC */
#ifdef STL_RTC
   RTC_PRER_ID,
   RTC_ALRMAR_ID,
   RTC_ALRMBR_ID,
#endif /* STL_RTC */
/* End of RTC */


/* I2C */
/* Channel 1 */
#ifdef STL_I2C_1
   I2C_1_CR1_ID,
   I2C_1_OAR1_ID,
   I2C_1_OAR2_ID,
#endif /* STL_I2C_1 */
/* End of Channel 1 */

/* Channel 2 */
#ifdef STL_I2C_2
   I2C_2_CR1_ID,
   I2C_2_OAR1_ID,
   I2C_2_OAR2_ID,
#endif /* STL_I2C_2 */
/* End of Channel 2 */

/* Channel 3 */
#ifdef STL_I2C_3
   I2C_3_CR1_ID,
   I2C_3_OAR1_ID,
   I2C_3_OAR2_ID,
#endif /* STL_I2C_3 */
/* End of Channel 3 */
/* End of I2C */


/* USART */
/* Channel 1 */
#ifdef STL_USART_1
   USART_1_CR1_ID,
   USART_1_CR2_ID,
   USART_1_CR3_ID,
   USART_1_BRR_ID,
   USART_1_GTPR_ID,
#endif /* STL_USART_1 */
/* End of Channel 1 */

/* Channel 2 */
#ifdef STL_USART_2
   USART_2_CR1_ID,
   USART_2_CR2_ID,
   USART_2_CR3_ID,
   USART_2_BRR_ID,
   USART_2_GTPR_ID,
#endif /* STL_USART_2 */
/* End of Channel 2 */

/* Channel 3 */
#ifdef STL_USART_3
   USART_3_CR1_ID,
   USART_3_CR2_ID,
   USART_3_CR3_ID,
   USART_3_BRR_ID,
   USART_3_GTPR_ID,
#endif /* STL_USART_3 */
/* End of Channel 3 */

/* Channel 4 */
#ifdef STL_USART_4
   USART_4_CR1_ID,
   USART_4_CR2_ID,
   USART_4_CR3_ID,
   USART_4_BRR_ID,
   /* For F405/F407, USART_4_GTPR register is totally reserved. */
#endif /* STL_USART_4 */
/* End of Channel 4 */

/* Channel 5 */
#ifdef STL_USART_5
   USART_5_CR1_ID,
   USART_5_CR2_ID,
   USART_5_CR3_ID,
   USART_5_BRR_ID,
   /* For F405/F407, USART_5_GTPR register is totally reserved. */
#endif /* STL_USART_5 */
/* End of Channel 5 */

/* Channel 6 */
#ifdef STL_USART_6
   USART_6_CR1_ID,
   USART_6_CR2_ID,
   USART_6_CR3_ID,
   USART_6_BRR_ID,
   USART_6_GTPR_ID,
#endif /* STL_USART_6 */
/* End of Channel 6 */
/* End of USART */


/* RCC */
#ifdef STL_RCC
   RCC_CFGR_ID,
   RCC_AHB1ENR_ID,
   RCC_AHB2ENR_ID,
   RCC_AHB3ENR_ID,
   RCC_AHB1LPENR_ID,
   RCC_AHB2LPENR_ID,
   RCC_AHB3LPENR_ID,
   RCC_APB2ENR_ID,
   RCC_APB1ENR_ID,
#endif /* STL_RCC */
/* End of RCC */


/* GPIO */
/* Channel (port) A */
#ifdef STL_GPIO_A
   GPIO_A_MODER_ID,
   GPIO_A_OTYPER_ID,
   GPIO_A_OSPEEDR_ID,
   GPIO_A_PUPDR_ID,
   GPIO_A_ODR_ID,
   GPIO_A_AFRL_ID,
   GPIO_A_AFRH_ID,
#endif /* STL_GPIO_A */
/* End of Channel (port) A */

/* Channel (port) B */
#ifdef STL_GPIO_B
   GPIO_B_MODER_ID,
   GPIO_B_OTYPER_ID,
   GPIO_B_OSPEEDR_ID,
   GPIO_B_PUPDR_ID,
   GPIO_B_ODR_ID,
   GPIO_B_AFRL_ID,
   GPIO_B_AFRH_ID,
#endif /* STL_GPIO_B */
/* End of Channel (port) B */

/* Channel (port) C */
#ifdef STL_GPIO_C
   GPIO_C_MODER_ID,
   GPIO_C_OTYPER_ID,
   GPIO_C_OSPEEDR_ID,
   GPIO_C_PUPDR_ID,
   GPIO_C_ODR_ID,
   GPIO_C_AFRL_ID,
   GPIO_C_AFRH_ID,
#endif /* STL_GPIO_C */
/* End of Channel (port) C */

/* Channel (port) D */
#ifdef STL_GPIO_D
   GPIO_D_MODER_ID,
   GPIO_D_OTYPER_ID,
   GPIO_D_OSPEEDR_ID,
   GPIO_D_PUPDR_ID,
   GPIO_D_ODR_ID,
   GPIO_D_AFRL_ID,
   GPIO_D_AFRH_ID,
#endif /* STL_GPIO_D */
/* End of Channel (port) D */

/* Channel (port) E */
#ifdef STL_GPIO_E
   GPIO_E_MODER_ID,
   GPIO_E_OTYPER_ID,
   GPIO_E_OSPEEDR_ID,
   GPIO_E_PUPDR_ID,
   GPIO_E_ODR_ID,
   GPIO_E_AFRL_ID,
   GPIO_E_AFRH_ID,
#endif /* STL_GPIO_E */
/* End of Channel (port) E */

/* Channel (port) F */
#ifdef STL_GPIO_F
   GPIO_F_MODER_ID,
   GPIO_F_OTYPER_ID,
   GPIO_F_OSPEEDR_ID,
   GPIO_F_PUPDR_ID,
   GPIO_F_ODR_ID,
   GPIO_F_AFRL_ID,
   GPIO_F_AFRH_ID,
#endif /* STL_GPIO_F */
/* End of Channel (port) F */

/* Channel (port) G */
#ifdef STL_GPIO_G
   GPIO_G_MODER_ID,
   GPIO_G_OTYPER_ID,
   GPIO_G_OSPEEDR_ID,
   GPIO_G_PUPDR_ID,
   GPIO_G_ODR_ID,
   GPIO_G_AFRL_ID,
   GPIO_G_AFRH_ID,
#endif /* STL_GPIO_G */
/* End of Channel (port) G */

/* Channel (port) H */
#ifdef STL_GPIO_H
   GPIO_H_MODER_ID,
   GPIO_H_OTYPER_ID,
   GPIO_H_OSPEEDR_ID,
   GPIO_H_PUPDR_ID,
   GPIO_H_ODR_ID,
   GPIO_H_AFRL_ID,
   GPIO_H_AFRH_ID,
#endif /* STL_GPIO_H */
/* End of Channel (port) H */

/* Channel (port) I */
#ifdef STL_GPIO_I
   GPIO_I_MODER_ID,
   GPIO_I_OTYPER_ID,
   GPIO_I_OSPEEDR_ID,
   GPIO_I_PUPDR_ID,
   GPIO_I_ODR_ID,
   GPIO_I_AFRL_ID,
   GPIO_I_AFRH_ID,
#endif /* STL_GPIO_I */
/* End of Channel (port) I */
/* End of GPIO */


/* SPI */
/* On F405/F407 PNs, SPI channels 2 and 3 have I2S function and registers. */
/* Channel 1 */
#ifdef STL_SPI_1
   SPI_1_CR1_ID,
   SPI_1_CR2_ID,
   SPI_1_CRCPR_ID,
#endif /* STL_SPI_1 */
/* End of Channel 1 */

/* Channel 2 */
#ifdef STL_SPI_2
   SPI_2_CR1_ID,
   SPI_2_CR2_ID,
   SPI_2_CRCPR_ID,
   SPI_2_I2SCFGR_ID,
   SPI_2_I2SPR_ID,
#endif /* STL_SPI_2 */
/* End of Channel 2 */

/* Channel 3 */
#ifdef STL_SPI_3
   SPI_3_CR1_ID,
   SPI_3_CR2_ID,
   SPI_3_CRCPR_ID,
   SPI_3_I2SCFGR_ID,
   SPI_3_I2SPR_ID,
#endif /* STL_SPI_3 */
/* End of Channel 3 */
/* End of SPI */


/* HDMI (CEC) is not present on F405/F407 */


/* ADC */
/* Device 1 */
#ifdef STL_ADC_1
   ADC_1_CR1_ID,
   ADC_1_CR2_ID,
   ADC_1_SMPR1_ID,
   ADC_1_SMPR2_ID,
   ADC_1_HTR_ID,
   ADC_1_LTR_ID,
#endif /* STL_ADC_1 */
/* End of Device 1 */

/* Device 2 */
#ifdef STL_ADC_2
   ADC_2_CR1_ID,
   ADC_2_CR2_ID,
   ADC_2_SMPR1_ID,
   ADC_2_SMPR2_ID,
   ADC_2_HTR_ID,
   ADC_2_LTR_ID,
#endif /* STL_ADC_2 */
/* End of Device 2 */

/* Device 3 */
#ifdef STL_ADC_3
   ADC_3_CR1_ID,
   ADC_3_CR2_ID,
   ADC_3_SMPR1_ID,
   ADC_3_SMPR2_ID,
   ADC_3_HTR_ID,
   ADC_3_LTR_ID,
#endif /* STL_ADC_3 */
/* End of Device 3 */
/* End of ADC */


/* DAC */
#ifdef STL_DAC
   DAC_DHR12L1_ID,
   DAC_DHR8R1_ID,
#endif /* STL_DAC */
/* End of DAC */


/* TIMERS */
/* TIMER 1 */
#ifdef STL_TIM_1
   TIM_1_PSC_ID,
   TIM_1_ARR_ID,
   #ifndef TIM_1_CC1_AS_INPUT
      TIM_1_CCR1_ID,
   #endif /* TIM_1_CC1_AS_INPUT */
   #ifndef TIM_1_CC2_AS_INPUT
      TIM_1_CCR2_ID,
   #endif /* TIM_1_CC2_AS_INPUT */
   #ifndef TIM_1_CC3_AS_INPUT
      TIM_1_CCR3_ID,
   #endif /* TIM_1_CC3_AS_INPUT */
   #ifndef TIM_1_CC4_AS_INPUT
      TIM_1_CCR4_ID,
   #endif /* TIM_1_CC4_AS_INPUT */
#endif /* STL_TIM_1 */
/* End of TIMER 1 */

/* TIMER 2 */
#ifdef STL_TIM_2
   TIM_2_PSC_ID,
   TIM_2_ARR_ID,
   #ifndef TIM_2_CC1_AS_INPUT
      TIM_2_CCR1_ID,
   #endif /* TIM_2_CC1_AS_INPUT */
   #ifndef TIM_2_CC2_AS_INPUT
      TIM_2_CCR2_ID,
   #endif /* TIM_2_CC2_AS_INPUT */
   #ifndef TIM_2_CC3_AS_INPUT
      TIM_2_CCR3_ID,
   #endif /* TIM_2_CC3_AS_INPUT */
   #ifndef TIM_2_CC4_AS_INPUT
      TIM_2_CCR4_ID,
   #endif /* TIM_2_CC4_AS_INPUT */
#endif /* STL_TIM_2 */
/* End of TIMER 2 */

/* TIMER 3 */
#ifdef STL_TIM_3
   TIM_3_PSC_ID,
   TIM_3_ARR_ID,
   #ifndef TIM_3_CC1_AS_INPUT
      TIM_3_CCR1_ID,
   #endif /* TIM_3_CC1_AS_INPUT */
   #ifndef TIM_3_CC2_AS_INPUT
      TIM_3_CCR2_ID,
   #endif /* TIM_3_CC2_AS_INPUT */
   #ifndef TIM_3_CC3_AS_INPUT
      TIM_3_CCR3_ID,
   #endif /* TIM_3_CC3_AS_INPUT */
   #ifndef TIM_3_CC4_AS_INPUT
      TIM_3_CCR4_ID,
   #endif /* TIM_3_CC4_AS_INPUT */
#endif /* STL_TIM_3 */
/* End of TIMER 3 */

/* TIMER 6 */
#ifdef STL_TIM_6
   TIM_6_PSC_ID,
   TIM_6_ARR_ID,
#endif /* STL_TIM_6 */
/* End of TIMER 6 */

/* TIMER 7 */
#ifdef STL_TIM_7
   TIM_7_PSC_ID,
   TIM_7_ARR_ID,
#endif /* STL_TIM_7 */
/* End of TIMER 7 */

/* TIMER 14 */
#ifdef STL_TIM_14
   TIM_14_PSC_ID,
   TIM_14_ARR_ID,
   #ifndef TIM_14_CC1_AS_INPUT
      TIM_14_CCR1_ID,
   #endif /* TIM_14_CC1_AS_INPUT */
#endif /* STL_TIM_14 */
/* End of TIMER 14 */

/* TIMER 15, 16, 17 are not present on F405/F407 PNs. */
/* End of TIMERS */


/* CAN - also known as bxCAN */
/* Channel 1 */
#ifdef STL_CAN_1
   CAN_1_IER_ID,
   CAN_1_BTR_ID,
   CAN_1_FM1R_ID,
   CAN_1_FA1R_ID,
#endif /* STL_CAN_1 */
/* End of Channel 1 */

/* Channel 2 */
#ifdef STL_CAN_2
   CAN_2_IER_ID,
   CAN_2_BTR_ID,
#endif /* STL_CAN_2 */
/* End of Channel 2 */
/* End of CAN */

/* DCMI */
#ifdef STL_DCMI
   DCMI_CWSTRT_ID,
   DCMI_CWSIZE_ID,
   DCMI_ESUR_ID,
   DCMI_ESCR_ID,
#endif /* STL_DCMI */
/* End of DCMI */

   STL_TOTAL_NUM_REGISTERS
} stl_prot_registers_t;



#endif /*FRSTL_PERIPH_API_H*/
