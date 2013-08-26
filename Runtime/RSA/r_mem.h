/* $Id: r_mem.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_mem.h
 * This file contains information on the portable memory management functions.
 */
#ifndef HEADER_COMMON_R_MEM_H
#define HEADER_COMMON_R_MEM_H

#ifdef  __cplusplus
extern "C" {
#endif

/* The Tornado 2 environment already has a define for Free.
 * So we discard their definition so our own definition can be used.
 */
#if defined(VXWORKS)
#if defined(Free)
#undef Free
#endif /* Free */
#endif /* VXWORKS */

/**
 * @fn void R_malloc_init()
 *
 * Initializes the memory management method functions.
 *
 * @note When working with the library built as a WIN32 DLL, the 
 * application's <tt>libc</tt> memory allocation routines are required as
 * it may have been compiled and linked with different flags.
 * Calling R_malloc_init() performs this, and has no effect on the 
 * behavior in standard builds which are already using the allocation routines.
 *
 * @see R_set_mem_functions().
 */
#define R_malloc_init() R_set_mem_functions(\
    (R_MEM_MALLOC_FUNCTION_T *)malloc,\
    (R_MEM_REALLOC_FUNCTION_T *)realloc,\
    (R_MEM_FREE_FUNCTION_T *)free)

#ifndef NO_CRYPTO_MEM
/* Compatibility macros with the CRYPTO names */
#define CRYPTO_set_mem_functions    R_set_mem_functions
#define CRYPTO_get_mem_functions    R_get_mem_functions
#define CRYPTO_malloc           R_malloc
#define CRYPTO_realloc          R_realloc
#define CRYPTO_free         R_free
#define CRYPTO_remalloc         R_remalloc
#endif /*  !NO_CRYPTO_MEM */


/**
 * @defgroup MEM_ALL_FUNCS Memory Management Functions
 * This section details the functions that facilitate memory management.
 * @{
 */

/*
 * R_MDEBUG can be defined when the library is compiled to include the
 * debug versions of memory functions. The R_MDEBUG definition cannot
 * be usefully defined when linking with an existing library binary
 * that has not been built with that definition. To include some debugging
 * information with an existing library binary implement debug code in a
 * set of functions that can be set with the R_set_mem_functions() call.
 *
 * If either CRYPTO_MDEBUG or R_MDEBUG are defined, developers must ensure
 * that both definitions exist.
 */
#ifndef NO_CRYPTO_MEM
#if (defined(CRYPTO_MDEBUG) && !defined(R_MDEBUG))
#define R_MDEBUG
#endif
#endif /*  !NO_CRYPTO_MEM */

#ifdef R_MDEBUG
/* Get the debug versions of Malloc, and other memory macros */
#include "r_memdbg.h"
#else
#if !defined(NO_MFUNC)
/**
 * @fn void *Malloc(size_t len)
 *
 * Allocates a block of memory.
 *
 * @param len     [In]      The size of memory to allocate.
 *
 * @return  A pointer to allocated memory.<br>
 *          <tt>NULL</tt> indicates error.
 *
 * @see     Realloc() and Free().
 */
#define Malloc      R_malloc

/**
 * @fn void *Realloc(void *a, size_t new_num, size_t old_num)
 *
 * Changes the size of a block of allocated memory.
 *
 * @param a       [In]      The address of memory to reallocate.
 * @param new_num [In]      The new size of the allocated memory.
 * @param old_num [In]      The old size of the allocated memory.
 *
 * @return  A pointer to reallocated memory.<br>
 *          <tt>NULL</tt> indicates error.
 *
 * @see     Malloc().
 */
#define Realloc(a,new_num,old_num)  \
            R_realloc((char *)(a),(new_num),(old_num))
#define FreeFunc    R_free

/**
 * @fn void Free(void *addr)
 *
 * Deallocates memory.
 *
 * @param addr    [In]      The address of memory to deallocate.
 *
 * @see     Malloc() and Realloc().
 */
#define Free(addr)  R_free((char *)(addr))
#else /* NO_MFUNC */
/**
 * @fn void *Malloc(size_t len)
 *
 * Allocates a block of memory.
 *
 * @param len     [In]      The size of memory to allocate.
 *
 * @return  Pointer to allocated memory on success.<br>
 *          Otherwise NULL on error.
 *
 * @see     Realloc() and Free().
 */
#define Malloc      malloc

/**
 * @fn void *Realloc(void *a, size_t new_num, size_t old_num)
 *
 * Changes the size of a block of allocated memory.
 *
 * @param a       [In]      The address of memory to reallocate.
 * @param new_num [In]      The new size of the allocated memory.
 * @param old_num [In]      The old size of the allocated memory.
 *
 * @return  Pointer to reallocated memory on success.<br>
 *          Otherwise NULL on error.
 *
 * @see     Malloc().
 */
#define Realloc(a,new_num,old_num)    realloc((a),(new_num))
#define FreeFunc    free

/**
 * @fn void Free(void *addr)
 *
 * Deallocates memory.
 *
 * @param addr    [In]  The address of memory to deallocate.
 *
 * @see     Malloc() and Realloc().
 */
#define Free(addr)  free((char *)(addr))
#endif /* NO_MFUNC */

/* Remalloc is a call to Free an existing pointer and then Malloc a new
 * one of the specified size.
 */
#define Remalloc    R_remalloc

#ifndef NO_MEM_CHECK
/* these macros are only used in debug mode */
#define MemCheck_start()
#define MemCheck_stop()
#define MemCheck_on()
#define MemCheck_off()
#define MemCheck_begin()

#ifndef Mem_get_mh_mode
#define Mem_get_mh_mode()    0
#endif
#endif /* !NO_MEM_CHECK */

#endif /* R_MDEBUG */

/*
 * Locking memory functions may be customised to allocate memory that holds
 * sensitive data that should not be swapped to disk as part of a virtual
 * memory system. NOTE: There are no specific debug versions of these macros.
 */
#if !defined(NO_MFUNC)
#else /* !NO_MFUNC */
#define Malloc_locked         malloc
#define Free_locked(addr)     free((char *)(addr))
#endif /* NO_MFUNC */

/**
 * Allocates memory.
 *
 * @param num     [In]  The size of memory to allocate.
 *
 * @return  Pointer to allocated memory on success.<br>
 *          Otherwise <tt>NULL</tt> on error.
 *
 * @see     R_set_mem_functions() and R_get_mem_functions().
 */
typedef char *R_MEM_MALLOC_FUNCTION_T(size_t num);

/**
 * Reallocates memory.
 *
 * @param addr    [In, Out] A reference to the allocated data to resize.
 * @param num_new [In]      The size of memory to allocate.
 * @param num_old [In]      The size of memory allocated to <i>addr</i>.
 *
 * @return  Pointer to reallocated memory on success.<br>
 *          Otherwise <tt>NULL</tt> on error.
 *
 * @see     R_set_mem_functions() and R_get_mem_functions().
 */
typedef char *R_MEM_REALLOC_FUNCTION_T(char *addr, size_t num_new,
    size_t num_old);

/**
 * Frees memory.
 * @param str     [In] A reference to the data to deallocate. 
 *
 * @see     R_set_mem_functions() and R_get_mem_functions().
 */
typedef void R_MEM_FREE_FUNCTION_T(char *str);

void R_set_mem_functions(R_MEM_MALLOC_FUNCTION_T *malloc_function,
    R_MEM_REALLOC_FUNCTION_T *realloc_function,
    R_MEM_FREE_FUNCTION_T *free_function);

void R_get_mem_functions(R_MEM_MALLOC_FUNCTION_T **malloc_function,
    R_MEM_REALLOC_FUNCTION_T **realloc_function,
    R_MEM_FREE_FUNCTION_T **free_function);

char *R_malloc(size_t num);
void  R_free(char *str);
char *R_realloc(char *addr, size_t num_new, size_t num_old);
char *R_remalloc(char *addr, size_t num);

int R_mem_ctrl(int mode);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_MEM_H */


