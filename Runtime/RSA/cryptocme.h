/* $Id: cryptocme.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryptocme.h
 * This file contains the cryptographic library prototypes and defines.
 */
#ifndef HEADER_CRYPTOC_ME_H
#define HEADER_CRYPTOC_ME_H

#ifdef  __cplusplus
extern "C" {
#endif

/* the current version number of the library */
#define CRYPTOC_ME_VERSION_NUMBER             0x1900

#ifndef CRYPTOC_ME
#define CRYPTOC_ME                             1
#endif

#define PRODUCT_LIBRARY_NEW                       CRYPTOC_ME_library_new
#define PRODUCT_LIBRARY_FREE                      CRYPTOC_ME_library_free
#define PRODUCT_DEFAULT_RESOURCE_LIST             \
    CRYPTOC_ME_get_default_resource_list
#define PRODUCT_FIPS140_SWITCH_RESOURCE_LIST      \
    CRYPTOC_ME_get_fips140_switch_resource_list
#define PRODUCT_NON_FIPS140_SWITCH_RESOURCE_LIST  \
    CRYPTOC_ME_get_non_fips140_switch_resource_list
#define PRODUCT_FIPS140_SSL_SWITCH_RESOURCE_LIST  \
    CRYPTOC_ME_get_fips140_ssl_switch_resource_list
#define PRODUCT_LIBRARY_VERSION                   CRYPTOC_ME_library_version
#define PRODUCT_LIBRARY_INFO                      CRYPTOC_ME_library_info
#define PRODUCT_LIBRARY_INFO_TYPE_FROM_STRING  \
    CRYPTOC_ME_library_info_type_from_string
#define PRODUCT_LIBRARY_INFO_TYPE_TO_STRING  \
    CRYPTOC_ME_library_info_type_to_string

#ifndef NO_SOCK
#define NO_SOCK
#endif

/* Include the header files that define the environment */
#include "r_com.h"

/* Include resource list and library context */
#include "r_res.h"
#include "r_lib_r.h"

/* Include the modules */
#ifndef NO_BIO
#include "bio.h"
#endif
#ifndef NO_PEM
#include "r_pem_mth.h"
#include "r_pswd_mth.h"
#endif
#include "r_pkey_mth.h"
#include "r_rand.h"
#include "cryp_mod.h"
#include "cryp_ops.h"
#include "cryp_err.h"
#include "nat_meth.h"
#include "cryp_meth.h"

#ifdef FIPS140_ONLY
#include "librarian.h"
#endif /* FIPS140_ONLY */

/* Library information types */
/**
 * @defgroup CRYPTOC_ME_GROUP Library Management
 * This section outlines the functions and identifiers used for library context
 * level operations including creating and freeing a library or obtaining
 * library information. These functions and identifiers also provide information
 * about key types, the library resource list and mapping Crypto-C ME
 * specific type identifiers to string value equivalents.
 * @ingroup CME_API
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup CRYPTOC_ME_INFO Crypto-C ME Information Defines
 *
 * This section defines the identifiers used to retrieve information about
 * the Crypto-C ME library.
 *
 * See CRYPTOC_ME_library_info_type_from_string(), CRYPTOC_ME_library_info(),
 * CRYPTOC_ME_library_info_type_to_string() and
 * CRYPTOC_ME_library_info_type_from_string().
 * @ingroup CRYPTOC_ME_GROUP
 *
 * @{
 */
/**
 * Indicates that an invalid string was passed as an argument.
 */
#define CRYPTOC_ME_INFO_UNKNOWN                                0
/**
 * Indicates the version of the library.
 *
 * @note The standard encoding method of
 * major.minor.subrelease.bugfixnumber is used.  For example, 0x1003
 * is 1.0.0c.
 */
#define CRYPTOC_ME_INFO_VERSION                                1
/**
 * Indicates the date the library was built.
 */
#define CRYPTOC_ME_INFO_BUILD_DATE                             2
/**
 * Indicates the flags used during the build of the library.
 */
#define CRYPTOC_ME_INFO_BUILD_FLAGS                            3
/**
 * Indicates the platform for which the library was built.
 */
#define CRYPTOC_ME_INFO_BUILD_PLATFORM                         4
/**
 * Indicates the unique build identifier for the library.
 */
#define CRYPTOC_ME_INFO_BUILD_ID                               5
/**
 * Indicates the build tag for the library.
 */
#define CRYPTOC_ME_INFO_BUILD_TAG                              6
/**
 * Indicates whether the library is an evaluation version.
 */
#define CRYPTOC_ME_INFO_BUILD_EVAL                             7
/**
 * Indicates whether the library is FIPS 140 validated cryptographic module.
 */
#define CRYPTOC_ME_INFO_BUILD_FIPS140                          8
/**
 * @}
 */

/**
 * @defgroup CRYPTOC_ME_FUNC Crypto-C ME Functions
 * This section outlines the functions used in the definition of resources
 * required for the Crypto-C ME library.
 * @ingroup CRYPTOC_ME_GROUP
 *
 * @{
 */
R_RES_LIST *CRYPTOC_ME_get_default_resource_list(void);
R_RES_LIST *CRYPTOC_ME_get_fips140_switch_resource_list(void);
R_RES_LIST *CRYPTOC_ME_get_non_fips140_switch_resource_list(void);
R_RES_LIST *CRYPTOC_ME_get_fips140_ssl_switch_resource_list(void);
R_RES_LIST *CRYPTOC_ME_get_small_resource_list(void);

int CRYPTOC_ME_library_new(R_RES_LIST *res_list, int flag, R_LIB_CTX **lib_ctx);
int CRYPTOC_ME_library_free(R_LIB_CTX *lib_ctx);

int CRYPTOC_ME_library_version(void);
char *CRYPTOC_ME_library_info(int type);
char *CRYPTOC_ME_library_info_type_to_string(int type);
int CRYPTOC_ME_library_info_type_from_string(char *str);
/**
 * @} CRYPTOC_ME_FUNC
 */

#ifdef  __cplusplus
}
#endif
#endif


