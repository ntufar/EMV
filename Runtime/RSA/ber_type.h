/* $Id: ber_type.h,v 1.1 2005/06/15 11:53:31 ntufar Exp $ */
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
 * This file contains information on the ASN.1 types used to perform
 * Basic Encoding Rules (BER) encoding and decoding operations.
 */

#ifndef HEADER_COMMON_BER_TYPE_H
#define HEADER_COMMON_BER_TYPE_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * Indicates the end of content for encoded items with an unspecified length.
 */
#define BER_EOC                  0

/**
 * Indicates either "true" or "false" as per the ASN.1 boolean values
 * #BER_TRUE and #BER_FALSE.
 */
#define BER_BOOLEAN              1

/**
 * Effectively unbounded but commonly used to hold values
 * that will fit into a <tt>long</tt>.
 */
#define BER_INTEGER              2

/**
 * An array of Bytes in which the first Byte is the number of bits to
 * discard from the end.
 */
#define BER_BIT_STRING           3

/**
 * An 8-bit (hexadecimal Byte) array or Byte array.
 */
#define BER_OCTET_STRING         4

/**
 * A Basic Encoding Rules (BER) object that has no data. It is used when data
 * is specified for a general case but not a specific case.
 */
#define BER_NULL                 5

/**
 * A Basic Encoding Rules (BER) object used to hold an ASN.1 identifier that
 * describes the make-up of the rest of the constructed elements.
 */
#define BER_OBJECT               6

/**
 * An indefinitely long string of characters (plus space) used to describe an
 * object.
 */
#define BER_OBJECT_DESCRIPTOR    7

/**
 * Embedded material that is not defined using ASN.1, such as a GIF file. This
 * type is deprecated in favour of #BER_EMBEDDED_PDV.
 */
#define BER_EXTERNAL             8

/**
 * A comma-separated list of three integers for the mantissa, the base
 * (2 or 10), and the exponent. (Also <tt>PLUS-INFINITY</tt> and
 * <tt>MINUS-INFINITY</tt>.) <br>
 * Hence, <tt>{x, y, z}</tt> is <tt>(x times (y to the power z))</tt>,
 * where <tt>y</tt> is allowed to take only the values 2 and 10.
 */
#define BER_REAL                 9

/**
 * A comma-separated list of names.
 */
#define BER_ENUMERATED          10

/**
 * Embedded material that is not defined using ASN.1, such as a GIF file. This
 * type supercedes #BER_EXTERNAL.
 */
#define BER_EMBEDDED_PDV        11

/**
 * A character string which may contain characters from any language.
 */
#define BER_UTF8STRING          12

/**
 * A constructed type that is used to hold an ordered list of elements.
 */
#define BER_SEQUENCE            16

/**
 * A constructed type that is used to hold a list of repeating elements.
 */
#define BER_SET                 17

/**
 * A string of characters containing the digits zero to 9 and space.
 */
#define BER_NUMERICSTRING       18

/**
 * A character array that only allows a small subset of values, namely
 * [A-Z] [a-z] [0-9] and [ '()+,-./:=?].
 */
#define BER_PRINTABLESTRING     19

/**
 * A deprecated synonym for #BER_TELETEXSTRING.
 */
#define BER_T61STRING           20

/**
 * A character string that allows register entries 6, 87, 102, 103, 106, 107,
 * 126, 144, 150, 153, 156, 164, 165 and 168 (plus space and delete)
 * of the International Register of Coded Character Sets.
 */
#define BER_TELETEXSTRING       20

/**
 * A character string that enables access to the "characters" used to
 * build crude pictures on videotext systems.
 */
#define BER_VIDEOTEXSTRING      21

/**
 * A character string that allows the register entries 1 and 6 (plus space and
 * delete) of the International Register of Coded Character Sets to be used
 * with escape sequences.
 */
#define BER_IA5STRING           22

/**
 * A character string representing the date and time in the format: <br>
 * <tt>ddmmyyhhmmssZ</tt>.
 */
#define BER_UTCTIME             23

/**
 * A character string representing the date and time in the format: <br>
 * <tt>ddmmyyyyhhmmssZ</tt>.
 */
#define BER_GENERALIZEDTIME     24

/**
 * A character string that allows any of the register entries in the
 * International Register for printable characters other than
 * the control character entries.
 */
#define BER_GRAPHICSTRING       25

/**
 * A deprecated synonym for #BER_VISIBLESTRING.
 */
#define BER_ISO64STRING         26

/**
 * A character string that allows register entry 6 of the International
 * Register of Coded Character Sets to be used with escape sequences.
 */
#define BER_VISIBLESTRING       26

/**
 * A character string that allows any of the register entries in the
 * International Register for printable characters.
 */
#define BER_GENERALSTRING       27

/**
 * A character string which may contain characters from any language
 * without using combining characters.
 */
#define BER_UNIVERSALSTRING     28

/**
 * A character string which may contain characters from any living
 * language.
 */
#define BER_BMPSTRING           30

/** The boolean value "false" for the #BER_BOOLEAN ASN.1 type. */
#define BER_FALSE        0
/** The boolean value "true" for the #BER_BOOLEAN ASN.1 type. */
#define BER_TRUE        255

#ifdef  __cplusplus
}
#endif

#endif /* !HEADER_COMMON_BER_TYPE_H */

