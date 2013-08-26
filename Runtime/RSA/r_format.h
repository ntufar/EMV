/* $Id: r_format.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * This file contains public defines and functions for handling data
 * encoding format identifiers.
 */

#ifndef HEADER_COMMON_R_FORMAT_H
#define HEADER_COMMON_R_FORMAT_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "r_com.h"

/**
 *  @defgroup ENC_FORMAT_FLAGS Data Encoding Format Flags
 *  This section lists the data encoding format flags.
 * @ingroup CME_API
 * @{
 */

/**
 *  @}
 */

/**
 * @defgroup ENC_FORMAT Data Encoding Formats
 * This section provides information on the formats in which data is read in
 * and written out.
 * @ingroup ENC_FORMAT_FLAGS
 * @{
 */

/**
 * The format flag. When data is passed to/from the library you can specify
 * how the data is encoded.
 */
typedef int                        R_FORMAT;

/** Indicates that the data is binary encoded. */
#define R_FORMAT_BINARY            0x0000

/** Indicates that the data is text format encoded. */
#define R_FORMAT_TEXT              0x1000

/** Indicates that the data is Privacy Enhanced Mail (PEM) encoded. */
#define R_FORMAT_PEM               (0x0100 | R_FORMAT_TEXT)

/** Indicates that the data is BASE64 encoded. */
#define R_FORMAT_BASE64            (0x0100 | R_FORMAT_BINARY)

/** Indicates that the data is in a C code function format. */
#define R_FORMAT_CODE_BINARY       (0x0001 | R_FORMAT_TEXT)

/** Indicates that the data is in a C code fields format. */
#define R_FORMAT_CODE_FIELDS       (0x0002 | R_FORMAT_TEXT)

/** Indicates that the data is in a C code data format. */
#define R_FORMAT_CODE_HEX          (0x0003 | R_FORMAT_TEXT)

/** Indicates that the data is in a plain hexadecimal Bytes format. */
#define R_FORMAT_HEX               (0x0004 | R_FORMAT_TEXT)

/**
 * @}
 */

/* Mask to use to get the formatting type. The rest of the number indicates
 * whether the format is text or binary or converted to PEM or BASE 64.
 */
#define R_FORMAT_MASK_TYPE         0x00ff

/**
 * @defgroup ENC_FORMAT_FUNCS Data Encoding Format Functions
 * This section outlines the functions that facilitate data encoding formats.
 * @ingroup ENC_FORMAT_FLAGS
 * @{
 */

int R_FORMAT_from_string(char *str, R_FORMAT *format);
int R_FORMAT_to_string(R_FORMAT format, unsigned int max_str_len, char *str);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_FORMAT_H */

