/* $Id: cryp_meth.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryp_meth.h
 * This file contains the cryptographic method table structures and
 * method defines.
 */

#ifndef HEADER_COMMON_CRYP_METH_H
#define HEADER_COMMON_CRYP_METH_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "cryp_mod.h"

/**
 * This structure contains the set of function pointers which are used
 * as a method table to map calls to the cryptographic Application
 * Programming Interface (API) functions through to their implementations.
 *
 * The functions provide support for <tt>init</tt>, <tt>update</tt>,
 * <tt>final</tt> and single update/final operations which are required by
 * PKCS #11. With this, individual functions can be mapped through to
 * hardware devices that provide a PKCS #11 interface.
 *
 */
struct r_cr_method_st
{
    /** @see R_CR_CTX_new(). */
    int (*ctx_new)(R_LIB_CTX *lib_ctx, R_RES_FLAG flag, R_CR_CTX **ctx);

    /** @see R_CR_CTX_free(). */
    int (*ctx_free)(R_CR_CTX *ctx);

    /** @see R_CR_new(). */
    int (*crypto_new)(R_CR_CTX *crypto_ctx, int alg_type, int alg_id,
                int alg_sub, R_CR **crypto);

    /** @see R_CR_dup(). */
    int (*crypto_dup)(R_CR *crypto, R_CR **new_crypto);

    /** @see R_CR_free(). */
    int (*crypto_free)(R_CR *crypto);

    /**
     * @see R_CR_get_error(), R_CR_get_reason(), R_CR_get_detail(),
     * R_CR_get_function(), R_CR_get_line(), R_CR_get_file(),
     * R_CR_get_error_string(), R_CR_get_reason_string(),
     * R_CR_get_detail_string() and R_CR_get_function_string().
     */
    int (*crypto_get_errinfo)(R_CR *crypto, int what, void **data);

    /** @see R_CR_set_info(). */
    int (*crypto_getinfo)(R_CR *crypto, int id, void **param);

    /** @see R_CR_get_info(). */
    int (*crypto_setinfo)(R_CR *crypto, int id, void *param);

    /** @see R_CR_encrypt_init(). */
    int (*encrypt_init)(R_CR *crypto, R_SKEY *key, R_ITEM *iv);

    /** @see R_CR_encrypt(). */
    int (*encrypt)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_encrypt_update(). */
    int (*encrypt_update)(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *out, unsigned int *olen);

    /** @see R_CR_encrypt_final(). */
    int (*encrypt_final)(R_CR *crypto, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_decrypt_init(). */
    int (*decrypt_init)(R_CR *crypto, R_SKEY *key, R_ITEM *iv);

    /** @see R_CR_decrypt(). */
    int (*decrypt)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_decrypt_update(). */
    int (*decrypt_update)(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *out, unsigned int *olen);

    /** @see R_CR_decrypt_final(). */
    int (*decrypt_final)(R_CR *crypto, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_sign_init(). */
    int (*sign_init)(R_CR *crypto, R_PKEY *key);

    /** @see R_CR_sign(). */
    int (*sign)(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *out, unsigned int *olen);

    /** @see R_CR_sign_update(). */
    int (*sign_update)(R_CR *crypto, unsigned char *data,
        unsigned int data_len);

    /** @see R_CR_sign_final(). */
    int (*sign_final)(R_CR *crypto,unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_verify_init(). */
    int (*verify_init)(R_CR *crypto, R_PKEY *key);

    /** @see R_CR_verify(). */
    int (*verify)(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *signature,
        unsigned int slen, int *result);

    /** @see R_CR_verify_update(). */
    int (*verify_update)(R_CR *crypto, unsigned char *data,
        unsigned int data_len);

    /** @see R_CR_verify_final(). */
    int (*verify_final)(R_CR *crypto, unsigned char *signature,
        unsigned int sig_len, int *result);

    /** @see R_CR_asym_encrypt_init(). */
    int (*asym_encrypt_init)(R_CR *crypto, R_PKEY *key);

    /** @see R_CR_asym_encrypt(). */
    int (*asym_encrypt)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_asym_decrypt_init(). */
    int (*asym_decrypt_init)(R_CR *crypto, R_PKEY *key);

    /** @see R_CR_asym_decrypt(). */
    int (*asym_decrypt)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_digest_init(). */
    int (*digest_init)(R_CR *crypto);

    /** @see R_CR_digest(). */
    int (*digest)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *out_len);

    /** @see R_CR_digest_update(). */
    int (*digest_update)(R_CR *crypto, unsigned char *data,
        unsigned int data_len);

    /** @see R_CR_digest_final(). */
    int (*digest_final)(R_CR *crypto, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_mac_init(). */
    int (*mac_init)(R_CR *crypto, R_SKEY *key);

    /** @see R_CR_mac(). */
    int (*mac)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_mac_update(). */
    int (*mac_update)(R_CR *crypto, unsigned char *data,
        unsigned int data_len);

    /** @see R_CR_mac_final(). */
    int (*mac_final)(R_CR *crypto, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_verify_mac_init(). */
        int (*verify_mac_init)(R_CR *crypto, R_SKEY *key);

    /** @see R_CR_verify_mac(). */
    int (*verify_mac)(R_CR *crypto, unsigned char *data,
        unsigned int data_len, unsigned char *mac,
        unsigned int mac_len, int *result);

    /** @see R_CR_verify_mac_update(). */
    int (*verify_mac_update)(R_CR *crypto, unsigned char *data,
        unsigned int data_len);

    /** @see R_CR_verify_mac_final(). */
    int (*verify_mac_final)(R_CR *crypto, unsigned char *mac,
        unsigned int mac_len, int *result);

    /** @see R_CR_key_exchange_init(). */
    int (*key_exchange_init)(R_CR *crypto, R_PKEY *key);

    /** @see R_CR_key_exchange_phase_1(). */
    int (*key_exchange_phase_1)(R_CR *crypto, unsigned char *out,
        unsigned int *olen);

    /** @see R_CR_key_exchange_phase_2(). */
    int (*key_exchange_phase_2)(R_CR *crypto, unsigned char *data,
        unsigned int dlen, unsigned char *out, unsigned int * olen);

    /** @see R_CR_generate_key_init(). */
    int (*generate_key_init)(R_CR *crypto);

    /** @see R_CR_generate_key(). */
    int (*generate_key)(R_CR *crypto, R_PKEY **key);

    /** @see R_CR_generate_parameter_init(). */
    int (*generate_params_init)(R_CR *crypto);

    /** @see R_CR_generate_parameter(). */
    int (*generate_params)(R_CR *crypto, R_PKEY **params);

    /** @see R_CR_random_seed(). */
    int (*random_seed)(R_CR *crypto, unsigned char *bytes,
        unsigned int len);

    /** @see R_CR_random_bytes(). */
    int (*gen_rand)(R_CR *crypto, unsigned int len,
        unsigned char *out, unsigned int *olen);
};


/**
 * These functions are the intermediate function level that should
 * correspond to the method table on an almost 1:1 basis. As a result, 
 * <tt>r_crm r - RSA - cr -CRYPTO - m</tt> method prefix.
 */
int r_crm_not_implemented(void);

int r_crm_ctx_new(R_LIB_CTX *lib_ctx, R_RES_FLAG flag, R_CR_CTX **crypto_ctx);
int r_crm_ctx_free(R_CR_CTX *crypto_ctx);

int r_crm_new(R_CR_CTX *crypto_ctx, R_CR_ALG_TYPE alg_type, R_CR_ALG_ID alg_id,
    R_CR_ALG_SUB alg_sub, R_CR **crypto);
int r_crm_dup(R_CR *crypto, R_CR **new_crypto);
int r_crm_free(R_CR *crypto);

int r_crm_digest_init(R_CR *crypto);
int r_crm_digest(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *out,
    unsigned int *out_len);
int r_crm_digest_update(R_CR *crypto, unsigned char *data,
    unsigned int data_len);
int r_crm_digest_final(R_CR *crypto, unsigned char *out,
    unsigned int *olen);

int r_crm_mac_init(R_CR *crypto, R_SKEY *key);
int r_crm_mac(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *out,
    unsigned int *olen);
int r_crm_mac_update(R_CR *crypto, unsigned char *data,
    unsigned int data_len);
int r_crm_mac_final(R_CR *crypto, unsigned char *out,
    unsigned int *olen);

int r_crm_verify_mac(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *mac, unsigned int mac_len,
    int *result);
int r_crm_verify_mac_update(R_CR *crypto, unsigned char *data,
    unsigned int data_len);
int r_crm_verify_mac_final(R_CR *crypto, unsigned char *mac,
    unsigned int mac_len, int *result);

int r_crm_encrypt_init(R_CR *crypto, R_SKEY *key, R_ITEM *iv);
int r_crm_decrypt_init(R_CR *crypto, R_SKEY *key, R_ITEM *iv);
int r_crm_cipher(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *out, unsigned int *out_len);
int r_crm_cipher_update(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int *olen);
int r_crm_cipher_final(R_CR *crypto, unsigned char *out,unsigned int *olen);

int r_crm_asym_init(R_CR *crypto, R_PKEY *key);
int r_crm_asym_enc(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *out,
    unsigned int *out_len);
int r_crm_asym_dec(R_CR *crypto, unsigned char *data,
    unsigned int data_len, unsigned char *out, unsigned int *out_len);

int r_crm_ke_init(R_CR *crypto, R_PKEY *key);
int r_crm_ke_phase_1(R_CR *crypto, unsigned char *out,
    unsigned int *olen);
int r_crm_ke_phase_2(R_CR *crypto, unsigned char *data,
    unsigned int dlen, unsigned char *out, unsigned int * olen);

int r_crm_kgen_init(R_CR *crypto);
int r_crm_generate_key(R_CR *crypto, R_PKEY **key);

int r_crm_pgen_init(R_CR *crypto);
int r_crm_generate_params(R_CR *crypto, R_PKEY **params);

int r_crm_sign_vfy_init(R_CR *crypto, R_PKEY *key);
int r_crm_sign(R_CR *crypto, unsigned char *data, unsigned int dlen,
    unsigned char *out, unsigned int *olen);
int r_crm_sign_update(R_CR *crypto, unsigned char *data, unsigned int data_len);
int r_crm_sign_final(R_CR *crypto,unsigned char *out, unsigned int *out_len);
int r_crm_verify(R_CR *crypto, unsigned char *data, unsigned int dlen,
    unsigned char *signature, unsigned int slen, int *result);
int r_crm_verify_update(R_CR *crypto, unsigned char *data,
    unsigned int data_len);
int r_crm_verify_final(R_CR *crypto, unsigned char *signature,
    unsigned int sig_len, int *result);

int r_crm_random_seed(R_CR *crypto, unsigned char *seed, unsigned int len);
int r_crm_gen_rand(R_CR *crypto, unsigned int len,
    unsigned char *out, unsigned int *olen);

int r_crm_get_errinfo(R_CR *crypto, int what, void **data);

int r_crm_get_info(R_CR *crypto, int id, void **param);
int r_crm_set_info(R_CR *crypto, int id, void *param);

int r_crm_function_lookup(R_CR *crypto, R_CR_IMP_METHOD *table,
    R_CR_IMP_METHOD **imp_meth);


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_CRYP_METH_H */
