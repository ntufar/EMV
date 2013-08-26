/* $Id: r_pkey_mth.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file  r_pkey_mth.h
 * @brief This file provides information on function prototypes and
 * identifiers for #R_PKEY_METHOD.
 */

#ifndef HEADER_COMMON_CERT_R_PKEY_MTH_H
#define HEADER_COMMON_CERT_R_PKEY_MTH_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_pkey.h"
#ifdef FIPS140_ONLY
#include "r_nist.h"
#endif

/*
 * @defgroup PKEY_METHOD_FLAGS Public Key Method Table Flags
 * All the flags that can be assigned to the flag field of public key method 
 * table.
 * @ingroup PKEY_GROUP
 * @{
 */

/* Defines for flags - implementation properties and features supported
 * for a given certificate (or certificate method).
 */
/**
 * No flags
 */
#define R_PKEY_METHOD_FL_NONE           0x0000
/**
 * Normal implementation
 */
#define R_PKEY_METHOD_FL_NORMAL         0x0001
/**
 * Compact implementation
 */
#define R_PKEY_METHOD_FL_COMPACT        0x0002
/**
 * Supports configuration
 */
#define R_PKEY_METHOD_FL_SUPPORT_CONFIG 0x0004
/**
 * Supports BIO ops
 */
#define R_PKEY_METHOD_FL_SUPPORT_BIO    0x0008
/**
 * Supports PEM format
 */
#define R_PKEY_METHOD_FL_SUPPORT_PEM    0x0010
/**
 * Supports name processing
 */
#define R_PKEY_METHOD_FL_SUPPORT_NAME   0x0020
/**
 * Allocated method
 */
#define R_PKEY_METHOD_FL_ALLOCATED      0x1001
/**
 * Allocated data
 */
#define R_PKEY_METHOD_FL_ALLOCATED_DATA 0x1002

/*
 * @}
 */

/*
 * @defgroup PKEY_METHOD Public Key Method Functions
 * All the functions that deal with public key method tables.
 * @ingroup PKEY_ALL_FUNCS
 * @{
 */

R_PKEY_METHOD *R_PKEY_get_method(R_PKEY *pkey);

char *R_PKEY_METHOD_get_name(R_PKEY_METHOD *method);
int   R_PKEY_METHOD_get_type(R_PKEY_METHOD *method);
int   R_PKEY_METHOD_get_flag(R_PKEY_METHOD *method);
int   R_PKEY_METHOD_free(R_PKEY_METHOD *method);

int R_PKEY_rsa_blinding_lib_start(R_RES_LIST *list, R_RES_ITEM *item,
    void **imp_data);
int R_PKEY_rsa_no_blinding_lib_start(R_RES_LIST *list, R_RES_ITEM *item,
    void **imp_data);

/*
 * @}
 */

#ifndef NO_BIO
/* R_PKEY print function to add into the resource list */
int (*R_PKEY_get_print_func(void *imp_data))(BIO *bio, R_PKEY *pkey,
    R_FORMAT format, char *format_arg);
#endif /* NO_BIO */

/**
 * @defgroup R_PKEY_RES Public Key Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library. For more information, 
 * see @ref RES_LIST_GROUP.
 * @ingroup PKEY_GROUP
 *
 * @{
 */

/**
 * The full #R_PKEY interface implemented in terms of 
 * Diffie-Hellman which is required if #R_PKEY functions are used.
 */
#define R_PKEY_RES_DH                                                   \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_DH,             \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_PKEY_pk_method,  \
      NULL }

/**
 * The full #R_PKEY interface implemented in terms of Digital
 * Signature Algorithm (DSA) which is required if #R_PKEY functions are used.
 */
#define R_PKEY_RES_DSA                                                  \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_DSA,            \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_PKEY_pk_method,  \
      NULL }

/**
 * The full #R_PKEY interface implemented in terms of RSA
 * which is required if #R_PKEY functions are used.
 */
#ifdef FIPS140_ONLY
/* Blinding cannot be set in FIPS140 shared library. It is always on. */
#define R_PKEY_RES_RSA                                                  \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_RSA,            \
      R_RES_FLAG_DEF, NULL, NULL,                                       \
      (void *(*)(void *))R_PKEY_pk_method, NULL }
#else /* ! FIPS140_ONLY */
#define R_PKEY_RES_RSA                                                  \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_RSA,            \
      R_RES_FLAG_DEF, R_PKEY_rsa_blinding_lib_start, NULL,              \
      (void *(*)(void *))R_PKEY_pk_method, NULL }
#endif /* FIPS140_ONLY */
/**
 * The full #R_PKEY interface implemented in terms of RSA
 * which is required if #R_PKEY functions are used. The RSA implementation
 * does not use any blinding functionality.
 */
#define R_PKEY_RES_RSA_NO_BLINDING                                      \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_RSA,            \
      R_RES_FLAG_DEF, R_PKEY_rsa_no_blinding_lib_start, NULL,           \
      (void *(*)(void *))R_PKEY_pk_method, NULL }



/**
 * @fn void R_PKEY_RES_CUSTOM(
 *        int (*start_fn)(R_RES_LIST *, R_RES_ITEM *, void **),
 *        int (*fin_fn)(R_RES_LIST *, R_RES_ITEM *, void **),
 *        R_PKEY_METHOD *(*meth_fn)(void *),
 *        void *(*data_fn)(void *),
 *        int type)
 *
 * Binds a custom method table to the public/private key module.
 *
 * @param start_fn This function performs library start up functionality,
 *                 this can be NULL if not required.
 * @param fin_fn   This function performs library finish functionality,
 *                 this can be NULL if not required.
 * @param meth_fn  This function must return the custom method list.
 * @param data_fn  This function can return data for the custom method to
 *                 use, this can be NULL if not required.
 * @param type     Type of the key that is implemented by meth_fn, can be
 *                 one of: #R_PKEY_TYPE_RSA, #R_PKEY_TYPE_DSA, #R_PKEY_TYPE_DH.
 */
#define R_PKEY_RES_CUSTOM(start_fn, fin_fn, meth_fn, data_fn, type)     \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, type, R_RES_FLAG_DEF,       \
      (int (*)(R_RES_LIST *, R_RES_ITEM *, void **))(start_fn),         \
      (int (*)(R_RES_LIST *, R_RES_ITEM *, void **))(fin_fn),           \
      (void *(*)(void *))meth_fn, (void *(*)(void *))data_fn }

#ifndef NO_BIO
/**
 * The standard public key print module 
 * which is required if R_PKEY_print() functions are used.
 */
#define R_PKEY_RES_PRINT                                            \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_PRINT_FUNC,                  \
      R_RES_SUB_ID_DEF, R_RES_FLAG_DEF, NULL, NULL, NULL,           \
      (void *(*)(void *))R_PKEY_get_print_func }
#endif /* NO_BIO */

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_CERT_R_PKEY_MTH_H */

