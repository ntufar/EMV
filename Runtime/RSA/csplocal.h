/* $Id: csplocal.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/**
 * @file
 */

#ifndef _CSPLOCAL_H_
#define _CSPLOCAL_H_


#if (defined(CERTC_ME) || defined(SSLCME))
#include "r_com.h"
#include "r_res.h"
#include "r_lib.h"
#include "r_mem.h"
#include "r_rand.h"
#include "r_skey.h"
#include "cryp_ops.h"
#include "cryp_mod.h"
#include "dsa.h"
#else
#include "cryptocme.h"
#endif

#include "librarian.h"

#ifndef NO_TIME_H
#include <time.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define CRYPTOC_LOCAL_set_new_library_vectors(vec) \
    CRYPTOC_LOCAL_set_version_library_vectors(vec, CRYPTOC_ME_VERSION_NUMBER)

/*
 *      Non-published library init APIs
 */
int R_CR_LOCAL_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
int R_CR_LOCAL_fips140_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
int R_CR_LOCAL_fips140_ssl_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
int R_CR_LOCAL_non_fips140_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
void R_CR_LOCAL_library_free(R_LIB_CTX *lib_ctx, R_CR_CTX *ctx);

/*
 *      Non-published APIs always access the version in the local executable.
 */
int R_CR_LOCAL_disable_operating_modes();
int R_CR_LOCAL_operating_mode_is_disabled();
int R_CR_LOCAL_enable_fips140_operating_mode();
int R_CR_LOCAL_enable_fips140_ssl_operating_mode();
int R_CR_LOCAL_operating_mode_is_fips140();
int R_CR_LOCAL_operating_mode_is_fips140_ssl();
int R_CR_LOCAL_enable_non_fips140_operating_mode();
int R_CR_LOCAL_operating_mode_is_non_fips140();
int R_CR_LOCAL_set_officer_sign_in_state();
int R_CR_LOCAL_set_user_sign_in_state();
int R_CR_LOCAL_sign_in_state_is_officer();
int R_CR_LOCAL_sign_in_state_is_user();
int R_CR_LOCAL_sign_in_state_is_disabled();

int R_CR_LOCAL_me_fips140_self_test();
int R_CR_LOCAL_me_fips140_startup_self_test();
int R_CR_LOCAL_get_self_test_result();
int R_CR_LOCAL_get_startup_test_result();

unsigned char* R_CR_LOCAL_get_version();
int R_CR_LOCAL_library_is_shared();
#ifndef NO_TIME_H
void R_CR_LOCAL_fetch_expire_date(struct tm* t);
#endif

DSA* R_CR_LOCAL_dsa_generate_parameters(int bits, unsigned char *seed,int seed_len,
		int *counter_ret, unsigned long *h_ret,
		void (*callback)(int,int,char *),char *cb_arg);
int R_CR_LOCAL_dsa_enable_default_method(void);
void R_CR_LOCAL_dsa_free(DSA *dsa);

int R_CR_LOCAL_dsa_is_prime(BIGNUM *q,void (*callback)(int,int,char *),
					char *cb_arg);

R_RANDOM *R_CR_LOCAL_rand_get_default(void);
int R_CR_LOCAL_rand_set_default(R_RANDOM *rnd);

void R_CR_LOCAL_set_mem_functions(R_MEM_MALLOC_FUNCTION_T *malloc_function,
    R_MEM_REALLOC_FUNCTION_T *realloc_function,
    R_MEM_FREE_FUNCTION_T *free_function);

void R_CR_LOCAL_get_mem_functions(R_MEM_MALLOC_FUNCTION_T **malloc_function,
    R_MEM_REALLOC_FUNCTION_T **realloc_function,
    R_MEM_FREE_FUNCTION_T **free_function);


char *R_CR_LOCAL_lock_get_name(int lock_id);
int R_CR_LOCAL_lock_num(void);
R_LOCK_CB_T *R_CR_LOCAL_lock_get_cb(void);
int R_CR_LOCAL_lock_set_cb(R_LOCK_CB_T *func);


/*
 *  The library call to obtain crypto for self-tests.
 *  This is only valid only if run by validation test programs.
 *  Otherwise returns an error.
 */
int R_CR_LOCAL_selftest_library_init(R_LIB_CTX **lib_ctx, R_CR_CTX **ctx);
void R_CR_LOCAL_selftest_library_free(R_LIB_CTX *lib_ctx, R_CR_CTX *ctx);

int R_CR_LOCAL_startup();
int R_CR_LOCAL_set_info(int info_id, void *info);
int R_CR_LOCAL_external_init(void* ob_handle, char *lpFileName);

/* Legacy typedef. */
typedef ts_imported_functions* (*get_library_vectors)();

typedef int (*CRYPTOC_SELECT_VERSION_FUNC_T)(int);
typedef void* (*CRYPTOC_GET_LIBRARY_VECTORS_FUNC_T)();
typedef int (*CRYPTOC_SIZE_OF_LIBRARY_VECTORS_FUNC_T)();

R_CR_DLL_EXPORT int CRYPTOC_LOCAL_select_version(int version);
R_CR_DLL_EXPORT void *CRYPTOC_LOCAL_get_library_vectors();
R_CR_DLL_EXPORT int CRYPTOC_LOCAL_size_of_library_vectors();
void CRYPTOC_LOCAL_set_library_vectors(ts_imported_functions* method_vectors);
int CRYPTOC_LOCAL_set_version_library_vectors(void* method_vectors,
    int version);
void *CRYPTOC_LOCAL_get_method_vectors();
void CRYPTOC_LOCAL_set_method_vectors(ts_imported_functions* new_vectors);
ts_imported_functions *CRYPTOC_LOCAL_get_post_init_export_list();
ts_lock_imported_functions *CRYPTOC_LOCAL_get_lock_post_init_export_list();
void* CRYPTOC_LOCAL_fetch_local_version_library_vectors(int version);
void CRYPTOC_LOCAL_set_disabled_vectors();
ts_imported_functions* CRYPTOC_LOCAL_get_disabled_vectors();
ts_lock_imported_functions* CRYPTOC_LOCAL_get_lock_disabled_vectors();

R_CR_METHOD *CRYPTOC_LOCAL_get_r_cr_method(void *imp_data);

#ifdef  __cplusplus
}
#endif

#endif /* _CSPLOCAL_H_ */


