/* $Id: r_res.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file provides defines, structures and function prototypes used
 * in the manipulation of resource lists found in library context objects.
 */

#ifndef HEADER_COMMON_R_RES_H
#define HEADER_COMMON_R_RES_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"
#include "r_modid.h"

#define R_RES_LIST_ACTION_PREPEND               0
#define R_RES_LIST_ACTION_APPEND                1
#define R_RES_LIST_ACTION_REPLACE               2
#define R_RES_LIST_ACTION_REMOVE                3

/**
 * @defgroup R_RES_LIST_FLAGS_ID List Flags
 * This section lists the attributes of a resource list item.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */

/** Indicates that the resource list item has been statically declared. */
#define R_RES_LIST_FLAG_STATIC                  0x01

/** Indicates that the resource list item is a dynamically allocated copy. */
#define R_RES_LIST_FLAG_COPY                    0x02

/** Indicates that the resource list item is read-only. */
#define R_RES_LIST_FLAG_READ_ONLY               0x04

/**
 * @}
 */

/**
 * @defgroup RES_LIST_TYPES Types
 * This section outlines the types used when dealing with the library and
 * the resources within.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */

/**
 * The resource item. A structure that is used to store the
 * individual members of a resource list.
 */
typedef struct r_res_item_st                    R_RES_ITEM;

/**
 * The resource list. A structure that is used to store the
 * resource list.
 *
 * See @ref R_RES_ITEM.
 */
typedef R_RES_ITEM                              R_RES_LIST;

/**
 * Indicates the type of the resource flag.
 * See @ref RES_FLAG for more information.
 */
typedef int                                     R_RES_FLAG;

/**
 * @}
 */

/**
 * This structure is used by the resource list item data type to hold
 * the identity and implementation details of a resource.
 */
struct r_res_item_st
{
    /** Type of resource. */
    int mod_id;

    /** Unique value for each resource implementation. */
    int impl_id;

    /** Sub identifier of resource stored. */
    int sub_id;

    /** Resource attributes.
     *  See @ref R_RES_LIST_FLAGS_ID.
     */
    R_RES_FLAG flag;

    /** Resource-specific library start-up function. */
    int (*start)(R_RES_LIST *, R_RES_ITEM *, void **);

    /** Resource-specific library finish function. */
    int (*finish)(R_RES_LIST *, R_RES_ITEM *, void **);

    /** Retrieves the resource method(s) function. */
    void *(*meth)(void *);

    /** Retrieves the resource data function. */
    void *(*data)(void *);
};

int R_RES_LIST_set_resource(R_RES_LIST *res_list, int mod_id, int impl_id,
        int sub_id, R_RES_FLAG flag, int res_type, void *data);
int R_RES_LIST_get_resource(R_RES_LIST *res_list, int mod_id, int imp_id,
        int sub_id, R_RES_FLAG flag, int res_type, void **data);

int R_RES_LIST_get_item(R_RES_LIST *res_list, int mod_id, int imp_id,
        int sub_id, R_RES_FLAG flag, R_RES_ITEM **data, R_RES_LIST **next);
int R_RES_LIST_set_item(R_RES_LIST **res_list, int action, R_RES_ITEM *item);

int R_RES_LIST_get_next_item(R_RES_LIST *res_list, R_RES_ITEM **data,
    R_RES_LIST **next);

int R_RES_LIST_get_num_entries(R_RES_LIST *res_list, int *count);
int R_RES_LIST_check_writable(R_RES_LIST *res_list);
int R_RES_LIST_set_writable(R_RES_LIST *res_list, int flag);

int R_RES_LIST_lib_finish(R_RES_LIST *res_list, R_RES_ITEM *item,
        void **imp_data);
int R_RES_LIST_free(R_RES_LIST *res_list);

int R_RES_LIST_join(R_RES_LIST **new_list, R_RES_LIST *append_list);
int R_RES_LIST_dup(R_RES_LIST **new_list, R_RES_LIST *res_list);

/**
 * @defgroup R_RES_LIST_RES Resource Definitions
 * This section details the definitions used in the resource list and
 * initialization of the library.
 * @ingroup RES_LIST_GROUP
 *
 * @{
 */

/**
 * The mandatory marker indicating the end of a resource list.
 */
#define R_RES_END_OF_LIST                                               \
    { R_RES_MOD_ID_RES_LIST, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,       \
      R_RES_LIST_FLAG_STATIC, NULL, R_RES_LIST_lib_finish, NULL, NULL }

/**
 * The mandatory marker indicating the end of a resource list. This can
 * be used if the list is a read-only list.
 */
#define R_RES_END_OF_LIST_READ_ONLY                                     \
    { R_RES_MOD_ID_RES_LIST, R_RES_IMPL_ID_DEF, R_RES_SUB_ID_DEF,       \
      (R_RES_LIST_FLAG_STATIC|R_RES_LIST_FLAG_READ_ONLY), NULL, NULL,   \
      NULL, NULL }

/**
 * @}
 */


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_RES_H */


