/* $Id: wlcorec.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 2001-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
/**
 * @file wlcorec.h
 * This file contains the cryptographic library product defines. This header
 * file is supplied for backward compatibility with Wireless Core 1.0 and
 * Wireless Core 1.6.
 */
#ifndef HEADER_WLCOREC_H
#define HEADER_WLCOREC_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "cryptocme.h"
/**
 * @defgroup WLCORE_MACROS Wireless Core Compatibility
 * @ingroup RelatedDocumentation Related Documentation
 * The functionality supported by Crypto-C ME was previously supplied
 * in RSA BSAFE Wireless Core.<br>
 * This section lists the macros supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup WLCORE_MACROS_ID Wireless Core Information Identifiers
 * This section lists the identifiers provided for backwards compatibility with
 * previous versions of Wireless Core.
 * @ingroup WLCORE_MACROS
 *
 * @{
 */
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_UNKNOWN.
 */
#define WLCORE_INFO_UNKNOWN                       CRYPTOC_ME_INFO_UNKNOWN
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_VERSION.
 */
#define WLCORE_INFO_VERSION                       CRYPTOC_ME_INFO_VERSION
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_BUILD_DATE.
 */
#define WLCORE_INFO_BUILD_DATE                    CRYPTOC_ME_INFO_BUILD_DATE
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_BUILD_FLAGS.
 */
#define WLCORE_INFO_BUILD_FLAGS                   CRYPTOC_ME_INFO_BUILD_FLAGS
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_BUILD_PLATFORM.
 */
#define WLCORE_INFO_BUILD_PLATFORM                CRYPTOC_ME_INFO_BUILD_PLATFORM
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_BUILD_TAG.
 */
#define WLCORE_INFO_BUILD_TAG                     CRYPTOC_ME_INFO_BUILD_TAG
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see CRYPTOC_ME_INFO_BUILD_EVAL.
 */
#define WLCORE_INFO_BUILD_EVAL                    CRYPTOC_ME_INFO_BUILD_EVAL
/**
 * @} WLCORE_MACROS_ID
 */
/**
 * @defgroup WLCORE_MACRO_RES Wireless Core Resource Definitions
 * This section details the resource definitions provided for backwards
 * compatibility with previous versions of Wireless Core.
 * @ingroup WLCORE_MACROS
 *
 * @{
 */
/**
 * This definition is supplied for backwards compatibility for previous
 * versions of Wireless Core.
 * @see R_CR_RES_LIBRARY_SMALL.
 */
#define WLCORE_RES_LIBRARY_SMALL                  R_CR_RES_LIBRARY_SMALL
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_LIBRARY.
 */
#define WLCORE_RES_LIBRARY                        R_CR_RES_LIBRARY
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_DEFAULT.
 */
#define WLCORE_RES_CRYPTO_DEFAULT                 R_CR_RES_CRYPTO_DEFAULT
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_CUSTOM.
 */
#define WLCORE_RES_CRYPTO_CUSTOM                  R_CR_RES_CRYPTO_CUSTOM
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_CUSTOM_METHOD()
 */
#define WLCORE_RES_CRYPTO_CUSTOM_METHOD \
                                           R_CR_RES_CRYPTO_CUSTOM_METHOD
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_SIGNATURE_MAP.
 */
#define WLCORE_RES_SIGNATURE_MAP                  R_CR_RES_SIGNATURE_MAP
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_PKEY_PRINT.
 */
#define WLCORE_RES_PKEY_PRINT                     R_CR_RES_PKEY_PRINT
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_PKEY_RSA.
 */
#define WLCORE_RES_PKEY_RSA                       R_CR_RES_PKEY_RSA
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_PKEY_DSA.
 */
#define WLCORE_RES_PKEY_DSA                       R_CR_RES_PKEY_DSA
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_PKEY_DH.
 */
#define WLCORE_RES_PKEY_DH                        R_CR_RES_PKEY_DH
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_RAND.
 */
#define WLCORE_RES_RAND                           R_CR_RES_RAND
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_TIME.
 */
#define WLCORE_RES_TIME                           R_CR_RES_TIME
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_COMMON_ERROR_STRINGS.
 */
#define WLCORE_RES_COMMON_ERROR_STRINGS \
                                          R_CR_RES_COMMON_ERROR_STRINGS
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_REASON_STRINGS.
 */
#define WLCORE_RES_CRYPTO_REASON_STRINGS \
                                          R_CR_RES_CRYPTO_REASON_STRINGS
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_FUNCTION_NAMES.
 */
#define WLCORE_RES_CRYPTO_FUNCTION_NAMES \
                                          R_CR_RES_CRYPTO_FUNCTION_NAMES
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_CRYPTO_DETAIL_STRINGS.
 */
#define WLCORE_RES_CRYPTO_DETAIL_STRINGS \
                                          R_CR_RES_CRYPTO_DETAIL_STRINGS
/**
 * This identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_RES_END_OF_LIST.
 */
#define WLCORE_RES_END_OF_LIST                    R_CR_RES_END_OF_LIST
/**
 * @} WLCORE_MACRO_RES
 */
/**
 * @defgroup WLCORE_MACROS_CUST Wireless Core Custom Configuration
 * This section details the custom identifiers provided for backwards
 * compatibility with previous versions of Wireless Core.
 * @ingroup WLCORE_MACROS
 *
 * @{
 */
/**
 * This custom identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_DEFINE_CUSTOM_CIPHER_LIST().
 */
#define WLCORE_CUSTOM_CIPHER_LIST                 R_CR_CUSTOM_CIPHER_LIST
/**
 * This custom identifier is supplied for backwards compatibility with previous
 * versions of Wireless Core.
 * @see R_CR_DEFINE_CUSTOM_METHOD_TABLE().
 */
#define WLCORE_CUSTOM_METHOD_TABLE                R_CR_CUSTOM_METHOD_TABLE
/**
 * @} WLCORE_MACROS
 */
/**
 * @defgroup WLCORE_MACROS_FN Wireless Core Functions
 * This section details the functions provided for backwards compatibility with
 * previous versions of Wireless Core.
 * @ingroup WLCORE_MACROS
 *
 * @{
 */
/* Function macros */
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_get_default_resource_list().
 */
#define WLCORE_get_default_resource_list \
                                         CRYPTOC_ME_get_default_resource_list
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_get_small_resource_list().
 */
#define WLCORE_get_small_resource_list \
                                         CRYPTOC_ME_get_small_resource_list
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see R_CR_get_crypto_resource_list().
 */
#define WLCORE_get_crypto_resource_list \
                                         CRYPTOC_ME_get_crypto_resource_list

/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_new().
 */
#define WLCORE_library_new                        CRYPTOC_ME_library_new
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_free().
 */
#define WLCORE_library_free                       CRYPTOC_ME_library_free

/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_version().
 */
#define WLCORE_library_version                    CRYPTOC_ME_library_version
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_info().
 */
#define WLCORE_library_info                       CRYPTOC_ME_library_info
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_info_type_to_string().
 */
#define WLCORE_library_info_type_to_string \
                                        CRYPTOC_ME_library_info_type_to_string
/**
 * This function is supplied for backwards compatibility with previous versions
 * of Wireless Core.
 * @see CRYPTOC_ME_library_info_type_from_string().
 */
#define WLCORE_library_info_type_from_string \
                                        CRYPTOC_ME_library_info_type_from_string
/**
 * @} WLCORE_MACROS_FN
 */
/**
 * @addtogroup WLCORE_MACROS_CUST
 *
 * @{
 */
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_SIGN_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_SIGN \
                                        R_CR_METHOD_SIGN_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_ERRINFO_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_ERRINFO \
                                        R_CR_METHOD_ERRINFO_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_INFO_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_INFO \
                                        R_CR_METHOD_INFO_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_SYM_ENC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_SYM_ENC \
                                        R_CR_METHOD_SYM_ENC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_SYM_DEC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_SYM_DEC \
                                        R_CR_METHOD_SYM_DEC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_VERIFY_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_VERIFY \
                                        R_CR_METHOD_VERIFY_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_ASYM_ENC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_ASYM_ENC \
                                        R_CR_METHOD_ASYM_ENC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_ASYM_DEC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_ASYM_DEC \
                                        R_CR_METHOD_ASYM_DEC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_DIGEST_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_DIGEST \
                                        R_CR_METHOD_DIGEST_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_MAC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_MAC \
                                        R_CR_METHOD_MAC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_VERIFY_MAC_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_VERIFY_MAC \
                                        R_CR_METHOD_VERIFY_MAC_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_KE_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_KE \
                                        R_CR_METHOD_KE_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_KEY_GEN_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_KEY_GEN \
                                        R_CR_METHOD_KEY_GEN_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_RAND_SEED_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_RAND_SEED \
                                        R_CR_METHOD_RAND_SEED_NOT_IMPLEMENTED
/**
 * This custom method identifier is supplied for backwards compatibility with
 * previous versions of Wireless Core.
 * @see R_CR_METHOD_RAND_GEN_NOT_IMPLEMENTED.
 */
#define R_CR_NOT_IMPLEMENTED_RAND_GEN \
                                        R_CR_METHOD_RAND_GEN_NOT_IMPLEMENTED
/**
 * @} WLCORE_MACROS_CUST
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_WLCOREC_H */


