/* $Id: r_prod.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_prod.h
 * This file contains the product library defines and includes.
 */

#ifndef HEADER_COMMON_R_PROD_H
#define HEADER_COMMON_R_PROD_H

#ifdef  __cplusplus
extern "C" {
#endif

/* include the appropriate product header file */
#ifdef RCRYPTO
#include "rcrypto.h"
#endif /* RCRYPTO */
#ifdef SSLCME
#include "sslcme.h"
#endif /* SSLCME */
#ifdef SSLC
#include "sslc.h"
#endif /* SSLC */
#ifdef BBANDC
#include "bbandc.h"
#endif
#ifdef CERTC_ME
#include "certcme.h"
#endif
#ifdef CRYPTOC_ME
#include "cryptocme.h"
#endif
#ifdef WLCORE
#include "wlcorec.h"
#endif
#ifdef WTLSC
#include "wtlsc.h"
#endif

#ifdef RCOM

#include "r_com.h"
#include "r_lib.h"
#include "r_res.h"
#include "bio.h"
#include "cryp_mod.h"

R_RES_LIST *RCOM_get_default_resource_list(void);

#ifndef PRODUCT_LIBRARY_NEW
#define PRODUCT_LIBRARY_NEW               R_LIB_CTX_new
#endif
#ifndef PRODUCT_LIBRARY_FREE
#define PRODUCT_LIBRARY_FREE              R_LIB_CTX_free
#endif
#ifndef PRODUCT_DEFAULT_RESOURCE_LIST
#define PRODUCT_DEFAULT_RESOURCE_LIST     RCOM_get_default_resource_list
#endif

#ifndef PRODUCT_CERT_TYPE_FROM_STRING
#define PRODUCT_CERT_TYPE_FROM_STRING     R_CERT_STORE_certtype_from_string
#endif
#ifndef PRODUCT_CERT_TYPE_TO_STRING
#define PRODUCT_CERT_TYPE_TO_STRING       R_CERT_STORE_certtype_to_string
#endif

#endif

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_PROD_H */

