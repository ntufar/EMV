/* $Id: r_shlib.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2001 RSA Security Inc. All rights reserved. This
 * work contains proprietary information of RSA Security Inc. Distribution
 * is limited to authorised licensees of RSA Security Inc. Any unauthorised
 * reproduction or distribution of this work is strictly prohibited.
 */

#ifndef HEADER_COMMON_OS_SHLIB_R_SHLIB_H
#define HEADER_COMMON_OS_SHLIB_R_SHLIB_H

#ifdef  __cplusplus
extern "C" {
#endif

/* 
 * This file defines cross-platform functions to load and unload 
 * a shared library and get a proc address.
 */

/* TODO: we need a generic pointer type */
#ifndef R_PTR_T_TYPEDEF_DEF
#define R_PTR_T_TYPEDEF_DEF
typedef void *R_PTR_T;
#endif /* R_PTR__T_TYPEDEF_DEF */

/* TODO: we need a generic function pointer type */
#ifndef R_FUNCPTR_T_TYPEDEF_DEF
#define R_FUNCPTR_T_TYPEDEF_DEF
typedef void (*R_FUNCPTR_T)(void);
#endif /* R_FUNCPTR_T_TYPEDEF_DEF */

/* generic handle - size of a pointer */
#ifndef R_SHLIB_HANDLE_T_TYPEDEF_DEF
#define R_SHLIB_HANDLE_T_TYPEDEF_DEF
typedef void *R_SHLIB_HANDLE_T;		
#endif

/* shared library loader function type */
#ifndef R_SHLIB_LOAD_T_TYPEDEF_DEF
#define R_SHLIB_LOAD_T_TYPEDEF_DEF
/* use the librarian.h definition if it is available */
#ifdef _LIBRARIAN_H_
typedef CRYPTOC_ME_FIPS140_LOAD_CB_T R_SHLIB_LOAD_T;
#else 
typedef void *(*R_SHLIB_LOAD_T)(char *filename, void *cb_arg, int *os_err);		
#endif
	
#endif /* R_SHLIB_LOAD_T_TYPEDEF_DEF */

/* TODO: we need a generic handle type - 32/64 bits */
#ifndef R_SHLIB_T_TYPEDEF_DEF
#define R_SHLIB_T_TYPEDEF_DEF
typedef struct {
  R_SHLIB_HANDLE_T shlib_handle;
  int flag;
  R_SHLIB_LOAD_T shlib_loader_cb;
  void *shlib_loader_arg;
  char *shlib_loc;
  
} R_SHLIB_T;
#endif /* R_SHLIB_T_TYPEDEF_DEF */

typedef int R_SHLIB_SEARCH_VAR_T;


#define R_SHLIB_SEARCH_VAR_PATH	          0x0001
#define R_SHLIB_SEARCH_VAR_ENV	          0x0002
/* The SHLIB NAME can be specified in combination with any of the above */
#define R_SHLIB_SEARCH_BASE_MASK          0x0FFF
#define R_SHLIB_SEARCH_VAR_NAME_FIRST     0x1000

#define R_SHLIB_FLAG_NONE	0x0000
#define R_SHLIB_FLAG_SELF	0x0001

#define R_SHLIB_NAME            "R_SHLIB_NAME"

#if ( defined(PLATFORM_WINDOWS) || defined(PLATFORM_WINCE) )
/* Win32 API implements implicit path searching in the LoadLibrary function
 * so the default search path should be left blank to avoid unexpected 
 * side effects.
 */
#define R_SHLIB_DEFAULT_SEARCH_PATH	{ NULL }
#else
#define R_SHLIB_DEFAULT_SEARCH_PATH	{ "/lib", "/usr/lib", \
					  "/usr/local/lib", NULL }
#endif

/* R_SHLIB_LD_LIBRARY_PATH and LD_LIBRARY_PATH are for all platforms,
 * but LIBPATH is for AIX only (to match the dlopen behavior on this platform).
 */
#if R_OS == R_OS_AIX

#define R_SHLIB_DEFAULT_SEARCH_ENV	{ "R_SHLIB_LD_LIBRARY_PATH", \
				 	  "LD_LIBRARY_PATH", \
                      "LIBPATH", \
                       NULL }
#else

#define R_SHLIB_DEFAULT_SEARCH_ENV	{ "R_SHLIB_LD_LIBRARY_PATH", \
				 	  "LD_LIBRARY_PATH", \
                       NULL }
#endif

/**
 * @brief Loads a shared library and returns a platform dependent 
 *        opaque handle to it. 
 *
 * @param libraryName	[IN]  the path to the shared library or dynamic 
 *                            link library that is to be loaded
 * @param pLib		[OUT] pointer to where to store the library handle
 * @param os_err	[OUT] optional location to return operating system
 *			      specific error code (on error)
 * @return		R_ERROR_NONE on success. 
 *			R_ERROR_NOT_SUPPORTED if loading shared libraries 
 *			is not supported on this platform. 
 *			R_ERROR_NOT_FOUND if the library could not be located. 
 *			R_ERROR_FAILED on other error condition.
 *
 * @note
 * 	It is the responsibility of R_os_shlib_unload to free up any memory
 * 	allocated by R_os_shlib_load.
 *
 * @note
 *	The search path for libraries is platform-specific.
 *
 * @note
 *	On some platforms libraryName can be NULL to indicate the current
 *	executable image.
 */
int R_os_shlib_load(char *libraryName, R_SHLIB_T *pLib, int *os_err);

/**
 * @brief Loads a shared library and returns a platform dependent 
 *        opaque handle to it. A search path (either directly specified
 *        by a path list or indirectly specified by a list of environment
 *        variables which contain paths) is used to locate the library.
 *
 * @param libraryName  	  [IN] the name of the shared library or dynamic 
 *                             link library that is to be loaded
 * @param search_var	  [IN] NULL terminated array of pointers to search
 *                             arguments.
 * @param search_var_type [IN] type of search variable. One of 
 *				#R_SHLIB_SEARCH_VAR_PATH or 
 *				#R_SHLIB_SEARCH_VAR_ENV.
 * @param pLib		  [OUT] pointer to where to store the library handle
 * @param os_err	  [OUT] optional location to return operating system
 *			        specific error code (on error)
 * @return		R_ERROR_NONE on success. 
 *			R_ERROR_NOT_SUPPORTED if loading shared libraries 
 *			is not supported on this platform. 
 *			R_ERROR_NOT_FOUND if the library could not be located. 
 *			R_ERROR_FAILED on other error condition.
 *
 * @note
 * 	It is the responsibility of R_os_shlib_unload to free up any memory
 * 	allocated by R_os_shlib_load.
 *
 * @note
 *	The search path for libraries is platform-specific.
 *
 * @note
 *	On some platforms libraryName can be NULL to indicate the current
 *	executable image.
 */
int R_os_shlib_load_search(char *libraryName, char **search_var, 
    R_SHLIB_SEARCH_VAR_T search_var_type, R_SHLIB_T *pLib, int *os_err);

/**
 * @brief Finds a shared library and returns the filename including path to it.
 *        A search path (either directly specified by a path list or indirectly
 *        specified by a list of environment variables which contain paths)
 *        is used to locate the library.
 *
 * @param libraryName  	  [IN] the name of the shared library or dynamic 
 *                             link library that is to be shearched for
 * @param search_var	  [IN] NULL terminated array of pointers to search
 *                             arguments.
 * @param search_var_type [IN] type of search variable. One of 
 *				#R_SHLIB_SEARCH_VAR_PATH or 
 *				#R_SHLIB_SEARCH_VAR_ENV.
 * @param filePath	  [OUT] pointer to where to store the library filename
 * @param os_err	  [OUT] optional location to return operating system
 *			        specific error code (on error)
 * @return		R_ERROR_NONE on success. 
 *			R_ERROR_NOT_FOUND if the library could not be located.
 *			See @ref R_ERROR_IDS for other valid values.
 *
 * @note
 * 	It is the responsibility of the caller to free up memory allocated by
 * 	this function when the return value is R_ERROR_NONE.
 */
int R_os_shlib_file_search(char *libraryName, char **search_var,
    R_SHLIB_SEARCH_VAR_T search_var_type, char **filePath, int *os_err);

/**
 * @brief Locate the address for an export symbol (function) of the 
 *        given shared library.
 *
 * @param pLib		[IN] library handle
 * @param procName	[IN] symbol name (i.e. function name)
 * @param addr		[OUT] address of symbol in current image
 * @param os_err	[OUT] optional location to return operating system
 *			specific error code (on error)
 * @return		R_ERROR_NONE on success. 
 *			R_ERROR_NOT_SUPPORTED if loading shared libraries 
 *			is not supported on this platform. 
 *			R_ERROR_NOT_FOUND if the library could not be located. 
 *			R_ERROR_FAILED on other error condition.
 */
int R_os_shlib_get_addr(R_SHLIB_T *pLib, char *procName, 
    R_PTR_T *addr, int *os_err);

/**
 * @brief Unloads a previously loaded shared library.
 *
 * @param pLib		[IN] library handle
 * @param os_err	[OUT] optional location to return operating system
 *			specific error code (on error)
 * @return		R_ERROR_NONE on success. 
 *			R_ERROR_NOT_SUPPORTED if loading shared libraries 
 *			is not supported on this platform. 
 *			R_ERROR_NOT_FOUND if the library could not be located. 
 *			R_ERROR_FAILED on other error condition.
 *
 * @note
 *	Any memory allocated during R_os_shlib_load will be freed during
 *      this function. Errors can be returned.
 *
 * @note
 *	Copying the library handle and calling this function more than once
 *      can cause unexpected confusion on some platforms. This routine provides
 *      no additional protection beyond what the underlying operating system
 *	routine provides.
 *
 */
int R_os_shlib_unload(R_SHLIB_T *pLib, int *os_err);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_OS_SHLIB_R_SHLIB_H */


