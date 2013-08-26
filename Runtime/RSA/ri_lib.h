/* $Id: ri_lib.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

#ifndef HEADER_COMMON_RI_LIB_H
#define HEADER_COMMON_RI_LIB_H

#ifdef  __cplusplus
extern "C" {
#endif

int r_lib_ctx_get_resource(R_LIB_CTX *lib_ctx, int mod_id, int imp_id,
	int sub_id, R_RES_FLAG flag, int res_type, void **data);

int r_lib_ctx_get_module(R_LIB_CTX *lib_ctx, int mod_id, int impl_id,
	int sub_id, R_RES_FLAG flag, void **mod);
int r_lib_ctx_get_module_nl(R_LIB_CTX *lib_ctx, int mod_id, int impl_id,
	int sub_id, R_RES_FLAG flag, void **mod);
int r_lib_ctx_get_module_data(R_LIB_CTX *lib_ctx, int mod_id, void **impl_data);

int r_lib_ctx_lib_feat_ctrl(R_LIB_CTX *lib_ctx, int impl_id, int cmd,
    R_LIB_FEAT *feat);

int r_lib_ctx_debug_ctrl(R_LIB_CTX *lib_ctx, int cmd, void *data);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_RI_LIB_H */

