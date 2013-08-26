/* $Id: r_nid.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_nid.h
 * This file defines the object identifiers used in ASN.1 processing.
 * The defines include:<br>
 * <li>Ciphers.</li>
 * <li>Public Key Cryptography Standards.</li>
 * <li>Padding types.</li>
 * <li>Certificate fields.</li>
 */
#ifndef HEADER_COMMON_R_NID_H
#define HEADER_COMMON_R_NID_H

#ifdef  __cplusplus
extern "C" {
#endif

#define SN_undef                        "UNDEF"
#define LN_undef                        "undefined"
#define NID_undef                       0
#define OBJ_undef                       0L

#define SN_Algorithm                    "Algorithm"
#define LN_algorithm                    "algorithm"
#define NID_algorithm                   38
#define OBJ_algorithm                   1L,3L,14L,3L,2L

#define LN_rsadsi                       "rsadsi"
#define NID_rsadsi                      1
#define OBJ_rsadsi                      1L,2L,840L,113549L

#define LN_pkcs                         "pkcs"
#define NID_pkcs                        2
#define OBJ_pkcs                        OBJ_rsadsi,1L

#define SN_md2                          "MD2"
#define LN_md2                          "md2"
#define NID_md2                         3
#define OBJ_md2                         OBJ_rsadsi,2L,2L

#define SN_md5                          "MD5"
#define LN_md5                          "md5"
#define NID_md5                         4
#define OBJ_md5                         OBJ_rsadsi,2L,5L

#define SN_rc4                          "RC4"
#define LN_rc4                          "rc4"
#define NID_rc4                         5
#define OBJ_rc4                         OBJ_rsadsi,3L,4L

#define LN_rsaEncryption                "rsaEncryption"
#define NID_rsaEncryption               6
#define OBJ_rsaEncryption               OBJ_pkcs,1L,1L

#define SN_md2WithRSAEncryption         "RSA-MD2"
#define LN_md2WithRSAEncryption         "md2WithRSAEncryption"
#define NID_md2WithRSAEncryption        7
#define OBJ_md2WithRSAEncryption        OBJ_pkcs,1L,2L

#define SN_md5WithRSAEncryption         "RSA-MD5"
#define LN_md5WithRSAEncryption         "md5WithRSAEncryption"
#define NID_md5WithRSAEncryption        8
#define OBJ_md5WithRSAEncryption        OBJ_pkcs,1L,4L

#define LN_pbeWithMD2AndDES_CBC         "pbeWithMD2AndDES-CBC"
#define NID_pbeWithMD2AndDES_CBC        9
#define OBJ_pbeWithMD2AndDES_CBC        OBJ_pkcs,5L,1L

#define LN_pbeWithMD5AndDES_CBC         "pbeWithMD5AndDES-CBC"
#define NID_pbeWithMD5AndDES_CBC        10
#define OBJ_pbeWithMD5AndDES_CBC        OBJ_pkcs,5L,3L

#define LN_X500                         "X500"
#define NID_X500                        11
#define OBJ_X500                        2L,5L

#define LN_X509                         "X509"
#define NID_X509                        12
#define OBJ_X509                        OBJ_X500,4L

#define SN_commonName                   "CN"
#define LN_commonName                   "commonName"
#define NID_commonName                  13
#define OBJ_commonName                  OBJ_X509,3L

#define SN_countryName                  "C"
#define LN_countryName                  "countryName"
#define NID_countryName                 14
#define OBJ_countryName                 OBJ_X509,6L

#define SN_localityName                 "L"
#define LN_localityName                 "localityName"
#define NID_localityName                15
#define OBJ_localityName                OBJ_X509,7L

/* Postal Address? PA */

/* should be "ST" (rfc1327) but MS uses 'S' */
#define SN_stateOrProvinceName          "ST"
#define LN_stateOrProvinceName          "stateOrProvinceName"
#define NID_stateOrProvinceName         16
#define OBJ_stateOrProvinceName         OBJ_X509,8L

#define SN_organizationName             "O"
#define LN_organizationName             "organizationName"
#define NID_organizationName            17
#define OBJ_organizationName            OBJ_X509,10L

#define SN_organizationalUnitName       "OU"
#define LN_organizationalUnitName       "organizationalUnitName"
#define NID_organizationalUnitName      18
#define OBJ_organizationalUnitName      OBJ_X509,11L

#define SN_rsa                          "RSA"
#define LN_rsa                          "rsa"
#define NID_rsa                         19
#define OBJ_rsa                         OBJ_X500,8L,1L,1L

#define LN_pkcs7                        "pkcs7"
#define NID_pkcs7                       20
#define OBJ_pkcs7                       OBJ_pkcs,7L

#define LN_pkcs7_data                   "pkcs7-data"
#define NID_pkcs7_data                  21
#define OBJ_pkcs7_data                  OBJ_pkcs7,1L

#define LN_pkcs7_signed                 "pkcs7-signedData"
#define NID_pkcs7_signed                22
#define OBJ_pkcs7_signed                OBJ_pkcs7,2L

#define LN_pkcs7_enveloped              "pkcs7-envelopedData"
#define NID_pkcs7_enveloped             23
#define OBJ_pkcs7_enveloped             OBJ_pkcs7,3L

#define LN_pkcs7_signedAndEnveloped     "pkcs7-signedAndEnvelopedData"
#define NID_pkcs7_signedAndEnveloped    24
#define OBJ_pkcs7_signedAndEnveloped    OBJ_pkcs7,4L

#define LN_pkcs7_digest                 "pkcs7-digestData"
#define NID_pkcs7_digest                25
#define OBJ_pkcs7_digest                OBJ_pkcs7,5L

#define LN_pkcs7_encrypted              "pkcs7-encryptedData"
#define NID_pkcs7_encrypted             26
#define OBJ_pkcs7_encrypted             OBJ_pkcs7,6L

#define LN_pkcs3                        "pkcs3"
#define NID_pkcs3                       27
#define OBJ_pkcs3                       OBJ_pkcs,3L

#define LN_dhKeyAgreement               "dhKeyAgreement"
#define NID_dhKeyAgreement              28
#define OBJ_dhKeyAgreement              OBJ_pkcs3,1L

#define SN_des_ecb                      "DES-ECB"
#define LN_des_ecb                      "des-ecb"
#define NID_des_ecb                     29
#define OBJ_des_ecb                     OBJ_algorithm,6L

#define SN_des_cfb64                    "DES-CFB"
#define LN_des_cfb64                    "des-cfb"
#define NID_des_cfb64                   30
/* IV + num */
#define OBJ_des_cfb64                   OBJ_algorithm,9L

#define SN_des_cbc                      "DES-CBC"
#define LN_des_cbc                      "des-cbc"
#define NID_des_cbc                     31
/* IV */
#define OBJ_des_cbc                     OBJ_algorithm,7L

#define SN_des_ede                      "DES-EDE"
#define LN_des_ede                      "des-ede"
#define NID_des_ede                     32
/* ?? */
#define OBJ_des_ede                     OBJ_algorithm,17L

#define SN_des_ede3                     "DES-EDE3"
#define LN_des_ede3                     "des-ede3"
#define NID_des_ede3                    33

#define SN_idea_cbc                     "IDEA-CBC"
#define LN_idea_cbc                     "idea-cbc"
#define NID_idea_cbc                    34

#define SN_idea_cfb64                   "IDEA-CFB"
#define LN_idea_cfb64                   "idea-cfb"
#define NID_idea_cfb64                  35

#define SN_idea_ecb                     "IDEA-ECB"
#define LN_idea_ecb                     "idea-ecb"
#define NID_idea_ecb                    36

#define SN_rc2_cbc                      "RC2-CBC"
#define LN_rc2_cbc                      "rc2-cbc"
#define NID_rc2_cbc                     37
#define OBJ_rc2_cbc                     OBJ_rsadsi,3L,2L

#define SN_rc2_ecb                      "RC2-ECB"
#define LN_rc2_ecb                      "rc2-ecb"
#define NID_rc2_ecb                     38

#define SN_rc2_cfb64                    "RC2-CFB"
#define LN_rc2_cfb64                    "rc2-cfb"
#define NID_rc2_cfb64                   39

#define SN_rc2_ofb64                    "RC2-OFB"
#define LN_rc2_ofb64                    "rc2-ofb"
#define NID_rc2_ofb64                   40

#define SN_sha                          "SHA"
#define LN_sha                          "sha"
#define NID_sha                         41
#define OBJ_sha                         OBJ_algorithm,18L

#define SN_shaWithRSAEncryption         "RSA-SHA"
#define LN_shaWithRSAEncryption         "shaWithRSAEncryption"
#define NID_shaWithRSAEncryption        42
#define OBJ_shaWithRSAEncryption        OBJ_algorithm,15L

#define SN_des_ede_cbc                  "DES-EDE-CBC"
#define LN_des_ede_cbc                  "des-ede-cbc"
#define NID_des_ede_cbc                 43

#define SN_des_ede3_cbc                 "DES-EDE3-CBC"
#define LN_des_ede3_cbc                 "des-ede3-cbc"
#define NID_des_ede3_cbc                44
#define OBJ_des_ede3_cbc                OBJ_rsadsi,3L,7L

#define SN_des_ofb64                    "DES-OFB"
#define LN_des_ofb64                    "des-ofb"
#define NID_des_ofb64                   45
#define OBJ_des_ofb64                   OBJ_algorithm,8L

#define SN_idea_ofb64                   "IDEA-OFB"
#define LN_idea_ofb64                   "idea-ofb"
#define NID_idea_ofb64                  46

#define LN_pkcs9                        "pkcs9"
#define NID_pkcs9                       47
#define OBJ_pkcs9                       OBJ_pkcs,9L

#define SN_pkcs9_emailAddress           "EMAIL"
#define LN_pkcs9_emailAddress           "emailAddress"
#define NID_pkcs9_emailAddress          48
#define OBJ_pkcs9_emailAddress          OBJ_pkcs9,1L

#define LN_pkcs9_unstructuredName       "unstructuredName"
#define NID_pkcs9_unstructuredName      49
#define OBJ_pkcs9_unstructuredName      OBJ_pkcs9,2L

#define LN_pkcs9_contentType            "contentType"
#define NID_pkcs9_contentType           50
#define OBJ_pkcs9_contentType           OBJ_pkcs9,3L

#define LN_pkcs9_messageDigest          "messageDigest"
#define NID_pkcs9_messageDigest         51
#define OBJ_pkcs9_messageDigest         OBJ_pkcs9,4L

#define LN_pkcs9_signingTime            "signingTime"
#define NID_pkcs9_signingTime           52
#define OBJ_pkcs9_signingTime           OBJ_pkcs9,5L

#define LN_pkcs9_countersignature       "countersignature"
#define NID_pkcs9_countersignature      53
#define OBJ_pkcs9_countersignature      OBJ_pkcs9,6L

#define LN_pkcs9_challengePassword      "challengePassword"
#define NID_pkcs9_challengePassword     54
#define OBJ_pkcs9_challengePassword     OBJ_pkcs9,7L

#define LN_pkcs9_unstructuredAddress    "unstructuredAddress"
#define NID_pkcs9_unstructuredAddress   55
#define OBJ_pkcs9_unstructuredAddress   OBJ_pkcs9,8L

#define LN_pkcs9_extCertAttributes      "extendedCertificateAttributes"
#define NID_pkcs9_extCertAttributes     56
#define OBJ_pkcs9_extCertAttributes     OBJ_pkcs9,9L

#define SN_netscape                     "Netscape"
#define LN_netscape                     "Netscape Communications Corp."
#define NID_netscape                    57
#define OBJ_netscape                    2L,16L,840L,1L,113730L

#define SN_netscape_cert_extension      "nsCertExt"
#define LN_netscape_cert_extension      "Netscape Certificate Extension"
#define NID_netscape_cert_extension     58
#define OBJ_netscape_cert_extension     OBJ_netscape,1L

#define SN_netscape_data_type           "nsDataType"
#define LN_netscape_data_type           "Netscape Data Type"
#define NID_netscape_data_type          59
#define OBJ_netscape_data_type          OBJ_netscape,2L

#define SN_des_ede_cfb64                "DES-EDE-CFB"
#define LN_des_ede_cfb64                "des-ede-cfb"
#define NID_des_ede_cfb64               60

#define SN_des_ede3_cfb64               "DES-EDE3-CFB"
#define LN_des_ede3_cfb64               "des-ede3-cfb"
#define NID_des_ede3_cfb64              61

#define SN_des_ede_ofb64                "DES-EDE-OFB"
#define LN_des_ede_ofb64                "des-ede-ofb"
#define NID_des_ede_ofb64               62

#define SN_des_ede3_ofb64               "DES-EDE3-OFB"
#define LN_des_ede3_ofb64               "des-ede3-ofb"
#define NID_des_ede3_ofb64              63

#define SN_sha1                         "SHA1"
#define LN_sha1                         "sha1"
#define NID_sha1                        64
#define OBJ_sha1                        OBJ_algorithm,26L

#define SN_sha1WithRSAEncryption        "RSA-SHA1"
#define LN_sha1WithRSAEncryption        "sha1WithRSAEncryption"
#define NID_sha1WithRSAEncryption       65
#define OBJ_sha1WithRSAEncryption       OBJ_pkcs,1L,5L

#define SN_dsaWithSHA                   "DSA-SHA"
#define LN_dsaWithSHA                   "dsaWithSHA"
#define NID_dsaWithSHA                  66
#define OBJ_dsaWithSHA                  OBJ_algorithm,13L

#define SN_dsa_2                        "DSA-old"
#define LN_dsa_2                        "dsaEncryption-old"
#define NID_dsa_2                       67
#define OBJ_dsa_2                       OBJ_algorithm,12L

/* proposed by microsoft to RSA */
#define LN_pbeWithSHA1AndRC2_CBC        "pbeWithSHA1AndRC2-CBC"
#define NID_pbeWithSHA1AndRC2_CBC       68
#define OBJ_pbeWithSHA1AndRC2_CBC       OBJ_pkcs,5L,11L

/* proposed by microsoft to RSA */
#define LN_pbeWithSHA1AndRC4            "pbeWithSHA1AndRC4"
#define NID_pbeWithSHA1AndRC4           69
#define OBJ_pbeWithSHA1AndRC4           OBJ_pkcs,5L,12L

#define SN_dsaWithSHA1_2                "DSA-SHA1-old"
#define LN_dsaWithSHA1_2                "dsaWithSHA1-old"
#define NID_dsaWithSHA1_2               70
#define OBJ_dsaWithSHA1_2               OBJ_algorithm,27L

#define SN_netscape_cert_type           "nsCertType"
#define LN_netscape_cert_type           "Netscape Cert Type"
#define NID_netscape_cert_type          71
#define OBJ_netscape_cert_type          OBJ_netscape_cert_extension,1L

#define SN_netscape_base_url            "nsBaseUrl"
#define LN_netscape_base_url            "Netscape Base Url"
#define NID_netscape_base_url           72
#define OBJ_netscape_base_url           OBJ_netscape_cert_extension,2L

#define SN_netscape_revocation_url      "nsRevocationUrl"
#define LN_netscape_revocation_url      "Netscape Revocation Url"
#define NID_netscape_revocation_url     73
#define OBJ_netscape_revocation_url     OBJ_netscape_cert_extension,3L

#define SN_netscape_ca_revocation_url   "nsCaRevocationUrl"
#define LN_netscape_ca_revocation_url   "Netscape CA Revocation Url"
#define NID_netscape_ca_revocation_url  74
#define OBJ_netscape_ca_revocation_url  OBJ_netscape_cert_extension,4L

#define SN_netscape_renewal_url         "nsRenewalUrl"
#define LN_netscape_renewal_url         "Netscape Renewal Url"
#define NID_netscape_renewal_url        75
#define OBJ_netscape_renewal_url        OBJ_netscape_cert_extension,7L

#define SN_netscape_ca_policy_url       "nsCaPolicyUrl"
#define LN_netscape_ca_policy_url       "Netscape CA Policy Url"
#define NID_netscape_ca_policy_url      76
#define OBJ_netscape_ca_policy_url      OBJ_netscape_cert_extension,8L

#define SN_netscape_ssl_server_name     "nsSslServerName"
#define LN_netscape_ssl_server_name     "Netscape SSL Server Name"
#define NID_netscape_ssl_server_name    77
#define OBJ_netscape_ssl_server_name    OBJ_netscape_cert_extension,12L

#define SN_netscape_comment             "nsComment"
#define LN_netscape_comment             "Netscape Comment"
#define NID_netscape_comment            78
#define OBJ_netscape_comment            OBJ_netscape_cert_extension,13L

#define SN_netscape_cert_sequence       "nsCertSequence"
#define LN_netscape_cert_sequence       "Netscape Certificate Sequence"
#define NID_netscape_cert_sequence      79
#define OBJ_netscape_cert_sequence      OBJ_netscape_data_type,5L

#define SN_desx_cbc                     "DESX-CBC"
#define LN_desx_cbc                     "desx-cbc"
#define NID_desx_cbc                    80

#define SN_id_ce                        "id-ce"
#define NID_id_ce                       81
#define OBJ_id_ce                       2L,5L,29L

#define SN_subject_key_identifier       "subjectKeyIdentifier"
#define LN_subject_key_identifier       "X509v3 Subject Key Identifier"
#define NID_subject_key_identifier      82
#define OBJ_subject_key_identifier      OBJ_id_ce,14L

#define SN_key_usage                    "keyUsage"
#define LN_key_usage                    "X509v3 Key Usage"
#define NID_key_usage                   83
#define OBJ_key_usage                   OBJ_id_ce,15L

#define SN_private_key_usage_period     "privateKeyUsagePeriod"
#define LN_private_key_usage_period     "X509v3 Private Key Usage Period"
#define NID_private_key_usage_period    84
#define OBJ_private_key_usage_period    OBJ_id_ce,16L

#define SN_subject_alt_name             "subjectAltName"
#define LN_subject_alt_name             "X509v3 Subject Alternative Name"
#define NID_subject_alt_name            85
#define OBJ_subject_alt_name            OBJ_id_ce,17L

#define SN_issuer_alt_name              "issuerAltName"
#define LN_issuer_alt_name              "X509v3 Issuer Alternative Name"
#define NID_issuer_alt_name             86
#define OBJ_issuer_alt_name             OBJ_id_ce,18L

#define SN_basic_constraints            "basicConstraints"
#define LN_basic_constraints            "X509v3 Basic Constraints"
#define NID_basic_constraints           87
#define OBJ_basic_constraints           OBJ_id_ce,19L

#define SN_crl_number                   "crlNumber"
#define LN_crl_number                   "X509v3 CRL Number"
#define NID_crl_number                  88
#define OBJ_crl_number                  OBJ_id_ce,20L

#define SN_certificate_policies         "certificatePolicies"
#define LN_certificate_policies         "X509v3 Certificate Policies"
#define NID_certificate_policies        89
#define OBJ_certificate_policies        OBJ_id_ce,32L

#define SN_authority_key_identifier     "authorityKeyIdentifier"
#define LN_authority_key_identifier     "X509v3 Authority Key Identifier"
#define NID_authority_key_identifier    90
#define OBJ_authority_key_identifier    OBJ_id_ce,35L

#define SN_bf_cbc                       "BF-CBC"
#define LN_bf_cbc                       "bf-cbc"
#define NID_bf_cbc                      91

#define SN_bf_ecb                       "BF-ECB"
#define LN_bf_ecb                       "bf-ecb"
#define NID_bf_ecb                      92

#define SN_bf_cfb64                     "BF-CFB"
#define LN_bf_cfb64                     "bf-cfb"
#define NID_bf_cfb64                    93

#define SN_bf_ofb64                     "BF-OFB"
#define LN_bf_ofb64                     "bf-ofb"
#define NID_bf_ofb64                    94

#define SN_mdc2                         "MDC2"
#define LN_mdc2                         "mdc2"
#define NID_mdc2                        95
#define OBJ_mdc2                        2L,5L,8L,3L,101L
/* An alternative?                      1L,3L,14L,3L,2L,19L */

#define SN_mdc2WithRSA                  "RSA-MDC2"
#define LN_mdc2WithRSA                  "mdc2withRSA"
#define NID_mdc2WithRSA                 96
#define OBJ_mdc2WithRSA                 2L,5L,8L,3L,100L

#define SN_rc4_40                       "RC4-40"
#define LN_rc4_40                       "rc4-40"
#define NID_rc4_40                      97

#define SN_rc2_40_cbc                   "RC2-40-CBC"
#define LN_rc2_40_cbc                   "rc2-40-cbc"
#define NID_rc2_40_cbc                  98

#define SN_givenName                    "G"
#define LN_givenName                    "givenName"
#define NID_givenName                   99
#define OBJ_givenName                   OBJ_X509,42L

#define SN_surname                      "SN"
#define LN_surname                      "surname"
#define NID_surname                     100
#define OBJ_surname                     OBJ_X509,4L

#define SN_initials                     "I"
#define LN_initials                     "initials"
#define NID_initials                    101
#define OBJ_initials                    OBJ_X509,43L

#define SN_uniqueIdentifier             "X500UID"
#define LN_uniqueIdentifier             "x500UniqueIdentifier"
#define NID_uniqueIdentifier            102
#define OBJ_uniqueIdentifier            OBJ_X509,45L

#define SN_crl_distribution_points      "crlDistributionPoints"
#define LN_crl_distribution_points      "X509v3 CRL Distribution Points"
#define NID_crl_distribution_points     103
#define OBJ_crl_distribution_points     OBJ_id_ce,31L

#define SN_md5WithRSA                   "RSA-NP-MD5"
#define LN_md5WithRSA                   "md5WithRSA"
#define NID_md5WithRSA                  104
#define OBJ_md5WithRSA                  OBJ_algorithm,3L

#define SN_serialNumber                 "SERIAL"
#define LN_serialNumber                 "serialNumber"
#define NID_serialNumber                105
#define OBJ_serialNumber                OBJ_X509,5L

#define SN_title                        "T"
#define LN_title                        "title"
#define NID_title                       106
#define OBJ_title                       OBJ_X509,12L

#define SN_description                  "D"
#define LN_description                  "description"
#define NID_description                 107
#define OBJ_description                 OBJ_X509,13L

/* CAST5 is CAST-128, corresponds to the documentation */
#define SN_cast5_cbc                    "CAST5-CBC"
#define LN_cast5_cbc                    "cast5-cbc"
#define NID_cast5_cbc                   108
#define OBJ_cast5_cbc                   1L,2L,840L,113533L,7L,66L,10L

#define SN_cast5_ecb                    "CAST5-ECB"
#define LN_cast5_ecb                    "cast5-ecb"
#define NID_cast5_ecb                   109

#define SN_cast5_cfb64                  "CAST5-CFB"
#define LN_cast5_cfb64                  "cast5-cfb"
#define NID_cast5_cfb64                 110

#define SN_cast5_ofb64                  "CAST5-OFB"
#define LN_cast5_ofb64                  "cast5-ofb"
#define NID_cast5_ofb64                 111

#define LN_pbeWithMD5AndCast5_CBC       "pbeWithMD5AndCast5CBC"
#define NID_pbeWithMD5AndCast5_CBC      112
#define OBJ_pbeWithMD5AndCast5_CBC      1L,2L,840L,113533L,7L,66L,12L

/* Sun uses this identifier
 * id-dsa-with-sha1 ID  ::= {
 *   iso(1) member-body(2) us(840) x9-57 (10040) x9cm(4) 3 }
 */
#define SN_dsaWithSHA1                  "DSA-SHA1"
#define LN_dsaWithSHA1                  "dsaWithSHA1"
#define NID_dsaWithSHA1                 113
#define OBJ_dsaWithSHA1                 1L,2L,840L,10040L,4L,3L

#define NID_md5_sha1                    114
#define SN_md5_sha1                     "MD5-SHA1"
#define LN_md5_sha1                     "md5-sha1"

#define SN_sha1WithRSA                  "RSA-SHA1-2"
#define LN_sha1WithRSA                  "sha1WithRSA"
#define NID_sha1WithRSA                 115
#define OBJ_sha1WithRSA                 OBJ_algorithm,29L

#define SN_dsa                          "DSA"
#define LN_dsa                          "dsaEncryption"
#define NID_dsa                         116
#define OBJ_dsa                         1L,2L,840L,10040L,4L,1L

#define SN_ripemd160                    "RIPEMD160"
#define LN_ripemd160                    "ripemd160"
#define NID_ripemd160                   117
#define OBJ_ripemd160                   1L,3L,36L,3L,2L,1L

#define SN_rc5_cbc_no_pad               "RC5-CBC-NO-PAD"
#define LN_rc5_cbc_no_pad               "rc5-cbc-no-pad"
#define NID_rc5_cbc_no_pad              118
#define OBJ_rc5_cbc_no_pad              OBJ_rsadsi,3L,8L

/* The name should actually be rsaSignatureWithripemd160, but the form
 * here continues the convention used with other definitions here.
 */
#define SN_ripemd160WithRSA             "RSA-RIPEMD160"
#define LN_ripemd160WithRSA             "ripemd160WithRSA"
#define NID_ripemd160WithRSA            119
#define OBJ_ripemd160WithRSA            1L,3L,36L,3L,3L,1L,2L

/* Taken from rfc2040
 *  RC5_CBC_Parameters ::= SEQUENCE {
 *      version           INTEGER (v1_0(16)),
 *      rounds            INTEGER (8..127),
 *      blockSizeInBits   INTEGER (64, 128),
 *      iv                OCTET STRING OPTIONAL
 *      }
 */
#define SN_rc5_cbc                      "RC5-CBC"
#define LN_rc5_cbc                      "rc5-cbc"
#define NID_rc5_cbc                     120
#define OBJ_rc5_cbc                     OBJ_rsadsi,3L,9L

#define SN_rc5_ecb                      "RC5-ECB"
#define LN_rc5_ecb                      "rc5-ecb"
#define NID_rc5_ecb                     121

#define SN_rc5_cfb64                    "RC5-CFB"
#define LN_rc5_cfb64                    "rc5-cfb"
#define NID_rc5_cfb64                   122

#define SN_rc5_ofb64                    "RC5-OFB"
#define LN_rc5_ofb64                    "rc5-ofb"
#define NID_rc5_ofb64                   123

#define SN_rle_compression              "RLE"
#define LN_rle_compression              "run length compression"
#define NID_rle_compression             124
#define OBJ_rle_compression             1L,1L,1L,1L,666L.1L

#define SN_zlib_compression             "ZLIB"
#define LN_zlib_compression             "zlib compression"
#define NID_zlib_compression            125
#define OBJ_zlib_compression            1L,1L,1L,1L,666L.2L

#define SN_ext_key_usage                "extendedKeyUsage"
#define LN_ext_key_usage                "X509v3 Extended Key Usage"
#define NID_ext_key_usage               126
#define OBJ_ext_key_usage               OBJ_id_ce,37L

#define SN_ms_sgc                       "msSGC"
#define LN_ms_sgc                       "Microsoft Server Gated Crypto"
#define NID_ms_sgc                      137
#define OBJ_ms_sgc                      1L,3L,6L,1L,4L,1L,311L,10L,3L,3L

#define SN_ns_sgc                       "nsSGC"
#define LN_ns_sgc                       "Netscape Server Gated Crypto"
#define NID_ns_sgc                      139
#define OBJ_ns_sgc                      OBJ_netscape,4L,1L

/* Taken from csrc.nist.gov/csor/algorithms.htm
 * I am not shure about SN_xx,
 * This list 128,192 & 256 in all 4 modes
 * Please note all NIDs are relative to the nist-aes one.
 */

#define SN_nistAlgorithms1              "nistAlgorithms1"
#define LN_nistAlgorithms1              "nist Algorthms 1"
#define NID_nistAlgorithms1             140
#define OBJ_nistAlgorithms1             2L,16L,840L,1L,101L,3L,4L,1L

#define SN_aes128_ecb                   "AES128-ECB"
#define LN_aes128_ecb                   "aes128-ecb"
#define NID_aes128_ecb                  (NID_nistAlgorithms1+1)
#define OBJ_aes128_ecb                  OBJ_nistAlgorithms1,1L

#define SN_aes128_cbc                   "AES128-CBC"
#define LN_aes128_cbc                   "aes128-cbc"
#define NID_aes128_cbc                  (NID_nistAlgorithms1+2)
#define OBJ_aes128_cbc                  OBJ_nistAlgorithms1,2L

#define SN_aes128_ofb                   "AES128-OFB"
#define LN_aes128_ofb                   "aes128-ofb"
#define NID_aes128_ofb                  (NID_nistAlgorithms1+3)
#define OBJ_aes128_ofb                  OBJ_nistAlgorithms1,3L

#define SN_aes128_cfb                   "AES128-CFB"
#define LN_aes128_cfb                   "aes128-cfb"
#define NID_aes128_cfb                  (NID_nistAlgorithms1+4)
#define OBJ_aes128_cfb                  OBJ_nistAlgorithms1,4L

#define SN_aes192_ecb                   "AES192-ECB"
#define LN_aes192_ecb                   "aes192-ecb"
#define NID_aes192_ecb                  (NID_nistAlgorithms1+5)
#define OBJ_aes192_ecb                  OBJ_nistAlgorithms1,21L

#define SN_aes192_cbc                   "AES192-CBC"
#define LN_aes192_cbc                   "aes192-cbc"
#define NID_aes192_cbc                  (NID_nistAlgorithms1+6)
#define OBJ_aes192_cbc                  OBJ_nistAlgorithms1,22L

#define SN_aes192_ofb                   "AES192-OFB"
#define LN_aes192_ofb                   "aes192-ofb"
#define NID_aes192_ofb                  (NID_nistAlgorithms1+7)
#define OBJ_aes192_ofb                  OBJ_nistAlgorithms1,23L

#define SN_aes192_cfb                   "AES192-CFB"
#define LN_aes192_cfb                   "aes192-cfb"
#define NID_aes192_cfb                  (NID_nistAlgorithms1+8)
#define OBJ_aes192_cfb                  OBJ_nistAlgorithms1,24L

#define SN_aes256_ecb                   "AES256-ECB"
#define LN_aes256_ecb                   "aes256-ecb"
#define NID_aes256_ecb                  (NID_nistAlgorithms1+9)
#define OBJ_aes256_ecb                  OBJ_nistAlgorithms1,41L

#define SN_aes256_cbc                   "AES256-CBC"
#define LN_aes256_cbc                   "aes256-cbc"
#define NID_aes256_cbc                  (NID_nistAlgorithms1+10)
#define OBJ_aes256_cbc                  OBJ_nistAlgorithms1,42L

#define SN_aes256_ofb                   "AES256-OFB"
#define LN_aes256_ofb                   "aes256-ofb"
#define NID_aes256_ofb                  (NID_nistAlgorithms1+11)
#define OBJ_aes256_ofb                  OBJ_nistAlgorithms1,43L

#define SN_aes256_cfb                   "AES256-CFB"
#define LN_aes256_cfb                   "aes256-cfb"
#define NID_aes256_cfb                  (NID_nistAlgorithms1+12)
#define OBJ_aes256_cfb                  OBJ_nistAlgorithms1,44L

#define SN_id_mgf                       "idMGF"
#define LN_id_mgf                       "Mask Generation function OAEP padding"
#define NID_id_mgf                      153
#define OBJ_id_mgf                      OBJ_pkcs,1L,8L

#define SN_id_pspecified                "idpSPEC"
#define LN_id_pspecified                "Parameters Source Function OAEP padding"
#define NID_id_pspecified               154
#define OBJ_id_pspecified               OBJ_pkcs,1L,9L

#define SN_rsaes_oaep                   "OAEP"
#define LN_rsaes_oaep                   "RSAES OAEP encryption scheme"
#define NID_rsaes_oaep                  155
#define OBJ_rsaes_oaep                  OBJ_pkcs,1L,7L

#define SN_des_40_cbc                   "DES-40-CBC"
#define LN_des_40_cbc                   "des-40-cbc"
#define NID_des_40_cbc                  156

#define SN_des_40_cfb                   "DES-40-CFB"
#define LN_des_40_cfb                   "des-40-cfb"
#define NID_des_40_cfb                  157

#define SN_rc6_ecb                      "RC6-ECB"
#define LN_rc6_ecb                      "rc6-ecb"
#define NID_rc6_ecb                     158
#define OBJ_rc6_ebc                     OBJ_rsadsi,3L,11L,1L

#define SN_rc6_cbc                      "RC6-CBC"
#define LN_rc6_cbc                      "rc6-cbc"
#define NID_rc6_cbc                     159
#define OBJ_rc6_cbc                     OBJ_rsadsi,3L,11L,2L

#define SN_rc6_ofb128                   "RC6-OFB"
#define LN_rc6_ofb128                   "rc6-ofb"
#define NID_rc6_ofb128                  160
#define OBJ_rc6_ofb128                  OBJ_rsadsi,3L,11L,3L

#define SN_rc6_cfb128                   "RC6-CFB"
#define LN_rc6_cfb128                   "rc6-cfb"
#define NID_rc6_cfb128                  161
#define OBJ_rc6_cfb128                  OBJ_rsadsi,3L,11L,4L

/* SHA2 - 256, 384 and 512 OID taken from:

        PKCS #1 v2.1: RSA Cryptography Standard
        RSA Laboratories
        DRAFT 2 - January 5, 2001
 */
#define SN_sha256                       "SHA256"
#define LN_sha256                       "sha256"
#define NID_sha256                      162
#define OBJ_sha256                      2L,16L,840L,1L,101L,3L,4L,2L,1L

#define SN_sha384                       "SHA384"
#define LN_sha384                       "sha384"
#define NID_sha384                      163
#define OBJ_sha384                      2L,16L,840L,1L,101L,3L,4L,2L,2L

#define SN_sha512                       "SHA512"
#define LN_sha512                       "sha512"
#define NID_sha512                      164
#define OBJ_sha512                      2L,16L,840L,1L,101L,3L,4L,2L,3L

/* More X500 and LDAP attribute types */
#define SN_street                       "STREET"
#define LN_street                       "street"
#define NID_street                      166
#define OBJ_street                      OBJ_X509,9L

#define SN_generationQualifier          "GQ"
#define LN_generationQualifier          "generationQualifier"
#define NID_generationQualifier         167
#define OBJ_generationQualifier         OBJ_X509,44L

#define SN_dnQualifier                  "DNQ"
#define LN_dnQualifier                  "dnQualifier"
#define NID_dnQualifier                 168
#define OBJ_dnQualifier                 OBJ_X509,46L

#define SN_userID                       "UID"
#define LN_userID                       "userID"
#define NID_userID                      169
#define OBJ_userID                      0L,9L,2342L,19200300L,100L,1L,1L

#define SN_domainComponent              "DC"
#define LN_domainComponent              "domainComponent"
#define NID_domainComponent             170
#define OBJ_domainComponent             0L,9L,2342L,19200300L,100L,1L,25L

#define SN_reason_code                  "reasonCode"
#define LN_reason_code                  "X509v3 CRL Reason Code"
#define NID_reason_code                 171
#define OBJ_reason_code                 OBJ_id_ce,21L

#define SN_instruction_code             "instructionCode"
#define LN_instruction_code             "X509v3 CRL Instruction Code"
#define NID_instruction_code            172
#define OBJ_instruction_code            OBJ_id_ce,23L

#define SN_invalidity_date              "invalidityDate"
#define LN_invalidity_date              "X509v3 CRL Invalidity Date"
#define NID_invalidity_date             173
#define OBJ_invalidity_date             OBJ_id_ce,24L

#define SN_delta_crl_indicator          "deltaCRLIndicator"
#define LN_delta_crl_indicator          "X509v3 Delta CRL Indicator"
#define NID_delta_crl_indicator         174
#define OBJ_delta_crl_indicator         OBJ_id_ce,27L

#define SN_issuing_distribution_point   "issuingDistributionPoint"
#define LN_issuing_distribution_point   "X509v3 CRL Issuing Distribution Point"
#define NID_issuing_distribution_point  175
#define OBJ_issuing_distribution_point  OBJ_id_ce,28L

#define SN_certificate_issuer           "certificateIssuer"
#define LN_certificate_issuer           "X509v3 CRL Certificate Issuer"
#define NID_certificate_issuer          176
#define OBJ_certificate_issuer          OBJ_id_ce,29L

#define SN_name_constraints             "nameConstraints"
#define LN_name_constraints             "X509v3 CRL Name Constraints"
#define NID_name_constraints            177
#define OBJ_name_constraints            OBJ_id_ce,30L

#define SN_ecc                          "ecc"
#define LN_ecc                          "Elliptic Curve Cryptography"
#define NID_ecc                         178
#define OBJ_ecc                         1L,2L,840L,10045L,2L,1L

#define SN_ECDSAwithSHA1                "ECDSA-with-SHA1"
#define LN_ECDSAwithSHA1                "Elliptic Curve DSA with SHA1"
#define NID_ECDSAwithSHA1               179
#define OBJ_ECDSAwithSHA1               1L,2L,840L,10045L,4L,1L

#define SN_id_kp                        "id_kp"
#define NID_id_kp                       180
#define OBJ_id_kp                       1L,3L,6L,1L,5L,5L,7L,3L 

#define SN_serverAuth                   "serverAuth"
#define LN_serverAuth                   "Server Authenication Key Usage Extension"
#define NID_serverAuth                  181 
#define OBJ_serverAuth                  OBJ_id_kp,1L

#define SN_clientAuth                   "clientAuth"
#define LN_clientAuth                   "Client Authentication Key Usage Extension"
#define NID_clientAuth                  182
#define OBJ_clientAuth                  OBJ_id_kp,2L

#define SN_codeSigning                  "codeSigning"
#define LN_codeSigning                  "Code Signing Key Usage Extension"
#define NID_codeSigning                 183
#define OBJ_codeSigning                 OBJ_id_kp,3L

#define SN_emailProtection              "emailProtection"
#define LN_emailProtection              "Email Protection Key Usage Extension"
#define NID_emailProtection             184
#define OBJ_emailProtection             OBJ_id_kp,4L

#define SN_ipsecEndSystem               "ipsecEndSystem"
#define LN_ipsecEndSystem               "IPSec End System Key Usage Extension"
#define NID_ipsecEndSystem              185
#define OBJ_ipsecEndSystem              OBJ_id_kp,5L

#define SN_ipsecTunnel                  "ipsecTunnel"
#define LN_ipsecTunnel                  "IPSec Tunnel Key Usage Extension"
#define NID_ipsecTunnel                 186
#define OBJ_ipsecTunnel                 OBJ_id_kp,6L

#define SN_ipsecUser                    "ipsecUser"
#define LN_ipsecUser                    "IPSec User Key Usage Extension"
#define NID_ipsecUser                   187
#define OBJ_ipsecUser                   OBJ_id_kp,7L

#define SN_timeStamping                 "timeStamping"
#define LN_timeStamping                 "Time Stamping Key Usage Extension"
#define NID_timeStamping                188
#define OBJ_timeStamping                OBJ_id_kp,8L

#define SN_ocspSigning                  "oscpSigning"
#define LN_ocspSigning                  "OCSP Key Usage Extension"
#define NID_ocspSigning                 189
#define OBJ_ocspSigning                 OBJ_id_kp,9L

/*
 * Exported function protoypes
 */

int R_NID_DIGEST_to_string(int nid, unsigned int max_str_len, char *str);
int R_NID_DIGEST_from_string(char *str, int *nid);

#ifdef  __cplusplus
}
#endif
#endif /* HEADER_COMMON_R_NID_H */

