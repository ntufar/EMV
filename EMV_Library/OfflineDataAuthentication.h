/*
OfflineDataAuthentication.h
Implements the "Offline Data Authentication" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.3; VIS 1.4.0, ch 6.

Note: Imlements the following authentication methods
- Static Data Authentication (SDA),
- Dynamic Data Authentication (DDA)
*/
#ifndef OFFLINEDATAAUTHENTICATION_H
#define OFFLINEDATAAUTHENTICATION_H

#include "EMV_Context.h"
#include "../Utility/utility.h"
#include "../Runtime/SystemControlImpl.h"
#include "IPKCertData.h"
#include "IccPKCertData.h"
#include "SSADataRecov.h"
#include "dol_parser.h"
#include "scr_command.h"

typedef struct oda_key_info
{
	byte *KeyModulus; 
	UNINT KeyLength;
	DataObject dob_KeyExponent;
	UNINT uiCryptoAlgID;
	UNINT uiHashAlgID;
} ODA_KEY_INFO;

class OfflineDataAuthentication :
	public EMV_Context
{
public:
	OfflineDataAuthentication(void);
	virtual ~OfflineDataAuthentication(void);

	int IsCommonData();
	int IsSdaData();
	int IsDdaData();

	int determineCryptoMethod();
	int StaticDataAuth(const byte *odaList, int oda_len);
	int DynamicDataAuth(const byte *odaList, int oda_len);

	int setAuthStatus (int crypto_mode, int status);

	int InitCertAuthPubKey(CryptoControlImpl *Crypto,
						   unsigned int *modulus, 
						   byte *bCAPKI);
	int retrieveIssuerPubKey(CryptoControlImpl *Crypto, 
							 unsigned int CAPK_modulus,
							 byte bCAPKI,
							 ODA_KEY_INFO *IssuerKeyInfo);
	int retreiveIccPubKey (CryptoControlImpl *Crypto,
						   const byte *odaList, int oda_len,
						   const ODA_KEY_INFO *IssuerKeyInfo,
						   const DataObject *pdob_IccPKCert,
						   DataObject *pdob_IccPKrem,
						   ODA_KEY_INFO *ICCKeyInfo);

private:
	
	bool isDateExpired(byte MM, byte YY);
	int checkHash(const byte *recovData, IPKCertData *CAcert,
				  DataObject *pdob_exp, DataObject *pdob_rem);
	int checkIccHash(const byte *recovData, IccPKCertData *CAcert,
					 const DataObject *pdob_IccPKExp,
					 const DataObject *pdob_IccPKRem,
					 const byte *odaList, int oda_len);
	int compareHash (byte *data, int data_len, const byte *hash_res,
						 int res_len);
	int BuildIssuerPubKey(const byte *recovData, IPKCertData *Cert,
						  DataObject *pdob_IPKRem, byte **IPubKey, 
						  unsigned int *pub_key_len);
	int BuildIccPubKey(const byte *recovData, IccPKCertData *Cert,
					   DataObject *pdob_IccPKRem, 
					   byte **IccPubKey, unsigned int *icc_key_len);
	
	bool checkIssuerID(const byte *PAN, const byte *cert_pan);
	bool checkPAN(const byte *PAN, const byte *cert_pan);
	int verifyStaticData(const byte *odaList, int oda_len,
						const ODA_KEY_INFO *IssuerKeyInfo,
						CryptoControlImpl *Crypto);
	int buildStaticData(const byte *oda_list, int oda_len, 
						byte **staticData, unsigned int *static_len);

	bool isValidCertificate (const byte *rid, byte capki, 
							 const byte *serial_num);
	int GenDynamicSignature (byte **dynoSig, unsigned int *dyno_len,
							 byte **ddol_data,
							 UNINT *ddol_data_len);
	int getDDOL(DataObject *dob_DDOL);
	bool IsUnpredNum(DOL_ELEMENT *dol);
	int getInternalAuthData (byte **auth_data, UNINT *auth_data_len);
	int ParseFormat1(tlv_parser *parsed_data, 
					 byte **dynoSig, UNINT *dyno_len);
	int ParseFormat2(tlv_parser *parsed_data, 
					 byte **dynoSig, UNINT *dyno_len);
	int StoreInContext (tlv_parser *parsed_data);
	int verifyDynamicData(byte *dynoSig, 
						int dyno_len,
						ODA_KEY_INFO *ICCKeyInfo,
						const byte *ddol_data,
						const UNINT ddol_data_len,
						CryptoControlImpl *Crypto);
	
};
#endif
