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
 * \file  frstl_flash_config.h
 * \brief this files contains private configuration data
          for the flash test module
 *
 */
#ifndef FRSTL_FLASH_CONFIG_H
#define FRSTL_FLASH_CONFIG_H

#include <frstl_part_number.h>

/* Flash Memory Base Address 
 *  
 */
#define FLASH_BASE_ADDRESS 0x08000000LU

/* Flash Slice Size in Bytes
 *  
 */
#define FLASH_SLICE_SIZE 1024LU

/* Flash Memory Size in Bytes
 *  
 */

#if defined STL_STM32F030F4 || defined STL_STM32F031C4 || defined STL_STM32F031F4 \
   || defined STL_STM32F031G4 || defined STL_STM32F031K4 || defined STL_STM32F051C4 \
   || defined STL_STM32F051K4 || defined STL_STM32F051R4 || defined STL_STM32F100C4 \
   || defined STL_STM32F100R4 || defined STL_STM32F101R4 || defined STL_STM32F101T4 \
   || defined STL_STM32F102C4 || defined STL_STM32F102R4 || defined STL_STM32F103C4 \
   || defined STL_STM32F103R4 || defined STL_STM32F103T4
   /* 16 Kbytes of Flash */
   #define FLASH_MEM_SIZE 16384U

#elif defined STL_STM32F030K6 || defined STL_STM32F030C6 || defined STL_STM32F031C6 \
   || defined STL_STM32F031F6 || defined STL_STM32F031G6 || defined STL_STM32F031K6 \
   || defined STL_STM32F051C6 || defined STL_STM32F051K6 || defined STL_STM32F051R6 \
   || defined STL_STM32L100C6 || defined STL_STM32L151C6 || defined STL_STM32L151R6 \
   || defined STL_STM32L152C6 || defined STL_STM32L152R6 || defined STL_STM32F100C6 \
   || defined STL_STM32F100R6 || defined STL_STM32F101C6 || defined STL_STM32F101R6 \
   || defined STL_STM32F101T6 || defined STL_STM32F102C6 || defined STL_STM32F102R6 \
   || defined STL_STM32F103C6 || defined STL_STM32F103R6 || defined STL_STM32F103T6
   /* 32 Kbytes of Flash */
   #define FLASH_MEM_SIZE 32768U

#elif defined STL_STM32F051R8 || defined STL_STM32F030C8 || defined STL_STM32F030R8 \
   || defined STL_STM32F051C8 || defined STL_STM32F051K8 || defined STL_STM32F071V8 \
   || defined STL_STM32F072C8 || defined STL_STM32F072R8 || defined STL_STM32F072V8 \
   || defined STL_STM32F105R8 || defined STL_STM32F105V8 || defined STL_STM32L100R8 \
   || defined STL_STM32L151C8 || defined STL_STM32L151R8 || defined STL_STM32L151V8 \
   || defined STL_STM32L152C8 || defined STL_STM32L152R8 || defined STL_STM32L152V8 \
   || defined STL_STM32F100C8 || defined STL_STM32F100R8 || defined STL_STM32F100V8 \
   || defined STL_STM32F101C8 || defined STL_STM32F101R8 || defined STL_STM32F101T8 \
   || defined STL_STM32F101V8 || defined STL_STM32F102C8 || defined STL_STM32F102R8 \
   || defined STL_STM32F103C8 || defined STL_STM32F103R8 || defined STL_STM32F103T8 \
   || defined STL_STM32F103V8
   /* 64 Kbytes of Flash */
   #define FLASH_MEM_SIZE 65536U

#elif defined STL_STM32F071CB || defined STL_STM32F071RB || defined STL_STM32F071VB \
   || defined STL_STM32F072CB || defined STL_STM32F072RB || defined STL_STM32F072VB \
   || defined STL_STM32F105RB || defined STL_STM32F105VB || defined STL_STM32F107RB \
   || defined STL_STM32F107VB || defined STL_STM32L100RB || defined STL_STM32L151CB \
   || defined STL_STM32L151RB || defined STL_STM32L151VB || defined STL_STM32L152CB \
   || defined STL_STM32L152RB || defined STL_STM32L152VB || defined STL_STM32F100CB \
   || defined STL_STM32F100RB || defined STL_STM32F100VB || defined STL_STM32F101CB \
   || defined STL_STM32F101RB || defined STL_STM32F101TB || defined STL_STM32F101VB \
   || defined STL_STM32F102CB || defined STL_STM32F102RB || defined STL_STM32F103CB \
   || defined STL_STM32F103RB || defined STL_STM32F103TB || defined STL_STM32F103VB \
   || defined STL_STM32F401CB || defined STL_STM32F401RB || defined STL_STM32F401VB
   /* 128 KBytes of Flash */
   #define FLASH_MEM_SIZE 131072U

#elif defined STL_STM32F100RC || defined STL_STM32F100VC || defined STL_STM32F100ZC \
   || defined STL_STM32F105RC || defined STL_STM32F105VC || defined STL_STM32F107RC \
   || defined STL_STM32F107VC || defined STL_STM32L100RC || defined STL_STM32L151CC \
   || defined STL_STM32L151RC || defined STL_STM32L151UC || defined STL_STM32L152CC \
   || defined STL_STM32L152RC || defined STL_STM32L152VC || defined STL_STM32L151QC \
   || defined STL_STM32L151ZC || defined STL_STM32L152QC || defined STL_STM32L152ZC \
   || defined STL_STM32L162RC || defined STL_STM32L162VC || defined STL_STM32F101RC \
   || defined STL_STM32F101VC || defined STL_STM32F101ZC || defined STL_STM32F103RC \
   || defined STL_STM32F103VC || defined STL_STM32F103ZC || defined STL_STM32F401CC \
   || defined STL_STM32F401RC || defined STL_STM32F401VC
   /* 256 Kbytes of Flash */
   #define FLASH_MEM_SIZE 262144U

#elif defined STL_STM32L151QD || defined STL_STM32L151RD || defined STL_STM32L151VD || defined STL_STM32L151ZD \
   || defined STL_STM32L152QD || defined STL_STM32L152RD || defined STL_STM32L152VD || defined STL_STM32L152ZD \
   || defined STL_STM32F100RD || defined STL_STM32F100VD || defined STL_STM32F100ZD || defined STL_STM32L162QD \
   || defined STL_STM32L162RD || defined STL_STM32L162VD || defined STL_STM32L162ZD || defined STL_STM32F101RD \
   || defined STL_STM32F101VD || defined STL_STM32F101ZD || defined STL_STM32F103RD || defined STL_STM32F103VD \
   || defined STL_STM32F103ZD || defined STL_STM32F401CD || defined STL_STM32F401RD || defined STL_STM32F401VD
   /* 384 Kbytes of Flash */
   #define FLASH_MEM_SIZE 393216U
   
#elif defined STL_STM32F100RE || defined STL_STM32F100VE || defined STL_STM32F100ZE \
   || defined STL_STM32F101RE || defined STL_STM32F101VE || defined STL_STM32F101ZE \
   || defined STL_STM32F103RE || defined STL_STM32F103VE || defined STL_STM32F103ZE \
   || defined STL_STM32F417VE || defined STL_STM32F417ZE || defined STL_STM32F417IE \
   || defined STL_STM32F405OE || defined STL_STM32F407VE || defined STL_STM32F407ZE \
   || defined STL_STM32F407IE || defined STL_STM32F401CE || defined STL_STM32F401RE \
   || defined STL_STM32F401VE
   /* 512 Kbytes of Flash */
   #define FLASH_MEM_SIZE 524288U
   
#elif defined STL_STM32F103RF || defined STL_STM32F103VF || defined STL_STM32F103ZF \
   || defined STL_STM32F101RF || defined STL_STM32F101VF || defined STL_STM32F101ZF
   /* 768 Kbytes of Flash */
   #define FLASH_MEM_SIZE 786432U
   
#elif defined STL_STM32F103RG || defined STL_STM32F103VG || defined STL_STM32F103ZG \
   || defined STL_STM32F101RG || defined STL_STM32F101VG || defined STL_STM32F101ZG \
   || defined STL_STM32F427IG || defined STL_STM32F427VG || defined STL_STM32F427ZG \
   || defined STL_STM32F429BG || defined STL_STM32F429IG || defined STL_STM32F429NG \
   || defined STL_STM32F429VG || defined STL_STM32F429ZG || defined STL_STM32F415RG \
   || defined STL_STM32F415VG || defined STL_STM32F415ZG || defined STL_STM32F415OG \
   || defined STL_STM32F417VG || defined STL_STM32F417IG || defined STL_STM32F417ZG \
   || defined STL_STM32F405RG || defined STL_STM32F405VG || defined STL_STM32F405ZG \
   || defined STL_STM32F405OG || defined STL_STM32F407VG || defined STL_STM32F407IG \
   || defined STL_STM32F407ZG || defined STL_STM32F437VG || defined STL_STM32F437ZG \
   || defined STL_STM32F437IG || defined STL_STM32F439VG || defined STL_STM32F439ZG \
   || defined STL_STM32F439IG || defined STL_STM32F439BG || defined STL_STM32F439NG
   /* 1 Mbytes of Flash */
   #define FLASH_MEM_SIZE 1048576U

   
#elif defined STL_STM32F427II || defined STL_STM32F427VI || defined STL_STM32F427ZI \
   || defined STL_STM32F429BI || defined STL_STM32F429II || defined STL_STM32F429NI \
   || defined STL_STM32F429VI || defined STL_STM32F429ZI || defined STL_STM32F437VI \
   || defined STL_STM32F437ZI || defined STL_STM32F437II || defined STL_STM32F437AI \
   || defined STL_STM32F439VI || defined STL_STM32F439ZI || defined STL_STM32F439II \
   || defined STL_STM32F439BI || defined STL_STM32F439NI || defined STL_STM32F439AI
   /* 2 Mbytes of Flash */
   #define FLASH_MEM_SIZE 2097152U
#else
  #error "Wrong or no part number defined"
#endif /* defined STL_STM32F030F4 */

/* Preprocessor checks whether FLASH_MEM_SIZE/FLASH_SLICE_SIZE is an integer value  */
#if ((FLASH_MEM_SIZE % FLASH_SLICE_SIZE) == 0LU )
   #define FLASH_NUMBER_OF_SLICES   (FLASH_MEM_SIZE/FLASH_SLICE_SIZE)
   #define FLASH_FIRST_SLICE_ID   0LU
   #define FLASH_LAST_SLICE_ID    ((FLASH_NUMBER_OF_SLICES-1LU) + FLASH_FIRST_SLICE_ID)
#else
   #error "The total number of Flash Slices is not an integer value"
#endif

/* Flash Signatures Base ADDRESS
 *  
 */
#define FLASH_SIGN_BASE_ADDR ((FLASH_BASE_ADDRESS+FLASH_MEM_SIZE)-((FLASH_MEM_SIZE/FLASH_SLICE_SIZE)*4U))
   /* The number of words (1 word = 4 bytes) in a slice has to be multiple of 16 */
#if ((FLASH_SLICE_SIZE/(16*4)) * (16*4)) != FLASH_SLICE_SIZE
   #error The number of words in a slice must be multiple of 16
#endif

/* Different sets of HW CRC registers, depending on the PN  */
/* F031, F051, F071 and F072 have CRC_POL register (configurable polynomial value) */
#if   defined STL_STM32F031C4 || defined STL_STM32F031C6 || defined STL_STM32F031F4 || defined STL_STM32F031F6 \
   || defined STL_STM32F031G4 || defined STL_STM32F031G6 || defined STL_STM32F031K4 || defined STL_STM32F031K6 \
   || defined STL_STM32F051C4 || defined STL_STM32F051C6 || defined STL_STM32F051C8 || defined STL_STM32F051K4 \
   || defined STL_STM32F051K6 || defined STL_STM32F051K8 || defined STL_STM32F051R4 || defined STL_STM32F051R6 \
   || defined STL_STM32F051R8 || defined STL_STM32F071CB || defined STL_STM32F071RB || defined STL_STM32F071V8 \
   || defined STL_STM32F071VB || defined STL_STM32F072C8 || defined STL_STM32F072CB || defined STL_STM32F072R8 \
   || defined STL_STM32F072RB || defined STL_STM32F072V8 || defined STL_STM32F072VB
   #define HW_CRC_TYPE_EXT_WITH_POLY

/* F030 doesn't have CRC_POL register */
#elif defined STL_STM32F030F4 || defined STL_STM32F030C6 || \
      defined STL_STM32F030K6 || defined STL_STM32F030C8 || \
      defined STL_STM32F030R8
   #define HW_CRC_TYPE_EXT_WITHOUT_POLY

/* STL_STM32F1, STL_STM32L1 and STL_STM32F4 don't have CRC_POL, nor CRC_INIT. Moreover, CRC_CR has just reset functionality.*/
#else
   #define HW_CRC_TYPE_FIX_POLY_ONLY_DR   
#endif 


/* the base address of HW_CRC peripheral is a parameter. And the same for registers' offsets.*/
#define HW_CRC_BASE_ADDRESS 0x40023000U
#define HW_CRC_DR_ADDRESS (HW_CRC_BASE_ADDRESS + 0x0000U)

#define CRC_STL_INIT                       ((stl_u32)0xFFFFFFFFU)
#define CRC_STL_IDR_INIT                   ((stl_u32)0x00U)
/* The following value of CRC_CR is required in order to obtain
 * a CRC IEEE compliant. The meaning is : bit-reverse input data by word ; bit-reverse output data.
 * Also a reset of HW CRC is performed.
 */
#define CRC_STL_CR_INIT                    ((stl_u32)0x000000E1U)
#define CRC_STL_RESET                      ((stl_u32)0x00000001U)

#define CRC_STL_POL_INIT                   ((stl_u32)0x04C11DB7U)
#endif /*FRSTL_FLASH_CONFIG_H*/
