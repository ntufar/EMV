/* $Id: r_error.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_error.h
 * This file contains the error definitions for the toolkit.
 */
#ifndef HEADER_COMMON_R_ERROR_H
#define HEADER_COMMON_R_ERROR_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @defgroup R_ERROR_IDS Error Identifiers
 * This section outlines the error codes returned, enabling identification of
 * specific errors.
 * @ingroup CME_ERR
 *
 * @{
 */
/**
 * Indicates that a fatal error has occurred in the operation performed.
 * This flag is set with the following error codes:<br>
 * <ul>
 * <li>#R_ERROR_INVALID_STATE.</li>
 * <li>#R_ERROR_INIT_NOT_CALLED.</li>
 * <li>#R_ERROR_SHOULD_NOT_HAVE_BEEN_CALLED.</li>
 * </ul>
 */
#define R_ERROR_FATAL_INTERNAL_ERROR    64

/*
 * Indicates that the specified parameter is incorrect or contains invalid
 * information. This flag is set with the following error codes:<br>
 * <ul>
 * <li>#R_ERROR_NULL_ARG.</li>
 * <li>#R_ERROR_BUFFER_TOO_SMALL.</li>
 * <li>#R_ERROR_BAD_VALUE.</li>
 * <li>#R_ERROR_BAD_RANGE.</li>
 * <li>#R_ERROR_BAD_FORMAT.</li>
 * <li>#R_ERROR_BAD_TYPE.</li>
 * <li>#R_ERROR_BAD_DATA.</li>
 * <li>#R_ERROR_BAD_LENGTH.</li>
 * </ul>
 */
#define R_ERROR_BAD_PARAMETER       32

/* Indicates the base value for all general errors used through all products */
#define R_ERROR_BASE            10000

/**
 * Indicates that no errors were detected in the requested operation.
 */
#define R_ERROR_NONE            0

/**
 * Indicates that the requested operation failed.
 */
#define R_ERROR_FAILED          (R_ERROR_BASE+1)
/**
 * Indicates that the requested operation detected an Input/Output error.
 */
#define R_ERROR_IO          (R_ERROR_BASE+2)
/**
 * Indicates that the requested operation detected a protocol error.
 */
#define R_ERROR_PROTOCOL        (R_ERROR_BASE+3)
/**
 * Indicates that the requested operation detected an End-of-File (EOF) error.
 */
#define R_ERROR_EOF         (R_ERROR_BASE+4)
/**
 * Indicates that the requested operation failed in a memory allocation
 * operation.
 */
#define R_ERROR_ALLOC_FAILURE       (R_ERROR_BASE+5)
/**
 * Indicates that the requested operation is restricted in an evaluation
 * version of the library.
 */
#define R_ERROR_EVAL_RESTRICTION    (R_ERROR_BASE+6)
/**
 * Indicates that the evaluation period of the library has expired.
 */
#define R_ERROR_EVAL_EXPIRED        (R_ERROR_BASE+7)
/**
 * Indicates that the requested operation detected that a pre-requirement was
 * not found.
 */
#define R_ERROR_NOT_FOUND       (R_ERROR_BASE+8)
/**
 * Indicates that the requested operation detected that a pre-requirement was
 * unavailable.
 */
#define R_ERROR_NOT_AVAILABLE       (R_ERROR_BASE+9)
/**
 * Indicates that the requested operation is not implemented in the current
 * instantiation of the library.
 */
#define R_ERROR_NOT_IMPLEMENTED     (R_ERROR_BASE+10)
/**
 * Indicates that the requested operation is not supported in the current
 * instantiation of the library.
 */
#define R_ERROR_NOT_SUPPORTED       (R_ERROR_BASE+11)
/**
 * Indicates that the requested operation entered an invalid state.
 */
#define R_ERROR_INVALID_STATE           \
            ((R_ERROR_BASE+12) | R_ERROR_FATAL_INTERNAL_ERROR)
/**
 * Indicates that the requested operation detected that an initialization
 * operation has not been performed.
 */
#define R_ERROR_INIT_NOT_CALLED         \
            ((R_ERROR_BASE+13) | R_ERROR_FATAL_INTERNAL_ERROR)
/**
 * Indicates that the requested operation should not have been called.
 */
#define R_ERROR_SHOULD_NOT_HAVE_BEEN_CALLED \
            ((R_ERROR_BASE+14) | R_ERROR_FATAL_INTERNAL_ERROR)
/**
 * Indicates that the requested method is not defined.
 */
#define R_ERROR_METHOD_UNDEFINED        \
            ((R_ERROR_BASE+15) | R_ERROR_FATAL_INTERNAL_ERROR)
/**
 * Indicates that the requested operation detected an inadequately sized
 * buffer.
 */
#define R_ERROR_BUFFER_TOO_SMALL        \
            ((R_ERROR_BASE+16) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * was passed as <tt>NULL</tt>.
 */
#define R_ERROR_NULL_ARG    ((R_ERROR_BASE+17) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed contained a bad or incorrect value.
 */
#define R_ERROR_BAD_VALUE   ((R_ERROR_BASE+18) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed was out of the allowed range.
 */
#define R_ERROR_BAD_RANGE   ((R_ERROR_BASE+19) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed used a format that is not supported or incorrect.
 */
#define R_ERROR_BAD_FORMAT  ((R_ERROR_BASE+20) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed used a type that is not supported or incorrect.
 */
#define R_ERROR_BAD_TYPE    ((R_ERROR_BASE+21) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed contained incorrect or invalid data.
 */
#define R_ERROR_BAD_DATA    ((R_ERROR_BASE+22) | R_ERROR_BAD_PARAMETER)
/**
 * Indicates that the requested operation detected that a required argument
 * passed contained an incorrect length value.
 */
#define R_ERROR_BAD_LENGTH  ((R_ERROR_BASE+23) | R_ERROR_BAD_PARAMETER)
/*
 * Indicates that the library instantiation requested is not supported.
 */
#define R_ERROR_RCOM_LIBRARY_NOT_SUPPORTED (R_ERROR_BASE+24)
/**
 * Indicates that the request operation was denied.
 */
#define R_ERROR_DENIED      (R_ERROR_BASE+25)
/**
 * Indicates that authentication is required before the operation
 * can succeed.
 */
#define R_ERROR_AUTHENTICATION_REQUIRED      (R_ERROR_BASE+26)

/**
 * Indicates that a required module was unable to be loaded.
 */
#define R_ERROR_MODULE_LOAD_FAILED \
			((R_ERROR_BASE+27)|R_ERROR_FATAL_INTERNAL_ERROR)

/* Resource Manager base for errors */
#define R_COM_ERR_LIB_CTX_BASE      10100

/**
 * @}
 */

/**
 * @fn Convert an R_ERROR to an exit code
 */
#define R_ERROR_EXIT_CODE(ret)   \
     ((ret) == R_ERROR_NONE) ? 0 : 1

#ifdef  __cplusplus
}
#endif
#endif  /* HEADER_COMMON_R_ERROR_H */




