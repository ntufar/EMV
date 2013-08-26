/* $Id: r_eitems.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_eitems.h
 * This file contains the function prototypes, defines and macros used in the
 * manipulation of extended item structures #R_EITEMS and #R_EITEM.
 */
#ifndef HEADER_COMMON_R_EITEMS_H
#define HEADER_COMMON_R_EITEMS_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF
#define HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF
/**
 * The extended item data set component.
 */
typedef struct r_eitem_st R_EITEM;

/**
 * The extended item data set.
 */
typedef struct r_eitems_st R_EITEMS;
#endif /* HEADER_COMMON_DATA_R_EITEMS_TYPEDEF_DEF */

/* Make the actual structures available to all
 * library components.
 */

#ifdef R_LIBRARY_BUILD
#include "r_eitems_st.h"
#endif

/**
 * @defgroup R_EITEM_DEFINITIONS R_EITEM Definitions
 * This section details the identifiers used to define the behavior
 * and components of #R_EITEMS. An #R_EITEM is a structure that holds
 * data and provides identifier and type fields.
 *
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup R_EITEM_FLAGS Flags
 * This section outlines the identifiers used to define the attributes of an
 * #R_EITEM.
 * @ingroup R_EITEM_DEFINITIONS
 * @{
 */

/**
 * Indicates that the #R_EITEM has been dynamically allocated.
 */
#define R_EITEMS_F_MALLOCED                     0x0001
/**
 * Indicates that the data of the #R_EITEM has been dynamically allocated.
 */
#define R_EITEMS_F_DATA_MALLOCED                0x0002

/** Indicates that the data passed in is owned by the #R_EITEM. */
#define R_EITEMS_PF_BY_ASSIGN           0x0000

/** Indicates that the item is to be freed by the library. */
#define R_EITEMS_PF_LIBFREE             0x0001

/** Indicates to copy all aspects of the passed item. */
#define R_EITEMS_PF_COPY                0x0002

/** Indicates to scan from the index to the end, and then loop. */
#define R_EITEMS_PF_LOOP                0x0004

/** Indicates to use the #R_EITEM passed directly, without making a local copy.
 */
#define R_EITEMS_PF_BY_REFERENCE        0x0008

/** Indicates to replace the existing entry in #R_EITEMS. */
#define R_EITEMS_PF_REPLACE             0x0010

/**
 * @}
 */


R_EITEM *R_EITEM_new(void);
void R_EITEM_init(R_EITEM *ip);
int R_EITEM_set(R_EITEM *a, int set,int field, unsigned char *data,
        int len, int flags);
int R_EITEM_copy(R_EITEM *a,R_EITEM *b,int flags);
R_EITEM *R_EITEM_dup(R_EITEM *ret,R_EITEM *a,int flags);
R_EITEMS *R_EITEMS_dup(R_EITEMS *ret,R_EITEMS *a,int flags);
void R_EITEM_free(R_EITEM *ip);

R_EITEMS *R_EITEMS_new(void);
void R_EITEMS_init(R_EITEMS *ctx);
void R_EITEMS_free(R_EITEMS *ctx);
int R_EITEMS_add(R_EITEMS *ctx, int set,int field, int data_type,
        unsigned char *data, int len, int flags);
int R_EITEMS_add_item(R_EITEMS *ctx, R_EITEM *item, int flags);
int R_EITEMS_delete(R_EITEMS *ctx, int set, int field, int flags);
int R_EITEMS_find_item(R_EITEMS *ctx, int set, int field, int *index,
        R_EITEM **datap, int flags);
int R_EITEMS_check_list(R_EITEMS *ctx, int set, int *list);
int R_EITEMS_compact(R_EITEMS *ctx, int flags);

#ifdef HEADER_BIO_H_TYPEDEF_DEF
void R_EITEM_dump(R_EITEM *ip, BIO *bio);
void R_EITEMS_dump(R_EITEMS *ctx, BIO *bio);
#endif /* HEADER_BIO_H_TYPEDEF_DEF */


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_EITEMS_H */
