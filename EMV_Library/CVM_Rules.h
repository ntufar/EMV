/*
CVM_Rules.h
Constants used in Cardholder Verification processing
*/
#ifndef CVM_RULES_H
#define CVM_RULES_H

//Errors
#define CVM_CONDITION_NOT_RECOGNIZED   0xA1000001
#define CVM_CONDITION_FAILED           0xA1000002
#define CVM_FAILED					   0xA1000003
#define CVM_METHOD_NOT_RECOGNIZED      0xA1000004
#define CVM_METHOD_NOT_SUPPORETED      0xA1000005
#define CVM_FORSED_FAILURE             0xA1000006

// CVM Conditions
#define COND_ALWAYS         0x00
#define COND_CASH           0x01
#define COND_NOTCASH        0x02
#define COND_IF_SUPPORTED   0x03
#define COND_UNDER_X_AMOUNT 0x06
#define COND_OVER_X_AMOUNT  0x07
#define COND_UNDER_Y_AMOUNT 0x08
#define COND_OVER_Y_AMOUNT  0x09

// CVM Types
#define CVM_TYPE_FAIL                   0x0000
#define CVM_TYPE_PLAINTEXT_PIN_ICC      0x0100
#define CVM_TYPE_ENCIPH_PIN_ONLINE      0x0200
#define CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN 0x0300
#define CVM_TYPE_ENCIPH_PIN_ICC         0x0400
#define CVM_TYPE_ENCIPH_PIN_ICC_SIGN    0x0500
#define CVM_TYPE_SIGN                   0x1e00
#define CVM_TYPE_NO_CVM                 0x1f00

// Control flow flag
#define CVM_APPLY_NEXT                  0x4000



#endif

