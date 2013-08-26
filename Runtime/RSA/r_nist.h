/* $Id: r_nist.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file contains public defines and functions for adding NIST-certified
 * cryptographic functionality to a resource list.
 */

#ifndef HEADER_COMMON_R_NIST_H
#define HEADER_COMMON_R_NIST_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "cryp_mod.h"

/*
 *  @defgroup NIST_GROUP NIST-certified Cryptographic Functionality
 *  This section details the components that provide support for
 *  NIST-certified cryptographic functionality.
 * @{
 */

/*
 *  @}
 */

/*
 * The functions that handle the NIST shared library.
 */
int R_NIST_library_start(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);
int R_NIST_library_finish(R_RES_LIST *reslist, R_RES_ITEM *resitem,
    void **imp_data);

/*
 * The method for NIST cryptographic functionality handling.
 */
R_CR_METHOD *R_NIST_get_crypto_method(void *imp_data);

/**
 * @defgroup R_NIST_RES NIST Resource Definitions
 * This section details the definition used in the resource list and
 * initialization of the library. See @ref RES_LIST_GROUP.
 * @ingroup NIST_API_GROUP
 *
 * @{
 */

/**
 * The NIST shared library implementation of the #R_CR interface.
 */
#define R_CR_RES_NIST                                                 \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,       \
      R_RES_FLAG_DEF, R_NIST_library_start, R_NIST_library_finish,    \
      (void *(*)(void *))R_NIST_get_crypto_method, NULL }

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_NIST_H */

