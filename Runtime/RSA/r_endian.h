/* $Id: r_endian.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_endian.h
 * This file provides information on the macros and defines which cater for
 * heterogeneous platforms, with respect to endianess and integer size for
 * platform-independent code.
 */
#ifndef HEADER_COMMON_R_ENDIAN_H
#define HEADER_COMMON_R_ENDIAN_H

#ifdef  __cplusplus
extern "C" {
#endif

/* Basic operations defines */
#define R_BYTE_SIZE                             8
#define R_UINT8_SIZE                            1
#define R_UINT16_SIZE                           2
#define R_UINT32_SIZE                           4

/* Some masks */
#if defined(OPT_64_BIT)
#define R_UINT8_MASK                            0x00000000000000ff
#define R_UINT16_MASK                           0x000000000000ffff
#define R_UINT32_MASK                           0x00000000ffffffff
#elif defined(OPT_32_BIT)
#define R_UINT8_MASK                            0x000000ff
#define R_UINT16_MASK                           0x0000ffff
#define R_UINT32_MASK                           0xffffffff
#else /* !OPT_64_BIT && !OPT_32_BIT */
#define R_UINT8_MASK                            0x00ff
#define R_UINT16_MASK                           0xffff
#define R_UINT32_MASK                           0xffffffffL
#endif /* !OPT_64_BIT && !OPT_32_BIT */

/* Read from and write to network defines */
#define R_WRITE_UINT32(data,buf)                                        \
        *(buf++) = (char)((data>>24) & R_UINT8_MASK);                   \
        *(buf++) = (char)((data>>16) & R_UINT8_MASK);                   \
        *(buf++) = (char)((data>> 8) & R_UINT8_MASK);                   \
        *(buf++) = (char)((data    ) & R_UINT8_MASK);

#define R_WRITE_UINT16(data,buf)                                        \
        *(buf++) = (char)((data>>8) & R_UINT8_MASK);                    \
        *(buf++) = (char)((data   ) & R_UINT8_MASK);

#define R_WRITE_UINT8(data,buf)                                         \
        *(buf++) = (char)(data & R_UINT8_MASK);

#define R_READ_UINT32(data,out)                                         \
        out = (int)(((unsigned char)data[0]));                          \
        out = (int)((out << R_BYTE_SIZE) | ((unsigned char)data[1]));   \
        out = (int)((out << R_BYTE_SIZE) | ((unsigned char)data[2]));   \
        out = (int)((out << R_BYTE_SIZE) | ((unsigned char)data[3]));

#define R_READ_UINT16(data,out)                                         \
        out = (int)(((unsigned char)data[0]));                          \
        out = (int)((out << R_BYTE_SIZE) | ((unsigned char)data[1]));

#define R_READ_UINT8(data,out)                                          \
        out = (int)(((unsigned char)data[0]) & R_UINT8_MASK);



#ifdef  __cplusplus
}
#endif

#endif  /* HEADER_COMMON_R_ENDIAN_H */

