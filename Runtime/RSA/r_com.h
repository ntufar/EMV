/* $Id: r_com.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_com.h
 * This file contains the common library prototypes, defines and structures.
 */
#ifndef HEADER_COMMON_R_COM_H
#define HEADER_COMMON_R_COM_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * The define for identifying the availability of library header 
 * <tt>stdio.h</tt>.
 */
#ifndef NO_STDIO_H
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if !defined(WIN32) && !defined(UNDER_PALMOS)
/**
 * The define for identifying the availability of library header
 * <tt>unistd.h</tt>.
 */
#ifndef NO_UNISTD_H
#include <unistd.h>
#endif /* NO_UNISTD_H */
#endif

#if defined(WIN32) || defined(MSDOS)
#ifndef UNDER_CE
#include <io.h>
#include <fcntl.h>
#endif /* !UNDER_CE */
#endif /* WIN32 || MSDOS */

/*
 * specify the platform specific path and directory delimiters
 * (i.e. the separator between elements in the path)
 */
#if defined(WIN32) || defined(MSDOS)
#define R_PATH_DELIMITER	';'
#define R_DIRECTORY_DELIMITER	'\\'
#else /* !(WIN32 || MSDOS) */
#define R_PATH_DELIMITER	':'
#define R_DIRECTORY_DELIMITER	'/'
#endif /* WIN32 || MSDOS */

/**
 * The define for identifying the availability of library header 
 * <tt>time.h</tt>.
 */
#ifndef NO_TIME_H
#include<time.h>
#endif

/*
 * Portability code for sleep function, use Sleep instead of sleep.
 */
#include "r_sleep.h"

/* Provide the current version of the library */
/**
 * Indicates the common library revision number.
 */
#define RCOM_VERSION_NUMBER               0x2300

/* Include the define values for the standard error codes */
#include "r_error.h"

#if defined(WINDOWS) || defined(WIN32)
#if defined(WIN32_DRIVER)
#include <ntddk.h>
#else /* WIN32_DRIVER */
#include <windows.h>
#endif /* WIN32_DRIVER */
/**
 * @fn int R_os_get_last_sys_error()
 *
 * Retrieves the last system error that occurred in the application.
 *
 * @return  The last system error.
 */
#define R_os_get_last_sys_error()          GetLastError()
/**
 * @fn void R_os_clear_sys_error()
 *
 * Resets the last system error that occurred in the application.
 */
#define R_os_clear_sys_error()             SetLastError(0)
#else
/**
 * @fn int R_os_get_last_sys_error()
 *
 * Retrieves the last system error that occurred in the application.
 *
 * @return  The last system error.
 */
#define R_os_get_last_sys_error()          errno
/**
 * @fn void R_os_clear_sys_error()
 *
 * Resets the last system error that occurred in the application.
 */
#define R_os_clear_sys_error()             errno=0
#endif

#ifndef R_YIELD_DEFINED
#define R_YIELD_DEFINED
#define R_yield_task(a)
#endif /* !R_YIELD_DEFINED */

/*
 * WIN16 requires additional information on the front of functions that
 * may cross the application/DLL boundary
 *
 * Although WIN16 is not a supported platform there is code that used to
 * support WIN16 in use and these macros let it continue to operate
 * unchanged
 */
#if !defined(MS_CALLBACK) || !defined(MS_FAR)
#ifdef WIN16
#define MS_CALLBACK   _far _loadds
#define MS_FAR        _far
#else /* !WIN16 */
#define MS_CALLBACK
#define MS_FAR
#endif /* WIN16 */
#endif /* !MS_CALLBACK || MS_FAR */

/*
 * MS_STATIC is used for items that are placed on the stack normally but
 * are safe to make static (i.e. global) in environments with small runtime
 * stacks
 */
#ifndef MS_STATIC
#if defined(WIN16) || defined(MSDOS) || defined(UNDER_PALMOS)
#define MS_STATIC   static
#else
#define MS_STATIC
#endif /* !WIN16 !MSDOS !UNDER_PALMOS */
#endif /* !MS_STATIC */

#if !defined(RCOM_LEAN)

/* include basic platform IO definitions
 *
 *  This file should be included prior to r_mem.h when building
 *  for vxWorks with the Tornado 2 environment. There is a define
 *  for Free in vxWorks that is also used in r_mem.h
 */

/* r_vxworks.h should be included before r_sock.h to prevent an
 * out-of order definition in Tornado 1 (netdb.h is not supplied).
 * r_mem.h has to be defined after r_sock.h for VxWorks.
 */

#ifdef VXWORKS
#include "r_vxworks.h"
#endif

#if !defined(NO_SOCK)
#include "r_sock.h"
#endif

#include "r_mem.h"

#if defined(PLATFORM_IMODE)
#include "r_imode.h"
#endif /* !PLATFORM_IMODE */

/* include support for asserts */
#include "r_assert.h"

/* include the endian macros */
#include "r_endian.h"

/* include the locking routines and CRYPTO definitions */
#include "r_lock.h"

/* include the surrender functions */
#include "r_surr.h"

#endif /* !defined(RCOM_LEAN) */

#ifndef Memcpy
/**
 * Transparently maps the arguments for the system function <tt>memcpy</tt>
 * or equivalent so it is platform-independent.
 */
#define Memcpy memcpy
#endif

#ifndef Memmove
/**
 * Transparently maps the arguments for the system function <tt>memmove</tt>
 * or equivalent so it is platform-independent.
 */
#define Memmove memmove
#endif

#ifndef Memset
/**
 * Transparently maps the arguments for the system function <tt>memset</tt>
 * or equivalent so it is platform-independent.
 */
#define Memset memset
#endif

#ifndef Memcmp
/**
 * Transparently maps the arguments for the system function <tt>memcmp</tt>
 * or equivalent so it is platform-independent.
 */
#define Memcmp memcmp
#endif

#ifndef Strcmp
/**
 * Transparently maps the arguments for the system function <tt>strcmp</tt>
 * or equivalent so it is platform-independent.
 */
#define Strcmp strcmp
#endif

#ifndef Strncmp
/**
* Transparently maps the arguments for the system function <tt>strncmp</tt>
 * or equivalent so it is platform-independent.
 */
#define Strncmp strncmp
#endif

#ifndef Strlen
/**
 * Transparently maps the arguments for the system function <tt>strlen</tt>
 * or equivalent so it is platform-independent.
 */
#define Strlen strlen
#endif

#ifndef Strcpy
/**
 * Transparently maps the arguments for the system function <tt>strcpy</tt>
 * or equivalent so it is platform-independent.
 */
#define Strcpy strcpy
#endif

#ifndef Strncpy
/**
 * Transparently maps the arguments for the system function <tt>strncpy</tt>
 * or equivalent so it is platform-independent.
 */
#define Strncpy strncpy
#endif

#ifndef Strcat
/**
 * Transparently maps the arguments for the system function <tt>strcat</tt>
 * or equivalent so it is platform-independent.
 */
#define Strcat strcat
#endif

#ifndef Strtok
/**
 * Transparently maps the arguments for the system function <tt>strtok</tt>
 * or equivalent so it is platform-independent.
 */
#define Strtok strtok
#endif

#ifndef Qsort
/**
 * Transparently maps the arguments for the system function <tt>qsort</tt>
 * or equivalent so it is platform-independent.
 */
#define Qsort(a,b,c,d)  \
                qsort((void *)(a),(size_t)(b),(size_t)(c),(d))
#endif

#ifndef Strtol
/**
 * Transparently maps the arguments for the system function <tt>strtol</tt>
 * or equivalent so it is platform-independent.
 */
#define Strtol strtol
#endif

#ifndef Strchr
/**
 * Transparently maps the arguments for the system function <tt>strchr</tt>
 * or equivalent so it is platform-independent.
 */
#define Strchr strchr
#endif

#ifndef Strstr
/**
 * Transparently maps the arguments for the system function <tt>strstr</tt>
 * or equivalent so it is platform-independent.
 */
#define Strstr strstr
#endif

#ifndef Strtoul
/**
 * Transparently maps the arguments for the system function <tt>strtoul</tt>
 * or equivalent so it is platform-independent.
 */
#define Strtoul strtoul
#endif

#ifndef Bsearch
/**
 * Transparently maps the arguments for the system function <tt>bsearch</tt>
 * or equivalent so it is platform-independent.
 */
#define Bsearch(a,b,c,d,e) \
        bsearch((void *)(a),(void *)(b),(size_t)(c),(size_t)(d),(e))
#endif

#ifndef Remove
/**
 * Transparently maps the arguments for the system function <tt>remove</tt>
 * or equivalent so it is platform-independent.
 */
#define Remove remove
#endif

#ifndef Getenv
/**
 * Transparently maps the arguments for the system function <tt>getenv</tt>
 * or equivalent so it is platform-independent.
 */
#define Getenv getenv
#endif

#ifndef Putenv
/**
 * Transparently maps the arguments for the system function <tt>putenv</tt>
 * or equivalent so it is platform-independent.
 */
#define Putenv putenv
#endif



#ifndef Isdigit
#ifndef NO_ISDIGIT
#include <ctype.h>
/**
 * Transparently maps the arguments for the system function <tt>isdigit</tt>
 * or equivalent so it is platform-independent.
 */
#define Isdigit isdigit
#else
#define Isdigit(a) (a >= '0' && a <= '9')
#endif
#endif

#ifndef CCONV
#define CCONV
#endif
 
#ifndef PRE_CCONV
#define PRE_CCONV
#endif


/* Common/shared structure definitions */
/**
 * This structure is used to hold generic data.
 */
typedef struct r_item_st
{
    /**
     * The length of the data array.
     */
    unsigned int len;

    /**
     * The data array.
     */
    unsigned char *data;
} R_ITEM;

/**
 * This structure is used to hold generic data marked with a unique type.
 */
typedef struct r_titem_st
{
    /**
     * The type of the data stored in the array.
     */
    unsigned int type;

    /**
     * The length of the data array.
     */
    unsigned int len;

    /**
     * The data array.
     */
    unsigned char *data;
} R_TITEM;

/* Common/shared string types */

/**
 * 
 * The define for UTF-8 encoded Unicode characters.
 *
 * @note The ASCII character set is a subset of UTF-8.
 */
#define R_UTF8 char *

#include <limits.h>
#if (defined(LONG_BIT) && (LONG_BIT == 32))         || \
    (defined(LONG_MAX) && (LONG_MAX == 2147483647))
/**
 * The define for accurately typing 32-bit integers transparently.
 */
#define R_INT32         long
/**
 * The define for accurately typing 32-bit unsigned integers transparently.
 */
#define R_UINT32        unsigned long

#ifdef WIN32
#define R_INT64         __int64
#define R_UINT64        unsigned __int64
#else
#define R_INT64         long long
#define R_UINT64        unsigned long long
#endif
#elif (defined(LONG_BIT) && (LONG_BIT == 64))         || \
      (defined(LONG_MAX) && (LONG_MAX == 9223372036854775807L))
#define R_INT64         long
#define R_UINT64        unsigned long
#endif
#if  (!defined(R_UINT32)) && \
     ((defined(INT_BIT) && (INT_BIT == 32))        || \
      (defined(INT_MAX) && (INT_MAX == 2147483647)))
#define R_INT32         int
#define R_UINT32        unsigned int
#endif

/**
 * The define for accurately typing 16-bit integers transparently.
 */
#define R_INT16         short
/**
 * The define for accurately typing 16-bit unsigned integers transparently.
 */
#define R_UINT16        unsigned short

#ifndef R_INT32
COMPILE ERROR = Cannot find a 32 bit data type for this platform;
#endif

/* When using the Test Framework the <i>main</i> must be replaced with the
 * Test Framework <i>main</i> which sets up the Test Framework. As r_com.h
 * should be included in all unit tests, system tests, and samples, add
 * platform specific definitions of <i>main</i> here.
 *
 * @note To override TEST_FRAMEWORK use OVERRIDE_TEST_FRAMEWORK. This currently
 * only available on a per file basis as the build system does not support
 * #defines on a per directory basis. The use of this negate all #defines
 * triggered by TEST_FRAMEWORK.
 *
 */

#ifdef TEST_FRAMEWORK
#ifndef OVERRIDE_TEST_FRAMEWORK
#if defined(PLATFORM_SOLARIS) || defined(PLATFORM_LINUX) || \
 (defined(PLATFORM_WINDOWS) && !defined(UNDER_CE)) || defined(PLATFORM_EPOC)
#include "teremote_comms.h"
#include "te_override.h"
#endif /* platform ids */
#endif /* OVERRIDE_TEST_FRAMEWORK */
#endif /* TEST_FRAMEWORK */

#ifdef  __cplusplus
}
#endif

#ifndef EVAL_CHECK_DATE
#define EVAL_CHECK_DATE()
#endif

#endif /* HEADER_COMMON_R_COM_H */

