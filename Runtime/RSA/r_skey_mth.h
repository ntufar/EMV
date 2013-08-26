/* $Id: r_skey_mth.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file holds all functionality related to symmetric keys and resource
 * lists.
 */

#ifndef HEADER_COMMON_KEY_R_SKEY_MTH_H
#define HEADER_COMMON_KEY_R_SKEY_MTH_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_skey.h"

R_SKEY_METHOD *R_SKEY_get_default_method(void *imp_data);

/**
 * @defgroup R_SKEY_RES Symmetric Key Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library. For more information,
 * see @ref RES_LIST_GROUP.
 * @ingroup SKEY_GROUP
 *
 * @{
 */

/**
 * The full #R_SKEY interface which is required if #R_SKEY functions are used.
 */
#define R_SKEY_RES_DEFAULT                                              \
    { R_RES_MOD_ID_SKEY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,           \
      R_RES_FLAG_DEF, NULL, NULL,                                       \
      (void *(*)(void *))R_SKEY_get_default_method, NULL }

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_KEY_R_SKEY_MTH_H */

