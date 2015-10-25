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
 * \file  frstl_user_api.h
 * \brief user application shall include this header
 *
 */
#ifndef FRSTL_USER_API_H
#define FRSTL_USER_API_H

#include <frstl_peripherals_PN.h>


/*-----------------------------------------------------------------------------------------------
 *-----                                                                                    ------
 *-----                                      COMMON PART                                   ------
 *-----                                                                                    ------
 *---------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------
 -----  definition of stl bool type
 -----------------------------------------------------------------------------------------------*/
/* Definition of STL boolean values
 * 
 */

#define STL_FALSE_DEF ((int)0xABCDABCDU)
#define STL_TRUE_DEF ((int)0x75601522U)

typedef enum
{
  STL_STM32_FALSE = STL_FALSE_DEF,
  STL_STM32_TRUE = STL_TRUE_DEF
} stl_bool_t;

/*-----------------------------------------------------------------------------------------------
 -----     Numbers for encoding test results
 -----------------------------------------------------------------------------------------------*/
/* 
 */
#define PASSED_RESULT_DEF 0x78A5C3E1
#define FAILED_RESULT_DEF ((int)(~((unsigned int)PASSED_RESULT_DEF)))

/*-----------------------------------------------------------------------------------------------
 -----  definition of online test module results
 -----------------------------------------------------------------------------------------------*/
/*
 */
typedef enum {
    e_OnlineTestResult_SUCCESS = PASSED_RESULT_DEF,
    e_OnlineTestResult_COREFAULT = FAILED_RESULT_DEF,
    e_OnlineTestResult_PERIFAULT = (FAILED_RESULT_DEF + 1),
    e_OnlineTestResult_FLASHFAULT = (FAILED_RESULT_DEF + 2),
    e_OnlineTestResult_SRAMFAULT = (FAILED_RESULT_DEF + 3),
    e_OnlineTestResult_NULL = (FAILED_RESULT_DEF + 4),
    e_OnlineTestResult_INVALID = (FAILED_RESULT_DEF + 5)
} stl_test_result_t;


/* Definition of a macro to avoid storing additional information about failing tests 
 * 
 */
#define STL_NO_ERRINFO (~(0UL))

/*-----------------------------------------------------------------------------------------------
 *-----                                                                                    ------
 *-----                                  END OF COMMON PART                                ------
 *-----                                                                                    ------
 *---------------------------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------------------------
 *-----                                                                                     ------
 *-----                                      FLASH PART                                     ------
 *-----                                                                                     ------
 *----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------
 *-----  definition of flash area type:
 *-----
 *-----  this is the descriptor of a single memory area to be tested
 *
 * 
 *-----------------------------------------------------------------------------------------------*/
typedef struct stl_flash_area_t {
   unsigned long start_slice;
   /*start memory slice*/
   unsigned long num_slices;
   /*number of consecutive memory slices after the start one*/
   struct stl_flash_area_t *next;
   /*pointer to the next flash area*/
} stl_flash_area_t;

/*-----------------------------------------------------------------------------------------------
 *-----  definition of flash_syncpoint type:
 *-----
 *-----  this is the descriptor of the protection mechanism used by the flash test during
 *-----  the execution of the test of single memory slices. This allows the end user to
 *-----  define his locking/unlocking routines in order to perform anything is required
 *-----  before/after running the single tests (e.g. routines to save/restore the status of 
 *-----  the CRC32 HW unit)
 *
 * 
 *-----------------------------------------------------------------------------------------------*/
typedef struct stl_flash_syncpoint_t {
   void *lock_param;
   /*input parameter of the lock_crc callback*/
   void *unlock_param;
   /*input parameter of the unlock_crc callback*/
   stl_test_result_t ( *flash_lock)(void *lock_param);
   /*callback to perform any required routine before testing a
    *one or more flash slices */
   stl_test_result_t ( *flash_unlock)(void *unlock_param);
   /*callback to perform any required routine after the test 
    *of one or more flash slices */
} stl_flash_syncpoint_t;

 /*-----------------------------------------------------------------------------------------------
 *-----                                                                                     ------
 *-----                                   END OF FLASH PART                                 ------
 *-----                                                                                     ------
 *----------------------------------------------------------------------------------------------*/

 /*------------------------------------------------------------------------------------------------
 *-----                                                                                      ------
 *-----                                      SRAM PART                                       ------
 *-----                                                                                      ------
 *-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------
 *-----  definition of sram_syncpoint type:
 *-----
 *-----  this is the descriptor of the protection mechanism used by the sram test during
 *-----  the execution of the test of single memory slices. This allows the end user to
 *-----  define his locking/unlocking routines in order to perform anything is required
 *-----  before/after running the single tests (e.g. routines to save/restore the status of 
 *-----  the CRC32 HW unit)
 *
 * 
 *-----------------------------------------------------------------------------------------------*/
typedef struct stl_sram_syncpoint_t {
   void *lock_param;
   /*input parameter of the sram_lock callback*/
   void *unlock_param;
   /*input parameter of the sram_unlock callback*/
   stl_test_result_t (*sram_lock)(void *lock_param);
   /*callback to perform any required routine before testing
    *one sram slice */
   stl_test_result_t (*sram_unlock)(void *unlock_param);
   /*callback to perform any required routine after the test of 
    *one sram slices */
} stl_sram_syncpoint_t;

/*-----------------------------------------------------------------------------------------------
 *-----  definition of sram area type:
 *-----
 *-----  this is the descriptor of a single group of slices to be tested
 * 
 * 
 *-----------------------------------------------------------------------------------------------*/
typedef struct stl_sram_area_t {
   unsigned long start_slice;
   /*start memory slice*/
   unsigned long num_slices;
   /*number of consecutive memory slices after the start one*/
   struct stl_sram_area_t *next;
   /*pointer to the next sram area*/
} stl_sram_area_t;

 /*------------------------------------------------------------------------------------------------
 *-----                                                                                      ------
 *-----                                    END OF SRAM PART                                  ------
 *-----                                                                                      ------
 *-----------------------------------------------------------------------------------------------*/


 /*------------------------------------------------------------------------------------------------
 *-----                                                                                      ------
 *-----                                  PERIPHERALS PART                                    ------
 *-----                                                                                      ------
 *-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------
 *-----  definition of periph_syncpoint type:
 *-----
 *-----  this is the descriptor of the protection mechanism used by the peripheral test. 
 *-----  This allows the end user to define his locking/unlocking routines in order to perform 
 *-----  anything is required before/after running the single tests,
 *
 * 
 *-----------------------------------------------------------------------------------------------*/

typedef struct stl_periph_syncpoint_t {
   /* input parameter of the sram_lock callback */
   void *lock_param;
   /* input parameter of the sram_unlock callback */
   void *unlock_param;
   /* callback to perform any required routine before updating
    * the peripheral configuration register */
   stl_test_result_t (*periph_lock)(void *lock_param);
   /* callback to perform any required routine after the test of 
    * one sram slices */
   stl_test_result_t (*periph_unlock)(void *unlock_param);
} stl_periph_syncpoint_t;


/* 
 * Function name : frstl_stm32_periph_lock
 *
 * This method shall :
 * 1) check stl_status to be == stl_sync_done , otherwise return  e_OnlineTestResult_INVALID
 * 2) call underlying frstl_periph method to lock the peripherals, returning the exit value of this one.
 *
 * @param none
 *
 * @return The function returns e_OnlineTestResult_SUCCESS if it completes successfully,
 *         otherwise it returns a proper error code.
 *
 * 
 */
stl_test_result_t frstl_stm32_periph_lock(void);


/* 
 * Function name : frstl_stm32_periph_update_unlock
 *
 * @param reg_id : the register to be updated.
 *
 * @return The function returns e_OnlineTestResult_SUCCESS if it completes successfully,
 *         otherwise it returns a proper error code.
 *
 * 
 */
stl_test_result_t frstl_stm32_periph_update_unlock(stl_prot_registers_t reg_id);
 
 /*------------------------------------------------------------------------------------------------
 *-----                                                                                      ------
 *-----                             END OF PERIPHERALS PART                                  ------
 *-----                                                                                      ------
 *-----------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------------
 -----  COMMON Public Functions definitions
 -----------------------------------------------------------------------------------------------*/

/*
 * Function Name: frstl_stm32_register
 *
 * This function makes the user pointers to point to some internal STL variables. In this way
 *    the user can know whether that all the test segments of the STL have successfully run to completion or not.
 *
 * @param num_dti : the number of DTIs after which "stl_complete" is expected to be set to true. 
 *                  It must be set to be non-negative.
 *
 * @param stl_part_done_p: double pointer used to retrieve the address of the variable signaling that a part is done.
 *                         The double pointer cannot be NULL.
 *
 * @param stl_completed_p: double pointer used to retrieve the address of the variable signaling that all tests are done.
 *                         The double pointer cannot be NULL. 
 * 
 * @return the function e_OnlineTestResult_SUCCESS if it is successful, 
 *         otherwise it returns a proper error code.
 * 
 * 
 */
stl_test_result_t frstl_stm32_register(unsigned long num_dti, const stl_bool_t **stl_part_done_p, const stl_bool_t **stl_completed_p);


/*
 * Function Name: frstl_stm32_resync
 * 
 * Description ... for implementer see SRS
 * 
 * @param: none
 * 
 * @return the function returns e_OnlineTestResult_SUCCESS if it is successful,
 *         otherwise it returns e_OnlineTestResult_INVALID.
 *
 * 
 */
stl_test_result_t frstl_stm32_resync(void);


/*
 * Function Name: frstl_stm_load_lists
 *
 * description ... for implementer, see SRS
 * 
 * @param  f_list_head : pointer to list of flash area descriptors. It cannot be NULL.
 * 
 * @param  s_list_head : pointer to list of sram sarea descriptors. It cannot be NULL.
 * 
 * @return   the function returns e_OnlineTestResult_SUCCESS if it is successful,      
 *           otherwise it returns a proper error code.
 *
 * 
 */
stl_test_result_t frstl_stm32_load_lists(stl_flash_area_t *f_list_head, stl_sram_area_t *s_list_head);


/*
 * Function Name: frstl_stm32_register_sync
 *
 * description ... for implementer, see SRS
 * 
 * @param  f_sync_struct : pointer to synchronization mechanism for Flash testing. It can be NULL.
 * 
 * @param  s_sync_struct : pointer to synchronization mechanism for SRAM testing. It can be NULL.
 *
 * @param  p_sync_struct : pointer to synchronization mechanism for peripheral testing. It can be NULL.
 * 
 * @return   the function returns e_OnlineTestResult_SUCCESS if it is successful,
 *           otherwise it returns a proper error code
 *
 * 
 */
stl_test_result_t frstl_stm32_register_sync(stl_flash_syncpoint_t *f_sync_struct, stl_sram_syncpoint_t *s_sync_struct,
                                      stl_periph_syncpoint_t *p_sync_struct);

/*
 * Function Name: frstl_stm32_run_test
 *
 * This function calls an appropriate STL test segment. Implementation... see SRS. 
 *
 * @param errinfo (output param): this shall eventually be filled with additional specific
 *                                information about error conditions.
 * 
 * @return The function returns e_OnlineTestResult_SUCCESS if it is successful,
 *         otherwise it returns a proper error code.
 * 
 * 
 */
stl_test_result_t frstl_stm32_run_test(unsigned long *errinfo);

#endif /* FRSTL_USER_API_H */
