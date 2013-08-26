/* $Id: err.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * @file err.h
 * This file lists definitions and macros used in error value
 * generation. The values in this file are not valid for all
 * RSA BSAFE products, and are supplied for compatibility only in these
 * cases.
 */
#ifndef HEADER_COMMON_ERR_H
#define HEADER_COMMON_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"
#include "r_vararg.h"


/*
 * Macro constants common to all error implementations
 *     (ZERO_ERR,ONE_ERR, standard)
 */


/* Number to represent each logical group of functions (library) */
#define ERR_LIB_NONE        1
#define ERR_LIB_SYS     2
#define ERR_LIB_BN      3
#define ERR_LIB_RSA     4
#define ERR_LIB_DH      5
#define ERR_LIB_EVP     6
#define ERR_LIB_BUF     7
#define ERR_LIB_OBJ     8
#define ERR_LIB_PEM     9
#define ERR_LIB_DSA     10
#define ERR_LIB_X509        11
#define ERR_LIB_METH        12
#define ERR_LIB_ASN1        13
#define ERR_LIB_CONF        14
#define ERR_LIB_CR      15
#define ERR_LIB_SIO     16
#define ERR_LIB_SSL     20
#define ERR_LIB_SSL23       21
#define ERR_LIB_SSL2        22
#define ERR_LIB_SSL3        23
#define ERR_LIB_HMAC        24
#define ERR_LIB_X509TC      25
#define ERR_LIB_SSLCERT     26
#define ERR_LIB_PKEY        27
#define ERR_LIB_R_PEM           28

#define ERR_LIB_RSAREF      30
#define ERR_LIB_PROXY       31
#define ERR_LIB_BIO     32
#define ERR_LIB_PKCS7       33

#define ERR_LIB_WTLSCERT        34
#define ERR_LIB_R_CERT          35
#define ERR_LIB_R_CACHE         36
#define ERR_LIB_R_LOCK          37
#define ERR_LIB_EXDATA          38
#define ERR_LIB_R_HW            39
#define ERR_LIB_SSLC            40
#define ERR_LIB_R_PKEY          41

#define ERR_LIB_USER        128

/* Save the error from a particular library. */
#define SYSerr(f,r)  ERR_PUT_error(ERR_LIB_SYS,(f),(r),ERR_file_name,__LINE__)
#define BNerr(f,r)   ERR_PUT_error(ERR_LIB_BN,(f),(r),ERR_file_name,__LINE__)
#define RSAerr(f,r)  ERR_PUT_error(ERR_LIB_RSA,(f),(r),ERR_file_name,__LINE__)
#define DHerr(f,r)   ERR_PUT_error(ERR_LIB_DH,(f),(r),ERR_file_name,__LINE__)
#define EVPerr(f,r)  ERR_PUT_error(ERR_LIB_EVP,(f),(r),ERR_file_name,__LINE__)
#define BUFerr(f,r)  ERR_PUT_error(ERR_LIB_BUF,(f),(r),ERR_file_name,__LINE__)
#define BIOerr(f,r)  ERR_PUT_error(ERR_LIB_BIO,(f),(r),ERR_file_name,__LINE__)
#define SIOerr(f,r)  ERR_PUT_error(ERR_LIB_SIO,(f),(r),ERR_file_name,__LINE__)
#define OBJerr(f,r)  ERR_PUT_error(ERR_LIB_OBJ,(f),(r),ERR_file_name,__LINE__)
#define PEMerr(f,r)  ERR_PUT_error(ERR_LIB_PEM,(f),(r),ERR_file_name,__LINE__)
#define DSAerr(f,r)  ERR_PUT_error(ERR_LIB_DSA,(f),(r),ERR_file_name,__LINE__)
#define X509err(f,r) ERR_PUT_error(ERR_LIB_X509,(f),(r),ERR_file_name,__LINE__)
#define METHerr(f,r) ERR_PUT_error(ERR_LIB_METH,(f),(r),ERR_file_name,__LINE__)
#define ASN1err(f,r) ERR_PUT_error(ERR_LIB_ASN1,(f),(r),ERR_file_name,__LINE__)
#define CONFerr(f,r) ERR_PUT_error(ERR_LIB_CONF,(f),(r),ERR_file_name,__LINE__)
#define CRerr(f,r) ERR_PUT_error(ERR_LIB_CR,(f),(r),ERR_file_name,__LINE__)
#define SSLerr(f,r)  ERR_PUT_error(ERR_LIB_SSL,(f),(r),ERR_file_name,__LINE__)
#define SSL23err(f,r) ERR_PUT_error(ERR_LIB_SSL23,(f),(r),ERR_file_name,__LINE__)
#define SSL2err(f,r) ERR_PUT_error(ERR_LIB_SSL2,(f),(r),ERR_file_name,__LINE__)
#define SSL3err(f,r) ERR_PUT_error(ERR_LIB_SSL3,(f),(r),ERR_file_name,__LINE__)
#define RSAREFerr(f,r) ERR_PUT_error(ERR_LIB_RSAREF,(f),(r),ERR_file_name,__LINE__)
#define PROXYerr(f,r) ERR_PUT_error(ERR_LIB_PROXY,(f),(r),ERR_file_name,__LINE__)
#define PKCS7err(f,r) ERR_PUT_error(ERR_LIB_PKCS7,(f),(r),ERR_file_name,__LINE__)
#define HMACerr(f,r) ERR_PUT_error(ERR_LIB_HMAC,(f),(r),ERR_file_name,__LINE__)
#define X509TCerr(f,r) ERR_PUT_error(ERR_LIB_X509TC,(f),(r),ERR_file_name,__LINE__)
#define SSLCERTerr(f,r) ERR_PUT_error(ERR_LIB_SSLCERT,(f),(r),ERR_file_name,__LINE__)
#define PKEYerr(f,r) ERR_PUT_error(ERR_LIB_PKEY,(f),(r),ERR_file_name,__LINE__)
#define WTLSCERTerr(f,r) ERR_PUT_error(ERR_LIB_WTLSCERT,(f),(r),ERR_file_name,__LINE__)
#define R_CERTerr(f,r) ERR_PUT_error(ERR_LIB_R_CERT,(f),(r),ERR_file_name,__LINE__)
#define R_PKEYerr(f,r) ERR_PUT_error(ERR_LIB_R_PKEY,(f),(r),ERR_file_name,__LINE__)
#define CACHEerr(f,r) ERR_PUT_error(ERR_LIB_R_CACHE,(f),(r),ERR_file_name,__LINE__)
#define LOCKerr(f,r) ERR_PUT_error(ERR_LIB_R_LOCK,(f),(r),ERR_file_name,__LINE__)
#define EXDATAerr(f,r) ERR_PUT_error(ERR_LIB_EXDATA,(f),(r),ERR_file_name,__LINE__)
#define R_HWerr(f,r) ERR_PUT_error(ERR_LIB_R_HW,(f),(r),ERR_file_name,__LINE__)
#define SSLCerr(f,r)  ERR_PUT_error(ERR_LIB_SSLC,(f),(r),ERR_file_name,__LINE__)

/* The explicit casting and type definition helps some compilers with
 *  preserving type information in shifts
 */
#define ERR_PACK(l,f,r)     (((((unsigned long)l)&0xffL)*0x1000000)| \
                ((((unsigned long)f)&0xfffL)*0x1000)| \
                ((((unsigned long)r)&0xfffL)))
#define ERR_GET_LIB(l)      (int)((((unsigned long)l)>>24L)&0xffL)
#define ERR_GET_FUNC(l)     (int)((((unsigned long)l)>>12L)&0xfffL)
#define ERR_GET_REASON(l)   (int)((l)&0xfffL)
#define ERR_FATAL_ERROR(l)  (int)((l)&ERR_R_FATAL)

/* OS functions - SYS errors have their function list maintained here */
#define SYS_F_FOPEN     1
#define SYS_F_CONNECT       2
#define SYS_F_GETSERVBYNAME 3
#define SYS_F_SOCKET        4
#define SYS_F_IOCTLSOCKET   5
#define SYS_F_BIND      6
#define SYS_F_LISTEN        7
#define SYS_F_ACCEPT        8
#define SYS_F_WSASTARTUP    9   /* For Winsock */
#define SYS_F_SYSLIBFIND    10  /* For PalmOS */
#define SYS_F_NETLIBIFGET   11  /* For PalmOS */
#define SYS_F_NETLIBOPEN    12  /* For PalmOS */

#define ERR_R_FATAL     32
/* reasons */
#define ERR_R_SYS_LIB   (ERR_LIB_SYS+0x0800)
#define ERR_R_BN_LIB    (ERR_LIB_BN+0x0800)
#define ERR_R_RSA_LIB   (ERR_LIB_RSA+0x0800)
#define ERR_R_DSA_LIB   (ERR_LIB_DSA+0x0800)
#define ERR_R_DH_LIB    (ERR_LIB_DH+0x0800)
#define ERR_R_EVP_LIB   (ERR_LIB_EVP+0x0800)
#define ERR_R_BUF_LIB   (ERR_LIB_BUF+0x0800)
#define ERR_R_BIO_LIB   (ERR_LIB_BIO+0x0800)
#define ERR_R_OBJ_LIB   (ERR_LIB_OBJ+0x0800)
#define ERR_R_PEM_LIB   (ERR_LIB_PEM+0x0800)
#define ERR_R_X509_LIB  (ERR_LIB_X509+0x0800)
#define ERR_R_METH_LIB  (ERR_LIB_METH+0x0800)
#define ERR_R_ASN1_LIB  (ERR_LIB_ASN1+0x0800)
#define ERR_R_CONF_LIB  (ERR_LIB_CONF+0x0800)
#define ERR_R_CR_LIB    (ERR_LIB_CR+0x0800)
#define ERR_R_SSL_LIB   (ERR_LIB_SSL+0x0800)
#define ERR_R_SSL23_LIB (ERR_LIB_SSL23+0x0800)
#define ERR_R_SSL2_LIB  (ERR_LIB_SSL2+0x0800)
#define ERR_R_SSL3_LIB  (ERR_LIB_SSL3+0x0800)
#define ERR_R_PROXY_LIB (ERR_LIB_PROXY+0x0800)
#define ERR_R_BIO_LIB   (ERR_LIB_BIO+0x0800)
#define ERR_R_PKCS7_LIB (ERR_LIB_PKCS7+0x0800)
#define ERR_R_HMAC_LIB  (ERR_LIB_HMAC+0x0800)
#define ERR_R_SIO_LIB   (ERR_LIB_SIO+0x0800)
#define ERR_R_X509TC_LIB    (ERR_LIB_X509TC+0x0800)
#define ERR_R_SSLCERT_LIB   (ERR_LIB_SSLCERT+0x0800)
#define ERR_R_PKEY_LIB  (ERR_LIB_PKEY+0x0800)
#define ERR_R_WTLSCERT_LIB  (ERR_LIB_PKEY+0x0800)

/* fatal error - strings in err.c for this table */
#define ERR_R_MALLOC_FAILURE            (1|ERR_R_FATAL)
#define ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED   (2|ERR_R_FATAL)
#define ERR_R_PASSED_NULL_PARAMETER     (3|ERR_R_FATAL)
#define ERR_R_GENERAL_FAILURE                   (4|ERR_R_FATAL)

/* A different class of error messages */
#define ERR_R_NESTED_ASN1_ERROR         (4)
#define ERR_R_BAD_ASN1_OBJECT_HEADER        (5)
#define ERR_R_BAD_GET_ASN1_OBJECT_CALL      (6)
#define ERR_R_EXPECTING_AN_ASN1_SEQUENCE    (7)
#define ERR_R_ASN1_LENGTH_MISMATCH      (8)
#define ERR_R_MISSING_ASN1_EOS          (9)

#define ERR_R_FATAL_INTERNAL_ERROR      (10|ERR_R_FATAL)
#define ERR_R_EVAL_RESTRICTION          (11|ERR_R_FATAL)
#define ERR_R_EVAL_EXPIRED          (12|ERR_R_FATAL)
#define ERR_R_INIT_NOT_CALLED           (13|ERR_R_FATAL)
#define ERR_R_NOT_SUPPORTED         (14)
#define ERR_R_SHOULD_RETRY          (15)
#define ERR_R_BUFFER_TOO_SMALL          (16)

/*
 * The error implementation has 3 variations ZERO_ERR,ONE_ERR and the standard
 */
#ifdef ONE_ERR

/* 
 * Stores library,function and reason codes and ignores file name and 
 * line numbers. 
 */
#define ERR_PUT_error(a,b,c,d,e)    ERR_put_error(a,b,c,NULL,0)
/** A macro defined as nothing in order to remove the function altogether. */
#define ERR_free_strings()
/** A macro to clear the stored error buffer */
#define ERR_remove_state(pid)           ERR_clear_error()
/** A macro defined as nothing in order to remove the function altogether. */
#define ERR_get_state()
/* 
 * Stores library,function and reason codes and ignores file name and 
 * line numbers. 
 */
#define ERR_put_error(lib,func,reason,file,line) \
                                err_one_err_buffer=ERR_PACK(lib,func,reason)
/** A macro to clear the stored error buffer. */
#define ERR_clear_error() err_one_err_buffer=0
/** A macro to return then clear the stored packed error code. */
#define ERR_get_error() \
    (err_one_err_last=err_one_err_buffer,err_one_err_buffer=0, \
     err_one_err_last)
/** A macro to return the stored packed error code. */
#define ERR_peek_error() err_one_err_buffer
/** A macro to print the current error code to the given
 *  file pointer. */
#define ERR_print_errors_fp(fp) \
   fprintf(fp,"%lu:%lu:NA:0: \n",CRYPTO_thread_id(),ERR_get_error());
/** A macro to print the current error code to the given BIO. */
#define ERR_print_errors(bp) { \
        char buf2[45]; \
        sprintf(buf2,"%lu:%lu:NA:0:\n",CRYPTO_thread_id(),ERR_get_error()); \
        BIO_write(bp,buf2,(int)Strlen(buf2)); \
        }


/* Declaration for ONE_ERR specific variable to replace the error hash */
/* ONE_ERR - only stores the buffer for the current error */
extern unsigned long err_one_err_buffer;
/* ONE_ERR - declare a variable here to be used in a macro to save having to
 *  introduce a scope in the macro */
extern unsigned long err_one_err_last;


/*****************************************************************/

/* !ONE_ERR */
#elif defined (ZERO_ERR)


/* Flags to indicate err_data field of err_state_st needs 
 * to be freed or not */
#define ERR_TXT_MALLOCED    0x01
#define ERR_TXT_STRING      0x02
/* Number of error elements for each thread */
#define ERR_NUM_ERRORS  16

/**
 * The error state structure. An opaque structure that holds all error
 * information for a single thread. Each execution thread maintains its own
 * error state using this structure.
 */
typedef struct err_state_st ERR_STATE;

/* Structure to hold the corresponding error string information
 *  for an error code */
typedef struct ERR_string_data_st
    {
    unsigned long error;
    char *string;
    } ERR_STRING_DATA;


/** A macro defined as nothing in order to remove the function altogether. */
#define ERR_PUT_error(a,b,c,d,e)
/** A macro defined as nothing in order to remove the function altogether. */
#define ERR_get_error()

/* Prototypes for functions from err.c source file */
#ifdef HEADER_COMMON_LHASH_H
LHASH *ERR_get_string_table(void );
LHASH *ERR_get_err_state_table(void );
#else
char *ERR_get_string_table(void );
char *ERR_get_err_state_table(void );
#endif /* HEADER_COMMON_LHASH_H */

void ERR_load_ERR_strings(void);
void ERR_load_strings(int lib,ERR_STRING_DATA str[]);
void ERR_free_strings(void);
void ERR_remove_state(unsigned long pid);
ERR_STATE *ERR_get_state(void);
void ERR_put_error(int lib, int func,int reason,char *file,int line);
void ERR_clear_error(void);
unsigned long ERR_peek_error(void);
unsigned long ERR_get_error_line(char **file,int *line);
unsigned long ERR_peek_error_line(char **file,int *line);
unsigned long ERR_peek_error_line_data(char **file,int *line,
                                       char **data,int *flags);
void ERR_set_error_data(char *data,int flags);
unsigned long ERR_get_error_line_data(char **file,int *line,
                                      char **data, int *flags);
char *ERR_error_string(unsigned long error_code,char *buf);
char *ERR_lib_error_string(unsigned long error_code);
char *ERR_func_error_string(unsigned long error_code);
char *ERR_reason_error_string(unsigned long error_code);
int ERR_get_next_error_library(void);

/* Prototypes for functions from err_prn.c source file */
#ifndef NO_FP_API
void ERR_print_errors_fp(FILE *fp);
#endif /* !NO_FP_API */
#ifdef HEADER_COMMON_BIO_H
void ERR_print_errors(BIO *bio);
#endif /* HEADER_COMMON_BIO_H */

/*****************************************************************/

#else  /* !ONE_ERR && !ZERO_ERR */

/* Flags to indicate err_data field of err_state_st needs 
 * to be freed or not */
#define ERR_TXT_MALLOCED    0x01
#define ERR_TXT_STRING      0x02
/* Number of error elements for each thread */
#define ERR_NUM_ERRORS  16

/** 
 * Indicates the file name of the current file. 
 */
#define ERR_file_name   __FILE__

/* Structure to hold all error information for each thread */
typedef struct err_state_st ERR_STATE;
/* Structure to hold the corresponding error string information
 *  for an error code */
/* Structure to hold the corresponding error string information
 *  for an error code */
typedef struct ERR_string_data_st
    {
    unsigned long error;
    char *string;
    } ERR_STRING_DATA;


#ifdef NO_ERR
/* 
 * Stores library,function and reason codes and ignores file name and 
 * line numbers. 
 */
#define ERR_PUT_error(a,b,c,d,e)    ERR_put_error(a,b,c,NULL,0)
#else  /* !NO_ERR */
/* 
 * Stores library,function and reason codes and ignores file name and 
 * line numbers. 
 */
#define ERR_PUT_error(a,b,c,d,e)    ERR_put_error(a,b,c,d,e)
#endif /* !NO_ERR */

/**
 * @defgroup COMMON_ERROR_FUNCS Error Reporting Functions
 *
 * This section includes functions that can be used to obtain
 * information from the library about errors that occurred during
 * operations.
 *
 * @{
 */
/* Prototypes for functions from err.c source file */
#ifdef HEADER_COMMON_LHASH_H
LHASH *ERR_get_string_table(void );
LHASH *ERR_get_err_state_table(void );
#else
char *ERR_get_string_table(void );
char *ERR_get_err_state_table(void );
#endif /* HEADER_COMMON_LHASH_H */
void ERR_load_ERR_strings(void);
void ERR_load_strings(int lib,ERR_STRING_DATA str[]);
void ERR_free_strings(void);
void ERR_remove_state(unsigned long pid);
ERR_STATE *ERR_get_state(void);
void ERR_put_error(int lib, int func,int reason,char *file,int line);
void ERR_clear_error(void);
unsigned long ERR_get_error(void);
unsigned long ERR_peek_error(void );
unsigned long ERR_get_error_line(char **file,int *line);
unsigned long ERR_peek_error_line(char **file,int *line);
unsigned long ERR_peek_error_line_data(char **file,int *line,
                                       char **data,int *flags);
void ERR_set_error_data(char *data,int flags);
unsigned long ERR_get_error_line_data(char **file,int *line,
                                      char **data, int *flags);
char *ERR_error_string(unsigned long error_code,char *buf);
char *ERR_lib_error_string(unsigned long error_code);
char *ERR_func_error_string(unsigned long error_code);
char *ERR_reason_error_string(unsigned long error_code);
int ERR_get_next_error_library(void );
void ERR_add_error_data( VAR_PLIST( int, num ) );

/* Prototypes for functions from err_prn.c source file */
#ifndef NO_FP_API
void ERR_print_errors_fp(FILE *fp);
#endif /* !NO_FP_API */
#if defined(HEADER_COMMON_BIO_H) || defined(DOXYGEN)
void ERR_print_errors(BIO *bio);
#endif /* HEADER_COMMON_BIO_H || DOXYGEN */

/* end group COMMON_ERROR_FUNCS */
/**
 * @}
 */

#endif /* !ONE_ERR && !ZERO_ERR */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_ERR_H */
