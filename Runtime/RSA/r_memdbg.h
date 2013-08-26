/* $Id: r_memdbg.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

#ifndef HEADER_COMMON_R_MEMDBG_H
#define HEADER_COMMON_R_MEMDBG_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_mem.h"

typedef struct r_mem_dbg_stats_st
	{
	long malloc_count;	/* number of mallocs performed */
	long free_count;	/* number of frees performed */
	long free_miss;		/* number of frees that went wrong */
	long mem_user;		/* current amount of memory used */
	long mem_max;		/* maximum amount of memory used */
	long mem_total;		/* total amount of memory */
	} R_MEM_DBG_STATS;

/* CRYPTO compatibility macros */
#define CRYPTO_dbg_remalloc		R_remalloc_dbg
#define CRYPTO_dbg_malloc		R_malloc_dbg
#define CRYPTO_dbg_realloc		R_realloc_dbg
#define CRYPTO_dbg_free			R_free_dbg
#define CRYPTO_mem_ctrl                 R_mem_ctrl

#define CRYPTO_mem_leaks		R_mem_dbg_leaks
#define CRYPTO_mem_leaks_cb		R_mem_dbg_leaks_cb

#define CRYPTO_MEM_CHECK OFF		R_MEM_CHECK_OFF
#define CRYPTO_MEM_CHECK_ON		R_MEM_CHECK_ON
#define CRYPTO_MEM_CHECK_ENABLE		R_MEM_CHECK_ENABLE
#define CRYPTO_MEM_CHECK_DISABLE	R_MEM_CHECK_DISABLE


/* The following can be used to detect memory leaks in libraries and report
 * information about where the memory was allocated if compiled with 
 * R_MDEBUG
 */
#define R_MEM_CHECK_OFF     0x0	/* an enum */
#define R_MEM_CHECK_ON      0x1	/* a bit */
#define R_MEM_CHECK_ENABLE  0x2	/* a bit */
#define R_MEM_CHECK_DISABLE 0x3	/* an enum */
#define R_MEM_GET_MH_MODE   0x8	/* get current flag */

/* macros to control the behaviour of the memory debug routines
 *
 * Typically you call R_mem_dbg_begin() to enable checking and
 * to switch checking on - enabled and on are separate concepts.
 */
#define R_mem_dbg_start() 	R_mem_ctrl(R_MEM_CHECK_ON)
#define R_mem_dbg_stop()	R_mem_ctrl(R_MEM_CHECK_OFF)
#define R_mem_dbg_on()	 	R_mem_ctrl(R_MEM_CHECK_ENABLE)
#define R_mem_dbg_off()	 	R_mem_ctrl(R_MEM_CHECK_DISABLE)
#define R_mem_dbg_begin() 	{ R_mem_ctrl(R_MEM_CHECK_ON); \
                            	  R_mem_ctrl(R_MEM_CHECK_ENABLE); }
#define R_mem_dbg_get_mh_mode()	R_mem_ctrl(R_MEM_GET_MH_MODE)

#define R_mem_dbg_is_on()	(R_mem_ctrl(R_MEM_GET_MH_MODE)&\
						R_MEM_CHECK_ENABLE)

#ifdef R_MDEBUG

/* compatibility macros for the old names */
#define MemCheck_start() 	R_mem_dbg_start()
#define MemCheck_stop()	 	R_mem_dbg_stop()
#define MemCheck_on()	 	R_mem_dbg_on()
#define MemCheck_off()	 	R_mem_dbg_off()
#define MemCheck_begin() 	R_mem_dbg_begin()
#define Mem_get_mh_mode()	R_mem_dbg_get_mh_mode()

#define Malloc(num)	R_malloc_dbg((size_t)num,__FILE__,__LINE__)
#define Realloc(addr,new_num,old_num) \
	R_realloc_dbg((char *)addr,(size_t)new_num,\
	                    (size_t)old_num,__FILE__,__LINE__)
#define Remalloc(addr,num) \
	R_remalloc_dbg((char **)addr,(size_t)num,__FILE__,__LINE__)
#define FreeFunc	R_free_dbg
#define Free(addr)	R_free_dbg((char *)(addr))


#include "r_memlk.h"

#endif /* R_MDEBUG */

char *R_malloc_dbg(size_t num,char *file,int line);
char *R_realloc_dbg(char *addr,size_t num_new,size_t num_old,
                                            char *file,int line);
void  R_free_dbg(char *addr);
char *R_remalloc_dbg(char *addr,size_t num,char *file,int line);


R_MEM_DBG_STATS *R_mem_dbg_stats(void);
long  	         R_mem_dbg_mem_max(void);
long         	 R_mem_dbg_mem_in_use(void);
 
char *R_malloc_dbg_wrap(size_t num);
char *R_realloc_dbg_wrap(char *addr,size_t num_new,size_t num_old);

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_MEMDBG_H */

