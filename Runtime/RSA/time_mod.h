/* $Id: time_mod.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file
 * This file provides defines, structures and function prototypes used by
 * the time module.
 */

#ifndef HEADER_COMMON_TIME_MOD_H
#define HEADER_COMMON_TIME_MOD_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"
#include "r_lib.h"

/**
 * @defgroup R_TIME_MODULE Time Module
 * This section describes how the time module provides support for performing
 * time of day based tasks.
 * @ingroup CME_API
 * @{
 */
/**
 * @}
 */

/* NOTE: These need to be kept consistent with the CRYPTO_FMT...
 * equivalents
 */
/**
 * @defgroup R_TIME_ID Time Identifiers
 * This section lists the identifiers used to specify time formats in
 * the time module.
 * @ingroup R_TIME_MODULE
 * @{
 */

/**
 * Specifies a format string containing Universal Coordinated
 * Time (UTC) <tt>"YYMMDDHHMM[SS](Z|(+|-)HHMM)"</tt>.
 */
#define R_TIME_EXTERNAL_FORMAT_UTC              1

/**
 * Specifies a format string containing generalized time
 * <tt>"YYYYMMDDHHMMSS[.S](Z|(+|-)HHMM)"</tt>.
 */
#define R_TIME_EXTERNAL_FORMAT_GT               2

/**
 * Specifies a format of Big Endian time in seconds since
 * Jan 1, 1970.
 */
#define R_TIME_EXTERNAL_FORMAT_UNIX_BIG_ENDIAN  3

/**
 * Specifies a format of time in seconds since Jan 1, 1970.
 */
#define R_TIME_EXTERNAL_FORMAT_UNIX_NATIVE      5

/**
 * Specifies a text format of time in a simple human 
 * readable form <tt>"YYYY:MM:DD:HH:MM:SS"</tt>.
 */
#define R_TIME_EXTERNAL_FORMAT_SHRF             6

/**
 * Specifies the number of Bytes required to store time in 
 * the Unix Big Endian time format.
 */
#define R_TIME_UNIX_BIG_ENDIAN_SIZE             8

/**
 * Specifies the number of Bytes required to store time in 
 * the Universal Coordinated Time (UTC) including the trailing 
 * <tt>'\0'</tt>.
 */
#define R_TIME_UTC_MAX_SIZE                     18

/**
 * Specifies the number of Bytes required to store time in 
 * the generalized time format including the trailing <tt>'\0'</tt>.
 */
#define R_TIME_GT_MAX_SIZE                      21

/**
 * Specifies the number of Bytes required to store time in 
 * a text format including the trailing <tt>'\0'</tt>.
 */
#define R_TIME_SHRF_SIZE                        20
/**
 * @}
 */


/**
 * @defgroup R_TIME_STRUCT Time Structures
 * This section details the time module structures used to maintain data and
 * methods for the time module.
 * @ingroup R_TIME_MODULE
 * @{
 */

/**
 * This structure indicates the time module context.
 * The time module context is an opaque structure that is created
 * by R_TIME_CTX_new() and needed to create a
 * time module instance. It can be freed via
 * R_TIME_CTX_free() when it is no longer required.
 *
 */
typedef struct r_time_ctx_st                    R_TIME_CTX;

/** 
 * This structure indicates the time module instance structure.
 * A time module instance is an opaque structure that is created
 * by R_TIME_new() and used to provide both methods and states for
 * time of day operations. It can be freed via R_TIME_free() when 
 * it is no longer required.
 */
typedef struct r_time_st                        R_TIME;

/** 
 * This structure indicates the time module method table.
 * A time module method table is an opaque structure that is used
 * to provide the functions for a time module instance.
 */
typedef struct r_time_method_st                 R_TIME_METHOD;

/**
 * @}
 */

/**
 * @defgroup R_TIME_FUNC Time Functions
 *
 * This section details the time module functions used by applications
 * requiring platform-independent time of day operations.
 * @ingroup R_TIME_MODULE
 * @{
 */
int R_TIME_CTX_new(R_LIB_CTX *lib_ctx, R_RES_FLAG flag, R_TIME_CTX **time_ctx);
int R_TIME_CTX_free(R_TIME_CTX *ctx);

int R_TIME_new(R_TIME_CTX *ctx, R_TIME **time_p);
int R_TIME_free(R_TIME *time_p);
int R_TIME_time(R_TIME *time_p);
int R_TIME_cmp(R_TIME *time1, R_TIME *time2, int *comp);
int R_TIME_offset(R_TIME *time1, R_TIME *time2, long off);
int R_TIME_export(R_TIME *time_p, int format, unsigned char *buf, unsigned int *len, 
                  unsigned int max_len);
int R_TIME_import(R_TIME *time_p, int format, unsigned char *buf, unsigned int buf_len);
int R_TIME_dup(R_TIME *f_time, R_TIME **d_time);

R_TIME_METHOD *R_TIME_get_time_mi_method(void *impl_data);
R_TIME_METHOD *R_TIME_get_utc_time_method(void *impl_data);

/**
 * @}
 */

/**
 * @defgroup R_TIME_RES Time Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library. For more information, 
 * see @ref RES_LIST_GROUP.
 * @ingroup R_TIME_MODULE
 *
 * @{
 */

/**
 * The full #R_TIME interface implemented in a
 * machine-independent way. Optional.
 */
#define R_TIME_RES_MI                                               \
    { R_RES_MOD_ID_TIME, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,       \
      R_RES_FLAG_DEF, NULL, NULL,                                   \
      (void *(*)(void *))R_TIME_get_time_mi_method, NULL }

/**
 * The full #R_TIME interface implemented in terms of Universal 
 * Coordinated Time (UTC) time.
 */
#define R_TIME_RES_UTC                                              \
    { R_RES_MOD_ID_TIME, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,       \
      R_RES_FLAG_DEF, NULL, NULL,                                   \
      (void *(*)(void *))R_TIME_get_utc_time_method, NULL }

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_TIME_MOD_H */


