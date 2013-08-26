/* $Id: r_pkey_m.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/**
 * @file
 * This file contains the macros used to replace functions that call through
 * to an underlying implementation.
 */

#ifndef HEADER_COMMON_CERT_R_PKEY_M_H
#define HEADER_COMMON_CERT_R_PKEY_M_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef NO_R_PKEY_METH_TABLE

/**
 * This structure can be used to to extract the fields of the public key
 * context that are common to all implementations and 'wrap' the
 * implementation specific variations.
 */
typedef struct r_pkey_ctx_wrap_st
{
    R_PKEY_METHOD   *method;            /**< Public key methods */
    R_LIB_CTX       *lib_ctx;           /**< Library context */
    void            *crypto_ctx;        /**< Crypto context */

} R_PKEY_CTX_WRAP;

/**
 * This structure can be used to to extract the fields of the public key
 * object that are common to all implementations and 'wrap' the
 * implementation specific variations.
 */
typedef struct r_pkey_wrap_st
{
    R_PKEY_CTX_WRAP *ctx;       /**< Public key context for the object */

} R_PKEY_WRAP;

#include "r_pkey_l.h"

#define R_PKEY_CTX_new(lib_ctx,flag,type,ctx)                         \
    r_pkey_pk_ctx_new(lib_ctx,flag,type,ctx)
#define R_PKEY_CTX_free(ctx)                                          \
    r_pkey_pk_ctx_free(ctx)
#define R_PKEY_CTX_get_info(ctx,id,param)                             \
    r_pkey_pk_ctx_get_info(ctx,id,param)
#define R_PKEY_CTX_set_info(ctx,id,param)                             \
   r_pkey_pk_ctx_set_info(ctx,id,param)

#define R_PKEY_CTX_get_LIB_CTX(ctx)                                   \
    ((R_PKEY_CTX_WRAP *)ctx)->lib_ctx

#define R_PKEY_new(ctx,pkeytype,pkey)                                 \
    r_pkey_pk_pkey_new(ctx,pkeytype,pkey)
#define R_PKEY_free(pkey)                                             \
    r_pkey_pk_pkey_free(pkey)
#define R_PKEY_copy(pkey, new_pkey, flag)                             \
    r_pkey_pk_pkey_copy(pkey, new_pkey, flag)
#define R_PKEY_set_info(pkey,id,param)                                \
    r_pkey_pk_pkey_set_info(pkey,id,param)
#define R_PKEY_get_info(pkey,id,param)                                \
    r_pkey_pk_pkey_get_info(pkey,id,param)

#define R_PKEY_get_PKEY_CTX(pkey)                                     \
    ((R_PKEY_WRAP *)pkey)->ctx

#define R_PKEY_from_binary(ctx,flag,type,max,buf,con,pkey)            \
    r_pkey_pk_pkey_from_binary(ctx,flag,type,max,buf,con,pkey)
#define R_PKEY_to_binary(pkey,maxlength,outbuf,outlength)             \
    r_pkey_pk_pkey_to_binary(pkey,maxlength,outbuf,outlength)
#define R_PKEY_from_public_key_binary(ctx,fl,type,max,buf,clen,key)   \
    r_pkey_pk_pkey_from_pubkey_binary(ctx,fl,type,max,buf,clen,key)
#define R_PKEY_to_public_key_binary(key,max,buf,olen)                 \
    r_pkey_pk_pkey_to_pubkey_binary(key,max,buf,olen)

#define R_PKEY_reference_inc(pkey)                                    \
    r_pkey_pk_pkey_reference_inc(pkey)
#define R_PKEY_cmp(one,two)                                           \
    r_pkey_pk_pkey_cmp(one,two)
#define R_PKEY_public_cmp(one,two)                                    \
    r_pkey_pk_pkey_public_cmp(one,two)
#define R_PKEY_iterate_fields(pkey,func,arg)                          \
    r_pkey_pk_pkey_iterate_fields(pkey,func,arg)

#define R_PKEY_get_type(pkey)                                         \
    r_pkey_pk_pkey_get_type(pkey)
#define R_PKEY_get_num_bits(pkey)                                     \
    r_pkey_pk_get_num_bits(pkey)
#define R_PKEY_get_num_primes(pkey)                                   \
    r_pkey_pk_get_num_primes(pkey)
#define R_PKEY_signhash(pkey, data, dlen, out, olen)                  \
    r_pkey_pk_signhash(pkey,data,dlen,out,olen)
#define R_PKEY_verifyhash(pkey, data, dlen, hash, hlen)               \
    r_pkey_pk_verifyhash(pkey,data,dlen,hash,hlen)

#ifndef NO_BIO
#define R_PKEY_print(bio,pkey,format,format_arg)                      \
    r_pkey_print(bio,pkey,format,format_arg)
#endif /* NO_BIO */

#endif /* NO_R_PKEY_METH_TABLE */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_CERT_R_PKEY_M_H */

