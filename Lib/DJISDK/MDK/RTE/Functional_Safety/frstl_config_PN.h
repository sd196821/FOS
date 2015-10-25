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
 * \file  frstl_config_PN.h
 * \brief this file contains public configuration
 *        to let the end user properly configure the STL
 *
 */
#ifndef FRSTL_PERIPH_CONFIG_H
#define FRSTL_PERIPH_CONFIG_H

/* This header file is specific for F405/F407 Part Numbers. */


/* *** USER_CONFIG_PART_1 ***
 * Safety relevant peripheral channels. To disable the testing inside the STL
 *    of a specific channel, comment out the related line.
 */

/* DMA */
/* DMA Controller 0 */
/* Channel (stream) 0 */
#define STL_DMA_0_CH_0

/* Channel (stream) 1 */
#define STL_DMA_0_CH_1

/* Channel (stream) 2 */
#define STL_DMA_0_CH_2

/* Channel (stream) 3 */
#define STL_DMA_0_CH_3

/* Channel (stream) 4 */
#define STL_DMA_0_CH_4

/* Channel (stream) 5 */
#define STL_DMA_0_CH_5

/* Channel (stream) 6 */
#define STL_DMA_0_CH_6

/* Channel (stream) 7 */
#define STL_DMA_0_CH_7
/* End of DMA Controller 0 */

/* DMA Controller 1 */
/* Channel (stream) 0 */
#define STL_DMA_1_CH_0

/* Channel (stream) 1 */
#define STL_DMA_1_CH_1

/* Channel (stream) 2 */
#define STL_DMA_1_CH_2

/* Channel (stream) 3 */
#define STL_DMA_1_CH_3

/* Channel (stream) 4 */
#define STL_DMA_1_CH_4

/* Channel (stream) 5 */
#define STL_DMA_1_CH_5

/* Channel (stream) 6 */
#define STL_DMA_1_CH_6

/* Channel (stream) 7 */
#define STL_DMA_1_CH_7
/* End of DMA Controller 1 */
/* End of DMA */

/* NVIC */
#define STL_NVIC

/* EXTI */
#define STL_EXTI

/* WWDG */
#define STL_WWDG

/* IWDG */
#define STL_IWDG

/* RTC */
#define STL_RTC

/* I2C */
/* Channel 1 */
#define STL_I2C_1

/* Channel 2 */
#define STL_I2C_2

/* Channel 3 */
#define STL_I2C_3
/* End of I2C */


/* USART */
/* Channel 1 */
#define STL_USART_1

/* Channel 2 */
#define STL_USART_2

/* Channel 3 */
#define STL_USART_3

/* Channel 4 */
#define STL_USART_4

/* Channel 5 */
#define STL_USART_5

/* Channel 6 */
#define STL_USART_6
/* End of USART */

/* RCC */
#define STL_RCC

/* GPIO */
/* Channel (port) A */
#define STL_GPIO_A

/* Channel (port) B */
#define STL_GPIO_B

/* Channel (port) C */
#define STL_GPIO_C

/* Channel (port) D */
#define STL_GPIO_D

/* Channel (port) E */
#define STL_GPIO_E

/* Channel (port) F */
#define STL_GPIO_F

/* Channel (port) G */
#define STL_GPIO_G

/* Channel (port) H */
#define STL_GPIO_H

/* Channel (port) I */
#define STL_GPIO_I
/* End of GPIO */


/* SPI */
/* Channel 1 */
#define STL_SPI_1

/* Channel 2 */
#define STL_SPI_2

/* Channel 3 */
#define STL_SPI_3
/* End of SPI */


/* ADC */
/* Device 1 */
#define STL_ADC_1

/* Device 2 */
#define STL_ADC_2

/* Device 3 */
#define STL_ADC_3
/* End of ADC */

/* DAC */
#define STL_DAC

/* TIMERS */
/* TIMER 1 */
#define STL_TIM_1

/* TIMER 2 */
#define STL_TIM_2

/* TIMER 3 */
#define STL_TIM_3

/* TIMER 6 */
#define STL_TIM_6

/* TIMER 7 */
#define STL_TIM_7

/* TIMER 14 */
#define STL_TIM_14

/* TIMER 15, TIMER 16 and TIMER 17 are not present on F405 F407 PNs. */
/* End of TIMERS */

/* CAN */
/* Channel 1 */
#define STL_CAN_1

/* Channel 2 */
#define STL_CAN_2
/* End of CAN */

/* DCMI */
#define STL_DCMI
/* End of DCMI */

/* *** USER_CONFIG_PART_2 ***
 * Registers Custom removal settings
 * If it necessary to exclude some registers from the test, uncomment the related lines.
 */

/* TIMER 1 */
/* #define TIM_1_CC1_AS_INPUT */
/* #define TIM_1_CC2_AS_INPUT */
/* #define TIM_1_CC3_AS_INPUT */
/* #define TIM_1_CC4_AS_INPUT */


/* TIMER 2 */
/* #define TIM_2_CC1_AS_INPUT */
/* #define TIM_2_CC2_AS_INPUT */
/* #define TIM_2_CC3_AS_INPUT */
/* #define TIM_2_CC4_AS_INPUT */


/* TIMER 3 */
/* #define TIM_3_CC1_AS_INPUT */
/* #define TIM_3_CC2_AS_INPUT */
/* #define TIM_3_CC3_AS_INPUT */
/* #define TIM_3_CC4_AS_INPUT */


/* TIMER 14 */
/* #define TIM_14_CC1_AS_INPUT */


/* *** USER_CONFIG_PART_3 ***
 * Algorithm selection for the FLASH test.
 *  
 *  These settings only apply to the YOGITECH version.
 */
#define FLASH_TEST_USE_HW_CRC
/* #define FLASH_TEST_USE_SW_CRC */
/* #define FLASH_TEST_USE_SW_ALGO */

#endif /* FRSTL_PERIPH_CONFIG_H */
