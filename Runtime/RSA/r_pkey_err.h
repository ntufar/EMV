/* $Id: r_pkey_err.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

#ifndef HEADER_COMMON_R_PKEY_ERR_H
#define HEADER_COMMON_R_PKEY_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

/* BEGIN ERROR CODES */
/* Error codes for the R_PKEY functions. */

/* Function codes. */
#define R_PKEY_F_PKEY_CMP                                100
#define R_PKEY_F_PKEY_COPY                               101
#define R_PKEY_F_PKEY_CTX_FREE                           102
#define R_PKEY_F_PKEY_CTX_GET_INFO                       103
#define R_PKEY_F_PKEY_CTX_SET_INFO                       104
#define R_PKEY_F_PKEY_FREE                               105
#define R_PKEY_F_PKEY_FROM_BINARY                        106
#define R_PKEY_F_PKEY_FROM_PUBKEY_BINARY                 107
#define R_PKEY_F_PKEY_GET_INFO                           108
#define R_PKEY_F_PKEY_ITERATE_FIELDS                     109
#define R_PKEY_F_PKEY_NEW                                110
#define R_PKEY_F_PKEY_PRINT                              111
#define R_PKEY_F_PKEY_PUBLIC_CMP                         112
#define R_PKEY_F_PKEY_SET_INFO                           113
#define R_PKEY_F_PKEY_SIGNHASH                           114
#define R_PKEY_F_PKEY_TO_BINARY                          115
#define R_PKEY_F_PKEY_TO_PUBKEY_BINARY                   116
#define R_PKEY_F_PKEY_VERIFYHASH                         117
#define R_PKEY_F_REFERENCE_INC                           118

/* Reason codes. */
/* No R_PKEY unique reason codes have been created yet. */
 
#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_PKEY_ERR_H */

