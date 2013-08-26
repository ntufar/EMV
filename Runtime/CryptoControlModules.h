#ifndef CRYPTOCONTROLMODULES_H
#define CRYPTOCONTROLMODULES_H

//cpp files
#define MOD_CryptoControl_Interface 0x01
#define MOD_CryptoControl_Server     0x02
#define MOD_CryptoInterface         0x03
#define MOD_CryptoOperationEvent    0x04

//interface functions
#define CRYPTO_openService        0x01
#define CRYPTO_connectedServices  0x02
#define CRYPTO_addOperationEvent  0x03
#define CRYPTO_encrypt            0x04
#define CRYPTO_decrypt            0x07
#define CRYPTO_initKey            0x08
#define CRYPTO_calcHash           0x09
#define CRYPTO_randomNumber       0x0A
#define CRYPTO_open               0x0C
#define CRYPTO_close              0x0D


#endif