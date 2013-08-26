/* $Id: bio.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
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
 * This file provides the Basic Input/Output (BIO) functionality including
 * functions, typedefs and structure declarations.
 */

#ifndef HEADER_COMMON_BIO_H
#define HEADER_COMMON_BIO_H

/**
 * @defgroup BIO_GROUP Input/Output Operations
 * This section describes Basic Input/Output (BIO) operations.
 * BIO is an abstraction for I/O used within the toolkit and
 * is a standardized interface for performing input and output operations.
 * This section also details how to provide support for input and
 * output operations on files. It includes comprehensive
 * information on all the BIO functions.
 * @ingroup CME_WW_BIOS
 * @{
 */
/**
 * @}
 */

#ifdef        __cplusplus
extern "C" {
#endif

/**
 * The BIO object type identifier.
 */
#ifndef HEADER_BIO_H_TYPEDEF_DEF
#define HEADER_BIO_H_TYPEDEF_DEF
typedef struct bio_st BIO;
#endif /* HEADER_BIO_H_TYPEDEF_DEF */

#include "r_com.h"                      /* for NULL + MS_FAR + MS_CALLBACK */
#include "r_vararg.h"
#include "bio_err.h"

#if !defined(NO_SOCK)
#include "sio.h"
#endif



#ifndef HEADER_COMMON_R_LIB_CTX_TYPEDEF_DEF
#define HEADER_COMMON_R_LIB_CTX_TYPEDEF_DEF
typedef struct r_lib_ctx_st                     R_LIB_CTX;
#endif

#ifndef HEADER_COMMON_EX_DATA_H_TYPEDEF_DEF
#define HEADER_COMMON_EX_DATA_H_TYPEDEF_DEF
typedef struct crypto_ex_data_st          CRYPTO_EX_DATA;
typedef struct crypto_ex_data_func_st CRYPTO_EX_DATA_FUNCS;
#endif
/* These are the 'types' of BIOs */

/* socket/fd for connect or accept */
/**
 * @defgroup BIO_IDENTIFIER Input/Output Identifiers and Flags
 * This section lists the identifiers and flags used by the
 * BIO subsystem for identification, manipulation and control
 * of #BIO objects.
 * @ingroup BIO_GROUP
 *
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup BIO_TYPE_DEF Type Identifiers
 * This section lists the identifiers that indicate the type of #BIO in use.
 * @ingroup BIO_IDENTIFIER
 * @{
 */
/**
 * The base type indicating that a BIO of this type modifies the data
 * written to, or read from a source/sink BIO. Filter BIOs may be
 * chained in a BIO stack.
 */
#define BIO_TYPE_FILTER          0x0200

/**
 * The base type indicating that a BIO of this type takes data from a device,
 * and/or sends data to a device (data exchange).
 * In the creation of a BIO stack, a source/sink BIO must be nominated as the
 * initial stack element, and one or more filter BIOs are subsequently pushed
 * onto the stack.
 *
 * However if a source/sink BIO is pushed onto a stack, any BIOs below it in
 * the stack are not reached. Although a BIO stack may contain multiple filter
 * BIOs, it should only contain a single source/sink BIO.
 */
#define BIO_TYPE_SOURCE_SINK     0x0400

/**
 * The base type that may be combined with the source/sink base type to
 * indicate that the BIO uses a file descriptor. BIOs of this type include
 * sockets, file descriptors, accept BIOs and connect BIOs. In this case, the
 * <tt>num</tt> field of the #BIO structure holds the file descriptor.
 */
#define BIO_TYPE_DESCRIPTOR      0x0100

/*
 * The base type that may be combined with the source/sink base type to
 * indicate that the BIO is a datagram socket.
 */
#define BIO_TYPE_DGRAM           0x0800

/**
 * Indicates that the BIO does not have a defined type.
 */
#define BIO_TYPE_NONE               0

/**
 * Indicates that the BIO is a memory buffer source/sink BIO.
 */
#define BIO_TYPE_MEM                (1 | BIO_TYPE_SOURCE_SINK)

/**
 * Indicates that the BIO is a file pointer source/sink BIO.
 */
#define BIO_TYPE_FILE               (2 | BIO_TYPE_SOURCE_SINK)

/**
 * Indicates that the BIO is a file descriptor source/sink BIO.
 */
#define BIO_TYPE_FD                 (4 | BIO_TYPE_SOURCE_SINK | \
                                     BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a <tt>NULL</tt> source/sink BIO. It is used to
 * discard data rather than process it. A read operation from a BIO of this
 * type does not modify the output buffer supplied.
 */
#define BIO_TYPE_NULL               (6 | BIO_TYPE_SOURCE_SINK)

#define BIO_TYPE_MD                 (8 | BIO_TYPE_FILTER)

/**
 * Indicates that the BIO is a data buffer filter BIO. It is used to store
 * data where the next/previous BIO in the BIO stack is non-blocking, and may
 * not be able to read/write all requested data within a single call.
 */
#define BIO_TYPE_BUFFER             (9 | BIO_TYPE_FILTER)

#define BIO_TYPE_CIPHER             (10 | BIO_TYPE_FILTER)

/**
 * Indicates that the BIO is a data base 64 filter BIO.
 */
#define BIO_TYPE_BASE64             (11 | BIO_TYPE_FILTER)

/* BER -> BINARY filter. */
#define BIO_TYPE_BER                (18 | BIO_TYPE_FILTER)

/* Cryptographic Message filter. */
#define BIO_TYPE_CM                 (22 | BIO_TYPE_FILTER)

/* PKCS #7 message filters. */
#define BIO_TYPE_P7                 (23 | BIO_TYPE_FILTER)

/* Cryptographic filter. */
#define BIO_TYPE_CR                 (24 | BIO_TYPE_FILTER)

/**
 * Indicates that the BIO is a <tt>NULL</tt> filter BIO. It does not filter
 * the data read from/written to the next BIO on the BIO stack, but is used
 * to retain the current state of the BIO.
 */
#define BIO_TYPE_NULL_FILTER        (17 | BIO_TYPE_FILTER)

#define BIO_TYPE_NBIO_TEST          (16 | BIO_TYPE_FILTER)
#define BIO_TYPE_DNBIO_TEST         (18 | BIO_TYPE_FILTER)

#ifndef NO_SOCK

/**
 * Indicates that the BIO is a Secure Socket Layer (SSL) filter BIO.
 */
#define BIO_TYPE_SSL                (7 | BIO_TYPE_FILTER)

/**
 * Indicates that the BIO is a socket source/sink BIO.
 */
#define BIO_TYPE_SOCKET             (5 | BIO_TYPE_SOURCE_SINK | \
                                     BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a socket connect source/sink BIO.
 */
#define BIO_TYPE_CONNECT            (12 | BIO_TYPE_SOURCE_SINK | \
                                     BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a socket accept source/sink BIO.
 */
#define BIO_TYPE_ACCEPT             (13 | BIO_TYPE_SOURCE_SINK | \
                                     BIO_TYPE_DESCRIPTOR)

#define BIO_TYPE_PROXY_CLIENT       (14 | BIO_TYPE_FILTER)
#define BIO_TYPE_PROXY_SERVER       (15 | BIO_TYPE_FILTER)

#define BIO_TYPE_SOCKS4A_CONNECT    (19 | BIO_TYPE_FILTER)

/** Indicates that the BIO is a filter BIO for WTLS operations. */
#define BIO_TYPE_WTLS               (20 | BIO_TYPE_FILTER)

/* BIOs that support datagrams. */
/**
 * Indicates that the BIO is a datagram socket source/sink BIO.
 */
#define BIO_TYPE_DGRAM_SOCKET       (32 | BIO_TYPE_DGRAM | \
                                     BIO_TYPE_SOURCE_SINK| BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a datagram socket connect source/sink BIO.
 */
#define BIO_TYPE_DGRAM_CONNECT      (33 | BIO_TYPE_DGRAM | \
                                     BIO_TYPE_SOURCE_SINK | BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a datagram socket multiplexing
 * source/sink BIO.
 */
#define BIO_TYPE_DGRAM_MUX          (34 | BIO_TYPE_DGRAM | \
                                     BIO_TYPE_SOURCE_SINK | BIO_TYPE_DESCRIPTOR)

/**
 * Indicates that the BIO is a datagram socket multiplexing session
 * source/sink BIO.
 */
#define BIO_TYPE_DGRAM_MUX_SESSION  (35 | BIO_TYPE_DGRAM | \
                                     BIO_TYPE_SOURCE_SINK | BIO_TYPE_DESCRIPTOR)

#endif /* NO_SOCK */
/**
 * @}
 */


/**
 * @defgroup BIO_CTRL_DEF Control Identifiers
 * This section lists the identifiers used in the
 * macros that redefine BIO_ctrl().
 * @ingroup BIO_IDENTIFIER
 *
 * @{
 */
/**
 * Rewinds to the start of input or output and resets the state of the BIO.
 * This is a BIO implementation-dependent action.
 */
#define BIO_CTRL_RESET                1
/**
 * Checks if the BIO has reached the End-of-File (EOF) marker.
 */
#define BIO_CTRL_EOF                2
/**
 * Retrieves extra information from the BIO.
 * This is a BIO implementation-dependent action.
 */
#define BIO_CTRL_INFO                3
/**
 * Sets the BIO I/O type.
 */
#define BIO_CTRL_SET                4
/**
 * Retrieves the BIO I/O type.
 */
#define BIO_CTRL_GET                5
/**
 * An internal control used for BIO stack manipulation.
 */
#define BIO_CTRL_PUSH                6
/**
 * An internal control used for BIO stack manipulation.
 */
#define BIO_CTRL_POP                7
/**
 * Retrieves the state of the BIO shutdown flag used by BIO_free(). <br>
 * See @ref BIO_SHUTDOWN_DEF for valid values.
 */
#define BIO_CTRL_GET_CLOSE        8
/**
 * Sets the state of the BIO shutdown flag used by BIO_free(). <br>
 * See @ref BIO_SHUTDOWN_DEF for valid values.
 */
#define BIO_CTRL_SET_CLOSE        9
/**
 * Checks if there is more data buffered in the BIO be use.
 */
#define BIO_CTRL_PENDING        10
/**
 * Flushes any remaining data from the BIO data buffer.
 */
#define BIO_CTRL_FLUSH                11
/**
 * Extra information to use for a duplicated BIO.
 */
#define BIO_CTRL_DUP                12
/**
 * Retrieves the number of Bytes in the BIO data buffer pending to write.
 */
#define BIO_CTRL_WPENDING        13
/**
 * Sets the BIO callback function.
 */
#define BIO_CTRL_SET_CALLBACK        14
/**
 * Retrieves a pointer to a BIO callback function.
 */
#define BIO_CTRL_GET_CALLBACK        15
/**
 * Sets the file name to be used by the file BIO.
 */
#define BIO_CTRL_SET_FILENAME        30        /* BIO_s_file special */

/* DGRAM session buffer size: */
#define BIO_CTRL_SET_DGRAM_BUFFER 64
#define BIO_CTRL_GET_DGRAM_BUFFER 65

#define BIO_CTRL_SET_DGRAM_PEER          66  /* opt - set the peer */
#define BIO_CTRL_GET_DGRAM_PEER          67  /* opt - get the peer */
#define BIO_CTRL_SET_DGRAM_AUTO_CONNECT  68  /* opt - set auto-connect mode */
#define BIO_CTRL_GET_DGRAM_AUTO_CONNECT  69  /* opt - get auto-connect mode */
#define BIO_CTRL_GET_CURRENT_SESSION     70  /* opt - get current session */
#define BIO_CTRL_SET_CURRENT_SESSION     71  /* opt - set current session */
#define BIO_CTRL_GET_NETWORK_TYPE        72  /* opt - get the network type */
#define BIO_CTRL_DELETE_CURRENT_SESSION  73  /* opt - delete current session */

/**
 * @}
 */

/* Network types */
#define BIO_NETWORK_TYPE_PACKET           1
#define BIO_NETWORK_TYPE_STREAM           2

/* modifiers */
#define BIO_FP_READ                 0x02
#define BIO_FP_WRITE                0x04
#define BIO_FP_APPEND               0x08
#define BIO_FP_TEXT                 0x10
#define BIO_FP_NO_SETMODE           0x20

/**
 * @defgroup BIO_SHUTDOWN_DEF Shutdown Identifiers
 * This section lists the valid BIO shutdown identifiers that may be set on
 * the <tt>shutdown</tt> field in the #BIO. These identifiers
 * indicate whether or not to close the I/O stream on BIO_free().
 * @ingroup BIO_IDENTIFIER
 * @{
 */
/* BIO_FILENAME_READ|BIO_CLOSE to open or close on free.
 * BIO_set_fp(in,stdin,BIO_NOCLOSE); */
/**
 * Indicates not to close the I/O stream on BIO_free().
 * Set on the <tt>shutdown</tt> field in the #BIO.
 */
#define BIO_NOCLOSE         0x00
/**
 * Indicates to close the I/O stream on BIO_free().
 * Set on the <tt>shutdown</tt> field in the #BIO.
 */
#define BIO_CLOSE           0x01
/**
 * @}
 */

/**
 * @defgroup BIO_FLAGS_DEF Flag Identifiers
 * This section lists the valid #BIO flag identifiers that may be set on
 * the <tt>flags</tt> field in the #BIO. These identifiers
 * indicate the current state of the #BIO.
 * @ingroup BIO_IDENTIFIER
 * @{
 */
/**
 * Indicates that the #BIO has data to read.
 */
#define BIO_FLAGS_READ                        0x01
/**
 * Indicates that the #BIO has data to write.
 */
#define BIO_FLAGS_WRITE                 0x02
/**
 * Indicates that the #BIO performs custom socket I/O. This flag is used
 * in conjunction with #BIO_FLAGS_READ and #BIO_FLAGS_WRITE.
 */
#define BIO_FLAGS_IO_SPECIAL                0x04
/**
 * Indicates a combination of #BIO_FLAGS_READ, #BIO_FLAGS_WRITE and
 * #BIO_FLAGS_IO_SPECIAL.
 */
#define BIO_FLAGS_RWS (BIO_FLAGS_READ|BIO_FLAGS_WRITE|BIO_FLAGS_IO_SPECIAL)
/**
 * Indicates whether a retry on write or read should be attempted for the
 * #BIO. This flag is used in conjunction with #BIO_FLAGS_READ and
 * #BIO_FLAGS_WRITE.
 */
#define BIO_FLAGS_SHOULD_RETRY                0x08
/**
 * Indicates that the #BIO should flush the data buffer on the write
 * operation.
 */
#define BIO_FLAGS_FLUSH_ON_WRITE        0x10
/**
 * Indicates that there is no more data in the message.
 */
#define BIO_FLAGS_EOM                   0x20
/**
 * @}
 */

/* Mostly used in the SSL BIO */
/* No longer in use
 * #define BIO_FLAGS_PROTOCOL_DELAYED_READ 0x10
 * #define BIO_FLAGS_PROTOCOL_DELAYED_WRITE 0x20
 * #define BIO_FLAGS_PROTOCOL_STARTUP        0x40
 */

#define BIO_FLAGS_BASE64_NO_NL        0x100

typedef struct bio_ctrl_peer_param_st
{
    char *peer;
    int  peer_len;
} BIO_CTRL_PEER_PARAM;


#ifdef SSLEAY_MACROS
#define BIO_set_flags(bio, f)   ((bio)->flags |= (f))

#define BIO_get_flags(bio)      ((bio)->flags)

#define BIO_set_retry_special(bio) \
               ((bio)->flags |= (BIO_FLAGS_IO_SPECIAL | BIO_FLAGS_SHOULD_RETRY))

#define BIO_set_retry_read(bio) \
               ((bio)->flags |=( BIO_FLAGS_READ | BIO_FLAGS_SHOULD_RETRY))

#define BIO_set_retry_write(bio) \
               ((bio)->flags |= (BIO_FLAGS_WRITE | BIO_FLAGS_SHOULD_RETRY))

/* These are normally used internally in BIOs */
#define BIO_clear_flags(bio, nflags)    ((bio)->flags &= ~(nflags))

#define BIO_clear_retry_flags(bio) \
                ((bio)->flags &= ~(BIO_FLAGS_RWS | BIO_FLAGS_SHOULD_RETRY))

#define BIO_get_retry_flags(bio) \
                ((bio)->flags & (BIO_FLAGS_RWS | BIO_FLAGS_SHOULD_RETRY))

/* These should be used by the application to tell why we should retry */
#define BIO_should_read(bio)            ((bio)->flags & BIO_FLAGS_READ)

#define BIO_should_write(bio)           ((bio)->flags & BIO_FLAGS_WRITE)

#define BIO_should_io_special(bio)      ((bio)->flags & BIO_FLAGS_IO_SPECIAL)

#define BIO_retry_type(bio)             ((bio)->flags & BIO_FLAGS_RWS)

#define BIO_should_retry(bio)           ((bio)->flags & BIO_FLAGS_SHOULD_RETRY)


#define BIO_set_cb(bio, cb)             ((bio)->callback=(cb))

#define BIO_set_cb_arg(bio,arg)         ((bio)->cb_arg=(char *)(arg))

#define BIO_get_cb_arg(bio)             ((bio)->cb_arg)

#define BIO_get_cb(bio)                 ((bio)->callback)


#define BIO_method_name(bio)            ((bio)->method->name)

#define BIO_method_type(bio)            ((bio)->method->type)

#endif /* SSLEAY_MACROS */

/**
 * @defgroup BIO_RR_IDS Retry Reason Identifiers
 * This section lists the identifiers used in conjunction
 * with BIO_should_io_special().
 * After this function returns true, BIO_get_retry_BIO() walks the BIO
 * stack and returns the reason for the special and the offending #BIO.
 * Given a #BIO, BIO_get_retry_reason() returns the retry reason code.
 * @ingroup BIO_IDENTIFIER
 *
 * @{
 */
 #ifndef NO_SSL
/**
 * Returned from the SSL #BIO if the certificate retrieval code has an
 * error.
 */
#define BIO_RR_SSL_X509_LOOKUP                0x01
#endif /* NO_SSL */
/**
 * Returned from the connect #BIO when a connect would have been blocked.
 */
#define BIO_RR_CONNECT                                0x02
/**
 * Returned from the accept #BIO. This is usually an indication of an
 * interruption.
 */
#define BIO_RR_ACCEPT                                0x03
/**
 * @}
 */

/**
 * @defgroup BIO_CB_DEF Callback Identifiers
 * This section lists the identifiers passed by the #BIO callback to
 * indicate which function initiated the callback.
 * @ingroup BIO_IDENTIFIER
 *
 * @{
 */

/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_free().
 */
#define BIO_CB_FREE         0x01


/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_read().
 */
#define BIO_CB_READ         0x02

/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_write().
 */
#define BIO_CB_WRITE        0x03

/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_puts().
 */
#define BIO_CB_PUTS         0x04

/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_gets().
 */
#define BIO_CB_GETS         0x05

/**
 * Indicates that the #BIO callback function was called during an
 * execution of BIO_ctrl().
 */
#define BIO_CB_CTRL         0x06

/**
 * Used to mask the function number of the command.
 */
#define BIO_CB_FUNC_MASK    0x7f

/**
 * Indicates that the #BIO callback function was called after the
 * execution of the underlying operation, rather than before.
 * The #BIO callback is usually executed both before and after the
 * underlying operation. This flag is used in conjunction with the other
 * @ref BIO_CB_DEF.
 */
#define BIO_CB_RETURN         0x80
/**
 * @fn int BIO_CB_return(int state)
 *
 * Sets the return part of the callback command.
 *
 * @param  state  [In]  The callback command.
 *
 * @note  The return flag indicates that the callback function is being
 *        invoked after the method table call and on return.
 *
 * @see   BIO_cb_pre() and BIO_cb_post().
 */
#define BIO_CB_return(state)      ((state) | BIO_CB_RETURN))

/**
 * @fn int BIO_cb_pre(int state)
 *
 * Indicates whether the #BIO callback was called before the specified
 * state.
 *
 * @param  state  [In]  The callback command.
 *
 * @see   BIO_CB_return() and BIO_cb_post().
 */
#define BIO_cb_pre(state)         (!((state) & BIO_CB_RETURN))
/**
 * @fn int BIO_cb_post(int state)
 *
 * Indicates whether the #BIO callback was called after the specified
 * state.
 *
 * @param  state  [In]  The callback command.
 *
 * @see   BIO_CB_return() and BIO_cb_pre().
 */
#define BIO_cb_post(state)        ((state) & BIO_CB_RETURN)

/* End defgroup BIO_CB_DEF */
/**
 * @}
 */


/**
 * @defgroup BIO_CB_TYPE Callback Types
 * This section documents the type of callback functions that can be set against
 * a #BIO.
 * @ingroup BIO_IDENTIFIER
 * @{
 */

/**
 * This is the standard callback function. It is called every time a #BIO
 * function is invoked. For reading and writing the callback is invoked both
 * before and after the implementation-dependent method is called.
 *
 * @see BIO_CB_FUNC_T().
 */
#define BIO_CB_TYPE_FUNC            0
/**
 * This is the information callback for connections. The callback is invoked
 * whenever the state machine ticks over.
 *
 * @see BIO_CB_FUNC_T().
 */
#define BIO_CB_TYPE_INFO            1
/**
 * This is the state callback. The callback is invoked whenever the state
 * changes in a #BIO.
 *
 * @see BIO_STATE_CB_FUNC_T().
 */
#define BIO_CB_TYPE_STATE           2

/**
 * @}
 */

/**
 * @defgroup BIO_ALL_FUNCS Input/Output Functions
 * This section documents the functions that enable the #BIO
 * functionality, including descriptions of the callback, file, allocation and
 * de-allocation functions which enable the writing and manipulation of BIOs.
 * @ingroup BIO_GROUP
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup BIO_CB_FN Callback Functions
 * This section documents the functions provided for the utilization of
 * user-defined callback routines to execute in BIO operations.
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
/**
 * Used for creating user-defined debugging routines or surrender functions.
 * The command value is a bit-wise combination of a command flag and a timing
 * flag value. The command value is dependent upon the #BIO command. The
 * timing value #BIO_CB_RETURN is included if the callback is invoked
 * after the #BIO method.
 *
 * @param bio    [In] A reference to the #BIO.
 * @param cmd    [In] The #BIO command identifier.
 * @param argp   [In] A pointer argument used for arbitrary data.
 * @param argi   [In] The integer argument.
 * @param argl   [In] The long argument.
 * @param ret    [In] The status of the current operation on the #BIO.
 * @return 1 indicates success.<br>
 *         Otherwise indicates error.
 *
 * @see BIO_get_cb(), BIO_set_cb_arg(), BIO_set_bio_cb(), BIO_get_cb_arg() and
 *      BIO_set_cb().
 */
typedef long BIO_CB_FUNC_T(BIO *bio, int cmd, char *argp, int argi,
                          long argl, long ret);
/** Deprecated name for the BIO callback type. */
typedef long R_BIO_CB_FUNC_T(BIO *bio, int cmd, char *argp, int argi,
                          long argl, long ret);

/**
 * The type of callback function that reports on the BIO state.
 *
 * @param   bio     [In]  A #BIO reference.
 * @param   type    [In]  The type of #BIO.
 * @param   state   [In]  The current #BIO state.<br>
 * @param   ret     [In]  The current success flag. One of:<br>
 *                        <li>-1 indicates an error occurred.</li>
 *                        <li>0 indicates end of file.</li>
 *                        <li>>0 indicates number of Bytes read.</li>
 * @param   flag    [In]  The current flags associated with the error.
 * @param   cb_arg  [In]  The user callback argument.
 *
 * @return  1 indicates success.<br>
 *          0 indicates error.
 */
typedef int BIO_STATE_CB_FUNC_T(BIO *bio, int type, int state, int ret,
                                int flag, char *cb_arg);

/**
 * The type used to hold the state callback and its user-defined argument for
 * transportation.
 */
typedef struct bio_state_cb_st
{
    /**
     * The callback function.
     */
    BIO_STATE_CB_FUNC_T *cb;
    /**
     * The user-defined callback argument.
     */
    void *cb_arg;
} BIO_STATE_CB;

/**
 * @}
 */

/**
 * This structure stores the data that is required to perform initialization
 * on a new BIO that was created from the resource list.
 */
typedef struct bio_init_st
{
    /**
     * The library context from which to obtain resources.
     */
    R_LIB_CTX *lib_ctx;

    /**
     * The flag indicating scope.<br>
     * See @ref RES_FLAG for valid values.
     */
    int flag;

    /**
     * The BIO type specific data to initialize with.
     */
    void *value;
} BIO_INIT;

/**
 * This structure stores pointers to functions that implement the #BIO
 * methods. Each #BIO has seven methods. A <tt>NULL</tt> pointer indicates
 * that the method is not implemented. <br>
 * The methods define the behavior of an individual #BIO type, and are
 * called directly by the #BIO access functions. The methods modify the
 * general #BIO behavior by replacing it with the specific behavior for
 * the #BIO sub-class.
 */
typedef struct bio_method_st
{
    /**
     * The numeric identifier for the #BIO_METHOD containing bits for the
     * general/class and specific/instance.
     */
    int type;

    /**
     * The string identifier corresponding to the type.
     *        @see BIO_method_name().
     */
    char *name;

#if defined(MS_CALLBACK) || defined(MS_FAR)
    int (MS_FAR *bwrite)(BIO *bio,char *buf,int len);
    int (MS_FAR *bread)(BIO *bio,char *buf,int len);
    int (MS_FAR *bputs)(BIO *bio,char *buf);
    int (MS_FAR *bgets)(BIO *bio,char *buf, int len);
    long (MS_FAR *ctrl)(BIO *bio,int argi,long argl,char *argp);
    int (MS_FAR *create)(BIO *bio);
    int (MS_FAR *destroy)(BIO *bio);
#else /* !(defined(MS_CALLBACK) || defined(MS_FAR)) */
    /** The method for writing a number of Bytes from a buffer. */
    int (*bwrite)(BIO *bio,char *buf,int len);

    /** The method for reading Bytes into a buffer. */
    int (*bread)(BIO *bio,char *buf,int len);

    /** The special write method. */
    int (*bputs)(BIO *bio,char *buf);

    /** The special read method. */
    int (*bgets)(BIO *bio,char *buf, int len);

    /**
     * A general object control allowing object functionality in addition
     * to read/write and create/destroy operations.
     */
    long (*ctrl)(BIO *bio,int argi,long argl,char *argp);

    /**
     * The method for creating a #BIO instance (including setting values
     * and allocating context memory).
     */
    int (*create)(BIO *bio);

    /**
     * The method for freeing an instance. The shutdown flag is checked to
     * determine whether the instance state (for example, underlying file
     * descriptors) should also be closed.
     */
    int (*destroy)(BIO *bio);
#endif /* !(defined(MS_CALLBACK) || defined(MS_FAR)) */
} BIO_METHOD;

/**
 * This structure contains the data and #BIO method structure.
 */
struct bio_st
{
    /** A pointer to the structure with the BIO method functions. */
    BIO_METHOD *method;

    /**
     * The user-defined callback called before and after method functions when
     * accessed through the <tt>BIO_xxx</tt> functions.
     *
     * @param  bio  [In]  A reference to the #BIO.
     * @param  mode [In]  The bit field which gives the function and the
     *                    return flag.
     * @param  argp [In]  The general pointer value for the callback.
     * @param  argi [In]  The general integer value for the callback.
     * @param  argl [In]  The general long value for the callback.
     * @param  ret  [In]  The current return status of the method.
     */
    BIO_CB_FUNC_T *callback;

    /** A pointer to user-supplied data for the callback function. */
    char *cb_arg; /* first argument for the callback */

    /**
     * The flag indicating whether the BIO is correctly initialized. <br>
     * This flag must be set before the <tt>bread</tt>, <tt>bwrite</tt>,
     * <tt>bgets</tt>, and <tt>bputs</tt> methods will work.<br>
     *
     * 0 indicates BIO is not initialized. 1 indicates BIO is initialized.
     */
    int init;

    /**
     * The flag indicating whether the underlying connection, such as a socket,
     * should be closed when the BIO is freed. <br>
     * See @ref BIO_SHUTDOWN_DEF for valid values.
     */
    int shutdown;

    /** A bit field storing values for the BIO state. */
    int flags;

    /** The reason behind a retry of read or write. */
    int retry_reason;

    /** An integer field for BIO data. */
    int num;

    /**
     * A pointer for BIO data. May be a single value or a local
     * context structure.
     */
    char *ptr;

    /**
     * The next BIO in the stack (that is, one element lower).
     * This is used by filter BIOs.
     */
    struct bio_st *next_bio;

    /**
     * The previous BIO in the stack (that is, one element higher).
     * This is used by filter BIOs.
     */
    struct bio_st *prev_bio;        /* used by filter BIOs */

    /**
     * The number of references to this BIO. This value is decremented by
     * free. If the value becomes 0, the structure is also removed.
     */
    int references;

    /** The number of Bytes read by the BIO. */
    unsigned long num_read;

    /** The number of Bytes written by the BIO. */
    unsigned long num_write;

    /** A pointer to external data. */
    CRYPTO_EX_DATA *ex_data;
};

/* connect BIO information */
#define BIO_CONN_S_BEFORE               1
#define BIO_CONN_S_GET_IP               2
#define BIO_CONN_S_GET_PORT             3
#define BIO_CONN_S_CREATE_SOCKET        4
#define BIO_CONN_S_CONNECT              5
#define BIO_CONN_S_OK                   6
#define BIO_CONN_S_BLOCKED_CONNECT      7
#define BIO_CONN_S_NBIO                 8

/* socks4a BIO information */
#define BIO_SOCKS4A_S_BEFORE                 1
#define BIO_SOCKS4A_S_GET_IP_AND_PORT        2
#define BIO_SOCKS4A_S_SETUP_CONNECT          3
#define BIO_SOCKS4A_S_CONNECT                4
#define BIO_SOCKS4A_S_READ_RESPONSE          5
#define BIO_SOCKS4A_S_OK                     6

#define BIO_number_read(bio)        ((bio)->num_read)
#define BIO_number_written(bio)     ((bio)->num_write)

#define BIO_C_SET_CONNECT                        100
#define BIO_C_DO_STATE_MACHINE                   101
#define BIO_C_SET_NBIO                           102
#define BIO_C_SET_PROXY_PARAM                    103
#define BIO_C_SET_FD                             104
#define BIO_C_GET_FD                             105
#define BIO_C_SET_FILE_PTR                       106
#define BIO_C_GET_FILE_PTR                       107
#define BIO_C_SET_FILENAME                       108
#define BIO_C_SET_SSL                            109
#define BIO_C_GET_SSL                            110
#define BIO_C_SET_MD                             111
#define BIO_C_GET_MD                             112
#define BIO_C_GET_CIPHER_STATUS                  113
#define BIO_C_SET_BUF_MEM                        114
#define BIO_C_GET_BUF_MEM_PTR                    115
#define BIO_C_GET_BUFF_NUM_LINES                 116
#define BIO_C_SET_BUFF_SIZE                      117
#define BIO_C_SET_ACCEPT                         118
#define BIO_C_SSL_MODE                           119
#define BIO_C_GET_MD_CTX                         120
#define BIO_C_GET_PROXY_PARAM                    121

/* data to read first */
#define BIO_C_SET_BUFF_READ_DATA                 122

#define BIO_C_GET_CONNECT                        123
#define BIO_C_GET_ACCEPT                         124
#define BIO_C_SET_SSL_RENEGOTIATE_BYTES          125
#define BIO_C_GET_SSL_NUM_RENEGOTIATES           126
#define BIO_C_SET_SSL_RENEGOTIATE_TIMEOUT        127
#define BIO_C_FILE_SEEK                          128
#define BIO_C_GET_CIPHER_CTX                     129

/* return end of input value */
#define BIO_C_SET_BUF_MEM_EOF_RETURN             130

#define BIO_C_SET_BIND_MODE                      131
#define BIO_C_GET_BIND_MODE                      132
#define BIO_C_FILE_TELL                          133
#define BIO_C_GET_SOCKS                          134
#define BIO_C_SET_SOCKS                          135
#define BIO_C_OPEN_FILE                          136
#define BIO_C_SET_WTLS                           137
#define BIO_C_GET_WTLS                           138
#define BIO_C_SET_WTLS_RENEGOTIATE_BYTES         139
#define BIO_C_GET_WTLS_NUM_RENEGOTIATES          140
#define BIO_C_SET_WTLS_RENEGOTIATE_TIMEOUT       141
#define BIO_C_WTLS_MODE                          142

/**
 * Perform processing to prepare for the next message.
 */
#define BIO_C_NEXT_MSG                           143
/**
 * Set the store context against the #BIO filter.
 */
#define BIO_C_SET_STORE                          144
/**
 * Set the verification context against the #BIO filter.
 */
#define BIO_C_SET_VFY_CTX                        145
/**
 * Set the #R_EITEMS against the #BIO filter.
 */
#define BIO_C_SET_EITEMS                         146
/**
 * Set the context for further operations against the #BIO filter.
 */
#define BIO_C_SET_CTX                            147
/**
 * Set the OP program code against the #BIO filter.
 */
#define BIO_C_SET_CODE                           148

/**
 * Set the state callback and argument against the #BIO filter.
 */
#define BIO_C_SET_STATE_CB                       149
/**
 * Retrieve the state callback and argument from the #BIO filter.
 */
#define BIO_C_GET_STATE_CB                       150
/**
 * Indicate that all the data has been written and any post-processing should
 * start and/or trailing data should now be put out.
 */
#define BIO_C_END_OF_MSG                         151
/**
 * Obtain the string corresponding to the state value passed.
 */
#define BIO_C_STATE_STRING                       152
/**
 * Set the padding method for a cipher BIO.
 */
#define BIO_C_SET_PADDING_MODE                   153
/**
 * Set the private asymmetric key for a cryptographic message BIO.
 * This asymmetric key is used to decrypt the symmetric key which
 * encrypts the enveloped data content.
 */
#define BIO_C_SET_ASYM_KEY                       154
/**
 * Set the certificate of a recipient for a cryptographic message BIO.
 * The certificate is used to determine the recipient index in the
 * header of a PKCS#7 enveloped message.
 */
#define BIO_C_SET_CERT                           155
/**
 * Set the ID of the encryption algorithm used in encrypting the content
 * data of an enveloped message.
 */
#define BIO_C_SET_ALG_ID                         156
/**
 * Get the parameters of the cryptographic algorithm.
 */
#define BIO_C_GET_PARAMS                         157
/**
 * Set the size (length) of the key.
 */
#define BIO_C_SET_KEY_SIZE                       158
/**
 * Set the effective key bits.
 */
#define BIO_C_SET_EFF_BITS                       159
/**
 * Set the number of rounds.
 */
#define BIO_C_SET_NO_ROUNDS                      160
/**
 * Set whether the cryptographic message is wrapped.
 */
#define BIO_C_SET_WRAPPED                        161
/**
 * Set the content type of the cryptographic message.
 */
#define BIO_C_SET_CONTENT_TYPE                   162
/**
 * Sets the operation callback and argument against the cryptographic message
 * BIO.
 */
#define BIO_C_SET_OP_CB                          163
/**
 * Initialize the BIO with the data passed in.
 */
#define BIO_C_INIT                               200

/* format defines for BIO_dump_format */
/**
 * Format the output of each Byte as two hexadecimal characters.
 */
#define BIO_DUMP_FORMAT_HEX                   0
/**
 * Format the output of each Byte as <tt>'0x'</tt> (<tt>zero-small-x</tt>),
 * followed by two hexadecimal characters.
 */
#define BIO_DUMP_FORMAT_HEX_PREFIX            1

/**
 * @defgroup BIO_STRUCT_FN Structure Functions
 * This section documents the functions that facilitate the
 * #BIO structure.
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
/**
 * @fn int BIO_set_app_data(BIO *bio, char *data)
 *
 * Sets the application data against the #BIO.
 *
 * @param   bio   [In]  The #BIO against which to set.
 * @param   data  [In]  The application data.
 * @return              1 indicates success.<br>
 *                      0 indicates error.
 *
 * @see  BIO_get_app_data(), BIO_set_ex_data() and BIO_get_ext_data().
 */
#define BIO_set_app_data(s,arg)     BIO_set_ex_data(s,0,(char *)arg)

/**
 * @fn char *BIO_set_app_data(BIO *bio, char *data)
 *
 * Retrieves the application data from the #BIO.
 *
 * @param   bio   [In]  The #BIO from which to retrieve the data.
 * @return              The application data.
 *
 * @see  BIO_set_app_data(), BIO_set_ex_data() and BIO_get_ext_data().
 */
#define BIO_get_app_data(s)         BIO_get_ex_data(s,0)

int BIO_get_ex_num(BIO *bio);
int BIO_set_ex_data(BIO *bio,int idx,char *data);
char *BIO_get_ex_data(BIO *bio,int idx);
void BIO_set_ex_free_func(BIO *bio,int idx,void (*cb)());
int BIO_get_ex_new_index(long argl, char *argp, int (*new_func)(),
        int (*dup_func)(), void (*free_func)());

#if !defined(NO_SOCK)
/* BIO_s_connect() and BIO_s_socks4a_connect() */

/**
 * @fn long *BIO_set_conn_hostname(BIO *bio, char *name)
 *
 * Sets the host name value <i>name</i> for the connection #BIO <i>bio</i>
 * when using a UDP or TCP-based #BIO.
 *
 * @param bio        [In, Out] A reference to the #BIO.
 * @param name       [In]      The host name value, with optional port.
 * @return 1 indicates success. <br>
 *         <= 0 indicates error.
 *
 * @note  This function is only effective if it is used before the
 *        connection is made.
 *
 * @see BIO_get_conn_hostname(), BIO_set_conn_ip(), BIO_set_conn_port()
 *      and BIO_set_conn_int_port().
 */
#define BIO_set_conn_hostname(bio,name) \
                              BIO_ctrl(bio,BIO_C_SET_CONNECT,0,(char *)name)

/**
 * @fn long *BIO_set_conn_port(BIO *bio, char *port)
 *
 * Sets the port value <i>port</i> for the connection #BIO <i>bio</i>.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param port       [In]      The port value.
 * @return  1 indicates success. <br>
 *          <=0 indicates error.
 *
 * @note  This function is only effective if it is used before the
 *        connection is made.
 *
 * @see BIO_get_conn_port(), BIO_set_conn_hostname(), BIO_set_conn_ip()
 *      and BIO_set_conn_int_port().
 */
#define BIO_set_conn_port(bio,port) \
                      BIO_ctrl(bio,BIO_C_SET_CONNECT,1,(char *)port)

/**
 * @fn long *BIO_set_conn_ip(BIO *bio, char *ip)
 *
 * Sets the IP address value <i>ip</i> for the connection #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @param ip   [In]      The IP address value.
 * @return  1 indicates success. <br>
 *          <=0 indicates error.
 *
 * @note  This function is only effective if it is used before the
 *        connection is made.
 *
 * @see BIO_get_conn_ip(), BIO_set_conn_hostname(), BIO_set_conn_port()
 *      and BIO_set_conn_int_port().
 */
#define BIO_set_conn_ip(bio,ip)   BIO_ctrl(bio,BIO_C_SET_CONNECT,2,(char *)ip)

/**
 * @fn long *BIO_set_conn_int_port(BIO *bio, int port)
 *
 * Sets the port value <i>port</i> for the connection #BIO <i>bio</i>.
 *
 * @param bio        [In, Out] A reference to the #BIO.
 * @param port       [In]      The port value. Must be passed as a variable
 *                             (not a constant) for this function to compile
 *                             on Sun platforms.
 * @return  1 indicates success. <br>
 *          <=0 indicates error.
 *
 * @note  This function is only effective if it is used before the
 *        connection is made.<br>
 *
 * @see BIO_get_conn_int_port(), BIO_set_conn_hostname(), BIO_set_conn_ip()
 *      and BIO_set_conn_port().
 */
#define BIO_set_conn_int_port(bio,port) \
                        BIO_ctrl(bio,BIO_C_SET_CONNECT,3,(char *)&port)

/**
 * @fn char *BIO_get_conn_hostname(BIO *bio)
 *
 * Returns a pointer to the host name for the connection #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  A pointer to the host name. <br>
 *          <tt>NULL</tt> indicates error.
 *
 * @note  This function only works for a connect #BIO or a BIO stack
 *        that uses a connect #BIO. All other #BIO types return <tt>NULL</tt>.
 *
 * @see BIO_set_conn_hostname().
 *
 * @eg
 * @include bio_get_conn_hostname.c
 */
#define BIO_get_conn_hostname(bio)        BIO_ptr_ctrl(bio,BIO_C_GET_CONNECT,0)

/**
 * @fn char *BIO_get_conn_port(BIO *bio)
 *
 * Returns the port value for the connection #BIO <i>bio</i> as a string.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  A pointer to the port value. <br>
 *          <tt>NULL</tt> indicates error.
 *
 * @see BIO_set_conn_port().
 */
#define BIO_get_conn_port(bio)            BIO_ptr_ctrl(bio,BIO_C_GET_CONNECT,1)

/**
 * @fn char *BIO_get_conn_ip(BIO *bio)
 *
 * Returns the IP address for the connection #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  A pointer to the IP address.<br>
 *          <tt>NULL</tt> indicates error.
 *
 * @see BIO_set_conn_ip().
 */
#define BIO_get_conn_ip(bio)              BIO_ptr_ctrl(bio,BIO_C_GET_CONNECT,2)

/**
 * @fn long BIO_get_conn_int_port(BIO *bio, char *portp)
 *
 * Returns the port number for the connection #BIO <i>bio</i>.
 *
 * @param bio    [In]   A reference to the #BIO.
 * @param portp  [Out]  A pointer to the port value.
 * @return  1 indicates success.<br>
 *         -1 indicates error.
 *
 * @see BIO_set_conn_int_port() and BIO_get_conn_port().
 *
 * @eg
 * @include bio_get_conn_int_port.c
 */
#define BIO_get_conn_int_port(bio,portp) \
                                 BIO_ctrl(bio,BIO_C_GET_CONNECT,3,(char *)portp)

/* BIO_s_socks4a_connect() also uses */
#define BIO_set_socks_userid(bio,user)      BIO_ctrl(bio,BIO_C_SET_SOCKS,1,user)
#define BIO_get_socks_userid(bio,user)      BIO_ptr_ctrl(bio,BIO_C_GET_SOCKS,1)

/**
 * @fn long BIO_set_nbio(BIO *bio, int nb_flag)
 *
 * Sets to blocking or non-blocking I/O of the underlying connection
 * #BIO <i>bio</i>.
 *
 * This function is only valid for connect BIOs and accept BIOs
 * (that is, created via BIO_new_accept() or BIO_new_connect()).
 * It is not valid for socket BIOs (that is,
 * created via BIO_new_socket()). In order to make a normal socket
 * #BIO be non-blocking, the socket must be non-blocking before it
 * is attached to a #BIO.
 *
 * @param bio             [In, Out]  A reference to the #BIO.
 * @param nb_flag         [In]      The blocking flag. One of:
 *                 <li>1 sets to non-blocking I/O.</li>
 *                 <li>0 sets to blocking I/O.</li>
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_new_accept(), BIO_new_connect() and BIO_new_socket().
 */
#define BIO_set_nbio(bio,nb_flag) BIO_ctrl(bio,BIO_C_SET_NBIO,(nb_flag),NULL)

/**
 * @fn char *BIO_set_accept_port(BIO *bio, char *name)
 *
 * Sets the port information for the accept socket of the server.
 *
 * @param bio  [In, Out]  A reference to the #BIO that will be used to
 *                        accept connections on the port described by
 *                        <i>name</i>.
 * @param name [In]       A <tt>NULL</tt> character string representing the
 *                        port on which to accept connections.
 *
 * @return   1  indicates success.<br>
 *           <=0 indicates error.
 *
 */
#define BIO_set_accept_port(bio,name) \
                                   BIO_ctrl(bio,BIO_C_SET_ACCEPT,0,(char *)name)

/**
 * @fn char * BIO_get_accept_port(BIO *bio)
 *
 * Returns the port information for the accept socket of the server.
 *
 * @param    bio  [In, Out]  A reference to the accept #BIO.
 * @return   The accept port of the #BIO<br>
 *           <tt>NULL</tt> indicates otherwise.
 *
 */
#define BIO_get_accept_port(bio)   BIO_ptr_ctrl(bio,BIO_C_GET_ACCEPT,0)

/**
 * @fn long BIO_set_nbio_accept(BIO *accept_bio, int nb_flag)
 *
 * Sets to blocking or non-blocking I/O of the
 * underlying connection #BIO <i>bio</i>. This function is only valid for
 * accept BIOs (that is, created via BIO_new_accept()). It is not valid
 * for socket BIOs or connect BIOs (that is, created via BIO_new_socket()
 * or BIO_new_connect()).
 *
 * @param accept_bio [In, Out]  A reference to the accept #BIO.
 * @param nb_flag    [In]       The blocking flag. One of:<br>
 *                              <li>1 sets to non-blocking I/O.</li>
 *                              <li>0 sets to blocking I/O.</li>
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_new_accept(), BIO_set_nbio().
 */
#define BIO_set_nbio_accept(bio, nb_flag) \
    BIO_ctrl(bio,BIO_C_SET_ACCEPT,1,(nb_flag)?"a":NULL)

/**
 * @fn long BIO_set_accept_bios(BIO *accept_bio, BIO *template_bio)
 *
 * Sets the template #BIO <i>template_bio</i> that is automatically
 * duplicated when a successful connection occurs on <i>accept_bio</i>.
 *
 * @param accept_bio        [In, Out]  A reference to the accept #BIO.
 * @param template_bio      [In]      A reference to the template #BIO.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_new_accept() and BIO_do_accept().
 */
#define BIO_set_accept_bios(accept_bio,template_bio) \
                    BIO_ctrl(accept_bio,BIO_C_SET_ACCEPT,2,(char *)template_bio)

/* Mode needs to come from sio.h */

/**
 * @fn long BIO_set_bind_mode(BIO *bio, int mode)
 *
 * Sets the relevant TCP/IP flag allowing a socket to be re-bound.
 * The #BIO is <i>bio</i> with a bind mode of <i>mode</i>.
 * This is used when restarting the application after a socket
 * shutdown did not execute cleanly.
 *
 * @param bio         [In, Out]  A reference to the #BIO.
 * @param mode        [In]       The bind mode. One of:<br>
 *        <table>
 *        <tr>
 *        <td><b>Mode</b></td>
 *        <td><b>Description</b></td>
 *        </tr>
 *        <tr>
 *        <td>#BIO_BIND_NORMAL</td>
 *        <td>Indicates no special mode. </td>
 *        </tr>
 *        <tr>
 *        <td>#BIO_BIND_REUSEADDR</td>
 *        <td>Indicates to set the reuse address flag.</td>
 *        </tr>
 *        </table>
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_get_bind_mode().
 */
#define BIO_set_bind_mode(bio,mode) BIO_ctrl(bio,BIO_C_SET_BIND_MODE,mode,NULL)

/**
 * @fn long BIO_get_bind_mode(BIO *bio)
 *
 * Returns the relevant TCP/IP flag for the #BIO <i>bio</i>
 * indicating whether a socket can be re-bound. This
 * function is used when restarting the application after a socket
 * shutdown did not execute cleanly. It should only be used for accept BIOs.
 *
 * @param bio  [In]  A reference to the #BIO.<br>
 * @return  The bind mode. One of:<br>
 *         <table>
 *         <tr>
 *         <td><b>Mode</b></td>
 *         <td><b>Description</b></td>
 *         </tr>
 *         <tr>
 *         <td>#BIO_BIND_NORMAL</td>
 *         <td>Indicates no special mode (default). </td>
 *         </tr>
 *         <tr>
 *         <td>#BIO_BIND_REUSEADDR</td>
 *         <td>Indicates to set the reuse address flag.</td>
 *         </tr>
 *         </table>
 *
 * @see BIO_set_bind_mode() and BIO_new_accept().
 */
#define BIO_get_bind_mode(bio)         BIO_ctrl(bio,BIO_C_GET_BIND_MODE,0,NULL)


/**
 * @fn int BIO_do_connect(BIO *bio)
 *
 * Sets up a client side connection socket on the connect #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return                1 indicates success. <br>
 *                        <=0 indicates the socket has closed.<br>
 *                        -1 indicates non-blocking return if the socket is
 *                        set as non-blocking.
 *
 * @see BIO_new_accept() and BIO_seek().
 *
 * @eg
 * @include bio_do_connect.c
 */
#define BIO_do_connect(bio) BIO_do_handshake(bio)

/**
 * @fn int BIO_do_accept(BIO *bio)
 *
 * Sets up a service side socket that accepts an incoming socket connection on
 * the accept #BIO <i>bio</i>. There is no type checking on the #BIO when
 * BIO_do_accept() is called. Developers therefore must ensure it is an accept
 * #BIO.<br>
 *
 * After the connection is established, BIO_pop() can be used to retrieve the
 * newly established socket #BIO. The first time BIO_do_accept() is called, it
 * performs any required host name lookups and attempts to bind to the socket.
 * Subsequent successful calls to BIO_do_accept() will return when a socket
 * connection has been established.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return     1 indicates success.<br>
 *             <=0 indicates the socket has closed.<br>
 *             -1 indicates an error condition (including retry).
 *
 * @see BIO_new_accept(), BIO_seek() and BIO_pop().
 *
 * @eg
 * @include bio_do_accept.c
 */
#define BIO_do_accept(bio)        BIO_do_handshake(bio)
#define BIO_do_dgram_mux(bio)     BIO_do_handshake(bio)

/**
 * @fn int BIO_do_handshake(BIO *bio)
 *
 * Attempts to perform the next state in a #BIO handshake for BIOs
 * containing state engines.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return     1 indicates success.<br>
 *             <=0 indicates the socket has closed.<br>
 *             -1 indicates possible retry.</td>
 *
 * @eg
 * @include bio_do_handshake.c
 */
#define BIO_do_handshake(bio)        BIO_ctrl(bio,BIO_C_DO_STATE_MACHINE,0,NULL)

/* BIO_s_proxy_client() */
#define BIO_set_url(bio,url) BIO_ctrl(bio,BIO_C_SET_PROXY_PARAM,0,(char *)(url))
#define BIO_set_proxies(bio,p) BIO_ctrl(bio,BIO_C_SET_PROXY_PARAM,1,(char *)(p))
#define BIO_set_filter_bio(bio,s) \
                               BIO_ctrl(bio,BIO_C_SET_PROXY_PARAM,2,(char *)(s))
#define BIO_set_proxy_cb(bio,cb) \
                              BIO_ctrl(bio,BIO_C_SET_PROXY_PARAM,3,(char *)(cb))
#define BIO_set_proxy_header(bio,sk) \
                                BIO_ctrl(bio,BIO_C_SET_PROXY_PARAM,4,(char *)sk)
#define BIO_set_no_connect_return(bio,bool) \
                                  BIO_int_ctrl(bio,BIO_C_SET_PROXY_PARAM,5,bool)

#define BIO_get_proxy_header(bio,skp) \
                               BIO_ctrl(bio,BIO_C_GET_PROXY_PARAM,0,(char *)skp)
#define BIO_get_proxies(bio,pxy_p) \
                           BIO_ctrl(bio,BIO_C_GET_PROXY_PARAM,1,(char *)(pxy_p))
#define BIO_get_url(bio,url) BIO_ctrl(bio,BIO_C_GET_PROXY_PARAM,2,(char *)(url))
#define BIO_get_no_connect_return(bio) \
                                  BIO_ctrl(bio,BIO_C_GET_PROXY_PARAM,5,NULL)


/**
 * @fn long BIO_set_fd(BIO *bio, int fd, int close_flag)
 *
 * Sets the read file descriptor <i>fd</i> to be associated with the #BIO
 * <i>bio</i>.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param fd         [In]      The file descriptor.
 * @param close_flag [In]      The close flag. <br>
 *                             See @ref BIO_SHUTDOWN_DEF for valid values.
 * @return  <= 0 indicates error.
 *
 * @see BIO_get_fd().
 */
#define BIO_set_fd(bio,fd,close_flag) \
                                    BIO_int_ctrl(bio,BIO_C_SET_FD,close_flag,fd)

/**
 * @fn long BIO_get_fd(BIO *bio, char *fd)
 *
 * Retrieves the read file descriptor <i>fd</i> associated with the #BIO
 * <i>bio</i>. The file descriptor is set by a prior call to BIO_set_fd().
 *
 * @param bio  [In]   A reference to the #BIO.
 * @param fd   [Out]  A pointer to the file descriptor.
 * @return  -1 indicates there was no prior BIO_set_fd() call. <br>
 *          Otherwise returns the file descriptor associated with the
 *          #BIO.
 *
 * @note  If the address of an integer variable is passed as an
 *        argument to BIO_get_fd(), the file descriptor is also assigned to
 *        the integer variable. If a <tt>NULL</tt> address is passed as an argument,
 *        it is ignored.
 *
 * @see BIO_set_fd().
 */
#define BIO_get_fd(bio,fd) BIO_ctrl(bio,BIO_C_GET_FD,0,(char *)fd)
#endif /* ! NO_SOCK */
/**
 * @}
 */

/**
 * @defgroup BIO_FILE_FN File Functions
 * This section documents the functions that provide a
 * platform-independent interface for file operations.
 *
 * @note  Not all operating systems support file operations.
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
/**
 * @fn long BIO_set_fp(BIO *bio,char *fp,long flags)
 *
 * Sets the file pointer <i>fp</i> to be used with the #BIO <i>bio</i>.
 *
 * @param bio       [In] A reference to the #BIO.
 * @param fp        [In] A reference to the file pointer.
 * @param flags     [In] The flags to set against the #BIO.
 * @return 1
 */
#define BIO_set_fp(bio,fp,flags) \
                BIO_ctrl(bio,BIO_C_SET_FILE_PTR,flags,(char *)fp)
/**
 * @fn long BIO_get_fp(BIO *bio, char *fp)
 *
 * Returns the file pointer associated with the #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @param fp  [Out]  A reference to the file pointer.<br>
 *                   It cannot be <tt>NULL</tt>.
 * @return 1
 */
#define BIO_get_fp(bio,fp) BIO_ctrl(bio,BIO_C_GET_FILE_PTR,0,(char *)fp)


/**
 * @fn int BIO_seek(BIO *bio, long offset)
 *
 * Moves the current position in the #BIO <i>bio</i>. This is the BIO
 * version of the standard C functions <tt>fseek</tt> and <tt>lseek</tt>.
 * This version only allows an offset from the beginning of a file.
 *
 * @param bio     [In]        A reference to the #BIO.
 * @param offset  [In]        The offset from the start of the #BIO.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @note  This function should only be used with file BIOs.
 *
 * @eg
 * @include bio_seek.c
 */
#define BIO_seek(bio,offset)      (int)BIO_ctrl(bio,BIO_C_FILE_SEEK,offset,NULL)

/**
 * @fn int BIO_tell(BIO *bio)
 *
 * Retrieves the current position in the #BIO <i>bio</i>. This is the BIO
 * version of the standard C <tt>ftell</tt> function.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  >=0 indicates the file offset position.<br>
 *          -1 indicates error.
 *
 * @eg
 * @include bio_tell.c
 */
#define BIO_tell(bio)        (int)BIO_ctrl(bio,BIO_C_FILE_TELL,0,NULL)


/**
 * @fn long BIO_read_filename(BIO *bio,char *name)
 *
 * Opens the file name <i>name</i> for reading on the #BIO <i>bio</i>.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param name       [In]       A reference to the file name.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_write_filename().
 */
#define BIO_read_filename(bio,name) BIO_ctrl(bio,BIO_C_SET_FILENAME, \
                BIO_CLOSE|BIO_FP_READ,name)

/**
 * @fn long BIO_write_filename(BIO *bio, char *name)
 *
 * Opens the file name <i>name</i> for writing on the #BIO <i>bio</i>.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param name       [In]       A reference to the file name.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_read_filename().
 */
#define BIO_write_filename(bio,name) BIO_ctrl(bio,BIO_C_SET_FILENAME, \
                BIO_CLOSE|BIO_FP_WRITE,name)

/**
 * @fn long BIO_append_filename(BIO *bio,char *name)
 *
 * Opens the file name <i>name</i> for writing on the #BIO <i>bio</i>
 * after End-of-File (EOF).
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param name       [In]       A reference to the file name.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_append_filename(bio,name) BIO_ctrl(bio,BIO_C_SET_FILENAME, \
                BIO_CLOSE|BIO_FP_APPEND,name)

/**
 * @fn long BIO_rw_filename(BIO *bio, char *name)
 *
 * Opens the file name <i>name</i> on the #BIO <i>bio</i>
 * for both reading and writing.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param name       [In]       A reference to the file name.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @eg
 * @include bio_rw_filename.c
 */
#define BIO_rw_filename(bio,name) BIO_ctrl(bio,BIO_C_SET_FILENAME, \
                BIO_CLOSE|BIO_FP_READ|BIO_FP_WRITE,name)

/**
 * @}
 */

/* WARNING: This increments the reference count on the read BIO of the
 * SSL structure.  This is because the ssl read BIO is now pointed to by
 * the next_bio field in the BIO.  So when you free the BIO, make sure
 * you are doing a BIO_free_all() to catch the underlying BIO. */

#if !defined(NO_SOCK)
/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
/**
 * @fn long BIO_set_ssl(BIO *bio, SSL *ssl, int close_flag)
 *
 * Sets the #SSL structure <i>ssl</i> for the #BIO <i>bio</i>.
 * The #SSL structure previously set for this #BIO is freed.
 *
 * @param bio        [In, Out] A reference to the #BIO.
 * @param ssl        [In]      A reference to the #SSL connection.
 * @param close_flag [In]      If set to #BIO_CLOSE the #SSL will be freed
 *                             by the call to BIO_free_all().<br>
 *                             If set to #BIO_NOCLOSE the #SSL
 *                             will need to be explicitly freed by the
 *                             caller.<br>
 *                             See @ref BIO_SHUTDOWN_DEF for valid values.
 *
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @note  If the #SSL has a read and write #BIO, then the read #BIO has
 *        its count incremented by this function. Call BIO_free_all() to
 *        free a #BIO that incorporates an #SSL in this manner rather
 *        than BIO_free().
 *
 * @see BIO_set_ssl_mode() and BIO_new_ssl().
 */
#define BIO_set_ssl(bio,ssl,close_flag) \
        BIO_ctrl(bio,BIO_C_SET_SSL,close_flag,(char *)ssl)

/**
 * @fn long BIO_get_ssl(BIO *bio, SSL **sslp)
 *
 * Returns the #SSL structure for the SSL #BIO <i>bio</i>.
 *
 * @param bio         [In]  A reference to the #BIO.
 * @param sslp        [Out] The address of the #SSL reference.
 * @return  1 indicates success.<br>
 *          <=0 indicates error (that is, <tt>ssl_ptr</tt> is <tt>NULL</tt>).
 *
 * @see BIO_set_ssl_mode.
 */
#define BIO_get_ssl(bio,sslp)        BIO_ctrl(bio,BIO_C_GET_SSL,0,(char *)sslp)

/**
 * @fn long BIO_set_ssl_mode(BIO *bio, int client)
 *
 * Sets the connection state client of the #SSL for the #BIO <i>bio</i>.
 *
 * @param bio     [In, Out]  A reference to the #BIO.
 * @param client  [In]       The client flag. One of:<br>
 *                           <li>1 indicates client side #SSL.</li>
 *                           <li>0 indicates server side #SSL.</li>
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_set_ssl(), BIO_new_ssl(), SSL_set_connect_state()
 *      and SSL_set_accept_state().
 */
#define BIO_set_ssl_mode(bio,client)    BIO_ctrl(bio,BIO_C_SSL_MODE,client,NULL)

/**
 * @fn int BIO_set_ssl_renegotiate_bytes(BIO *bio, int num)
 *
 * Sets the number of Bytes that are sent between renegotiations for
 * the #SSL #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @param num  [In]       The number of Bytes.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_set_ssl_renegotiate_timeout().
 */
#define BIO_set_ssl_renegotiate_bytes(bio,num) \
        BIO_ctrl(bio,BIO_C_SET_SSL_RENEGOTIATE_BYTES,num,NULL);
#define BIO_get_num_renegotiates(bio) \
        BIO_ctrl(bio,BIO_C_GET_SSL_NUM_RENEGOTIATES,0,NULL);

/**
 * @fn int BIO_set_ssl_renegotiate_timeout(BIO *bio, int seconds)
 *
 * Sets the renegotiation period for the #SSL #BIO <i>bio</i>. The
 * renegotiation period specifies the elapsed time between renegotiations.
 *
 * @param bio      [In, Out]  A reference to the #BIO.
 * @param seconds  [In]     The renegotiation period.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 *
 * @see BIO_set_ssl_renegotiate_bytes().
 */
#define BIO_set_ssl_renegotiate_timeout(bio,seconds) \
        BIO_ctrl(bio,BIO_C_SET_SSL_RENEGOTIATE_TIMEOUT,seconds,NULL);

#define BIO_set_wtls(bio,wtls,c)     BIO_ctrl(bio,BIO_C_SET_WTLS,c,(char *)wtls)
#define BIO_get_wtls(bio,wtlsp) BIO_ctrl(bio,BIO_C_GET_WTLS,0,(char *)wtlsp)
#define BIO_set_wtls_mode(bio,client) BIO_ctrl(bio,BIO_C_WTLS_MODE,client,NULL)
#define BIO_set_wtls_renegotiate_bytes(bio,num) \
        BIO_ctrl(bio,BIO_C_SET_WTLS_RENEGOTIATE_BYTES,num,NULL);
#define BIO_set_wtls_renegotiate_timeout(bio,seconds) \
        BIO_ctrl(bio,BIO_C_SET_WTLS_RENEGOTIATE_TIMEOUT,seconds,NULL);
/**
 * @}
 */

#endif /* ! NO_SOCK */

/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
#define BIO_get_mem_data(bio,pp)    BIO_ctrl(bio,BIO_CTRL_INFO,0,(char *)pp)
#define BIO_set_mem_buf(bio,bm,c)   BIO_ctrl(bio,BIO_C_SET_BUF_MEM,c,(char *)bm)
#define BIO_get_mem_ptr(bio,pp) BIO_ctrl(bio,BIO_C_GET_BUF_MEM_PTR,0,(char *)pp)
#define BIO_set_mem_eof_return(bio,v) \
                               BIO_ctrl(bio,BIO_C_SET_BUF_MEM_EOF_RETURN,v,NULL)

/**
 * @fn int BIO_get_buffer_num_lines(BIO *bio)
 *
 * Returns the number of lines in buffer #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return  The number of lines in the buffer.<br>
 *         -1 indicates error.
 *
 */
#define BIO_get_buffer_num_lines(bio) \
                                  BIO_ctrl(bio,BIO_C_GET_BUFF_NUM_LINES,0,NULL)
/**
 * @fn int BIO_set_buffer_size(BIO *bio, long size)
 *
 * Sets the buffer size of #BIO <i>bio</i>.
 *
 * @param bio  [In, Out] A reference to the #BIO.
 * @param size [In]      The size of the buffer.
 *
 * @return 1 indicates success.<br>
 *         -1 indicates error.
 *
 */
#define BIO_set_buffer_size(bio,size) \
                                  BIO_ctrl(bio,BIO_C_SET_BUFF_SIZE,size,NULL)
/**
 * @fn int BIO_set_read_buffer_size(BIO *bio, long size)
 *
 * Sets the read buffer size of #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @param size [In]      The size of the read buffer.
 *
 * @return  1 indicates success.<br>
 *         -1 indicates error.
 *
 */
#define BIO_set_read_buffer_size(bio,size) \
                                  BIO_int_ctrl(bio,BIO_C_SET_BUFF_SIZE,size,0)
/**
 * @fn int BIO_set_write_buffer_size(BIO *bio, long size)
 *
 * Sets the write buffer size of #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @param size [In]      The size of the write buffer.
 *
 * @return  1 indicates success.<br>
 *         -1 indicates error.
 *
 */
#define BIO_set_write_buffer_size(bio,size) \
                                  BIO_int_ctrl(bio,BIO_C_SET_BUFF_SIZE,size,1)
/**
 * @fn int BIO_set_buffer_read_data(BIO *bio, char *buf, long num)
 *
 * Sets the buffer read data for #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @param buf  [In]       The data to set.
 * @param num  [In]       The length of <i>buf</i>.
 *
 * @return  1 indicates success.<br>
 *         -1 indicates error.
 *
 */
#define BIO_set_buffer_read_data(bio,buf,num) \
                                  BIO_ctrl(bio,BIO_C_SET_BUFF_READ_DATA,num,buf)

/* Don't use the next one unless you know what you are doing */
#define BIO_dup_state(bio,ret)    BIO_ctrl(bio,BIO_CTRL_DUP,0,(char *)(ret))


/**
 * @fn int BIO_reset(BIO *bio)
 *
 * Resets the #BIO <i>bio</i> to its initial state.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return  1 indicate success.<br>
 *         -1 indicates error.
 *
 * @note  The initial state of a #BIO depends on the type of #BIO. For
 *        example, file BIOs reset pointers to the start of the file.
 *        Connect and accept BIOs reset their state engines.  Socket BIOs
 *        reset the usage of the socket.
 */
#define BIO_reset(bio)             (int)BIO_ctrl(bio,BIO_CTRL_RESET,0,NULL)
/**
 * @fn int BIO_eof(BIO *bio)
 *
 * Retrieves the status whether End-of-File (EOF) has been reached or not,
 * against #BIO <i>bio</i>.
 *
 * @param bio  [In, Out]  A reference to the #BIO.
 * @return  1 indicates the EOF has been reached.<br>
 *         -1 indicates error.
 *
 */
#define BIO_eof(bio)               (int)BIO_ctrl(bio,BIO_CTRL_EOF,0,NULL)
/**
 * @}
 */

/**
 * @defgroup BIO_STATE_FUNC State Operations
 * This section lists the operations used to set or determine the state of the
 * #BIO. <br>
 * The states include:<br>
 * <li>Data pending in buffer for write.</li>
 * <li>Data pending in buffer for read.</li>
 * <li>Data in buffer should retry write.</li>
 * <li>Data not in buffer should retry read.</li>
 * <li>Close I/O device on BIO_free().</li>
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
/**
 * @fn int BIO_set_close(BIO *bio, long mode)
 *
 * Sets the close mode for the #BIO <i>bio</i>. When a #BIO is
 * freed, the underlying file descriptor or pointer is
 * closed/freed depending on this flag. For example, if there is a
 * file pointer #BIO implementing <tt>stdout</tt>, do not
 * close <tt>stdout</tt> when the #BIO is freed. If there is a file pointer
 * #BIO implementing memory, free this memory when the #BIO is freed.
 *
 * @param bio        [In, Out]  A reference to the #BIO.
 * @param mode       [In] The close flag. <br>
 *                    See @ref BIO_SHUTDOWN_DEF for valid values.
 * @return  The close flag. One of:<br>
 *          <li>0 indicates #BIO_NOCLOSE.</li>
 *          <li>1 indicates #BIO_CLOSE.</li>
 *
 * @see BIO_get_close() and @ref BIO_SHUTDOWN_DEF.
 */
#define BIO_set_close(bio,mode) \
                               (int)BIO_ctrl(bio,BIO_CTRL_SET_CLOSE,(mode),NULL)

/**
 * @fn int BIO_get_close(BIO *bio)
 *
 * Returns the close flag for the #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  The close flag. One of:<br>
 *          <li>0 indicates #BIO_NOCLOSE.</li>
 *          <li>1 indicates #BIO_CLOSE.</li>
 *
 * @see BIO_set_close(), BIO_new_fp() and @ref BIO_SHUTDOWN_DEF.
 */
#define BIO_get_close(bio)        (int)BIO_ctrl(bio,BIO_CTRL_GET_CLOSE,0,NULL)

/**
 * @fn int BIO_pending(BIO *bio)
 *
 * Indicates that additional buffered data is available internally
 * for the application to read from the #BIO <i>bio</i>. The remaining
 * Bytes can be read from the internal data buffer without reading any more
 * data from the peer. When using select system calls, BIO_pending() helps the
 * application avoid waiting for data from the peer when it is
 * already available in a local buffer.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_pending(bio)             (int)BIO_ctrl(bio,BIO_CTRL_PENDING,0,NULL)
/**
 * @fn int BIO_wpending(BIO *bio)
 *
 * Indicates that all the data in the buffer has not yet been written. An
 * application can keep flushing the data until this function indicates
 * otherwise.
 *
 * @param bio  [In]  A reference to the #BIO.
 * @return  1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_wpending(bio)            (int)BIO_ctrl(bio,BIO_CTRL_WPENDING,0,NULL)

/**
 * @fn int BIO_flush(BIO *bio)
 *
 * Flushes any data stored in any output buffers of the BIO stack <i>bio</i>.
 *
 * @param bio  [In]  A reference to the BIO stack.
 * @return  1 indicates the BIO stack was flushed.<br>
 *          <= 0 indicates error.
 *
 * @note  Not all BIOs buffer data.
 *
 * @eg
 * @include bio_flush.c
 */
#define BIO_flush(bio)                (int)BIO_ctrl(bio,BIO_CTRL_FLUSH,0,NULL)

/**
 * @fn int BIO_get_info_cb(BIO *bio, char *cbp)
 *
 * Retrieves the information callback set against the #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO against which the callback is
 *                   to be returned.
 * @param cbp  [Out] The callback pointer.
 *
 * @return     1 indicates the callback is returned.<br>
 *             <= 0 indicates error.
 *
 * @see BIO_set_info_cb()
 */
#define BIO_get_info_cb(bio,cbp) \
                        (int)BIO_ctrl(bio,BIO_CTRL_GET_CALLBACK,0,(char *)cbp)
/**
 * @fn int BIO_set_info_cb(BIO *bio, char *cbp)
 *
 * Sets the information callback against #BIO <i>bio</i>.
 *
 * @param bio  [In]  A reference to the #BIO against which the callback is
 *                   to be set.
 * @param cbp  [Out] The callback to be set against <i>bio</i>.
 *
 * @return     1 indicates the callback is set.<br>
 *             <= 0 indicates errors.
 *
 * @see BIO_get_info_cb()
 */
#define BIO_set_info_cb(bio,cbp) \
                        (int)BIO_ctrl(bio,BIO_CTRL_SET_CALLBACK,0,(char *)cbp)

#define BIO_get_network_type(bio) \
                           BIO_ctrl(bio, BIO_CTRL_GET_NETWORK_TYPE, 0, NULL)

/* For the BIO_f_buffer() type */
#define BIO_buffer_get_num_lines(bio) \
                           BIO_ctrl(bio,BIO_C_GET_BUFF_NUM_LINES,0,NULL)

/**
 * @}
 */

/*
 * @defgroup BIO_MSG_FN Message Functions
 * This section documents the functions that facilitate handling of
 * messages within the context of a BIO.
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */

/*
 * @fn int BIO_end_of_msg(BIO *bio)
 *
 * Tells the #BIO that no more data is to be written in this message.
 * As a result, any buffered data is flushed, and any data required to
 * complete the message is written.
 *
 * @param   bio  [In]  A reference to the #BIO.
 * @return  >= 0 indicates the end of message has been handled.<br>
 *          -1 indicates error.
 *
 */
#define BIO_end_of_msg(bio)     (int)BIO_ctrl(bio,BIO_C_END_OF_MSG,0,NULL)

/*
 * @fn long BIO_set_verification(BIO *bio, R_VERIFY_CTX *ctx)
 *
 * Sets the verification context against a #BIO. A verification context is
 * needed for verifying a PKCS #7 signed data message.
 *
 * @param   bio  [In]  A reference to the #BIO.
 * @param   ctx  [In]  A verification context.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_verification(bio, ctx)                  \
    BIO_ctrl(bio, BIO_C_SET_VFY_CTX, 0, (char *)ctx)

/*
 * @fn long BIO_set_store(BIO *bio, R_CERT_STORE_CTX *store)
 *
 * Sets the certificate store context against a #BIO. A certificate store
 * context is used when verifying a PKCS #7 signed data message.
 *
 * @param   bio    [In]  A reference to the #BIO.
 * @param   store  [In]  A certificate store context.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_store(bio, store)                       \
    BIO_ctrl(bio, BIO_C_SET_STORE, 0, (char *)store)

/*
 * @fn long BIO_set_cert(BIO *bio, R_CERT *cert)
 *
 * Sets the certificate against a #BIO. A certificate is needed to identify
 * a recipient from a PKCS #7 enveloped data message.
 *
 * @param   bio   [In]  A reference to the #BIO.
 * @param   cert  [In]  A certificate.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_cert(bio, cert)                         \
    BIO_ctrl(bio, BIO_C_SET_CERT, 0, (char *)cert)

/*
 * @fn long BIO_set_asym_key(BIO *bio, R_PKEY *pkey)
 *
 * Sets the asymmetric key against a #BIO. An asymmetric key is needed to
 * decrypt information in a recipient from a PKCS #7 enveloped data message.
 *
 * @param   bio   [In]  A reference to the #BIO.
 * @param   pkey  [In]  An asymmetric key.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_asym_key(bio, pkey)                     \
    BIO_ctrl(bio, BIO_C_SET_ASYM_KEY, 0, (char *)pkey)

/*
 * @fn long BIO_set_alg(BIO *bio, R_CR_ALG_ID alg_id)
 *
 * Sets the symmetric cipher algorithm against a #BIO. The algorithm is needed
 * to encrypt the data for a PKCS #7 enveloped data message.
 *
 * @param   bio     [In]  A reference to the #BIO.
 * @param   alg_id  [In]  An algorithm identifier.<br>
 *                        See @ref R_CR_IDS for valid values.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_alg(bio, alg_id)                        \
    BIO_ctrl(bio, BIO_C_SET_ALG_ID, alg_id, NULL)

/*
 * @fn long BIO_set_content_type(BIO *bio, R_CM_TYPE type)
 *
 * Sets the content type of the cryptographic message.
 * When creating a new
 *
 * @param   bio   [In]  A reference to the #BIO.
 * @param   type  [In]  A cryptographic message type.<br>
 *
 *                        Valid values are:
 *                        <li>R_CM_TYPE_SIGNED_DATA</li>
 *                        <li>R_CM_TYPE_ENVELOPED_DATA</li>
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_content_type(bio, type)                 \
    BIO_ctrl(bio, BIO_C_SET_CONTENT_TYPE, type, NULL)

/*
 * @fn long BIO_set_unwrapped(BIO *bio)
 *
 * Tells the cryptographic message BIO filter that the message data does not
 * have content info. The content info identifies the type of message and is
 * left off when the message is embedded in another cryptographic message.
 *
 * @param   bio     [In]  A reference to the #BIO.
 *                        See @ref R_CR_IDS for valid values.
 * @return
 *          1 indicates success.<br>
 *          <=0 indicates error.
 */
#define BIO_set_unwrapped(bio)                          \
     BIO_ctrl(bio, BIO_C_SET_WRAPPED, 0, NULL)

/*
 * @}
 */

/*
#ifdef NO_STDIO
#define NO_FP_API
#endif
*/

/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
#ifdef SSLC_COMPAT_MACROS
#define BIO_sock_should_retry            SIO_sock_should_retry
#define BIO_conn_should_retry            SIO_conn_should_retry
#define BIO_sock_non_fatal_error         SIO_sock_non_fatal_error
#define BIO_conn_non_fatal_error         SIO_conn_non_fatal_error
#define BIO_fd_should_retry              SIO_fd_should_retry
#define BIO_fd_non_fatal_error           SIO_fd_non_fatal_error
#define BIO_gethostbyname                SIO_gethostbyname
#define BIO_gethostbyaddr                SIO_gethostbyaddr
#define BIO_set_gethostbyname            SIO_set_gethostbyname
#define BIO_get_gethostbyname            SIO_get_gethostbyname
#define BIO_set_gethostbyaddr            SIO_set_gethostbyaddr
#define BIO_get_gethostbyaddr            SIO_get_gethostbyaddr
#define BIO_sock_error                   SIO_sock_error
#define BIO_socket_ioctl                 SIO_socket_ioctl
#define BIO_socket_nbio                  SIO_socket_nbio
#define BIO_get_port                     SIO_get_port
#define BIO_get_host_ip                  SIO_get_host_ip
#define BIO_get_accept_socket            SIO_get_accept_socket
#define BIO_accept                       SIO_accept
#define BIO_connect                      SIO_connect
#define BIO_sock_init                    SIO_sock_init
#define BIO_sock_cleanup                 SIO_sock_cleanup
#define BIO_set_tcp_nodelay              SIO_set_tcp_nodelay
#define BIO_ghbn_ctrl                    SIO_ghbn_ctrl
#define BIO_ghbn_default                 SIO_ghbn_default
#define BIO_ghbn_cache                   SIO_ghbn_cache
#define BIO_ghbn_cache_ctrl              SIO_ghbn_cache_ctrl
#define BIO_ghba_default                 SIO_ghba_default
#define BIO_BIND_NORMAL                  SIO_BIND_NORMAL
#define BIO_BIND_REUSEADDR_IF_UNUSED     SIO_BIND_REUSEADDR_IF_UNUSED
#define BIO_BIND_REUSEADDR               SIO_BIND_REUSEADDR
#define BIO_R_SHOULD_RETRY               ERR_R_SHOULD_RETRY
#endif /* SSLC_COMPAT_MACROS */

/* old names */
#define BIO_set_callback(a,b) BIO_set_cb(a,b)
#define BIO_set_callback_arg(a,b) BIO_set_cb_arg(a,b)
#define BIO_get_callback_arg(a) BIO_get_cb_arg(a)
#define BIO_get_callback(a) BIO_get_cb(a)
#define BIO_get_info_callback(a,b) BIO_get_info_cb(a,b)
#define BIO_set_info_callback(a,b) BIO_set_info_cb(a,b)
#define BIO_debug_callback BIO_debug_cb
#define BIO_set_tcp_ndelay(x,y) BIO_set_tcp_nodelay(x,y)

#ifndef NO_FP_API
#  if defined(WIN16) && defined(_WINDLL)
BIO_METHOD *BIO_s_file_internal(void);
BIO *BIO_new_file_internal(char *filename, char *mode);
BIO *BIO_new_fp_internal(FILE *stream, int close_flag);
#         define BIO_s_file        BIO_s_file_internal
#         define BIO_new_file      BIO_new_file_internal
#         define BIO_new_fp        BIO_new_fp_internal
#  else /* defined(WIN16) && defined(_WINDLL)  */
/**
 * @}
 */

BIO_METHOD *BIO_s_file(void);

/**
 * @addtogroup BIO_FILE_FN
 *
 * @{
 */
BIO *BIO_new_file(char *filename, char *mode);
BIO *BIO_new_fp(FILE *stream, int close_flag);
#         define BIO_s_file_internal         BIO_s_file
#         define BIO_new_file_internal       BIO_new_file
#         define BIO_new_fp_internal         BIO_new_fp
#  endif /* defined(WIN16) && defined(_WINDLL)        */
#endif /* NO_FP_API */

/**
 * @}
 */

/**
 * @defgroup BIO_INIT_FN Allocation/Deallocation Functions
 * This section details the functions used to create, initialize and
 * free BIOs.
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
BIO *BIO_new(BIO_METHOD *method);
int BIO_new_init(R_LIB_CTX *lib_ctx, int flag, int type, int sub_id,
    void *value, BIO **bio);
int BIO_set(BIO *bio,BIO_METHOD *type);
int BIO_free(BIO *bio);
void BIO_free_all(BIO *bio);
/**
 * @}
 */

/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
int BIO_read(BIO *bio, char *out, int outl);
int BIO_gets(BIO *bio, char *in, int inl);
int BIO_write(BIO *bio, char *in, int inl);
int BIO_puts(BIO *bio, char *in);
long BIO_ctrl(BIO *bio, int cmd, long larg, char *parg);
char *BIO_ptr_ctrl(BIO *bio, int cmd, long larg);
long BIO_int_ctrl(BIO *bio, int cmd, long larg, int iarg);
BIO *BIO_push(BIO *bio, BIO *stack);
BIO *BIO_pop(BIO *bio);
BIO *BIO_find_type(BIO *bio, int type);
BIO *BIO_get_retry_BIO(BIO *bio, int *reason);
BIO *BIO_dup_chain(BIO *in);

long MS_CALLBACK BIO_debug_cb(BIO *bio,int cmd,char *argp,int argi,
        long argl,long ret);
/**
 * @}
 */

BIO_METHOD *BIO_s_mem(void);
BIO_METHOD *BIO_s_null(void);
#ifndef NO_SOCK
BIO_METHOD *BIO_s_socket(void);
BIO_METHOD *BIO_s_connect(void);
BIO_METHOD *BIO_s_accept(void);
BIO_METHOD *BIO_s_fd(void);
BIO_METHOD *BIO_s_udp_connect(void);
BIO_METHOD *BIO_s_dgram_mux(void);
BIO_METHOD *BIO_s_dgram_mux_session(void);
#endif /* NO_SOCK */

/**
 * This section lists the Filter BIOs that may be used in a BIO stack.
 * These provide data filtering
 * prior to writing to, or after reading from, a source/sink #BIO.
 */
BIO_METHOD *BIO_f_null(void);
BIO_METHOD *BIO_f_buffer(void);
BIO_METHOD *BIO_f_nbio_test(void);

/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
int BIO_dump(BIO *bio,unsigned char *bytes,int len);
int BIO_dump_format(BIO *bio, unsigned char *data, int len, int format,
                                    int separator, int indent, int wrap);

void ERR_load_BIO_strings(void );

BIO *BIO_new_mem(void);
#if !defined(NO_SOCK)

/**
 * Creates a socket #BIO for a socket file descriptor <i>fd</i> where all read
 * and write operations refer to the socket.
 *
 * @param fd          [In]  The socket file descriptor.
 * @param close_flag  [In]  The close flag. One of:<br>
 *                          <li>#BIO_CLOSE.</li>
 *                          <li>#BIO_NOCLOSE.</li>
 * @return  The #BIO reference.<br>
 *          <tt>NULL</tt> indicates error.
 *
 * @note The socket #BIO does not implement the <tt>gets</tt> method (that is,
 * BIO_gets() returns the error <tt>UNSUPPORTED_METHOD</tt>).
 *
 * @eg
 * @include bio_new_socket.c
 */
BIO *BIO_new_socket(SIO_SOCK fd, int close_flag);

BIO *BIO_new_dgram(int sock, int close_flag);

/**
 * Creates a new #BIO for a file descriptor <i>fd</i> where all read and
 * write operations refer to <i>fd</i>. <i>close_flag</i> indicates whether
 * BIO_free() should close the file pointer.
 *
 * @param fd          [In]  The file descriptor.
 * @param close_flag  [In]  The close flag. One of:<br>
 *                          <li>#BIO_CLOSE.</li>
 *                          <li>#BIO_NOCLOSE.</li>
 * @return  The #BIO reference.<br>
 *          <tt>NULL</tt> indicates error.
 *
 * @note The file descriptor #BIO does not implement the <tt>gets</tt> method
 * (that is, BIO_gets() returns the error <tt>UNSUPPORTED_METHOD</tt>).
 *
 * @eg
 * @include bio_new_fd.c
 */
BIO *BIO_new_fd(int fd, int close_flag);

BIO *BIO_new_connect(char *host_port);
BIO *BIO_new_accept(char *host_port);
BIO *BIO_new_dgram_connect(char *host_port);
BIO *BIO_new_dgram_mux(char *host_port);
BIO *BIO_new_dgram_mux_session(char *peer_addr);
#endif /* !defined(NO_SOCK) */
void BIO_copy_next_retry(BIO *bio);

void BIO_reference_inc(BIO *bio);
/**
 * @}
 */

#ifndef SSLEAY_MACROS
/**
 * @addtogroup BIO_STATE_FUNC
 *
 * @{
 */
void BIO_set_flags(BIO *bio,int f);

int BIO_get_flags(BIO *bio);

void BIO_set_retry_special(BIO *bio);

void BIO_set_retry_read(BIO *bio);

void BIO_set_retry_write(BIO *bio);

void BIO_clear_flags(BIO *bio,int f);

void BIO_clear_retry_flags(BIO *bio);

int BIO_get_retry_flags(BIO *bio);

int BIO_should_read(BIO *bio);

int BIO_should_write(BIO *bio);

int BIO_should_io_special(BIO *bio);

int BIO_retry_type(BIO *bio);

int BIO_should_retry(BIO *bio);

int BIO_get_retry_reason(BIO *bio);

char *BIO_method_name(BIO *bio);

int BIO_method_type(BIO *bio);
/**
 * @}
 */

/**
 * @addtogroup BIO_CB_FN
 *
 * @{
 */
void BIO_set_cb(BIO *bio, BIO_CB_FUNC_T *cb);
void BIO_set_cb_arg(BIO *bio, char *arg);
void BIO_set_bio_cb(BIO *bio, BIO_CB_FUNC_T *cb, char *arg);


char *BIO_get_cb_arg(BIO *bio);
BIO_CB_FUNC_T *BIO_get_cb(BIO *bio);

void BIO_set_state_cb(BIO *bio, BIO_STATE_CB_FUNC_T *cb, char *arg);

int BIO_state_to_string(BIO *bio, int state, unsigned int len, char *str);

char *BIO_get_state_cb_arg(BIO *bio);
BIO_STATE_CB_FUNC_T *BIO_get_state_cb(BIO *bio);

int BIO_set_cb_recursive(BIO *bio, int type, void *cb, char *arg);

int BIO_flags_to_string(int flags, char sep, unsigned int len, char *str);

int BIO_cb_cmd_to_string(int cmd, unsigned int len, char *str);

/**
 * @}
 */

#endif /* !SSLEAY_MACROS */

/**
 * @addtogroup BIO_FILE_FN
 *
 * @{
 */
int BIO_open_file(BIO  *bio,char *name,char *mode);
/**
 * @}
 */

/**
 * @addtogroup BIO_STRUCT_FN
 *
 * @{
 */
int BIO_set_dgram_peer(BIO *bio, char *peer,int peer_len);
int BIO_get_dgram_peer(BIO *bio, char **peer,int *peer_len);
int BIO_set_dgram_auto_connect(BIO *bio, int flag);
int BIO_get_dgram_auto_connect(BIO *bio);
int BIO_get_current_session(BIO *bio, BIO **active);
int BIO_set_current_session(BIO *bio, BIO *active);
int BIO_delete_current_session(BIO *bio, BIO *active);

/**
 * @}
 */

/**
 * @defgroup BIO_PRINT_FN Print Functions
 * This section documents the functions used for formatting
 * the printing of data to a #BIO.
 *
 * @ingroup BIO_ALL_FUNCS
 * @{
 */
/**
 * The BIO_print_hex() flag required for printing little-endian numbers.
 * Set flag to 0 for normal or 1 for reverse print.
 */
#define BIO_PRINT_HEX_REVERSE        1
int BIO_print_hex(BIO *bio, unsigned char *bytes,int len,int flags);

#ifdef ANSI_STRICT
int BIO_printf(BIO *bio, ...);
#else
int BIO_printf( VAR_PLIST( BIO *, bio ) );
#endif
/**
 * @}
 */

/* Using the TEST_FRAMEWORK is done on a globally for a build, however
 * the OVERRIDE_TEST_FRAMEWORK can be defined on a per file basis. Currently
 * the build system does not support creating a define for a directory, so
 * this is the only way to override using the test framework.
 */
#ifdef TEST_FRAMEWORK
#ifndef OVERRIDE_TEST_FRAMEWORK

#include "te_bio_filter.h"
#include "temessage_type.h"

/**
 * If using the Test Framework and redirecting stdout and strerr the the
 * Test Framework BIO filter is used. This sets up a bio filter which sets on
 * top of the test frameworks communications object. The forces all program
 * output to be redirected to the test frameworks controller program.
 */
#define BIO_new_fp(fp, param) \
    ((stdout == fp || stderr == fp) ? BIO_new_tefilter(): BIO_new_fp(fp, param))

#endif
#endif

#ifdef        __cplusplus
}
#endif
#endif /* HEADER_COMMON_BIO_H */


