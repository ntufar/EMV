/* $Id: r_modid.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/** @file  r_modid.h
 *  This file contains the defines used in creating items for a resource list.
 */

#ifndef HEADER_COMMON_DATA_R_MODID_H
#define HEADER_COMMON_DATA_R_MODID_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * Exported macro constants
 */

/* Different types of modules in the resource list */
/**
 * Indicates any module identifier will match.
 */
#define R_RES_MOD_ID_ANY                        (-2)
/**
 * Indicates any module identifier will match.
 */
#define R_RES_MOD_ID_ALL                        (-1)
/**
 * Indicates the resource list module.
 */
#define R_RES_MOD_ID_RES_LIST                   0
/**
 * Indicates the library module.
 */
#define R_RES_MOD_ID_LIBRARY                    1
/**
 * Indicates the memory module.
 */
#define R_RES_MOD_ID_MEM                        2
/**
 * Indicates the locking module.
 */
#define R_RES_MOD_ID_LOCK                       3
/**
 * Indicates the error module.
 */
#define R_RES_MOD_ID_ERR                        4
/**
 * Indicates the time module.
 */
#define R_RES_MOD_ID_TIME                       5
/**
 * Indicates the cryptographic module.
 */
#define R_RES_MOD_ID_CRYPTO                     6
/**
 * Indicates the Wireless Transport Layer Security C (WTLSC)
 * implementation module.
 */
#define R_RES_MOD_ID_WTLSC_CRYPTO               7
/**
 * Indicates the caching module.
 */
#define R_RES_MOD_ID_CACHE                      8
/**
 * Indicates the secret key module.
 */
#define R_RES_MOD_ID_SKEY                       9
/**
 * Indicates the certificate module.
 */
#define R_RES_MOD_ID_CERT                       10
/**
 * Indicates the compression module.
 */
#define R_RES_MOD_ID_COMP                       11
/**
 * Indicates the key generation module.
 */
#define R_RES_MOD_ID_KGEN                       12
/**
 * Indicates the certificate generation module.
 */
#define R_RES_MOD_ID_CGEN                       13
/**
 * Indicates the version module.
 */
#define R_RES_MOD_ID_VERSION                    14
/**
 * Indicates the Wireless Transport Layer Security (WTLS) module.
 */
#define R_RES_MOD_ID_WTLS                       15
/**
 * Indicates the public key module.
 */
#define R_RES_MOD_ID_PKEY                       16
/**
 * Indicates the Privacy Enhanced Mail (PEM) module.
 */
#define R_RES_MOD_ID_PEM                        17
/**
 * Indicates the product feature module.
 */
#define R_RES_MOD_ID_FEATURE                    18
/**
 * Indicates the debug module.
 */
#define R_RES_MOD_ID_DEBUG                      19
/**
 * Indicates the password module.
 */
#define R_RES_MOD_ID_PASSWD                     20
/**
 * Indicates the Socket I/O (SIO) module.
 */
#define R_RES_MOD_ID_SIO                        21
/**
 * Indicates the chain verification module.
 */
#define R_RES_MOD_ID_VERIFY                     22
/**
 * Indicates the random module.
 */
#define R_RES_MOD_ID_RAND                       23
/**
 * Indicates the memory buffer module.
 */
#define R_RES_MOD_ID_BUFFER                     24
/**
 * Indicates the WAP Markup Language Signing (WMLS) module.
 */
#define R_RES_MOD_ID_WMLS                       25
/**
 * Indicates the certificate store module.
 */
#define R_RES_MOD_ID_CERT_STORE                 26
/**
 * Indicates the cryptographic message syntax standard module.
 */
#define R_RES_MOD_ID_CM                         27
/**
 * Indicates the Secure Socket Layer (SSL) module.
 */
#define R_RES_MOD_ID_SSL                        28
/**
 * Indicates the certificate request module.
 */
#define R_RES_MOD_ID_CERT_REQ                   29
/**
 * Indicates the certificate revocation list (CRL) module.
 */
#define R_RES_MOD_ID_CRL                        30
/**
 * Indicates the BIO module.
 */
#define R_RES_MOD_ID_BIO                        31
/**
 * Indicates the FIPS certified shared library (dll) module.
 */
#define R_RES_MOD_ID_FIPS                       32
/**
 * Indicates the number of separate modules identified.
 */
#define R_RES_NUM_MOD_ID                        33


/* Implementation ID defines */
/**
 * Indicates that any implementation identifier will match.
 */
#define R_RES_IMPL_ID_ANY                       (-1)
/**
 * Indicates the default implementation.
 */
#define R_RES_IMPL_ID_DEF                       0
/**
 * Indicates all implementations.
 */
#define R_RES_IMPL_ID_ALL                       1
/**
 * Indicates the WTLSC product implementation.
 */
#define R_RES_IMPL_ID_WTLSC                     2
/**
 * Indicates the SSLC product implementation.
 */
#define R_RES_IMPL_ID_SSLC                      3
/**
 * Indicates the WMLSC product implementation.
 */
#define R_RES_IMPL_ID_WMLSC                     4
/**
 * Indicates the cipher algorithm function - cryptographic module.
 */
#define R_RES_IMPL_ID_CIPHER_ALG_FUNC           5
/**
 * Indicates the print function - certificate and public key modules.
 */
#define R_RES_IMPL_ID_PRINT_FUNC                6
/**
 * Indicates tndicates to verify details using time function - chain
 * verification module.
 */
#define R_RES_IMPL_ID_VFY_DETAILS_TIME_FUNC     7
/**
 * Indicates the verify details function - chain verification module.
 */
#define R_RES_IMPL_ID_VFY_DETAILS_FUNC          8
/**
 * Indicates the create state function - chain verification module.
 */
#define R_RES_IMPL_ID_CREATE_STATE_FUNC         9
/**
 * Indicates the verify state function - chain verification module.
 */
#define R_RES_IMPL_ID_VERIFY_STATE_FUNC         10
/**
 * Indicates the protocol implementation.
 */
#define R_RES_IMPL_ID_PROTOCOL                  11
/**
 * The protocol method implementation. - SSL module
 */
#define R_RES_IMPL_ID_PROTOCOL_METHOD           12
/**
 * The cipher map. - SSL module
 */
#define R_RES_IMPL_ID_CIPHER_MAP                13
/**
 * The cipher suites validation function to be used by ssl - SSL module.
 */
#define R_RES_IMPL_ID_CIPHER_FUNC               14
/**
 * The protocol crypto method - SSL module.
 */
#define R_RES_IMPL_ID_CRYPTO_METHOD             15
/**
 * Indicates the verification extensions function - chain verification module.
 */
#define R_RES_IMPL_ID_VFY_EXTENSIONS            16
/**
 * Indicates the verification Certificate Revocation List (CRL)function -
 * chain verification module.
 */
#define R_RES_IMPL_ID_VFY_CRL_FUNC              17
/**
 * Indicates the a hardware implementation for the module
 */
#define R_RES_IMPL_ID_HDW                       18
/**
 * Indicates the a FIPS 140 implementation for the module
 */
#define R_RES_IMPL_ID_FIPS140                   19
/**
 * Indicates the a standard implementation for the module
 */
#define R_RES_IMPL_ID_STD                       20
/**
 * Indicates the duplicate function.
 */
#define R_RES_IMPL_ID_DUP_FUNC                  21


/* Sub ID defines */
/**
 * Matches any sub identifier.
 */
#define R_RES_SUB_ID_ANY                        (-1)
/**
 * Indicates the default sub identifier.
 */
#define R_RES_SUB_ID_DEF                        0
/**
 * Indicates all sub identifiers.
 */
#define R_RES_SUB_ID_ALL                        1
/**
 * The error strings identifier - all modules that support full error handling.
 */
#define R_RES_SUB_ID_ERROR_STRINGS              2
/**
 * The reason strings identifier - all modules that support full error handling.
 */
#define R_RES_SUB_ID_REASON_STRINGS             3
/**
 * The detailed strings identifier - all modules that  support full error
 * handling.
 */
#define R_RES_SUB_ID_DETAIL_STRINGS             4
/**
 * The function strings identifier - all modules that support full error
 * handling.
 */
#define R_RES_SUB_ID_FUNCTION_STRINGS           5
/**
 * The mapping of signatures - cryptographic module.
 */
#define R_RES_SUB_ID_MAP                        6
/**
 * The protocol version 2 server - SSL module.
 */
#define R_RES_SUB_ID_SSL2_SERVER                7
/**
 * The protocol version 2 client - SSL module.
 */
#define R_RES_SUB_ID_SSL2_CLIENT                8
/**
 * The protocol version 2 client and/or server - SSL module.
 */
#define R_RES_SUB_ID_SSL2_BOTH                  9
/**
 * The protocol version 3 server - SSL module.
 */
#define R_RES_SUB_ID_SSL3_SERVER                10
/**
 * The protocol version 3 client - SSL module.
 */
#define R_RES_SUB_ID_SSL3_CLIENT                11
/**
 * The protocol version 3 client and/or server - SSL module.
 */
#define R_RES_SUB_ID_SSL3_BOTH                  12
/**
 * The protocol version tls1 server - SSL module.
 */
#define R_RES_SUB_ID_TLS1_SERVER                13
/**
 * The protocol version tls1 client - SSL module.
 */
#define R_RES_SUB_ID_TLS1_CLIENT                14
/**
 * The protocol version tls1 client and/or server - SSL module.
 */
#define R_RES_SUB_ID_TLS1_BOTH                  15
/**
 * The protocol version 2 or 3 server - SSL module.
 */
#define R_RES_SUB_ID_SSL23_SERVER               16
/**
 * The protocol version 2 or 3 client - SSL module.
 */
#define R_RES_SUB_ID_SSL23_CLIENT               17
/**
 * The protocol version 2 or 3 client and/or server - SSL module.
 */
#define R_RES_SUB_ID_SSL23_BOTH                 18

/**
 * @defgroup RES_FLAG Flags
 * This section outlines the flag values used to determine the scope in which
 * the module can be used.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */
/**
 * Matches any flag.
 */
#define R_RES_FLAG_ANY                          (-1)
/**
 * Indicates the default flag. Reserved for future use.
 */
#define R_RES_FLAG_DEF                          0
/*
 * Indicates the global use flag.
 */
#define R_RES_FLAG_GLOBAL                       0
/*
 * Indicates the shareable when no locking required flag.
 */
#define R_RES_FLAG_SHARED                       1
/*
 * Indicates the exclusive use only flag.
 */
#define R_RES_FLAG_PRIVATE                      2

/**
 * @}
 */

/* General types of resources */
/**
 * Matches any type.
 */
#define R_RES_TYPE_ANY                          0
/**
 * Indicates anonymous data function pointer.
 */
#define R_RES_TYPE_DATA                         1
/**
 * Indicates the table of methods function pointer.
 */
#define R_RES_TYPE_METHS                        2
/**
 * Indicates the function to call on startup of library.
 */
#define R_RES_TYPE_START                        3
/**
 * Indicates the function to call when library is finished.
 */
#define R_RES_TYPE_FINISH                       4
/**
 * Indicates anonymous data initialized value.
 */
#define R_RES_TYPE_DATA_INIT                    5
/**
 * Indicates the table of methods initialized value.
 */
#define R_RES_TYPE_METHS_INIT                   6

/**
 * Indicates to prepend the resource list item.
 */
#define R_RES_LIST_ACTION_PREPEND               0
/**
 * Indicates to append the resource list item.
 */
#define R_RES_LIST_ACTION_APPEND                1
/**
 * Indicates to replace the existing resource list item.
 */
#define R_RES_LIST_ACTION_REPLACE               2
/**
 * Indicates to remove the existing resource list item.
 */
#define R_RES_LIST_ACTION_REMOVE                3

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_DATA_R_MODID_H */


