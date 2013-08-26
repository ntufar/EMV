/* $Id: dsa.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

#ifndef HEADER_COMMON_DSA_H
#define HEADER_COMMON_DSA_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifndef HEADER_COMMON_BN_H_TYPEDEF_DEF
#define HEADER_COMMON_BN_H_TYPEDEF_DEF
typedef struct bignum_st BIGNUM;
typedef struct bignum_ctx BN_CTX;
typedef struct bn_mont_ctx_st BN_MONT_CTX;
typedef struct bn_recp_ctx_st BN_RECP_CTX;
typedef struct bn_prime_ctx_st BN_PRIME_CTX;
typedef struct bn_blind_ctx_st BN_BLIND_CTX;
typedef struct bn_blind_meth_st BN_BLIND_METH;
#endif

#define DSA_FLAG_CACHE_MONT_P	0x01

#ifndef HEADER_COMMON_DSA_H_TYPEDEF_DEF
#define HEADER_COMMON_DSA_H_TYPEDEF_DEF
typedef struct dsa_st DSA;
#endif /* HEADER_COMMON_DSA_H_TYPEDEF_DEF */

struct dsa_st
	{
        /* This first variable is used to pick up errors where
         * a DSA is passed rather than an EVP_PKEY */
        int pad;
        int version;
        int write_params;
        BIGNUM *p;
        BIGNUM *q;      /* == 20 */
        BIGNUM *g;
       
        BIGNUM *pub_key;  /* y public key */
        BIGNUM *priv_key; /* x private key */
       
        BIGNUM *kinv;   /* Signing pre-calc */
        BIGNUM *r;      /* Signing pre-calc */
       
        int flags;
        /* Normally used to cache montgomery values */
        char *method_mont_p;
	int references;
	};

#ifndef NOPROTO

DSA *	DSA_new(void);
void	DSA_set_size_cb(int (*cb)());
int	DSA_size(DSA *dsa);
/* Set the callbacks for the signature and verification code */
void 	DSA_set_sign_cb(int (*cb)());
void 	DSA_set_sign_init_cb(int (*cb)());
void 	DSA_set_verify_cb(int (*cb)());
	/* next 4 return -1 on error */
int	DSA_sign_setup(DSA *dsa,BN_CTX *ctx_in,BIGNUM **kinvp,BIGNUM **rp);
int	DSA_sign(int type,unsigned char *dgst,int dlen,
		unsigned char *sig, unsigned int *siglen, DSA *dsa);
int	DSA_verify(int type,unsigned char *dgst,int dgst_len,
		unsigned char *sigbuf, int siglen, DSA *dsa);
void	DSA_free(DSA *dsa);

void	ERR_load_DSA_strings(void );

DSA *	d2i_DSAPublicKey(DSA **a, unsigned char **pp, long length);
DSA *	d2i_DSAPrivateKey(DSA **a, unsigned char **pp, long length);
DSA * 	d2i_DSAparams(DSA **a, unsigned char **pp, long length);
DSA *	DSA_generate_parameters(int bits, unsigned char *seed,int seed_len,
		int *counter_ret, unsigned long *h_ret,
		void (*callback)(int,int,char *),char *cb_arg);
int	DSA_generate_key(DSA *dsa);
int	i2d_DSAPublicKey(DSA *dsa, unsigned char **pp);
int 	i2d_DSAPrivateKey(DSA *dsa, unsigned char **pp);
int	i2d_DSAparams(DSA *dsa,unsigned char **pp);

#ifdef HEADER_COMMON_BIO_H
int	DSAparams_print(BIO *bio, DSA *dsa);
int	DSA_print(BIO *bio, DSA *dsa, int off);
#endif
#ifndef NO_FP_API
int	DSAparams_print_fp(FILE *fp, DSA *dsa);
int	DSA_print_fp(FILE *fp, DSA *dsa, int off);
#endif

int DSA_is_prime(BIGNUM *q,void (*callback)(int,int,char *),char *cb_arg);

/* Set the minimal set of functionality in a DSA method (new and free) */
int     DSA_enable_default_method(void);
/* Set the callbacks of the default method */
void    DSA_set_default_method_new_cb(DSA *(*cb)(void));
void    DSA_set_default_method_free_cb(void (*cb)(DSA *));
void    DSA_set_default_method_size_cb(int (*cb)(DSA *));
void    DSA_set_default_method_sign_cb(int (*cb)(int,unsigned char *,int,unsigned char *,unsigned int *,DSA *));
void    DSA_set_default_method_setup_cb(int (*cb)(DSA *,BN_CTX *,BIGNUM **,BIGNUM **));
void    DSA_set_default_method_verify_cb(int (*cb)(int,unsigned char *,int, unsigned char *,int, DSA *));
void    DSA_set_default_method_p_dup_cb(DSA *(*cb)(DSA *));

/* Define SHA_LONG since DSA dirctly uses the SHA
*/
#ifndef SHA_LONG

#if (!defined(OPT_SHA_INT) && !defined(OPT_SHA_LONG))
#define OPT_SHA_LONG
#endif

#ifdef OPT_SHA_LONG
#define SHA_LONG unsigned long
#endif

#ifdef OPT_SHA_INT
#define SHA_LONG unsigned int
#endif

#endif

int dsa_ghash_and_mod(BIGNUM **result,
			     BN_CTX *bn_ctx,
			     SHA_LONG *t_in,
			     unsigned char *message,
			     unsigned int messageLen,
			     BIGNUM *modulus);

#else /* NOPROTO */

DSA *	DSA_new();
void 	DSA_set_size_cb();
int	DSA_size();
void 	DSA_set_sign_cb();
void 	DSA_set_sign_init_cb();
void 	DSA_set_verify_cb();
int	DSA_sign_setup();
int	DSA_sign();
int	DSA_verify();
void	DSA_free();
int     DSA_enable_default_method();

void	ERR_load_DSA_strings();

DSA *	d2i_DSAPublicKey();
DSA *	d2i_DSAPrivateKey();
DSA * 	d2i_DSAparams();
DSA *	DSA_generate_parameters();
int	DSA_generate_key();
int	i2d_DSAPublicKey();
int 	i2d_DSAPrivateKey();
int	i2d_DSAparams();

int	DSA_is_prime();

#ifdef HEADER_COMMON_BIO_H
int	DSAparams_print();
int	DSA_print();
#endif /* HEADER_COMMON_BIO_H */
#ifndef NO_FP_API
int	DSAparams_print_fp();
int	DSA_print_fp();
#endif /* NO_FP_API */

/* Set the minimal set of functionality in a DSA method (new and free) */
int     DSA_enable_default_method();
/* Set the callbacks of the default method */
void    DSA_set_default_method_new_cb();
void    DSA_set_default_method_free_cb();
void    DSA_set_default_method_size_cb();
void    DSA_set_default_method_sign_cb();
void    DSA_set_default_method_setup_cb();
void    DSA_set_default_method_verify_cb();
void    DSA_set_default_method_p_dup_cb();

#endif /* NOPROTO */

/* BEGIN ERROR CODES */
/* Error codes for the DSA functions. */

/* Function codes. */
#define DSA_F_DSAPARAMS_PRINT				 110
#define DSA_F_DSAPARAMS_PRINT_FP			 111
#define DSA_F_DSA_FREE					 103
#define DSA_F_DSA_IS_PRIME				 102
#define DSA_F_DSA_NEW					 104
#define DSA_F_DSA_PARAMS_DUP				 109
#define DSA_F_DSA_PRINT					 112
#define DSA_F_DSA_PRINT_FP				 113
#define DSA_F_DSA_SIGN					 105
#define DSA_F_DSA_SIGN_SETUP				 106
#define DSA_F_DSA_SIZE					 107
#define DSA_F_DSA_VERIFY				 108

/* Reason codes. */
#define DSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE		 100
 
#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_DSA_H */


