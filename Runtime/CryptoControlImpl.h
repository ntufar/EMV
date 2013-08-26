#ifndef CRYPTOCONTROLIMPL_H
#define CRYPTOCONTROLIMPL_H

#include "CryptoOperationEventImpl.h"
#include "RSA/cryptocme.h"
#include "RSAPublicKey.h"
#include "CryptoMeErrors.h"
#include "ServiceControl.h"
#include "OperationEvent.h"
#include "ServiceControl.h"
#include "amAdder.h"
#include "EventAdder.h"
#include <wintypes.h>
#include "patch.h"
#define CRYPTO_REG_KEY "Software\\SCS\\SmartPOS\\TerminalInfo\\Crypto"

typedef int (* INITKEYCA)(UINT_KEY Key,
                                                const byte *RID,
                                                unsigned int ridLen,
                                                const byte *PKI, unsigned int pkiLen,
                                                unsigned int *modulus);
typedef int (* INITKEY) (UINT_KEY Key,
                                                 const byte *keyMod, unsigned int uiKeyModLen,
                                                 const byte *keyExp, unsigned int uikeyExpLen,
                                                 unsigned int uiCryptoAlgID, unsigned int uiHashAlgID);
typedef int (* ENCRYPT)(UINT_KEY Key,
                                                byte *pDataBuf,
                                                unsigned int uiDataLen);
typedef int (* DECRYPT)(UINT_KEY Key,
                                                byte *pCipherBuf,
                                                unsigned int uiCipherLen);
typedef int (* CALCHASH)(UINT_KEY Key,
                                                 byte *pMsg,
                                                 unsigned int uiMsgLen);
typedef int (* RANDOMNUMBER)(UINT_KEY Key,
                                                         unsigned int uiAlgID, unsigned int uiLength);
                                                                                                                             
typedef byte (* GETCRYPTOALGID)(UINT_KEY Key);
typedef byte (* GETHASHALGID)(UINT_KEY Key);
typedef int (* CHECKCAINTEGRITY)(UINT_KEY Key, int *keysVerified);




class CryptoControlImpl :
	public EventAdder,
	public OperationEvent,
	public amAdder,
	public ServiceControl
{
public:
	CryptoControlImpl(void);
	virtual ~CryptoControlImpl(void);

	virtual int initKeyCA (const byte *RID, unsigned int ridLen, 
						   const byte *PKI, unsigned int pkiLen,
						   unsigned int *modulus);
	virtual int initKey (const byte *keyMod, unsigned int uiKeyModLen, 
						 const byte *keyExp, unsigned int uikeyExpLen,
						 unsigned int uiCryptoAlgID, unsigned int uiHashAlgID);
	virtual int encrypt (byte *pDataBuf,
						 unsigned int uiDataLen);
	virtual int decrypt (byte *pCipherBuf,
						 unsigned int uiCipherLen);
	virtual int calcHash (byte *pMsg,
						  unsigned int uiMsgLen);
	virtual int randomNumber (unsigned int uiAlgID, unsigned int uiLength);
	virtual byte getCryptoAlgID();
	virtual byte getHashAlgID();

	virtual int checkCAIntegrity(int *keysVerified);

private:
	// Members
	R_LIB_CTX  *lib_ctx;  // Library context
    	R_CR_CTX   *ctx;      // Cryptographic context
	R_PKEY_CTX *pkey_ctx; // Key context
	long LibStatus;

	byte *pubKeyArr;
	unsigned pubKeyLength;
	unsigned uiCryptoAlgID;
	unsigned uiHashAlgID;

private:
	// Member functions
	long checkInitialization (bool checkEvent = true);
	char hexChar2AsciiChar(byte btVal);
	char* hex2ascii(const byte *bRID, unsigned int ridLen);
	void closeRegKeys(HKEY hKey, HKEY hRID, HKEY hPKI);
	int GetRegistryBinValue (HKEY hKey, 
							 const char *subKey, 
							 DWORD dwType, 
							 BYTE **ppbBuff, 
						     DWORD *dwSize);
	int setKeyFromRegistry(const char *pRID, const char *pPKI, 
		unsigned int *modulus);

	int decrypt_data(byte *data, unsigned int dlen,
					byte *buf,  unsigned int *mlen);
	void freeCryptoC(R_LIB_CTX *lib_ctx, 
					 R_CR_CTX *ctx,
					 R_PKEY_CTX *pkey_ctx);
	int decrypt_cryptome (byte *pCipherBuf,
		                  unsigned int uiCipherLen,
						  CryptoOperationEventImpl *opEvent);
	int encrypt_data(byte *data, unsigned int dlen,
		   			 byte *buf,  unsigned int *mlen);
	int encrypt_cryptome (byte *pPlainTextBuf,
						  unsigned int uiPlainTextLen,
						  CryptoOperationEventImpl *opEvent);
	int hash_data(byte *data, unsigned int dlen,
				  byte *buf,  unsigned int *mlen);
	int hash_cryptome (byte *pData,
					   unsigned int uiDataLen,
					   CryptoOperationEventImpl *opEvent);
	int rand_data(unsigned int dlen,
				  byte *buf,  
				  unsigned int *mlen);
	int rand_cryptome (unsigned int uiDataLen,
					  CryptoOperationEventImpl *opEvent);


	long InitCriptoCME();
	void releaseCryptoCME();

	void clean();
	int setPubKey (const byte *key, unsigned int szKey);
	void setCryptoAlg (unsigned int id);
	void setHashAlg (unsigned int id);

	int verifyRID(const char *pRID, 
				  int *indxs);
	bool checkRID(const char *pRID, byte rid[]);
	int VerifyKey(const char *ascIndx, 
		   		  const char *ascRID, 
				  const byte rid[] 
				  );
	char* CreateKeyPath (const char* ascRID, const char* ascIndx);
	int getValFromReg (const char *path, 
		  			   const char* val_name, 
					   byte **pVal, int *val_len);

};

#endif
