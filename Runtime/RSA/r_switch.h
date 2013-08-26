/* $Id: r_switch.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2003 RSA Security Inc. All rights reserved. 
 *
 * This work contains proprietary information of RSA Security. 
 * Distribution is limited to authorized licensees of RSA 
 * Security. Any unauthorized reproduction, distribution or 
 * modification of this work is strictly prohibited.
 */

/**
 * @file
 * This file contains public defines and functions for adding R_CR_SWICTH
 * cryptographic functionality to a resource list.
 */

#ifndef HEADER_COMMON_R_SWITCH_H
#define HEADER_COMMON_R_SWITCH_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "cryp_mod.h"

/**
 * @defgroup CR_SWITCH_GROUP Cryptographic Switch
 * This section details the components that provide support for
 * transparant (hardware vs. software) cryptographic operations.
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup CR_SWITCH_STRUCT Cryptographic Switch Structures
 * This section details the cryptographic switch structures used to
 * maintain data and methods for the cryptographic switch functions.
 * @ingroup CR_SWITCH_GROUP
 * @{
 */

/**
 * The cryptographic switch structure. This opaque structure represents a
 * single mode of operation of the library/module. Depending on how the
 * resource list is configured, objects can be in one of 4 modes (hardware/
 * software with fips/standard).
 */
typedef struct r_cr_switch_st             R_CR_SWITCH;

/**
 * @}
 */

/* Resource list functions for the different modes of operation */
int R_CR_SWITCH_hdw_lib_start(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);
int R_CR_SWITCH_hdw_lib_finish(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);

int R_CR_SWITCH_fips140_ssl_lib_start(R_RES_LIST *reslist,
    R_RES_ITEM *resitem, void **imp_data);
int R_CR_SWITCH_fips140_lib_start(R_RES_LIST *reslist,
    R_RES_ITEM *resitem, void **imp_data);
int R_CR_SWITCH_fips140_lib_finish(R_RES_LIST *reslist,
    R_RES_ITEM *resitem, void **imp_data);

int R_CR_SWITCH_std_lib_start(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);
int R_CR_SWITCH_std_lib_finish(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);

void *R_CR_SWITCH_get_hdw_cb(void *imp_data);

R_CR_METHOD *R_CR_SWITCH_get_method(void *imp_data);
R_CR_IMP_METHOD *R_CR_SWITCH_get_default_imp_method(void *imp_data);

/**
 * @defgroup CR_SWITCH_ITEMS Cryptographic Switch Resource List Definitions
 * This section details the defines that can be used in resource lists to
 * enable transparant handling of hardware and software cryptographic
 * operations. For more information, see @ref RES_LIST_GROUP.
 * @ingroup CR_SWITCH_GROUP
 * @{
 */

/**
 * This resource enables transparant hardware support. It will initialize all
 * hardware state (R_HW_CTX, etc.) needed to perform cryptographic operations
 * in hardware.
 */
#define R_CR_SWITCH_RES_HARDWARE                                             \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_HDW, R_RES_SUB_ID_DEF,              \
      R_RES_FLAG_DEF, R_CR_SWITCH_hdw_lib_start, R_CR_SWITCH_hdw_lib_finish, \
      NULL, R_CR_SWITCH_get_hdw_cb }

/**
 * This resource enables transparent FIPS-140 support. It will initialize the
 * FIPS state (Crypto C Micro Edition -ME Cryptographic Module) needed to 
 * perform cryptographic operations in a FIPS-140 validated mode. This mode is
 * mutually exclusive with R_CR_SWITCH_RES_FIPS140_SSL.
 */
#define R_CR_SWITCH_RES_FIPS140                                              \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_FIPS140, R_RES_SUB_ID_DEF,          \
      R_RES_FLAG_DEF, R_CR_SWITCH_fips140_lib_start,                         \
      R_CR_SWITCH_fips140_lib_finish, NULL, NULL }

/**
 * This resource enables transparent FIPS-140 SSL support. It will initialize 
 * the FIPS state (Crypto C Micro Edition -ME Cryptographic Module) needed to 
 * perform cryptographic operations in a FIPS-140 validated mode. 
 * This mode serves the
 * same purpose as R_CR_SWITCH_RES_FIPS140 with the distinction that more
 * algorithms are available such that an SSL handshake is possible. This mode
 * is mutually exclusive with R_CR_SWITCH_RES_FIPS140.
 */
#define R_CR_SWITCH_RES_FIPS140_SSL                                          \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_FIPS140, R_RES_SUB_ID_DEF,          \
      R_RES_FLAG_DEF, R_CR_SWITCH_fips140_ssl_lib_start,                     \
      R_CR_SWITCH_fips140_lib_finish, NULL, NULL }

/**
 * This resource enables transparent FIPS-140 support. It will initialize 
 * the FIPS state (Crypto C Micro Edition -ME Cryptographic Module) needed to 
 * perform cryptographic operations in a non-FIPS (un-validated) mode.
 */
#define R_CR_SWITCH_RES_STANDARD                                             \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_STD, R_RES_SUB_ID_DEF,              \
      R_RES_FLAG_DEF, R_CR_SWITCH_std_lib_start, R_CR_SWITCH_std_lib_finish, \
      NULL, NULL }

/**
 * This resource holds the methods needed for an application to perform
 * transparant hardware/software cryptographic operations.
 */
#define R_CR_SWITCH_RES_METHOD                                               \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,              \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_CR_SWITCH_get_method, \
      (void *(*)(void *))R_CR_SWITCH_get_default_imp_method }

/**
 * This resource holds the default set of R_CR_SWITCH resource items needed.
 */
#define R_CR_SWITCH_RES_DEFAULT                                              \
    R_CR_SWITCH_RES_STANDARD,                                                \
    R_CR_SWITCH_RES_FIPS140,                                                 \
    R_CR_SWITCH_RES_HARDWARE,                                                \
    R_CR_SWITCH_RES_METHOD

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SWITCH_H */


