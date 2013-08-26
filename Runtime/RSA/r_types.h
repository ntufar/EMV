/* $Id: r_types.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_types.h
 * This file contains the library structure and type definitions.
 */
#ifndef HEADER_COMMON_R_TYPES_H
#define HEADER_COMMON_R_TYPES_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 *  @defgroup DATA_MNG_FLAGS Data Management Flags
 *  This section lists the data management flags.
 *  @ingroup CME_API
 * @{
 */
 
/**
 *  @}
 */
 
/* This gets set if the flags field if the we need to 'free' the
 * R_RANDOM when we call R_rand_free().  If it is not set, the
 * rand_ctrl will only be called to clean things up.
 */
#define R_RANDOM_FLG_MALLOCED       0x01

/* portable form of a random callback function */
/**
 * @typedef R_RANDOM
 * The random object type.
 */
typedef struct r_random_st R_RANDOM;
/**
 * This structure is used by the random object type.
 */
struct r_random_st
{
    /**
     * A method function for generation of random data.
     *
     * @see R_rand_bytes().
     */
    int (*rand_bytes)(R_RANDOM *ctx,unsigned char *bytes,int len);
    /**
     * A method function for seeding of the random generator.
     * @see R_rand_seed().
     */
    int (*rand_seed)(R_RANDOM *ctx,unsigned char *bytes,int len);
    /**
     * A method function for control of the random generator used by
     * other functions as a single interface.
     *
     * @see R_rand_entropy_count(), R_rand_set_entropy_func(),
     * R_rand_get_entropy_func(), R_rand_load_file(), R_rand_write_file()
     * and R_rand_file_name().
     */
    int (*rand_ctrl)(R_RANDOM *ctx,int op,char *arg);
    /**
     * The data used by the random implementation.
     */
    char *arg;
    /**
     * A method flag for used for keeping the state of the #R_RANDOM.
     */
    int flags;  /* normally set to zero */
};
/**
 * @typedef R_SURRENDER
 * The surrender function and argument.
 */
typedef struct r_surrender_st R_SURRENDER;
/**
 * This structure provides a status update of a time intensive operation. It
 * also allows you to abort the operation if required.
 */
struct r_surrender_st
{
    /* Return 0 to continue, non-zero to 'cancel' function */
    /**
     * The surrender function pointer used as a generic method of
     * passing user-defined callback or information collection functions.
     */
    int (*callback)(R_SURRENDER *ctx,int function,int num);
    /**
     * The argument data used by the callback operation.
     */
    char *arg;
};

typedef struct r_fixed_point_number_st R_FIXED_POINT_NUMBER;
struct r_fixed_point_number_st
{
    unsigned long hi;
    unsigned long lo;
};

/**
 * @typedef R_INDEXED_INFO
 * This structure details the index containing information for get and set
 * functions.
 */
typedef struct r_indexed_info_st R_INDEXED_INFO;
/** This structure details the index containing information for get and set
 * functions.
 */
struct r_indexed_info_st
{
    /** The index into the list of the item to work with. */
    int index;
    /** The data of the item in the list. */
    void  *data;
    /** The length of the data. */
    unsigned int len;
    /** The data value as an integer. */
    int value;
};

/**
 * @typedef R_ID_INFO
 * The information to work with requires a second identity value to find it.
 */
typedef struct r_id_info_st R_ID_INFO;
/** The information to get or set requires a second information identifier.
 *  This type is used when calling set_info and get_info to get a number of
 *  information items in one call.
 */
struct r_id_info_st
{
    /** The information identifier. */
    int info_id;
    /** The information data associated with the identifier. */
    void *value;
};

/** @defgroup R_FLAG_COPY_IDS Copy Flag Identifiers
 *
 * This section provides information on the copy mode. When data is passed 
 * to/from the library you can specify whether or not the copy should be done 
 * by value, by reference or by direct assignment.
 * @ingroup DATA_MNG_FLAGS
 * @{
 */

/**
 * The copy flag. When data is passed to/from the library you can specify
 * whether or not the copy should be done by value, by reference or
 * by direct assignment.
 */
typedef int R_FLAG_COPY;

/* 
 * action    flag       app    lib
 * obj_get   BY_VAL      F      X
 *           BY_REF      X      F   [app will not free "obj" until it is 
 *           BY_ASSIGN   F      X        finished with the returned reference]
 * obj_set   BY_VAL      F      X
 *           BY_REF      F      X   [app will not free passed reference
 *           BY_ASSIGN   X      F        until after it has freed "obj"]
 *
 * BY_REF makes the lifetime of the two objects linked and it is up to 
 * the application to manage the objects in a manner that preserves this
 * relationship.
 */

/** 
 * Indicates to copy by value. A complete clone of the object is made.
 * The lifecycles of the two objects are independent.
 */
#define R_FLAG_COPY_BY_VALUE        0x0000

/** 
 * Indicates to copy by reference. A reference to the object is made.
 * The lifecycles of objects sharing references are linked.
 */
#define R_FLAG_COPY_BY_REFERENCE    0x0001

/** 
 * Indicates to copy by assignment. The object is assigned to the required
 * party. The caller does not keep a reference to the passed object.
 */
#define R_FLAG_COPY_BY_ASSIGN       0x0002

/** 
 * Indicates to copy using the default flag settings. 
 */
#define R_FLAG_COPY_DEFAULT     R_FLAG_COPY_BY_VALUE

/**
 * @}
 */

/** @defgroup R_FLAG_SHARE_IDS Shared Flag Identifiers
 *
 * This section provides information on the shared flags available.
 * @ingroup DATA_MNG_FLAGS
 * @{
 */
 
/**
 * The constructor flag. Indicates whether or not it is permissible to share
 * the internal state between objects. 
 */
typedef int R_FLAG_SHARE;

/** 
 * Indicates to share nothing. The states of the two objects are completely
 * separate.
 */
#define R_FLAG_SHARE_NONE       0x0000

/** 
 * Indicates to share data. Constructed objects may reference the state of
 * the object from which it was constructed. The lifecycles of the two objects
 * are linked.
 */
#define R_FLAG_SHARE_DATA       0x0001

/** Indicates the share default in which nothing is shared. */
#define R_FLAG_SHARE_DEFAULT    R_FLAG_SHARE_NONE

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif


