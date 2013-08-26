/* $Id: r_memlk.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

#ifndef HEADER_COMMON_R_MEMLK_H
#define HEADER_COMMON_R_MEMLK_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "bio.h"


#define R_MEM_DBG_TRACE_CB_LOCATION_MALLOC 	1
#define R_MEM_DBG_TRACE_CB_LOCATION_REALLOC 	2
#define R_MEM_DBG_TRACE_CB_LOCATION_FREE 	3

typedef void R_MEM_DBG_LEAKS_CB_T(unsigned long order, char *file, 
				  int line, int num_bytes, char *addr);

typedef void R_MEM_DBG_TRACE_CB_T(int location, unsigned long order, 
				  char *file, int line, int num_bytes, 
				  char *addr, unsigned char *cb_arg);

void R_mem_dbg_leaks(BIO *bio);
void R_mem_dbg_leaks_cb(R_MEM_DBG_LEAKS_CB_T *cb);
void R_mem_dbg_set_trace_cb(R_MEM_DBG_TRACE_CB_T *cb,unsigned char *cb_arg);
void R_mem_dbg_set_failure(unsigned long alloc_count);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_MEMLK_H */

