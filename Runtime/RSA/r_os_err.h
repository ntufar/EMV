/* $Id: r_os_err.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_os_err.h
 * This file defines function prototypes used in platform-independent
 * operating system error handling.
 */
#ifndef HEADER_COMMON_R_OS_ERR_H
#define HEADER_COMMON_R_OS_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

int R_os_io_non_fatal_error(int err);
int R_os_io_should_retry(int i,int err);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_OS_ERR_H */
