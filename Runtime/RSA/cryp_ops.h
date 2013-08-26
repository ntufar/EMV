/* $Id: cryp_ops.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryp_ops.h
 * This file contains the defines included in the custom cipher and method 
 * tables.
 *
 * @see @ref alg_defines and @ref method_defines.
 */

#ifndef HEADER_COMMON_CRYP_OPS_H
#define HEADER_COMMON_CRYP_OPS_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @defgroup cipher_defines Symmetric Ciphers
 *
 * This section outlines how to include symmetric algorithms in a custom 
 * cipher list for the cryptographic module. The following table lists 
 * the defines used when creating a custom cipher list. 
 *
 * @see R_CR_new(), R_CR_encrypt_init(), R_CR_encrypt_update(),
 * R_CR_encrypt_final(), R_CR_encrypt(), R_CR_decrypt_init(),
 * R_CR_decrypt_update(), R_CR_decrypt_final() and R_CR_decrypt().
 *
 * <b>Symmetric Ciphers</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td>
 *  <td><b> Algorithm Identifier </b></td>
 *  <td><b>Algorithm Type</b></td>
 *  <td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES128_CBC </td><td> #R_CR_ID_AES_128_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES128_CFB </td><td> #R_CR_ID_AES_128_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES128_ECB </td><td> #R_CR_ID_AES_128_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES128_OFB </td><td> #R_CR_ID_AES_128_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES192_CBC </td><td> #R_CR_ID_AES_192_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES192_CFB </td><td> #R_CR_ID_AES_192_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr><td>
 *     #R_CR_CIPHER_AES192_ECB </td><td> #R_CR_ID_AES_192_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES192_OFB </td><td> #R_CR_ID_AES_192_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES256_CBC </td><td> #R_CR_ID_AES_256_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES256_CFB </td><td> #R_CR_ID_AES_256_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES256_ECB </td><td> #R_CR_ID_AES_256_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_AES256_OFB </td><td> #R_CR_ID_AES_256_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES40_CBC </td><td> #R_CR_ID_DES_40_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES40_CFB </td><td> #R_CR_ID_DES_40_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_CBC </td><td> #R_CR_ID_DES_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_CFB </td><td> #R_CR_ID_DES_CFB64 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_ECB </td><td> #R_CR_ID_DES_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE </td><td> #R_CR_ID_DES_EDE </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE3 </td><td> #R_CR_ID_DES_EDE3 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE3_CBC </td><td> #R_CR_ID_DES_EDE3_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE3_CFB </td><td> #R_CR_ID_DES_EDE3_CFB64</td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE3_OFB</td>
 *    <td> #R_CR_ID_DES_EDE3_OFB64</td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE_CBC </td><td> #R_CR_ID_DES_EDE_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE_CFB </td><td> #R_CR_ID_DES_EDE_CFB64 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_EDE_OFB </td><td> #R_CR_ID_DES_EDE_OFB64 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_DES_OFB </td><td> #R_CR_ID_DES_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES128_CBC </td>
 *     <td> #R_CR_ID_AES_128_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES128_CFB </td>
 *     <td> #R_CR_ID_AES_128_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES128_ECB </td>
 *     <td> #R_CR_ID_AES_128_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES128_OFB </td>
 *     <td> #R_CR_ID_AES_128_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES192_CBC </td>
 *     <td> #R_CR_ID_AES_192_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES192_CFB </td>
 *     <td> #R_CR_ID_AES_192_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES192_ECB </td>
 *     <td> #R_CR_ID_AES_192_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES192_OFB </td>
 *     <td> #R_CR_ID_AES_192_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES256_CBC </td>
 *     <td> #R_CR_ID_AES_256_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES256_CFB </td>
 *     <td> #R_CR_ID_AES_256_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES256_ECB </td>
 *     <td> #R_CR_ID_AES_256_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_MEDIUM_AES256_OFB </td>
 *     <td> #R_CR_ID_AES_256_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_NULL </td><td> #R_CR_ID_NULL </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC2_40_CBC </td><td> #R_CR_ID_RC2_40_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC2_CBC </td><td> #R_CR_ID_RC2_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC2_CFB </td><td> #R_CR_ID_RC2_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC2_ECB </td><td> #R_CR_ID_RC2_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC2_OFB </td><td> #R_CR_ID_RC2_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4 </td><td> #R_CR_ID_RC4 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_40 </td><td> #R_CR_ID_RC4_40 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_40_586 </td><td> #R_CR_ID_RC4_40 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_40_686 </td><td> #R_CR_ID_RC4_40 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_40_786 </td><td> #R_CR_ID_RC4_40 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_586 </td><td> #R_CR_ID_RC4 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_686 </td><td> #R_CR_ID_RC4 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC4_786 </td><td> #R_CR_ID_RC4 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC5_CBC </td><td> #R_CR_ID_RC5_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC5_CBC_FAST </td><td> #R_CR_ID_RC5_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC5_CFB </td><td> #R_CR_ID_RC5_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC5_ECB </td><td> #R_CR_ID_RC5_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_RC5_OFB </td><td> #R_CR_ID_RC5_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES128_CBC </td>
 *     <td> #R_CR_ID_AES_128_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES128_CFB </td>
 *     <td> #R_CR_ID_AES_128_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES128_ECB </td>
 *     <td> #R_CR_ID_AES_128_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES128_OFB </td>
 *     <td> #R_CR_ID_AES_128_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES192_CBC </td>
 *     <td> #R_CR_ID_AES_192_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES192_CFB </td>
 *     <td> #R_CR_ID_AES_192_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES192_ECB </td>
 *     <td> #R_CR_ID_AES_192_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES192_OFB </td>
 *     <td> #R_CR_ID_AES_192_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES256_CBC </td>
 *     <td> #R_CR_ID_AES_256_CBC </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES256_CFB </td>
 *     <td> #R_CR_ID_AES_256_CFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES256_ECB </td>
 *     <td> #R_CR_ID_AES_256_ECB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_CIPHER_SMALL_AES256_OFB </td>
 *     <td> #R_CR_ID_AES_256_OFB </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 * </table>
 * <br>
 * 
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup digest_defines Digests
 * This section details the defines used to include digest algorithms in a
 * custom cipher list for the cryptographic module. The following table lists
 * the defines used when creating a custom cipher list.
 *
 * @see R_CR_new(), R_CR_digest_init(), R_CR_digest_update,
 * R_CR_digest_final() and R_CR_digest().
 *
 * <b>Digests</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td>
 *  <td><b> Algorithm Identifier </b></td>
 *  <td><b>Algorithm Type</b></td>
 *  <td><b>Algorithm Subtype</b>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_MD2 </td>
 *     <td> #R_CR_ID_MD2 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_MD5 </td>
 *     <td> #R_CR_ID_MD5 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_NULL </td>
 *     <td> #R_CR_ID_NULL </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_SHA1 </td>
 *     <td> #R_CR_ID_SHA1 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_SHA256 </td>
 *     <td> #R_CR_ID_SHA256 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_SHA384 </td>
 *     <td> #R_CR_ID_SHA384 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_DIGEST_SHA512 </td>
 *     <td> #R_CR_ID_SHA512 </td>
 *     <td> #R_CR_TYPE_CIPHER</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 * </table>
 * 
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup mac_defines Message Authentication Code
 * This section details the defines used to include Message Authentication
 * Code (MAC) and/or verify MAC algorithms in a custom cipher list for the
 * cryptographic module.
 *
 * @see R_CR_new(), R_CR_mac_init(), R_CR_mac_update(),
 * R_CR_mac_final() and R_CR_mac().
 *
 * <b>Message Authentication Codes</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_HMAC_MD5 </td>
 *     <td> #R_CR_ID_HMAC_MD5 </td>
 *     <td> #R_CR_TYPE_MAC </td>
 *     <td> #R_CR_SUB_MAC<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_HMAC_SHA1 </td>
 *     <td> #R_CR_ID_HMAC_SHA1 </td>
 *     <td> #R_CR_TYPE_MAC </td>
 *     <td> #R_CR_SUB_MAC<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
 /**
  * @}
  */
/**
 * @defgroup gen_defines Parameter/Key Generation
 * This section outlines the defines used to include key or parameter
 * generation algorithms in a custom cipher list for the cryptographic
 * module.
 *
 * @see R_CR_new(), R_CR_generate_key_init(), R_CR_generate_key(),
 * R_CR_generate_parameter_init() and R_CR_generate_parameter().
 *
 * <b>Key/Parameter Generation</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_KEYGEN_DSA </td>
 *     <td> #R_CR_ID_DSA_KEY_GENERATION </td>
 *     <td> #R_CR_TYPE_KEYGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_KEYGEN_RSA_VENDOR </td>
 *     <td> #R_CR_ID_RSA_KEY_GENERATION_VENDOR </td>
 *     <td> #R_CR_TYPE_KEYGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_KEYGEN_RSA </td>
 *     <td> #R_CR_ID_RSA_KEY_GENERATION_X931 </td>
 *     <td> #R_CR_TYPE_KEYGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_KEYGEN_RSA_X931 </td>
 *     <td> #R_CR_ID_RSA_KEY_GENERATION_X931 </td>
 *     <td> #R_CR_TYPE_KEYGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PARAMGEN_DH </td>
 *     <td> #R_CR_ID_DH_PARAMETER_GENERATION </td>
 *     <td> #R_CR_TYPE_PARAMGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PARAMGEN_DSA </td>
 *     <td> #R_CR_ID_DSA_PARAMETER_GENERATION </td>
 *     <td> #R_CR_TYPE_PARAMGEN </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup ke_defines Key Exchange
 * This section details the defines used to include key agreement
 * algorithms in a custom cipher list for the cryptographic module.
 *
 * @see R_CR_new(), R_CR_key_exchange_init(), R_CR_key_exchange_phase_1()
 * and R_CR_key_exchange_phase_2().
 *
 * <b>Key Agreement</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_KEY_EXCHANGE_DH </td>
 *     <td> #R_CR_ID_KE_DH </td>
 *     <td> #R_CR_TYPE_KEY_EXCHANGE </td>
 *     <td> #R_CR_SUB_NONE </td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup asym_defines Asymmetric Ciphers
 * This section details the defines used to include asymmetric key
 * algorithms in a custom cipher list for the cryptographic module.
 * 
 * @see R_CR_new(), R_CR_asym_encrypt_init(), R_CR_asym_encrypt(),
 * R_CR_asym_decrypt_init() and R_CR_asym_decrypt().
 *
 * <b>Asymmetric Ciphers</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PKEY_RSA </td>
 *     <td> #R_CR_ID_RSA </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PKEY_RSA_PKCS1 </td>
 *     <td> #R_CR_ID_RSA_PKCS1 </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PKEY_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_ID_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PKEY_RSA_PKCS1_SSL </td>
 *     <td> #R_CR_ID_RSA_PKCS1_SSL </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PKEY_RSA_PKCS1_RAW </td>
 *     <td> #R_CR_ID_RSA_PKCS1_RAW </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PRIVKEY_RSA </td>
 *     <td> #R_CR_ID_RSA </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PRIVKEY_RSA_PKCS1 </td>
 *     <td> #R_CR_ID_RSA_PKCS1 </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PRIVKEY_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_ID_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PRIVATE<br>
 *          #R_CR_SUB_ENCRYPT<br> 
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PUBKEY_RSA </td>
 *     <td> #R_CR_ID_RSA </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PUBKEY_RSA_PKCS1 </td>
 *     <td> #R_CR_ID_RSA_PKCS1 </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_PUBKEY_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_ID_RSA_PKCS1_OAEP </td>
 *     <td> #R_CR_TYPE_ASYM </td>
 *     <td> #R_CR_SUB_PUBLIC<br>
 *          #R_CR_SUB_ENCRYPT<br>
 *          #R_CR_SUB_DECRYPT </td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup sign_defines Signature Ciphers
 *
 * This section details the defines used to include signature and/or verify
 * algorithms in a custom cipher list for the cryptographic module.
 * 
 * @see R_CR_new(), R_CR_asym_encrypt_init(), R_CR_asym_encrypt(),
 * R_CR_asym_decrypt_init() and R_CR_asym_decrypt().
 *
 * <b>Signatures</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_DSA </td>
 *     <td> #R_CR_ID_DSA </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_DSA_SHA1 </td>
 *     <td> #R_CR_ID_SHA1_DSA </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_RSA_MD2 </td>
 *     <td> #R_CR_ID_MD2_RSA </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_RSA_MD5 </td>
 *     <td> #R_CR_ID_MD5_RSA </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_RSA_SHA1 </td>
 *     <td> #R_CR_ID_SHA1_RSA </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_RSA_SHA1_RAW </td>
 *     <td> #R_CR_ID_SHA1_RSA_RAW </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_SIG_RSA_X931_SHA1 </td>
 *     <td> #R_CR_ID_SHA1_RSA_X931 </td>
 *     <td> #R_CR_TYPE_SIGNATURE </td>
 *     <td> #R_CR_SUB_SIGN<br>
 *          #R_CR_SUB_VERIFY </td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup rand_defines Entropy Management
 * This section outlines the defines used to include pseudo random number
 * generation algorithms in a custom cipher list for the cryptographic module.
 * The following table lists the defines used when creating a custom
 * cipher list. 
 *
 * @see R_CR_new(), R_CR_random_seed() and R_CR_random_bytes().
 *
 * <b>PRNG</b>
 * @br
 * <table>
 *  <tr> <td>
 *  <b> Algorithm Define </b> </td><td><b> Algorithm Identifier </b></td>
 *  <td><b> Algorithm Type</b></td><td><b>Algorithm Subtype</b></td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_RANDOM_GENERATOR</td>
 *     <td> #R_CR_ID_RANDOM</td>
 *     <td> #R_CR_TYPE_RANDOM</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_RANDOM_MODULUS</td>
 *     <td> #R_CR_ID_RANDOM_MODULUS</td>
 *     <td> #R_CR_TYPE_RANDOM</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_RANDOM_ENTROPY </td>
 *     <td> #R_CR_ID_RANDOM_ENTROPY </td>
 *     <td> #R_CR_TYPE_RANDOM</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_RANDOM_GENERATOR_SYS </td>
 *     <td> #R_CR_ID_RANDOM_SYS </td>
 *     <td> #R_CR_TYPE_RANDOM</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 *  <tr> <td>
 *     #R_CR_RANDOM_OTP </td>
 *     <td> #R_CR_ID_RANDOM_OTP </td>
 *     <td> #R_CR_TYPE_RANDOM</td><td> #R_CR_SUB_NONE</td>
 *  </tr>
 * </table>
 * @br
 * @ingroup alg_defines
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup alg_defines Cryptographic Defines for Algorithm Identifiers
 * This section details the custom list defines to cryptographic identifiers
 * and supported operation types and subtypes.
 * The list of custom ciphers define includes the:<br>
 * <li>Algorithm type.</li>
 * <li>Algorithm identifier.</li>
 * <li>Algorithm subtype.</li>
 * <li>Algorithm method.</li>
 * <li>Implementation data.</li>
 *
 * @ingroup CRYPTO_MODULE
 * @{
 */
/**
 * Indicates that the digest is <tt>NULL</tt>.
 */
#define R_CR_DIGEST_NULL                    \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_NULL,                   \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_null,                \
            NULL                            \
        }
/**
 * Indicates that the digest is SHA-1.
 */
#define R_CR_DIGEST_SHA1                    \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_SHA1,                   \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_sha1,                \
            NULL                            \
        }
/**
 * Indicates that the digest is SHA-256.
 */
#define R_CR_DIGEST_SHA256                  \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_SHA256,                 \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_sha2_256,            \
            NULL                            \
        }
/**
 * Indicates that the digest is SHA-384.
 */
#define R_CR_DIGEST_SHA384                  \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_SHA384,                 \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_sha2_384,            \
            NULL                            \
        }
/**
 * Indicates that the digest is SHA-512.
 */
#define R_CR_DIGEST_SHA512                  \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_SHA512,                 \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_sha2_512,            \
            NULL                            \
        }
/**
 * Indicates that the digest is MD2.
 */
#define R_CR_DIGEST_MD2                     \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_MD2,                    \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_md2,                 \
            NULL                            \
        }
/**
 * Indicates that the digest is MD5.
 */
#define R_CR_DIGEST_MD5                     \
        {   R_CR_TYPE_DIGEST,               \
            R_CR_ID_MD5,                    \
            R_CR_SUB_NONE,                  \
            r_crn_dgst_md5,                 \
            NULL                            \
        }
/**
 * Indicates Message Authentication Code (MAC) using SHA-1.
 */
#define R_CR_HMAC_SHA1                      \
        {   R_CR_TYPE_MAC,                  \
            R_CR_ID_HMAC_SHA1,              \
            R_CR_SUB_MAC|R_CR_SUB_VERIFY,   \
            r_crn_hmac_sha1,                \
            NULL                            \
        }
/**
 * Indicates Message Authentication Code (MAC) using MD5.
 */
#define R_CR_HMAC_MD5                       \
        {   R_CR_TYPE_MAC,                  \
            R_CR_ID_HMAC_MD5,               \
            R_CR_SUB_MAC|R_CR_SUB_VERIFY,   \
            r_crn_hmac_md5,                 \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is <tt>NULL</tt>.
 */
#define R_CR_CIPHER_NULL                    \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_NULL,                   \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_null,                \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES CBC.
 */
#define R_CR_CIPHER_DES_CBC                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_cbc,             \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE.
 */
#define R_CR_CIPHER_DES_EDE                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede,             \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES ECB.
 */
#define R_CR_CIPHER_DES_ECB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_ECB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ecb,             \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE3.
 */
#define R_CR_CIPHER_DES_EDE3                \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE3,               \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede3,            \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE3 CBC.
 */
#define R_CR_CIPHER_DES_EDE3_CBC            \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE3_CBC,           \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede3_cbc,        \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES 40-bit CBC.
 */
#define R_CR_CIPHER_DES40_CBC               \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_40_CBC,             \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_40_cbc,          \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES 40-bit CFB.
 */
#define R_CR_CIPHER_DES40_CFB               \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_40_CFB,             \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_40_cfb,          \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES CFB.
 */
#define R_CR_CIPHER_DES_CFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_CFB64,              \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_cfb,             \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE CBC.
 */
#define R_CR_CIPHER_DES_EDE_CBC             \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede_cbc,         \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE CFB.
 */
#define R_CR_CIPHER_DES_EDE_CFB             \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE_CFB64,          \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede_cfb,         \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE OFB.
 */
#define R_CR_CIPHER_DES_EDE_OFB             \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE_OFB64,          \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede_ofb,         \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES EDE3 CFB.
 */
#define R_CR_CIPHER_DES_EDE3_CFB            \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE3_CFB64,         \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede3_cfb,        \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher DES EDE3 OFB64.
 */
#define R_CR_CIPHER_DES_EDE3_OFB            \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_EDE3_OFB64,         \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ede3_ofb,        \
            NULL                            \
        }
/**
 * Indicates that the symmetric cipher is DES OFB.
 */
#define R_CR_CIPHER_DES_OFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_DES_OFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_des_ofb,             \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA public operation.
 */
#define R_CR_PUBKEY_RSA                     \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA,                    \
            R_CR_SUB_PUBLIC|                \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_public,          \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA private operation.
 */
#define R_CR_PRIVKEY_RSA                    \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA,                    \
            R_CR_SUB_PRIVATE|               \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_private,         \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA public/private operation.
 */
#define R_CR_PKEY_RSA                       \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA,                    \
            R_CR_SUB_PUBLIC|R_CR_SUB_PRIVATE|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa,                 \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 public operation.
 */
#define R_CR_PUBKEY_RSA_PKCS1               \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1,              \
            R_CR_SUB_PUBLIC|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_public,    \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 operation.
 */
#define R_CR_PRIVKEY_RSA_PKCS1              \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1,              \
            R_CR_SUB_PRIVATE|               \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_private,   \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 public/private operation.
 */
#define R_CR_PKEY_RSA_PKCS1                 \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1,              \
            R_CR_SUB_PUBLIC|R_CR_SUB_PRIVATE|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1,           \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 RAW public operation.
 */
#define R_CR_PUBKEY_RSA_PKCS1_RAW           \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_RAW,          \
            R_CR_SUB_PUBLIC|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_public,    \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 RAW operation.
 */
#define R_CR_PRIVKEY_RSA_PKCS1_RAW          \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_RAW,          \
            R_CR_SUB_PRIVATE|               \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_private,   \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 RAW public/private operation.
 */
#define R_CR_PKEY_RSA_PKCS1_RAW             \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_RAW,          \
            R_CR_SUB_PUBLIC|R_CR_SUB_PRIVATE|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1,           \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 Optimal Asymmetric Encryption 
 * Padding (OAEP) public operation.
 */
#define R_CR_PUBKEY_RSA_PKCS1_OAEP          \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_OAEP,         \
            R_CR_SUB_PUBLIC|                \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_oaep_pub,  \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 Optimal Asymmetric Encryption 
 * Padding (OAEP) private operation.
 */
#define R_CR_PRIVKEY_RSA_PKCS1_OAEP         \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_OAEP,         \
            R_CR_SUB_PRIVATE|               \
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_oaep_priv, \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 Optimal Asymmetric Encryption 
 * Padding (OAEP) public/private operation.
 */
#define R_CR_PKEY_RSA_PKCS1_OAEP            \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_OAEP,         \
            R_CR_SUB_PUBLIC|R_CR_SUB_PRIVATE|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_oaep,      \
            NULL                            \
        }
/**
 * Indicates an asymmetric cipher RSA PKCS #1 SSL public/private operation.
 */
#define R_CR_PKEY_RSA_PKCS1_SSL             \
        {   R_CR_TYPE_ASYM,                 \
            R_CR_ID_RSA_PKCS1_SSL,          \
            R_CR_SUB_PUBLIC|R_CR_SUB_PRIVATE|\
            R_CR_SUB_ENCRYPT|R_CR_SUB_DECRYPT,\
            r_crn_asym_rsa_pkcs1_ssl,       \
            NULL                            \
        }
/**
 * Indicates an RSA X931 private operation.
 */
#define R_CR_PRIVKEY_RSA_X931                  \
        {   R_CR_TYPE_ASYM,                    \
            R_CR_ID_RSA_X931,                  \
            R_CR_SUB_PRIVATE|R_CR_SUB_ENCRYPT, \
            r_crn_asym_rsa_x931_priv,          \
            NULL                               \
        }
/**
 * Indicates an RSA X931 public operation.
 */
#define R_CR_PUBKEY_RSA_X931                   \
        {   R_CR_TYPE_ASYM,                    \
            R_CR_ID_RSA_X931,                  \
            R_CR_SUB_PUBLIC|R_CR_SUB_DECRYPT,  \
            r_crn_asym_rsa_x931_pub,           \
            NULL                               \
        }
/**
 * Indicates a RSA SHA-1 signature operation.
 */
#define R_CR_SIG_RSA_SHA1                   \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_SHA1_RSA,               \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_sign_vfy,                 \
            NULL                            \
        }
/**
 * Indicates a RSA SHA-1 RAW signature operation.
 */
#define R_CR_SIG_RSA_SHA1_RAW               \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_SHA1_RSA_RAW,           \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_sign_vfy,                 \
            NULL                            \
        }
/**
 * Indicates an RSA SHA-1 X931 signature operation.
 */
#define R_CR_SIG_RSA_X931_SHA1              \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_SHA1_RSA_X931,          \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_sign_vfy,                 \
            NULL                            \
        }
/**
 * Indicates an RSA MD2 signature operation.
 */
#define R_CR_SIG_RSA_MD2                    \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_MD2_RSA,                \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_sign_vfy,                 \
            NULL                            \
        }
/**
 * Indicates an RSA MD5 signature operation.
 */
#define R_CR_SIG_RSA_MD5                    \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_MD5_RSA,                \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_sign_vfy,                 \
            NULL                            \
        }
/**
 * Indicates a 'raw' DSA signature operation.
 */
#define R_CR_SIG_DSA                        \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_DSA,                    \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_raw_dsa_sign_vfy,         \
            NULL                            \
        }
/**
 * Indicates a DSA SHA-1 signature operation.
 */
#define R_CR_SIG_DSA_SHA1                   \
        {   R_CR_TYPE_SIGNATURE,            \
            R_CR_ID_SHA1_DSA,               \
            R_CR_SUB_SIGN|R_CR_SUB_VERIFY,  \
            r_crn_dsa_sign_vfy,             \
            NULL                            \
        }
/**
 * Indicates Diffie-Hellman key agreement.
 */
#define R_CR_KEY_EXCHANGE_DH                \
        {   R_CR_TYPE_KEY_EXCHANGE,         \
            R_CR_ID_KE_DH,                  \
            R_CR_SUB_NONE,                  \
            r_crn_ke_dh,                    \
            NULL                            \
        }
/**
 * Indicates an RC2 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC2_CBC                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC2_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc2_cbc,             \
            NULL                            \
        }
/**
 * Indicates an RC2 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC2_ECB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC2_ECB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc2_ecb,             \
            NULL                            \
        }
/**
 * Indicates an RC2 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC2_CFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC2_CFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc2_cfb,             \
            NULL                            \
        }
/**
 * Indicates an RC2 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC2_OFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC2_OFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc2_ofb,             \
            NULL                            \
        }
/**
 * Indicates an RC2 40-bit Cipher Block Chaining (CBC) symmetric cipher 
 * operation.
 */
#define R_CR_CIPHER_RC2_40_CBC              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC2_40_CBC,             \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc2_40_cbc,          \
            NULL                            \
        }
/**
 * Indicates an RC4 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4                     \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4,                    \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4,                 \
            NULL                            \
        }
/**
 * Indicates an RC4 40-bit symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_40                  \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4_40,                 \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_40,              \
            NULL                            \
        }
#ifdef CPU_X86
/**
 * Indicates an RC4 586 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_586                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4,                    \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_586,             \
            NULL                            \
        }
/**
 * Indicates an RC4 40-bit 586 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_40_586              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4_40,                 \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_40_586,          \
            NULL                            \
        }
/**
 * Indicates an RC4 686 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_686                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4,                    \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_686,             \
            NULL                            \
        }
/**
 * Indicates an RC4 40-bit 686 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_40_686              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4_40,                 \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_40_686,          \
            NULL                            \
        }
/**
 * Indicates an RC4 786 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_786                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4,                    \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_786,             \
            NULL                            \
        }
/**
 * Indicates an RC4 40-bit 786 symmetric cipher operation.
 */
#define R_CR_CIPHER_RC4_40_786              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC4_40,                 \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc4_40_786,          \
            NULL                            \
        }
#endif
/**
 * Indicates an RC5 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC5_CBC                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5_cbc,             \
            NULL                            \
        }
/**
 * Indicates an RC5 Cipher Block Chaining (CBC) symmetric cipher operation.
 * Included for compatibility with OpenSSL.
 */
#define R_CR_CIPHER_RC5_CBC_NO_PAD          \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5_cbc,             \
            NULL                            \
        }
/**
 * Indicates an RC5 Cipher Block Chaining (CBC) performance optimized 
 * symmetric cipher operation.
 */
#define R_CR_CIPHER_RC5_CBC_FAST            \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5f_cbc,            \
            NULL                            \
        }
/**
 * Indicates an RC5 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC5_ECB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_ECB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5_ecb,             \
            NULL                            \
        }
/**
 * Indicates an RC5 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC5_CFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_CFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5_cfb,             \
            NULL                            \
        }
/**
 * Indicates an RC5 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC5_OFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC5_OFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc5_ofb,             \
            NULL                            \
        }
/**
 * Indicates RSA key agreement generation.
 */
#define R_CR_KEYGEN_RSA_VENDOR               \
        {   R_CR_TYPE_KEYGEN,               \
            R_CR_ID_RSA_KEY_GENERATION_VENDOR, \
            R_CR_SUB_NONE,                  \
            r_crn_rsa_key_gen,              \
            NULL                            \
        }

/**
 * Indicates RSA key agreement generation.
 */
#define R_CR_KEYGEN_RSA_FIPS140_DEFAULT        \
        {   R_CR_TYPE_KEYGEN,               \
            R_CR_ID_RSA_KEY_GENERATION,     \
            R_CR_SUB_NONE,                  \
            r_crn_rsa_key_gen_x931,         \
            NULL                            \
        }

/**
 * Indicates RSA key agreement generation.
 */
#define R_CR_KEYGEN_RSA_NONFIPS140_DEFAULT     \
        {   R_CR_TYPE_KEYGEN,               \
            R_CR_ID_RSA_KEY_GENERATION,     \
            R_CR_SUB_NONE,                  \
            r_crn_rsa_key_gen,              \
            NULL                            \
        }
/**
 * Indicates RSA key agreement generation using X931.
 */
#define R_CR_KEYGEN_RSA_X931                \
        {   R_CR_TYPE_KEYGEN,               \
            R_CR_ID_RSA_KEY_GENERATION_X931, \
            R_CR_SUB_NONE,                  \
            r_crn_rsa_key_gen_x931,         \
            NULL                            \
        }
#define R_CR_KEYGEN_RSA R_CR_KEYGEN_RSA_X931
/**
 * Indicates Diffie-Hellman parameter generation.
 */
#define R_CR_PARAMGEN_DH                    \
        {   R_CR_TYPE_PARAMGEN,             \
            R_CR_ID_DH_PARAMETER_GENERATION,\
            R_CR_SUB_NONE,                  \
            r_crn_dh_param_gen,             \
            NULL                            \
        }
/**
 * Indicates Digital Signature Algorithm (DSA) parameter generation.
 */
#define R_CR_PARAMGEN_DSA                   \
        {   R_CR_TYPE_PARAMGEN,             \
            R_CR_ID_DSA_PARAMETER_GENERATION,\
            R_CR_SUB_NONE,                  \
            r_crn_dsa_param_gen,            \
            NULL                            \
        }
/**
 * Indicates Digital Signature Algorithm (DSA) key agreement generation.
 */
#define R_CR_KEYGEN_DSA                     \
        {   R_CR_TYPE_KEYGEN,               \
            R_CR_ID_DSA_KEY_GENERATION,     \
            R_CR_SUB_NONE,                  \
            r_crn_dsa_key_gen,              \
            NULL                            \
        }
/*
 * Indicates an RC6 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC6_CBC                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_cbc,             \
            NULL                            \
        }
/*
 * Indicates an RC6 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC6_ECB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_ECB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_ecb,             \
            NULL                            \
        }
/*
 * Indicates an RC6 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC6_CFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_CFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_cfb,             \
            NULL                            \
        }
/*
 * Indicates an RC6 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_RC6_OFB                 \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_OFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_ofb,             \
            NULL                            \
        }
/*
 * Indicates an RC6 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_RC6_CBC           \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_CBC,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_s_cbc,           \
            NULL                            \
        }
/*
 * Indicates an RC6 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_RC6_ECB           \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_ECB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_s_ecb,           \
            NULL                            \
        }
/*
 * Indicates an RC6 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_RC6_CFB           \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_CFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_s_cfb,           \
            NULL                            \
        }
/*
 * Indicates an RC6 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_RC6_OFB           \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_RC6_OFB,                \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_rc6_s_ofb,           \
            NULL                            \
        }
/**
 * Indicates an AES128 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES128_CBC              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_cbc,          \
            NULL                            \
        }
/**
 * Indicates an AES128 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES128_ECB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_ecb,          \
            NULL                            \
        }
/**
 * Indicates an AES128 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES128_CFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_cfb,          \
            NULL                            \
        }
/**
 * Indicates an AES128 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES128_OFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_ofb,          \
            NULL                            \
        }
/**
 * Indicates an AES192 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES192_CBC              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_cbc,          \
            NULL                            \
        }
/**
 * Indicates an AES192 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES192_ECB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_ecb,          \
            NULL                            \
        }
/**
 * Indicates an AES192 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES192_CFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_cfb,          \
            NULL                            \
        }
/**
 * Indicates an AES192 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES192_OFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_ofb,          \
            NULL                            \
        }
/**
 * Indicates an AES256 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES256_CBC              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_cbc,          \
            NULL                            \
        }
/**
 * Indicates an AES256 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES256_ECB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_ecb,          \
            NULL                            \
        }
/**
 * Indicates an AES256 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES256_CFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_cfb,          \
            NULL                            \
        }
/**
 * Indicates an AES256 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_AES256_OFB              \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_ofb,          \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES128 Cipher Block
 * Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES128_CBC       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_m_cbc,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES128 Electronic
 * Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES128_ECB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_m_ecb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES128 Cipher 
 * Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES128_CFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_m_cfb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES128 Output
 * Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES128_OFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_m_ofb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES192 Cipher Block
 * Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES192_CBC       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_m_cbc,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES192 Electronic Code
 * Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES192_ECB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_m_ecb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES192 Cipher Feedback
 * (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES192_CFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_m_cfb,        \
            NULL                            \
        }
/**
 * Indicates a symmetric cipher code size/performance trade-off optimized 
 * AES192 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES192_OFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_m_ofb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES256 Cipher Block
 * Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES256_CBC       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_m_cbc,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES256 Electronic
 * Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES256_ECB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_m_ecb,        \
            NULL                            \
        }
/**
 * Indicates a code size/performance trade-off optimized AES256 Cipher Feedback
 * (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES256_CFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_m_cfb,        \
            NULL                            \
        }
/**
 * Indicates a symmetric cipher code size/performance trade-off optimized 
 * AES256 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_MEDIUM_AES256_OFB       \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_m_ofb,        \
            NULL                            \
        }
/**
 * Indicates an AES128 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES128_CBC        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_s_cbc,        \
            NULL                            \
        }
/**
 * Indicates an AES128 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES128_ECB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_s_ecb,        \
            NULL                            \
        }
/**
 * Indicates an AES128 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES128_CFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_s_cfb,        \
            NULL                            \
        }
/**
 * Indicates an AES128 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES128_OFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_128_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes128_s_ofb,        \
            NULL                            \
        }
/**
 * Indicates an AES192 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES192_CBC        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_s_cbc,        \
            NULL                            \
        }
/**
 * Indicates an AES192 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES192_ECB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_s_ecb,        \
            NULL                            \
        }
/**
 * Indicates an AES192 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES192_CFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_s_cfb,        \
            NULL                            \
        }
/**
 * Indicates an AES192 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES192_OFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_192_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes192_s_ofb,        \
            NULL                            \
        }
/**
 * Indicates an AES256 Cipher Block Chaining (CBC) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES256_CBC        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CBC,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_s_cbc,        \
            NULL                            \
        }
/**
 * Indicates an AES256 Electronic Code Book (ECB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES256_ECB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_ECB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_s_ecb,        \
            NULL                            \
        }
/**
 * Indicates an AES256 Cipher Feedback (CFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES256_CFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_CFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_s_cfb,        \
            NULL                            \
        }
/**
 * Indicates an AES256 Output Feedback (OFB) symmetric cipher operation.
 */
#define R_CR_CIPHER_SMALL_AES256_OFB        \
        {   R_CR_TYPE_CIPHER,               \
            R_CR_ID_AES_256_OFB,            \
            R_CR_SUB_NONE,                  \
            r_crn_ciph_aes256_s_ofb,        \
            NULL                            \
        }
/**
 * Indicates the FIPS186-2 random generator.
 */
#define R_CR_RANDOM_GENERATOR               \
        {   R_CR_TYPE_RANDOM,               \
            R_CR_ID_RANDOM,                 \
            R_CR_SUB_NONE,                  \
            r_crn_random_fips1862_mth,      \
            NULL                            \
        }
/**
 * Indicates the FIPS186-2 global random generator.
 */
#define R_CR_RANDOM_GENERATOR_GLOBAL               \
        {   R_CR_TYPE_RANDOM,                      \
            R_CR_ID_RANDOM_GLOBAL,                 \
            R_CR_SUB_NONE,                         \
            r_crn_random_fips1862_global_mth,      \
            NULL                                   \
        }
/**
 * Indicates the FIPS186-2 random generator with modulus.
 */
#define R_CR_RANDOM_MODULUS                 \
        {   R_CR_TYPE_RANDOM,               \
            R_CR_ID_RANDOM_MODULUS,         \
            R_CR_SUB_NONE,                  \
            r_crn_random_fips1862_mod_mth,  \
            NULL                            \
        }
/**
 * Indicates an implementation that returns locally collected entropy.
 */
#define R_CR_RANDOM_ENTROPY                 \
        {   R_CR_TYPE_RANDOM,               \
            R_CR_ID_RANDOM_ENTROPY,         \
            R_CR_SUB_NONE,                  \
            r_crn_random_mth,               \
            NULL                            \
        }
/**
 * Indicates the random generator system.
 */
#define R_CR_RANDOM_GENERATOR_SYS           \
        {   R_CR_TYPE_RANDOM,               \
            R_CR_ID_RANDOM_SYS,             \
            R_CR_SUB_NONE,                  \
            r_crn_random_sys_mth,           \
            NULL                            \
        }
/**
 * Indicates the random that is a one time pad.
 */
#define R_CR_RANDOM_OTP                     \
        {   R_CR_TYPE_RANDOM,               \
            R_CR_ID_RANDOM_OTP,             \
            R_CR_SUB_NONE,                  \
            r_crn_random_otp_mth,           \
            NULL                            \
        }
/**
 * The End-Of-List (EOL) marker.
 */
#define R_CR_END_OF_LIST                    \
        {   R_CR_TYPE_NONE,                 \
            R_CR_ID_UNKNOWN,                \
            R_CR_ID_UNKNOWN,                \
            NULL,                           \
            NULL                            \
        }

/**
 * @}
 */

/**
 * @defgroup method_defines Cryptographic Method Defines
 * This section details the custom method table which is created for developers
 * requiring only the framework for operations specified in size-constrained
 * systems.<br>
 * <br>
 * A custom cipher list must be defined in conjunction with the custom method
 * table. Algorithms included in the custom cipher list will include the 
 * cipher code. However, ciphers may be unusable if the appropriate custom 
 * method entries are not defined.<br>
 * <br>
 * The custom method is a fixed size table and requires a correct number
 * of entries for correct operation. Incorrect definitions will cause
 * unexpected results. 
 * <br>
 * The following methods are support by the cryptographic module:
 * <ul> 
 * <li><tt>_SMALL</tt> - this method removes the convenience functions, leaving
 * only <tt>_init</tt>, <tt>_update</tt> and <tt>final</tt>, with the exception
 * of key generation which removes the parameter generation functions. </li>
 * <li><tt>_NOT_IMPLEMENTED</tt> - <tt>R_CR_</tt> functions defined with this
 * method will return #R_ERROR_NOT_IMPLEMENTED.</li>
 * <li><tt>RANDOM</tt> - when a random method is required but random seeding is
 * not, entropy can be added to a random object via R_CR_set_info().
 * Random methods are also supplied via the library resource list, as different
 * modules of the library require random objects to be available, without
 * the necessity of the library. The library utilizes the same random
 * structures if they are available.</li>
 * </ul>
 * <br>
 * <table>
 * <tr>
 *     <td><b>Method Option Standard</b></td>
 *     <td><b>Method Option Reduced Functions</b></td>
 *     <td><b>Method Option Not Implemented</b></td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_REQUIRED </td>
 *     <td>N/A</td>
 *     <td>N/A</td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_ERRINFO </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_ERRINFO_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_INFO </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_INFO_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_SYM_ENC </td>
 *     <td> #R_CR_METHOD_SYM_ENC_SMALL </td>
 *     <td> #R_CR_METHOD_SYM_ENC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_SYM_DEC </td>
 *     <td> #R_CR_METHOD_SYM_DEC_SMALL </td>
 *     <td> #R_CR_METHOD_SYM_DEC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_SIGN </td>
 *     <td> #R_CR_METHOD_SIGN_SMALL </td>
 *     <td> #R_CR_METHOD_SIGN_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_VERIFY </td>
 *     <td> #R_CR_METHOD_VERIFY_SMALL </td>
 *     <td> #R_CR_METHOD_VERIFY_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_ASYM_ENC </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_ASYM_ENC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_ASYM_DEC </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_ASYM_DEC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_DIGEST </td>
 *     <td> #R_CR_METHOD_DIGEST_SMALL </td>
 *     <td> #R_CR_METHOD_DIGEST_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_MAC </td>
 *     <td> #R_CR_METHOD_MAC_SMALL </td>
 *     <td> #R_CR_METHOD_MAC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_VERIFY_MAC </td>
 *     <td> #R_CR_METHOD_VERIFY_MAC_SMALL </td>
 *     <td> #R_CR_METHOD_VERIFY_MAC_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_KE </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_KE_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_KEY_GEN </td>
 *     <td> #R_CR_METHOD_KEY_GEN_SMALL </td>
 *     <td> #R_CR_METHOD_KEY_GEN_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_RAND_SEED </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_RAND_SEED_NOT_IMPLEMENTED </td>
 * </tr>
 * <tr>
 *     <td> #R_CR_METHOD_RAND_GEN </td>
 *     <td>N/A</td>
 *     <td> #R_CR_METHOD_RAND_GEN_NOT_IMPLEMENTED </td>
 * </tr>
 * </table>
 * @ingroup CRYPTO_MODULE
 * @{
 */
/* Required definition to use the cryptographic module */
/**
 * The cryptographic method table entry required.
 */
#define R_CR_METHOD_REQUIRED    \
        r_crm_ctx_new,          \
        r_crm_ctx_free,         \
        r_crm_new,              \
        r_crm_dup,              \
        r_crm_free

/* Cryptographic error information may not be available depending on
 * library compile options.
 */
#ifndef NO_CRYPTO_ERR
/**
 * Indicates the cryptographic method table entry for error information.
 */
#define R_CR_METHOD_ERRINFO \
    r_crm_get_errinfo
#else
/**
 * Indicates the cryptographic method table entry for error information.
 */
#define R_CR_METHOD_ERRINFO \
    (int(*)(R_CR *, int, void **))r_crm_not_implemented
#endif

/**
 * Indicates the cryptographic method table entry for not implemented error 
 * information.
 */
#define R_CR_METHOD_ERRINFO_NOT_IMPLEMENTED \
    (int(*)(R_CR *, int, void **))r_crm_not_implemented

/* Cryptographic information set and get functions */
/**
 * Indicates the cryptographic method table entry for set/get information.
 */
#define R_CR_METHOD_INFO  \
        r_crm_get_info,   \
        r_crm_set_info

/**
 * Indicates the cryptographic method table entry not implemented set/get 
 * information.
 */
#define R_CR_METHOD_INFO_NOT_IMPLEMENTED                             \
        (int (*)(R_CR *, int, void **))r_crm_not_implemented, \
        (int (*)(R_CR *, int, void *))r_crm_not_implemented

/* Symmetric cipher encrypt operations */
/**
 * Indicates the cryptographic method table entry for symmetric encryption.
 */
#define R_CR_METHOD_SYM_ENC   \
        r_crm_encrypt_init,   \
        r_crm_cipher,         \
        r_crm_cipher_update,  \
        r_crm_cipher_final

/* Symmetric cipher encrypt Small implementation remove short cut function */
/**
 * Indicates the cryptographic method table entry for symmetric encryption with
 * small code optimized.
 */
#define R_CR_METHOD_SYM_ENC_SMALL                                        \
        r_crm_encrypt_init,                                              \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
             unsigned int *))r_crm_not_implemented,                      \
        r_crm_cipher_update,                                             \
        r_crm_cipher_final

/**
 * Indicates the cryptographic method table entry for not implemented symmetric
 * encryption.
 */
#define R_CR_METHOD_SYM_ENC_NOT_IMPLEMENTED                        \
        (int (*)(R_CR *, R_SKEY *, R_ITEM *))r_crm_not_implemented,        \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *,   \
             unsigned int *))r_crm_not_implemented,                        \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *,   \
             unsigned int *))r_crm_not_implemented,                        \
        (int (*)(R_CR *, unsigned char *, unsigned int *))r_crm_not_implemented

/* Symmetric cipher decrypt operations */
/**
 * Indicates the cryptographic method table entry for symmetric decryption.
 */
#define R_CR_METHOD_SYM_DEC     \
        r_crm_decrypt_init,     \
        r_crm_cipher,           \
        r_crm_cipher_update,    \
        r_crm_cipher_final

/* Symmetric Cipher Decrypt small implementation remove short cut function */
/**
 * Indicates the cryptographic method table entry for symmetric decryption 
 * with small code optimized.
 */
#define R_CR_METHOD_SYM_DEC_SMALL                                          \
        r_crm_decrypt_init,                                                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *,   \
             unsigned int *))r_crm_not_implemented,                        \
        r_crm_cipher_update,                                               \
        r_crm_cipher_final

/**
 * Indicates the cryptographic method table entry for not implemented symmetric
 * decryption.
 */
#define R_CR_METHOD_SYM_DEC_NOT_IMPLEMENTED                                \
        (int (*)(R_CR *, R_SKEY *, R_ITEM *))r_crm_not_implemented,        \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *,   \
             unsigned int *))r_crm_not_implemented,                        \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *,   \
             unsigned int *))r_crm_not_implemented,                        \
        (int (*)(R_CR *, unsigned char *, unsigned int *))r_crm_not_implemented

/* Sign operations, dependant on DIGEST and ASYM operations */
/**
 * Indicates the cryptographic method table entry for signature operations.
 */
#define R_CR_METHOD_SIGN     \
        r_crm_sign_vfy_init, \
        r_crm_sign,          \
        r_crm_sign_update,   \
        r_crm_sign_final

/* Sign operations small, remove short cut function */
/**
 * Indicates the cryptographic method table entry for signature operations 
 * with small code optimized.
 */
#define R_CR_METHOD_SIGN_SMALL                                           \
        r_crm_sign_vfy_init,                                             \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        r_crm_sign_update,                                               \
        r_crm_sign_final

/**
 * Indicates the cryptographic method table entry for not implemented 
 * signature operation.
 */
#define R_CR_METHOD_SIGN_NOT_IMPLEMENTED                                 \
        (int (*)(R_CR *, R_PKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        (int (*)(R_CR *, unsigned char *, unsigned int))                 \
            r_crm_not_implemented,                                       \
        (int (*)(R_CR *, unsigned char *, unsigned int *))               \
        r_crm_not_implemented

/* Signature verification operations */
/**
 * Indicates the cryptographic method table entry for signature verification.
 */
#define R_CR_METHOD_VERIFY   \
        r_crm_sign_vfy_init, \
        r_crm_verify,        \
        r_crm_verify_update, \
        r_crm_verify_final

/* Signature Verification operations small, remove short cut function */
/**
 * Indicates the cryptographic method table entry for signature verification 
 * with small code optimized.
 */
#define R_CR_METHOD_VERIFY_SMALL                                         \
        r_crm_sign_vfy_init,                                             \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int, int *))r_crm_not_implemented,                  \
        r_crm_verify_update,                                             \
        r_crm_verify_final

/**
 * Indicates the cryptographic method table entry for not implemented 
 * signature verification.
 */
#define R_CR_METHOD_VERIFY_NOT_IMPLEMENTED                               \
        (int (*)(R_CR *, R_PKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int, int *))r_crm_not_implemented,                  \
        (int (*)(R_CR *, unsigned char *, unsigned int))r_crm_not_implemented,\
        (int (*)(R_CR *, unsigned char *, unsigned int, int *))          \
            r_crm_not_implemented

/* Asymmetric key encrypt operations */
/**
 * Indicates the cryptographic method table entry for asymmetric encryption.
 */
#define R_CR_METHOD_ASYM_ENC          \
        r_crm_asym_init,              \
        r_crm_asym_enc

/**
 * Indicates the cryptographic method table entry for not implemented 
 * asymmetric encryption.
 */
#define R_CR_METHOD_ASYM_ENC_NOT_IMPLEMENTED                             \
        (int (*)(R_CR *, R_PKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented

/* Asymmetric key decrypt operations */
/**
 * Indicates the cryptographic method table entry for asymmetric decryption.
 */
#define R_CR_METHOD_ASYM_DEC \
        r_crm_asym_init,     \
        r_crm_asym_dec

/**
 * Indicates the cryptographic method table entry for not implemented 
 * asymmetric decryption.
 */
#define R_CR_METHOD_ASYM_DEC_NOT_IMPLEMENTED                                    \
        (int (*)(R_CR *, R_PKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented

/* Digest Operations */
/**
 * Indicates the cryptographic method table entry for a digest operation.
 */
#define R_CR_METHOD_DIGEST   \
        r_crm_digest_init,   \
        r_crm_digest,        \
        r_crm_digest_update, \
        r_crm_digest_final

/* Digest Operations small, short cut function removed */
/**
 * Indicates the cryptographic method table entry for a digest operation 
 * with small code optimized.
 */
#define R_CR_METHOD_DIGEST_SMALL                                         \
        r_crm_digest_init,                                               \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        r_crm_digest_update,                                             \
        r_crm_digest_final

/**
 * Indicates the cryptographic method table entry for not implemented digest 
 * operation.
 */
#define R_CR_METHOD_DIGEST_NOT_IMPLEMENTED                               \
        (int (*)(R_CR *))r_crm_not_implemented,                          \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        (int (*)(R_CR *, unsigned char *,unsigned int))r_crm_not_implemented, \
        (int (*)(R_CR *, unsigned char *,unsigned int *))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for Message Authentication
 * Code (MAC).
 */
#define R_CR_METHOD_MAC   \
        r_crm_mac_init,   \
        r_crm_mac,        \
        r_crm_mac_update, \
        r_crm_mac_final

/**
 * Indicates the cryptographic method table entry for Message Authentication
 * Code (MAC) with small code optimized.
 */
#define R_CR_METHOD_MAC_SMALL                                            \
        r_crm_mac_init,                                                  \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        r_crm_mac_update,                                                \
        r_crm_mac_final

/**
 * Indicates the cryptographic method table entry for not implemented
 * Message Authentication Code (MAC).
 */
#define R_CR_METHOD_MAC_NOT_IMPLEMENTED                                  \
        (int (*)(R_CR *, R_SKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented,                       \
        (int (*)(R_CR *, unsigned char *,unsigned int))r_crm_not_implemented, \
        (int (*)(R_CR *, unsigned char *,unsigned int *))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for signature verification 
 * with Message Authentication Code (MAC).
 */
#define R_CR_METHOD_VERIFY_MAC       \
        r_crm_mac_init,              \
        r_crm_verify_mac,            \
        r_crm_verify_mac_update,     \
        r_crm_verify_mac_final

/**
 * Indicates the cryptographic method table entry for signature verification
 * with small code optimized Message Authentication Code (MAC).
 */
#define R_CR_METHOD_VERIFY_MAC_SMALL                                     \
        r_crm_mac_init,                                                  \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int, int *))r_crm_not_implemented,                  \
        r_crm_verify_mac_update,                                         \
        r_crm_verify_mac_final

/**
 * Indicates the cryptographic method table entry for not implemented 
 * signature verification with Message Authentication Code (MAC).
 */
#define R_CR_METHOD_VERIFY_MAC_NOT_IMPLEMENTED                           \
        (int (*)(R_CR *, R_SKEY *))r_crm_not_implemented,                \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int, int *))r_crm_not_implemented,                  \
        (int (*)(R_CR *,unsigned char *, unsigned int))r_crm_not_implemented, \
        (int (*)(R_CR *,unsigned char *, unsigned int, int *))           \
            r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for key agreement.
 */
#define R_CR_METHOD_KE    \
        r_crm_ke_init,    \
        r_crm_ke_phase_1, \
        r_crm_ke_phase_2

/**
 * Indicates the cryptographic method table entry for not implemented key 
 * agreement.
 */
#define R_CR_METHOD_KE_NOT_IMPLEMENTED                     \
        (int (*)(R_CR *, R_PKEY *))r_crm_not_implemented,  \
        (int (*)(R_CR *, unsigned char *, unsigned int *)) \
            r_crm_not_implemented,                         \
        (int (*)(R_CR *, unsigned char *, unsigned int, unsigned char *, \
            unsigned int *))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for key agreement generation.
 */
#define R_CR_METHOD_KEY_GEN   \
        r_crm_kgen_init,      \
        r_crm_generate_key,   \
        r_crm_pgen_init,      \
        r_crm_generate_params

/**
 * Indicates the cryptographic method table entry for key agreement generation
 * with small code optimized.
 */
#define R_CR_METHOD_KEY_GEN_SMALL               \
        r_crm_kgen_init,                        \
        r_crm_generate_key,                     \
        (int (*)(R_CR *))r_crm_not_implemented, \
        (int (*)(R_CR *, R_PKEY **))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for not implemented key 
 * agreement generation.
 */
#define R_CR_METHOD_KEY_GEN_NOT_IMPLEMENTED                \
        (int (*)(R_CR *))r_crm_not_implemented,            \
        (int (*)(R_CR *, R_PKEY **))r_crm_not_implemented, \
        (int (*)(R_CR *))r_crm_not_implemented,            \
        (int (*)(R_CR *, R_PKEY **))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for random seeding.
 */
#define R_CR_METHOD_RAND_SEED \
        r_crm_random_seed

/**
 * Indicates the cryptographic method table entry for not implemented 
 * random seeding.
 */
#define R_CR_METHOD_RAND_SEED_NOT_IMPLEMENTED \
        (int (*)(R_CR *,unsigned char *, unsigned int))r_crm_not_implemented

/**
 * Indicates the cryptographic method table entry for the random generator.
 */
#define R_CR_METHOD_RAND_GEN \
        r_crm_gen_rand

/**
 * Indicates the cryptographic method table entry for not implemented 
 * random generator.
 */
#define R_CR_METHOD_RAND_GEN_NOT_IMPLEMENTED \
        (int (*)(R_CR *,unsigned int, unsigned char *, unsigned int *)) \
            r_crm_not_implemented

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_CRYP_OPS_H */


