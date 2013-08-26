/* $Id: r_passwd.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_passwd.h
 * This file contains the prototypes for the password callbacks.
 */

#ifndef HEADER_COMMON_R_PASSWD_H
#define HEADER_COMMON_R_PASSWD_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @defgroup PASSWD_ALL_FUNCS Password Management Functions
 * This section outlines the functions provided for the management of user
 * passwords.
 * @ingroup R_PASSWD_GROUP
 * @{
 */

/**
 * The type of password callback.
 * @param  buf     [In]     The buffer containing the password.
 * @param  length  [In]     The length of the buffer.
 * @param  prompt  [In]     The prompt for the password.
 * @param  verify  [In]     The flag:<br>
 *                          <li>Non-zero indicates the password
 *                          is required.</li>
 *                          <li>Zero indicates otherwise.</li>
 *
 * @see R_passwd_set_cb() and R_passwd_get_cb().
 */
typedef int R_PASSWD_CB_T(char *buf, int length, char *prompt, int verify);

int R_passwd_set_cb(R_PASSWD_CB_T *cb);

int R_passwd_get_cb(R_PASSWD_CB_T **cb);

int R_passwd_get_passwd(char *buf, int length, char *prompt, int verify);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_PASSWD_H */

