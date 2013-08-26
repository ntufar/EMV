/* $Id: r_shlibx.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2001 RSA Security Inc. All rights reserved. This
 * work contains proprietary information of RSA Security Inc. Distribution
 * is limited to authorised licensees of RSA Security Inc. Any unauthorised
 * reproduction or distribution of this work is strictly prohibited.
 */

/* from bsource/include/rsashlib.h */

/* 
 * Forward mapping from Crypto-C RSA_LoadLibrary, RSA_GetProcAddress and 
 * RSA_UnLoadLibrary (toolkit/bsource/support/rsashlib.c) to the shared
 * loading interface
 *
 */

#if !defined(_RSASHLIB_H)
#define _RSASHLIB_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef void (*PROC_POINTER)();

POINTER RSA_CALLING_CONV RSA_LoadLibrary(char *libraryName, ITEM *outHandle);
PROC_POINTER RSA_CALLING_CONV RSA_GetProcAddress(ITEM *pLibHandle,
							char *procName); 
UINT4 RSA_CALLING_CONV RSA_UnloadLibrary(ITEM *pLibHandle);

#ifndef NULL
#define NULL 0
#endif

#ifdef  __cplusplus
}
#endif

#endif /* !defined(_RSASHLIB_H) */

