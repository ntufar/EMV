/* $Id: nat_meth.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file nat_meth.h
 * This file contains the methods and functions used for the native
 * implementations of the cryptographic module. Functions in this
 * file should not be called directly.
 */

#ifndef HEADER_COMMON_NAT_METH_H
#define HEADER_COMMON_NAT_METH_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef const void *(R_CR_IMPL_RETRIEVER_FUNC)(void);

/**
 * This structure is used for implementing method objects.
 */
struct r_cr_imp_method_st
{
    /**
     * The cryptographic operation identifier.
     * @see @ref R_CR_TYPE.
     */
    int type;                           /* algorithm type */
    /**
     * The cryptographic identifier.
     * @see @ref R_CR_IDS.
     */
    int id;                             /* specific algorithm */
    /**
     * The cryptographic operation subtype identifier.
     * @see @ref R_CR_SUB.
     */
    int sub;                            /* algortihm subtype */
    /**
     * The pointer to the specific method used by <i>id</i>,<i>type</i> and
     * <i>sub</i>.
     */
    R_CR_IMPL_RETRIEVER_FUNC *imp_meth; /* retrieve pointer to specific */
                                        /* implementation */
    /**
     * The cryptographic implemenation-dependent data.
     */
    const void *imp_meth_data;          /* generic data   */
};


/* asymetric methods */
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_public;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_private;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_public;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_private;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_oaep;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_oaep_pub;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_oaep_priv;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_pkcs1_ssl;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_x931_pub;
R_CR_IMPL_RETRIEVER_FUNC r_crn_asym_rsa_x931_priv;

/* symmetric cipher methods */
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_null;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede3;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede3_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede3_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ede3_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_40_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_des_40_cfb;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_40_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc2_64_cbc;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_40;

/**
 * X86 CPU methods
 */
#ifdef CPU_X86
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_586;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_40_586;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_686;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_40_686;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_786;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc4_40_786;
#endif

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc5f_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc5_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc5_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc5_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc5_ofb;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_ofb;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_s_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_s_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_s_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_rc6_s_ofb;

R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_m_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_m_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_m_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_m_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_s_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_s_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_s_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes128_s_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_m_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_m_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_m_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_m_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_s_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_s_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_s_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes192_s_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_m_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_m_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_m_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_m_ofb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_s_cbc;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_s_ecb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_s_cfb;
R_CR_IMPL_RETRIEVER_FUNC r_crn_ciph_aes256_s_ofb;

/* hash mac digests */
R_CR_IMPL_RETRIEVER_FUNC r_crn_hmac_md5;
R_CR_IMPL_RETRIEVER_FUNC r_crn_hmac_sha1;

/* digests */
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_sha1;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_sha2_256;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_sha2_384;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_sha2_512;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_null;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_md2;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dgst_md5;

/* signature methods table */
R_CR_IMPL_RETRIEVER_FUNC r_crn_sign_vfy;

/* random methods */
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_mth;
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_fips1862_mth;
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_fips1862_mod_mth;
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_fips1862_global_mth;
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_sys_mth;
R_CR_IMPL_RETRIEVER_FUNC r_crn_random_otp_mth;

/* key exchange methods */
R_CR_IMPL_RETRIEVER_FUNC r_crn_ke_dh;

/* key generation methods */
R_CR_IMPL_RETRIEVER_FUNC r_crn_rsa_key_gen;
R_CR_IMPL_RETRIEVER_FUNC r_crn_rsa_key_gen_x931;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dh_param_gen;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dsa_param_gen;
R_CR_IMPL_RETRIEVER_FUNC r_crn_dsa_key_gen;

/* dsa sign and verify */
R_CR_IMPL_RETRIEVER_FUNC r_crn_dsa_sign_vfy;
R_CR_IMPL_RETRIEVER_FUNC r_crn_raw_dsa_sign_vfy;

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_NAT_METH_H */
