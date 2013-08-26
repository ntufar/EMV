/* $Id: r_time.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_time.h
 * This file contains the time management Application Programming Interface
 * (API) prototypes, structures and defines.
 */

#ifndef HEADER_COMMON_R_TIME_H
#define HEADER_COMMON_R_TIME_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"

typedef union r_time_t_st R_TIME_T;
union r_time_t_st {
        struct r_secs_st{
                R_INT32 high; /* high 32 bits */
                R_UINT32 low; /* low 32 bits */
                R_UINT32 nano;
        } secs;
        R_INT32 force_align;
        unsigned char bytes[sizeof(R_INT32)*3];
};

/**
 * @defgroup R_TIME_GROUP Time Management
 * This section outlines the functions and identifiers which provide a
 * platform-independent way of handling system time operations.
 * @ingroup CME_API
 * @{
 */
/**
 * @}
 */


#ifdef CT_INT32
#undef CT_INT32
#endif
#ifdef CT_UINT32
#undef CT_UINT32
#endif
#define CT_INT32            R_INT32
#define CT_UINT32           R_UINT32

#define CRYPTO_TIME_T           R_TIME_T

#define CRYPTO_time         R_time
#define CRYPTO_time_offset      R_time_offset
#define CRYPTO_time_export      R_time_export
#define CRYPTO_time_import      R_time_import
#define CRYPTO_time_cmp         R_time_cmp

#define CRYPTO_time_to_int              R_time_to_int
#define CRYPTO_time_from_int            R_time_from_int

#define CRYPTO_get_time_cb      R_time_get_func
#define CRYPTO_set_time_cb      R_time_set_func

#define CRYPTO_get_time_offset_cb   R_time_get_offset_func
#define CRYPTO_set_time_offset_cb   R_time_set_offset_func

#define CRYPTO_get_time_cmp_cb      R_time_get_cmp_func
#define CRYPTO_set_time_cmp_cb      R_time_set_cmp_func

#define CRYPTO_get_time_import_cb   R_time_get_import_func
#define CRYPTO_set_time_import_cb   R_time_set_import_func

#define CRYPTO_get_time_export_cb   R_time_get_export_func
#define CRYPTO_set_time_export_cb   R_time_set_export_func

/**
 * @defgroup TIME_FORMAT Time Formats
 * This section outlines the time formats that are recognized by the time
 * handling code.
 * @ingroup R_TIME_GROUP
 * @{
 */

/**
 * Specifies a format string containing Universal Coordinated
 * Time (UTC) <tt>"YYMMDDHHMM[SS](Z|(+|-)HHMM)"</tt>. Its value is according
 * to the ASN.1 notation.
 */
#define R_TIME_FMT_UTC              23

/**
 * Specifies a format string containing generalized time
 * <tt>"YYYYMMDDHHMMSS.S(Z|(+|-)HHMM)"</tt>. Its value is according to the
 * ASN.1 notation.
 */
#define R_TIME_FMT_GENERALIZEDTIME  24

/**
 * Specifies a format of Big Endian time in seconds since January 1 1970.
 */
#define R_TIME_FMT_BIGENDIAN        3

/**
 * @}
 */

/**
 * @defgroup TIME_LEN Time Format Lengths
 * This section defines the maximum size of the output of each recognized
 * time format.
 * @ingroup R_TIME_GROUP
 * @{
 */

/**
 * Specifies the maximum size of the output for Universal Coordinated
 * Time (UTC) time.
 */
#define R_TIME_LEN_UTC          (13+1)

/**
 * Specifies the maximum size of the output for generalized time.
 */
#define R_TIME_LEN_GENERALIZEDTIME  (16+1)

/**
 * Specifies the maximum size of the output for Big Endian time.
 */
#define R_TIME_LEN_BIGENDIAN        (sizeof(R_INT32)*2)

/**
 * @}
 */

/**
 * @defgroup TIME_RANGE Time Ranges
 * This section lists the ranges of time values for each recognized format.
 * @ingroup R_TIME_GROUP
 * @{
 */

/**
 * Specifies the minimum time value for formatted Universal Coordinated
 * Time (UTC).
 */
#define R_TIME_MIN_UTC          "500101000000Z"

/**
 * Specifies the maximum time value for formatted Universal Coordinated
 * Time (UTC).
 */
#define R_TIME_MAX_UTC          "491231235959Z"

/**
 * Specifies the EPOCH time value for formatted Universal Coordinated
 * Time (UTC).
 */
#define R_TIME_NAN_UTC          "000000000000Z"

/**
 * Specifies the minimum time value for generalized time.
 */
#define R_TIME_MIN_GENERALIZEDTIME  "00000101000000.0Z"

/**
 * Specifies the maximum time value for generalized time.
 */
#define R_TIME_MAX_GENERALIZEDTIME  "99991231235959.9Z"

/**
 * Specifies the EPOCH time value for generalized time.
 */
#define R_TIME_NAN_GENERALIZEDTIME  "00000000000000.0Z"

/**
 * @}
 */

#define CRYPTO_FMT_UTC          R_TIME_FMT_UTC
#define CRYPTO_FMT_GENERALIZEDTIME  R_TIME_FMT_GENERALIZEDTIME
#define CRYPTO_FMT_BIGENDIAN        R_TIME_FMT_BIGENDIAN

#define CRYPTO_LEN_UTC          R_TIME_LEN_UTC
#define CRYPTO_LEN_GENERALIZEDTIME  R_TIME_LEN_GENERALIZEDTIME
#define CRYPTO_LEN_BIGENDIAN        R_TIME_LEN_BIGENDIAN

#define CRYPTO_MIN_UTC          R_TIME_MIN_UTC
#define CRYPTO_MAX_UTC          R_TIME_MAX_UTC
#define CRYPTO_NAN_UTC          R_TIME_NAN_UTC
#define CRYPTO_MIN_GENERALIZEDTIME  R_TIME_MIN_GENERALIZEDTIME
#define CRYPTO_MAX_GENERALIZEDTIME  R_TIME_MAX_GENERALIZEDTIME
#define CRYPTO_NAN_GENERALIZEDTIME  R_TIME_NAN_GENERALIZEDTIME


/**
 * Compares two #R_TIME_T structures <i>tm1</i>
 * and <i>tm2</i>.
 *
 * @param tm1  [In]  The first #R_TIME_T reference to be 
 *                   compared with <i>tm2</i>.
 * @param tm2  [In]  The second #R_TIME_T reference to be 
 *                   compared with <i>tm1</i>.
 *
 * @see R_time_cmp().
 */
typedef int R_TIME_CMP_FUNC_T(R_TIME_T *tm1, R_TIME_T *tm2);

/** 
 * Exports an #R_TIME_T structure <i>tm</i> in a given format.
 *
 * @param tm       [In]   A pointer to input #R_TIME_T time value.<br>
 *                        <tt>NULL</tt> causes the function to fail.
 * @param format   [In]   The output format. One of:<br>
 * <li>#R_TIME_EXTERNAL_FORMAT_UTC</li>.
 * <li>#R_TIME_EXTERNAL_FORMAT_GT</li>.
 * <li>#R_TIME_EXTERNAL_FORMAT_UNIX_BIG_ENDIAN</li>.
 * <li>#R_TIME_EXTERNAL_FORMAT_UNIX_NATIVE</li>.
 * <li>#R_TIME_EXTERNAL_FORMAT_SHRF</li>.
 * @param buffer   [Out]  The buffer to hold the result of the conversion.<br>
 * <tt>NULL</tt> causes the function to fail.
 * @param buf_len  [In]   The length of the output buffer.
 *
 * @note The operation fails if the length is not sufficient to 
 *       store the result.
 *
 * @see R_time_export().
 */
typedef int R_TIME_EXPORT_FUNC_T(R_TIME_T *tm, int format, char *buffer,
    int buf_len);

/**
 * Returns the current time in the #R_TIME_T structure <i>tm</i>.
 *
 * @param tm  [Out]  The #R_TIME_T reference.
 *
 * @see R_time().
 */
typedef R_TIME_T *R_TIME_FUNC_T(R_TIME_T *tm);

/** 
 * Converts the input data buffer from the given time format to #R_TIME_T.
 *
 * @param buffer   [In]   The buffer containing formatted data for conversion.
 * @param buf_len  [In]   The length of <i>buffer</i>.
 * @param format   [In]   The input format. One of:<br>
 * <li>#R_TIME_FMT_BIGENDIAN.</li>
 * <li><tt>R_TIME_FMT_GENERALIZED_TIME</tt>.</li>
 * <li>#R_TIME_FMT_UTC.</li>
 * @param tm       [Out]  A pointer to the destination #R_TIME_T structure.<br>
 * <tt>NULL</tt> causes the function to fail.
 *
 * @see R_time_import().
 */
typedef int R_TIME_IMPORT_FUNC_T(char *buffer, int buf_len, 
            int format, R_TIME_T *tm);

/** 
 * Adds an offset in seconds and nanoseconds to the
 * given time value <i>tm</i> and returns the results.
 *
 * @param ret          [Out]  A pointer to the result time.
 * @param tm           [In]   A pointer to the time to offset.
 * @param secs_offset  [In]   The offset in seconds (can be positive or
 * negative).
 * @param nano_offset  [In]   The nanoseconds component of the offset. This
 * can be positive or negative but must not exceed a magnitude of 1
 * second.
 *
 * @see R_time_offset().
 */
typedef R_TIME_T *R_TIME_OFFSET_FUNC_T(R_TIME_T *ret, R_TIME_T *tm,
    R_INT32 secs_offset, R_INT32 nano_offset);


/**
 * @defgroup TIME_FUNCS Time Functions
 * This section outlines the functions that facilitate time management.
 * @ingroup R_TIME_GROUP
 * @{
 */

int R_time_size(void);

R_TIME_T *R_time_new(void);
void R_time_free(R_TIME_T *tm);

R_TIME_T *R_time(R_TIME_T *tm);
R_TIME_FUNC_T *R_time_get_func(void);
void R_time_set_func(R_TIME_FUNC_T *func);

R_TIME_T *R_time_offset(R_TIME_T *ret, R_TIME_T *tm,
    R_INT32 secs_offset, R_INT32 nano_offset);
R_TIME_OFFSET_FUNC_T *R_time_get_offset_func(void);
void R_time_set_offset_func(R_TIME_OFFSET_FUNC_T *func);

int R_time_from_int(R_TIME_T *tm, int i);
int R_time_to_int(R_TIME_T *tm);

int R_time_cmp(R_TIME_T *tm1, R_TIME_T *tm2);
R_TIME_CMP_FUNC_T *R_time_get_cmp_func(void);
void R_time_set_cmp_func(R_TIME_CMP_FUNC_T *func);

int R_time_import(char *buffer, int buf_len, int format, R_TIME_T *tm);
R_TIME_IMPORT_FUNC_T *R_time_get_import_func(void);
void R_time_set_import_func(R_TIME_IMPORT_FUNC_T *func);

int R_time_export(R_TIME_T *tm, int format, char *buffer, int buf_len);
R_TIME_EXPORT_FUNC_T *R_time_get_export_func(void);
void R_time_set_export_func(R_TIME_EXPORT_FUNC_T *func);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_TIME_H */






