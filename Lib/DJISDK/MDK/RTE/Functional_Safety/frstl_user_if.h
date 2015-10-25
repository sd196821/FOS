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
 * \file  frstl_user_if.h
 * \brief Enumeration of test segments, common definitions, and top-level APIs.
 * User application shall include this header to access the STL library
 */

#ifndef FRSTLM4_USER_IF_H
#define FRSTLM4_USER_IF_H


/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* DEFINES, MACROS AND STATIC VARIABLES                                       */
/*----------------------------------------------------------------------------*/

/*! Indexes of the test segments. */
typedef enum {
   FRSTLM4_TEST_LIST_HEAD = -1,

   FRSTLM4_TEST_ID_0,   /* frstl_armcm4__gp_regs() */
   FRSTLM4_TEST_ID_1,   /* frstl_armcm4__mul64() */
   FRSTLM4_TEST_ID_2,   /* frstl_armcm4__mla() */
   FRSTLM4_TEST_ID_3,   /* frstl_armcm4__dp_arithm() */
   FRSTLM4_TEST_ID_4,   /* frstl_armcm4__dp_logic() */
   FRSTLM4_TEST_ID_5,   /* frstl_armcm4__dp_misc() */
   FRSTLM4_TEST_ID_6,   /* frstl_armcm4__div() */
   FRSTLM4_TEST_ID_7,   /* frstl_armcm4__bshft() */
   FRSTLM4_TEST_ID_8,   /* frstl_armcm4__dsp_mac() */
   FRSTLM4_TEST_ID_9,   /* frstl_armcm4__dps_sgn() */
   FRSTLM4_TEST_ID_10,  /* frstl_armcm4__dsp_usgn() */
   FRSTLM4_TEST_ID_11,  /* frstl_armcm4__dsp_sat() */
   FRSTLM4_TEST_ID_12,  /* frstl_armcm4__dsp_misc() */
   FRSTLM4_TEST_ID_13,  /* frstl_armcm4__lsu16() */
   FRSTLM4_TEST_ID_14,  /* frstl_armcm4__lsu32() */
   FRSTLM4_TEST_ID_15,  /* frstl_armcm4__ctrl16() */
   FRSTLM4_TEST_ID_16,  /* frstl_armcm4__ctrl32() */
   FRSTLM4_TEST_ID_17,  /* frstl_armcm4__special() */
#if FRSTLM4_FPU_TEST_ENABLE == 1
   FRSTLM4_TEST_ID_18,  /* frstl_armcm4__fpu_lsu() */
   FRSTLM4_TEST_ID_19,  /* frstl_armcm4__fpu_rbk() */
   FRSTLM4_TEST_ID_20,  /* frstl_armcm4__fpu_dp_mul() */
   FRSTLM4_TEST_ID_21,  /* frstl_armcm4__fpu_dp_add1() */
   FRSTLM4_TEST_ID_22,  /* frstl_armcm4__fpu_dp_add2() */
   FRSTLM4_TEST_ID_23,  /* frstl_armcm4__fpu_dp_add3() */
   FRSTLM4_TEST_ID_24,  /* frstl_armcm4__fpu_dp_add4() */
   FRSTLM4_TEST_ID_25,  /* frstl_armcm4__fpu_dp_rnd() */
   FRSTLM4_TEST_ID_26,  /* frstl_armcm4__fpu_dp_abs() */
   FRSTLM4_TEST_ID_27,  /* frstl_armcm4__fpu_dp_cnv() */
   FRSTLM4_TEST_ID_28,  /* frstl_armcm4__fpu_dp_div() */
   FRSTLM4_TEST_ID_29,  /* frstl_armcm4__fpu_dec() */
#  if FRSTLM4_FPU_EXCP_TEST_ENABLE == 1
   FRSTLM4_TEST_ID_30,  /* frstl_armcm4__fpu_exc() */
#  endif /* FRSTLM4_FPU_EXCP_TEST_ENABLE */
#endif /* FRSTLM4_FPU_TEST_ENABLE */   
   
   FRSTLM4_TEST_LIST_TAIL
} ids;

/*! Index of the first test segment */
#define FRSTLM4_FIRST_TEST_ID   (FRSTLM4_TEST_LIST_HEAD + 1)
/*! Index of the last test segment */
#define FRSTLM4_LAST_TEST_ID    (FRSTLM4_TEST_LIST_TAIL - 1)

/*! Boolean type definition */
typedef enum {
   STL_FALSE = (int)0xABCDABCD,
   STL_TRUE = (int)0x75601522
} stl_bool;

/*! Encoding for test succesful */
#define FRSTLM4_PASSED_RESULT 0x78A5C3E1
/*! Encoding for test failed */
#define FRSTLM4_FAILED_RESULT ~FRSTLM4_PASSED_RESULT

/*! Test module result definition */
typedef enum {
   e_OnlineTestResult_PASSED = FRSTLM4_PASSED_RESULT,
   e_OnlineTestResult_FAILED = FRSTLM4_FAILED_RESULT
} e_OnlineTestResult_t;


/*----------------------------------------------------------------------------*/
/* BODY                                                                       */
/*----------------------------------------------------------------------------*/

/*!
 * This is the entry point from the main application, and it is used to schedule
 * the execution of a test segment.
 *
 * \param u8_TestSegmentID - The test identifier identifies the test to be executed
 * \return An error code: e_OnlineTestResult_FAILED in case of failure,
 * e_OnlineTestResult_PASSED otherwise
 */
e_OnlineTestResult_t frstl_run_test(const unsigned char u8_TestSegmentID);

/*!
 * Resets the STL tracking variable
 */
void frstl_reset(void);

/*!
 * Registers the stl_run_ok status signal
 *
 * \param stl_run_ok - A double pointer that is used to return the address of
 * the run ok flag. This tells whether the STL has completed or not a run cycle
 * \return An error code: e_OnlineTestResult_FAILED in case of failure,
 * e_OnlineTestResult_PASSED otherwise
 */
e_OnlineTestResult_t frstl_register(const stl_bool** stl_run_ok);

/*!
 * This function schedules a test segment for execution, and checks the test 
 * segment to return the expected signature. It then sets the return value 
 * accordingly
 *
 * \param u8_TestSegmentID - The test identifier
 * \return An error code: e_OnlineTestResult_FAILED in case of failure,
 * e_OnlineTestResult_PASSED otherwise
 */
e_OnlineTestResult_t frstl_run_and_update(const unsigned char u8_TestSegmentID);

#endif /*FRSTLM4_USER_IF_H*/
