/* $Id: r_skey.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file contains defines and structures for symmetric key
 * manipulation.
 */

#ifndef HEADER_COMMON_R_SKEY_H
#define HEADER_COMMON_R_SKEY_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"
#include "r_lib.h"

/**
 * @defgroup SKEY_GROUP Symmetric Key Operations
 * This section details the functions that facilitate symmetric key
 * processing, as well as providing details of symmetric key types and
 * outlining the identifiers used to retrieve symmetric key information.
 * @ingroup KEYS_GROUP
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup SKEY_INFO_GROUP Symmetric Key Identifiers and Flags
 * This section details of symmetric key types and outlines
 * the identifiers used to retrieve symmetric key information.
 * @ingroup SKEY_GROUP
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup SKEY_TYPE Types
 * This section details the symmetric key types that #R_SKEY can handle.
 * @ingroup SKEY_INFO_GROUP
 * @{
 */

/** Indicates that the type of symmetric key is unknown. */
#define R_SKEY_TYPE_UNKNOWN                 (-1)
/** Indicates that the type of symmetric key is in raw binary (generic) form.
 */
#define R_SKEY_TYPE_GENERIC                 1

/**
 * @}
 */

/**
 * @defgroup SKEY_ID Information Identifiers
 * This section outlines the identifiers that can be used to obtain
 * symmetric key information.
 * Pass the identifier #R_SKEY_INFO_ID_VALUE with a data type of #R_ITEM *
 * into <i>param</i> when calling R_SKEY_get_info().<br>
 * The following table details the data types to pass into <i>param</i> when
 * calling R_SKEY_get_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_SKEY_INFO_ID_VALUE</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_SKEY_INFO_ID_VALUE_LEN</td>
 *     <td>#R_ITEM *</td>
 * </tr></table>
 * @br
 * The following table details the data types to pass into <i>param</i> when
 * calling R_PKEY_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_SKEY_INFO_ID_VALUE</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_SKEY_INFO_ID_VALUE_LEN</td>
 *     <td>#R_ITEM *</td>
 * </tr></table>
 * @br
 * @ingroup SKEY_INFO_GROUP
 * @{
 */

/* Handle for storing the key's identifier */
#define R_SKEY_INFO_ID_KEY_ID		1
/* Handle for storing whether the key is to be permantently kept on the 
 * token. 
 */
#define R_SKEY_INFO_ID_IS_TOKEN		2
/* Handle for storing the key's label */
#define R_SKEY_INFO_ID_LABEL		3
/* Handle for storing the key's class */
#define R_SKEY_INFO_ID_CLASS		4
/* Handle for storing the key's wrap authority */
#define R_SKEY_INFO_ID_KEY_WRAP		5
/* Handle for storing the key's unwrap authority */
#define R_SKEY_INFO_ID_KEY_UNWRAP	6
/* Handle for storing the key's sensitive indicator */
#define R_SKEY_INFO_ID_KEY_SENSITIVE	7
/* Handle for storing the key's extractable indicator */
#define R_SKEY_INFO_ID_KEY_EXTRACTABLE	8
/* Handle for storing the key's type */
#define R_SKEY_INFO_ID_KEY_TYPE		9
/* Handle for storing the key's encrypt permission */
#define R_SKEY_INFO_ID_ENCRYPT		10
/* Handle for storing the key's decrypt permission */
#define R_SKEY_INFO_ID_DECRYPT		11
/* Handle for storing the key's verify permission */
#define R_SKEY_INFO_ID_VERIFY		12
/* Handle for storing the key's sign permission */
#define R_SKEY_INFO_ID_SIGN		13
/** Identifies the raw (i.e. binary) key data. */
#define R_SKEY_INFO_ID_VALUE		14
/** Identifies the length of the raw (i.e. binary) key data. */
#define R_SKEY_INFO_ID_VALUE_LEN	15
/* Handle for storing the key's Hardware device handle */
#define R_SKEY_INFO_ID_HW_HANDLE	16
/* Handle for storing the key's special storage attributes */
#define R_SKEY_INFO_ID_ATTRIBUTES	17

/**
 * @}
 */

/** This opaque structure is used for symmetric key storage. */
typedef struct r_skey_st                    R_SKEY;

/** This opaque structure is used for symmetric key methods storage. */
typedef struct r_skey_method_st             R_SKEY_METHOD;

/**
 * @defgroup SKEY_ALL_FUNCS Operation Functions
 * This section details the functions which facilitate symmetric key
 * cryptography.
 * @ingroup SKEY_GROUP
 * @{
 */

int R_SKEY_new(R_LIB_CTX *ctx, int key_type, R_ITEM *key_descriptor,
    R_SKEY **new_skey);
int R_SKEY_free(R_SKEY *skey);
int R_SKEY_get_info(R_SKEY *skey, int id, void *param);
int R_SKEY_set_info(R_SKEY *skey, int id, void *param);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SKEY_H */

