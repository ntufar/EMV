// CryptoControl Service
// CryptoControl Interface Declaration.
//
// This control provides an interface to cryptographic services, such as 
// encription/decription of byte string, calculating a hash number, and 
// generating a random number.

#ifndef CRYPTOINTERFACE_H
#define CRYPTOINTERFACE_H 

#include "ServiceInterface.h"
#include "custom_types.h"
#include "CryptoErrors.h"

class CryptoInterface :
	public ServiceInterface
{
public:
	CryptoInterface(void);
	virtual ~CryptoInterface(void);

	virtual int initKeyCA (const byte *RID, unsigned int ridLen, 
						   const byte *PKI, unsigned int pkiLen,
						   unsigned int *modulus) = 0;
	virtual int initKey (const byte *keyMod, unsigned int uiKeyModLen, 
						 const byte *keyExp, unsigned int uikeyExpLen,
						 unsigned int uiCryptoAlgID, 
						 unsigned int uiHashAlgID) = 0;
	virtual int encrypt (byte *pDataBuf,
						 unsigned int uiDataLen) = 0;
	virtual int decrypt (byte *pCipherBuf,
						 unsigned int uiCipherLen) = 0;
	virtual int calcHash (byte *pMsg,
						  unsigned int uiMsgLen) = 0;
	virtual int randomNumber (unsigned int uiAlgID, unsigned int uiLength) = 0;
	virtual byte getCryptoAlgID() = 0;
	virtual byte getHashAlgID() = 0;
	virtual int checkCAIntegrity(int *keysVerified) = 0;
};

#endif

