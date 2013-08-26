/* $Id: r_lib_r.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file provides information on the structures, function prototypes and
 * defines for library context operations that relate to resource lists.
 */

#ifndef HEADER_COMMON_R_LIB_R_H
#define HEADER_COMMON_R_LIB_R_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_lib.h"

typedef int R_LIB_CTX_FUNC_T(R_LIB_CTX *ctx, R_RES_FLAG flag,
    R_LIB_CTX **new_ctx);

R_STRTBL *R_LIB_CTX_com_err_str_table(void *imp_data);

int R_LIB_CTX_lib_debug_data_start(R_RES_LIST *res_list, R_RES_ITEM *item,
        void **imp_data);
int R_LIB_CTX_lib_feature_start(R_RES_LIST *res_list, R_RES_ITEM *item,
        void **imp_data);


R_LIB_CTX_FUNC_T *R_LIB_CTX_get_dup_func(void *imp_data);

#ifndef Rm_LIB_CTX_DIRECT

R_LIB_METHOD *R_LIB_CTX_get_default_method(void *imp_data);
R_LIB_METHOD *R_LIB_CTX_get_small_method(void *imp_data);
R_LIB_METHOD *R_LIB_CTX_get_tiny_method(void *imp_data);

R_LIB_METHOD *R_LIB_CTX_get_default_nl_method(void *imp_data);
R_LIB_METHOD *R_LIB_CTX_get_small_nl_method(void *imp_data);

#else /* Rm_LIB_CTX_DIRECT */

#define R_LIB_CTX_get_default_method       NULL
#define R_LIB_CTX_get_small_method         NULL
#define R_LIB_CTX_get_tiny_method          NULL

#define R_LIB_CTX_get_default_nl_method    NULL
#define R_LIB_CTX_get_small_nl_method      NULL

#endif /* Rm_LIB_CTX_DIRECT */

/**
 * @defgroup R_LIB_RES Library Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */

/**
 * A tiny library interface that only supports the <tt>get_resource</tt>
 * method of the #R_LIB_CTX interface.
 *
 * @see R_LIB_CTX_get_tiny_method().
 */
#define R_LIB_RES_TINY                                               \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_get_tiny_method, NULL }

/**
 * A cut-down library interface that only supports the <tt>get_resource</tt>,
 * <tt>get_module</tt> and <tt>get_module_data</tt> methods of the #R_LIB_CTX
 * interface.
 *
 * @see R_LIB_CTX_get_small_method().
 */
#define R_LIB_RES_SMALL                                              \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_get_small_method, NULL }

/**
 * Indicates the full #R_LIB_CTX interface.
 * @see R_LIB_CTX_get_default_method().
 */
#define R_LIB_RES_DEFAULT                                            \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_get_default_method, NULL }

/**
 * A cut-down library interface that only supports the <tt>get_resource</tt>,
 * <tt>get_module</tt> and <tt>get_module_data</tt> methods of the #R_LIB_CTX
 * interface. This resource doesn't use locking.
 *
 * @see R_LIB_CTX_get_small_nl_method().
 */
#define R_LIB_RES_SMALL_NOT_LOCKED                                   \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_get_small_nl_method, NULL }

/**
 * Indicates the full #R_LIB_CTX interface. This resource doesn't use locking.
 * @see R_LIB_CTX_get_default_nl_method().
 */
#define R_LIB_RES_DEFAULT_NOT_LOCKED                                 \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_get_default_nl_method, NULL }

/**
 * Textual descriptions of common error codes. This is only required if using
 * R_LIB_CTX_get_string() string functions.
 *
 * @see R_LIB_CTX_com_err_str_table().
 */
#define R_LIB_RES_ERROR_STRINGS                                            \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_ERROR_STRINGS, \
      R_RES_FLAG_DEF, NULL, NULL, NULL,                                    \
      (void *(*)(void *))R_LIB_CTX_com_err_str_table }

/**
 * Indicates that #R_LIB_CTX_dup() is available.
 */
#define R_LIB_RES_DUP                                                     \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DUP_FUNC, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL, NULL,                                   \
      (void *(*)(void *))R_LIB_CTX_get_dup_func }

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_LIB_R_H */

