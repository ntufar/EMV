/* $Id: librarian.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/**
 * @file
 * This file provides information on initializing and destroying library and
 * cipher contexts, as well as outlining FIPS-validated functionality.
 */

#ifndef _LIBRARIAN_H_
#define _LIBRARIAN_H_

#ifndef NO_TIME_H
#include <time.h>
#endif

#ifndef CRYPTOC_ME
#include "r_com.h"
#include "r_res.h"
#include "r_lib.h"
#include "r_mem.h"
#include "r_rand.h"
#include "r_skey.h"
#include "cryp_ops.h"
#include "cryp_mod.h"
#ifndef NO_DSA
#include "dsa.h"
#endif /* NO_DSA */
#else
#include "cryptocme.h"
#endif

#include "cspxport.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define CRYPTOC_ME_VERSION_NUMBER_1_7_2    0x1720
#define CRYPTOC_ME_VERSION_NUMBER_1_9_0    0x1900
#define CRYPTOC_ME_VERSION_NUMBER_2_0_0    0x2000

/* The newest version of the library vectors method table is ... */
#define LIBRARY_VECTORS_T       ts_lock_imported_functions
/* This is the latest library vectors declared in librarian.c */
#define NEWEST_LIBRARY_VECTORS  librarian_lock_method_vectors

#ifndef RET_CHECK
#define RET_CHECK if(ret) goto err;
#endif


#ifndef CHECK
#define CHECK(r, str, l)        \
        if (r != 0) {                   \
                return(r);                      \
        }
#endif

#ifndef CHECK_ERR
#define CHECK_ERR(r, str, l)    \
        if (r != 0) {                   \
                goto err;               \
        }
#endif


#define R_SP_CHECK_LIBRARY_LOAD                 \
        int ret = 0;                            \
        LIBRARY_VECTORS_T *lib_ptr;             \
	\
        ret = R_CR_LOCAL_startup();             \
        if(ret) return(ret);                    \
        lib_ptr = CRYPTOC_LOCAL_fetch_local_library_vectors();\
	if (lib_ptr == NULL) return(R_ERROR_MODULE_LOAD_FAILED);

#define R_SP_CHECK_LIBRARY_LOAD_NO_RET      \
        LIBRARY_VECTORS_T *lib_ptr;         \
	\
        R_CR_LOCAL_startup();               \
        lib_ptr = CRYPTOC_LOCAL_fetch_local_library_vectors();


#define R_SP_CHECK_LIBRARY_LOAD_RET_CHAR        \
        LIBRARY_VECTORS_T *lib_ptr;             \
        int ret = 0;                            \
        ret = R_CR_LOCAL_startup();             \
        if(ret) return("FAILED LIBRARY LOAD");  \
        lib_ptr = CRYPTOC_LOCAL_fetch_local_version_library_vectors();




/**
 *  This define is placed in the client application before the first
 *  <tt>CRYPTOC_FIPS140</tt> or <tt>CRYPTOC_ME_FIPS140</tt> call is made. It
 *  enables a local library to operate as the default when the FIPS140 shared
 *  library is unavailable.
 *
 *  @note This operation increases the client application's code size and
 *        should not be used when seeking to minimize code footprint.
 */
ts_imported_functions *CRYPTOC_LOCAL_get_post_init_export_list();
ts_lock_imported_functions *CRYPTOC_LOCAL_get_lock_post_init_export_list();

LIBRARY_VECTORS_T* CRYPTOC_LOCAL_fetch_local_library_vectors();

void CRYPTOC_LOCAL_set_method_vectors(ts_imported_functions *new_vectors);
void CRYPTOC_LOCAL_set_version_method_vectors(void *new_vectors, int version);
#define CRYPTOC_FIPS140_USE_LOCAL_DEFAULT_LIB
#define CRYPTOC_FIPS140_USE_LOCAL_DEFAULT_LIB_1_7_2  \
        {                                \
        CRYPTOC_LOCAL_set_method_vectors(CRYPTOC_LOCAL_get_post_init_export_list()); \
        }


/**
 * @defgroup FIPS140_ME_LIBRARY_FUNC Library Operation Functions
 * This section details the functions that are used to open the library
 * and cryptographic contexts for #FIPS140_MODE and #NON_FIPS140_MODE cryptographic
 * operations.
 * @ingroup FIPS140_FUNCS
 * @{
 */

/*
 *  Opens a library and a cryptographic context depending on whether
 *  the library is in #FIPS140_MODE or #NON_FIPS140_MODE.
 *  If in #FIPS140_MODE, a library context that contains only
 *  FIPS140 routines is created. If in #NON_FIPS140_MODE, the default
 *  Crypto-C ME library context is created.
 */
int CRYPTOC_ME_FIPS140_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);

/*
 *  Opens a library context that contains only FIPS140 routines.
 *  If no other libraries are open and the current mode is
 *  #NON_FIPS140_MODE, converts system to #FIPS140_MODE after
 *  running the necessary transition tests. Otherwise returns an error.
 */
int CRYPTOC_ME_FIPS140_fips140_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);

/*
 *  Opens the default Crypto-C ME library context. If no other libraries are
 *  open and the current mode is #FIPS140_MODE, converts system to
 *  #NON_FIPS140_MODE after performing the necessary transition tasks.
 *  Otherwise returns an error.
 */
int CRYPTOC_ME_FIPS140_non_fips140_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);

/*
 *      Releases any library and cryptographic contexts that were allocated by
 *      an <tt>R_CR_SP</tt> call.
 */
void CRYPTOC_ME_FIPS140_library_free(R_LIB_CTX *lib_ctx, R_CR_CTX *ctx);

/*
 *     Allows the calling application to control aspects of how the FIPS140
 *     shared library is to loaded.
 */
int CRYPTOC_ME_FIPS140_library_set_info(R_LIB_CTX *lib_ctx, int info_id, void *info);


/**
 * Loads the FIPS140 shared library into the current execution space.
 *
 * @param filename [In]      The filename of the shared library to be
 *                           loaded. This can be set by the application by
 *                           calling CRYPTOC_ME_FIPS140_library_set_info() using
 *                           #CRYPTOC_ME_FIPS140_INFO_ID_SHLIB_LOC.
 * @param cb_arg   [In/Out]  The user-defined callback argument. This can be
 *                           set by the application by calling
 *                           CRYPTOC_ME_FIPS140_library_set_info() using
 *                           #CRYPTOC_ME_FIPS140_INFO_ID_LOAD_CB_ARG.
 * @param os_err   [Out]     The OS specific error set if it fails to load the
 *                           shared library. The setting of this return
 *                           parameter is optional.
 *
 *
 * @return The OS specific handle for the loaded shared library, or
 * <tt>NULL</tt> on error.
 *
 * @note The library must be loaded in such a way that it maintains symbol
 * isolation from the existing execution environment. For example, if
 * <tt>dlopen()</tt> is used then the load argument <tt>RTLD_GLOBAL</tt> must not
 * be used.
 *
 */

typedef void *(*CRYPTOC_ME_FIPS140_LOAD_CB_T)(char *filename, void *cb_arg, int *os_err);


/**
 * @} FIPS140_ME_LIBRARY_FUNC
 */

/**
 * @defgroup FIPS140_INFO_ID  FIPS140 Library Identifiers
 * This section details the defines used in the setting of data against the
 * FIPS140 library object.
 * The following table details the data types to pass into <i>info_id</i> when
 * calling CRYPTOC_ME_FIPS140_library_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>info_id Data Type</b></td>
 * </tr><tr>
 *     <td>#CRYPTOC_ME_FIPS140_INFO_ID_LOAD_CB</td>
 *     <td>#CRYPTOC_ME_FIPS140_LOAD_CB_T</td>
 * </tr><tr>
 *     <td>#CRYPTOC_ME_FIPS140_INFO_ID_LOAD_CB_ARG</td>
 *     <td><tt>void *</tt></td>
 * </tr><tr>
 *     <td>#CRYPTOC_ME_FIPS140_INFO_ID_SHLIB_LOC</td>
 *     <td><tt>char *</tt></td>
 * </tr><tr>
 *     <td>#CRYPTOC_ME_FIPS140_INFO_ID_ENTROPY_LOC</td>
 *     <td><tt>char *</tt></td>
 * </tr><tr>

 * </tr></table>
 * @br
 * @ingroup FIPS140_API_GROUP
 * @{
 */
/**
 * A FIPS140 library identifier which indicates the FIPS140 shared library load
 * function.
 */
#define CRYPTOC_ME_FIPS140_INFO_ID_LOAD_CB          1
/**
 * A FIPS140 library identifier which indicates the FIPS140 shared library load
 * function callback argument.
 */
#define CRYPTOC_ME_FIPS140_INFO_ID_LOAD_CB_ARG      2
/**
 * A FIPS140 library identifier which indicates the file location of the FIPS140
 * shared library.
 */
#define CRYPTOC_ME_FIPS140_INFO_ID_SHLIB_LOC        3
/**
 * A FIPS140 library identifier which indicates the file location of the FIPS140
 * shared library entropy file.
 */
#define CRYPTOC_ME_FIPS140_INFO_ID_ENTROPY_LOC      4


/**
 * @} FIPS140_INFO_ID
 */

/*
 * @defgroup FIPS140_DSA_GROUP FIPS140 DSA Parameter Generation
 * This section details the API to the FIPS140-tested DSA parameter generator.
 *
 * @ingroup CRYPTOC_ME_GROUP
 * @{
 */

#ifndef NO_DSA
/*
 * Generates a set of DSA parameters per FIPS186-2
 */
DSA* CRYPTOC_ME_FIPS140_dsa_generate_parameters(int bits, unsigned char *seed,
		int seed_len, int *counter_ret, unsigned long *h_ret,
		void (*callback)(int,int,char *),char *cb_arg);

/*
 * Frees the DSA parameters structure that was previously returned
 *      by a call to dsa_generate_parameters
 */
void CRYPTOC_ME_FIPS140_dsa_free(DSA *dsa);

/*
 * Checks a value to see whether is it prime.
 */
int CRYPTOC_ME_FIPS140_dsa_is_prime(BIGNUM *q,void (*callback)(int,int,char *),
						char *cb_arg);

#endif /* NO_DSA */

/*
 * @} FIPS140_DSA_GROUP
 */


/**
 * @defgroup FIPS140_OPERATING_MODES FIPS140 Operating Modes
 * This section details the possible FIPS140 operating modes, and outlines
 * the functions used to detect and modify the FIPS140 operating mode.
 * @ingroup FIPS140_API_GROUP
 * @{
 */



/**
 * Indicates the FIPS140 operating mode.
 * The following table details the usage of this type.<br>
 *
 * @note This typedef deprecates <tt>operating_mode_t</tt>
 *
 * <table><tr>
 * <td><b>FIPS140 Operating Mode</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>#DISABLED_MODE</td>
 * <td>No new library contexts may be created. No transition to
 * any other mode is possible.</td>
 * </tr><tr>
 * <td>#FIPS140_MODE</td>
 * <td>#FIPS140_MODE library contexts may be initialized.
 * Another mode may be entered once they are closed.</td>
 * </tr><tr>
 * <td>#FIPS140_SSL_MODE</td>
 * <td>#FIPS140_SSL_MODE library contexts may be initialized.
 * Another mode may be entered once they are closed.</td>
 * </tr><tr>
 * <td>#NON_FIPS140_MODE</td>
 * <td>#NON_FIPS140_MODE library contexts may be initialized.
 * Another mode may be entered once they are closed.</td>
 * </tr></table>
 */

typedef int R_FIPS140_OPERATING_MODE_T;
typedef R_FIPS140_OPERATING_MODE_T operating_mode_t;  

/**
 * Indicates that the FIPS140 library is disabled, usually due to an internal
 * or caller's usage error. No future transition into #FIPS140_MODE or
 * #NON_FIPS140_MODE is permitted.  The caller's current operating system
 * process may continue to operate with currently opened library and
 * cryptographic contexts, but no additional contexts may be opened.
 */
#define DISABLED_MODE   0

/**
 * Indicates that the FIPS140 library is running in #FIPS140_MODE.
 * A transition into #NON_FIPS140_MODE is possible only after all
 * #FIPS140_MODE library contexts have been closed.
 */
#define FIPS140_MODE               1

/**
 * Indicates that the FIPS140 library is running in #NON_FIPS140_MODE.
 * A transition into #FIPS140_MODE is possible only after all
 * #NON_FIPS140_MODE library contexts have been closed.
 */
#define NON_FIPS140_MODE   2

/**
 * Indicates that the FIPS140 library is running in #FIPS140_SSL_MODE.
 * A transition into #NON_FIPS140_MODE is possible only after all
 * #FIPS140_SSL_MODE library contexts have been closed.
 */
#define FIPS140_SSL_MODE  3


/**
 * @} FIPS140_OPERATING_MODES
 */

/**
 * @defgroup FIPS140_FUNCS FIPS140 Functions
 * This section details the functions available to utilize
 * FIPS140 functionality.
 * @ingroup FIPS140_API_GROUP
 * @{
 */

/**
 * @} FIPS140_FUNCS
 */


/**
 * @defgroup FIPS140_OP_MODE_FUNC Operating Modes Functions
 * This section details the functions that facilitate the detection
 * and transition of the FIPS140 operating modes.
 * @ingroup FIPS140_FUNCS
 * @{
 */

/*
 *      Disables new library context creation if no libraries
 *      are currently operating.
 */
int CRYPTOC_FIPS140_disable_operating_modes();
int CRYPTOC_FIPS140_operating_mode_is_disabled();

/*
 *  Enables new FIPS140-approved algorithm-only library context creation.
 *  This is only valid if no libraries are currently operating.
 */
int CRYPTOC_FIPS140_enable_fips140_operating_mode();
int CRYPTOC_FIPS140_enable_fips140_ssl_operating_mode();
int CRYPTOC_FIPS140_operating_mode_is_fips140();
int CRYPTOC_FIPS140_operating_mode_is_fips140_ssl();

/*
 *  Enables access to the entire Crypto-C ME resource library.
 *  This is only valid if no libraries are currently operating.
 */
int CRYPTOC_FIPS140_enable_non_fips140_operating_mode();
int CRYPTOC_FIPS140_operating_mode_is_non_fips140();


/**
 * @} FIPS140_OP_MODE_FUNC
 */


/*
 * @defgroup FIPS140_USER_MODE_FUNC User Mode Functions
 * This section details the functions that facilitate the detection
 * and transition of the FIPS140 user modes.
 * @ingroup FIPS140_FUNCS
 * @{
 */

/*
 *  Routines to control user roles.
 *  Officers get to run self-tests.
 */
int     CRYPTOC_FIPS140_set_officer_sign_in_state();
int     CRYPTOC_FIPS140_set_user_sign_in_state();
int     CRYPTOC_FIPS140_sign_in_state_is_officer();
int     CRYPTOC_FIPS140_sign_in_state_is_user();
int     CRYPTOC_FIPS140_sign_in_state_is_disabled();

/*
 * @} FIPS140_USER_MODE_FUNC
 */


/*
 * @defgroup FIPS140_SELFTEST_FUNC Self-test Functions
 * This section details the functions that facilitate the
 * operation of the FIPS140 self tests.
 * @ingroup FIPS140_FUNCS
 * @{
 */

/*
 *  Returns the Crypto-C ME return code from the
 *  most recent self-test failure.
 */
int CRYPTOC_FIPS140_me_fips140_self_test();
int CRYPTOC_FIPS140_me_fips140_startup_self_test();
int CRYPTOC_FIPS140_get_self_test_result();
int CRYPTOC_FIPS140_get_startup_test_result();

/*
 * @} FIPS140_SELFTEST_FUNC
 */


/**
 * @defgroup FIPS140_VERSION_FUNC Version Functions
 * This section details the functions that enable access to
 * information about the software versions that are currently operating.
 * @ingroup FIPS140_FUNCS
 * @{
 */

unsigned char* CRYPTOC_FIPS140_get_version();

int CRYPTOC_FIPS140_library_is_shared();

#ifndef NO_TIME_H
void CRYPTOC_FIPS140_fetch_expire_date(struct tm* t);
#endif


/**
 * @} FIPS140_VERSION_FUNC
 */


/**
 * @defgroup FIPS140_LIBRARY_SHARE Shared Resource Functions
 * This section details the functions that are used to share
 * resources between the calling application and the FIPS140 library.
 * Although both entities reside in the same process space,
 * continuity between resources must be guaranteed.  For example,
 * mixed debug and non-debug memory allocators could cause
 * an exception event.
 * @ingroup FIPS140_FUNCS
 * @{
 */

R_RANDOM *CRYPTOC_FIPS140_rand_get_default(void);

int CRYPTOC_FIPS140_rand_set_default(R_RANDOM *rnd);

void CRYPTOC_FIPS140_set_mem_functions(R_MEM_MALLOC_FUNCTION_T *malloc_function,
    R_MEM_REALLOC_FUNCTION_T *realloc_function,
    R_MEM_FREE_FUNCTION_T *free_function);

void CRYPTOC_FIPS140_get_mem_functions(
    R_MEM_MALLOC_FUNCTION_T **malloc_function,
    R_MEM_REALLOC_FUNCTION_T **realloc_function,
    R_MEM_FREE_FUNCTION_T **free_function);

char *CRYPTOC_FIPS140_lock_get_name(int lock_id);
int CRYPTOC_FIPS140_lock_num(void);

#ifndef NO_R_LOCK
R_LOCK_CB_T *CRYPTOC_FIPS140_lock_get_cb(void);
int CRYPTOC_FIPS140_lock_set_cb(R_LOCK_CB_T *func);
#endif /* !NO_R_LOCK */


/**
 * @} FIPS140_LIBRARY_SHARE
 */


/*
 *      Deprecated definitions from FIPS140-1 product
 */
#define R_CR_SP_library_init CRYPTOC_ME_FIPS140_library_init
#define R_CR_SP_nist_library_init CRYPTOC_ME_FIPS140_fips140_library_init
#define R_CR_SP_non_nist_library_init CRYPTOC_ME_FIPS140_non_fips140_library_init
#define R_CR_SP_library_free CRYPTOC_ME_FIPS140_library_free
#define R_CR_SP_disable_operating_modes CRYPTOC_FIPS140_disable_operating_modes
#define R_CR_SP_operating_mode_is_disabled CRYPTOC_FIPS140_operating_mode_is_disabled
#define R_CR_SP_enable_nist_operating_mode CRYPTOC_FIPS140_enable_fips140_operating_mode
#define R_CR_SP_enable_nist_ssl_operating_mode CRYPTOC_FIPS140_enable_fips140_ssl_operating_mode
#define R_CR_SP_operating_mode_is_nist CRYPTOC_FIPS140_operating_mode_is_fips140
#define R_CR_SP_operating_mode_is_nist_ssl CRYPTOC_FIPS140_operating_mode_is_fips140_ssl
#define R_CR_SP_enable_non_nist_operating_mode CRYPTOC_FIPS140_enable_non_fips140_operating_mode
#define R_CR_SP_operating_mode_is_non_nist CRYPTOC_FIPS140_operating_mode_is_non_fips140
#define R_CR_SP_set_officer_sign_in_state CRYPTOC_FIPS140_set_officer_sign_in_state
#define R_CR_SP_set_user_sign_in_state CRYPTOC_FIPS140_set_user_sign_in_state
#define R_CR_SP_sign_in_state_is_officer CRYPTOC_FIPS140_sign_in_state_is_officer
#define R_CR_SP_sign_in_state_is_user CRYPTOC_FIPS140_sign_in_state_is_user
#define R_CR_SP_sign_in_state_is_disabled CRYPTOC_FIPS140_sign_in_state_is_disabled
#define R_CR_SP_me_nist_self_test CRYPTOC_FIPS140_me_fips140_self_test
#define R_CR_SP_me_nist_startup_self_test CRYPTOC_FIPS140_me_fips140_startup_self_test
#define R_CR_SP_get_self_test_result CRYPTOC_FIPS140_get_self_test_result

/*
 *      Deprecated definitions from FIPS140-1-1 product
 */
#define CRYPTOC_ME_NIST_library_init CRYPTOC_ME_FIPS140_library_init
#define CRYPTOC_ME_NIST_nist_library_init CRYPTOC_ME_FIPS140_fips140_library_init
#define CRYPTOC_ME_NIST_non_nist_library_init CRYPTOC_ME_FIPS140_non_fips140_library_init
#define CRYPTOC_ME_NIST_library_free CRYPTOC_ME_FIPS140_library_free
#define CRYPTOC_NIST_disable_operating_modes CRYPTOC_FIPS140_disable_operating_modes
#define CRYPTOC_NIST_operating_mode_is_disabled CRYPTOC_FIPS140_operating_mode_is_disabled
#define CRYPTOC_NIST_enable_nist_operating_mode CRYPTOC_FIPS140_enable_fips140_operating_mode
#define CRYPTOC_NIST_enable_nist_ssl_operating_mode CRYPTOC_FIPS140_enable_fips140_ssl_operating_mode
#define CRYPTOC_NIST_operating_mode_is_nist CRYPTOC_FIPS140_operating_mode_is_fips140
#define CRYPTOC_NIST_operating_mode_is_nist_ssl CRYPTOC_FIPS140_operating_mode_is_fips140_ssl
#define CRYPTOC_NIST_enable_non_nist_operating_mode CRYPTOC_FIPS140_enable_non_fips140_operating_mode
#define CRYPTOC_NIST_operating_mode_is_non_nist CRYPTOC_FIPS140_operating_mode_is_non_fips140
#define CRYPTOC_NIST_set_officer_sign_in_state CRYPTOC_FIPS140_set_officer_sign_in_state
#define CRYPTOC_NIST_set_user_sign_in_state CRYPTOC_FIPS140_set_user_sign_in_state
#define CRYPTOC_NIST_sign_in_state_is_officer CRYPTOC_FIPS140_sign_in_state_is_officer
#define CRYPTOC_NIST_sign_in_state_is_user CRYPTOC_FIPS140_sign_in_state_is_user
#define CRYPTOC_NIST_sign_in_state_is_disabled CRYPTOC_FIPS140_sign_in_state_is_disabled
#define CRYPTOC_NIST_me_nist_self_test CRYPTOC_FIPS140_me_fips140_self_test
#define CRYPTOC_NIST_me_nist_startup_self_test CRYPTOC_FIPS140_me_fips140_startup_self_test
#define CRYPTOC_NIST_get_self_test_result CRYPTOC_FIPS140_get_self_test_result
#define CRYPTOC_ME_NIST_dsa_generate_parameters CRYPTOC_ME_FIPS140_dsa_generate_parameters
#define CRYPTOC_ME_NIST_dsa_free CRYPTOC_ME_FIPS140_dsa_free
#define CRYPTOC_ME_NIST_dsa_is_prime CRYPTOC_ME_FIPS140_dsa_is_prime
#define CRYPTOC_NIST_get_self_test_result CRYPTOC_FIPS140_get_self_test_result
#define CRYPTOC_NIST_get_startup_test_result CRYPTOC_FIPS140_get_startup_test_result
#define CRYPTOC_NIST_get_version CRYPTOC_FIPS140_get_version
#define CRYPTOC_NIST_library_is_shared CRYPTOC_FIPS140_library_is_shared
#define CRYPTOC_NIST_fetch_expire_date CRYPTOC_FIPS140_fetch_expire_date
#define CRYPTOC_NIST_rand_get_default CRYPTOC_FIPS140_rand_get_default
#define CRYPTOC_NIST_rand_set_default CRYPTOC_FIPS140_rand_set_default
#define CRYPTOC_NIST_set_mem_functions CRYPTOC_FIPS140_set_mem_functions
#define CRYPTOC_NIST_get_mem_functions CRYPTOC_FIPS140_get_mem_functions
#define CRYPTOC_NIST_USE_LOCAL_DEFAULT_LIB CRYPTOC_FIPS140_USE_LOCAL_DEFAULT_LIB
#define NIST_MODE FIPS140_MODE
#define NON_NIST_MODE NON_FIPS140_MODE
#define NIST_SSL_MODE FIPS140_SSL_MODE


#ifdef  __cplusplus
}
#endif

#endif /* _LIBRARIAN_H_ */



