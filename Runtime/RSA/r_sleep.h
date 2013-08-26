/* $Id: r_sleep.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
/**
 * @file
 * Provides define R_sleep as platform independent for function sleep. 
 */
#ifndef HEADER_COMMON_R_SLEEP_H
#define HEADER_COMMON_R_SLEEP_H

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(WINDOWS) || defined(WIN32)

#define R_sleep(sec)               Sleep(sec * 1000L)

#elif defined(ChorusOS)

#include <arpa/ftpd/systemSleep.h>
#define R_sleep(sec)               systemSleep(sec)

#elif defined(VXWORKS)

#include <sysLib.h>
#define R_sleep(sec)               taskDelay(sec * sysClkRateGet());

#else

#define R_sleep(sec)               sleep(sec)

#endif

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SLEEP_H */


