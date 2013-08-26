/* $Id: r_assert.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */

/** @file r_assert.h
 *  This file is used instead of ANSI-C assert as it does not exist on all
 *  platforms. To activate the assert, compile with <tt>-DOPT_R_ASSERT</tt>.
 */

#undef r_assert

/* The following is a 'portable' abort for platforms with memory
 * write protection for byte 0 in memory
 */
/*
#define abort(X) { char *nullp=NULL; *nullp='z'; }
*/

#if defined(OPT_R_ASSERT) || defined(DEBUG)
#define r_assert(c)                                                     \
        if (!(c)) {                                                     \
                fprintf(stderr, __FILE__":%d: failed assertion `%s'\n", \
                        __LINE__, #c);                                  \
                abort(); /*R_ASSERT*/                                   \
        }
#else /* !(defined(OPT_R_ASSERT) || defined(DEBUG)) */
#define r_assert(c)
#endif /* defined(OPT_R_ASSERT) || defined(DEBUG) */

