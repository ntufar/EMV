/* $Id: r_errinf.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_errinf.h
 * This file contains the error structure definitions and function prototypes.
 */
#ifndef HEADER_COMMON_R_ERRINF_H
#define HEADER_COMMON_R_ERRINF_H

#ifdef  __cplusplus
extern "C" {
#endif
/**
 * Captures the filename of the function where the error was
 * generated.
 */
#define R_ERR_INFO_FILE_NAME_INFO               __FILE__
/**
 * Captures the line number in the file where the error was
 * generated.
 */
#define R_ERR_INFO_LINE_INFO                    __LINE__
/**
 * Used when the filename information is not available.
 */
#define R_ERR_INFO_FILE_NOT_AVAILABLE           "NOT AVAILABLE"
/**
 * Used when line number information is not available.
 */
#define R_ERR_INFO_LINE_NOT_AVAILABLE           (-1)

/**
 * Captures the filename of the function where the error was
 * generated.
 */
#define R_ERR_INFO_FILE_NAME                    R_ERR_INFO_FILE_NAME_INFO
/**
 * Captures the line number in the file where the error was
 * generated.
 */
#define R_ERR_INFO_LINE                         R_ERR_INFO_LINE_INFO

/**
 * The data assigned to error object which is to be deallocated by the 
 * error object.
 */
#define R_ERR_INFO_MANAGE_DATA                  0x01
/**
 * Indicates that the data assigned to error object is by reference only.
 */
#define R_ERR_INFO_REFERENCE_DATA               0x02

/**
 * This structure holds all error information
 */
typedef struct r_error_info_st
        {
        int error;
        int reason;
        int detail;
        int function;
        char *file;
        int line;
        char *err_data;
        int flag;
        } R_ERR_INFO;

R_ERR_INFO *R_ERR_INFO_new(void);
int R_ERR_INFO_init(R_ERR_INFO *error);
int R_ERR_INFO_clear(R_ERR_INFO *error);
int R_ERR_INFO_reset(R_ERR_INFO *error);
int R_ERR_INFO_free(R_ERR_INFO *error);

int R_ERR_INFO_log_error(R_ERR_INFO *error, int code, int reason, int detail,
        int function, char *file, int line);
int R_ERR_INFO_log_error_data(R_ERR_INFO *error, char *err_data, int flag);

int R_ERR_INFO_get_error(R_ERR_INFO *error);
int R_ERR_INFO_get_reason(R_ERR_INFO *error);
int R_ERR_INFO_get_detail(R_ERR_INFO *error);
int R_ERR_INFO_get_function(R_ERR_INFO *error);
int R_ERR_INFO_get_line(R_ERR_INFO *error);
char *R_ERR_INFO_get_file(R_ERR_INFO *error);


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_ERRINF_H */

