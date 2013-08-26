/* $Id: cryp_macros.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file cryp_macros.h
 * This file contains the macro functions used to reduce code size.
 * Use of these macros removes the call to the public Application Programming
 * Interface (API) objects that perform variable validation before executing
 * the method table entries.
 */

#ifndef HEADER_COMMON_CRYP_MACROS_H
#define HEADER_COMMON_CRYP_MACROS_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef NO_R_CR_FUNC
#define R_CR_CTX_free(ctx) \
    ctx->method->ctx_free(ctx)

#define R_CR_new(ctx,alg_type,alg_id,alg_sub,crypto) \
    ctx->method->crypto_new(ctx,alg_type,alg_id,alg_sub,crypto)
#define R_CR_dup(crypto,new_crypto) \
    crypto->method->crypto_dup(crypto,new_crypto)
#define R_CR_free(crypto) \
    crypto->method->crypto_free(crypto)

#define R_CR_encrypt_init(crypto,key,iv) \
    crypto->method->encrypt_init(crypto,key,iv)
#define R_CR_encrypt(crypto,data,data_len,out,out_len) \
    crypto->method->encrypt(crypto,data,data_len,out,olen)
#define R_CR_encrypt_update(crypto,data,data_len,out,out_len) \
    crypto->method->encrypt_update(crypto,data,data_len,out,olen)
#define R_CR_encrypt_final(crypto,out,out_len) \
    crypto->method->encrypt_final(crypto,out,olen)

#define R_CR_decrypt_init(crypto,key,iv) \
    crypto->method->decrypt_init(crypto,key,iv)
#define R_CR_decrypt(crypto,data,data_len,out,out_len) \
    crypto->method->decrypt(crypto,data,data_len,out,olen)
#define R_CR_decrypt_update(crypto,data,data_len,out,out_len) \
    crypto->method->decrypt_update(crypto,data,data_len,out,olen)
#define R_CR_decrypt_final(crypto,out,out_len) \
    crypto->method->decrypt_final(crypto,out,olen)

#define R_CR_sign_init(crypto,key) \
    (crypto->method->sign_init(crypto,key)
#define R_CR_sign(crypto,data,data_len,out,out_len) \
    crypto->method->sign(crypto,data,data_len,out,olen)
#define R_CR_sign_update(crypto,data,data_len) \
    crypto->method->sign_update(crypto,data,data_len)
#define R_CR_sign_final(crypto,out,out_len) \
    crypto->method->sign_final(crypto,out,out_len)

#define R_CR_verify_init(crypto,key) \
    crypto->method->verify_init(crypto,key)
#define R_CR_verify(crypto,data,data_len,signature,sig_len,result) \
    crypto->method->verify(crypto,data,data_len,signature,sig_len,result)
#define R_CR_verify_update(crypto,data,data_len) \
    crypto->method->verify_update(crypto,data,data_len)
#define R_CR_verify_final(crypto,signature,sig_len,result) \
    crypto->method->verify_final(crypto,signature,sig_len,result)

#define R_CR_asym_encrypt_init(crypto,key) \
    crypto->method->asym_encrypt_init(crypto,key)
#define R_CR_asym_encrypt(crypto,data,data_len,out,out_len) \
    crypto->method->asym_encrypt(crypto,data,data_len,out,out_len)
#define R_CR_asym_decrypt_init(crypto,key) \
    crypto->method->asym_decrypt_init(crypto,key)
#define R_CR_asym_decrypt(crypto,data,data_len,out,out_len) \
    crypto->method->asym_decrypt(crypto,data,data_len,out,out_len)

#define R_CR_digest_init(crypto) \
    crypto->method->digest_init(crypto)
#define R_CR_digest(crypto,data,data_len,out,out_len) \
    crypto->method->digest(crypto,data,data_len,out,out_len)
#define R_CR_digest_update(crypto,data,data_len) \
    crypto->method->digest_update(crypto,data,data_len)
#define R_CR_digest_final(crypto,out,out_len) \
    crypto->method->digest_final(crypto,out,out_len)

#define R_CR_mac_init(crypto,key) \
    crypto->method->mac_init(crypto, key)
#define R_CR_mac(crypto,data,data_len,out,out_len) \
    crypto->method->mac(crypto,data,data_len,out,out_len)
#define R_CR_mac_update(crypto,data,data_len) \
    crypto->method->mac_update(crypto,data,data_len)
#define R_CR_mac_final(crypto,out,out_len) \
    crypto->method->mac_final(crypto,out,out_len)

#define R_CR_verify_mac_init(crypto,key) \
    crypto->method->verify_mac_init(crypto, key)
#define R_CR_verify_mac(crypto,data,data_len,mac,mac_len,result) \
    crypto->method->verify_mac(crypto,data,data_len,mac,mac_len,result)
#define R_CR_verify_mac_update(crypto,data,data_len) \
    crypto->method->verify_mac_update(crypto,data,data_len)
#define R_CR_verify_mac_final(crypto,mac,mac_len,result) \
    crypto->method->verify_mac_final(crypto,mac,mac_len,result)

#define R_CR_key_exchange_init(crypto,params) \
    crypto->method->key_exchange_init(crypto,key)
#define R_CR_key_exchange_phase_1(crypto,out,out_len) \
    crypto->method->key_exchange_phase_1(crypto,out,out_len)
#define R_CR_key_exchange_phase_2(crypto,data,data_len,out, out_len) \
    crypto->method->key_exchange_phase_2(crypto,data,data_len,out,out_len)

#define R_CR_generate_key_init(crypto) \
    crypto->method->generate_key_init(crypto)
#define R_CR_generate_key(crypto,key) \
    crypto->method->generate_key(crypto, key)

#define R_CR_generate_parameter_init(crypto) \
    crypto->method->generate_params_init(crypto)
#define R_CR_generate_parameter(crypto,key) \
    crypto->method->generate_params(crypto, key)

#define R_CR_random_seed(crypto,bytes,len) \
    crypto->method->random_seed(crypto,bytes,len)
#define R_CR_random_bytes(crypto,dlen,out,out_len) \
    crypto->method->gen_rand(crypto,dlen,out,out_len)

#define R_CR_get_error(crypto,data)                                 \
    crypto->method->crypto_get_errinfo(crypto,R_CR_ERRINFO_ERROR,   \
        (void *)data)
#define R_CR_get_reason(crypto,data)                                \
    crypto->method->crypto_get_errinfo(crypto,R_CR_ERRINFO_REASON,  \
        (void *)data)
#define R_CR_get_detail(crypto,data)                                \
    crypto->method->crypto_get_errinfo(crypto,R_CR_ERRINFO_DETAIL,  \
        (void *)data)
#define R_CR_get_function(crypto,data)                              \
    crypto->method->crypto_get_errinfo(crypto,R_CR_ERRINFO_FUNCTION,\
        (void *)data)
#define R_CR_get_line(crypto,data)                                  \
    crypto->method->crypto_get_errinfo(crypto,R_CR_ERRINFO_LINE,    \
        (void *)data)

#define R_CR_get_file(crypto,data)                  \
    crypto->method->crypto_get_errinfo(crypto,      \
        R_CR_ERRINFO_FILE,(void **)data)
#define R_CR_get_error_string(crypto,data)          \
    crypto->method->crypto_get_errinfo(crypto,      \
        R_CR_ERRINFO_ERROR_STRING,(void **)data)
#define R_CR_get_reason_string(crypto,data)         \
    crypto->method->crypto_get_errinfo(crypto,      \
        R_CR_ERRINFO_REASON_STRING,(void **)data)
#define R_CR_get_detail_string(crypto,data)         \
    crypto->method->crypto_get_errinfo(crypto,      \
        R_CR_ERRINFO_DETAIL_STRING,(void **)data)
#define R_CR_get_function_string(crypto,data)       \
    crypto->method->crypto_get_errinfo(crypto,      \
        R_CR_ERRINFO_FUNCTION_STRING,(void **)data)

#endif /* NO_R_CR_FUNC */
/**
 * Macros created by the use of #NO_R_CR_METH_TABLE_CRM
 * call directly to the cryptographic method functions without
 * the use of the library or resource initialization.
 */
#ifdef NO_R_CR_METH_TABLE_CRM
#define NO_R_CR_METH_TABLE

#include "cryp_meth.h"

#define R_CR_CTX_new(lib_ctx,flag,crypto_ctx) \
    r_crm_ctx_new(lib_ctx,flag,crypto_ctx)
#define R_CR_CTX_free(ctx) \
    r_crm_ctx_free(ctx)

#define R_CR_new(ctx,alg_type,alg_id,alg_sub,crypto) \
    r_crm_new(ctx,alg_type,alg_id,alg_sub,crypto)
#define R_CR_dup(crypto,new_crypto) \
    r_crm_dup(crypto,new_crypto)
#define R_CR_free(crypto) \
    r_crm_free(crypto)

#define R_CR_encrypt_init(crypto,key,iv) \
    r_crm_encrypt_init(crypto,key,iv)
#define R_CR_encrypt(crypto,data,data_len,out,out_len) \
    r_crm_cipher(crypto,data,data_len,out,out_len)
#define R_CR_encrypt_update(crypto,data,data_len,out,out_len) \
    r_crm_cipher_update(crypto,data,data_len,out,out_len)
#define R_CR_encrypt_final(crypto,out,out_len) \
    r_crm_cipher_final(crypto,out,out_len)

#define R_CR_decrypt_init(crypto,key,iv) \
    r_crm_decrypt_init(crypto,key,iv)
#define R_CR_decrypt(crypto,data,data_len,out,out_len) \
    r_crm_cipher(crypto,data,data_len,out,out_len)
#define R_CR_decrypt_update(crypto,data,data_len,out,out_len) \
    r_crm_cipher_update(crypto,data,data_len,out,out_len)
#define R_CR_decrypt_final(crypto,out,out_len) \
    r_crm_cipher_final(crypto,out,out_len)

#define R_CR_sign_init(crypto,key) \
    r_crm_sign_vfy_init(crypto,key)
#define R_CR_sign(crypto,data,data_len,out,out_len) \
    r_crm_sign(crypto,data,data_len,out,out_len)
#define R_CR_sign_update(crypto,data,data_len) \
    r_crm_sign_update(crypto,data,data_len)
#define R_CR_sign_final(crypto,out,out_len) \
    r_crm_sign_final(crypto,out,out_len)

#define R_CR_verify_init(crypto,key) \
    r_crm_sign_vfy_init(crypto,key)
#define R_CR_verify(crypto,data,data_len,signature,sig_len,result) \
    r_crm_verify(crypto,data,data_len,signature,sig_len,result)
#define R_CR_verify_update(crypto,data,data_len) \
    r_crm_verify_update(crypto,data,data_len)
#define R_CR_verify_final(crypto,signature,sig_len,result) \
    r_crm_verify_final(crypto,signature,sig_len,result)

#define R_CR_asym_encrypt_init(crypto,key) \
    r_crm_asym_init(crypto,key)
#define R_CR_asym_encrypt(crypto,data,data_len,out,out_len) \
    r_crm_asym_enc(crypto,data,data_len,out,out_len)
#define R_CR_asym_decrypt_init(crypto,key) \
    r_crm_asym_init(crypto,key)
#define R_CR_asym_decrypt(crypto,data,data_len,out,out_len) \
    r_crm_asym_dec(crypto,data,data_len,out,out_len)

#define R_CR_digest_init(crypto) \
    r_crm_digest_init(crypto)
#define R_CR_digest(crypto,data,data_len,out,out_len) \
    r_crm_digest(crypto,data,data_len,out,out_len)
#define R_CR_digest_update(crypto,data,data_len) \
    r_crm_digest_update(crypto,data,data_len)
#define R_CR_digest_final(crypto,out,out_len) \
    r_crm_digest_final(crypto,out,out_len)

#define R_CR_mac_init(crypto,key) \
    r_crm_mac_init(crypto, key)
#define R_CR_mac(crypto,data,data_len,out,out_len) \
    r_crm_mac(crypto,data,data_len,out,out_len)
#define R_CR_mac_update(crypto,data,data_len) \
    r_crm_mac_update(crypto,data,data_len)
#define R_CR_mac_final(crypto,out,out_len) \
    r_crm_mac_final(crypto,out,out_len)

#define R_CR_verify_mac_init(crypto,key) \
    r_crm_mac_init(crypto, key)
#define R_CR_verify_mac(crypto,data,data_len,mac,mac_len,result) \
    r_crm_verify_mac(crypto,data,data_len,mac,mac_len,result)
#define R_CR_verify_mac_update(crypto,data,data_len) \
    r_crm_verify_mac_update(crypto,data,data_len)
#define R_CR_verify_mac_final(crypto,mac,mac_len,result) \
    r_crm_verify_mac_final(crypto,mac,mac_len,result)

#define R_CR_key_exchange_init(crypto,key) \
    r_crm_ke_init(crypto,key)
#define R_CR_key_exchange_phase_1(crypto,out,out_len) \
    r_crm_ke_phase_1(crypto,out,out_len)
#define R_CR_key_exchange_phase_2(crypto,data,data_len,out, out_len) \
    r_crm_ke_phase_2(crypto,data,data_len,out,out_len)

#define R_CR_generate_key_init(crypto) \
    r_crm_kgen_init(crypto)
#define R_CR_generate_key(crypto,key) \
    r_crm_generate_key(crypto, key)

#define R_CR_generate_parameter_init(crypto) \
    r_crm_pgen_init(crypto)
#define R_CR_generate_parameter(crypto,key) \
    r_crm_generate_params(crypto, key)

#define R_CR_random_seed(crypto,bytes,len) \
    r_crm_random_seed(crypto,bytes,len)
#define R_CR_random_bytes(crypto,dlen,out,out_len) \
    r_crm_gen_rand(crypto,dlen,out,out_len)

#define R_CR_get_error(crypto,data)            \
    r_crm_get_errinfo(crypto,R_CR_ERRINFO_ERROR,    \
        (void *)data)
#define R_CR_get_reason(crypto,data)            \
    r_crm_get_errinfo(crypto,R_CR_ERRINFO_REASON,    \
        (void *)data)
#define R_CR_get_detail(crypto,data)            \
    r_crm_get_errinfo(crypto,R_CR_ERRINFO_DETAIL,    \
        (void *)data)
#define R_CR_get_function(crypto,data)            \
    r_crm_get_errinfo(crypto,R_CR_ERRINFO_FUNCTION,    \
        (void *)data)
#define R_CR_get_line(crypto,data)            \
    r_crm_get_errinfo(crypto,R_CR_ERRINFO_LINE,    \
        (void *)data)

#define R_CR_get_file(crypto,data)        \
    r_crm_get_errinfo(crypto,        \
        R_CR_ERRINFO_FILE,(void **)data)
#define R_CR_get_error_string(crypto,data)    \
    r_crm_get_errinfo(crypto,        \
        R_CR_ERRINFO_ERROR_STRING,(void **)data)
#define R_CR_get_reason_string(crypto,data)    \
    r_crm_get_errinfo(crypto,        \
        R_CR_ERRINFO_REASON_STRING,(void **)data)
#define R_CR_get_detail_string(crypto,data)    \
    r_crm_get_errinfo(crypto,        \
        R_CR_ERRINFO_DETAIL_STRING,(void **)data)
#define R_CR_get_function_string(crypto,data)    \
    r_crm_get_errinfo(crypto,        \
        R_CR_ERRINFO_FUNCTION_STRING,(void **)data)

#endif /* NO_R_CR_METH_TABLE_CRM */


#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_CRYP_MACROS_H */

