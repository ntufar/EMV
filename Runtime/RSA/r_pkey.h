/* $Id: r_pkey.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/** @file  r_pkey.h
 *  This file contains structures, defines and function prototypes
 *  for public and private key operations.
 */

#ifndef HEADER_COMMON_CERT_R_PKEY_H
#define HEADER_COMMON_CERT_R_PKEY_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_lib.h"
#include "r_types.h"
#include "pk_ids.h"
#include "r_pkey_err.h"
#include "r_format.h"

#ifndef NO_BIO
#include "bio.h"
#endif /* NO_BIO */
/**
 * @defgroup KEYS_GROUP Key Operations
 * This section outlines the keys used in cryptographic operations and
 * certificate processing. There are two main types of keys:<br>
 * <li>Asymmetric (public and private).</li>
 * <li>Symmetric.</li>
 * 
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup PKEY_GROUP Asymmetric Key Operations
 * This section provides information on the functions that perform asymmetric
 * (public and private) key processing. It details how to retrieve information
 * on identifiers and fields, and how to set print and format options.
 * @ingroup KEYS_GROUP
 *
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup PKEY_INFO_GROUP Asymmetric Key Identifiers and Flags
 * This section detail the public key information identifiers and flags
 * that #R_PKEY can handle.
 * @ingroup PKEY_GROUP
 *
 * @{
 */
/**
 * @}
 */


/*
 * Exported macro constants
 */

/**
 * @defgroup PKEY_TYPE Types
 * This section details the public key types that #R_PKEY can handle.
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

/*
 * There are definitions for a PKEY type used in R_PKEY_from_binary()
 * which are deliberately compatible with the defines used for the 
 * @ref EVP_PKEY types in older implementations .
 *
 * That is the values are the same as @ref EVP_PKEY_RSA, @ref EVP_PKEY_DSA and
 * @ref EVP_PKEY_DH.
 *
 */
/**
 * Indicates the type used to identify an allocated #R_PKEY. An #R_PKEY
 * may contain either a public or private key for the nominated type of key
 * allocated.
 */
typedef int R_PKEY_TYPE;
/**
 * Indicates that the <tt>PKEY</tt> type is unknown.
 */
#define R_PKEY_TYPE_UNKNOWN  -1
/**
 * Indicates that the <tt>PKEY</tt> type is RSA.
 */
#define R_PKEY_TYPE_RSA       6
/**
 * Indicates that the <tt>PKEY</tt> type is Diffie-Hellman.
 */
#define R_PKEY_TYPE_DH        28
/**
 * Indicates that the <tt>PKEY</tt> type is Digital Signature Algorithm (DSA).
 */
#define R_PKEY_TYPE_DSA       116
/**
 * Indicates that the <tt>PKEY</tt> type is Digital Signature Algorithm (DSA)
 * parameters.
 */
#define R_PKEY_TYPE_DSAPARAMS  1001
/**
 * Indicates that the <tt>PKEY</tt> type is Elliptic Curve Cryptography (ECC).
 */
#define R_PKEY_TYPE_ECC       178

/**
 * @}
 */

/**
 * @defgroup PKEY_FLAGS Flags
 * This section outlines the flags associated with a public key structure.
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

/*
 * Defines for flags used in the _from_binary calls.
 *
 * NOTE: the flag values for both R_CERT and R_PKEY are the same.
 *
 */
/**
 * Indicates default data referencing.
 */
#define R_PKEY_FL_DEFAULT          0x0000
/**
 * Indicates to copy data.
 */
#define R_PKEY_FL_COPY_DATA        0x0000
/**
 * Indicates to use data by reference.
 */
#define R_PKEY_FL_BY_REFERENCE     0x0001

/**
 * @}
 */

/**
 * @defgroup PKEY_FORMATS Formats
 * This section outlines the formats of public key data that can be
 * interpretted.
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

/**
 * Indicates the format used to encode the data of a key.
 */
typedef int R_PKEY_FORMAT;

/** Indicates that the key data is binary encoded. */
#define R_PKEY_FORMAT_BINARY            R_FORMAT_BINARY

/** Indicates that the key data is Privacy Enhanced Mail (PEM) encoded. */
#define R_PKEY_FORMAT_PEM               R_FORMAT_PEM

/** Indicates the key data is in PKCS #1 format. */
#define R_PKEY_FORMAT_PKCS1             (0x0000 | R_FORMAT_BINARY)

/** Indicates the key data is in PKCS #8 format. */
#define R_PKEY_FORMAT_PKCS8             (0x0001 | R_FORMAT_BINARY)

/**
 * @}
 */

/* Indicates that the <tt>PKEY</tt> is in text format. */
#define R_PKEY_FORMAT_TEXT              R_FORMAT_TEXT

/* Indicates text output format. */
#define R_PKEY_PRINT_FORMAT_TEXT        R_FORMAT_TEXT

/* Indicates C code function format.  */
#define R_PKEY_PRINT_FORMAT_CODE_BINARY R_FORMAT_CODE_BINARY

/* Indicates C code fields format.  */
#define R_PKEY_PRINT_FORMAT_CODE_FIELDS R_FORMAT_CODE_FIELDS

/* Indicates C code data format. */
#define R_PKEY_PRINT_FORMAT_CODE_HEX    R_FORMAT_CODE_HEX

/* Indicates plain hexadecimal Bytes format. */
#define R_PKEY_PRINT_FORMAT_HEX         R_FORMAT_HEX

/* Indicates the key is in public key information block format. */
#define R_PKEY_FORMAT_PUBKEY_INFO       (0x0002 | R_FORMAT_BINARY)

#ifndef NO_PEM
/**
 * @defgroup PKEY_PEM Privacy Enhanced Mail Cipher Strings
 * This section details the strings recognized by #R_PKEY as ciphers to use
 * when encrypting a Privacy Enhanced Mail (PEM) file. 
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

/* supported PEM cipher strings for encrypted keys */
/**
 * Indicates a Privacy Enhanced Mail (PEM) cipher in Data Encryption Standard
 * Cipher Block Chaining (DES CBC) mode.
 */
#define R_PKEY_PEM_CIPHER_DES           "DES-CBC"
/**
 * Indicates a Privacy Enhanced Mail (PEM) cipher in Triple Data Encryption
 * Standard Cipher Block Chaining (DES CBC) mode.
 */
#define R_PKEY_PEM_CIPHER_DES_EDE       "DES-EDE3-CBC"

/**
 * @}
 */
#endif /* NO_PEM */

/*
 * @defgroup PKEY_FIELD Fields
 * This section outlines the fields of a public key recognized by #R_PKEY.
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

/* ID values for R_PKEY_get_field - defines come from pk_ids.h */
/*
 * Indicates that the data is the modulus (<tt>n</tt>) of the RSA key. The 
 * modulus is the product of the primes.
 */
#define R_PKEY_FIELD_ID_RSA_MOD         PK_RSA_N
/*
 * Indicates that the data is the public exponent (<tt>e</tt>) of the RSA key. 
 * The public exponent is often <tt>65537 (0x10001)</tt> which allows fast 
 * exponentiation calculating.
 */
#define R_PKEY_FIELD_ID_RSA_EXP         PK_RSA_E
/* Indicates that the data is the private exponent (<tt>d</tt>) of the RSA 
 *  key. The private exponent is the inverse of the public exponent
 *  (<tt>e.d=1 mod (p-1)(q-1)...</tt>).
 */
#define R_PKEY_FIELD_ID_RSA_PRIV_EXP    PK_RSA_D
/* Indicates that the data is the <tt>nth</tt> prime of the RSA key. */
#define R_PKEY_FIELD_ID_RSA_PRIME_N(n)    PK_RSA_PRIME(n)
/* Indicates that the data is the <tt>nth</tt> exponent calculation of the 
 *  RSA key. The calculation is the private exponent <tt>mod prime - 1</tt>
 *  and is a pre-calculation used in a Chinese Remainder Theorem 
 *  implementation of the private key operations.
 */
#define R_PKEY_FIELD_ID_RSA_EXP_N(n)      PK_RSA_EXP(n)
/* Indicates that the data is the <tt>nth</tt> inverse calculation of the 
 *  RSA key. The calculation is the inverse of the previous prime mod this 
 *  prime (<tt>inv(q) mod p</tt>) and is a pre-calculation used in a Chinese
 *  Remainder Theorem implementation of the private key operations.
 */
#define R_PKEY_FIELD_ID_RSA_INV_N(n)      PK_RSA_INV(n)
/* Indicates that the data is the first subprime for the nth prime of the RSA
 *  key.
 */
#define R_PKEY_FIELD_ID_RSA_SUBPRIME1_N(n) PK_RSA_SUBPRIME1(n)
/* Indicates that the data is the second subprime for the nth prime of the RSA
 *  key.
 */
#define R_PKEY_FIELD_ID_RSA_SUBPRIME2_N(n) PK_RSA_SUBPRIME2(n)
/* Indicates that the data is the first prime (<tt>q</tt>) of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_Q           PK_RSA_Q
/* Indicates that the data is the first exponent calculation of the RSA key.
 *  The calculation is the private exponent <tt>mod (q-1)</tt> and is a
 *  pre-calculation used in a Chinese Remainder Theorem implementation
 *  of the private key operations.
 */
#define R_PKEY_FIELD_ID_RSA_DMQ1        PK_RSA_DMQ1
/* Indicates that the data is the first subprime (<tt>q1</tt>) for the first
 *  prime q of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_Q1          PK_RSA_Q1
/* Indicates that the data is the second subprime (<tt>q2</tt>) for the first
 *  prime q of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_Q2          PK_RSA_Q2
/* Indicates that the data is the second prime (<tt>p</tt>) of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_P           PK_RSA_P
/* Indicates that the data is the second exponent calculation of the RSA key.
 *  The calculation is the private exponent <tt>mod (p-1)</tt> and is a
 *  pre-calculation used in a Chinese Remainder Theorem implementation
 *  of the private key operations.
 */
#define R_PKEY_FIELD_ID_RSA_DMP1        PK_RSA_DMP1
/* Indicates that the data is the second inverse calculation of the RSA key.
 *  The calculation is the inverse of the previous prime <tt>mod</tt> this
 *  prime (<tt>inv(q) mod p</tt>) and is a pre-calculation used in a
 *  Chinese Remainder Theorem implementation of the private key operations.
 */
#define R_PKEY_FIELD_ID_RSA_IQMP        PK_RSA_IQMP
/* Indicates that the data is the first subprime (<tt>p1</tt>) for the second
 *  prime p of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_P1          PK_RSA_P1
/* Indicates that the data is the second subprime (<tt>p2</tt>) for the second
 *  prime p of the RSA key.
 */
#define R_PKEY_FIELD_ID_RSA_P2          PK_RSA_P2
/*
 * Indicates that the data is the prime parameter of the Diffie-Hellman key.
 * The prime value identifies the Galois field (<tt>p=jq+1</tt>).
 */
#define R_PKEY_FIELD_ID_DH_PRIME        PK_DH_PRIME
/*
 * Indicates that the data is the public key value of the Diffie-Hellman key.
 * The public key is calculated by raising the generator to a
 * random value <tt>mod p (y=g^x mod p)</tt>.
 */
#define R_PKEY_FIELD_ID_DH_GENERATOR    PK_DH_GENERATOR
/*
 * Indicates that the data is the public key value of the Diffie-Hellman key. 
 * The public key is calculated by raising the generator to a random value 
 * <tt>mod p (y=g^x mod p)</tt>.
 */
#define R_PKEY_FIELD_ID_DH_PUB_KEY      PK_DH_PUB_KEY
/*
 * Indicates that the data is the private key value of the Diffie-Hellman key.
 */
#define R_PKEY_FIELD_ID_DH_PRIV_KEY     PK_DH_PRIV_KEY

/* Indicates that the data is the prime modulus parameter <tt>(p)</tt> of the
 *  DSA key. The prime modulus identifier is between <tt>2^(L-1)</tt> and
 *  <tt>2^L</tt> for <tt>L</tt> in the range <tt>512-1024</tt> and is a
 *  multiple of <tt>64</tt>.
 */
#define R_PKEY_FIELD_ID_DSA_PRIME       PK_DSA_P

/* Indicates that the data is the sub-prime/prime divisor parameter
 *  <tt>(q)</tt>of the DSA key. The sub-prime is a prime divisor of the
 *  <tt>prime - 1</tt> between <tt>2^159</tt> and <tt>2^160</tt>.
 */
#define R_PKEY_FIELD_ID_DSA_SUBPRIME    PK_DSA_Q

/* Indicates that the data is the base/generator parameter <tt>(g)</tt>
 *  of the DSA key. The base/generator is used as the exponential base for
 *  DSA calculations <tt>g = h^[(p-1)/q]</tt>.
 */
#define R_PKEY_FIELD_ID_DSA_BASE        PK_DSA_G

/* Indicates that the data is the public key value <tt>(y)</tt> of the DSA
 *  key. The public key is the base/generator value raised to the private 
 *  key part <tt>mod p (y=g^x mod p)</tt>.
 */
#define R_PKEY_FIELD_ID_DSA_PUB_KEY     PK_DSA_PUB_KEY

/* Indicates that the data is the private key value <tt>(x)</tt> of the DSA
 *  key. The private key is a randomly or pseudo-randomly generated integer 
 *  between <tt>0</tt> and the sub-prime/divisor. The private key is the
 *  exponent to which the base generator is raised to obtain the public key 
 *  part <tt>(y=g^x mod p)</tt>.
 */
#define R_PKEY_FIELD_ID_DSA_PRIV_KEY    PK_DSA_PRIV_KEY

/* Indicates that the data is the seed used in the generation of the DSA key. 
 *  The value of the seed is retained for use in certifying the proper
 *  generation of p and q.
 */
#define R_PKEY_FIELD_ID_DSA_SEED        PK_DSA_SEED

/* Indicates that the data is the counter used in the generation of the prime 
 *  modulus parameter <tt>(p)</tt> of the DSA key. The value of the counter is
 *  retained for use in certifying the proper generation of p.
 */
#define R_PKEY_FIELD_ID_DSA_COUNTER     PK_DSA_COUNTER

/* Indicates that the data is the value <tt>(h)</tt> used to generate the
 *  base/generator parameter g of the DSA key. The value of h is
 *  retained for use in certifying the proper generation of g.
 */
#define R_PKEY_FIELD_ID_DSA_H           PK_DSA_H


#define R_PKEY_FIELD_ID_ECC_OID          PK_ECC_OID
#define R_PKEY_FIELD_ID_ECC_PARAMS       PK_ECC_PARAMS
#define R_PKEY_FIELD_ID_ECC_PUB_KEY      PK_ECC_PUB_KEY
/**
 * @}
 */

/* Indicates that the R_PKEY field has no type */
#define R_PKEY_FIELD_TYPE_NONE          0

/* Indicates that the R_PKEY field is an integer */
#define R_PKEY_FIELD_TYPE_INT           1

/* Indicates that the R_PKEY field is an R_ITEM */
#define R_PKEY_FIELD_TYPE_ITEM          2

/**
 * @defgroup PKEY_INFO Information Identifiers
 * This section lists the identifiers used to set and/or retrieve information 
 * from an #R_PKEY.
 * The following table details the data types to pass into <i>param</i> when
 * calling R_PKEY_get_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_MOD</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_EXP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_PRIV_EXP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_PRIME_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_EXP_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_INV_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_Q</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_DMQ1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_Q1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_Q2</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_P</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_DMP1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_IQMP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_P1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_P2</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_GENERATOR</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PUB_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PRIV_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_SUBPRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_BASE</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PUB_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PRIV_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_SEED</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_COUNTER</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_H</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_R_PKEY_CTX</td>
 *     <td>#R_PKEY_CTX **</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_R_EITEMS</td>
 *     <td>#R_EITEMS **</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_FLAG</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DATA</td>
 *     <td><tt>void **</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_REFERENCE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_TYPE</td>
 *     <td>#R_PKEY_TYPE *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_NUM_BITS</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_NUM_PRIMES</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * The following table details the data types to pass into <i>param</i> when
 * calling R_PKEY_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_MOD</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_EXP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_PRIV_EXP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_PRIME_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_EXP_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_INV_N</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_Q</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_DMQ1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_Q1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_Q2</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_P</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_DMP1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_IQMP</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_P1</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_RSA_X931_P2</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_GENERATOR</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PUB_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DH_PRIV_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_SUBPRIME</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_BASE</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PUB_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_PRIV_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_SEED</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_COUNTER</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_DSA_H</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_PKEY_INFO_ID_NUM_PRIMES</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 * @ingroup PKEY_INFO_GROUP
 * @{
 */

#define R_PKEY_INFO_ID_BASE           2000
/**
 * This identifier is used for the retrieval of the RSA modulus associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_MOD.
 */
#define R_PKEY_INFO_ID_RSA_MOD        R_PKEY_FIELD_ID_RSA_MOD
/**
 * This identifier is used for the retrieval of the RSA exponent associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_EXP.
 */
#define R_PKEY_INFO_ID_RSA_EXP        R_PKEY_FIELD_ID_RSA_EXP
/**
 * This identifier is used for the retrieval of the RSA private exponent
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_PRIV_EXP.
 */
#define R_PKEY_INFO_ID_RSA_PRIV_EXP   R_PKEY_FIELD_ID_RSA_PRIV_EXP
/**
 * This identifier is used for the retrieval of the <tt>nth</tt> RSA prime 
 * associated with the #R_PKEY. To retrieve this value the parameter 
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_PRIME_N.
 */
#define R_PKEY_INFO_ID_RSA_PRIME_N(n)   R_PKEY_FIELD_ID_RSA_PRIME_N(n)
/**
 * This identifier is used for the retrieval of the <tt>nth</tt> RSA exponent 
 * associated with the #R_PKEY. To retrieve this value the parameter 
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_EXP_N.
 */
#define R_PKEY_INFO_ID_RSA_EXP_N(n)     R_PKEY_FIELD_ID_RSA_EXP_N(n)
/**
 * This identifier is used for the retrieval of the associated RSA inverse 
 * associated with the #R_PKEY. To retrieve this value the parameter 
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_INV_N.
 */
#define R_PKEY_INFO_ID_RSA_INV_N(n)     R_PKEY_FIELD_ID_RSA_INV_N(n)
/**
 * This identifier is used for the retrieval of the first RSA prime associated
 * with the #R_PKEY. To retrieve this value the parameter reference should
 * be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_Q.
 */
#define R_PKEY_INFO_ID_RSA_Q          R_PKEY_FIELD_ID_RSA_Q
/**
 * This identifier is used for the retrieval of the first RSA exponent
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_DMQ1.
 */
#define R_PKEY_INFO_ID_RSA_DMQ1       R_PKEY_FIELD_ID_RSA_DMQ1
/**
 * This identifier is used for the retrieval of the first RSA X9.31 subprime 1
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_Q1.
 */
#define R_PKEY_INFO_ID_RSA_X931_Q1    R_PKEY_FIELD_ID_RSA_Q1
/**
 * This identifier is used for the retrieval of the first RSA X9.31 subprime 2
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_Q2.
 */
#define R_PKEY_INFO_ID_RSA_X931_Q2    R_PKEY_FIELD_ID_RSA_Q2
/**
 * This identifier is used for the retrieval of the second RSA prime associated
 * with the #R_PKEY. To retrieve this value the parameter reference should
 * be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_P.
 */
#define R_PKEY_INFO_ID_RSA_P          R_PKEY_FIELD_ID_RSA_P
/**
 * This identifier is used for the retrieval of the second RSA exponent
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_DMP1.
 */
#define R_PKEY_INFO_ID_RSA_DMP1       R_PKEY_FIELD_ID_RSA_DMP1
/**
 * This identifier is used for the retrieval of the second RSA inverse
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_IQMP.
 */
#define R_PKEY_INFO_ID_RSA_IQMP       R_PKEY_FIELD_ID_RSA_IQMP
/**
 * This identifier is used for the retrieval of the second RSA X9.31 subprime 1
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_P1.
 */
#define R_PKEY_INFO_ID_RSA_X931_P1    R_PKEY_FIELD_ID_RSA_P1
/**
 * This identifier is used for the retrieval of the second RSA X9.31 subprime 2
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and #R_PKEY_FIELD_ID_RSA_P2.
 */
#define R_PKEY_INFO_ID_RSA_X931_P2    R_PKEY_FIELD_ID_RSA_P2
/**
 * This identifier is used for the retrieval of the Diffie-Hellman prime
 * value associated with the #R_PKEY. To retrieve this value the parameter
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and 
 * #R_PKEY_FIELD_ID_DH_PRIME.
 */
#define R_PKEY_INFO_ID_DH_PRIME       R_PKEY_FIELD_ID_DH_PRIME
/**
 * This identifier is used for the retrieval of the Diffie-Hellman parameter
 * value associated with the #R_PKEY. To retrieve this value the parameter
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DH_GENERATOR.
 */
#define R_PKEY_INFO_ID_DH_GENERATOR   R_PKEY_FIELD_ID_DH_GENERATOR
/**
 * This identifier is used for the retrieval of the Diffie-Hellman public
 * key associated with the #R_PKEY. To retrieve this value the parameter
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info()
 *      and #R_PKEY_FIELD_ID_DH_PUB_KEY.
 */
#define R_PKEY_INFO_ID_DH_PUB_KEY     R_PKEY_FIELD_ID_DH_PUB_KEY
/**
 * This identifier is used for the retrieval of the Diffie-Hellman private
 * key associated with the #R_PKEY. To retrieve this value the parameter
 * reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info()
 *      and #R_PKEY_FIELD_ID_DH_PRIV_KEY.
 */
#define R_PKEY_INFO_ID_DH_PRIV_KEY     R_PKEY_FIELD_ID_DH_PRIV_KEY
/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) prime associated with the #R_PKEY. To retrieve this
 * value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_PRIME.
 */
#define R_PKEY_INFO_ID_DSA_PRIME      R_PKEY_FIELD_ID_DSA_PRIME
/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) sub-prime associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_SUBPRIME.
 */
#define R_PKEY_INFO_ID_DSA_SUBPRIME   R_PKEY_FIELD_ID_DSA_SUBPRIME
/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) base associated with the #R_PKEY. To retrieve this 
 * value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info()
 * and #R_PKEY_FIELD_ID_DSA_BASE.
 */
#define R_PKEY_INFO_ID_DSA_BASE       R_PKEY_FIELD_ID_DSA_BASE
/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) public key associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_PUB_KEY.
 */
#define R_PKEY_INFO_ID_DSA_PUB_KEY    R_PKEY_FIELD_ID_DSA_PUB_KEY

/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) private key associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_PRIV_KEY.
 */
#define R_PKEY_INFO_ID_DSA_PRIV_KEY             R_PKEY_FIELD_ID_DSA_PRIV_KEY

/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) seed associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_SEED.
 */
#define R_PKEY_INFO_ID_DSA_SEED             R_PKEY_FIELD_ID_DSA_SEED

/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) counter associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as
 * cast <tt>int *</tt>.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_COUNTER.
 */
#define R_PKEY_INFO_ID_DSA_COUNTER             R_PKEY_FIELD_ID_DSA_COUNTER

/**
 * This identifier is used for the retrieval of the Digital Signature 
 * Algorithm (DSA) h value associated with the #R_PKEY. To retrieve
 * this value the parameter reference should be passed in as cast #R_ITEM *.
 *
 * @see R_PKEY_get_info(), R_PKEY_set_info() and
 *      #R_PKEY_FIELD_ID_DSA_H.
 */
#define R_PKEY_INFO_ID_DSA_H             R_PKEY_FIELD_ID_DSA_H

/**
 * This identifier is used for the retrieval of the #R_PKEY_CTX associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast #R_PKEY_CTX **.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_R_PKEY_CTX     (R_PKEY_INFO_ID_BASE+1)
/**
 * This identifier is used for the retrieval of the #R_EITEMS associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast #R_EITEMS **.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_R_EITEMS       (R_PKEY_INFO_ID_BASE+2)
/**
 * This identifier is used for the retrieval of the flags associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast <tt>int *</tt>.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_FLAG           (R_PKEY_INFO_ID_BASE+3)
/**
 * This identifier is used for the retrieval of the implementation data
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast <tt>void **</tt>.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_DATA           (R_PKEY_INFO_ID_BASE+4)
/**
 * This identifier is used for the retrieval of the reference count associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast <tt>int *</tt>.
 *
 * @see R_PKEY_get_info() and R_PKEY_reference_inc().
 */
#define R_PKEY_INFO_ID_REFERENCE      (R_PKEY_INFO_ID_BASE+5)
/**
 * This identifier is used for the retrieval of the #R_PKEY_TYPE 
 * associated with the #R_PKEY. To retrieve this value the parameter reference
 * should be passed in as cast #R_PKEY_TYPE *.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_TYPE           (R_PKEY_INFO_ID_BASE+6)
/**
 * This identifier is used for the retrieval of the number of bits associated
 * with the #R_PKEY. To retrieve this value the parameter reference should be
 * passed in as cast <tt>int *</tt>.
 *
 * @see R_PKEY_get_info().
 */
#define R_PKEY_INFO_ID_NUM_BITS        (R_PKEY_INFO_ID_BASE+7)
/**
 * This identifier is used for the retrieval of the number of primes 
 * associated with the #R_PKEY. This is valid for two prime and MultiPrime
 * keys. To retrieve this value the parameter reference should be passed in
 * as cast <tt>int *</tt>.
 *
 * @see R_PKEY_get_info() and R_PKEY_set_info().
 */
#define R_PKEY_INFO_ID_NUM_PRIMES     (R_PKEY_INFO_ID_BASE+8)

/**
 *  This identifier is used to access the Hardware Identifier for persistant Key Objects
 *  from a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_KEY_ID           (R_PKEY_INFO_ID_BASE+50)
/**
 *  This identifier is used for the retrieval of Hardware Object attributes
 */
#define R_PKEY_INFO_ID_ATTRIBUTES	(R_PKEY_INFO_ID_BASE+51)
/*
 *
 */
#define R_PKEY_INFO_ID_HW_HANDLE        (R_PKEY_INFO_ID_BASE+53)
/*
 *  This identifier is used to locate a private key handle in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_HW_PRIVATE_HANDLE  (R_PKEY_INFO_ID_BASE+54)
/*
 *  This identifier is used to locate a public key handle in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_HW_PUBLIC_HANDLE   (R_PKEY_INFO_ID_BASE+55)
/*
 *  This identifier is used to locate a class object in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_HW_CLASS		(R_PKEY_INFO_ID_BASE+56)
/*
 *  This identifier is used to locate a subject object in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_HW_SUBJECT       (R_PKEY_INFO_ID_BASE+57)
/*
 *  This identifier is used to locate export Key Encryption Key (KEK) authority
 * in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_KEY_WRAP         (R_PKEY_INFO_ID_BASE+58)
/*
 *  This identifier is used to locate import Key Encryption Key (KEK) authority
 * in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_KEY_UNWRAP       (R_PKEY_INFO_ID_BASE+59)
/*
 *  This identifier is used to locate privacy need in a <tt>PKEY</tt>.
 */
#define R_PKEY_INFO_ID_KEY_SENSITIVE    (R_PKEY_INFO_ID_BASE+60)

/* Handle for storing whether the key is to be
	permantently kept on the token. */
#define R_PKEY_INFO_ID_IS_TOKEN		(R_PKEY_INFO_ID_BASE+61)
/* Handle for storing the key's label */
#define R_PKEY_INFO_ID_HW_LABEL		(R_PKEY_INFO_ID_BASE+62)
/* Handle for storing the key's extractable indicator */
#define R_PKEY_INFO_ID_KEY_EXTRACTABLE	(R_PKEY_INFO_ID_BASE+63)
/* Handle for storing the key's type */
#define R_PKEY_INFO_ID_KEY_TYPE		(R_PKEY_INFO_ID_BASE+64)
/* Handle for storing the key's encrypt permission */
#define R_PKEY_INFO_ID_ENCRYPT		(R_PKEY_INFO_ID_BASE+65)
/* Handle for storing the key's decrypt permission */
#define R_PKEY_INFO_ID_DECRYPT		(R_PKEY_INFO_ID_BASE+66)
/* Handle for storing the key's verify permission */
#define R_PKEY_INFO_ID_VERIFY		(R_PKEY_INFO_ID_BASE+67)
/* Handle for storing the key's sign permission */
#define R_PKEY_INFO_ID_SIGN		(R_PKEY_INFO_ID_BASE+68)
/* Handle for storing the key's storage module */
#define R_PKEY_INFO_ID_HW_MODULE_INFO	(R_PKEY_INFO_ID_BASE+69)
/* Handle for storing the key's storage module unit number */
#define R_PKEY_INFO_ID_HW_MODULE_SLOT	(R_PKEY_INFO_ID_BASE+71)
/* Handle for storing the key's storage module device/sub device indicator */
#define R_PKEY_INFO_ID_HW_DEVICE_ID	(R_PKEY_INFO_ID_BASE+72)

#define R_PK_SETUP_REC(type,obj) { (type), { sizeof(obj), ((void*)(obj)) } },

typedef struct r_pkey_setup_st
{
   int	  type;
   R_ITEM object;

} R_PKEY_SETUP, *R_PKEY_SETUP_PTR;


/**
 * @}
 */

/*
 * There are opaque data types for those things for which can
 * switch the implementation routines - hence they do not really have
 * a known type as this is able to be changed at runtime.
 *
 */
#ifndef HEADER_COMMON_R_PKEY_TYPEDEF_DEF
#define HEADER_COMMON_R_PKEY_TYPEDEF_DEF
/**
 * This public key structure can contain both public and/or private key data.
 */
typedef struct r_pkey_st R_PKEY;
#endif /* HEADER_COMMON_R_PKEY_TYPEDEF_DEF */

#ifndef HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF
#define HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF
typedef struct r_eitem_st R_EITEM;      /* Extended item structure. */
typedef struct r_eitems_st R_EITEMS;    /* Extended items structure. */
#endif /* HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF */

/*
 * There is a method table (which encapsulates the functions that implement
 * the handling of all public key related functions for a particular type).
 */
/**
 * The table of methods for public keys.
 */
typedef struct r_pkey_method_st R_PKEY_METHOD;


/*
 * There is a context which holds a method and other information needed
 * for the runtime glue between routines.
 */
#ifndef HEADER_COMMON_R_PKEY_CTX_TYPEDEF_DEF
#define HEADER_COMMON_R_PKEY_CTX_TYPEDEF_DEF
/**
 * The public key context structure.
 */
typedef struct r_pkey_ctx_st R_PKEY_CTX;
#endif /* HEADER_COMMON_R_PKEY_CTX_TYPEDEF_DEF */

#include "r_pkey_m.h"

/*
 * Exported functions
 */

/**
 * @defgroup PKEY_CTX_INFO Context Information Identifiers
 * This section lists the identifiers used to set and/or retrieve information 
 * from an #R_PKEY_CTX object.
 * The following table details the data types to pass into <i>param</i> when
 * calling R_PKEY_CTX_get_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_LIB_CTX</td>
 *     <td>#R_LIB_CTX **</td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_R_PKEY_METHOD</td>
 *     <td>#R_PKEY_METHOD **</td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_CRYPTO_CTX</td>
 *     <td><tt>void **</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_FLAG</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_DATA</td>
 *     <td><tt>void **</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * The following table details the data types to pass into <i>param</i> when
 * calling R_PKEY_CTX_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_FLAG</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_PKEY_CTX_INFO_ID_DATA</td>
 *     <td><tt>void **</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 * @ingroup PKEY_INFO_GROUP
 *
 * @{
 */
/**
 * This identifier is used for the retrieval of the #R_LIB_CTX associated
 * with the #R_PKEY_CTX. To retrieve this value the parameter reference should
 * be passed in as cast #R_LIB_CTX **.
 *
 * @see R_PKEY_CTX_get_info().
 */
#define R_PKEY_CTX_INFO_ID_LIB_CTX               1
/**
 * This identifier is used for the retrieval of the #R_PKEY_METHOD associated
 * with the #R_PKEY_CTX. To retrieve this value the parameter reference should
 * be passed in as cast #R_PKEY_METHOD **.
 *
 * @see R_PKEY_CTX_get_info().
 */
#define R_PKEY_CTX_INFO_ID_R_PKEY_METHOD         2
/**
 * This identifier is used for the retrieval of the cryptographic context
 * associated with the #R_PKEY_CTX. To retrieve this value the parameter
 * reference should be passed in as cast <tt>void **</tt>.
 *
 * @see R_PKEY_CTX_get_info().
 */
#define R_PKEY_CTX_INFO_ID_CRYPTO_CTX            3
/**
 * This identifier is used for the setting or retrieval of the flags
 * associated with the #R_PKEY_CTX. To retrieve this value the parameter
 * reference should be passed in as cast <tt>int *</tt>.
 *
 * @see R_PKEY_CTX_get_info() and R_PKEY_CTX_set_info().
 */
#define R_PKEY_CTX_INFO_ID_FLAG                  4
/**
 * This identifier is used for the setting or  retrieval of the extra
 * implementation data associated with the #R_PKEY_CTX. To retrieve this value
 * the parameter reference should be passed in as cast <tt>void **</tt>.
 *
 * @see R_PKEY_CTX_get_info() and R_PKEY_CTX_set_info().
 */
#define R_PKEY_CTX_INFO_ID_DATA                  5

/**
 * @}
 */

/**
 * @defgroup PKEY_ALL_FUNCS Asymmetric Key Functions
 * This section provides information on the functions which perform asymmetric
 * key processing.
 * @ingroup PKEY_GROUP
 * @{
 */
/**
 * @}
 */

 /**
  * @defgroup PKEY_CB_FUNC Callback Functions
  * This section documents the function provided for the utilization of
  * user-defined callback routines.
  * @ingroup PKEY_ALL_FUNCS
  * @{
  */
 /**
 * The callback function to use with R_PKEY_iterate_fields().
 * This function will be called and passed with each field of the key, one
 * key at a time.
 *
 * @param    arg   [In]  The user-defined argument.
 * @param    type  [In]  The type of the data.
 * @param    item  [In]  An item of data.
 * @return   #R_ERROR_NONE indicates success.<br>
 *           See @ref R_ERROR_IDS for valid values.
 *
 * @see     R_PKEY_iterate_fields().
 */
 typedef int R_PKEY_CB_T(void *arg, int type, R_ITEM *item);

 /**
 * @}
 */

/**
 * @defgroup PKEY_CTX Context Functions
 * This section lists the functions that facilitate public key contexts.
 * @ingroup PKEY_ALL_FUNCS
 * @{
 */

#ifndef NO_R_PKEY_METH_TABLE
int R_PKEY_CTX_new(R_LIB_CTX *lib_ctx, R_RES_FLAG flag, R_PKEY_TYPE pkeytype,
    R_PKEY_CTX **pkey_ctx);
int R_PKEY_CTX_free(R_PKEY_CTX *ctx);

int R_PKEY_CTX_get_info(R_PKEY_CTX *pkey_ctx, int id, void *param);
int R_PKEY_CTX_set_info(R_PKEY_CTX *pkey_ctx, int id, void *param);

R_LIB_CTX *R_PKEY_CTX_get_LIB_CTX(R_PKEY_CTX *ctx);
#endif /* !defined(NO_R_PKEY_METH_TABLE) */

R_PKEY_METHOD *R_PKEY_pk_method(void *imp_data);

/**
 * @}
 */

/**
 * @defgroup R_PKEY_PUB_FN Operation Functions
 * This section contains all the functions that manage public keys.
 * @ingroup PKEY_ALL_FUNCS
 * @{
 */

#ifndef NO_R_PKEY_METH_TABLE
R_PKEY_CTX *R_PKEY_get_PKEY_CTX(R_PKEY *pkey);

/* Return the "type" of a pkey - R_PKEY_TYPE_* */
int R_PKEY_get_type(R_PKEY *pkey);

/* Public/Private key functions */
int R_PKEY_new(R_PKEY_CTX *ctx, R_PKEY_TYPE pkeytype, R_PKEY **pkey);
int R_PKEY_free(R_PKEY *pkey);
int R_PKEY_copy(R_PKEY *new_pkey, R_PKEY *pkey, int flag);

int R_PKEY_from_binary(R_PKEY_CTX *pkey_ctx, int flag, R_PKEY_TYPE type,
    unsigned int max_buf_len, const unsigned char *buf,
    unsigned int *consumed_len, R_PKEY **pkey);
int R_PKEY_to_binary(R_PKEY *pkey, unsigned int max_buf_len, unsigned char *buf,
    unsigned int *consumed_len);
int R_PKEY_from_public_key_binary(R_PKEY_CTX *pkey_ctx, int flag,
    R_PKEY_TYPE type, unsigned int max_buf_len, const unsigned char *buf,
    unsigned int *consumed_len, R_PKEY **pkey);
int R_PKEY_to_public_key_binary(R_PKEY *pkey, unsigned int max_buf_len,
    unsigned char *buf, unsigned int *out_len);

int R_PKEY_reference_inc(R_PKEY *pkey);
int R_PKEY_cmp(R_PKEY *key1, R_PKEY *key2);
int R_PKEY_public_cmp(R_PKEY *key1, R_PKEY *key2);

int R_PKEY_get_info(R_PKEY *pkey, int id, void *param);
int R_PKEY_set_info(R_PKEY *pkey, int type, void *param);

int R_PKEY_iterate_fields(R_PKEY *pkey, R_PKEY_CB_T *func, void *arg);

/* Crypto-related functions */
int R_PKEY_get_num_bits(R_PKEY *pkey);
int R_PKEY_get_num_primes(R_PKEY *pkey);
int R_PKEY_signhash(R_PKEY *pkey, unsigned char *data, unsigned int dlen,
    unsigned char *out, unsigned int *olen);
int R_PKEY_verifyhash(R_PKEY *pkey, unsigned char *data, unsigned int dlen,
    unsigned char *hash, unsigned int hlen);
#endif /* !defined(NO_R_PKEY_METH_TABLE) */

int R_PKEY_generate_simple(R_PKEY_CTX *pkey_ctx, R_PKEY **rpkey, int type,
    int num_bits, int modifier, int flags, R_SURRENDER *surrender);

/* wrapper functions - common non-format specific functions that simply
 * encapsulate often used steps
 */

int R_PKEY_from_file(R_PKEY_CTX *pkey_ctx, R_PKEY **pkey, char *filename,
    int type, R_FORMAT format);

int R_PKEY_TYPE_to_string(R_PKEY_TYPE type, unsigned int max_str_len,
    char *str);
int R_PKEY_TYPE_from_string(R_PKEY_TYPE *type, char *str);
int R_PKEY_TYPE_to_PEM_header(R_PKEY_TYPE type, unsigned int max_str_len,
    char *str);

int R_PKEY_FORMAT_to_string(R_PKEY_FORMAT format, unsigned int max_str_len,
    char *str);
int R_PKEY_FORMAT_from_string(char *str, R_PKEY_FORMAT *format);

#ifndef NO_BIO
int R_PKEY_to_bio(BIO *bio, R_PKEY *pkey, R_FORMAT format, char *cipher);

#ifndef NO_R_PKEY_METH_TABLE
int R_PKEY_print(BIO *bio, R_PKEY *pkey, R_FORMAT format, char *format_arg);
#endif /* !defined(NO_R_PKEY_METH_TABLE) */

int R_PKEY_from_bio(BIO *bio, R_PKEY_CTX *pkey_ctx, R_PKEY **pkey, int type,
    R_FORMAT format);

/* R_PKEY print function to add into the resource list */
typedef int (R_PKEY_PRINT_FUNC_T)(BIO *bio, R_PKEY *pkey, R_FORMAT format,
				  char *format_arg);

R_PKEY_PRINT_FUNC_T *R_PKEY_get_print_func(void *imp_data);

#endif /* NO_BIO */

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_CERT_R_PKEY_H */
