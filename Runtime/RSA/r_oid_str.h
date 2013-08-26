/* $Id: r_oid_str.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_oid_str.h
 * This file contains the functionality that manages the certificate
 * Object Identifier (OID).
 */
 
#ifndef HEADER_COMMON_R_OID_STR_H
#define HEADER_COMMON_R_OID_STR_H

#ifdef  __cplusplus
extern "C" {
#endif




/**
 * @defgroup NAME_FORMAT Distinguished Name Format
 * This section defines the Distinguished Name (DN) format identifiers.
 * The identifiers are used in converting ASN.1 Object Identifiers (OID)
 * for a DN to a string.
 * @ingroup CERT_IDENTIFIER
 * @{
 */

/** 
 * Indicates the format of an Object Identifier (OID) when represented 
 * as a string.
 */
typedef int R_OID_FORMAT;

/**
 * Indicates a long format name. The long format is a human readable string for
 * the Object Identifier (OID) value.
 */
#define R_OID_FORMAT_LONG_NAME       0

/**
 * Indicates a short format name. The short format is a string for the Object 
 * Identifier (OID) value that has been abbreviated. This format is useful when
 * displaying a number of Object Identifiers (OIDs) on the one line, such as when
 * displaying a certificate name.
 */
#define R_OID_FORMAT_SHORT_NAME      1

/**
 * Indicates a dotted number format. The dotted format is the ASN.1 standard's
 * number or value format with periods separating each number.
 */
#define R_OID_FORMAT_DOTTED_NUMBER   2

/**
 * @}
 */

#ifndef HEADER_COMMON_R_CERT_NAME_ENTRY_TYPEDEF_DEF
#define HEADER_COMMON_R_CERT_NAME_ENTRY_TYPEDEF_DEF
/** Indicates the type of certificate name type. */
typedef int R_CERT_NAME_ENTRY_TYPE;
#endif /* HEADER_COMMON_R_CERT_NAME_ENTRY_TYPEDEF_DEF */

/** Indicates that the #R_OID structure was dynamically allocated. */
#define R_OID_DYNAMIC_OID   0x0001
/** Indicates that R_OID.data was dynamically allocated. */
#define R_OID_DYNAMIC_DATA  0x0002

/** Indicates the type of an object identifier.  */
typedef struct r_oid_st R_OID;
/** The data structure of an object identifier. */
struct r_oid_st
{
    /** Indicates the library context used to create the #R_OID. */
    R_LIB_CTX *lib_ctx;

    /** A pointer to the Object Identifier (OID) value */
    unsigned char *data;

    /** The length of the Object Identifier (OID) value */
    unsigned int len;

    /** Indicates whether #R_OID and/or R_OID.data should be freed. */
    int flag;
};

/**
 * @defgroup CERT_OID_FUNCS Object Identifier Functions
 * This section details the functions that manage ASN.1 Object 
 * Identifiers (OIDs).
 * @ingroup CERT_ALL_FUNCS
 * @{
 */

/** 
 * @fn int R_OID_init_with_constant(R_OID *oid, char *constant)
 * 
 * Initializes an #R_OID with an <tt>R_OID_*</tt> constant.
 *
 * @param oid      [In] The Object Identifier (OID).
 * @param constant [In] The OID's numerical reference.
 *
 * @return              #R_ERROR_NONE indicates success.<br>
 *                      See @ref R_ERROR_IDS for valid values.
 */
#define R_OID_init_with_constant(oid, oid_constant) \
    R_OID_init(oid, R_FLAG_COPY_BY_REFERENCE, \
               (unsigned char *)(oid_constant), \
               sizeof(oid_constant)-1)

int R_OID_new(R_LIB_CTX *lib_ctx, R_OID **oid);
int R_OID_free(R_OID *oid);
int R_OID_init(R_OID *oid, int flag, unsigned char *data, unsigned int len);

int R_OID_to_string(R_OID *oid, R_OID_FORMAT format,
    unsigned int max_str_len, char *str);

int R_OID_from_string(R_LIB_CTX *lib_ctx, R_OID_FORMAT format, char *str,
    R_OID **oid);

int r_oid_to_dotted_string(unsigned char *oid_data, unsigned int oid_len,
                           unsigned int max_str_len, char *str);
int r_dotted_str_to_oid(unsigned char *type_str, unsigned int type_len,
                        unsigned char **oid_data, unsigned int *oid_len);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_OID_STR_H */
