/* $Id: cspxport.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
#ifndef __CSPXPORT_H
#define __CSPXPORT_H
 
#ifndef CRYPTOC_ME
#include "r_com.h"
#include "r_res.h"
#include "r_lib.h"
#include "r_mem.h"
#include "r_rand.h"
#include "r_skey.h"
#include "cryp_ops.h"
#include "cryp_mod.h"
#else
#include "cryptocme.h"
#endif

#ifndef NO_DSA
#include "dsa.h"
#endif /* NO_DSA */

#ifndef NO_TIME_H
#include <time.h>
#endif

#include "r_lock.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* Create function prototypes for all exported procedures.
   These definitions are used both for the shared library
   and for the client apps to ensure lexical binding
   throughout the system.
*/
typedef int (*t_library_is_shared)();
typedef int (*t_disable_operating_modes)();
typedef int (*t_operating_mode_is_disabled)();
typedef int (*t_enable_fips140_operating_mode)();
typedef int (*t_enable_fips140_ssl_operating_mode)();
typedef int (*t_operating_mode_is_fips140)();
typedef int (*t_operating_mode_is_fips140_ssl)();
typedef int (*t_enable_non_fips140_operating_mode)();
typedef int (*t_operating_mode_is_non_fips140)();
typedef int (*t_library_init)(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
typedef void (*t_library_free)(R_LIB_CTX *lib_ctx, R_CR_CTX *ctx);
typedef int (*t_set_officer_sign_in_state)();
typedef int (*t_set_user_sign_in_state)();
typedef int (*t_sign_in_state_is_officer)();
typedef int (*t_sign_in_state_is_user)();
typedef int (*t_sign_in_state_is_disabled)();
typedef int (*t_me_fips140_self_test)();
typedef int (*t_me_fips140_startup_self_test)();
typedef int (*t_get_self_test_result)();
typedef int (*t_get_startup_test_result)();
typedef unsigned char* (*t_get_version)();

typedef void (*t_init)(void);
typedef void (*t_fini)(void);

typedef int (*t_r_skey_new)(R_LIB_CTX *ctx, int key_type, R_ITEM *key_descriptor,
    R_SKEY **new_skey);
typedef int (*t_r_skey_free)(R_SKEY *skey);
typedef int (*t_r_skey_get_info)(R_SKEY *skey, int id, void *param);
typedef int (*t_r_skey_set_info)(R_SKEY *skey, int id, void *param);
typedef R_RANDOM *(*t_r_rand_get_default)(void);
typedef int (*t_r_rand_set_default)(R_RANDOM *rnd); /* the R_RANDOM is copied */
typedef void (*t_r_set_mem_functions)(R_MEM_MALLOC_FUNCTION_T *malloc_function,
    R_MEM_REALLOC_FUNCTION_T *realloc_function,
    R_MEM_FREE_FUNCTION_T *free_function);
typedef void (*t_r_get_mem_functions)(R_MEM_MALLOC_FUNCTION_T **malloc_function,
    R_MEM_REALLOC_FUNCTION_T **realloc_function,
    R_MEM_FREE_FUNCTION_T **free_function);

#ifndef NO_DSA
typedef DSA* (*t_dsa_generate_parameters)(int bits, unsigned char *seed,int seed_len,
		int *counter_ret, unsigned long *h_ret,
                void (*callback)(int,int,char *),char *cb_arg);
typedef int  (*t_dsa_enable_default_method)(void);
typedef void (*t_dsa_free)(DSA *dsa);
typedef int (*t_dsa_is_prime)(BIGNUM *q,void (*callback)(int,int,char *),
	      char *cb_arg);
#else /* NO_DSA */
typedef void* (*t_dsa_generate_parameters)(int bits, unsigned char *seed,
    int seed_len, int *counter_ret, unsigned long *h_ret,
    void (*callback)(int,int,char *),char *cb_arg);
typedef int  (*t_dsa_enable_default_method)(void);
typedef void (*t_dsa_free)(void *dsa);
typedef int (*t_dsa_is_prime)(void *q,void (*callback)(int,int,char *),
              char *cb_arg);
#endif /* NO_DSA */


#ifndef NO_TIME_H
typedef void (*t_fetch_expire_date)(struct tm*);
#else /* NO_TIME_H */
typedef void (*t_fetch_expire_date)(void *);
#endif /* NO_TIME_H */

#ifndef NO_R_LOCK
typedef R_LOCK_CB_T *(*t_r_lock_get_cb)(void);
typedef int (*t_r_lock_set_cb)(R_LOCK_CB_T *);
typedef int (*t_r_lock_num)(void);
typedef char *(*t_r_lock_get_name)(int);
#endif /* !NO_R_LOCK */

/**
 * This structure is used by the random object type.
 */

/**
 *	This structure is a table of function pointers  
 *  that are exposed by the NIST shared library.
 */
typedef struct t_imported_functions 
	{
	t_library_is_shared library_is_shared;
	t_disable_operating_modes disable_operating_modes;
	t_operating_mode_is_disabled operating_mode_is_disabled;
	t_enable_fips140_operating_mode enable_fips140_operating_mode;
	t_operating_mode_is_fips140 operating_mode_is_fips140;
	t_enable_non_fips140_operating_mode enable_non_fips140_operating_mode;
	t_operating_mode_is_non_fips140 operating_mode_is_non_fips140;
	t_library_init library_init;
	t_library_init library_init_fips140;
	t_library_init library_init_non_fips140;
	t_library_free library_free;
	t_dsa_generate_parameters dsa_generate_parameters;
	t_dsa_enable_default_method dsa_enable_default_method;
	t_dsa_free dsa_free;
	t_dsa_is_prime dsa_is_prime;
	t_set_officer_sign_in_state set_officer_sign_in_state;
	t_set_user_sign_in_state set_user_sign_in_state;
	t_sign_in_state_is_officer sign_in_state_is_officer;
	t_sign_in_state_is_user sign_in_state_is_user;
	t_sign_in_state_is_disabled sign_in_state_is_disabled;
	t_me_fips140_startup_self_test me_fips140_startup_self_test;
	t_me_fips140_self_test me_fips140_self_test;
	t_get_self_test_result get_self_test_result;
	t_get_startup_test_result get_startup_test_result;
	t_get_version get_version;

	t_r_rand_get_default r_rand_get_default;
	t_r_rand_set_default r_rand_set_default;
	t_r_set_mem_functions r_set_mem_functions;
	t_r_get_mem_functions r_get_mem_functions;
	t_fetch_expire_date fetch_expire_date;
	t_library_init library_init_fips140_ssl;
	t_enable_fips140_ssl_operating_mode enable_fips140_ssl_operating_mode;
	t_operating_mode_is_fips140_ssl operating_mode_is_fips140_ssl;

} ts_imported_functions, *tptr_imported_functions;


/**
 *	This structure is a table of function pointers  
 *  that are exposed by the NIST shared library in version 1.9.
 */
typedef struct t_lock_imported_functions 
	{
	unsigned long vers;
	t_library_is_shared library_is_shared;
	t_disable_operating_modes disable_operating_modes;
	t_operating_mode_is_disabled operating_mode_is_disabled;
	t_enable_fips140_operating_mode enable_fips140_operating_mode;
	t_operating_mode_is_fips140 operating_mode_is_fips140;
	t_enable_non_fips140_operating_mode enable_non_fips140_operating_mode;
	t_operating_mode_is_non_fips140 operating_mode_is_non_fips140;
	t_library_init library_init;
	t_library_init library_init_fips140;
	t_library_init library_init_non_fips140;
	t_library_free library_free;
	t_dsa_generate_parameters dsa_generate_parameters;
	t_dsa_enable_default_method dsa_enable_default_method;
	t_dsa_free dsa_free;
	t_dsa_is_prime dsa_is_prime;
	t_set_officer_sign_in_state set_officer_sign_in_state;
	t_set_user_sign_in_state set_user_sign_in_state;
	t_sign_in_state_is_officer sign_in_state_is_officer;
	t_sign_in_state_is_user sign_in_state_is_user;
	t_sign_in_state_is_disabled sign_in_state_is_disabled;
	t_me_fips140_startup_self_test me_fips140_startup_self_test;
	t_me_fips140_self_test me_fips140_self_test;
	t_get_self_test_result get_self_test_result;
	t_get_startup_test_result get_startup_test_result;
	t_get_version get_version;

	t_r_rand_get_default r_rand_get_default;
	t_r_rand_set_default r_rand_set_default;
	t_r_set_mem_functions r_set_mem_functions;
	t_r_get_mem_functions r_get_mem_functions;
	t_fetch_expire_date fetch_expire_date;
	t_library_init library_init_fips140_ssl;
	t_enable_fips140_ssl_operating_mode enable_fips140_ssl_operating_mode;
	t_operating_mode_is_fips140_ssl operating_mode_is_fips140_ssl;

#ifdef NO_R_LOCK
	void *r_lock_get_name;
	void *r_lock_num;
	void *r_lock_get_cb;
	void *r_lock_set_cb;
#else /* !NO_R_LOCK */
	t_r_lock_get_name r_lock_get_name;
	t_r_lock_num r_lock_num;
	t_r_lock_get_cb r_lock_get_cb;
	t_r_lock_set_cb r_lock_set_cb;
#endif /* !NO_R_LOCK */

} ts_lock_imported_functions, *tptr_lock_imported_functions;



#ifndef R_CR_DLL_EXPORT
#define R_CR_DLL_EXPORT
#endif

#ifdef  __cplusplus
}
#endif

#endif /* __CSPXPORT_H */

