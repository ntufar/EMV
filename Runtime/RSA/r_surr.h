/* $Id: r_surr.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_surr.h
 * This file provides function prototypes for interoperation of
 * #R_SURRENDER with callback function prototypes.
 */
#ifndef HEADER_COMMON_R_SURR_H
#define HEADER_COMMON_R_SURR_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_types.h"

int R_surr_new2old_cb(R_SURRENDER *surr,int p,int n);
void R_surr_set_default(int (*func)(R_SURRENDER *surr, int p, int n), char *arg);
R_SURRENDER *R_surr_get_default(void);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SURR_H */
