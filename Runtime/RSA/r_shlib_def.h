/* $Id: r_shlib_def.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 2001 RSA Security Inc. All rights reserved. This
 * work contains proprietary information of RSA Security Inc. Distribution
 * is limited to authorised licensees of RSA Security Inc. Any unauthorised
 * reproduction or distribution of this work is strictly prohibited. 
 */
 
#ifndef HEADER_COMMON_R_SHLIB_DEF_H
#define HEADER_COMMON_R_SHLIB_DEF_H

#ifdef  __cplusplus
extern "C" {
#endif

#if R_OS == R_OS_WINDOWS || R_OS == R_OS_WINCE

#define EXP_FUNC __declspec(dllexport)
#define IMP_FUNC __declspec(dllimport)

#else /* !R_OS == R_OS_WINDOWS || R_OS == R_OS_WINCE */

#define EXP_FUNC
#define IMP_FUNC

#endif /* R_OS == R_OS_WINDOWS || R_OS == R_OS_WINCE */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SHLIB_DEF_H */

