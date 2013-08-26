/* $Id: bio_err.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * The contents of this file are automatically generated. DO NOT DOXYGENATE.
 */

#ifndef HEADER_COMMON_BIO_ERR_H
#define HEADER_COMMON_BIO_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

/* BEGIN ERROR CODES */
/* Error codes for the BIO functions. */

/* Function codes. */
#define BIO_F_ACPT_STATE				 100
#define BIO_F_BIO_CTRL					 101
#define BIO_F_BIO_GETS					 102
#define BIO_F_BIO_NEW					 103
#define BIO_F_BIO_PUTS					 104
#define BIO_F_BIO_READ					 105
#define BIO_F_BIO_WRITE					 106
#define BIO_F_BUFFER_CTRL				 107
#define BIO_F_CONN_CTRL					 108
#define BIO_F_CONN_STATE				 109
#define BIO_F_FILE_CTRL					 110
#define BIO_F_MEM_WRITE					 111
#define BIO_F_SSL_NEW					 112
#define BIO_F_UDP_ACPT_STATE				 113
#define BIO_F_WSASTARTUP				 114

/* Reason codes. */
#define BIO_R_BAD_FOPEN_MODE				 100
#define BIO_R_ERROR_SETTING_NBIO_ON_ACCEPTED_SOCKET	 101
#define BIO_R_ERROR_SETTING_NBIO_ON_ACCEPT_SOCKET	 102
#define BIO_R_ERROR_SETTING_NBIO_ON_UDP_ACCEPT_SOCKET	 103
#define BIO_R_KEEPALIVE					 104
#define BIO_R_NBIO_CONNECT_ERROR			 105
#define BIO_R_NO_ACCEPT_PORT_SPECIFIED			 106
#define BIO_R_NO_UDP_ACCEPT_PORT_SPECIFIED		 107
#define BIO_R_NULL_PARAMETER				 108
#define BIO_R_UNINITALISED				 109
#define BIO_R_UNSUPPORTED_METHOD			 110
#define BIO_R_WSASTARTUP				 111
 
#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_BIO_ERR_H */

