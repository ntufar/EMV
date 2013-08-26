/* $Id: op_res.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
#ifndef HEADER_COMMON_DATA_OP_RES_H
#define HEADER_COMMON_DATA_OP_RES_H

#ifdef  __cplusplus
extern "C" {
#endif

/** @file  op_res.h
 *  Public header file for resource list operation functions and defines.
 */

/**
 * @defgroup OP_BIO_SUB_ID OP BIO Filter Sub Identifiers
 *
 * This section details the identifiers that are used to specify whether the
 * #BIO filter can handle decoding and/or encoding.
 * @ingroup BIO_OP_GROUP
 * @{
 */

/** Resource list sub identifier - only reading handling. */
#define OP_BIO_SUB_ID_READ          0x01
/** Resource list sub identifier - only writing handling. */
#define OP_BIO_SUB_ID_WRITE         0x02
/** Resource list sub identifier - reading and writing handled. */
#define OP_BIO_SUB_ID_DEF           (OP_BIO_SUB_ID_READ | OP_BIO_SUB_ID_WRITE)
/**
 * Resource list sub identifier - converts the indefinite length BER encoding
 * into a DER encoding (must be definitie length).
 */
#define OP_BIO_SUB_ID_DER           0x10

/**
 * @}
 */

/**
 * @defgroup OP_BIO_RES OP BIO Filter Resource List Items
 *
 * This section details the defines to use to include functionality in the
 * resource list.
 * @ingroup BIO_OP_GROUP
 * @{
 */

extern BIO_METHOD *op_get_dec_bio_method();
extern BIO_METHOD *op_get_enc_bio_method();
extern BIO_METHOD *op_get_bio_method();
extern BIO_METHOD *op_get_der_bio_method();

extern int op_bio_state_to_string(int state, unsigned int len, char *data);
extern int op_bio_der_state_to_string(int state, unsigned int len, char *data);

/**
 * The resource list item that allows reading through a BIO of BER data using
 * OP.
 */
#define OP_RES_BIO_READ                                     \
    { R_RES_MOD_ID_BIO, BIO_TYPE_BER, OP_BIO_SUB_ID_READ,   \
      R_RES_FLAG_DEF, NULL, NULL,                           \
      (void *(*)(void *))op_get_dec_bio_method,             \
      (void *(*)(void *))op_bio_state_to_string }

/**
 * The resource list item that allows writing through a BIO of BER data using
 * OP.
 */
#define OP_RES_BIO_WRITE                                    \
    { R_RES_MOD_ID_BIO, BIO_TYPE_BER, OP_BIO_SUB_ID_WRITE,  \
      R_RES_FLAG_DEF, NULL, NULL,                           \
      (void *(*)(void *))op_get_enc_bio_method,             \
      (void *(*)(void *))op_bio_state_to_string }

/**
 * The resource list item that allows reading and writing through a BIO of BER
 * data using OP.
 */
#define OP_RES_BIO_DEFAULT                                  \
    { R_RES_MOD_ID_BIO, BIO_TYPE_BER, OP_BIO_SUB_ID_DEF,    \
      R_RES_FLAG_DEF, NULL, NULL,                           \
      (void *(*)(void *))op_get_bio_method,                 \
      (void *(*)(void *))op_bio_state_to_string }

/**
 * The resource list item that allows conversion of an indefinite length encoded
 * buffer into a DER encoding.
 */
#define OP_RES_BIO_DER                                      \
    { R_RES_MOD_ID_BIO, BIO_TYPE_BER, OP_BIO_SUB_ID_DER,    \
      R_RES_FLAG_DEF, NULL, NULL,                           \
      (void *(*)(void *))op_get_der_bio_method,             \
      (void *(*)(void *))op_bio_der_state_to_string}

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* !HEADER_COMMON_DATA_OP_RES_H */

