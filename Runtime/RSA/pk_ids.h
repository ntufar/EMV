/* $Id: pk_ids.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file pk_ids.h
 * This file contains defines that identify cryptographic components such as
 * the components of public and private keys.
 */
/**
* 
* @defgroup PKDEFS Public Key Defines
* This section contains defines that identify cryptographic components such as
* the components of public and private keys.
* @ingroup CME_API
* 
* @{
*/


#ifndef HEADER_COMMON_PK_IDS_H
#define HEADER_COMMON_PK_IDS_H

#ifdef  __cplusplus
extern "C" {
#endif

/* 
 * The identifier map for the set/get functions of
 * objects that use PK defines directly for retrieving components:
 *
 *   0x0000 0000
 *   0x0000 3FFF           Library PK Identifiers  
 *
 *   0x0000 4000
 *   0x0000 7FFF           Shared Object Identifiers 
 *
 *   0x0000 8000
 *   0x0000 FFFF           Object Specific Identifiers
 *
 *   
 *   0x00FF 0000           Identifier Modifier Masks (bit field of 8 bits)
 *
 *   0x0100 0000           
 *   0x7FFF FFFF           Application PK Identifiers       
 * 
 */

#define PK_LIBRARY_BASE         0x00000000

#define PK_SHARED_ID_BASE       0x00004000
#define PK_SHARED_ID_EXT        PK_SHARED_ID_BASE
#define PK_SHARED_ID_SAN        0x00004200

#define PK_OBJECT_ID_BASE       0x00008000 

#define PK_OBJECT_MOD_R_TIME    0x00010000

#define PK_APPLICATION_BASE     0x7FFFFFFF


/**
 * @defgroup PK_RSA Public Key - RSA Part Defines
 * This section details the defines that relate to parts of an RSA key.
 * @{
 */

/** Indicates that SSL padding is required. */
#define PK_RSA_FLG_PADDING_SSL  0x0800

/** Indicates that RSA blinding is required. */
#define PK_RSA_FLG_BLINDING  0x1000

/* Defines that can be used to get information out of a RSA key */
/** Indicates the group of data items that comprise an RSA key. */
#define PK_TYPE_RSA             0x0010

/** Indicates that the data is the number of primes in the RSA key. A standard 
 *  RSA key will have two primes while MultiPrime keys have three or more.
 */
#define PK_RSA_NUM_PRIMES       0x0001
/** Indicates that we wish to perform the RSA private key operations without
 *  blinding being used.  Blinding is used to stop some timing attacks
 *  against the RSA algorithm.
 */
#define PK_RSA_BLINDING		0x0002
#define PK_RSA_BLINDING_MODE_OFF		0
#define PK_RSA_BLINDING_MODE_NO_UPDATE		1
#define PK_RSA_BLINDING_MODE_FULL_UPDATE	2
#define PK_RSA_BLINDING_MODE_SQR_UPDATE		3

/** Indicates that the data is the modulus (n) of the RSA key. The modulus is 
 *  the product of the primes.
 */
#define PK_RSA_N                0x0010
/** Indicates that the data is the public exponent (e) of the RSA key. The 
 *  public exponent is often 65537 (0x10001) which allows fast exponentiation
 *  calculating.
 */
#define PK_RSA_E                0x0011
/** Indicates that the data is the private exponent (d) of the RSA key. 
 *  The private exponent is the inverse of the public exponent 
 *  (<tt>e.d=1 mod (p-1)(q-1)...</tt>).
 */
#define PK_RSA_D                0x0012
/** Indicates that the data is the <tt>nth</tt> prime of the RSA key. */
#define PK_RSA_PRIME(n)         (0x0013+((n)*3))
/** Indicates that the data is the nth exponent calculation of the RSA key. 
 *  The calculation is the private exponent mod prime - 1 and is a 
 *  pre-calculation used in a Chinese Remainder Theorem implementation
 *  of the private key operations.
 */
#define PK_RSA_EXP(n)           (0x0014+((n)*3))
/** Indicates that the data is the nth inverse calculation of the RSA key. 
 *  The calculation is the inverse of the previous prime mod this prime 
 *  (<tt>inv(q) mod p</tt>) and is a pre-calculation used in a Chinese 
 *  Remainder Theorem implementation of the private key operations.
 */
#define PK_RSA_INV(n)           (0x0015+((n)*3))
/** Indicates that the data is the first subprime for the nth prime of the RSA
 *  key. 
 */
#define PK_RSA_SUBPRIME1(n)     (0x0116+((n)*2))
/** Indicates that the data is the second subprime for the nth prime of the RSA
 *  key. 
 */
#define PK_RSA_SUBPRIME2(n)     (0x0117+((n)*2))


/* Note that P and Q are swapped */
/** Indicates that the data is the first prime (<tt>q</tt>) of the RSA key. 
 */
#define PK_RSA_Q                PK_RSA_PRIME(0)
/** Indicates that the data is the first exponent calculation of the RSA key. 
 *  The calculation is the private exponent <tt>mod (q-1)</tt> and is a 
 *  pre-calculation used in a Chinese Remainder Theorem implementation 
 *  of the private key operations.
 */
#define PK_RSA_DMQ1             PK_RSA_EXP(0)
/** Indicates that the data is the first subprime (<tt>q1</tt>) for the first 
 *  prime q of the RSA key. 
 */
#define PK_RSA_Q1               PK_RSA_SUBPRIME1(0)
/** Indicates that the data is the second subprime (<tt>q2</tt>) for the first 
 *  prime q of the RSA key. 
 */
#define PK_RSA_Q2               PK_RSA_SUBPRIME2(0)
/** Indicates that the data is the second prime (<tt>p</tt>) of the RSA key. 
 */
#define PK_RSA_P                PK_RSA_PRIME(1)
/** Indicates that the data is the second exponent calculation of the RSA key. 
 *  The calculation is the private exponent <tt>mod (p-1)</tt> and is a 
 *  pre-calculation used in a Chinese Remainder Theorem implementation 
 *  of the private key operations.
 */
#define PK_RSA_DMP1             PK_RSA_EXP(1)
/** Indicates that the data is the second inverse calculation of the RSA key. 
 *  The calculation is the inverse of the previous prime <tt>mod</tt> this 
 *  prime (<tt>inv(q) mod p</tt>) and is a pre-calculation used in a 
 *  Chinese Remainder Theorem implementation of the private key operations.
 */
#define PK_RSA_IQMP             PK_RSA_INV(1)
/** Indicates that the data is the first subprime (<tt>p1</tt>) for the second 
 *  prime p of the RSA key. 
 */
#define PK_RSA_P1               PK_RSA_SUBPRIME1(1)
/** Indicates that the data is the second subprime (<tt>p2</tt>) for the second 
 *  prime p of the RSA key. 
 */
#define PK_RSA_P2               PK_RSA_SUBPRIME2(1)

/**
 * @}
 */

/**
 * @defgroup PK_DH Public Key - Diffie-Hellman Part Defines
 * This section details the defines that relate to the parts of a 
 * Diffie-Hellman key.
 * @{
 */

/* Defines that can be used to get information out of a DH key */
/** Indicates the group of data items that comprise a Diffie-Hellman key. */
#define PK_TYPE_DH              0x0012

/** Indicates that the data is the prime parameter of the Diffie-Hellman key. 
 *  The prime value identifies the Galois field <tt>p=jq+1</tt>.
 */
#define PK_DH_P                 0x0001
/** Indicates that the data is the prime parameter of the Diffie-Hellman key. 
 *  The prime value identifies the Galois field <tt>p=jq+1</tt>.
 */
#define PK_DH_PRIME             PK_DH_P
/** Indicates that the data is the generator parameter of the Diffie-Hellman 
 *  key. The generator is the multiplicative subgroup order. It is the 
 *  exponential base used when calculating the public and private key.
 */
#define PK_DH_G                 0x0002
/** Indicates that the data is the generator parameter of the Diffie-Hellman 
 *  key. The generator is the multiplicative subgroup order. It is the 
 *  exponential base used when calculating the public and private key.
 */
#define PK_DH_GENERATOR         PK_DH_G
/** Indicates that the data is the public key value of the Diffie-Hellman key.
 *  The public key is calculated by raising the generator to a random value
 *  <tt>mod p (y=g^x mod p)</tt>.
 */
#define PK_DH_PUB_KEY           0x0003
/** Indicates that the data is the public key value of the Diffie-Hellman key.
 *  The public key is calculated by raising the generator to a random value
 *  <tt>mod p (y=g^x mod p)</tt>.
 */
#define PK_DH_Y                 PK_DH_PUB_KEY
/** Indicates that the data is the private key value of the Diffie-Hellman key.
 *  The private key is the random value used as the exponent in calculating
 *  the public key.
 */
#define PK_DH_PRIV_KEY          0x0004
/** Indicates that the data is the private key value of the Diffie-Hellman key.
 *  The private key is the random value used as the exponent in calculating
 *  the public key.
 */
#define PK_DH_X                 PK_DH_PRIV_KEY
/** Indicates that the data is the length of the private key value in a 
 *  Diffie-Hellman key. The length determines the security of a 
 *  Diffie-Hellman key.
 */
#define PK_DH_PRIV_LENGTH       0x0005
/** Indicates that the data is the length of the private key value in a 
 *  Diffie-Hellman key. The length determines the security of a 
 *  Diffie-Hellman key.
 */
#define PK_DH_EXP_BITS          PK_DH_PRIV_LENGTH

/**
 * @}
 */


/**
 * @defgroup PK_DSA Public Key - DSA Part Defines
 * This section details the defines that relate to the parts of a DSA key.
 * @{
 */

/* Defines that can be used to get information out of a DSA key */
/** Indicates the group of data items that make up a DSA key. */
#define PK_TYPE_DSA             0x0014

/* do not change the order (or the values) without updating the
 * DSA methods */

/** Indicates that the data is the prime modulus parameter <tt>(p)</tt> of the
 *  DSA key. The prime modulus identifier is between <tt>2^(L-1)</tt> and
 *  <tt>2^L</tt> for <tt>L</tt> in the range <tt>512-1024</tt> and is a
 *  multiple of <tt>64</tt>.
 */
#define PK_DSA_P                0x0020

/** Indicates that the data is the prime modulus parameter <tt>(p)</tt> of the
 *  DSA key. The prime modulus identifier is between <tt>2^(L-1)</tt> and
 *  <tt>2^L</tt> for <tt>L</tt> in the range <tt>512-1024</tt> and is a
 *  multiple of <tt>64</tt>.
 */
#define PK_DSA_PRIME            0x0020

/** Indicates that the data is the sub-prime/prime divisor parameter
 *  <tt>(q)</tt>of the DSA key. The sub-prime is a prime divisor of the
 *  <tt>prime - 1</tt> between <tt>2^159</tt> and <tt>2^160</tt>.
 */
#define PK_DSA_Q                0x0021

/** Indicates that the data is the sub-prime/prime divisor parameter
 *  <tt>(q)</tt>of the DSA key. The sub-prime is a prime divisor of the
 *  <tt>prime - 1</tt> between <tt>2^159</tt> and <tt>2^160</tt>.
 */
#define PK_DSA_SUBPRIME         0x0021

/** Indicates that the data is the base/generator parameter <tt>(g)</tt>
 *  of the DSA key. The base/generator is used as the exponential base for
 *  DSA calculations <tt>g = h^[(p-1)/q]</tt>.
 */
#define PK_DSA_G                0x0022

/** Indicates that the data is the base/generator parameter <tt>(g)</tt>
 *  of the DSA key. The base/generator is used as the exponential base for
 *  DSA calculations <tt>g = h^[(p-1)/q]</tt>.
 */
#define PK_DSA_BASE             0x0022

/** Indicates that the data is the public key value <tt>(y)</tt> of the DSA
 *  key. The public key is the base/generator value raised to the private 
 *  key part <tt>mod p (y=g^x mod p)</tt>.
 */
#define PK_DSA_PUB_KEY          0x0023

/** Indicates that the data is the private key value <tt>(x)</tt> of the DSA
 *  key. The private key is a randomly or pseudo-randomly generated integer 
 *  between <tt>0</tt> and the sub-prime/divisor.
 */
#define PK_DSA_PRIV_KEY         0x0024

/** Indicates that the data is the seed used in the generation of the DSA key. 
 *  The value of the seed is retained for use in certifying the proper
 *  generation of p and q.
 */
#define PK_DSA_SEED             0x0025

/** Indicates that the data is the counter used in the generation of the prime 
 *  modulus parameter <tt>(p)</tt> of the DSA key. The value of the counter is
 *  retained for use in certifying the proper generation of p.
 */
#define PK_DSA_COUNTER          0x0026

/** Indicates that the data is the value <tt>(h)</tt> used to generate the
 *  base/generator parameter g of the DSA key. The value of h is
 *  retained for use in certifying the proper generation of g.
 */
#define PK_DSA_H                0x0027

/**
 * @}
 */

/*
 * @defgroup PK_ECC Public Key - ECC Part defines
 * This section details the defines that relate to the parts of an ECC key.
 * @{
 */

/*
 * Indicates that the group of data items relate to ECC keys.
 */
#define PK_TYPE_ECC             0x0018

/*
 * The data is the object identifier of the type of ECC algorithm.
 */
#define PK_ECC_OID              0x0001

/*
 * The data is the paramters to use when performing an ECC operation.
 */
#define PK_ECC_PARAMS           0x0002

/*
 * The data is the public key of an ECC public-private key.
 */
#define PK_ECC_PUB_KEY          0x0003

/*
 * @}
 */

/**
 * @defgroup PK_CERT PK - Certificate Part Defines
 * This section details the defines that relate to the parts of a certificate.
 * @{
 */

/** Indicates that the data is the version of the format of the certificate.
 *  The value is stored in <tt>length</tt> of #R_EITEM rather than the data
 *  field.
 */
#define PK_CERT_VER                     0x0001
/** Indicates that the data is the serial number of the certificate. This is
 *  an integer value of a variable length.
 */
#define PK_CERT_SERIAL                  0x0002
/** Indicates that the data is the object identifier of the digest algorithm
 *  used in generating the hash of the certificate body for the signature.
 */
#define PK_CERT_ALG_ID                  0x0003
/** Indicates that the data is the issuer name of the certificate. 
 */
#define PK_CERT_ISSUER                  0x0004
/** Indicates that the data is the time before which the certificate is 
 *  not valid. 
 */
#define PK_CERT_NOT_BEFORE              0x0005
/** Indicates that the data is the time after which the certificate is 
 *  not valid. 
 */
#define PK_CERT_NOT_AFTER               0x0006
/** Indicates that the data is the subject name of the certificate. The name
 *  identifies the owner of the certificate.
 */
#define PK_CERT_SUBJECT                 0x0007
/** Indicates that the data is the object identifier that represents the type
 *  of public key stored in the certificate. This define is obsolete.
 */
#define PK_CERT_PUBKEY_ID               0x0008
/** Indicates that the data is the public key information of a certificate
 *  and contains a key, an identifier, and, sometimes, parameters for the key.
 */
#define PK_CERT_PUBKEY                  0x0009
/** Indicates that the data is a unique identifier that acts as a replacement
 *  for the issuer name in the case of an issuer name being reused.
 */
#define PK_CERT_ISSUER_ATTRS            0x000a
/** Indicates that the data is a unique identifier that acts as a replacement 
 *  for the subject name in the case of an issuer name being reused.
 */
#define PK_CERT_SUBJECT_ATTRS           0x000b
/** Indicates that the data is a set of extensions that can be used to include
 *  additional attributes to the certificate.
 */
#define PK_CERT_EXTENSIONS              0x000c
/** Indicates that the data is the identifier of the digest-signing algorithm 
 *  used in generating the signature of the certificate.
 */
#define PK_CERT_SIG_ALG_ID              0x000d
/** Indicates that the data is the signature of the certificate. The signature
 *  is calculated by digesting the body of the certificate and signing it
 *  with the issuer's private key.
 */
#define PK_CERT_SIGNATURE               0x000e
/** Indicates that the data is the set of parameters associated with a public 
 *  key. This define is obsolete.
 */
#define PK_CERT_PUBKEY_PARAMS           0x000f
/** Indicates that the data is the body of the certificate. The body includes
 *  all fields of the certificate except for the signature information.
 */
#define PK_CERT_BODY                    0x0040
/** Indicates that the data is the signature information of the certificate. 
 *  The signature information includes the algorithm identifier and signature.
 */
#define PK_CERT_SIG_INFO                0x0041

#define PK_CERT_ALL                     0x007f

/**
 * @}
 */

/**
 * @defgroup PK_CRL PK - Certificate Revocation List Defines
 * This section details the defines that relate to the parts of a CRL.
 * @{
 */

/** The data is the version of the CRL.
 */
#define PK_CRL_VER                      0x0001
/** The data is the object identifier of the signature algorithm used in
 *  generating the signature of the CRL body.
 */
#define PK_CRL_ALG_ID                   0x0003
/** The data is the parameters of the signature algorithm used in
 *  generating the signature of the CRL body.
 */
#define PK_CRL_ALG_PARAMS               0x0013

/** The data is the common issuer name of the certificates.  */
#define PK_CRL_ISSUER                   0x0004

/** The data is the date the last issued CRL became invalid. */
#define PK_CRL_LAST                     0x0005

/** The data is the date the next CRL becomes valid. */
#define PK_CRL_NEXT                     0x0006

#define PK_CRL_EXTENSIONS               0x0010

/** The data is the count of entries in the CRL. Each entry contains
 *  identification information and revocation timing information of the
 *  certificate that has been revoked.
 */
#define PK_CRL_CNT                      0x001f

/**
 * @}
 */

/**
 * @defgroup PK_AKI PK - Authority Key Identifier Defines
 * This section details the defines that relate to the Authority Key Identifier
 * Extension .
 * @{
 */

/** The data is the key identifier field. This is an octet string.
 */
#define PK_AKI_KEY_ID                   0x0001

/** The data is the certificate issuer field. This is a general name.
 */
#define PK_AKI_CERT_ISSUER              0x0002

/** The data is the certificate serial number field. This is an integer.
 */
#define PK_AKI_CERT_SERIAL_NUMBER       0x0003

/**
 * @}
 */

/**
 * @defgroup PK_RC2_PARAM PK - RC2 Parameter Defines
 * This section details the defines that relate to the parts of the RC2
 * parameters.
 * @{
 */

/**
 * Indicates that the group of data items that make up the RC2 parameters.
 */
#define PK_TYPE_RC2_PARAM               0x0038

/**
 * The data is the IV of the RC2 parameters.
 */
#define PK_RC2_PARAM_IV                 0x0002

/**
 * The data is the effective key bits to use in RC2 operations.
 */
#define PK_RC2_PARAM_EFF_KEY_BITS       0x0004

/**
 * @}
 */

/**
 * @defgroup PK_RC5_PARAM PK - RC5 Parameter Defines
 * This section details the defines that relate to the parts of the RC5
 * parameters.
 * @{
 */

/**
 * Indicates that the group of data items that make up the RC5 parameters.
 */
#define PK_TYPE_RC5_PARAM               0x0039

/**
 * The data is the version of the RC5 parameters structure.
 */
#define PK_RC5_PARAM_VER                0x0001

/**
 * The data is the IV of the RC5 parameters.
 */
#define PK_RC5_PARAM_IV                 0x0002

/**
 * The data is the number of rounds per RC5 operation to perform.
 */
#define PK_RC5_PARAM_ROUNDS             0x0003

/**
 * The data is the size (in bits) of a block for the RC5 operation.
 */
#define PK_RC5_PARAM_BLOCK_SIZE         0x0004

/**
 * This is used to supply a void (*func)(int lock) callback
 * that will be called to lock/unlock when any internal data
 * fields are updated.  It needs to be used when a RSA structure is
 * shared between multiple threads
 */
#define PK_RSA_BLINDING_LOCK		0x0005

/**
 * @}
 */


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_PK_IDS_H */

/**
* @}PKDEFS
*/



