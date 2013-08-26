/* $Id: r_pswd_mth.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file contains structures, defines and function prototypes for
 * the password operations that relate to resource lists.
 */

#ifndef HEADER_COMMON_R_PSWD_MTH_H
#define HEADER_COMMON_R_PSWD_MTH_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @defgroup R_PASSWD_GROUP Password Management
 * This section details the options available that facilitate the 
 * password functionality.
 * @{
 */
/**
 * @}
 */

#ifndef HEADER_COMMON_R_PASSWD_METHOD_TYPEDEF_DEF
#define HEADER_COMMON_R_PASSWD_METHOD_TYPEDEF_DEF
typedef struct r_passwd_method_st                       R_PASSWD_METHOD;
#endif /* HEADER_COMMON_R_PASSWD_METHOD_TYPEDEF_DEF */

R_PASSWD_METHOD *R_PASSWD_get_default_method(void *impl_data);

/**
 * @defgroup PASSWD_RES Password Resource Definitions
 * This section details the definition used in the resource list and
 * initialization of the library. For more information, 
 * see @ref RES_LIST_GROUP.
 * @ingroup R_PASSWD_GROUP
 *
 * @{
 */

/**
 * The full <tt>#R_PASSWD</tt> interface which is required if encrypted
 * Privacy Enhanced Mail (PEM) messages are to be handled.
 */
#define R_PASSWD_RES_DEFAULT                                        \
    { R_RES_MOD_ID_PASSWD, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,     \
      R_RES_FLAG_DEF, NULL, NULL,                                   \
      (void *(*)(void *))R_PASSWD_get_default_method, NULL }

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_PSWD_MTH_H */

