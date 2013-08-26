/* $Id: cryp_err.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryp_err.h
 * This file contains the defines and includes associated with cryptographic
 * error handling.
 */

#ifndef HEADER_COMMON_CRYP_ERR_H
#define HEADER_COMMON_CRYP_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_errinf.h"
#include "r_strtbl.h"

#ifndef NO_CRYPTO_ERR
#define R_CR_log_error(estr,code,res,det,func)                          \
            R_ERR_INFO_log_error( (estr), (code), (res), (det), (func), \
            R_ERR_INFO_FILE_NAME,                                       \
            R_ERR_INFO_LINE)
#else
#define R_CR_log_error(estr,code,res,det,func)
#endif

/* defines for what info to retrieve out of the errinfo */
#define R_CR_ERRINFO_ERROR                  1
#define R_CR_ERRINFO_REASON                 2
#define R_CR_ERRINFO_DETAIL                 3
#define R_CR_ERRINFO_FUNCTION               4
#define R_CR_ERRINFO_LINE                   5
#define R_CR_ERRINFO_FILE                   6

#define R_CR_ERRINFO_ERROR_STRING           11
#define R_CR_ERRINFO_REASON_STRING          12
#define R_CR_ERRINFO_DETAIL_STRING          13
#define R_CR_ERRINFO_FUNCTION_STRING        14
/* function definitions                */
/**
 * @defgroup CRYP_PUB_API_FN_ID Public Function Identifiers
 * This section details the defines used for identifying the cryptographic
 * function where an error occurred.
 * @see R_CR_get_function(), R_CR_get_error() and @ref CRYP_ERR_FN_STR.
 * @ingroup R_ERROR_IDS 
 * @{
 */
/**
 * The identifier for functions unknown to the cryptographic module.
 */
#define R_CR_F_NO_FUNCTION                  0
/**
 * The identifier for R_CR_CTX_new().
 */
#define R_CR_F_R_CR_CTX_NEW                 1
/**
 * The identifier for R_CR_CTX_free().
 */
#define R_CR_F_R_CR_CTX_FREE                2
/**
 * The identifier for R_CR_CTX_get_info().
 */
#define R_CR_F_R_CR_CTX_GET_INFO            3
/**
 * The identifier for R_CR_CTX_set_info().
 */
#define R_CR_F_R_CR_CTX_SET_INFO            4
/**
 * The identifier for R_CR_new().
 */
#define R_CR_F_R_CR_NEW                     5
/**
 * The identifier for R_CR_dup().
 */
#define R_CR_F_R_CR_DUP                     6
/**
 * The identifier for R_CR_free().
 */
#define R_CR_F_R_CR_FREE                    7
/**
 * The identifier for R_CR_encrypt_init().
 */
#define R_CR_F_R_CR_ENCRYPT_INIT            8
/**
 * The identifier for R_CR_encrypt().
 */
#define R_CR_F_R_CR_ENCRYPT                 9
/**
 * The identifier for R_CR_encrypt_update().
 */
#define R_CR_F_R_CR_ENCRYPT_UPDATE          10
/**
 * The identifier for R_CR_encrypt_final().
 */
#define R_CR_F_R_CR_ENCRYPT_FINAL           11
/**
 * The identifier for R_CR_decrypt_init().
 */
#define R_CR_F_R_CR_DECRYPT_INIT            12
/**
 * The identifier for R_CR_decrypt().
 */
#define R_CR_F_R_CR_DECRYPT                 13
/**
 * The identifier for R_CR_decrypt_update().
 */
#define R_CR_F_R_CR_DECRYPT_UPDATE          14
/**
 * The identifier for R_CR_decrypt_final().
 */
#define R_CR_F_R_CR_DECRYPT_FINAL           15
/**
 * The identifier for R_CR_sign_init().
 */
#define R_CR_F_R_CR_SIGN_INIT               16
/**
 * The identifier for R_CR_sign().
 */
#define R_CR_F_R_CR_SIGN                    17
/**
 * The identifier for R_CR_sign_update().
 */
#define R_CR_F_R_CR_SIGN_UPDATE             18
/**
 * The identifier for R_CR_sign_final().
 */
#define R_CR_F_R_CR_SIGN_FINAL              19
/**
 * The identifier for R_CR_verify_init().
 */
#define R_CR_F_R_CR_VERIFY_INIT             20
/**
 * The identifier for R_CR_verify().
 */
#define R_CR_F_R_CR_VERIFY                  21
/**
 * The identifier for R_CR_verify_update().
 */
#define R_CR_F_R_CR_VERIFY_UPDATE           22
/**
 * The identifier for R_CR_verify_final().
 */
#define R_CR_F_R_CR_VERIFY_FINAL            23
/**
 * The identifier for R_CR_verify_final().
 */
#define R_CR_F_R_CR_ASYM_ENCRYPT_INIT       24
/**
 * The identifier for R_CR_verify_final().
 */
#define R_CR_F_R_CR_ASYM_ENCRYPT            25
/**
 * The identifier for R_CR_asym_decrypt_init().
 */
#define R_CR_F_R_CR_ASYM_DECRYPT_INIT       26
/**
 * The identifier for R_CR_asym_decrypt().
 */
#define R_CR_F_R_CR_ASYM_DECRYPT            27
/**
 * The identifier for R_CR_digest_init().
 */
#define R_CR_F_R_CR_DIGEST_INIT             28
/**
 * The identifier for R_CR_digest().
 */
#define R_CR_F_R_CR_DIGEST                  29
/**
 * The identifier for R_CR_digest_update().
 */
#define R_CR_F_R_CR_DIGEST_UPDATE           30
/**
 * The identifier for R_CR_digest_final().
 */
#define R_CR_F_R_CR_DIGEST_FINAL            31
/**
 * The identifier for R_CR_key_exchange_init().
 */
#define R_CR_F_R_CR_KE_INIT                 32
/**
 * The identifier for R_CR_key_exchange_phase_1().
 */
#define R_CR_F_R_CR_KE_PHASE_1              33
/**
 * The identifier for R_CR_key_exchange_phase_2().
 */
#define R_CR_F_R_CR_KE_PHASE_2              34
/**
 * The identifier for R_CR_generate_key_init().
 */
#define R_CR_F_R_CR_KGEN_INIT               35
/**
 * The identifier for R_CR_generate_key().
 */
#define R_CR_F_R_CR_GENERATE_KEY            36
/**
 * The identifier for R_CR_generate_parameter_init().
 */
#define R_CR_F_R_CR_PGEN_INIT               37
/**
 * The identifier for R_CR_generate_parameter().
 */
#define R_CR_F_R_CR_GENERATE_PARAMS         38
/**
 * The identifier for R_CR_random_seed().
 */
#define R_CR_F_R_CR_RANDOM_SEED             39
/**
 * The identifier for R_CR_random_bytes().
 */
#define R_CR_F_R_CR_RANDOM_BYTES            40
/**
 * The identifier for R_CR_get_error_string().
 */
#define R_CR_F_R_CR_GET_ERRINFO             41
/**
 * The identifier for R_CR_get_info().
 */
#define R_CR_F_R_CR_GET_INFO                42
/**
 * The identifier for R_CR_set_info().
 */
#define R_CR_F_R_CR_SET_INFO                43
/**
 * The identifier for R_CR_get_default_method().
 */
#define R_CR_F_R_CR_GET_DEFAULT_METHOD      44
/**
 * The identifier for <tt>R_CR_ID_to_sig_id()</tt>.
 */
#define R_CR_F_R_CR_IDS_TO_SIG_ID           45
/**
 * The identifier for <tt>R_CR_ID_from_sig_id()</tt>.
 */
#define R_CR_F_R_CR_IDS_FROM_SIG_ID         46
/**
 * The identifier for R_CR_mac_init().
 */
#define R_CR_F_R_CR_MAC_INIT                47
/**
 * The identifier for R_CR_mac().
 */
#define R_CR_F_R_CR_MAC                     48
/**
 * The identifier for R_CR_mac_update().
 */
#define R_CR_F_R_CR_MAC_UPDATE              49
/**
 * The identifier for R_CR_mac_final().
 */
#define R_CR_F_R_CR_MAC_FINAL               50
/**
 * The identifier for R_CR_verify_mac_init().
 */
#define R_CR_F_R_CR_VERIFY_MAC_INIT         51
/**
 * The identifier for R_CR_verify_mac().
 */
#define R_CR_F_R_CR_VERIFY_MAC              52
/**
 * The identifier for R_CR_verify_mac_update().
 */
#define R_CR_F_R_CR_VERIFY_MAC_UPDATE       53
/**
 * The identifier for R_CR_verify_mac_final().
 */
#define R_CR_F_R_CR_VERIFY_MAC_FINAL        54
/**
 * @}
 */

/* here are the definitions for the r_crm_ functions */
/**
 * @defgroup CRYP_MTH_API_FN_ID Method Function Identifiers
 * This section details the defines used for identifying the cryptographic
 * method function where an error has occurred.
 * @see R_CR_get_function(), R_CR_get_error() and @ref CRYP_ERR_FN_STR.
 * @ingroup R_ERROR_IDS
 * @{
 */
/**
 * The identifier for <tt>r_crm_ctx_new()</tt>.
 */
#define R_CR_F_R_CRM_CTX_NEW                101
/**
 * The identifier for <tt>r_crm_ctx_free()</tt>.
 */
#define R_CR_F_R_CRM_CTX_FREE               102
/**
 * The identifier for <tt>r_crm_new()</tt>.
 */
#define R_CR_F_R_CRM_NEW                    103
/**
 * The identifier for <tt>r_crm_dup()</tt>.
 */
#define R_CR_F_R_CRM_DUP                    104
/**
 * The identifier for <tt>r_crm_free()</tt>.
 */
#define R_CR_F_R_CRM_FREE                   105
/**
 * The identifier for <tt>r_crm_get_errinfo()</tt>.
 */
#define R_CR_F_R_CRM_GET_ERRINFO            106
/**
 * The identifier for <tt>r_crm_get_info()</tt>.
 */
#define R_CR_F_R_CRM_GET_INFO               107
/**
 * The identifier for <tt>r_crm_set_info()</tt>.
 */
#define R_CR_F_R_CRM_SET_INFO               108
/**
 * The identifier for <tt>r_crm_encrypt_init()</tt>.
 */
#define R_CR_F_R_CRM_ENCRYPT_INIT           109
/*
 * The identifier for <tt>r_crm_encrypt()</tt>.
 */
#define R_CR_F_R_CRM_ENCRYPT                110
/*
 * The identifier for <tt>r_crm_encrypt_update()</tt>.
 */
#define R_CR_F_R_CRM_ENCRYPT_UPDATE         111
/*
 * The identifier for <tt>r_crm_encrypt_final()</tt>.
 */
#define R_CR_F_R_CRM_ENCRYPT_FINAL          112
/**
 * The identifier for <tt>r_crm_decrypt_init()</tt>.
 */
#define R_CR_F_R_CRM_DECRYPT_INIT           113
/*
 * The identifier for <tt>r_crm_decrypt()</tt>.
 */
#define R_CR_F_R_CRM_DECRYPT                114
/*
 * The identifier for <tt>r_crm_decrypt_update()</tt>.
 */
#define R_CR_F_R_CRM_DECRYPT_UPDATE         115
/*
 * The identifier for <tt>r_crm_ecrypt_final()</tt>.
 */
#define R_CR_F_R_CRM_DECRYPT_FINAL          116
/**
 * The identifier for <tt>r_crm_sign_vfy_init()</tt>.
 */
#define R_CR_F_R_CRM_SIGN_VFY_INIT          117
/**
 * The identifier for <tt>r_crm_sign()</tt>.
 */
#define R_CR_F_R_CRM_SIGN                   118
/**
 * The identifier for <tt>r_crm_sign_update()</tt>.
 */
#define R_CR_F_R_CRM_SIGN_UPDATE            119
/**
 * The identifier for <tt>r_crm_sign_final()</tt>.
 */
#define R_CR_F_R_CRM_SIGN_FINAL             120
/*
 * The identifier for <tt>r_crm_verify_init()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_INIT            121
/**
 * The identifier for <tt>r_crm_verify()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY                 122
/**
 * The identifier for <tt>r_crm_verify_update()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_UPDATE          123
/**
 * The identifier for <tt>r_crm_verify_final()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_FINAL           124
/*
 * The identifier for <tt>r_crm_asym_encrypt_init()</tt>.
 */
#define R_CR_F_R_CRM_ASYM_ENCRYPT_INIT      125
/*
 * The identifier for <tt>r_crm_asym_encrypt()</tt>.
 */
#define R_CR_F_R_CRM_ASYM_ENCRYPT           126
/**
 * The identifier for <tt>r_crm_decrypt_init()</tt>.
 */
#define R_CR_F_R_CRM_ASYM_DECRYPT_INIT      127
/**
 * The identifier for <tt>r_crm_decrypt()</tt>.
 */
#define R_CR_F_R_CRM_ASYM_DECRYPT           128
/**
 * The identifier for <tt>r_crm_digest_init()</tt>.
 */
#define R_CR_F_R_CRM_DIGEST_INIT            129
/**
 * The identifier for <tt>r_crm_digest()</tt>.
 */
#define R_CR_F_R_CRM_DIGEST                 130
/**
 * The identifier for <tt>r_crm_digest_update()</tt>.
 */
#define R_CR_F_R_CRM_DIGEST_UPDATE          131
/**
 * The identifier for <tt>r_crm_digest_final()</tt>.
 */
#define R_CR_F_R_CRM_DIGEST_FINAL           132
/**
 * The identifier for <tt>r_crm_ke_init()</tt>.
 */
#define R_CR_F_R_CRM_KE_INIT                133
/**
 * The identifier for <tt>r_crm_ke_phase_1()</tt>.
 */
#define R_CR_F_R_CRM_KE_PHASE_1             134
/**
 * The identifier for <tt>r_crm_ke_phase_2()</tt>.
 */
#define R_CR_F_R_CRM_KE_PHASE_2             135
/**
 * The identifier for <tt>r_crm_kgen_init()</tt>.
 */
#define R_CR_F_R_CRM_KGEN_INIT              136
/**
 * The identifier for <tt>r_crm_generate_key()</tt>.
 */
#define R_CR_F_R_CRM_GENERATE_KEY           137
/**
 * The identifier for <tt>r_crm_pgen_init()</tt>.
 */
#define R_CR_F_R_CRM_PGEN_INIT              138
/**
 * The identifier for <tt>r_crm_generate_params()</tt>.
 */
#define R_CR_F_R_CRM_GENERATE_PARAMS        139
/**
 * The identifier for <tt>r_crm_random_seed()</tt>.
 */
#define R_CR_F_R_CRM_RANDOM_SEED            140
/**
 * The identifier for <tt>r_crm_gen_rand()</tt>.
 */
#define R_CR_F_R_CRM_GEN_RAND               141
/**
 * The identifier for <tt>r_crm_mac_init()</tt>.
 */
#define R_CR_F_R_CRM_MAC_INIT               142
/**
 * The identifier for <tt>r_crm_mac()</tt>.
 */
#define R_CR_F_R_CRM_MAC                    143
/**
 * The identifier for <tt>r_crm_mac_update()</tt>.
 */
#define R_CR_F_R_CRM_MAC_UPDATE             144
/**
 * The identifier for <tt>r_crm_mac_final()</tt>.
 */
#define R_CR_F_R_CRM_MAC_FINAL              145
/*
 * The identifier for <tt>r_crm_verify_mac_init()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_MAC_INIT        146
/**
 * The identifier for <tt>r_crm_verify_mac()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_MAC             147
/**
 * The identifier for <tt>r_crm_verify_mac_update()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_MAC_UPDATE      148
/**
 * The identifier for <tt>r_crm_verify_mac_final()</tt>.
 */
#define R_CR_F_R_CRM_VERIFY_MAC_FINAL       149
/*
 * The identifier for <tt>r_crm_cipher_init()</tt>.
 */
#define R_CR_F_R_CRM_CIPHER_INIT            150
/**
 * The identifier for <tt>r_crm_cipher()</tt>.
 */
#define R_CR_F_R_CRM_CIPHER                 151
/**
 * The identifier for <tt>r_crm_cipher_update()</tt>.
 */
#define R_CR_F_R_CRM_CIPHER_UPDATE          152
/**
 * The identifier for <tt>r_crm_cipher_final()</tt>.
 */
#define R_CR_F_R_CRM_CIPHER_FINAL           153
/**
 * @}
 */

/* Native methods    */
/**
 * @defgroup CRYP_INT_API_FN_ID Internal Function Identifiers
 * This section details the defines used for identifying the cryptographic
 * internal function where an error occurred.
 * @see R_CR_get_function(), R_CR_get_error() and @ref CRYP_ERR_FN_STR.
 * @ingroup R_ERROR_IDS
 * @{
 */
/**
 * The identifier for <tt>r_crn_evp_digest_init()</tt>.
 */
#define R_CRN_EVP_DIGEST_INIT               201
/**
 * The identifier for <tt>r_crn_evp_digest_new()</tt>.
 */
#define R_CRN_EVP_DIGEST_NEW                202
/**
 * The identifier for <tt>r_crn_evp_digest_free()</tt>.
 */
#define R_CRN_EVP_DIGEST_FREE               203
/**
 * The identifier for <tt>r_crn_evp_digest()</tt>.
 */
#define R_CRN_EVP_DIGEST                    204
/**
 * The identifier for <tt>r_crn_evp_digest_update()</tt>.
 */
#define R_CRN_EVP_DIGEST_UPDATE             205
/**
 * The identifier for <tt>r_crn_evp_digest_final()</tt>.
 */
#define R_CRN_EVP_DIGEST_FINAL              206

/**
 * The identifier for <tt>r_crn_hmac_init()</tt>.
 */
#define R_CRN_HMAC_INIT                     207
/**
 * The identifier for <tt>r_crn_hmac_new()</tt>.
 */
#define R_CRN_HMAC_NEW                      208
/**
 * The identifier for <tt>r_crn_hmac_free()</tt>.
 */
#define R_CRN_HMAC_FREE                     209
/**
 * The identifier for <tt>r_crn_hmac_update()</tt>.
 */
#define R_CRN_HMAC_UPDATE                   210
/**
 * The identifier for <tt>r_crn_hmac_final()</tt>.
 */
#define R_CRN_HMAC_FINAL                    211
/**
 * The identifier for <tt>r_crn_hmac()</tt>.
 */
#define R_CRN_HMAC                          212
/**
 * The identifier for <tt>r_crn_verify_hmac()</tt>.
 */
#define R_CRN_VERIFY_HMAC                   213
/**
 * The identifier for <tt>r_crn_verify_hmac_final()</tt>.
 */
#define R_CRN_VERIFY_HMAC_FINAL             214

/**
 * The identifier for <tt>r_crn_cipher_update()</tt>.
 */
#define R_CRN_CIPHER_UPDATE                 215
/**
 * The identifier for <tt>r_crn_cipher_init()</tt>.
 */
#define R_CRN_CIPHER_INIT                   216
/**
 * The identifier for <tt>r_crn_cipher_new()</tt>.
 */
#define R_CRN_CIPHER_NEW                    217
/**
 * The identifier for <tt>r_crn_cipher_free()</tt>.
 */
#define R_CRN_CIPHER_FREE                   218
/**
 * The identifier for <tt>r_crn_cipher()</tt>.
 */
#define R_CRN_CIPHER                        219

/**
 * The identifier for <tt>r_crn_pk_init()</tt>.
 */
#define R_CRN_PK_INIT                       220
/**
 * The identifier for <tt>r_crn_pk_free()</tt>.
 */
#define R_CRN_PK_FREE                       221
/**
 * The identifier for <tt>r_crn_pk_new()</tt>.
 */
#define R_CRN_PK_NEW                        222

/**
 * The identifier for <tt>r_crn_evp_get_info()</tt>.
 */
#define R_CRN_EVP_GET_INFO                  223
/**
 * The identifier for <tt>r_crn_asym_get_info()</tt>.
 */
#define R_CRN_ASYM_GET_INFO                 224

/**
 * The identifier for <tt>r_crn_evp_set_info()</tt>.
 */
#define R_CRN_EVP_SET_INFO                  225

/**
 * The identifier for <tt>r_crn_sign_vfy_init()</tt>.
 */
#define R_CRN_SIGN_VFY_INIT                 226
/**
 * The identifier for <tt>r_crn_sign()</tt>.
 */
#define R_CRN_SIGN                          227
/**
 * The identifier for <tt>r_crn_verify()</tt>.
 */
#define R_CRN_VERIFY                        228
/**
 * The identifier for <tt>r_crn_vfy_new()</tt>.
 */
#define R_CRN_SIGN_VFY_NEW                  229
/**
 * The identifier for <tt>r_crn_vfy_free()</tt>.
 */
#define R_CRN_SIGN_VFY_FREE                 230
/**
 * The identifier for <tt>r_crn_sign_update()</tt>.
 */
#define R_CRN_SIGN_UPDATE                   231
/**
 * The identifier for <tt>r_crn_sign_final()</tt>.
 */
#define R_CRN_SIGN_FINAL                    232
/**
 * The identifier for <tt>r_crn_verify_update()</tt>.
 */
#define R_CRN_VERIFY_UPDATE                 233
/**
 * The identifier for <tt>r_crn_verify_final()</tt>.
 */
#define R_CRN_VERIFY_FINAL                  234

/**
 * The identifier for <tt>r_crn_dh_ke_phase_1()</tt>.
 */
#define R_CRN_DH_KE_PHASE_1                 235
/**
 * The identifier for <tt>r_crn_dh_ke_phase_2()</tt>.
 */
#define R_CRN_DH_KE_PHASE_2                 236
/**
 * @}
 */

/* detail definitions                */
/**
 * @defgroup CRYP_ERR_DETAIL Error Detail Identifiers
 * This section details the defines used to identify error details
 * for errors generated in the cryptographic module.
 *
 * @see R_CR_get_detail(), R_CR_get_reason() and @ref CRYP_ERR_DETAIL_STR.
 * @ingroup R_ERROR_IDS
 * @{
 */
/**
 * The identifier used for errors where no details are available.
 */
#define R_CR_D_NO_DETAILS                   0

/**
 * @}
 */

/**
 * @defgroup CRYP_ERR_REASON Error Reason Identifiers
 * This section details the defines used to identify error reasons
 * for errors generated in the cryptographic module.
 *
 * @see R_CR_get_reason(), R_CR_get_error() and @ref CRYP_ERR_REASON_STR.
 * @ingroup R_ERROR_IDS
 *
 * @{
 */
/* reason definitions                */
/**
 * Indicates that the identifier is used for errors where no reason is 
 * supplied.
 */
#define R_CR_R_NO_REASON                    0
/**
 * Indicates that the cryptographic object passed to the operation was 
 * <tt>NULL</tt>.
 */
#define R_CR_R_CRYPTO_IS_NULL               1
/**
 * Indicates that the cryptographic object passed to the operation did 
 * not have a type matching the required type for the operation being 
 * performed.
 */
#define R_CR_R_CRYPTO_WRONG_TYPE            2
/**
 * Indicates that the operation being performed detected that a required key 
 * value supplied has the value <tt>NULL</tt>.
 */
#define R_CR_R_KEY_IS_NULL                  3
/**
 * Indicates that the operation requested has detected that the method called 
 * by the module is set to <tt>NULL</tt>. The method has not been loaded
 * or has been incorrectly instantiated and is unavailable.
 */
#define R_CR_R_IMPL_IS_NULL                 4
/**
 * Indicates that the operation requested has detected that the underlying 
 * implementation called by the method is set to <tt>NULL</tt>. The 
 * implementation has not been loaded or has been incorrectly instantiated 
 * and is unavailable.
 */
#define R_CR_R_IMPL_METH_IS_NULL            5
/**
 * @}
 */
#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_CRYP_ERR_H */


