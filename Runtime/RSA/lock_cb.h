/* $Id: lock_cb.h,v 1.1 2005/06/15 11:53:32 ntufar Exp $ */
/*
 * Copyright (C) 1998-2004 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
/**
 * @file
 */

#ifndef HEADER_COMMON_LOCK_CB_H
#define HEADER_COMMON_LOCK_CB_H


#if !(defined(PLATFORM_SOLARIS) || defined(WIN32) || defined (PTHREAD) || \
      defined(PLATFORM_LINUX) || defined(VXWORKS))
#error "Locking not supported on this platform!"
#endif /* !(PLATFORM_SOLARIS || WIN32 || PTHREAD || PLATFORM_LINUX || VXWORKS)
        *
        */

int R_lock_default_cb_add(void);
int R_lock_default_cb_delete(void);

/* fwd decl of the callbacks registered */
int R_lock_default_cb(int mode, int lockid, char *file, int line);

#endif /* HEADER_COMMON_LOCK_CB_H */

