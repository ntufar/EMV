/* $Id: r_lib.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * defines used in the manipulation of library context objects.
 */

#ifndef HEADER_COMMON_R_LIB_H
#define HEADER_COMMON_R_LIB_H

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(SMALL_CODE_SIZE) && !defined(Rm_LIB_CTX_DIRECT)
#define Rm_LIB_CTX_DIRECT
#endif

#if defined(Rm_LIB_CTX_TABLE) && defined(Rm_LIB_CTX_DIRECT)
#undef Rm_LIB_CTX_TABLE
#endif

#ifdef Rm_LIB_CTX_FULL

#ifdef Rm_LIB_CTX_TABLE
#undef Rm_LIB_CTX_TABLE
#endif /* Rm_LIB_CTX_TABLE */

#ifdef Rm_LIB_CTX_DIRECT
#undef Rm_LIB_CTX_DIRECT
#endif /* Rm_LIB_CTX_DIRECT */

#endif /* Rm_LIB_CTX_FULL */

#include "r_com.h"
#include "r_res.h"
#include "r_flg.h"
#include "r_strtbl.h"

#ifndef NO_BIO
#include "bio.h"
#endif

/**
 * @defgroup RES_LIST_GROUP Resource List Module
 * This section provides information on the resource list, which is used to
 * perform link and runtime implementation selection of modules.
 * @ingroup CME_API
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup RES_LIST_TYPE Types
 * This section outlines the types used when dealing with the library and
 * the resources within.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */
/**
 * The common library context. This opaque structure is created via
 * R_LIB_CTX_new() and is required by all other #R_LIB_CTX
 * functions. It maintains the state required by the library
 * during execution. It can be freed via R_LIB_CTX_free() when it is no
 * longer required. Under normal circumstances only one context is
 * needed at a time.
 */

#ifndef HEADER_COMMON_R_LIB_CTX_TYPEDEF_DEF
#define HEADER_COMMON_R_LIB_CTX_TYPEDEF_DEF
typedef struct r_lib_ctx_st                     R_LIB_CTX;
#endif

/* end defgroup RES_LIST_TYPE */
/**
 * @}
 */

/**
 * The library method table. An opaque structure that contains
 * the methods for the #R_LIB_CTX functions.
 */
typedef struct r_lib_method_st                  R_LIB_METHOD;

/** 
 *  The library context debug structure which is used to define the type of
 *  debugging required and the location where the debug information is
 *  sent.
 */
typedef struct r_lib_debug_st
{
    R_FLG dbg_flg;
#ifndef NO_BIO
    BIO *bio;
#else
    void *bio;
#endif
} R_LIB_DEBUG;

#define R_DBG_SET(bit_num, dbg_prt)             \
    (((dbg_prt) != NULL) ? R_FLG_SET((bit_num), (&((dbg_prt)->dbg_flg))) : 0)
#define R_DBG_ON(bit_num, dbg_prt)              \
    (((dbg_prt) != NULL) ? R_FLG_ISSET((bit_num), (&((dbg_prt)->dbg_flg))) : 0)
#define R_DBG_CLR(bit_num, dbg_prt)             \
    (((dbg_prt) != NULL) ? R_FLG_CLR((bit_num), (&((dbg_prt)->dbg_flg))) : 0)
#define R_DBG_SET_ALL(dbg_prt)                  \
    (((dbg_prt) != NULL) ? R_FLG_SET_ALL((&((dbg_prt)->dbg_flg))) : 0)
#define R_DBG_ZERO(dbg_prt)                     \
    (((dbg_prt) != NULL) ? R_FLG_ZERO((&((dbg_prt)->dbg_flg))) : 0)

/* The R_LIB_DEBUG control defines */
#define R_LIB_DEBUG_GET                         1
#define R_LIB_DEBUG_SET                         2

/** 
 *  The library context feature structure which is used to store the state of
 *  the library features.
 */
typedef struct r_lib_feat_st
{
    unsigned long feature;
} R_LIB_FEAT;

/* Feature hash defines */
#define R_LIB_FEATURE_LOCKING                   0x00000001L

/* The R_LIB_FEAT control defines */
#define R_LIB_FEAT_SET                          1
#define R_LIB_FEAT_GET                          2
#define R_LIB_FEAT_DISABLE                      3
#define R_LIB_FEAT_ENABLE                       4
#define R_LIB_FEAT_IS_ENABLED                   5

/**
 * @defgroup LIB_CTX_INFO_TYPE Information Types
 * This section lists the information types that comprise library context.
 * The following table details the data types to pass into <i>value</i> when
 * calling R_LIB_CTX_get_info().
 * @ingroup RES_LIST_GROUP
 * @{
 * @br
 *
 * <!-- BEGIN R_LIB_CTX_get_info value types -->
 *
 * <table><tr>
 * <td><b>Identifier</b></td>
 *     <td><b>Value Data Type</b></td>
 * </tr><tr>
 * <td>#R_LIB_CTX_INFO_ID_RESOURCE_LIST</td>
 *     <td><tt>R_RES_LIST *</tt></td>
 * </tr><tr>
 * <td>#R_LIB_CTX_INFO_ID_MODE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * The following table details the data types to pass into <i>value</i> when
 * calling R_LIB_CTX_set_info().
 * @br
 *
 * <!-- BEGIN R_LIB_CTX_set_info value types -->
 *
 * <table><tr>
 * <td><b>Identifier</b></td>
 *     <td><b>Value Data Type</b></td>
 * </tr><tr>
 * <td>#R_LIB_CTX_INFO_ID_MODE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 * </tr></table>
 */

/**
 * Indicates the resource list of the library context.
 */
#define R_LIB_CTX_INFO_ID_RESOURCE_LIST 0x01

/**
 * Indicates the default mode of the library context. See @ref LIB_CTX_MODES
 * for valid options.
 */
#define R_LIB_CTX_INFO_ID_MODE          0x02

/**
 * @}
 */

/**
 * @defgroup LIB_CTX_MODES Library Context Modes
 * This section describes the library mode options.
 * @ingroup CRYPTOC_ME_GROUP  
 * @{
 */
/**
 * Indicates that FIPS 140 mode is enabled for the library.
 */
#define R_LIB_CTX_FIPS140_MODE  0x01

/**
 * Indicates that FIPS 140 mode is disabled for the library.
 */
#define R_LIB_CTX_STANDARD_MODE 0x02

/**
 * Indicates that hardware mode is enabled for the library.
 */
#define R_LIB_CTX_HARDWARE_MODE 0x04

/**
 * Indicates that software mode is enabled for the library.
 */
#define R_LIB_CTX_SOFTWARE_MODE 0x08
/**
 * @}
 */

/*
 * @defgroup RES_LIST_FN Operation Functions
 * This section outlines the functions used for initialization and 
 * manipulation of the #R_LIB_CTX and resources used within.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */

/* Get string defines */
#define R_LIB_CTX_get_error_string(lib_ctx, mod_id, code)                     \
    R_LIB_CTX_get_string((lib_ctx), (mod_id), R_RES_SUB_ID_ERROR_STRINGS,     \
        (code))
#define R_LIB_CTX_get_reason_string(lib_ctx, mod_id, code)                    \
    R_LIB_CTX_get_string((lib_ctx), (mod_id), R_RES_SUB_ID_REASON_STRINGS,    \
        (code))
#define R_LIB_CTX_get_detail_string(lib_ctx, mod_id, code)                    \
    R_LIB_CTX_get_string((lib_ctx), (mod_id), R_RES_SUB_ID_DETAIL_STRINGS,    \
        (code))
#define R_LIB_CTX_get_function_string(lib_ctx, mod_id, code)                  \
    R_LIB_CTX_get_string((lib_ctx), (mod_id), R_RES_SUB_ID_FUNCTION_STRINGS,  \
        (code))

#define R_LIB_CTX_load_module(lib_ctx, mod_id, impl_id, sub_id,               \
    flag, ptr, type, name)                                                    \
    (*type) = R_RES_FLAG_GLOBAL;                                              \
    if (R_LIB_CTX_get_module((lib_ctx), (mod_id), (impl_id), (sub_id),        \
        (flag), (void **)(ptr)) != R_ERROR_NONE)                              \
    {                                                                         \
        name((lib_ctx), (flag), (ptr));                                       \
        (*type) = R_RES_FLAG_PRIVATE;                                         \
    }

#define R_LIB_CTX_load_typed_module(lib_ctx, mod_id, impl_id, sub_id,         \
    flag, ptr, type, name)                                                    \
    (*type) = R_RES_FLAG_GLOBAL;                                              \
    if (R_LIB_CTX_get_module((lib_ctx), (mod_id), (impl_id), (sub_id),        \
        (flag), (void **)(ptr)) != R_ERROR_NONE)                              \
    {                                                                         \
        name((lib_ctx), (flag), (sub_id), (ptr));                             \
        (*type) = R_RES_FLAG_PRIVATE;                                         \
    }

#define R_LIB_CTX_unload_module(lib_ctx, ptr, type, name)                     \
    if (type == R_RES_FLAG_PRIVATE)                                           \
    {                                                                         \
        name(ptr);                                                            \
    }

int R_LIB_CTX_new(R_RES_LIST *r_list, R_RES_FLAG flag, R_LIB_CTX **lib_ctx);
int R_LIB_CTX_free(R_LIB_CTX *lib_ctx);
int R_LIB_CTX_dup(R_LIB_CTX *lib_ctx, R_RES_FLAG flag, R_LIB_CTX **res_ctx);
int R_LIB_CTX_set_info(R_LIB_CTX *lib_ctx, int info_id, void *value);
int R_LIB_CTX_get_info(R_LIB_CTX *lib_ctx, int info_id, void *value);

int R_LIB_CTX_module_setup(R_LIB_CTX *lib_ctx, int mod_id, int imp_id,
    int sub_id, R_RES_FLAG flag, void *rgen);

R_RES_LIST *R_LIB_CTX_get_resource_list(R_LIB_CTX *lib_ctx);

char *R_LIB_CTX_get_string(R_LIB_CTX *lib_ctx, int mod_id, int table_id,
        int err_code);

#if defined(Rm_LIB_CTX_TABLE) || defined(Rm_LIB_CTX_DIRECT)

#include "rx_lib.h"

#endif /* defined(Rm_LIB_CTX_TABLE) || defined(Rm_LIB_CTX_DIRECT) */

#if !defined(Rm_LIB_CTX_TABLE) && !defined(Rm_LIB_CTX_DIRECT)

int R_LIB_CTX_get_resource(R_LIB_CTX *res_ctx, int mod_id, int impl_id,
        int sub_id, R_RES_FLAG flag, int res_type, void **data);
int R_LIB_CTX_get_module(R_LIB_CTX *res_ctx, int mod_id, int impl_id,
        int sub_id, R_RES_FLAG flag, void **mod);
int R_LIB_CTX_get_module_data(R_LIB_CTX *lib_ctx, int mod_id, void **impl_data);

int R_LIB_CTX_set_features(R_LIB_CTX *lib_ctx, int impl_id,
    R_LIB_FEAT *features);
int R_LIB_CTX_get_features(R_LIB_CTX *lib_ctx, int impl_id,
    R_LIB_FEAT *features);
int R_LIB_CTX_reset_features(R_LIB_CTX *lib_ctx, int impl_id);
int R_LIB_CTX_feature_disable(R_LIB_CTX *lib_ctx, int impl_id,
    R_LIB_FEAT *feature);
int R_LIB_CTX_feature_enable(R_LIB_CTX *lib_ctx, int impl_id,
    R_LIB_FEAT *feature);
int R_LIB_CTX_is_feature_enabled(R_LIB_CTX *lib_ctx, int impl_id,
    R_LIB_FEAT *feature);

int R_LIB_CTX_get_lib_debug_data(R_LIB_CTX *lib_ctx, R_LIB_DEBUG **data);
int R_LIB_CTX_set_lib_debug_data(R_LIB_CTX *lib_ctx, R_LIB_DEBUG *data);

#endif /* !defined(Rm_LIB_CTX_TABLE) && !defined(Rm_LIB_CTX_DIRECT) */

/* end defgroup RES_LIST_FN */
/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_LIB_H */


