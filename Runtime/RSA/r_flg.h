/* $Id: r_flg.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_flg.h
 * This file provides structures, defines and macros used in the manipulation
 * of bit-masked flag variables.
 */
#ifndef HEADER_COMMON_R_FLG_H
#define HEADER_COMMON_R_FLG_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef R_FLG_BITS
#define R_FLG_BITS        256
#endif
#define R_FLG_LONG_BITS   (sizeof(long)*8)
#define R_FLG_LONGS       (R_FLG_BITS/R_FLG_LONG_BITS)

typedef struct r_flg_st {
        long    dbg_bits[R_FLG_LONGS];
} R_FLG;

#define R_FLG_ZERO(mod_dbg)    \
                Memset((char *)(mod_dbg),0,sizeof (*(mod_dbg)))

#define R_FLG_SET_ALL(mod_dbg)    \
                Memset((char *)(mod_dbg),0xFF,sizeof (*(mod_dbg)))

#define R_FLG_SET(bitnum, mod_dbg)        \
                ((mod_dbg)->dbg_bits[(bitnum)/R_FLG_LONG_BITS] |= \
                ((unsigned)1 << ((bitnum) % R_FLG_LONG_BITS)))

#define R_FLG_CLR(bitnum, mod_dbg)        \
                ((mod_dbg)->dbg_bits[(bitnum)/R_FLG_LONG_BITS] &= \
                ~((unsigned)1 << ((bitnum) % R_FLG_LONG_BITS)))

#define R_FLG_ISSET(bitnum, mod_dbg)      \
                ((mod_dbg)->dbg_bits[(bitnum)/R_FLG_LONG_BITS] & \
                ((unsigned)1 << ((bitnum) % R_FLG_LONG_BITS)))

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_FLG_H */
