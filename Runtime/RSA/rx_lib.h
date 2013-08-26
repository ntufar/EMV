/* $Id: rx_lib.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file provides information on the structures, function prototypes and
e* defines used in the manipulation of library context objects in small
 * configurations.
 */

#ifndef HEADER_COMMON_RX_LIB_H
#define HEADER_COMMON_RX_LIB_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef Rm_LIB_CTX_TABLE

#include "r_lib_m.h"

#define R_LIB_CTX_get_resource(lib_ctx, mod_id, impl_id, sub_id, flag,      \
    res_type, data)                                                         \
    (lib_ctx)->meth->get_resource((lib_ctx), (mod_id), (impl_id), (sub_id), \
        (flag), (res_type), (data))
#define R_LIB_CTX_get_module(lib_ctx, mod_id, impl_id, sub_id, flag, mod)   \
    ((lib_ctx)->meth->get_module == NULL) ? R_ERROR_NOT_AVAILABLE :         \
    (lib_ctx)->meth->get_module((lib_ctx), (mod_id), (impl_id), (sub_id),   \
        (flag), (mod))
#define R_LIB_CTX_get_module_data(lib_ctx, mod_id, impl_data)               \
    (lib_ctx)->meth->get_module_data((lib_ctx), (mod_id), (impl_data))

#define R_LIB_CTX_set_features(lib_ctx, impl_id, features)                  \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_SET, \
        (features))
#define R_LIB_CTX_get_features(lib_ctx, impl_id, features)                  \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_GET, \
        (features))
#define R_LIB_CTX_reset_features(lib_ctx, impl_id)                          \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id),                 \
        R_LIB_FEAT_SET, NULL)
#define R_LIB_CTX_feature_disable(lib_ctx, impl_id, feature)                \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id),                 \
        R_LIB_FEAT_DISABLE, (feature))
#define R_LIB_CTX_feature_enable(lib_ctx, impl_id, feature)                 \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id),                 \
        R_LIB_FEAT_ENABLE, (feature))
#define R_LIB_CTX_is_feature_enabled(lib_ctx, impl_id, feature)             \
    (lib_ctx)->meth->lib_feature_ctrl((lib_ctx), (impl_id),                 \
        R_LIB_FEAT_IS_ENABLED, (feature))

#define R_LIB_CTX_get_lib_debug_data(lib_ctx, data)                         \
    (lib_ctx)->meth->lib_debug_ctrl((lib_ctx), R_LIB_DEBUG_GET, (data))
#define R_LIB_CTX_set_lib_debug_data(lib_ctx, data)                         \
    (lib_ctx)->meth->lib_debug_ctrl((lib_ctx), R_LIB_DEBUG_SET, (data))

#endif /* Rm_LIB_CTX_TABLE */

#ifdef Rm_LIB_CTX_DIRECT

#include "ri_lib.h"

#define R_LIB_CTX_get_resource(lib_ctx, mod_id, impl_id, sub_id, flag,      \
    res_type, data)                                                         \
    r_lib_ctx_get_resource((lib_ctx), (mod_id), (impl_id), (sub_id),        \
        (flag), (res_type), (data))
#define R_LIB_CTX_get_module(lib_ctx, mod_id, impl_id, sub_id, flag, mod)   \
    r_lib_ctx_get_module((lib_ctx), (mod_id), (impl_id), (sub_id),          \
        (flag), (mod))
#define R_LIB_CTX_get_module_data(lib_ctx, mod_id, impl_data)               \
    r_lib_ctx_get_module_data((lib_ctx), (mod_id), (impl_data))

#define R_LIB_CTX_set_features(lib_ctx, impl_id, features)                  \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_SET, (features))
#define R_LIB_CTX_get_features(lib_ctx, impl_id, features)                  \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_GET, (features))
#define R_LIB_CTX_reset_features(lib_ctx, impl_id)                          \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_SET, NULL)
#define R_LIB_CTX_feature_disable(lib_ctx, impl_id, feature)                \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_DISABLE, (feature))
#define R_LIB_CTX_feature_enable(lib_ctx, impl_id, feature)                 \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_ENABLE, (feature))
#define R_LIB_CTX_is_feature_enabled(lib_ctx, impl_id, feature)             \
    r_lib_ctx_lib_feat_ctrl((lib_ctx), (impl_id), R_LIB_FEAT_IS_ENABLED,    \
        (feature))

#define R_LIB_CTX_get_lib_debug_data(lib_ctx, data)                         \
    r_lib_ctx_debug_ctrl((lib_ctx), R_LIB_DEBUG_GET, (data))
#define R_LIB_CTX_set_lib_debug_data(lib_ctx, data)                         \
    r_lib_ctx_debug_ctrl((lib_ctx), R_LIB_DEBUG_SET, (data))

#endif /* Rm_LIB_CTX_DIRECT */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_RX_LIB_H */

