/* $Id: r_lock.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_lock.h
 * This file contains information on the defines and declarations for
 * synchronization functions.
 */
#ifndef HEADER_COMMON_R_LOCK_H
#define HEADER_COMMON_R_LOCK_H

#ifdef  __cplusplus
extern "C" {
#endif

#define CRYPTO_LOCK             R_LOCK_LOCK
#define CRYPTO_UNLOCK               R_LOCK_UNLOCK
#define CRYPTO_READ             R_LOCK_READ
#define CRYPTO_WRITE                R_LOCK_WRITE
/**
 * @defgroup R_LOCK_GROUP Synchronization via Locking
 * This section outlines the locking functions in the library that enable the
 * synchronization of multithreaded applications.
 *
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup LOCK_DEFS Locking Flags
 * This section outlines the locking control options.
 * @ingroup R_LOCK_GROUP
 * @{
 */
/**
 * Specifies the mask flag used when requesting a lock. Used in conjunction 
 * with either #R_LOCK_READ or #R_LOCK_WRITE.
 */
#define R_LOCK_LOCK             1
/**
 * Specifies the mask flag used when releasing a lock. Used in conjunction 
 * with either #R_LOCK_READ or #R_LOCK_WRITE.
 */
#define R_LOCK_UNLOCK               2
/**
 * Specifies the mask flag used when requesting or releasing a read operation 
 * lock. Used in conjunction with either #R_LOCK_LOCK or #R_LOCK_UNLOCK.
 */
#define R_LOCK_READ             4
/**
 * Specifies the mask flag used when requesting or releasing a write operation
 * lock. Used in conjunction with either #R_LOCK_LOCK or #R_LOCK_UNLOCK.
 */
#define R_LOCK_WRITE                8

/**
 * @}
 */

#ifndef NO_LOCKING
#define CRYPTO_r_lock(a)            R_lock_r(a)
#define CRYPTO_r_unlock(a)          R_unlock_r(a)
#define CRYPTO_w_lock(a)            R_lock_w(a)
#define CRYPTO_w_unlock(a)          R_unlock_w(a)
#define CRYPTO_add(a,b,c)           R_add(a,b,c)
#define CRYPTO_add_lock(a,b,c)          R_locked_add(a,b,c)

#define CRYPTO_get_id_cb()          R_thread_id_get_cb()
#define CRYPTO_set_id_cb(f)         R_thread_id_set_cb(f)
#define CRYPTO_thread_id()          R_thread_id()


#else /* NO_LOCKING */
#define CRYPTO_w_lock(a)
#define CRYPTO_w_unlock(a)
#define CRYPTO_r_lock(a)
#define CRYPTO_r_unlock(a)
#define CRYPTO_add(a,b,c)           ((*(a))+=(b))
#define CRYPTO_thread_id()          0
#endif /* !NO_LOCKING */

#define CRYPTO_LOCK_ERR             R_LOCK_ERR
#define CRYPTO_LOCK_ERR_HASH            R_LOCK_ERR_HASH
#define CRYPTO_LOCK_X509            R_LOCK_X509
#define CRYPTO_LOCK_X509_INFO           R_LOCK_X509_INFO
#define CRYPTO_LOCK_X509_PKEY           R_LOCK_X509_PKEY
#define CRYPTO_LOCK_X509_CRL            R_LOCK_X509_CRL
#define CRYPTO_LOCK_X509_REQ            R_LOCK_X509_REQ
#define CRYPTO_LOCK_DSA             R_LOCK_DSA
#define CRYPTO_LOCK_RSA             R_LOCK_RSA
#define CRYPTO_LOCK_X509_STORE          R_LOCK_X509_STORE
#define CRYPTO_LOCK_SSL_CTX         R_LOCK_SSL_CTX
#define CRYPTO_LOCK_SSL_CERT            R_LOCK_SSL_CERT
#define CRYPTO_LOCK_SSL_SESSION         R_LOCK_SSL_SESSION
#define CRYPTO_LOCK_SSL             R_LOCK_SSL
#define CRYPTO_LOCK_EVP_PKEY            R_LOCK_EVP_PKEY
#define CRYPTO_LOCK_RAND            R_LOCK_RAND
#define CRYPTO_LOCK_MALLOC          R_LOCK_MALLOC
#define CRYPTO_LOCK_BIO             R_LOCK_BIO
#define CRYPTO_LOCK_SIO_GETHOSTBYNAME       R_LOCK_SIO_GETHOSTBYNAME
#define CRYPTO_LOCK_MALLOC_MOD          R_LOCK_MALLOC_MOD
#define CRYPTO_LOCK_RSA_HOOK            R_LOCK_RSA_HOOK
#define CRYPTO_LOCK_DH              R_LOCK_DH

/**
 * @defgroup LOCK_PKEY_FLAGS Public Key Synchronization Flags
 * This section details the flags associated with synchronization of a public
 * key structure.
 * @ingroup R_LOCK_GROUP
 * @{
 */

/** 
 * Indicates an invalid lock.
 */
#define R_LOCK_INVALID              0
/* 
 * Indicates a lock on error.
 */
#define R_LOCK_ERR              1
/* 
 * Indicates a lock on error hash.
 */
#define R_LOCK_ERR_HASH             2
#define R_LOCK_X509             3
#define R_LOCK_X509_INFO            4
#define R_LOCK_X509_PKEY            5
#define R_LOCK_X509_CRL             6
#define R_LOCK_X509_REQ             7
/*
 * Indicates a lock on <<tt>#DSA</tt>.
 */
#define R_LOCK_DSA              8
/* 
 * Indicates a lock on <tt>#RSA</tt>.
 */
#define R_LOCK_RSA              9
/* 
 * Indicates a lock on <tt>#EVP_PKEY</tt>.
 */
#define R_LOCK_EVP_PKEY             10
#define R_LOCK_X509_STORE           11
/*
 * Indicates a lock on <tt>#SSL_CTX</tt>.
 */
#define R_LOCK_SSL_CTX                          12
/* 
 * Indicates a lock on <tt>#SSLCERT</tt>. 
 */
#define R_LOCK_SSL_CERT                         13
/* 
 * Indicates a lock on <tt>#SSL_SESSION</tt>.
 */
#define R_LOCK_SSL_SESSION                      14
/*
 * Indicates a lock on <tt>#SSL</tt>.
 */
#define R_LOCK_SSL                              15
/**
 * Indicates a lock on a random number generator.
 */
#define R_LOCK_RAND             16
/* 
 * Indicates a lock on <tt>malloc</tt>.
 */
#define R_LOCK_MALLOC               17
/** 
 * Indicates a lock on #BIO.
 */
#define R_LOCK_BIO              18
/* 
 * Indicates a lock on a socket.
 */
#define R_LOCK_SIO_GETHOSTBYNAME        19
/*
 * Indicates a lock on the malloc module.
 */
#define R_LOCK_MALLOC_MOD           21
/*
 * Indicates a lock on the RSA hook.
 */
#define R_LOCK_RSA_HOOK             22
/*
 * Indicates a lock on the DH.
 */
#define R_LOCK_DH               23
/** 
 * Indicates an application lock.
 */
#define R_LOCK_APP_LOCK             24
#define R_LOCK_R_CACHE_LOCK         25
/** 
 * Indicates a lock on getting a module from the library context.
 */
#define R_LOCK_GET_MODULE           26
#define R_LOCK_R_CERT_STORE_LOCK        27
#define R_LOCK_R_CERT               28
/** 
 * Indicates the total number of pre-allocated locks.
 */
#define R_LOCK_NUM              29

/**
 * @}
 */

/* old names */
#define CRYPTO_set_locking_callback(x)      CRYPTO_set_locking_cb(x)
#define CRYPTO_get_locking_callback()       CRYPTO_get_locking_cb()
#define CRYPTO_set_add_lock_callback(x)     CRYPTO_set_add_lock_cb(x)
#define CRYPTO_get_add_lock_callback()      CRYPTO_get_add_lock_cb()
#define CRYPTO_set_id_callback(x)       CRYPTO_set_id_cb(x)
#define CRYPTO_get_id_callback()        CRYPTO_get_id_cb()

#define CRYPTO_get_new_lockid(name)     R_lockid_new(name)
#define CRYPTO_get_num_locks()          R_lock_num()
#define CRYPTO_set_locking_cb(func)     R_lock_set_cb(func)
#define CRYPTO_get_locking_cb()         R_lock_get_cb()
#define CRYPTO_set_add_lock_cb(func)        R_locked_add_set_cb(func)
#define CRYPTO_get_add_lock_cb()        R_locked_add_get_cb()
#define CRYPTO_get_lock_name(lockid)        R_lock_get_name(lockid)
#define CRYPTO_lock(mode,lockid,file,line)  \
                R_lock_ctrl(mode,lockid,file,line)


/**
 * @defgroup LOCK_FUNCS Locking Functions
 * This section outlines the functions that implement the toolkit's 
 * locking functionality.
 * @ingroup R_LOCK_GROUP
 * @{
 */

#ifdef NO_R_LOCK

#define R_lock_w(type)
#define R_unlock_w(type)
#define R_lock_r(type)
#define R_unlock_r(type)
#define R_add(addr,amount,type)         (*(addr)=*(addr)+(amount))
#define R_lock(mode,type,file,line)
#define R_unlock(mode,type,file,line)

#else /* NO_R_LOCK */

#ifndef R_lock_w
/**
 * @fn int R_lock_w(int lockid)
 * Retrieves a write lock for the lock <i>lockid</i>.
 *
 * @param lockid  [In]  The lock identifier.
 * @return
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note The caller is blocked until the lock
 * becomes available.<br>
 * This macro calls R_lock_ctrl() with <tt>__FILE__</tt> and <tt>__LINE__</tt>
 * as the file and line parameters. This identifies the source code file and
 * line number where the lock/unlock occurs. This is useful when debugging.
 *
 * @see R_lock_r(), R_unlock_r() and R_unlock_w().
 */
#define R_lock_w(lockid)    \
    R_lock(R_LOCK_WRITE,lockid,__FILE__,__LINE__)

/**
 * @fn int R_unlock_w(int lockid)
 * Clears the write lock for <i>lockid</i>.
 *
 * @param lockid  [In]  The lock identifier.
 * @return
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note  The caller is blocked until the lock
 * becomes available.<br>
 * This macro calls R_lock_ctrl() with <tt>__FILE__</tt> and <tt>__LINE__</tt>
 * as the file and line parameters.
 * This identifies the source code file and
 * line number where the lock/unlock occurs.
 * This is useful when debugging.
 *
 * @see R_lock_r(), R_unlock_r() and R_lock_w().
 */
#define R_unlock_w(lockid)  \
    R_unlock(R_LOCK_WRITE,lockid,__FILE__,__LINE__)

/**
 * @fn int R_lock_r(int type)
 * Retrieves a read lock for the lock <i>type</i>.
 *
 * @param type  [In]  The lock identifier.
 * @return
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note The caller is blocked until the lock
 * becomes available.<br>
 * This macro calls R_lock_ctrl() with <tt>__FILE__</tt> and
 * <tt>__LINE__</tt> as the file and line parameters.
 * This identifies the source code file and
 * line number where the lock/unlock occurs.
 * This is useful when debugging.
 *
 * @see R_unlock_r(), R_lock_w() and R_unlock_w().
 */
#define R_lock_r(type)  \
    R_lock(R_LOCK_READ,type,__FILE__,__LINE__)

/**
 * @fn int R_unlock_r(int lockid)
 * Clears the read lock for <i>lockid</i>.
 *
 * @param lockid  [In]  The lock identifier.
 * @return
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note The caller is blocked until the lock
 * becomes available.
 *
 * @see R_lock_r(), R_lock_w() and R_unlock_w().
 */
#define R_unlock_r(lockid)  \
    R_unlock(R_LOCK_READ,lockid,__FILE__,__LINE__)

/**
 * @fn int R_add(int *addr, int amount, int type)
 * Increments reference counts. This is an atomic
 * adjustment that is performed on an all or nothing basis and is a
 * lock protected update of an integer.
 *
 * @param addr    [Out] A pointer to the integer.
 * @param amount  [In]  The amount by which to change the integer.
 * @param type    [In]  The lock identifier.
 * @return
 * 1 indicates success.<br>
 * Otherwise indicates error.
 *
 * @see R_locked_add_set_cb().
 */
#define R_add(addr,amount,type) \
    R_locked_add(addr,amount,type,__FILE__,__LINE__)

/**
 * @fn int R_lock(int mode, int lockid, char *file, int line)
 * Sets a specified lock.
 *
 * @param mode    [In]  The lock mode. One of:<br>
 * <li> #R_LOCK_READ</li>.
 * <li> #R_LOCK_WRITE</li>.
 * @param lockid  [In]  The lock identifier.
 * @param file    [In]  The source code file (may be <tt>NULL</tt>).
 * @param line    [In]  The line number in the file (may be 0).
 * @return
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note <tt>file</tt> and <tt>line</tt> are optional fields
 * indicating the source code file and line number where
 * the lock/unlock occurs. This is useful when debugging.<br>
 * Applications should call R_lock_r(),
 * R_unlock_r(), R_lock_w() or R_unlock_w() in preference
 * to directly accessing this function.
 *
 * @see R_lock_r(), R_unlock_r(), R_lock_w() and R_unlock_w().
 */
#define R_lock(mode,lockid,file,line)   \
    R_lock_ctrl(R_LOCK_LOCK|(mode),lockid,file,line)

/**
 * @fn int R_unlock(int mode, int lockid, char *file, int line)
 * Clears a specified lock.
 *
 * @param mode    [In]  The lock mode. One of:<br>
 * <li> #R_LOCK_READ</li>.
 * <li> #R_LOCK_WRITE</li>.
 * @param lockid  [In]  The lock identifier.
 * @param file    [In]  The source code file (may be <tt>NULL</tt>).
 * @param line    [In]  The line number in the file (may be 0).
 * @returns
 * >0 indicates success.<br>
 * <=0 indicates error.
 *
 * @note <tt>file</tt> and <tt>line</tt> are optional fields
 * indicating the source code file and line number where
 * the lock/unlock occurs. This is useful when debugging.<br>
 * Applications should call R_lock_r(),
 * R_unlock_r(), R_lock_w() or R_unlock_w() in preference
 * to directly accessing this function.
 *
 * @see R_lock_r(), R_unlock_r(), R_lock_w() and R_unlock_w().
 */
#define R_unlock(mode,lockid,file,line) \
    R_lock_ctrl(R_LOCK_UNLOCK|(mode),lockid,file,line)

#endif /* ! R_lock_w */

#endif /* NO_R_LOCK */

#ifdef NO_R_LOCK

#define R_lockid_new(a)
#define R_lockids_free()
#define R_lock_num()                    0
#define R_lock_get_name(a)
#define R_lock_get_cb()
#define R_locked_add_get_cb()
#define R_lock_set_cb(a)
#define R_locked_add_set_cb(a)
#define R_lock_ctrl(a,b,c,d)
#define R_locked_add(a,b,c,d,e)
#define R_thread_id_get_cb()
#define R_thread_id_set_cb(a)
#define R_thread_id()                   0

#else /* !NO_R_LOCK */

/**
 * Reports on the locking mechanism.
 *
 * @param    mode      [In] The lock mode. Use one of the following
 *                          combinations:<br>
 *                          <li>#R_LOCK_LOCK with #R_LOCK_READ</li>     
 *                          <li>#R_LOCK_LOCK with #R_LOCK_WRITE</li>
 *                          <li>#R_LOCK_UNLOCK with #R_LOCK_READ</li>
 *                          <li>#R_LOCK_UNLOCK with #R_LOCK_WRITE</li><br>
 *                          See @ref LOCK_DEFS for valid values.
 * @param    lockid    [In] The identifier for the lock.
 * @param    file      [In] The file name (optional).
 * @param    line      [In] The line in <i>file</i> (optional).
 * @return   > 0 indicates success.<br>
 *           <= 0 indicates an error.
 *
 * @see      R_lock_get_cb(), R_lock_set_cb() and R_lock_w().
 */
typedef int R_LOCK_CB_T(int mode, int lockid, char *file, int line);
R_LOCK_CB_T *R_lock_get_cb(void);
int R_lock_set_cb(R_LOCK_CB_T *func);

/**
 * Implements locking of data structures and objects.
 * This callback is used to increment/decrement an integer for
 * maintaining reference counts against the major data structures.
 *
 * @param    num       [In] The object upon which to operate.
 * @param    amount    [In] The amount to use.
 * @param    lockid    [In] The identifier for the lock.
 * @param    file      [In] The file name (optional).
 * @param    line      [In] The line in <i>file</i> (optional).
 *
 * @see      R_locked_add_get_cb() and R_locked_add_set_cb().
 */
typedef int R_LOCKED_ADD_CB_T(int *num, int amount, int lockid, char *file,
    int line);
R_LOCKED_ADD_CB_T *R_locked_add_get_cb(void);
int R_locked_add_set_cb(R_LOCKED_ADD_CB_T *func);

int R_lockid_new(char *name);
void R_lockids_free(void);
int R_lock_num(void);
char *R_lock_get_name(int lockid);
int R_lock_ctrl(int mode, int lockid, char *file, int line);
int R_locked_add(int *pointer, int amount, int lockid, char *file, int line);

/**
 * Returns a unique identifier for each thread.
 * This callback is called by R_thread_id().
 *
 * @see      R_thread_id(), R_thread_id_get_cb() and R_thread_id_set_cb().
 */
typedef unsigned long R_THREAD_ID_CB_T(void);

int R_thread_id_set_cb(R_THREAD_ID_CB_T *func);
R_THREAD_ID_CB_T *R_thread_id_get_cb(void);

unsigned long R_thread_id(void);

#endif /* NO_R_LOCK */

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_LOCK_H */


