/* $Id: r_imode.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_imode.h
 * This file contains the list of defines required for the I-MODE environment.
 *
 * The defines are located in this file to reduce the need for a large
 * number of defines on the compile command line for I-MODE system builds.
 */

#ifndef HEADER_COMMON_R_IMODE_H
#define HEADER_COMMON_R_IMODE_H

/* We must have prototypes for functions that deal with pointers and
 * longs or we break things as ints are only two bytes
 */
#include <string.h>

/* 16-bit environment */
#define OPT_16_BIT

/* Use faster version of EXP_MONT  */
#undef NO_BN_MOD_EXP_MONT

/* We want to place large stack items in global space */
#define CCONV

#define R_INT32 long
#define R_UINT32 unsigned long

/* We need R_os_clear_sys_error as we use it in quite a few places
 * and as we are not including e_os.h (it comes directly here)
 * it has to be done now
 */
#define R_os_get_last_sys_error()	errno
#define R_os_clear_sys_error()	errno=0

/* If your system has time.h please delete the following lines */
#ifndef SOLARIS
#define NO_TIME_H
#define NO_UNISTD_H
#endif

/* If your system doesn't have socket I/F, please add the following lines
#define NO_SOCK
*/

#ifdef USE_SOCKETS
#define INVALID_SOCKET	(-1)
#endif

/* If your system has stdio/file IO function, please add delete the
 * following lines
 */
#ifndef SOLARIS
#define NO_FP_API
#endif

/* I-MODE specific switches */
#ifndef SMALL_CODE_SIZE
#define SMALL_CODE_SIZE
#endif
#ifndef NO_DES_READ_PWD_C
#define NO_DES_READ_PWD_C
#endif
#ifndef NO_CRYPTO_TMDIFF_C
#define NO_CRYPTO_TMDIFF_C
#endif
#ifndef NO_TEST
#define NO_TEST
#endif
#ifndef NO_RIPEMD
#define NO_RIPEMD
#endif
#ifndef NO_PROXY
#define NO_PROXY
#endif
#ifndef NO_OBJ_ADD
#define NO_OBJ_ADD
#endif
#ifndef NO_TLS1
#define NO_TLS1
#endif
#ifndef NO_TXT_DB
#define NO_TXT_DB
#endif
#ifndef NO_READ_PWD
#define NO_READ_PWD
#endif
#ifndef NO_CONF
#define NO_CONF
#endif
#ifndef NO_MDC2
#define NO_MDC2
#endif
#ifndef NO_PKCS7
#define NO_PKCS7
#endif
#ifndef NO_BF
#define NO_BF
#endif
#ifndef NO_ERR
#define NO_ERR
#endif
#ifndef NO_RC5
#define NO_RC5
#endif
#ifndef NO_CAST
#define NO_CAST
#endif
#ifndef NO_DH
#define NO_DH
#endif
#ifndef NO_COMP
#define NO_COMP
#endif
#ifndef NO_IDEA
#define NO_IDEA
#endif
#ifndef NO_ASN1
#define NO_ASN1
#endif
#ifndef NO_APPS
#define NO_APPS
#endif
#ifndef NO_LIBCRL
#define NO_LIBCRL
#endif
#ifndef NO_DSA
#define NO_DSA
#endif
#ifndef NO_X509V3
#define NO_X509V3
#endif
#ifndef NO_X509_VERIFY
#define NO_X509_VERIFY
#endif
#ifndef NO_CA_LIST
#define NO_CA_LIST
#endif
#ifndef NO_TMP_PKEY
#define NO_TMP_PKEY
#endif
#ifndef NO_PEM
#define NO_PEM
#endif
#ifndef MFUNC
#define MFUNC
#endif
#ifdef NO_ECC
#define NO_ECC
#endif
#ifndef NO_AES
#define NO_AES
#endif
#ifndef NO_RC6
#define NO_RC6
#endif

#ifndef NO_SHA256
#define NO_SHA256
#endif
#ifndef NO_TIME_MI_MODULE
#define NO_TIME_MI_MODULE
#endif

/* Removes the auto-server tmp key stuff - some of this is in
 * shared client/server code - see ssl/s3_lib.c - we should
 * revisit this later.
 */
#define NO_TMP_PKEY

/* No dynamic adding of objects */
#define NO_OBJ_ADD

/* Client code to handle the ca list from the server is gone - as we
 * don't have client certificate support losing this is okay for now
 */
#define NO_CA_LIST

#define NO_CRL

/* We have *no* default for verify - application must provide one or handle
 * via other mechanisms or we will fail to allow connections unless
 * verify mode is left as VERIFY_NONE
 */
#define NO_X509_VERIFY

#endif /* !HEADER_COMMON_R_IMODE_H */

