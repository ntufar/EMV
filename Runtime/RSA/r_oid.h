/* $Id: r_oid.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_oid.h
 * This file contains functionality that manages Object Identifier (OID)
 * strings for certificate extensions. 
 */

#ifndef HEADER_COMMON_R_OID_H
#define HEADER_COMMON_R_OID_H

#ifdef  __cplusplus
extern "C" {
#endif

#define R_OID_RSA_ENCRYPTION            "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x01"
#define R_OID_MD2_WITH_RSA_ENCRYPTION   "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x02"
#define R_OID_MD5_WITH_RSA_ENCRYPTION   "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x04"
#define R_OID_SHA_WITH_RSA_ENCRYPTION   "\x2B\x0E\x03\x02\x0F"
#define R_OID_SHA1_WITH_RSA_ENCRYPTION  "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x05"

#define R_OID_MD5_WITH_RSA              "\x2B\x0E\x03\x02\x03"
#define R_OID_DSA_WITH_SHA1             "\x2A\x86\x48\xCE\x38\x04\x03"
#define R_OID_SHA1_WITH_RSA             "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x05"
#define R_OID_SHA1_WITH_RSA_2           "\x2B\x0E\x03\x02\x1D"
#define R_OID_RIPEMD160_WITH_RSA        "\x2B\x24\x03\x03\x01\x02"

#define R_OID_PBE_WITH_MD2_AND_DES_CBC  "\x2A\x86\x48\x86\xF7\x0D\x01\x05\x01"
#define R_OID_PBE_WITH_MD5_AND_DES_CBC  "\x2A\x86\x48\x86\xF7\x0D\x01\x05\x03"
#define R_OID_PBE_WITH_SHA1_AND_RC2_CBC "\x2A\x86\x48\x86\xF7\x0D\x01\x05\x0B"
#define R_OID_PBE_WITH_SHA1_AND_RC4     "\x2A\x86\x48\x86\xF7\x0D\x01\x05\x0C"

#define R_OID_MD2                       "\x2A\x86\x48\x86\xF7\x0D\x02\x02"
#define R_OID_MD5                       "\x2A\x86\x48\x86\xF7\x0D\x02\x05"
#define R_OID_SHA                       "\x2B\x0E\x03\x02\x12"
#define R_OID_SHA1                      "\x2B\x0E\x03\x02\x1A"
#define R_OID_RIPEMD160                 "\x2B\x24\x03\x02\x01"

#define R_OID_RC2_CBC                   "\x2A\x86\x48\x86\xF7\x0D\x03\x02"
#define R_OID_RC4                       "\x2A\x86\x48\x86\xF7\x0D\x03\x04"
#define R_OID_DES_EDE3_CBC              "\x2A\x86\x48\x86\xF7\x0D\x03\x07"
#define R_OID_RC5_CBC_NO_PAD            "\x2A\x86\x48\x86\xF7\x0D\x03\x08"
#define R_OID_RC5_CBC                   "\x2A\x86\x48\x86\xF7\x0D\x03\x09"
#define R_OID_DES_ECB                   "\x2B\x0E\x03\x02\x06"
#define R_OID_DES_CFB                   "\x2B\x0E\x03\x02\x09"
#define R_OID_DES_CBC                   "\x2B\x0E\x03\x02\x07"
#define R_OID_DES_EDE                   "\x2B\x0E\x03\x02\x11"
#define R_OID_AES128_CBC                "\x60\x86\x48\x01\x65\x03\x04\x01\x02"
#define R_OID_AES192_CBC                "\x60\x86\x48\x01\x65\x03\x04\x01\x16"
#define R_OID_AES256_CBC                "\x60\x86\x48\x01\x65\x03\x04\x01\x2A"

#define R_OID_DH_KEY_AGREEMENT          "\x2A\x86\x48\x86\xF7\x0D\x01\x03\x01"

#define R_OID_DSA                       "\x2A\x86\x48\xCE\x38\x04\x01"
#define R_OID_DSA_2                     "\x2B\x0E\x03\x02\x0C"
#define R_OID_DSA_WITH_SHA              "\x2B\x0E\x03\x02\x0D"
#define R_OID_DSA_WITH_SHA1_2           "\x2B\x0E\x03\x02\x1B"

#define R_OID_COMMON_NAME               "\x55\x04\x03"
#define R_OID_COUNTRY_NAME              "\x55\x04\x06"
#define R_OID_LOCALITY_NAME             "\x55\x04\x07"
#define R_OID_STATE_OR_PROVINCE_NAME    "\x55\x04\x08"
#define R_OID_STREET_ADDRESS            "\x55\x04\x09"
#define R_OID_ORGANIZATION_NAME         "\x55\x04\x0A"
#define R_OID_ORGANIZATIONAL_UNIT_NAME  "\x55\x04\x0B"
#define R_OID_GIVENNAME                 "\x55\x04\x2A"
#define R_OID_SURNAME                   "\x55\x04\x04"
#define R_OID_INITIALS                  "\x55\x04\x2B"
#define R_OID_UNIQUE_IDENTIFIER         "\x55\x04\x2D"
#define R_OID_SERIAL_NUMBER             "\x55\x04\x05"
#define R_OID_TITLE                     "\x55\x04\x0C"
#define R_OID_DESCRIPTION               "\x55\x04\x0D"

#define R_OID_RSAES_OAEP                "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x07"
#define R_OID_OAEP_ID_MGF1              "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x08"
#define R_OID_OAEP_ID_PSPECIFIED        "\x2A\x86\x48\x86\xF7\x0D\x01\x01\x09"

#define R_OID_PKCS9_EMAIL_ADDRESS       "\x2A\x86\x48\x86\xF7\x0D\x01\x09\x01"

/* PKCS#7 related items */
#define R_OID_PKCS7                     "\x2A\x86\x48\x86\xF7\x0D\x01\x07"
#define R_OID_PKCS7_DATA                "\x2A\x86\x48\x86\xF7\x0D\x01\x07\x01"
#define R_OID_PKCS7_SIGNED              "\x2A\x86\x48\x86\xF7\x0D\x01\x07\x02"
#define R_OID_PKCS7_ENVELOPED           "\x2A\x86\x48\x86\xF7\x0D\x01\x07\x03"

#define R_OID_PKCS9_CONTENT_TYPE        "\x2A\x86\x48\x86\xF7\x0D\x01\x09\x03"
#define R_OID_PKCS9_MESSAGE_DIGEST      "\x2A\x86\x48\x86\xF7\x0D\x01\x09\x04"
#define R_OID_PKCS9_SIGNING_TIME        "\x2A\x86\x48\x86\xF7\x0D\x01\x09\x05"
#define R_OID_PKCS9_COUNTER_SIGNATURE   "\x2A\x86\x48\x86\xF7\x0D\x01\x09\x06"


#define R_OID_ECC                       "\x2A\x86\x48\xCE\x3D\x02\x01"

#define R_OID_ECDSA_WITH_SHA1           "\x2A\x86\x48\xCE\x3D\x04\x01"

/**
 * @defgroup CERT_EXT_OID Extension Object Identifier Strings
 * This section details the Object Identifier (OID) strings
 * for certificate extensions. 
 * @ingroup CERT_IDENTIFIER
 * @{
 */

/* Defines for the object identifiers */
/**
 * Indicates the subject key identifier extension Object Identifier (OID).
 */
#define R_OID_SUBJECT_KEY_IDENTIFIER    "\x55\x1d\x0e"
/**
 * Indicates the key usage extension Object Identifier (OID).
 */
#define R_OID_KEY_USAGE                 "\x55\x1d\x0f"
/**
 * Indicates the private key usage period extension Object Identifier (OID).
 */
#define R_OID_PRIVATE_KEY_USAGE_PERIOD  "\x55\x1d\x10"
/**
 * Indicates the subject alternative name extension Object Identifier (OID).
 */
#define R_OID_SUBJECT_ALT_NAME          "\x55\x1d\x11"
/**
 * Indicates the issuer alternative name extension Object Identifier (OID).
 */
#define R_OID_ISSUER_ALT_NAME           "\x55\x1d\x12"
/**
 * Indicates the basic constraint extension Object Identifier (OID).
 */
#define R_OID_BASIC_CONSTRAINTS         "\x55\x1d\x13"
/**
 * Indicates the Certificate Revocation List (CRL) number extension 
 * Object Identifier (OID).
 */
#define R_OID_CRL_NUMBER                "\x55\x1d\x14"
/**
 * Indicates the Certificate Revocation List (CRL) reason code extension
 * Object Identifier (OID).
 */
#define R_OID_REASON_CODE               "\x55\x1d\x15"
/**
 * Indicates the Certificate Revocation List (CRL) instruction code extension
 * Object Identifier (OID).
 */
#define R_OID_INSTRUCTION_CODE          "\x55\x1d\x17"
/**
 * Indicates the Certificate Revocation List (CRL) invalidity date extension
 * Object Identifier (OID).
 */
#define R_OID_INVALIDITY_DATE           "\x55\x1d\x18"
/**
 * Indicates the delta Certificate Revocation List (CRL) indicator extension
 * Object Identifier (OID).
 */
#define R_OID_DELTA_CRL_INDICATOR       "\x55\x1d\x1b"
/**
 * Indicates the Certificate Revocation List (CRL) issuing distribution point
 * extension Object Identifier (OID).
 */
#define R_OID_ISSUING_DISTRIBUTION_POINT "\x55\x1d\x1c"
/**
 * Indicates the Certificate Revocation List (CRL) certificate issuer extension
 * Object Identifier (OID).
 */
#define R_OID_CERTIFICATE_ISSUER        "\x55\x1d\x1d"
/**
 * Indicates the Certificate Revocation List (CRL) name constraints
 * extension Object Identifier (OID).
 */
#define R_OID_NAME_CONSTRAINTS          "\x55\x1d\x1e"
/**
 * Indicates the Certificate Revocation List (CRL) distribution points
 * extension Object Identifier (OID).
 */
#define R_OID_CRL_DISTRIBUTION_POINTS   "\x55\x1d\x1f"
/**
 * Indicates the certificate policies extension Object Identifier (OID).
 */
#define R_OID_CERTIFICATE_POLICIES      "\x55\x1d\x20"
/**
 * Indicates the authority key identifier extension Object Identifier (OID).
 */
#define R_OID_AUTHORITY_KEY_IDENTIFIER  "\x55\x1d\x23"
/**
 * Indicates the extended key usage extension Object Identifier (OID).
 */
#define R_OID_EXTENDED_KEY_USAGE        "\x55\x1d\x25"

/**
 * @}
 */

/**
 * @defgroup CERT_EKU_OID Extended Key Usage Object Identifier Strings
 * This section details Extended Key Usage Object Identifier (OID) strings
 * for certificates as defined in 
 * <a href="http:\\www.ietf.org\rfc\rfc3280.txt">RFC 3280</a>
 * (Internet X.509 Public Key Infrastructure Certificate and Certificate
 * Revocation List (CRL) Profile). 
 * @ingroup CERT_IDENTIFIER
 * @{
 */

/**
 * Indicates the extended key usage extension 
 * Server Authentication Object Identifier (OID).
 */
#define R_OID_SERVER_AUTH               "\x2B\x06\x01\x05\x05\x07\x03\x01"
/**
 * Indicates the extended key usage extension 
 * Client Authentication Object Identifier (OID).
 */
#define R_OID_CLIENT_AUTH               "\x2B\x06\x01\x05\x05\x07\x03\x02"
/**
 * Indicates the extended key usage extension 
 * Code Signing Object Identifier (OID).
 */
#define R_OID_CODE_SIGNING              "\x2B\x06\x01\x05\x05\x07\x03\x03"
/**
 * Indicates the extended key usage extension 
 * E-mail Protection Object Identifier (OID).
 */
#define R_OID_EMAIL_PROTECTION          "\x2B\x06\x01\x05\x05\x07\x03\x04"
/**
 * Indicats the extended key usage extension 
 * IPSec End System Object Identifier (OID).
 */
#define R_OID_IPSEC_END_SYSTEM          "\x2B\x06\x01\x05\x05\x07\x03\x05"
/**
 * Indicates the extended key usage extension  
 * IPSec Tunnel Object Identifier (OID).
 */
#define R_OID_IPSEC_TUNNEL              "\x2B\x06\x01\x05\x05\x07\x03\x06"
/**
 * Indicates the extended key usage extension 
 * IPSec User Object Identifier (OID).
 */
#define R_OID_IPSEC_USER                "\x2B\x06\x01\x05\x05\x07\x03\x07"
/**
 * Indicates the extended key usage extension 
 * Time Stamping Object Identifier (OID).
 */
#define R_OID_TIME_STAMPING             "\x2B\x06\x01\x05\x05\x07\x03\x08"
/**
 * Indicates the extended key usage extension 
 * Online Certificate Status Protocol (OSCP) Signing Object Identifier (OID).
 */
#define R_OID_OCSP_SIGNING              "\x2B\x06\x01\x05\x05\x07\x03\x09"


/**
 * @}
 */

/* preserve old defines for backward compatibility */
#define R_OID_KEY_USAGE_EXT              R_OID_KEY_USAGE
#define R_OID_BASIC_CONSTRAINT_EXT       R_OID_BASIC_CONSTRAINTS
#define R_OID_EXTENDED_KEY_USAGE_EXT     R_OID_EXTENDED_KEY_USAGE
#define R_OID_EKU_EXT_SERVER_AUTH        R_OID_SERVER_AUTH
#define R_OID_EKU_EXT_CLIENT_AUTH        R_OID_CLIENT_AUTH
#define R_OID_EKU_EXT_CODE_SIGNING       R_OID_CODE_SIGNING
#define R_OID_EKU_EXT_EMAIL_PROTECTION   R_OID_EMAIL_PROTECTION
#define R_OID_EKU_EXT_IPSEC_ENDSYSTEM    R_OID_IPSEC_END_SYSTEM
#define R_OID_EKU_EXT_IPSEC_TUNNEL       R_OID_IPSEC_TUNNEL
#define R_OID_EKU_EXT_IPSEC_USER         R_OID_IPSEC_USER
#define R_OID_EKU_EXT_TIME_STAMPING      R_OID_TIME_STAMPING
#define R_OID_EKU_EXT_OCSP_SIGNING       R_OID_OCSP_SIGNING
#define R_CERT_EKU_ENCODING_PREFIX       "\x30\x0a\x06\x08"

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_OID_H */

