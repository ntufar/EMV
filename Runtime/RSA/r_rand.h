/* $Id: r_rand.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_rand.h
 * This file provides defines, macros and function prototypes for the
 * manipulation of random objects and the generation of pseudo random
 * numbers.
 */

#ifndef HEADER_COMMON_R_RAND_H
#define HEADER_COMMON_R_RAND_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_types.h"

/**
 * @defgroup R_RAND_GROUP Entropy Management
 * This section lists the functions, types and identifiers used for pseudo
 * random number generation.
 *
 * A source of pseudo random numbers is required for various aspects of
 * the security protocol and components included in this product.
 * Failure to appropriately seed the Pseudo Random Number Generator (PRNG)
 * will seriously impact the security provided.  Your application should
 * provide this random seed.
 *
 * The exact requirements for this seeding process may depend upon your
 * application and the environment for which your application is designed.
 * For more information, see <A HREF="http:\\www.ietf.org\rfc\rfc1750.txt">
 * RFC 1750 - Randomness Recommendations for Security</A>.
 *
 * @{
 */
/**
 * @}
 */
/**
 * @defgroup R_RAND_DEFS Entropy Management Definitions
 * This section details the defines utilized by the Pseudo Random Number
 * Generator (PRNG).
 * @ingroup R_RAND_GROUP
 * @{
 */

/**
 * Defines the amount of random data with which to seed the Pseudo Random
 * Number Generator (PRNG).
 */
#define R_RAND_ADD_ENTROPY_LARGE    0x01
/**
 * Defines the amount of random data with which to seed the Pseudo Random
 * Number Generator (PRNG).
 */
#define R_RAND_ADD_ENTROPY_SMALL    0x02

/**
 * Indicates that the current default random is NULL, or not set.
 */
#define R_RAND_DEFAULT_STATE_NULL   0x00
/**
 * Indicates that the current default random is set.
 */
#define R_RAND_DEFAULT_STATE_SET    0x01
/**
 * Defines the default name of the entropy file.
 */
#define R_RAND_DEFAULT_ENTROPY_FILE "entropy"
/**
 * Defines the environment variable that overrides the default entropy file 
 * name. 
 */
#define R_RAND_ENV_ENTROPY_FILE     "R_RAND_ENV_ENTROPY_FILE"
/**
 * Indicates the maximum number of bytes read from the entropy file.
 */
#define R_RAND_ENTROPY_FILE_LEN     64
/**
 * Indicates the maximum length of the entropy file name.
 */
#define R_RAND_MAX_ENTROPY_FILENAME_LEN    256

/**
 * @}
 */

/**
 * @defgroup R_RAND_ALL_FUNCS Entropy Seeding Functions
 * This section details the functions that generate the seed for random number
 * generation.
 * @ingroup R_RAND_GROUP
 * @{
 */
/**
 * @}
 */

/*
 * @defgroup R_RAND_LIB_FUNCS Functions for the Library Context
 * This section describes the functions used with the random number generation
 * and resource list modules.
 * @ingroup R_RAND_ALL_FUNCS
 * @{
 */

int R_rand_lib_cleanup(void *res_list, void *res_item, void **imp_data);

/*
 * @}
 */

/*
 * @defgroup R_RAND_METH_FUNCS Method Table Functions
 * This section describes the functions used with the Random Number Generator
 * (RNG) method table.
 * @ingroup R_RAND_ALL_FUNCS
 * @{
 */

/* basic random method */
R_RANDOM *R_rand_meth_sha1(void *lib_ctx);
R_RANDOM *R_rand_meth_sys(void *lib_ctx);
R_RANDOM *R_rand_meth_fips1862_sha1(void *lib_ctx);
R_RANDOM *R_rand_meth_fips1862_mod_sha1(void *lib_ctx);
R_RANDOM *R_rand_meth_otp(void *lib_ctx);

/*
 * Null random method. If specified as the default random method, e.g. using
 * the compile option -DR_RAND_METHOD_DEFAULT=R_rand_meth_null, then no
 * random method is available.
 */
R_RANDOM *R_rand_meth_null(void *lib_ctx);
    

/*
 * @}
 */

/**
 * @defgroup R_RAND_FUNCS Management Functions
 * This section lists the functions used for generating pseudo random numbers.
 * @ingroup R_RAND_ALL_FUNCS
 * @{
 */
/**
 * Creates user-defined random entropy collection routines
 * for seeding a random object. The buffer allocated for collection
 * should be at least as long as the value specified in <i>len</i>.
 *
 * @param data [Out] The random entropy buffer.
 * @param len  [In]  The length of random entropy to write to 
 *                   <i>data</i>.
 *
 * @return #R_ERROR_NONE indicates success.<br>
 *         See @ref R_ERROR_IDS for valid values.
 */
typedef int R_RAND_ENT_FUNC_T(unsigned char *data, unsigned int len);
R_RANDOM *R_rand_new(R_RANDOM *rnd);
int R_rand_gather_entropy(R_RANDOM *rnd, int size);
void R_rand_free(R_RANDOM *rnd);

int R_rand_add_entropy(R_RANDOM *rnd, int num);
/* Return the approximate number of 'random bits' added to the system.
 * This will be a very approximate value.  Values less than 100 should
 * be treated with caution.
 */
R_RANDOM *R_rand_get_default(void);
int R_rand_set_default(R_RANDOM *rnd); /* the R_RANDOM is copied */
int R_rand_get_default_state(void);
int R_rand_seed(R_RANDOM *rnd, unsigned char *buffer, int num);
int R_rand_bytes(R_RANDOM *rnd, unsigned char *buffer, int num);

int R_rand_entropy_count(R_RANDOM *rnd, unsigned long *num);
int R_rand_set_entropy_func(R_RANDOM *rnd, R_RAND_ENT_FUNC_T *entropy_func);
R_RAND_ENT_FUNC_T *R_rand_get_entropy_func(R_RANDOM *rnd);
int R_rand_gather_entropy(R_RANDOM *rnd, int size);
int R_rand_entropy_add(R_RANDOM *rnd, int size, int num, int block_size,
    unsigned char *prev_block, unsigned char *temp_block, int flag);

int R_rand_load_file(R_RANDOM *rnd, char *filename, long size);
int R_rand_write_file(R_RANDOM *rnd, char *filename);
char *  R_rand_file_name(char *buffer, int size);

/**
 * @}
 */

/**
 * @defgroup R_RAND_RES Entropy Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library. For more information, see 
 * @ref RES_LIST_GROUP.
 * @ingroup R_RAND_GROUP
 *
 * @{
 */

/**
 * The standard random module which is required if asymmetric key or
 * random operations are used.
 *
 * @see R_rand_get_default().
 */
#define R_RAND_RES_DEFAULT                                              \
    { R_RES_MOD_ID_RAND, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,           \
      R_RES_FLAG_DEF, NULL,                                             \
      (int (*)(R_RES_LIST *, R_RES_ITEM *, void **))R_rand_lib_cleanup, \
      (void *(*)(void *))R_rand_get_default, NULL }

/**
 * The small random module.
 */
#define R_RAND_RES_SMALL                                                \
    { R_RES_MOD_ID_RAND, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,           \
      R_RES_FLAG_DEF, NULL,                                             \
      (int (*)(R_RES_LIST *, R_RES_ITEM *, void **))R_rand_lib_cleanup, \
      NULL, NULL }

/**
 * @}
 */

/* Compatibility with the old RAND_ functions */

/*
 * @defgroup R_RAND_DEP_FUNCS Deprecated Entropy Management Functions
 * This section lists the deprecated functions used for generating pseudo
 * random numbers. These are supplied for backward compatibility.
 * @ingroup R_RAND_ALL_FUNCS
 * @{
 */

/**
 * @fn int RAND_set_rand_method(R_RANDOM *meth)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Sets the method <i>meth</i> which is used for generating pseudo random
 * numbers via RAND_seed() and RAND_bytes().
 *
 * @param meth  [In]  The <tt>RAND_METHOD</tt> reference.
 *
 * @see RAND_get_rand_method(), RAND_default_method(), RAND_seed() and
 * RAND_bytes().
 */
#define RAND_set_rand_method(meth)  /* Nothing */

/**
 * @fn R_RANDOM *RAND_get_rand_method(void)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Returns the currently active method used for generating
 * pseudo random numbers via RAND_seed() and RAND_bytes().
 *
 * @returns The <tt>RAND_METHOD</tt> reference.
 *
 * @see RAND_set_rand_method(), RAND_default_method(), RAND_seed() and
 * RAND_bytes().
 */
#define RAND_get_rand_method()  (NULL)

/**
 * @fn R_RANDOM *RAND_default_method(void)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Returns the default software-based method used for generating
 * pseudo random numbers.
 *
 * @returns The <tt>RAND_METHOD</tt> reference.
 *
 * @note RAND_get_rand_method() returns that last value.
 *
 * @see RAND_set_rand_method() and RAND_get_rand_method().
 */
#define RAND_default_method()   (NULL)

/**
 * @fn void RAND_cleanup(void)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Zeroes all states in the Random Number Generator (RNG) when a program
 * is finished with the <tt>RAND</tt> library.
 *
 * @see R_rand_free().
 */
#define RAND_cleanup()      R_rand_free(R_rand_get_default())

/**
 * @fn int RAND_bytes(unsigned char *buffer, int num)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Places <i>num</i> random bytes into buffer <i>buffer</i>. RAND_seed()
 * must be called before using RAND_bytes().
 *
 * @param buffer  [Out]  The buffer.
 * @param num     [In]   The buffer length.
 *
 * @see R_rand_bytes().
 */
#define RAND_bytes(buffer,num)      R_rand_bytes(R_rand_get_default(),buffer,num)

/**
 * @fn int RAND_seed(unsigned char *buffer, int num)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Adds additional seed to the Random Number Generator (RNG)
 * state by adding <i>num</i> bytes from the buffer <i>buffer</i>.
 * This function can be called with sensitive data
 * such as user entered passwords.
 *
 * @param buffer  [In]  The buffer.
 * @param num     [In]  The number of Bytes to add.
 *
 * @note It is recommended to use RAND_load_file() and
 * RAND_write_file() in order to preserve the random state between
 * application executions.
 *
 * @see R_rand_seed().
 */
#define RAND_seed(buffer,num)       R_rand_seed(R_rand_get_default(),buffer,num)

/**
 * @fn int RAND_load_file(char *filename, long size)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Reads data from the file in sections of size
 * until the end of the file is reached.
 *
 * @param filename [In]  The file name.
 * @param size   [In]    The size of the data buffer to read.
 * @return               The number of Bytes passed to RAND_seed().
 *
 * @see R_rand_load_file().
 */
#define RAND_load_file(filename,size)   R_rand_load_file(R_rand_get_default(),filename,size)

/**
 * @fn int RAND_write_file(char *filename)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Writes data in sections of size Bytes to the named file.
 *
 * @param filename    [In]  The file name.
 * @return                  1 indicates success.<br>
 *                          <= 0 indicates error.
 *
 * @see R_rand_write_file().
 */
#define RAND_write_file(filename)   R_rand_write_file(R_rand_get_default(),filename)

/**
 * @fn int RAND_file_name(char *buffer, int size)
 *
 * This function is deprecated and supplied for backward compatibility.
 * Returns a default name for the location of a rand file. The file
 * name is stored in the buffer <i>buffer</i> of <i>size</i> Bytes in length.
 *
 * @param buffer  [Out]  The buffer.
 * @param size    [In]   The length of the buffer.
 * @return               The RAND file location.<br>
 *                       <tt>NULL</tt> indicates error.
 *
 * @note <tt>NULL</tt> is also returned when the buffer has insufficient
 * space to store the RAND file name.
 *
 * @see R_rand_file_name().
 */
#define RAND_file_name(buffer,size) R_rand_file_name(buffer,size)

/*
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_RAND_H */

