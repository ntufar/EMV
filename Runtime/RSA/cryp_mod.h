/* $Id: cryp_mod.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryp_mod.h
 * This file contains the public definitions and function
 * declarations of the cryptographic module.
 *
 * @see @ref CRYPTO_DIGEST_SIZE, @ref CRYPTO_CIPHER_SIZE,
 * @ref CRYPTO_ALG_SUP_RET, @ref R_CR_IDS, @ref R_CR_TYPE,
 * @ref R_CR_SUB, @ref R_CR_INFO_ID, @ref R_CR_FLAG
 * and @ref CRYPTO_CTX_INFO.
 */

#ifndef HEADER_COMMON_CRYP_MOD_H
#define HEADER_COMMON_CRYP_MOD_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_lib.h"
#include "r_com.h"
#include "r_nid.h"
#include "r_pkey.h"
#include "r_skey.h"

#include "nat_meth.h"
/**
 * @defgroup CRYPTO_MODULE Cryptographic Module Operations
 * This section details the resources, functions, types and identifiers
 * used by the cryptographic module.
 * @ingroup CME_API
 * @{
 */
/**
 * Indicates the type of the cryptographic algorithm identifier.
 * See @ref R_CR_IDS for more information.
 */
typedef int R_CR_ALG_ID;
/**
 * Indicates the type of the cryptographic algorithm operation type.
 * See @ref R_CR_TYPE for more information.
 */
typedef int R_CR_ALG_TYPE;
/**
 * Indicates the type of the cryptographic algorithm operation subtype.
 * See @ref R_CR_SUB for more information.
 */
typedef int R_CR_ALG_SUB;

/**
 * @}
 */
/**
 * @defgroup CRYP_OBJ_ID Cryptographic Object Identifiers
 * This section contains the identifiers used in the creation of a
 * cryptographic object. The instantiation of a new cryptographic
 * object requires three components:<br>
 * <li> The algorithm operation type.</li>
 * <li> The algorithm operation subtype.</li>
 * <li> The algorithm identifier.</li>
 *
 * @ingroup CRYPTO_MODULE
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup CRYPTO_DIGEST_SIZE Cryptographic Digest Size Defines
 * This section details the hash functions, message digests and digital
 * signature defines used by the cryptographic library.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * Indicates the length of the generated MD5 digest.
 */
#define R_CR_DIGEST_MD5_LEN                 16
/**
 * Indicates the length of the generated SHA-1 digest.
 */
#define R_CR_DIGEST_SHA1_LEN                20
/**
 * Indicates the length of the generated SHA-256 digest.
 */
#define R_CR_DIGEST_SHA256_LEN              32
/**
 * Indicates the length of the generated SHA-384 digest.
 */
#define R_CR_DIGEST_SHA384_LEN              48
/**
 * Indicates the length of the generated SHA-512 digest.
 */
#define R_CR_DIGEST_SHA512_LEN              64
#ifndef NO_SHA512
/**
 * Indicates the maximum length of the available digest types.
 */
#define R_CR_DIGEST_MAX_LEN                 R_CR_DIGEST_SHA512_LEN
#elif !defined(NO_SHA384)
#define R_CR_DIGEST_MAX_LEN                 R_CR_DIGEST_SHA384_LEN
#elif !defined(NO_SHA256)
#define R_CR_DIGEST_MAX_LEN                 R_CR_DIGEST_SHA256_LEN
#elif !defined(NO_SHA1)
#define R_CR_DIGEST_MAX_LEN                 R_CR_DIGEST_SHA1_LEN
#elif !defined(NO_MD5)
#define R_CR_DIGEST_MAX_LEN                 R_CR_DIGEST_MD5_LEN
#else
#define R_CR_DIGEST_MAX_LEN                 16
#endif
/**
 * @}
 */
/**
 * @defgroup CRYPTO_CIPHER_SIZE Cryptographic Symmetric Cipher Size Defines
 * This section details the symmetric cipher key and Initialization Vector (IV)
 * lengths utilized by the cryptographic library.
 * @ingroup CRYPTO_MODULE
 * @{
 */
/**
 * Indicates the maximum symmetric cipher key length.
 */
#define R_CR_CIPHER_KEY_MAX_LEN             32 /* AES is the biggest */
/**
 * Indicates the maximum symmetric cipher Initialization Vector (IV) length.
 */
#define R_CR_CIPHER_IV_MAX_LEN              32 /* AES is the biggest */

/**
 * @}
 */

/**
 * @defgroup CRYPTO_ALG_SUP_RET Cryptographic Algorithm Support Return Values
 * This section details the defines used in determining the availability
 * of algorithms at program run time.
 * @ingroup CRYPTO_MODULE
 * @{
 */
/**
 * Indicates the algorithm availability status is not supported.
 */
#define R_CR_NOT_SUPPORTED                  0
/**
 * Indicates the algorithm availability status is not available.
 */
#define R_CR_NOT_AVAIL                      1
/**
 * Indicates the algorithm availability status is supported.
 */
#define R_CR_SUPPORTED                      2

/**
 * @}
 */

/**
 * @defgroup R_CR_TYPE Operation Types
 * This section details the cryptographic algorithms and their
 * associated types.
 * The following table details the strings that are interpreted by
 * R_CR_TYPE_from_string() and output by R_CR_TYPE_to_string().
 * @br
 * <table><tr>
 * <td><b>Identifier</b></tr>
 * <td><b>String</b></tr>
 * </tr><tr>
 * <td>#R_CR_TYPE_NONE</td>
 * <td><tt>"NONE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_ASYM</td>
 * <td><tt>"ASYM"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_CIPHER</td>
 * <td><tt>"CIPHER"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_DIGEST</td>
 * <td><tt>"DIGEST"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_RANDOM</td>
 * <td><tt>"RANDOM"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_KEY_EXCHANGE</td>
 * <td><tt>"KEY_EXCHANGE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_SIGNATURE</td>
 * <td><tt>"SIGNATURE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_MAC</td>
 * <td><tt>"MAC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_KEYGEN</td>
 * <td><tt>"KEYGEN"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_PARAMGEN</td>
 * <td><tt>"PARAMGEN"</tt></td>
 * </tr><tr>
 * <td>#R_CR_TYPE_MAX</td>
 * <td><tt>"MAX"</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * @see R_CR_new() and R_CR_CTX_alg_supported().
 *
 * @ingroup CRYP_OBJ_ID
 * @{
 */
/**
 * Indicates that the operation type is none.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"NONE"</tt></td>
 * <td>This string is interpreted as the <tt>NONE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"NONE"</tt></td>
 * <td>The string that represents a <tt>NONE</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_NONE                      0
/**
 * Indicates an asymmetric operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"ASYM"</tt></td>
 * <td>This string is interpreted as the <tt>ASYM</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"ASYM"</tt></td>
 * <td>The string that represents an <tt>ASYM</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_ASYM                      1
/**
 * Indicates a symmetric operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"CIPHER"</tt></td>
 * <td>This string is interpreted as the <tt>CIPHER</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"CIPHER"</tt></td>
 * <td>The string that represents a <tt>CIPHER</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_CIPHER                    2
/**
 * Indicates a digest operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"DIGEST"</tt></td>
 * <td>This string is interpreted as the <tt>DIGEST</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"DIGEST"</tt></td>
 * <td>The string that represents a <tt>DIGEST</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_DIGEST                    3
/**
 * Indicates a random operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"RANDOM"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"RANDOM"</tt></td>
 * <td>The string that represents a <tt>RANDOM</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_RANDOM                    4
/**
 * Indicates a key agreement operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"KEY_EXCHANGE"</tt></td>
 * <td>This string is interpreted as the <tt>KEY_EXCHANGE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"KEY_EXCHANGE"</tt></td>
 * <td>The string that represents a <tt>KEY_EXCHANGE</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_KEY_EXCHANGE              5
/**
 * Indicates a signature operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"SIGNATURE"</tt></td>
 * <td>This string is interpreted as the <tt>SIGNATURE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"SIGNATURE"</tt></td>
 * <td>The string that represents a <tt>SIGNATURE</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_SIGNATURE                 6
/**
 * Indicates a Message Authentication Code (MAC) operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"MAC"</tt></td>
 * <td>This string is interpreted as the <tt>MAC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"MAC"</tt></td>
 * <td>The string that represents a <tt>MAC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_MAC                       7
/**
 * Indicates a key generation operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"KEYGEN"</tt></td>
 * <td>This string is interpreted as the <tt>KEYGEN</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"KEYGEN"</tt></td>
 * <td>The string that represents a <tt>KEYGEN</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_KEYGEN                    8
/**
 * Indicates a parameter generation operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"PARAMGEN"</tt></td>
 * <td>This string is interpreted as the <tt>PARAMGEN</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"PARAMGEN"</tt></td>
 * <td>The string that represents a <tt>PARAMGEN</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_PARAMGEN                  9
/**
 * Indicates an identifier maximum value operation type.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_TYPE_from_string()</td>
 * <td><tt>"MAX"</tt></td>
 * <td>This string is interpreted as the <tt>MAX</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_TYPE_to_string()</td>
 * <td><tt>"MAX"</tt></td>
 * <td>The string that represents a <tt>MAX</tt> type.</td>
 * </tr></table>
 */
#define R_CR_TYPE_MAX                       9

/**
 * @}
 */

/* There are two sorts of sub-ids -- Those with a single bit set that can be
   combined by bit-wise or in a method table for methods that can handle more
   than one sub-id. For algorithms for which combinable sub-ids are not
   sensible, a range for scalar sub-id allocation is also reserved.

   Assuming a 32-bit integer, up to 30 single-bit sub-ids and 2^^31 - 2
   scalar sub-ids may be defined.

   The macros below have the effect of defining scalar sub-ids as odd numbers
   and single-bit sub-ids as even numbers. Using the low-order bit to
   distinguish scalar and bit ids ensures independence from integer size.
*/
#define R_CR_SUB_BIT(n)                 (1<<((n)+1))
#define R_CR_SUB_SCALAR(n)              (((n)<<1)|1)
#define R_CR_IS_SUB_SCALAR(sub)         ((((sub)&1)==1)||(sub==R_CR_SUB_NONE))
#define R_CR_IS_SUB_BIT(sub)            (!R_CR_IS_SUB_SCALAR(sub))

/**
 * @defgroup R_CR_SUB Operation Subtypes
 * This section details the cryptographic algorithms and possible variations
 * denoted by a subtype identifier. The algorithm subtype is often used to
 * define the area of operation available to the algorithm type selected.
 * The following table details the strings that are interpreted by
 * R_CR_SUB_from_string() and output by R_CR_SUB_to_string().
 * @br
 * <table><tr>
 * <td><b>Identifier</b></tr>
 * <td><b>String</b></tr>
 * </tr><tr>
 * <td>#R_CR_SUB_NONE</td>
 * <td><tt>"NONE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_SIGN</td>
 * <td><tt>"SIGN"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_VERIFY</td>
 * <td><tt>"VERIFY"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_ENCRYPT</td>
 * <td><tt>"ENCRYPT"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_DECRYPT</td>
 * <td><tt>"DECRYPT"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PUBLIC</td>
 * <td><tt>"PUBLIC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PRIVATE</td>
 * <td><tt>"PRIVATE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_MAC</td>
 * <td><tt>"MAC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PUB_ENC</td>
 * <td><tt>"PUB_ENC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PUB_DEC</td>
 * <td><tt>"PUB_DEC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PRIV_ENC</td>
 * <td><tt>"PRIV_ENC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_SUB_PRIV_DEC</td>
 * <td><tt>"PRIV_DEC"</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * @see R_CR_new() and R_CR_CTX_alg_supported().
 *
 * @ingroup CRYP_OBJ_ID
 * @{
 */
/**
 * Indicates that the operation subtype identifier is none.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"NONE"</tt></td>
 * <td>This string is interpreted as the <tt>NONE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"NONE"</tt></td>
 * <td>The string that represents a <tt>NONE</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_CIPHER, #R_CR_TYPE_DIGEST, #R_CR_TYPE_RANDOM,
 * #R_CR_TYPE_KEYGEN, #R_CR_TYPE_PARAMGEN and #R_CR_TYPE_KEY_EXCHANGE.<br>
 *
 */
#define R_CR_SUB_NONE                   0
/**
 * A subtype identifier which indicates a sign operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"SIGN"</tt></td>
 * <td>This string is interpreted as the <tt>SIGN</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"SIGN"</tt></td>
 * <td>The string that represents a <tt>SIGN</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_SIGNATURE.<br>
 */
#define R_CR_SUB_SIGN                   R_CR_SUB_BIT(0)
/**
 * A subtype identifier which indicates a signature verification operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"VERIFY"</tt></td>
 * <td>This string is interpreted as the <tt>VERIFY</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"VERIFY"</tt></td>
 * <td>The string that represents a <tt>VERIFY</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_SIGNATURE.<br>
 */
#define R_CR_SUB_VERIFY                 R_CR_SUB_BIT(1)
/**
 * A subtype identifier which indicates an encryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"ENCRYPT"</tt></td>
 * <td>This string is interpreted as the <tt>ENCRYPT</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"ENCRYPT"</tt></td>
 * <td>The string that represents an <tt>ENCRYPT</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_ENCRYPT                R_CR_SUB_BIT(2)
/**
 * A subtype identifier which indicates a decryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"DECRYPT"</tt></td>
 * <td>This string is interpreted as the <tt>DECRYPT</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"DECRYPT"</tt></td>
 * <td>The string that represents a <tt>DECRYPT</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_DECRYPT                R_CR_SUB_BIT(3)
/**
 * A subtype identifier which indicates a public key operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PUBLIC"</tt></td>
 * <td>This string is interpreted as the <tt>PUBLIC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PUBLIC"</tt></td>
 * <td>The string that represents a <tt>PUBLIC</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_PUBLIC                 R_CR_SUB_BIT(4)
/**
 * A subtype identifier which indicates a private key operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PRIVATE"</tt></td>
 * <td>This string is interpreted as the <tt>PRIVATE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PRIVATE"</tt></td>
 * <td>The string that represents a <tt>PRIVATE</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_PRIVATE                R_CR_SUB_BIT(5)

/**
 * A subtype identifier which indicates a Message Authentication Code (MAC)
 * operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"MAC"</tt></td>
 * <td>This string is interpreted as the <tt>MAC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"MAC"</tt></td>
 * <td>The string that represents a <tt>MAC</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_MAC.<br>
 */
#define R_CR_SUB_MAC                    R_CR_SUB_BIT(6)

/**
 * A subtype identifier which indicates a public key encryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.<br>
 * <br>
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PUB_ENC"</tt></td>
 * <td>This string is interpreted as the <tt>PUB_ENC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PUB_ENC"</tt></td>
 * <td>The string that represents a <tt>PUB_ENC</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_PUB_ENC                (R_CR_SUB_PUBLIC|R_CR_SUB_ENCRYPT)
/**
 * A subtype identifier which indicates a public key decryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.<br>
 * <br>
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PUB_DEC"</tt></td>
 * <td>This string is interpreted as the <tt>PUB_DEC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PUB_DEC"</tt></td>
 * <td>The string that represents a <tt>PUB_DEC</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_PUB_DEC                (R_CR_SUB_PUBLIC|R_CR_SUB_DECRYPT)
/**
 * A subtype identifier which indicates a private key encryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.<br>
 * <br>
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PRIV_ENC"</tt></td>
 * <td>This string is interpreted as the <tt>PRIV_ENC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PRIV_ENC"</tt></td>
 * <td>The string that represents a <tt>PRIV_ENC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_SUB_PRIV_ENC               (R_CR_SUB_PRIVATE|R_CR_SUB_ENCRYPT)
/**
 * A subtype identifier which indicates a private key decryption operation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.<br>
 * <br>
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_SUB_from_string()</td>
 * <td><tt>"PRIV_DEC"</tt></td>
 * <td>This string is interpreted as the <tt>PRIV_DEC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_SUB_to_string()</td>
 * <td><tt>"PRIV_DEC"</tt></td>
 * <td>The string that represents a <tt>PRIV_DEC</tt> type.</td>
 * </tr></table>
 * @br
 * @see #R_CR_TYPE_ASYM.<br>
 */
#define R_CR_SUB_PRIV_DEC               (R_CR_SUB_PRIVATE|R_CR_SUB_DECRYPT)

/**
 * @}
 */
/**
 * @defgroup R_CR_IDS Algorithm Identifiers
 * This section details the constants which specify the cryptographic algorithm
 * to use in a particular cryptographic operation.
 * The following table details the strings that are interpreted by
 * R_CR_ID_from_string() and output by R_CR_ID_to_string().
 * @br
 * <table><tr>
 * <td><b>Identifier</b></tr>
 * <td><b>String</b></tr>
 * </tr><tr>
 * <td>#R_CR_ID_UNKNOWN</td>
 * <td><tt>"UNKNOWN"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_NULL</td>
 * <td><tt>"NULL"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RANDOM</td>
 * <td><tt>"RANDOM"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RANDOM_MODULUS</td>
 * <td><tt>"RANDOM_MODULUS"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RANDOM_ENTROPY</td>
 * <td><tt>"RANDOM_ENTROPY"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RANDOM_SYS</td>
 * <td><tt>"RANDOM_SYS"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RANDOM_OTP</td>
 * <td><tt>"RANDOM_OTP"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DIGEST_NULL</td>
 * <td><tt>"DIGEST_NULL"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA1</td>
 * <td><tt>"SHA1"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA256</td>
 * <td><tt>"SHA256"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA384</td>
 * <td><tt>"SHA384"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA512</td>
 * <td><tt>"SHA512"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_MD2</td>
 * <td><tt>"MD2"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_MD5</td>
 * <td><tt>"MD5"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_HMAC_MD5</td>
 * <td><tt>"HMAC_MD5"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_HMAC_SHA1</td>
 * <td><tt>"HMAC_SHA1"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_CBC</td>
 * <td><tt>"DES_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE</td>
 * <td><tt>"DES_EDE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_ECB</td>
 * <td><tt>"DES_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_CFB64</td>
 * <td><tt>"DES_CFB64"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE3</td>
 * <td><tt>"DES_EDE3"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE_CBC</td>
 * <td><tt>"DES_EDE_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE3_CBC</td>
 * <td><tt>"DES_EDE3_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE_CFB64</td>
 * <td><tt>"DES_EDE_CFB64"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE3_CFB64</td>
 * <td><tt>"DES_EDE3_CFB64"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE_OFB64</td>
 * <td><tt>"DES_EDE_OFB64"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_EDE3_OFB64</td>
 * <td><tt>"DES_EDE3_OFB64"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_40_CBC</td>
 * <td><tt>"DES_40_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_40_CFB</td>
 * <td><tt>"DES_40_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DES_OFB</td>
 * <td><tt>"DES_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC2_CBC</td>
 * <td><tt>"RC2_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC2_ECB</td>
 * <td><tt>"RC2_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC2_CFB</td>
 * <td><tt>"RC2_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC2_OFB</td>
 * <td><tt>"RC2_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC2_40_CBC</td>
 * <td><tt>"RC2_40_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC4</td>
 * <td><tt>"RC4"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC4_40</td>
 * <td><tt>"RC4_40"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC5_CBC</td>
 * <td><tt>"RC5_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC5_ECB</td>
 * <td><tt>"RC5_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC5_CFB</td>
 * <td><tt>"RC5_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RC5_OFB</td>
 * <td><tt>"RC5_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_128_CBC</td>
 * <td><tt>"AES_128_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_128_ECB</td>
 * <td><tt>"AES_128_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_128_CFB</td>
 * <td><tt>"AES_128_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_128_OFB</td>
 * <td><tt>"AES_128_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_192_CBC</td>
 * <td><tt>"AES_192_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_192_ECB</td>
 * <td><tt>"AES_192_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_192_CFB</td>
 * <td><tt>"AES_192_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_192_OFB</td>
 * <td><tt>"AES_192_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_256_CBC</td>
 * <td><tt>"AES_256_CBC"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_256_ECB</td>
 * <td><tt>"AES_256_ECB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_256_CFB</td>
 * <td><tt>"AES_256_CFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_AES_256_OFB</td>
 * <td><tt>"AES_256_OFB"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA</td>
 * <td><tt>"RSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_PKCS1</td>
 * <td><tt>"RSA_PKCS1"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_PKCS1_OAEP</td>
 * <td><tt>"RSA_PKCS1_OAEP"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_PKCS1_SSL</td>
 * <td><tt>"RSA_PKCS1_SSL"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_PKCS1_RAW</td>
 * <td><tt>"RSA_PKCS1_RAW"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_X931</td>
 * <td><tt>"RSA_X931"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DSA</td>
 * <td><tt>"DSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA1_DSA</td>
 * <td><tt>"SHA1_DSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA1_RSA_X931</td>
 * <td><tt>"SHA1_RSA_X931"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA1_RSA</td>
 * <td><tt>"SHA1_RSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SHA1_RSA_RAW</td>
 * <td><tt>"SHA1_RSA_RAW"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_MD2_RSA</td>
 * <td><tt>"MD2_RSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_MD5_RSA</td>
 * <td><tt>"MD5_RSA"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SIGNATURE_TYPE_NONE</td>
 * <td><tt>"SIGNATURE_TYPE_NONE"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_SIGNATURE_TYPE_DER</td>
 * <td><tt>"SIGNATURE_TYPE_DER"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_KE_DH</td>
 * <td><tt>"KE_DH"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_KEY_GENERATION</td>
 * <td><tt>"RSA_KEY_GENERATION"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_KEY_GENERATION_X931</td>
 * <td><tt>"RSA_KEY_GENERATION"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_RSA_KEY_GENERATION_VENDOR</td>
 * <td><tt>"RSA_KEY_GENERATION_VENDOR"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DSA_KEY_GENERATION</td>
 * <td><tt>"DSA_KEY_GENERATION"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DSA_PARAMETER_GENERATION</td>
 * <td><tt>"DSA_PARAMETER_GENERATION"</tt></td>
 * </tr><tr>
 * <td>#R_CR_ID_DH_PARAMETER_GENERATION</td>
 * <td><tt>"DH_PARAMETER_GENERATION"</tt></td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * See R_CR_new(), R_CR_get_info() and R_CR_CTX_alg_supported().
 *
 * @ingroup CRYP_OBJ_ID
 * @{
 */
/* Use this macro to define IDs that are meaningful only to the R_CR_xxx
   functions and not to lower layers (e.g., the nat_method layer. These IDs
   MUST NOT be passed to lower layers that expect some type of NID_xxx. The
   local IDs begin at 4096 to give wide berth to the NIDs defined in
   object.h (that currently end at 119.
*/
#define R_CR_ID_LOCAL(local_id)             (4096 + (local_id))

/* Define algorithm IDs and map them to NIDs where possible.
   In general, two names are defined for each ID -- one that includes the
   algorithm type and one that does not.
 */
/**
 * Indicates that the cryptographic identifier is an unknown algorithm.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"UNKNOWN"</tt></td>
 * <td>This string is interpreted as the <tt>UNKNOWN</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"UNKNOWN"</tt></td>
 * <td>The string that represents an <tt>UNKNOWN</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_UNKNOWN                     (-1)
/**
 * Indicates that the cryptographic identifier is <tt>NULL</tt>.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"NULL"</tt></td>
 * <td>This string is interpreted as the <tt>NULL</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"NULL"</tt></td>
 * <td>The string that represents a <tt>NULL</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_NULL                        0

/**
 * Indicates the identifier for the FIPS 186-2 random generation
 * implemenation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RANDOM"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RANDOM"</tt></td>
 * <td>The string that represents a <tt>RANDOM</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RANDOM                      R_CR_ID_LOCAL(0)

/**
 * Indicates a random cryptographic identifier that returns
 * locally collected entropy.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RANDOM_ENTROPY"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM_ENTROPY</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RANDOM_ENTROPY"</tt></td>
 * <td>The string that represents a <tt>RANDOM_ENTROPY</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RANDOM_ENTROPY              R_CR_ID_LOCAL(11)

/*
 * Indicates a random cryptographic identifier that uses
 * the global FIPS 186-2 CN1 random object.
 */
#define R_CR_ID_RANDOM_GLOBAL               R_CR_ID_LOCAL(12)

/**
 * Indicates the identifier for the FIPS 186-2 random generation
 * with modulus implemenation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RANDOM_MODULUS"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RANDOM_MODULUS"</tt></td>
 * <td>The string that represents a <tt>RANDOM</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RANDOM_MODULUS              R_CR_ID_LOCAL(13)

/**
 * Indicates that the cryptographic identifier is random and uses local system
 * random function calls.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RANDOM_SYS"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM_SYS</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RANDOM_SYS"</tt></td>
 * <td>The string that represents a <tt>RANDOM_SYS</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RANDOM_SYS                  R_CR_ID_LOCAL(8)

/**
 * Indicates the identifier for the deterministic random implementation.
 * This "random" implementation allows byte blocks to be set by the 
 * application that are returned without modification from 
 * #R_CR_random_bytes. This option is meant to be used for testing 
 * purposes only, where deterministic random output is an advantage.
 * 
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RANDOM_OTP"</tt></td>
 * <td>This string is interpreted as the <tt>RANDOM_OTP</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RANDOM_OTP"</tt></td>
 * <td>The string that represents a <tt>RANDOM_OTP</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RANDOM_OTP                  R_CR_ID_LOCAL(17)

/**
 * A cryptographic identifier which indicates a null digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DIGEST_NULL"</tt></td>
 * <td>This string is interpreted as the <tt>DIGEST_NULL</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DIGEST_NULL"</tt></td>
 * <td>The string that represents a <tt>DIGEST_NULL</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DIGEST_NULL                 R_CR_ID_NULL

/**
 * A cryptographic identifier which indicates a SHA-1 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA1"</tt></td>
 * <td>This string is interpreted as the <tt>SHA1</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA1"</tt></td>
 * <td>The string that represents a <tt>SHA1</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA1                        NID_sha1
/**
 * A cryptographic identifier which indicates a SHA-256 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA256"</tt></td>
 * <td>This string is interpreted as the <tt>SHA256</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA256"</tt></td>
 * <td>The string that represents a <tt>SHA256</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA256                      NID_sha256
/**
 * A cryptographic identifier which indicates a SHA-384 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA384"</tt></td>
 * <td>This string is interpreted as the <tt>SHA384</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA384"</tt></td>
 * <td>The string that represents a <tt>SHA384</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA384                      NID_sha384
/**
 * A cryptographic identifier which indicates a SHA-512 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA512"</tt></td>
 * <td>This string is interpreted as the <tt>SHA512</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA512"</tt></td>
 * <td>The string that represents a <tt>SHA512</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA512                      NID_sha512

/**
 * A cryptographic identifier which indicates an MD2 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"MD2"</tt></td>
 * <td>This string is interpreted as the <tt>MD2</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"MD2"</tt></td>
 * <td>The string that represents a <tt>MD2</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_MD2                         NID_md2
/**
 * A cryptographic identifier which indicates an MD5 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"MD5"</tt></td>
 * <td>This string is interpreted as the <tt>MD5</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"MD5"</tt></td>
 * <td>The string that represents a <tt>MD5</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_MD5                         NID_md5

/**
 * A cryptographic identifier which indicates a Message Authentication Code
 * (MAC) utilizing MD5 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"HMAC_MD5"</tt></td>
 * <td>This string is interpreted as the <tt>HMAC_MD5</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"HMAC_MD5"</tt></td>
 * <td>The string that represents a <tt>HMAC_MD5</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_HMAC_MD5                    R_CR_ID_LOCAL(1)
/**
 * A cryptographic identifier which indicates a Message Authentication Code
 * (MAC) utilizing SHA-1 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"HMAC_SHA1"</tt></td>
 * <td>This string is interpreted as the <tt>HMAC_SHA1</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"HMAC_SHA1"</tt></td>
 * <td>The string that represents a <tt>HMAC_SHA1</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_HMAC_SHA1                   R_CR_ID_LOCAL(2)

/**
 * A cryptographic identifier which indicates a DES CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>DES_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_CBC"</tt></td>
 * <td>The string that represents a <tt>DES_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_CBC                     NID_des_cbc

/**
 * A cryptographic identifier which indicates a 2DES EDE ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE"</tt></td>
 * <td>The string that represents a <tt>DES_EDE</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE                     NID_des_ede
/**
 * A cryptographic identifier which indicates a DES ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>DES_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_ECB"</tt></td>
 * <td>The string that represents a <tt>DES_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_ECB                     NID_des_ecb
/**
 * A cryptographic identifier which indicates a DES CFB64 symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_CFB64"</tt></td>
 * <td>This string is interpreted as the <tt>DES_CFB64</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_CFB64"</tt></td>
 * <td>The string that represents a <tt>DES_CFB64</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_CFB64                   NID_des_cfb64
/**
 * A cryptographic identifier which indicates a 3DES EDE ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE3"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE3</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE3"</tt></td>
 * <td>The string that represents a <tt>DES_EDE3</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE3                    NID_des_ede3
/**
 * A cryptographic identifier which indicates a 2DES EDE CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE_CBC"</tt></td>
 * <td>The string that represents a <tt>DES_EDE_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE_CBC                 NID_des_ede_cbc
/**
 * A cryptographic identifier which indicates a 3DES EDE CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE3_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE3_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE3_CBC"</tt></td>
 * <td>The string that represents a <tt>DES_EDE3_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE3_CBC                NID_des_ede3_cbc
/**
 * A cryptographic identifier which indicates a 2DES EDE CFB64 symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE_CFB64"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE_CFB64</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE_CFB64"</tt></td>
 * <td>The string that represents a <tt>DES_EDE_CFB64</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE_CFB64               NID_des_ede_cfb64
/**
 * A cryptographic identifier which indicates a 3DES EDE CFB64 symmetric
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE3_CFB64"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE3_CFB64</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE3_CFB64"</tt></td>
 * <td>The string that represents a <tt>DES_EDE3_CFB64</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE3_CFB64              NID_des_ede3_cfb64
/**
 * A cryptographic identifier which indicates a 2DES EDE OFB64 symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE_OFB64"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE_OFB64</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE_OFB64"</tt></td>
 * <td>The string that represents a <tt>DES_EDE_OFB64</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE_OFB64               NID_des_ede_ofb64
/**
 * A cryptographic identifier which indicates a 3DES EDE OFB64 symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_EDE3_OFB64"</tt></td>
 * <td>This string is interpreted as the <tt>DES_EDE3_OFB64</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_EDE3_OFB64"</tt></td>
 * <td>The string that represents a <tt>DES_EDE3_OFB64</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_EDE3_OFB64              NID_des_ede3_ofb64
/**
 * A cryptographic identifier which indicates a DES 40-bit CBC symmetric
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_40_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>DES_40_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_40_CBC"</tt></td>
 * <td>The string that represents a <tt>DES_40_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_40_CBC                  NID_des_40_cbc
/**
 * A cryptographic identifier which indicates a DES 40-bit CFB symmetric
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_40_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>DES_40_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_40_CFB"</tt></td>
 * <td>The string that represents a <tt>DES_40_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_40_CFB                  NID_des_40_cfb
/**
 * A cryptographic identifier which indicates a DES OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DES_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>DES_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DES_OFB"</tt></td>
 * <td>The string that represents a <tt>DES_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DES_OFB                     NID_des_ofb64

/**
 * A cryptographic identifier which indicates an RC2 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC2_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>RC2_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC2_CBC"</tt></td>
 * <td>The string that represents an <tt>RC2_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC2_CBC                     NID_rc2_cbc
/**
 * A cryptographic identifier which indicates an RC2 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC2_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>RC2_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC2_ECB"</tt></td>
 * <td>The string that represents an <tt>RC2_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC2_ECB                     NID_rc2_ecb
/**
 * A cryptographic identifier which indicates an RC2 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC2_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC2_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC2_CFB"</tt></td>
 * <td>The string that represents an <tt>RC2_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC2_CFB                     NID_rc2_cfb64
/**
 * A cryptographic identifier which indicates an RC2 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC2_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC2_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC2_OFB"</tt></td>
 * <td>The string that represents an <tt>RC2_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC2_OFB                     NID_rc2_ofb64
/**
 * A cryptographic identifier which indicates an RC2 40-bit CBC symmetric
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC2_40_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>RC2_40_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC2_40_CBC"</tt></td>
 * <td>The string that represents an <tt>RC2_40_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC2_40_CBC                  NID_rc2_40_cbc

/**
 * A cryptographic identifier which indicates an RC4 symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC4"</tt></td>
 * <td>This string is interpreted as the <tt>RC4</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC4"</tt></td>
 * <td>The string that represents an <tt>RC4</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC4                         NID_rc4
/**
 * A cryptographic identifier which indicates an RC4 40-bit symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC4_40"</tt></td>
 * <td>This string is interpreted as the <tt>RC4_40</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC4_40"</tt></td>
 * <td>The string that represents an <tt>RC4_40</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC4_40                      NID_rc4_40

/**
 * A cryptographic identifier which indicates an RC5 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC5_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>RC5_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC5_CBC"</tt></td>
 * <td>The string that represents an <tt>RC5_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC5_CBC                     NID_rc5_cbc

/*
 * Equivalent RC5-CBC identifier for compatibility with OpenSSL
 */
#define R_CR_ID_RC5_CBC_NO_PAD              NID_rc5_cbc_no_pad

/**
 * A cryptographic identifier which indicates an RC5 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC5_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>RC5_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC5_ECB"</tt></td>
 * <td>The string that represents an <tt>RC5_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC5_ECB                     NID_rc5_ecb
/**
 * A cryptographic identifier which indicates an RC5 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC5_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC5_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC5_CFB"</tt></td>
 * <td>The string that represents an <tt>RC5_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC5_CFB                     NID_rc5_cfb64
/**
 * A cryptographic identifier which indicates an RC5 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC5_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC5_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC5_OFB"</tt></td>
 * <td>The string that represents an <tt>RC5_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC5_OFB                     NID_rc5_ofb64

/*
 * A cryptographic identifier which indicates an RC6 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC6_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>RC6_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC6_CBC"</tt></td>
 * <td>The string that represents an <tt>RC6_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC6_CBC                     NID_rc6_cbc
/*
 * A cryptographic identifier which indicates an RC6 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC6_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>RC6_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC6_ECB"</tt></td>
 * <td>The string that represents an <tt>RC6_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC6_ECB                     NID_rc6_ecb
/*
 * A cryptographic identifier which indicates an RC6 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC6_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC6_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC6_CFB"</tt></td>
 * <td>The string that represents an <tt>RC6_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC6_CFB                     NID_rc6_cfb128
/*
 * A cryptographic identifier which indicates an RC6 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RC6_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>RC6_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RC6_OFB"</tt></td>
 * <td>The string that represents an <tt>RC6_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RC6_OFB                     NID_rc6_ofb128

/**
 * A cryptographic identifier which indicates an AES 128 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_128_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>AES_128_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_128_CBC"</tt></td>
 * <td>The string that represents an <tt>AES_128_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_128_CBC                 NID_aes128_cbc
/**
 * A cryptographic identifier which indicates an AES 128 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_128_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_128_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_128_ECB"</tt></td>
 * <td>The string that represents an <tt>AES_128_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_128_ECB                 NID_aes128_ecb
/**
 * A cryptographic identifier which indicates an AES 128 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_128_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_128_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_128_CFB"</tt></td>
 * <td>The string that represents an <tt>AES_128_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_128_CFB                 NID_aes128_cfb
/**
 * A cryptographic identifier which indicates an AES 128 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_128_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_128_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_128_OFB"</tt></td>
 * <td>The string that represents an <tt>AES_128_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_128_OFB                 NID_aes128_ofb

/**
 * A cryptographic identifier which indicates an AES 192 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_192_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>AES_192_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_192_CBC"</tt></td>
 * <td>The string that represents an <tt>AES_192_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_192_CBC                 NID_aes192_cbc
/**
 * A cryptographic identifier which indicates an AES 192 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_192_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_192_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_192_ECB"</tt></td>
 * <td>The string that represents an <tt>AES_192_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_192_ECB                 NID_aes192_ecb
/**
 * A cryptographic identifier which indicates an AES 192 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_192_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_192_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_192_CFB"</tt></td>
 * <td>The string that represents an <tt>AES_192_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_192_CFB                 NID_aes192_cfb
/**
 * A cryptographic identifier which indicates an AES 192 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_192_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_192_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_192_OFB"</tt></td>
 * <td>The string that represents an <tt>AES_192_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_192_OFB                 NID_aes192_ofb

/**
 * A cryptographic identifier which indicates an AES 256 CBC symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_256_CBC"</tt></td>
 * <td>This string is interpreted as the <tt>AES_256_CBC</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_256_CBC"</tt></td>
 * <td>The string that represents an <tt>AES_256_CBC</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_256_CBC                 NID_aes256_cbc
/**
 * A cryptographic identifier which indicates an AES 256 ECB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_256_ECB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_256_ECB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_256_ECB"</tt></td>
 * <td>The string that represents an <tt>AES_256_ECB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_256_ECB                 NID_aes256_ecb
/**
 * A cryptographic identifier which indicates an AES 256 CFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_256_CFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_256_CFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_256_CFB"</tt></td>
 * <td>The string that represents an <tt>AES_256_CFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_256_CFB                 NID_aes256_cfb
/**
 * A cryptographic identifier which indicates an AES 256 OFB symmetric cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"AES_256_OFB"</tt></td>
 * <td>This string is interpreted as the <tt>AES_256_OFB</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"AES_256_OFB"</tt></td>
 * <td>The string that represents an <tt>AES_256_OFB</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_AES_256_OFB                 NID_aes256_ofb

/**
 * A cryptographic identifier which indicates an asymmetric RSA cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA"</tt></td>
 * <td>This string is interpreted as the <tt>RSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA"</tt></td>
 * <td>The string that represents an <tt>RSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA                         NID_rsa
/**
 * A cryptographic identifier which indicates an asymmetric RSA PKCS1 padding
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_PKCS1"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_PKCS1</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_PKCS1"</tt></td>
 * <td>The string that represents an <tt>RSA_PKCS1</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_PKCS1                   NID_rsaEncryption
/**
 * A cryptographic identifier which indicates an asymmetric RSA PKCS #1 OAEP
 * padding cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_PKCS1_OAEP"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_PKCS1_OAEP</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_PKCS1_OAEP"</tt></td>
 * <td>The string that represents an <tt>RSA_PKCS1_OAEP</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_PKCS1_OAEP              NID_rsaes_oaep
/**
 * A cryptographic identifier which indicates an asymmetric RSA PKCS #1 SSL
 * padding cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_PKCS1_SSL"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_PKCS1_SSL</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_PKCS1_SSL"</tt></td>
 * <td>The string that represents an <tt>RSA_PKCS1_SSL</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_PKCS1_SSL               R_CR_ID_LOCAL(7)
/**
 * A cryptographic identifier which indicates an asymmetric RSA PKCS #1 RAW
 * padding cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_PKCS1_RAW"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_PKCS1_RAW</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_PKCS1_RAW"</tt></td>
 * <td>The string that represents an <tt>RSA_PKCS1_RAW</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_PKCS1_RAW               R_CR_ID_LOCAL(9)

/**
 * A cryptographic identifier which indicates an asymmetric RSA X9.31 
 * padding cipher.
 *
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_X931"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_X931</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_X931"</tt></td>
 * <td>The string that represents an <tt>RSA_X931</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_X931                    R_CR_ID_LOCAL(14)

/**
 * A cryptographic identifier which indicates an asymmetric DSA signature
 * cipher.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DSA"</tt></td>
 * <td>This string is interpreted as the <tt>DSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DSA"</tt></td>
 * <td>The string that represents a <tt>DSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DSA                         NID_dsa

/* Defines for signing and verify */
/**
 * A cryptographic identifier which indicates a DSA signature with SHA-1
 * digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA1_DSA"</tt></td>
 * <td>This string is interpreted as the <tt>SHA1_DSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA1_DSA"</tt></td>
 * <td>The string that represents a <tt>SHA1_DSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA1_DSA                    NID_dsaWithSHA1

/**
 * A cryptographic identifier which indicates an RSA signature with SHA-1
 * digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA1_RSA"</tt></td>
 * <td>This string is interpreted as the <tt>SHA1_RSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA1_RSA"</tt></td>
 * <td>The string that represents a <tt>SHA1_RSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA1_RSA                    NID_sha1WithRSAEncryption
/**
 * A cryptographic identifier which indicates a RAW RSA signature with SHA-1
 * digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA1_RSA_RAW"</tt></td>
 * <td>This string is interpreted as the <tt>SHA1_RSA_RAW</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA1_RSA_RAW"</tt></td>
 * <td>The string that represents a <tt>SHA1_RSA_RAW</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA1_RSA_RAW                R_CR_ID_LOCAL(10)
/**
 * A cryptographic identifier which indicates an RSA X9.31 signature with
 * SHA-1 digest.
 *
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SHA1_RSA_X931"</tt></td>
 * <td>This string is interpreted as the <tt>SHA1_RSA_X931</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SHA1_RSA_X931"</tt></td>
 * <td>The string that represents an <tt>SHA1_RSA_X931</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_SHA1_RSA_X931               R_CR_ID_LOCAL(15)

/**
 * A cryptographic identifier which indicates an RSA signature with MD2 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"MD2_RSA"</tt></td>
 * <td>This string is interpreted as the <tt>MD2_RSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"MD2_RSA"</tt></td>
 * <td>The string that represents a <tt>MD2_RSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_MD2_RSA                     NID_md2WithRSAEncryption
/**
 * A cryptographic identifier which indicates an RSA signature with MD5 digest.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"MD5_RSA"</tt></td>
 * <td>This string is interpreted as the <tt>MD5_RSA</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"MD5_RSA"</tt></td>
 * <td>The string that represents a <tt>MD5_RSA</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_MD5_RSA                     NID_md5WithRSAEncryption

/**
 * A signature type identifier which indicates none.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SIGNATURE_TYPE_NONE"</tt></td>
 * <td>This string is interpreted as the <tt>SIGNATURE_TYPE_NONE</tt>
 *     type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SIGNATURE_TYPE_NONE"</tt></td>
 * <td>The string that represents a <tt>SIGNATURE_TYPE_NONE</tt>
 *     type.</td>
 * </tr></table>
 */
#define R_CR_ID_SIGNATURE_TYPE_NONE         R_CR_ID_NULL
/**
 * A signature type identifier which indicates Distinguished Encoding Rules
 * (DER).
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"SIGNATURE_TYPE_DER"</tt></td>
 * <td>This string is interpreted as the <tt>SIGNATURE_TYPE_DER</tt>
 *     type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"SIGNATURE_TYPE_DER"</tt></td>
 * <td>The string that represents a <tt>SIGNATURE_TYPE_DER</tt>
 *     type.</td>
 * </tr></table>
 */
#define R_CR_ID_SIGNATURE_TYPE_DER          1

/* Defines for key exchange methods */
/**
 * A cryptographic identifier which indicates the Diffie-Hellman key agreement.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"KE_DH"</tt></td>
 * <td>This string is interpreted as the <tt>KE_DH</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"KE_DH"</tt></td>
 * <td>The string that represents a <tt>KE_DH</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_KE_DH                       NID_dhKeyAgreement

/* Defines for key generation methods */
/**
 * A cryptographic identifier which indicates RSA key generation via X9.31.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_KEY_GENERATION"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_KEY_GENERATION</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_KEY_GENERATION"</tt></td>
 * <td>The string that represents an <tt>RSA_KEY_GENERATION</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_KEY_GENERATION          R_CR_ID_LOCAL(3)
/**
 * A cryptographic identifier which indicates RSA key generation via X9.31.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_KEY_GENERATION_X931"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_KEY_GENERATION_X931</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_KEY_GENERATION_X931"</tt></td>
 * <td>The string that represents an <tt>RSA_KEY_GENERATION_X931</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_KEY_GENERATION_X931     R_CR_ID_LOCAL(18)
/**
 * A cryptographic identifier which indicates DSA key generation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DSA_KEY_GENERATION"</tt></td>
 * <td>This string is interpreted as the <tt>DSA_KEY_GENERATION</tt> type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DSA_KEY_GENERATION"</tt></td>
 * <td>The string that represents a <tt>DSA_KEY_GENERATION</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_DSA_KEY_GENERATION          R_CR_ID_LOCAL(4)
/**
 * A cryptographic identifier which indicates DSA parameter generation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DSA_PARAMETER_GENERATION"</tt></td>
 * <td>This string is interpreted as the <tt>DSA_PARAMETER_GENERATION</tt>
 *     type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DSA_PARAMETER_GENERATION"</tt></td>
 * <td>The string that represents a <tt>DSA_PARAMETER_GENERATION</tt>
 *     type.</td>
 * </tr></table>
 */
#define R_CR_ID_DSA_PARAMETER_GENERATION    R_CR_ID_LOCAL(5)
/**
 * A cryptographic identifier which indicates Diffie-Hellman parameter
 * generation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"DH_PARAMETER_GENERATION"</tt></td>
 * <td>This string is interpreted as the <tt>DH_PARAMETER_GENERATION</tt>
 *     type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"DH_PARAMETER_GENERATION"</tt></td>
 * <td>The string that represents a <tt>DH_PARAMETER_GENERATION</tt>
 *     type.</td>
 * </tr></table>
 */
#define R_CR_ID_DH_PARAMETER_GENERATION     R_CR_ID_LOCAL(6)
/**
 * A cryptographic identifier which indicates RSA key generation.
 * The following table details the usage of the identifier
 * in @ref R_CR_CTX_FN.
 * @br
 * <table><tr>
 * <td><b>Function</b></td>
 * <td><b>String</b></td>
 * <td><b>Description</b></td>
 * </tr><tr>
 * <td>R_CR_ID_from_string()</td>
 * <td><tt>"RSA_KEY_GENERATION_VENDOR"</tt></td>
 * <td>This string is interpreted as the <tt>RSA_KEY_GENERATION_VENDOR</tt>
 * type.</td>
 * </tr><tr>
 * <td>R_CR_ID_to_string()</td>
 * <td><tt>"RSA_KEY_GENERATION_VENDOR"</tt></td>
 * <td>The string that represents an <tt>RSA_KEY_GENERATION_VENDOR</tt> type.</td>
 * </tr></table>
 */
#define R_CR_ID_RSA_KEY_GENERATION_VENDOR    R_CR_ID_LOCAL(16)

#define R_CR_ID_ECDSA_SHA1                  NID_ECDSAwithSHA1

/**
 * @}
 */

/**
 * @defgroup R_CR_INFO_ID Cryptographic Operation Property Identifiers
 * This section details the defines used in the setting and/or retrieval of
 * data from the cryptographic object.
 * The following table details the data types to pass into <i>param</i> when
 * calling R_CR_get_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_KEY_LEN</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_IV_LEN</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_ROUNDS</td>
 *     <td><tt>long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_BLOCK_SIZE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DIGEST_MAC_LEN</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DIGEST_BLOCK_SIZE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_BITS</td>
 *     <td><tt>long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_SURRENDER</td>
 *     <td>#R_SURRENDER **</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CRYPTO_TYPE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CRYPTO_ID</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CRYPTO_SUB</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_BLOCK_PADDING</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_FLAGS</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_PUBLIC_KEY</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_PRIVATE_KEY</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_P</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_Q</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_G</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_PARAMETERS</td>
 *     <td>#R_PKEY *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_SIGNATURE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_DH_PRIV_KEY</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_ENTROPY_FUNC</td>
 *     <td>#R_RAND_ENT_FUNC_T *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RANDOM</td>
 *     <td>#R_RANDOM **</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_BLOCK_SIZE</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_AUTO_SEED</td>
 *     <td>int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_KEY_SEED_COMPARE</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_RUN_TIME_TESTS</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_MODULUS</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_PREDICTABLE_MODE</td>
 *     <td>int *</td>
 * </tr></table>
 * @br
 *
 * The following table details the data types to pass into <i>param</i> when
 * calling R_CR_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_ROUNDS</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_CIPHER_BITS</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_SURRENDER</td>
 *     <td>#R_SURRENDER *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_BLOCK_PADDING</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_FLAGS</td>
 *     <td><tt>int</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_NUM_BITS</td>
 *     <td><tt>unsigned int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_NUM_PRIMES</td>
 *     <td><tt>unsigned int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_PUBLIC_KEY</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_PRIVATE_KEY</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_P</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_Q</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_G</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_SEED</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DH_PRIME_LENGTH</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DH_GENERATOR_ORDER</td>
 *     <td><tt>unsigned long *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RSA_E</td>
 *     <td><tt>unsigned int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_DSA_PARAMETERS</td>
 *     <td>#R_PKEY *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_SIGNATURE</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_ADD_ENTROPY</td>
 *     <td><tt>int *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_LOAD_FILE</td>
 *     <td><tt>char *</tt></td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_ENTROPY_FUNC</td>
 *     <td>#R_RAND_ENT_FUNC_T *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_BLOCK_SIZE</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_AUTO_SEED</td>
 *     <td>int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_KEY_SEED_COMPARE</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_RUN_TIME_TESTS</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_SEED_RESET</td>
 *     <td>unsigned int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_MODULUS</td>
 *     <td>#R_ITEM *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_PREDICTABLE_MODE</td>
 *     <td>int *</td>
 * </tr><tr>
 *     <td>#R_CR_INFO_ID_RAND_REAL_RANDOM</td>
 *     <td>R_RANDOM *</td>
 * </tr></table>
 * @br
 * @ingroup CRYPTO_MODULE
 * @{
 */
/*
 * A cryptographic identifier which indicates that the algorithm is supported.
 */
#define R_CR_INFO_ID_SUPPORTED              0
/**
 * A cryptographic identifier which indicates the key length in bytes.
 */
#define R_CR_INFO_ID_KEY_LEN                1
/*
 * A cryptographic identifier which indicates the export strength cipher.
 */
#define R_CR_INFO_ID_IS_EXPORT              2
/*
 * A cryptographic identifier which indicates key agreement authentication.
 */
#define R_CR_INFO_ID_KE_AUTHENTICATE        3
/*
 * A cryptographic identifier which indicates the key agreement type.
 */
#define R_CR_INFO_ID_KE_TYPE                4
/*
 * A cryptographic identifier which indicates the export strength key length.
 */
#define R_CR_INFO_ID_CIPHER_EXP_KEY_LEN     5
/**
 * A cryptographic identifier which indicates the Initialization Vector (IV)
 * length in bytes.
 */
#define R_CR_INFO_ID_CIPHER_IV_LEN          6
/*
 * A cryptographic identifier which indicates the symmetric cipher parameter.
 */
#define R_CR_INFO_ID_CIPHER_PARAM           7
/**
 * A cryptographic identifier which indicates the symmetric cipher rounds
 * when using RC5.
 */
#define R_CR_INFO_ID_CIPHER_ROUNDS          8
/*
 * A cryptographic identifier which indicates the symmetric cipher type.
 */
#define R_CR_INFO_ID_CIPHER_TYPE            9
/**
 * A cryptographic identifier for block ciphers, which indicates the
 * symmetric cipher block size in bytes.
 */
#define R_CR_INFO_ID_CIPHER_BLOCK_SIZE      10
/**
 * A cryptographic identifier which indicates the digest or Message
 * Authentication Code (MAC) length in bytes.
 */
#define R_CR_INFO_ID_DIGEST_MAC_LEN         11
/**
 * A cryptographic identifier which indicates the digest's internal block
 * size in bytes.
 */
#define R_CR_INFO_ID_DIGEST_BLOCK_SIZE      13
/**
 * A cryptographic identifier used with RC2, which indicates the
 * symmetric cipher bits in bytes.
 */
#define R_CR_INFO_ID_CIPHER_BITS            14
/*
 * A cryptographic identifier which indicates the PKCS #1
 * Optimal Asymmetric Encryption Padding (OAEP) parameter.
 */
#define R_CR_INFO_ID_OAEP_PARAM             15
/**
 * A cryptographic identifier which indicates the surrender function.
 */
#define R_CR_INFO_ID_SURRENDER              16
/**
 * A cryptographic identifier which indicates the cryptographic
 * @ref R_CR_TYPE.
 */
#define R_CR_INFO_ID_CRYPTO_TYPE            17
/**
 * A cryptographic identifier which indicates the cryptographic @ref R_CR_IDS.
 */
#define R_CR_INFO_ID_CRYPTO_ID              18
/**
 * A cryptographic identifier which indicates the cryptographic @ref R_CR_SUB.
 */
#define R_CR_INFO_ID_CRYPTO_SUB             19
/**
 * A cryptographic identifier which indicates the block padding to use.<br>
 * 0 - no padding (same as not calling final) <br>
 * 1 - use padding for block ciphers
 */
#define R_CR_INFO_ID_BLOCK_PADDING          20
/**
 * A cryptographic identifier which indicates the flags. See @ref R_CR_FLAG
 * for more details.
 */
#define R_CR_INFO_ID_FLAGS                  21
/**
 * A cryptographic identifier which indicates the number of bits of the asymmetric
 * key.
 */
#define R_CR_INFO_ID_NUM_BITS               22  /** data type unsigned int */
/**
 * A cryptographic identifier which indicates the number of primes (RSA
 * MultiPrime).
 */
#define R_CR_INFO_ID_NUM_PRIMES             23  /** data type unsigned int */
/**
 * A cryptographic identifier which indicates the asymmetric public key.
 */
#define R_CR_INFO_ID_PUBLIC_KEY             24
/**
 * A cryptographic identifier which indicates the asymmetric private key.
 */
#define R_CR_INFO_ID_PRIVATE_KEY            25
/**
 * A cryptographic identifier which indicates the Digital Signature
 * Algorithm (DSA) prime number (<tt>P</tt>).
 */
#define R_CR_INFO_ID_DSA_P                  26
/**
 * A cryptographic identifier which indicates the Digital Signature
 * Algorithm (DSA) factor of the prime number (<tt>Q</tt>).
 */
#define R_CR_INFO_ID_DSA_Q                  27
/**
 * A cryptographic identifier which indicates the Digital Signature
 * Algorithm (DSA) generator (<tt>G</tt>).
 */
#define R_CR_INFO_ID_DSA_G                  28

/**
 * A cryptographic identifier which indicates the Diffie-Hellman prime length.
 */
#define R_CR_INFO_ID_DH_PRIME_LENGTH        29  /** data type unsigned int */
/**
 * A cryptographic identifier which indicates the Diffie-Hellman generator
 * order.
 */
#define R_CR_INFO_ID_DH_GENERATOR_ORDER     30
/**
 * A cryptographic identifier which indicates the RSA public exponent
 * (<tt>E</tt>).
 */
#define R_CR_INFO_ID_RSA_E                  31  /** data type unsigned int */
/**
 * A cryptographic identifier which indicates the Digital Signature
 * Algorithm (DSA) parameters.
 */
#define R_CR_INFO_ID_DSA_PARAMETERS         32
/**
 * A cryptographic identifier which indicates the signature.
 */
#define R_CR_INFO_ID_SIGNATURE              33
/**
 * A cryptographic identifier which indicates the Diffie-Hellman private key
 * value.
 */
#define R_CR_INFO_DH_PRIV_KEY               34
/**
 * A cryptographic identifier which indicates the random seed file name.
 */
#define R_CR_INFO_ID_RAND_FILE_NAME         48
/**
 * A cryptographic identifier which indicates the random seed write file.
 */
#define R_CR_INFO_ID_RAND_WRITE_FILE        49
/**
 * A cryptographic identifier which adds "entropy" into the random
 * generator. @ref R_ENTROPY_TYPE for valid options.
 */
#define R_CR_INFO_ID_RAND_ADD_ENTROPY       50
/**
 * A cryptographic identifier which indicates to load seed file into random
 * generator.
 */
#define R_CR_INFO_ID_RAND_LOAD_FILE         51
/**
 * A cryptographic identifier which indicates the random entropy collection
 * function.
 */
#define R_CR_INFO_ID_RAND_ENTROPY_FUNC      52
/**
 * A cryptographic identifier which indicates the R_RANDOM implementation
 * method structure.
 */
#define R_CR_INFO_ID_RANDOM                 53
/**
 * A cryptographic identifier which indicates the size of the seed (in Bytes)
 * to supply to a PRNG as defined by FIPS 186-2 Appendix 3.1. If the size of
 * the seed is changed the internal seeding information is also reset.
 *
 * @see #R_CR_INFO_ID_RAND_SEED_RESET
 */
#define R_CR_INFO_ID_RAND_BLOCK_SIZE        54
/**
 * A cryptographic identifier which indicates that an internal seed should be
 * used when not explicitly provided by the application via a call to
 * @ref R_CR_random_seed(). The seed will be procuded by calling a
 * customized entropy collection algorithm. By default autoseeding is
 * enabled.
 */
#define R_CR_INFO_ID_RAND_AUTO_SEED         56
/**
 * A cryptographic identifier which indicates the state of the key-seed
 * comparison test for the FIPS 186-2 PRNG. By default seed compare is
 * enabled.
 * @ref R_RNG_KEY_SEED_COMPARE for valid options.
 */
#define R_CR_INFO_ID_RAND_KEY_SEED_COMPARE  57
/**
 * A cryptographic identifier which indicates the state of the run-time tests
 * for the FIPS 186-2 PRNG. By default the run-time tests are enabled.
 * @ref R_RNG_TESTS for valid options.
 */
#define R_CR_INFO_ID_RAND_RUN_TIME_TESTS    58
/**
 * A cryptographic identifier which resets the seeding information for the
 * FIPS 186-2 PRNG. This option will initialize the seeding information to
 * a known state. Subsequent calls to #R_CR_random_bytes() will not succeed
 * until the generator has been seeded (or automatic seeding is switched on).
 */
#define R_CR_INFO_ID_RAND_SEED_RESET        59
/**
 * A cryptographic identifier which sets the value of the modulus for the
 * FIPS 186-2 PRNG.
 */
#define R_CR_INFO_ID_RAND_MODULUS           60
/**
 * A cryptographic identifier which sets the random object into a 
 * deterministic mode of operation for testing purposes. Only available
 * when using #R_CR_ID_RANDOM_OTP. By default the deterministic mode
 * of operation is enabled.
 */
#define R_CR_INFO_ID_RAND_PREDICTABLE_MODE  62
/**
 * A cryptographic idnetifier which sets against a random object a random
 * object with which to get random data from. Only available when using
 * #R_CR_ID_RANDOM_OTP.
 */
#define R_CR_INFO_ID_RAND_REAL_RANDOM       63
/**
 * A cryptographic identifier which indicates the Digital Signature
 * Algorithm (DSA) initial (<tt>SEED</tt>).
 */
#define R_CR_INFO_ID_DSA_SEED               64

/* next available value for R_CR_INFO_ID is: 65 */

/**
 * @}
 */

/**
 * @defgroup R_CR_FLAG Cryptographic Behavior Modifying Flags
 * This section details the flags used in conjunction with the cryptographic
 * objects to effect algorithm operations. These flags are algorithm-dependent.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * A cryptographic flag which indicates a symmetric cipher with no block
 * padding.
 */
#define R_CR_FLAG_CIPHER_NO_BLOCK_PADDING   0x0001
/**
 * A cryptographic flag which indicates a symmetric cipher key set.
 */
#define R_CR_FLAG_CIPHER_KEY_SET            0x0002
/**
 * A cryptographic flag which indicates a signature Distinguished Encoding
 * Rules (DER).
 */
#define R_CR_FLAG_DER_SIGNATURE             0x0004

/**
 * A cryptographic flag which indicates that the items contained in the R_CR
 * have been allocated locally.
 */
#define R_CR_FLAG_ITEMS_ALLOCED             0x0008

/**
 * A cryptographic flag which indicates that a random number generator has
 * been set against the cryptographic object.
 */
#define R_CR_FLAG_RANDOM_AVAIL              0x0010

/**
 * A cryptographic flag which indicates that the random number generator set
 * against the cryptographic object is an R_CR type.
 */
#define R_CR_FLAG_RANDOM_R_CR               0x0020


/**
 * @}
 */

/**
 * @defgroup R_ENTROPY_TYPE Random Entropy Types
 * This section describes the options that control the amount of entropy
 * collected by the random generator when #R_CR_INFO_ID_RAND_ADD_ENTROPY
 * is used.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * Indicates the "small" entropy collection routines should be called to
 * add entropy into the generator.
 */
#define R_CR_RANDOM_ENTROPY_TYPE_SMALL      1
/**
 * Indicates the "large" entropy collection routines should be called to
 * add entropy into the generator. A larger amount of entropy is collected
 * when using this option, however the collection time is longer.
 */
#define R_CR_RANDOM_ENTROPY_TYPE_LARGE      2
/**
 * @}
 */

/**
 * @defgroup R_RNG_KEY_SEED_COMPARE RNG Key-Seed Comparison States
 * This section describes the control options for the PRNG key-seed comparison.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * Indicates that the RNG key-seed comparison is not enabled.
 */
#define R_CR_RANDOM_RNG_KEY_SEED_COMPARE_OFF           0
/**
 * Indicates that the RNG key-seed comparison is currently active. This is the
 * default setting.
 */
#define R_CR_RANDOM_RNG_KEY_SEED_COMPARE_ON            1
/**
 * Indicates that the last attempt to generate random bytes failed to pass
 * the key-seed comparison.
 */
#define R_CR_RANDOM_RNG_KEY_SEED_COMPARE_FAILED        2
/**
 * @}
 */

/**
 * @defgroup R_RNG_TESTS RNG Run-Time Test States
 * This section describes the control options for the PRNG run-time tests.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * Indicates that the RNG run-time tests are not enabled.
 */
#define R_CR_RANDOM_RNG_TESTS_OFF           0
/**
 * Indicates that the RNG run-time tests are currently active. This is the
 * default setting.
 */
#define R_CR_RANDOM_RNG_TESTS_ON            1
/**
 * Indicates that the last attempt to generate random bytes failed to pass
 * the run-time test.
 */
#define R_CR_RANDOM_RNG_TESTS_FAILED        2
/**
 * @}
 */

/**
 * @defgroup CRYPTO_CTX_INFO Cryptographic Context Information Defines
 * The section details the defines used in the setting and/or retrieval of
 * data from a cryptographic context object.
 * The following table details the data types to pass into <i>param</i> when
 * calling R_CR_CTX_get_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_CR_CTX_INFO_ID_RANDOM</td>
 *     <td>#R_CR **</td>
 * </tr><tr>
 *     <td>#R_CR_CTX_INFO_ID_SURRENDER</td>
 *     <td>#R_SURRENDER **</td>
 * </tr><tr>
 * </tr></table>
 * @br
 *
 * The following table details the data types to pass into <i>param</i> when
 * calling R_CR_CTX_set_info().
 * @br
 * <table><tr>
 *     <td><b>Identifier</b></td>
 *     <td><b>Param Data Type</b></td>
 * </tr><tr>
 *     <td>#R_CR_CTX_INFO_ID_SURRENDER</td>
 *     <td>#R_SURRENDER *</td>
 * </tr><tr>
 * </tr></table>
 * @br
 * @ingroup CRYPTO_MODULE
 * @{
 */
/**
 * The random cryptographic context identifier.
 */
#define R_CR_CTX_INFO_ID_RANDOM             0
/**
 * A cryptographic context identifier which indicates the surrender function.
 */
#define R_CR_CTX_INFO_ID_SURRENDER          1
/**
 * @}
 */

/* Structure types */
/**
 * A cryptographic method type identifier.
 */
typedef struct r_cr_method_st               R_CR_METHOD;
/**
 * A cryptographic implementation method type identifier.
 */
typedef struct r_cr_imp_method_st           R_CR_IMP_METHOD;
/**
 * A cryptographic context object type identifier.
 */
typedef struct r_cr_ctx_st                  R_CR_CTX;
/**
 * A cryptographic object type identifier.
 */
typedef struct r_cr_st                      R_CR;
/**
 * A sign/verify data map object type identifier.
 */
typedef struct r_sign_vfy_map_obj_st        R_CR_SIGN_VFY_MAP;

/**
 * This structure is used to map a sign/verify identifier to an
 * asymmetric and digest identifier pair.
 */
struct r_sign_vfy_map_obj_st
    {
    /**
     * A cryptographic identifier which indicates the signature corresponding
     * to the digest and asymmetric cipher identifiers.
     */
    int sig_id;
    /**
     * A cryptographic identifier which indicates the digest corresponding to
     * the signature.
     */
    int dig_id;
    /**
     * A cryptographic identifier which indicates the asymmetric cipher
     * corresponding to the signature.
     */
    int pk_id;
    };

/**
 * @defgroup R_CR_RES Cryptographic Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library. For more information,
 * see @ref RES_LIST_GROUP.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * A small library interface that only supports the
 * <tt>get_resource</tt>, <tt>get_module</tt> and
 * <tt>get_module_data</tt> methods of the #R_LIB_CTX
 * interface. This is sufficient for normal use with the cryptograpic module.
 *
 * @see R_LIB_CTX_get_small_method().
 */
#define R_CR_RES_LIBRARY_SMALL \
        { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
          R_RES_FLAG_DEF, NULL, NULL, \
          (void *(*)(void *))R_LIB_CTX_get_small_method, NULL }

/**
 * Indicates the full #R_LIB_CTX interface.
 * @see R_LIB_CTX_get_default_method().
 */
#define R_CR_RES_LIBRARY \
        { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
          R_RES_FLAG_DEF, NULL, NULL, \
          (void *(*)(void *))R_LIB_CTX_get_default_method, NULL }

/**
 * The default list of algorithms available. Where there are optimized
 * implementations for an algorithm, the fastest is included in the default
 * list.
 *
 * @see R_CR_get_default_method() and R_CR_get_default_imp_method().
 */
#ifdef FIPS140_ONLY
#define R_CR_RES_CRYPTO_DEFAULT R_CR_RES_NIST
#else
#define R_CR_RES_CRYPTO_DEFAULT \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, NULL, \
      (void *(*)(void *))R_CR_get_default_method, \
      (void *(*)(void *))R_CR_get_default_imp_method }
#endif
/**
 * Binds a custom algorithm list to the cryptographic
 * module. The custom list must be specified with the
 * #R_CR_DEFINE_CUSTOM_CIPHER_LIST macro.
 * @see R_CR_get_default_method().
 */
#define R_CR_RES_CRYPTO_CUSTOM \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, NULL, \
      (void *(*)(void *))R_CR_get_default_method, \
      (void *(*)(void *))(R_CR_HAVE_CIPHER_LIST *(*)(void *))r_crm_custom_list_retriever }

/**
 * The default map which maps two #R_CR identifiers to a signature. For example,
 * #R_CR_ID_SHA1_RSA (#R_CR_ID_SHA1 and #R_CR_ID_RSA)
 *
 * @see R_CR_get_default_signature_map().
 */
#define R_CR_RES_SIGNATURE_MAP \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_MAP,\
          R_RES_FLAG_DEF, NULL, NULL, NULL,\
      (void *(*)(void *))R_CR_get_default_signature_map }

/**
 * The standard thread synchronization module. Only required for multi-threaded
 * applications to protect shared data.
 *
 * @see R_LOCK_get_default_method().
 */
#define R_CR_RES_LOCK \
    { R_RES_MOD_ID_LOCK, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, R_LOCK_lib_finish, \
      (void *(*)(void *))R_LOCK_get_default_method, NULL }

/**
 * The standard asymmetric key print module. This is only required if
 * R_PKEY_print() is used.
 */
#define R_CR_RES_PKEY_PRINT \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_PRINT_FUNC, \
      R_RES_SUB_ID_DEF, R_RES_FLAG_DEF, NULL, NULL, NULL, \
      (void *(*)(void *))R_PKEY_get_print_func }

/**
 * The RSA key module. This is only required if #R_PKEY functions are used.
 *
 * @see R_PKEY_pk_method().
 */
#define R_CR_RES_PKEY_RSA \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_RSA, \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_PKEY_pk_method, \
      NULL }

/**
 * The Digital Signature Algorithm (DSA) key module. This is only required
 * if #R_PKEY functions are used.
 * @see R_PKEY_pk_method().
 */
#define R_CR_RES_PKEY_DSA \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_DSA, \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_PKEY_pk_method, \
      NULL }

/**
 * The Diffie-Hellman key module. This is only required if #R_PKEY functions
 * are used.
 *
 * @see R_PKEY_pk_method().
 */
#define R_CR_RES_PKEY_DH \
    { R_RES_MOD_ID_PKEY, R_RES_IMPL_ID_DEF, R_PKEY_TYPE_DH, \
      R_RES_FLAG_DEF, NULL, NULL, (void *(*)(void *))R_PKEY_pk_method, \
      NULL }

/**
 * The standard random module. This is only required if asymmetric key or
 * random operations are used.
 *
 * @see R_rand_get_default().
 */
#define R_CR_RES_RAND \
    { R_RES_MOD_ID_RAND, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, \
      (int (*)(R_RES_LIST *, R_RES_ITEM *, void **))R_rand_lib_cleanup, \
      (void *(*)(void *))R_rand_get_default, NULL }

/**
 * The standard time module. This module is optional.
 *
 * @see R_TIME_get_time_mi_method().
 */
#define R_CR_RES_TIME \
    { R_RES_MOD_ID_TIME, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, NULL, \
      (void *(*)(void *))R_TIME_get_time_mi_method, NULL }

/**
 * Textual descriptions of common error codes. This is only required if using
 * R_CR_get_error() string functions.
 *
 * @see R_LIB_CTX_com_err_str_table().
 */
#define R_CR_RES_COMMON_ERROR_STRINGS \
    { R_RES_MOD_ID_LIBRARY, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_ERROR_STRINGS, \
      R_RES_FLAG_DEF, NULL, NULL, NULL, \
      (void *(*)(void *))R_LIB_CTX_com_err_str_table }

/**
 * Textual descriptions of cryptographic error reason codes. This is only
 * required if using R_CR_get_error() string functions.
 *
 * @see R_CR_get_reason_string_table().
 */
#define R_CR_RES_CRYPTO_REASON_STRINGS \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_REASON_STRINGS, \
          R_RES_FLAG_DEF, NULL, NULL, NULL, \
      (void *(*)(void *))R_CR_get_reason_string_table }

/**
 * Textual descriptions of cryptographic error function codes.
 * This is only required if using R_CR_get_error() string functions.
 *
 * @see R_CR_get_function_string_table().
 */
#define R_CR_RES_CRYPTO_FUNCTION_NAMES \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_FUNCTION_STRINGS,\
          R_RES_FLAG_DEF, NULL, NULL, NULL,\
      (void *(*)(void *))R_CR_get_function_string_table }

/**
 * Textual descriptions of cryptographic error detail codes.
 * This is only required if using R_CR_get_error() string functions.
 *
 * @see R_CR_get_detail_string_table().
 */
#define R_CR_RES_CRYPTO_DETAIL_STRINGS \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DETAIL_STRINGS, \
          R_RES_FLAG_DEF, NULL, NULL, NULL, \
      (void *(*)(void *))R_CR_get_detail_string_table }

/**
 * The mandatory marker to indicate the end of a resource list.
 */
#define R_CR_RES_END_OF_LIST \
    { R_RES_MOD_ID_RES_LIST, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_LIST_FLAG_STATIC, NULL, R_RES_LIST_lib_finish, NULL, NULL }

#ifndef NO_BIO
extern BIO_METHOD *r_cr_digest_get_bio_method();
extern BIO_METHOD *r_cr_encrypt_get_bio_method();
extern BIO_METHOD *r_cr_decrypt_get_bio_method();
extern BIO_METHOD *r_cr_cipher_get_bio_method();

/**
 * The #BIO method that digests data.
 */
#define R_CR_RES_BIO_DIGEST                                    \
    { R_RES_MOD_ID_BIO, BIO_TYPE_CR, R_CR_TYPE_DIGEST,         \
      R_RES_FLAG_DEF, NULL, NULL,                              \
      (void *(*)(void *))r_cr_digest_get_bio_method, NULL }

/**
 * The #BIO method that enciphers data.
 */
#define R_CR_RES_BIO_ENCRYPT                                   \
    { R_RES_MOD_ID_BIO, BIO_TYPE_CIPHER, R_CR_SUB_ENCRYPT,     \
      R_RES_FLAG_DEF, NULL, NULL,                              \
      (void *(*)(void *))r_cr_encrypt_get_bio_method, NULL }

/**
 * The #BIO method that deciphers data.
 */
#define R_CR_RES_BIO_DECRYPT                                   \
    { R_RES_MOD_ID_BIO, BIO_TYPE_CIPHER, R_CR_SUB_DECRYPT,     \
      R_RES_FLAG_DEF, NULL, NULL,                              \
      (void *(*)(void *))r_cr_decrypt_get_bio_method, NULL }

/**
 * The #BIO method that deciphers data that is read and enciphers data that is
 * written.
 */
#define R_CR_RES_BIO_CIPHER                                    \
    { R_RES_MOD_ID_BIO, BIO_TYPE_CIPHER,                       \
      R_CR_SUB_ENCRYPT | R_CR_SUB_DECRYPT, R_RES_FLAG_DEF,     \
      NULL, NULL,                                              \
      (void *(*)(void *))r_cr_cipher_get_bio_method, NULL }

#endif /* NO_BIO */

/**
 * @}
 */

#include "cryp_macros.h"

/**
 * @defgroup R_CR_FUNCTIONS Cryptographic Functions
 * This section details the functions used to construct, manipulate
 * and destroy cryptographic objects.
 * @ingroup CRYPTO_MODULE
 *
 * @{
 */
/**
 * @defgroup R_CR_CTX_FN Operation Functions
 * This section details the functions that facilitate the management
 * of #R_CR_CTX reference and #R_CR objects.
 *
 * @{
 */
#if !defined(NO_R_CR_METH_TABLE)
int R_CR_CTX_new(R_LIB_CTX *lib_ctx, R_RES_FLAG flag,
                         R_CR_CTX **crypto_ctx);
#endif /* !defined(NO_R_CR_METH_TABLE) */

#if !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE)
int R_CR_CTX_free(R_CR_CTX *ctx);

int R_CR_new(R_CR_CTX *ctx, R_CR_ALG_TYPE alg_type,
            R_CR_ALG_ID alg_id, R_CR_ALG_SUB alg_sub, R_CR **crypto);
int R_CR_dup(R_CR *crypto, R_CR **new_crypto);
int R_CR_free(R_CR *crypto);
/**
 * @}
 */
/**
 * @defgroup R_CR_SYM_FN Symmetric Operation Functions
 * This section outlines the functions that facilitate the encryption and
 * decryption of data in symmetric cryptographic operations.
 *
 * @{
 */
int R_CR_encrypt_init(R_CR *crypto, R_SKEY *key, R_ITEM *iv);
int R_CR_encrypt(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
int R_CR_encrypt_update(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
int R_CR_encrypt_final(R_CR *crypto,unsigned char *out, unsigned int *olen);

int R_CR_decrypt_init(R_CR *crypto, R_SKEY *key, R_ITEM *iv);
int R_CR_decrypt(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
int R_CR_decrypt_update(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
int R_CR_decrypt_final(R_CR *crypto,unsigned char *out, unsigned int *olen);
/**
 * @}
 */
/**
 * @defgroup R_CR_SIGN_FN Signature Operation Functions
 * This section outlines the functions that facilitate the signing and
 * verification of data in non-repudiation operations.
 *
 * @{
 */
int R_CR_sign_init(R_CR *crypto, R_PKEY *key);
int R_CR_sign(R_CR *crypto, unsigned char *data, unsigned int dlen,
    unsigned char *out, unsigned int *olen);
int R_CR_sign_update(R_CR *crypto, unsigned char *data, unsigned int dlen);
int R_CR_sign_final(R_CR *crypto,unsigned char *out, unsigned int *olen);

int R_CR_verify_init(R_CR *crypto, R_PKEY *key);
int R_CR_verify(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *signature, unsigned int slen,
    int *result);
int R_CR_verify_update(R_CR *crypto, unsigned char *data,
        unsigned int dlen);
int R_CR_verify_final(R_CR *crypto, unsigned char *signature,
        unsigned int sig_len, int *result);
/**
 * @}
 */

/**
 * @defgroup R_CR_ASYM_FN Asymmetric Operation Functions
 * This section details the functions that facilitate cryptographic
 * operations using public and private keys.
 *
 * @{
 */
int R_CR_asym_encrypt_init(R_CR *crypto, R_PKEY *key);
int R_CR_asym_encrypt(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *out,
                unsigned int *olen);
int R_CR_asym_decrypt_init(R_CR *crypto, R_PKEY *key);
int R_CR_asym_decrypt(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
/**
 * @}
 */
/**
 * @defgroup R_CR_DGST_FN Digest and MAC Operation Functions
 * This section details the functions that manage the creation of a digest.
 * Digests can be used in asymmetric algorithms or Message Authentication Code
 * (MAC) operations. MAC operations can be used in symmetric algorithms.
 * Digests are also used as part of the signing and verification process.
 *
 * @{
 */
int R_CR_digest_init(R_CR *crypto);
int R_CR_digest(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out,
    unsigned int *out_len);
int R_CR_digest_update(R_CR *crypto, unsigned char *data,
    unsigned int dlen);
int R_CR_digest_final(R_CR *crypto, unsigned char *out,
    unsigned int *olen);

int R_CR_mac_init(R_CR *crypto, R_SKEY *key);
int R_CR_mac(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out,
    unsigned int *olen);
int R_CR_mac_update(R_CR *crypto, unsigned char *data,
    unsigned int dlen);
int R_CR_mac_final(R_CR *crypto, unsigned char *out,
    unsigned int *olen);

int R_CR_verify_mac_init(R_CR *crypto, R_SKEY *key);
int R_CR_verify_mac(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *mac, unsigned int mac_len,
    int *result);
int R_CR_verify_mac_update(R_CR *crypto, unsigned char *data,
        unsigned int dlen);
int R_CR_verify_mac_final(R_CR *crypto, unsigned char *mac,
        unsigned int mac_len, int *result);
/**
 * @}
 */
/**
 * @defgroup R_CR_KE_FN Key Agreement Functions
 * This section outlines the functions that enable phased key agreement
 * operations. Diffie-Hellman is an algorithm implemented using key
 * agreement operations.
 *
 * @{
 */
int R_CR_key_exchange_init(R_CR *crypto, R_PKEY *params);
int R_CR_key_exchange_phase_1(R_CR *crypto, unsigned char *out,
    unsigned int *olen);
int R_CR_key_exchange_phase_2(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int * olen);
/**
 * @}
 */
/**
 * @defgroup R_CR_KEYGEN_FN Key Generation Functions
 * This section outlines the functions that facilitate key and key
 * parameter generation. Parameters can also be generated for use
 * in key agreement operations.
 *
 * @{
 */
int R_CR_generate_key_init(R_CR *crypto);
int R_CR_generate_key(R_CR *crypto, R_PKEY **key);

int R_CR_generate_parameter_init(R_CR *crypto);
int R_CR_generate_parameter(R_CR *crypto, R_PKEY **key);

/**
 * @}
 */

/**
 * @defgroup R_CR_RND_FN Random Number Generation Functions
 * This section outlines the functions that generate pseudo random numbers used
 * for padding and generating keys. The functions interact with the Pseudo
 * Random Number Generator (PRNG) state engine to produce a random number
 * stream.
 *
 * @{
 */
int R_CR_random_seed(R_CR *crypto, unsigned char *bytes, unsigned int len);
int R_CR_random_bytes(R_CR *crypto, unsigned int  dlen,
    unsigned char *obuf, unsigned int *olen);
/**
 * @}
 */
#endif /* !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE) */

/**
 * @addtogroup R_CR_CTX_FN
 *
 * @{
 */
int R_CR_get_info(R_CR *crypto, int id, void *param);
int R_CR_set_info(R_CR *crypto, int id, void *param);

int R_CR_CTX_get_info(R_CR_CTX *ctx, int id, void *param);
int R_CR_CTX_set_info(R_CR_CTX *ctx, int id, void *param);

int R_CR_CTX_alg_supported(R_CR_CTX *ctx, int alg_type, int alg_id,
    int alg_sub, int *is_supported);

const R_CR_SIGN_VFY_MAP *R_CR_get_default_signature_map(void *imp_data);

int R_CR_CTX_ids_to_sig_id(R_CR_CTX *ctx, int dig_id, int pkey_id, int *sig_id);
int R_CR_CTX_ids_from_sig_id(R_CR_CTX *ctx, int sig_id, int *dig_id,
    int *pkey_id);
/**
 * @}
 */
/**
 * @defgroup CRYP_ERR_FUNCS Cryptographic Error Functions
 * This section details the functions that enable the extraction of detailed
 * error information after an error has occurred in the cryptographic module.
 * @ingroup CME_ERR
 *
 * @{
 */

#if !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE)
int R_CR_get_error(R_CR *crypto, int *data);
int R_CR_get_reason(R_CR *crypto, int *data);
int R_CR_get_detail(R_CR *crypto, int *data);
int R_CR_get_function(R_CR *crypto, int *data);
int R_CR_get_line(R_CR *crypto, int *data);

int R_CR_get_file(R_CR *crypto, char **data);
int R_CR_get_error_string(R_CR *crypto, char **data);
int R_CR_get_reason_string(R_CR *crypto, char **data);
int R_CR_get_detail_string(R_CR *crypto, char **data);
int R_CR_get_function_string(R_CR *crypto, char **data);
#endif /* !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE) */


#if !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE)
/* error related strings */
R_STRTBL *R_CR_get_reason_string_table(void *imp_data);
R_STRTBL *R_CR_get_detail_string_table(void *imp_data);
R_STRTBL *R_CR_get_function_string_table(void *imp_data);
#endif /* !defined(NO_R_CR_FUNC) && !defined(NO_R_CR_METH_TABLE) */

#ifndef NO_BIO
BIO *BIO_new_CR_MD(R_LIB_CTX *ctx, int flag, int id);
#endif /* NO_BIO */
/**
 * @}
 */

/**
 * @addtogroup R_CR_CTX_FN
 *
 * @{
 */
int R_CR_ID_from_string(char *str, R_CR_ALG_ID *type);
int R_CR_ID_to_string(R_CR_ALG_ID type, unsigned int max_str_len, char *str);
int R_CR_TYPE_from_string(char *str, R_CR_ALG_TYPE *type);
int R_CR_TYPE_to_string(R_CR_ALG_TYPE type, unsigned int max_str_len, char *str);
int R_CR_SUB_from_string(char *str, R_CR_ALG_SUB *type);
int R_CR_SUB_to_string(R_CR_ALG_SUB type, unsigned int max_str_len, char *str);
/**
 * @}
 */
/* Default method */
/**
 * @addtogroup R_CR_CTX_FN
 * @{
 */
R_CR_METHOD *R_CR_get_default_method(void *imp_data);
R_CR_IMP_METHOD *R_CR_get_default_imp_method(void *imp_data);
/**
 * @}
 */

/*
 * @addtogroup R_CR_CTX_FN
 *
 * @{
 */
/**
 * @fn void R_CR_RES_CRYPTO_CUSTOM_METHOD(R_CR_METHOD *(*meth_fn)(void),
 *           R_CR_IMP_METHOD *(*alg_fn)(void))
 *
 * Binds a custom algorithm list and method table to the cryptographic module.
 * The custom method list must be specified with the
 * #R_CR_DEFINE_CUSTOM_METHOD_TABLE macro. The custom algorithm list must be
 * specified with the #R_CR_DEFINE_CUSTOM_CIPHER_LIST macro.
 *
 * @param meth_fn [In] The function returning the custom method list.
 * @param alg_fn  [In] The function returning the custom algorithm list.
 *
 */
#define R_CR_RES_CRYPTO_CUSTOM_METHOD(meth_fn, alg_fn) \
    { R_RES_MOD_ID_CRYPTO, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF, \
      R_RES_FLAG_DEF, NULL, NULL, \
      (void *(*)(void *))meth_fn, \
      (void *(*)(void *))alg_fn }

/**
 * @fn R_CR_IMP_METHOD *R_CR_DEFINE_CUSTOM_CIPHER_LIST
 *     (R_CR_IMP_METHOD list, void fn)
 *
 * Creates a function to return the custom algorithms. The custom algorithm
 * list is an array of type #R_CR_IMP_METHOD.
 *
 * @param list [In] The custom algorithm list.
 * @param fn   [In] The name of the function to create.
 *
 * @return   A cryptographic implementation method table.
 *
 * @see #R_CR_RES_CRYPTO_CUSTOM_METHOD.
 */
#define R_CR_DEFINE_CUSTOM_CIPHER_LIST(list, fn) \
    static R_CR_IMP_METHOD *fn(void)\
        { return((R_CR_IMP_METHOD *)list); } typedef int _dummy_int ## fn

/**
 * @fn R_CR_METHOD *R_CR_DEFINE_CUSTOM_METHOD_TABLE
 *     (R_CR_METHOD list, void fn)
 *
 * Creates a function to return the custom methods. The custom methods list
 * is a structure of #R_CR_METHOD.
 *
 * @param list [In] The custom methods list.
 * @param fn   [In] The name of the function to create.
 *
 * @return   A cryptographic method table.
 *
 * @see #R_CR_RES_CRYPTO_CUSTOM_METHOD.
 */
#define R_CR_DEFINE_CUSTOM_METHOD_TABLE(list, fn) \
    static R_CR_METHOD *fn(void *imp_data)\
    { return((R_CR_METHOD *)&list); }  typedef int _dummy_int ## fn

/**
 * @}
 */
/**
 * @}
 */

#ifdef FIPS140_ONLY
#include "r_nist.h"
#endif

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_CRYP_MOD_H */


