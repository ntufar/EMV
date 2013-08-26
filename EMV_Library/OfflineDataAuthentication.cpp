#include "OfflineDataAuthentication.h"
#include "SDADataRecov.h"

OfflineDataAuthentication::OfflineDataAuthentication(void)
{
}

OfflineDataAuthentication::~OfflineDataAuthentication(void)
{
}

int OfflineDataAuthentication::IsCommonData()
{
	// Check Common Data

	// TSI
	if (!EnvContext.tagExist (0x9b))
		return EMV_MISSING_MANDATORY_DATA;

	// TVR
	if (!EnvContext.tagExist (0x95))
		return EMV_MISSING_MANDATORY_DATA;

	// Application Interchange Profile
	if (!EnvContext.tagExist (0x82))
		return EMV_MISSING_MANDATORY_DATA;

	// Terminal Capabilities
	if (!EnvContext.tagExist (0x9f33, false))
		return EMV_MISSING_MANDATORY_DATA;

	// Application Identifier
	if (!EnvContext.tagExist (0x9f06, false))
		return EMV_MISSING_MANDATORY_DATA;

	// Primary Application Number
	if (!EnvContext.tagExist (0x5a))
		return EMV_MISSING_MANDATORY_DATA;

	return SUCCESS;
}

int OfflineDataAuthentication::IsSdaData()
{
	// Check SDA specific Data
	
	// Issuer Public Key Certificate
	if (!EnvContext.tagExist (0x90))
		return EMV_MISSING_MANDATORY_DATA;

	// Certification Authority Public Key Index
	if (!EnvContext.tagExist (0x8f))
		return EMV_MISSING_MANDATORY_DATA;

	// Issuer Public Key Exponent
	if (!EnvContext.tagExist (0x9f32))
		return EMV_MISSING_MANDATORY_DATA;

	// Signed Authentication Data
	if (!EnvContext.tagExist (0x93))
		return EMV_MISSING_MANDATORY_DATA;
	
	return SUCCESS;
}

int OfflineDataAuthentication::IsDdaData()
{
	// DDA specific data

	// Certification Authority Public Key Index
	if (!EnvContext.tagExist (0x8f))
		return EMV_MISSING_MANDATORY_DATA;

	// Issuer Public Key Certificate
	if (!EnvContext.tagExist (0x90))
		return EMV_MISSING_MANDATORY_DATA;

	// ICC Public Key Certificate
	if (!EnvContext.tagExist (0x9f46))
		return EMV_MISSING_MANDATORY_DATA;

	// Issuer Public Key Exponent
	if (!EnvContext.tagExist (0x9f32))
		return EMV_MISSING_MANDATORY_DATA;

	// ICC Public Key Exponent
	if (!EnvContext.tagExist (0x9f47))
		return EMV_MISSING_MANDATORY_DATA;

	return SUCCESS;
}

int OfflineDataAuthentication::determineCryptoMethod()
{
	// Get AIP and terminal capabilities from the Context
	DataObject dob_AIP;
	DataObject dob_term_cap;
	if (EnvContext.getTagValue (0x82, &dob_AIP, true) != SUCCESS ||
		EnvContext.getTagValue (0x9f33, &dob_term_cap, false) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	int res = CRYPTO_NO_AUTHENTICATION;

	// Check if DDA/AC is supported in AIP
	if (check_bit(dob_AIP.Data[0], 0x01)) // First bit is checked according to Bulletin #9 (see www.emvco.com)
	{
		// Check if a terminal supports DDA/AC
		if (check_bit(dob_term_cap.Data [2], 0x08)) // 4th bit is checked according to Bulletin #9
			res = CRYPTO_DDA_AC;
	}
	if (res == CRYPTO_NO_AUTHENTICATION)
	{
		// Check if DDA is supported by AIP
		if (check_bit(dob_AIP.Data [0], 0x20)) 
		{
			// Check if a terminal supports DDA
			if (check_bit(dob_term_cap.Data [2], 0x40))
				res = CRYPTO_DDA;
		}
	}

	if (res == CRYPTO_NO_AUTHENTICATION)
	{
		// Check if SDA is supported by AIP
		if (check_bit(dob_AIP.Data [0], 0x40)) 
		{
			// Check if a terminal supports SDA
			if (check_bit(dob_term_cap.Data [2], 0x80))
				res = CRYPTO_SDA;
			else
			{
				// Check if it is Offline capable terminal
				if (IsOfflineTerminal())
				{
					// Offline capable terminal must support static authentication
					// (see EMV book 4, section 2.4).
					res = setAuthStatus(CRYPTO_NO_AUTHENTICATION, EMV_FUNCTION_IS_MISSING_FOR_TERMINAL_TYPE);
				}
			}
		}
	}
	return res;
}

int OfflineDataAuthentication::StaticDataAuth(const byte *odaList, int oda_len)
{
	UIControlImpl *pUI = (UIControlImpl*)EnvContext.GetService (CNTXT_UI);

	unsigned int CAPK_modulus;
	int res;

	// Check the data used by the ODA
	if (IsCommonData() != SUCCESS || IsSdaData() != SUCCESS)
		return setAuthStatus (CRYPTO_SDA, EMV_MISSING_MANDATORY_DATA);

	// Get reference to Crypto Service
	CryptoControlImpl *Crypto =
		(CryptoControlImpl*)EnvContext.GetService (CNTXT_CRYPTO);

	CryptoOperationEventImpl opEvent;

	// 1.Retrieve the Certification Authority Public Key stored on the terminal
	byte bCAPKI;
	if ((res = InitCertAuthPubKey (Crypto, &CAPK_modulus, &bCAPKI)) != SUCCESS)
	{
		if (res == ERR_CRYPT_RID_KEY_OPEN_FAILED ||
			res == ERR_CRYPT_PKI_KEY_OPEN_FAILED)
		{
			// Public Key index is not found
			return setAuthStatus(CRYPTO_SDA, EMV_CONDITIONS_NOT_SATISFIED);
		}
		else
			return setAuthStatus (CRYPTO_SDA, res);
	}

	// Store the value of CA Public Key index (Not really necessary, but
	// sume of the tests might require to provide this value
	setDataObject(0x9F22, &bCAPKI, 1, "b", CNFG_TRANSACTION);

	// 2. Retreive Issuer Public Key
	ODA_KEY_INFO IssuerKeyInfo;
	res = retrieveIssuerPubKey(Crypto, CAPK_modulus, bCAPKI, &IssuerKeyInfo);
	if (res != SUCCESS)
	{
		return setAuthStatus (CRYPTO_SDA, res);
	}

	// 3. Verify Signed Static Application Data
	res = verifyStaticData(odaList, oda_len, 
						   &IssuerKeyInfo,
						   Crypto);

	delete [] IssuerKeyInfo.KeyModulus;
	return setAuthStatus (CRYPTO_SDA, res);
}


int OfflineDataAuthentication::DynamicDataAuth(const byte *odaList, int oda_len)
{
	UIControlImpl *pUI = (UIControlImpl*)EnvContext.GetService (CNTXT_UI);

	unsigned int CAPK_modulus;
	int res;

	// Check the data used by the ODA
	if (IsCommonData() != SUCCESS || IsDdaData() != SUCCESS)
		return setAuthStatus (CRYPTO_DDA, EMV_MISSING_MANDATORY_DATA);

	// Get ICC Pub Key Certificate
	DataObject dob_IccPKCert;
	if (EnvContext.getTagValue (0x9f46, &dob_IccPKCert, true) != SUCCESS)
		return setAuthStatus (CRYPTO_DDA, EMV_MISSING_MANDATORY_DATA);

	// Get ICC Pub Key Exponent
	DataObject dob_IccPKexp;
	if (EnvContext.getTagValue (0x9f47, &dob_IccPKexp, true) != SUCCESS)
		return setAuthStatus (CRYPTO_DDA, EMV_MISSING_MANDATORY_DATA);

	// Get ICC Public Key Reminder
	DataObject dob_IccPKrem;
	if (EnvContext.getTagValue (0x9f48, &dob_IccPKrem, true) != SUCCESS)
		dob_IccPKrem.reset ();

	// Get reference to Crypto Service
	CryptoControlImpl *Crypto =
		(CryptoControlImpl*)EnvContext.GetService (CNTXT_CRYPTO);

	CryptoOperationEventImpl opEvent;
	byte bCAPKI;

	// 1.Retrieve the Certification Authority Public Key stored on the terminal
	if ((res = InitCertAuthPubKey (Crypto, &CAPK_modulus, &bCAPKI)) != SUCCESS)
	{
		if (res == ERR_CRYPT_RID_KEY_OPEN_FAILED ||
			res == ERR_CRYPT_PKI_KEY_OPEN_FAILED)
		{
			// Public Key index is not found
			return setAuthStatus(CRYPTO_DDA, EMV_CONDITIONS_NOT_SATISFIED);
		}
		else
			return setAuthStatus (CRYPTO_DDA, res);
	}

	// Store the value of CA Public Key index (Not really necessary, but
	// sume of the tests might require to provide this value
	setDataObject(0x9F22, &bCAPKI, 1, "b", CNFG_TRANSACTION);

	// 2. Retreive Issuer Public Key
	ODA_KEY_INFO IssuerKeyInfo;
	res = retrieveIssuerPubKey(Crypto, CAPK_modulus, bCAPKI, &IssuerKeyInfo);
	if (res != SUCCESS)
	{
		return setAuthStatus (CRYPTO_DDA, res);
	}

	// 3. Retreive ICC Public Key
	ODA_KEY_INFO ICCKeyInfo;
	ICCKeyInfo.dob_KeyExponent = dob_IccPKexp;
	res = retreiveIccPubKey(Crypto,
							odaList, oda_len,
							&IssuerKeyInfo,
							&dob_IccPKCert,
							&dob_IccPKrem,
							&ICCKeyInfo);
	if (res != SUCCESS)
	{
		delete [] IssuerKeyInfo.KeyModulus;
		return setAuthStatus (CRYPTO_DDA, res);
	}

	// 4. Generate Dynamic Signature
	byte *dynoSig = 0;
	unsigned int dyno_len;
	byte *ddol_data = 0;
	UNINT ddol_data_len = 0;
	if ((res = GenDynamicSignature (&dynoSig, &dyno_len, 
									&ddol_data, &ddol_data_len)) != SUCCESS)
	{
		delete [] IssuerKeyInfo.KeyModulus;
		delete [] ICCKeyInfo.KeyModulus;
		return setAuthStatus (CRYPTO_DDA, res);
	}

	// 5. Verify Dynamic Signature
	res = verifyDynamicData(dynoSig, dyno_len, 
						   &ICCKeyInfo,
						   ddol_data,
						   ddol_data_len,
						   Crypto);

	if (dyno_len > 0)
		delete [] dynoSig;
	if (ddol_data_len > 0)
		delete [] ddol_data;
	delete [] IssuerKeyInfo.KeyModulus;
	delete [] ICCKeyInfo.KeyModulus;
	return setAuthStatus (CRYPTO_DDA, res);
}


int OfflineDataAuthentication::InitCertAuthPubKey(CryptoControlImpl *Crypto,
												  unsigned int *modulus, 
												  byte *bCAPKI)
{
	int res;
	DataObject dob_AID;
	DataObject dob_CAPKI;

	// Get AID 
	if ((res = EnvContext.getTagValue (0x9f06, &dob_AID, false)) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;
	// Get CAPKI
	if ((res = EnvContext.getTagValue (0x8f, &dob_CAPKI, false)) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;
	
	if (dob_AID.len < 5 || dob_CAPKI.len != 1)
	{
		// This should never happen - AID must be at least 5 bytes
		return EMV_INVALID_FORMAT;
	}

	res = Crypto->initKeyCA (dob_AID.Data, 5, 
							 dob_CAPKI.Data, dob_CAPKI.len, 
							 modulus);
	if (res == SUCCESS)
		*bCAPKI = dob_CAPKI.Data [0];
	return res;
}

int OfflineDataAuthentication::setAuthStatus (int crypto_mode, int status)
{	
	bool exception = false;
	byte crypto_bit = 0x00;

	// Get TVR and TSI from the context
	DataObject dob_TVR;
	DataObject dob_TSI;
	if (EnvContext.getTagValue (0x95, &dob_TVR, true) != SUCCESS ||
		EnvContext.getTagValue (0x9b, &dob_TSI, true) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	if (!dob_TSI.Data || !dob_TVR.Data)
	{
		return EMV_DATA_NOT_FOUND;
	}

	bool statusFlg = true;
	switch (crypto_mode)
	{
	case CRYPTO_SDA:
		crypto_bit = 0x40;
		break;
	case CRYPTO_DDA:
		crypto_bit = 0x08;
		break;
	case CRYPTO_DDA_AC:
		crypto_bit = 0x04;
	case CRYPTO_NO_AUTHENTICATION:
		if (status == EMV_FUNCTION_IS_MISSING_FOR_TERMINAL_TYPE)
			exception = true;
	default:
		// Set the 'Offline data authentication was not performed' to '1' in TVR
		set_bit(dob_TVR.Data [0], 0x80);
		// Reset the 'Offline data authentication was performed' to '0' in TSI
		reset_bit(dob_TSI.Data [0], 0x80);
		statusFlg = false;
	}

	if (statusFlg)
	{
		if (status == SUCCESS)
		{
			reset_bit(dob_TVR.Data [0], crypto_bit); // reset ODA failed bit
			set_bit(dob_TSI.Data [0], 0x80);   // ODA was performed
		}
		else if (status == EMV_CONDITIONS_NOT_SATISFIED)
		{
			set_bit(dob_TVR.Data [0], crypto_bit); // ODA failed
			set_bit(dob_TSI.Data [0], 0x80); // ODA was performed
		}
		else if (status == EMV_DATA_NOT_FOUND || status == NO_TAG_FOUND ||
					status == EMV_MISSING_MANDATORY_DATA)
		{
			set_bit(dob_TVR.Data [0], crypto_bit | 0x20); // ODA failed and ICC data missing
			set_bit(dob_TSI.Data [0], 0x80); // ODA was performed
		}
		else
		{
			set_bit(dob_TVR.Data [0], crypto_bit); // ODA failed
			set_bit(dob_TSI.Data [0], 0x80); // ODA was performed
			exception = true;
		}
	}

	// Update context
	EnvContext.setTagValue(0x9b, &dob_TSI, IO_UPDATE);
	EnvContext.setTagValue(0x95, &dob_TVR, IO_UPDATE);
	
	if (exception)
		return status;
	else
		return SUCCESS;
}

// Check the date according to the rule specified in EMV book 4, section 2.7.3
// Note that the current date stored in the hash (tag 0x9a) and the expiration
// date read from the card are presented as 2-byte array, where first element
// is year YY, and the second element is month MM.
// Those are numeric format, meaning each digit in YY, or MM presents a decimal
// number. Thus the year 99 will be represented by 0x99, which is decimal 153
// Years from 0 - 49 are considered to be 20XX
// Years from 50 - 99 are considered to be 19XX
bool OfflineDataAuthentication::isDateExpired(byte MM, byte YY)
{
	// Get current date from the hash
	DataObject dob_curDate;
	int res = EnvContext.getTagValue (0x9A, &dob_curDate, true);
	if (res != SUCCESS)
	{
		// Current date is not found in hash, add the current date to the hash,
		// and try again
		AddCurTime2Hash();
		// Read date from the hash again
		res = EnvContext.getTagValue (0x9A, &dob_curDate, true);
		if (res != SUCCESS)
			return true; // Cannot retreive current date; consider it Expired
	}
	
	// if current and expiration dates are both either 19XX or 20XX, then
	if ((dob_curDate.Data [0] >= 0 && dob_curDate.Data [0] <= 0x49 &&
		YY >= 0 && YY <= 0x49) ||
		(dob_curDate.Data [0] >= 0x50 && dob_curDate.Data [0] <= 0x99 &&
		YY >= 50 && YY <= 0x99))
	{
		if (dob_curDate.Data [0] < YY)
			return false; // Not Expired
		else if (dob_curDate.Data [0] > YY)
			return true;  // Expired
		else  // dob_curDate.Data [0] == YY
		{  
			if (dob_curDate.Data [1] <= MM)
				return false; // Not Expired
			else
				return true;  // Expired
		}
	} 
	else if (dob_curDate.Data [0] >= 0x50 && dob_curDate.Data [0] <= 0x99 &&
		YY >= 0 && YY <= 0x49)
	{
		// If current date is in 19XX and expiration date is in 20XX
		return false; // Not Expired
	}
	else if (dob_curDate.Data [0] >= 0 && dob_curDate.Data [0] <= 0x49 &&
		YY >= 0x50 && YY <= 0x99)
	{
		// If current date is in 20XX and expiration date is in 19XX
		return true; // Expired
	}
	else
	{
		// Invalid year format -- can be only in a range from 0x00 to 0x99
		return true; // Expired
	}
}

int OfflineDataAuthentication::checkHash(const byte *recovData, 
										 IPKCertData *CAcert,
										 DataObject *pdob_exp,
										 DataObject *pdob_rem)
{
	int res;
	int rem_len;
	int exp_len;

	exp_len = pdob_exp->len;
	rem_len = pdob_rem->len;
	
	// Find the length and allocate a buffer to keep the concatinated data
	int data_len = CAcert->hash - CAcert->cert_format;
	int buff_len = exp_len + rem_len + data_len;
	byte *buff = new byte [buff_len];
	if (!buff)
		return ERR_MEMORY_ALLOC;
	
	memcpy (buff, recovData + CAcert->cert_format, data_len);
	if (rem_len > 0)
	{
        memcpy (buff + data_len, pdob_rem->Data, rem_len);
		data_len += rem_len;
	}
	memcpy (buff + data_len, pdob_exp->Data, pdob_exp->len);

	res = compareHash (buff, buff_len, recovData + CAcert->hash, 20);

	// Release memory
	delete [] buff;

	return res;
}

int OfflineDataAuthentication::checkIccHash(const byte *recovData, 
										 IccPKCertData *CAcert,
										 const DataObject *pdob_IccPKExp,
										 const DataObject *pdob_IccPKRem,
										 const byte *odaList, int oda_len)
{
	int res;
	int rem_len;
	int exp_len;

	exp_len = pdob_IccPKExp->len;
	rem_len = pdob_IccPKRem->len;

	// Build Static Data
	byte *staticData;
	unsigned int static_len;
	if ((res = buildStaticData(odaList, oda_len, 
							   &staticData, &static_len)) != SUCCESS)
	{
		return res;
	}

	// Find the length and allocate a buffer to keep the concatinated data
	int data_len = CAcert->hash - CAcert->cert_format;
	int buff_len = exp_len + rem_len + data_len + static_len;
	byte *buff = new byte [buff_len];
	if (!buff)
	{
		if (static_len > 0)
			delete []staticData;
		return ERR_MEMORY_ALLOC;
	}
	
	memcpy (buff, recovData + CAcert->cert_format, data_len);
	if (rem_len > 0)
	{
        memcpy (buff + data_len, pdob_IccPKRem->Data, pdob_IccPKRem->len);
		data_len += pdob_IccPKRem->len;
	}
	memcpy (buff + data_len, pdob_IccPKExp->Data, pdob_IccPKExp->len);

	data_len += pdob_IccPKExp->len;
	if (static_len > 0)
		memcpy (buff + data_len, staticData, static_len);

	res = compareHash (buff, buff_len, recovData + CAcert->hash, 20);

	// Release memory
	if (static_len > 0)
		delete [] staticData;
	delete [] buff;

	return res;
}

int OfflineDataAuthentication::compareHash (byte *data, int data_len, 
											const byte *hash_res,
											int res_len)
{
	int res;
	// Get reference to Crypto Service
	CryptoControlImpl *Crypto =
		(CryptoControlImpl*)EnvContext.GetService (CNTXT_CRYPTO);

	CryptoOperationEventImpl opEvent;

	Crypto->addOperationEvent(&opEvent);

	if ((res = Crypto->calcHash (data, data_len)) != SUCCESS)
	{
		// Error while calculating the hash; terminate the transaction
		Crypto->removeEvent();
		return ERR_MEMORY_ALLOC;
	}
	Crypto->removeEvent();

	byte *new_hash;
	int new_len;
	opEvent.getByteString (&new_hash);
	new_len = opEvent.getLength ();

	if (new_len != res_len)
		return EMV_CONDITIONS_NOT_SATISFIED;

	if (memcmp(new_hash, hash_res, new_len) != 0)
		return EMV_CONDITIONS_NOT_SATISFIED;
	
	return SUCCESS;
}

int OfflineDataAuthentication::BuildIssuerPubKey(const byte *recovData, 
												 IPKCertData *CAcert,
												 DataObject *pdob_IPKRem,
												 byte **IPubKey, 
												 unsigned int *pub_key_len)
{
	int rem_len = pdob_IPKRem->len;
	
	int pub_key_len_recov = recovData[CAcert->pub_key_len];
	int pub_key_calc = CAcert->hash - CAcert->pub_key ;
	for (int i = pub_key_calc - 1; i >= 0; i--)
	{
		if (recovData[CAcert->pub_key + i] != 0xbb)
			break;
		else
			pub_key_calc--;
	}
	if ((pub_key_calc + rem_len) != pub_key_len_recov)
	{
		// Card has invalid data; abort transaction
		return EMV_INVALID_FORMAT;
	}
	if (pub_key_calc < pub_key_len_recov && rem_len == 0)
	{
		// Issuer Public key reminder is missing.
		return EMV_MISSING_MANDATORY_DATA;
	}

	*IPubKey = new byte [pub_key_len_recov];
	if (!(*IPubKey))
		return ERR_MEMORY_ALLOC;


	memcpy (*IPubKey, recovData + CAcert->pub_key, pub_key_calc);
	if (rem_len > 0)
		memcpy (*IPubKey + pub_key_calc, pdob_IPKRem->Data, rem_len);
	*pub_key_len = pub_key_len_recov;

	return SUCCESS;
}

int OfflineDataAuthentication::BuildIccPubKey(const byte *recovData, 
											  IccPKCertData *CAcert,
											  DataObject *pdob_IccPKRem,
											  byte **IccPubKey, 
											  unsigned int *icc_key_len
											  )
{
	int rem_len = pdob_IccPKRem->len;
	
	int pub_key_len_recov = recovData[CAcert->pub_key_len];
	int pub_key_calc = CAcert->hash - CAcert->pub_key ;
	for (int i = pub_key_calc - 1; i >= 0; i--)
	{
		if (recovData[CAcert->pub_key + i] != 0xbb)
			break;
		else
			pub_key_calc--;
	}
	if ((pub_key_calc + rem_len) != pub_key_len_recov)
	{
		// Card has invalid data; abort transaction
		return EMV_INVALID_FORMAT;
	}
	if (pub_key_calc < pub_key_len_recov && rem_len == 0)
	{
		// The ICC Public key reminder is missing.
		return EMV_MISSING_MANDATORY_DATA;
	}

	*IccPubKey = new byte [pub_key_len_recov];
	if (!(*IccPubKey))
		return ERR_MEMORY_ALLOC;


	memcpy (*IccPubKey, recovData + CAcert->pub_key, pub_key_calc);
	if (rem_len > 0)
		memcpy (*IccPubKey + pub_key_calc, pdob_IccPKRem->Data, rem_len);
	*icc_key_len = pub_key_len_recov;

	return SUCCESS;
}

int OfflineDataAuthentication::retrieveIssuerPubKey(
								 CryptoControlImpl *Crypto, 
								 unsigned int CAPK_modulus,
								 byte bCAPKI,
								 ODA_KEY_INFO *IssuerKeyInfo
								 )
{
	int res;

	// Initialize data
	// --------------------------------
	// Get Issuer Public Key Certificate
	DataObject dob_IssPKCert;
	if (EnvContext.getTagValue (0x90, &dob_IssPKCert, true))
		return EMV_MISSING_MANDATORY_DATA;
	printf("0x90: Issuer Public Key Certificate\n");
	printHex(dob_IssPKCert.Data,dob_IssPKCert.len);
	// Get PAN
	DataObject dob_PAN;
	if (EnvContext.getTagValue (0x5a, &dob_PAN, true))
		return EMV_MISSING_MANDATORY_DATA;
	printf("0x5a: PAN\n");
	printHex(dob_PAN.Data,dob_PAN.len);

	// Get AID
	DataObject dob_AID;
	if (EnvContext.getTagValue (0x9f06, &dob_AID, false))
		return EMV_MISSING_MANDATORY_DATA;
	printf("0x9f06: AID\n");
	printHex(dob_AID.Data,dob_AID.len);

	// Get Issuer Pub Key Exponent
	if (EnvContext.getTagValue (0x9f32, &(IssuerKeyInfo->dob_KeyExponent), true))
		return EMV_MISSING_MANDATORY_DATA;
	printf("0x9f32: Issuer Pub Key Exponent\n");
	printHex(IssuerKeyInfo->dob_KeyExponent.Data,IssuerKeyInfo->dob_KeyExponent.len);

	// Get Issuer Pub Key Reminder
	DataObject dob_IssPKrem;
	if (EnvContext.getTagValue (0x92, &dob_IssPKrem, true) != SUCCESS)
		dob_IssPKrem.reset ();
	printf("0x92: Issuer Pub Key Reminder\n");
	printHex(dob_IssPKrem.Data,dob_IssPKrem.len);

	// -----------------------------

	// 2.1 Check the length of the Issuer Public Key certificate
	if (CAPK_modulus != dob_IssPKCert.len)
	{
		// Condition 1, ch 5.3, book 3, EMV spec
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	CryptoOperationEventImpl opEvent;
	Crypto->addOperationEvent(&opEvent);

	// 2.2 Recover data from the certificate
	if ((res = Crypto->decrypt(dob_IssPKCert.Data, dob_IssPKCert.len)) 
		!= SUCCESS)
	{
		Crypto->removeEvent();
		return opEvent.getError ();
	}

	Crypto->removeEvent();

	byte *recovData;
	int recovLen;
	opEvent.getByteString (&recovData);
	recovLen = opEvent.getLength ();
	IPKCertData CAcert (recovLen);

	// Check header, trailer, and format of the recovered data
	if (recovData[CAcert.header] != 0x6a ||           //header
		recovData[CAcert.trailer] != 0xbc ||  //trailer
		recovData[CAcert.cert_format] != 0x02)             //Certificate format
	{
		// Conditions 2, 3, or 4 (of ch 5.3, EMV book 3) are not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// Check PAN number
	if (!checkIssuerID(dob_PAN.Data, recovData + CAcert.issuer_id))
	{
		// Conditions 8 (of ch 5.3, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}
	
	// Check the expiration date
	if (isDateExpired(recovData[CAcert.exp_date], recovData[CAcert.exp_date +1]))
	{
		// Conditions 9 (of ch 5.3, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// Check if concatination of RID, Cert.Auth.Pub Key Index, 
	// and Certificate Serial Number is valid (EMV book 2, ch 5.3, condition 10)
	if (!isValidCertificate (dob_AID.Data, bCAPKI, 
							 recovData + CAcert.cert_serial_num))
		return EMV_CONDITIONS_NOT_SATISFIED;

	// Check crypto and hash algorithm ids
	if (recovData[CAcert.pub_key_alg] != Crypto->getCryptoAlgID() ||
		recovData[CAcert.hash_alg] != Crypto->getHashAlgID())
	{
		// Condition 11 (of ch 5.3, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}
	IssuerKeyInfo->uiCryptoAlgID = recovData[CAcert.pub_key_alg];
	IssuerKeyInfo->uiHashAlgID  = recovData[CAcert.hash_alg] ;

	// Check if reminder is present
	if ((recovData[CAcert.pub_key_len] > (CAcert.hash - CAcert.pub_key)) &&
		dob_IssPKrem.len == 0)
	{
		// Issuer Public key reminder is missing.
		return EMV_MISSING_MANDATORY_DATA;
	}
	// Calculate and verify hash 
	if ((res = checkHash(recovData, &CAcert, &(IssuerKeyInfo->dob_KeyExponent),
					   &dob_IssPKrem)) != SUCCESS)
	{
		// Condition 5-7 (of ch 5.3, EMV book 3) is not satisfied
		return res;
	}

	// ALL the checks for the Data Recovered from the issuer Public Key Certificate
	// are SUCCESSFULL (except the rule 10, which is optional for EMV and not 
	// implemented here).

	//Extract Issuer Public Key
	return BuildIssuerPubKey(recovData, &CAcert, &dob_IssPKrem, 
							 &(IssuerKeyInfo->KeyModulus), 
							 &(IssuerKeyInfo->KeyLength));
}

int OfflineDataAuthentication::retreiveIccPubKey(
								    CryptoControlImpl *Crypto,
									const byte *odaList, int oda_len,
									const ODA_KEY_INFO *IssuerKeyInfo,
									const DataObject *pdob_IccPKCert,
									DataObject *pdob_IccPKrem,
									ODA_KEY_INFO *ICCKeyInfo)
{
	int res;
	// initialize data:

	// Get PAN
	DataObject dob_PAN;
	if (EnvContext.getTagValue (0x5a, &dob_PAN, true))
		return EMV_MISSING_MANDATORY_DATA;


	// 1. Check the length of the ICC Public Key certificate
	if (IssuerKeyInfo->KeyLength != pdob_IccPKCert->len)
	{
		// Condition 1, ch 6.4, book 3, EMV spec
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// 2. Recover Data from ICC certificate
	// 2.1 Initialize key to the Issuer key
	res = Crypto->initKey (IssuerKeyInfo->KeyModulus, IssuerKeyInfo->KeyLength, 
						   IssuerKeyInfo->dob_KeyExponent.Data,
						   IssuerKeyInfo->dob_KeyExponent.len,
						   IssuerKeyInfo->uiCryptoAlgID, 
						   IssuerKeyInfo->uiHashAlgID );

	if (res != SUCCESS)
	{
		// Failed to initialize ICC pub key;
		// terminate the transaction
		return res;
	}

	CryptoOperationEventImpl opEvent;
	Crypto->addOperationEvent(&opEvent);

	// 2.2 Recover data from the certificate
	if ((res = Crypto->decrypt(pdob_IccPKCert->Data, 
							   pdob_IccPKCert->len)) != SUCCESS)
	{
		Crypto->removeEvent();
		return opEvent.getError ();
	}

	Crypto->removeEvent();

	byte *recovData;
	int recovLen;
	opEvent.getByteString (&recovData);
	recovLen = opEvent.getLength ();
	IccPKCertData CAcert (recovLen);

	// Check header, trailer, and format of the recovered data
	if (recovData[CAcert.header] != 0x6a ||           //header
		recovData[CAcert.trailer] != 0xbc ||        //trailer
		recovData[CAcert.cert_format] != 0x04)      //Certificate format
	{
		// Conditions 2, 3, or 4 (of ch 6.4, EMV book 3) are not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// Check PAN number
	if (!checkPAN(dob_PAN.Data, recovData + CAcert.pan))
	{
		// Conditions 8 (of ch 6.4, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}
	
	// Check the expiration date
	if (isDateExpired(recovData[CAcert.exp_date], recovData[CAcert.exp_date +1]))
	{
		// Conditions 9 (of ch 6.4, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}


	// Check crypto and hash algorithm ids
	if (recovData[CAcert.pub_key_alg] != Crypto->getCryptoAlgID() ||
		recovData[CAcert.hash_alg] != Crypto->getHashAlgID())
	{
		// Condition 10 (of ch 6.4, EMV book 3) is not satisfied
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	ICCKeyInfo->uiCryptoAlgID = recovData[CAcert.pub_key_alg];
	ICCKeyInfo->uiHashAlgID = recovData[CAcert.hash_alg] ;

	// Check if reminder is present
	if (recovData[CAcert.pub_key_len] > CAcert.hash - CAcert.pub_key &&
		pdob_IccPKrem->len == 0)
	{
		// the ICC Public key reminder is missing.
		return EMV_MISSING_MANDATORY_DATA;
	}
	// Calculate and verify hash 
	if ((res = checkIccHash(recovData, &CAcert, 
							&(ICCKeyInfo->dob_KeyExponent),
							pdob_IccPKrem,
						    odaList, oda_len)) != SUCCESS)
	{
		// Conditions 5-7 (of ch 6.4, EMV book 3) are not satisfied
		return res;
	}

	// ALL the checks for the Data Recovered from the issuer Public Key Certificate
	// are SUCCESSFUL.

	//Extract Issuer Public Key
	return BuildIccPubKey(recovData, &CAcert, pdob_IccPKrem, 
						  &(ICCKeyInfo->KeyModulus), 
						  &(ICCKeyInfo->KeyLength));
}


bool OfflineDataAuthentication::checkIssuerID(const byte *PAN, 
											  const byte *cert_pan)
{
	// Adjust the length of the buffer to compare
	int id_size = 4;
	for (int i = id_size - 1; i >= 0; i--)
	{
		if (cert_pan[i] != 0xff)
			break;
        id_size--;
	}

	if (memcmp(PAN, cert_pan, id_size) == 0)
	{
		// Condition 8 (of ch 5.3, EMV book 3) is satisfied!
		return true;
	}
	else
	{
		// Conditions 8 (of ch 5.3, EMV book 3) is not satisfied
		return false;
	}
}

bool OfflineDataAuthentication::checkPAN(const byte *PAN,
										 const byte *cert_pan)
{
	// Adjust the length of the PAN retreived from the certificate
	int pan_size_retr = 10;
	for (int i = pan_size_retr - 1; i >= 0; i--)
	{
		if (cert_pan[i] != 0xff)
			break;
        pan_size_retr--;
	}

	// Adjust the length of the PAN retreived from the ICC
	int pan_size_icc = 10;
	for (int i = pan_size_icc - 1; i >= 0; i--)
	{
		if (cert_pan[i] != 0xff)
			break;
        pan_size_icc--;
	}

	if (pan_size_icc == pan_size_retr)
	{
		if (memcmp(PAN, cert_pan, pan_size_icc) == 0)
		{
			// Condition 8 (of ch 6.4, EMV book 3) is satisfied!
			return true;
		}
	}
	// Conditions 8 (of ch 6.4, EMV book 3) is not satisfied
	return false;
}

// Signed Static Application Data Verification
// According to EMV book 2, chapter 5.4
int OfflineDataAuthentication::verifyStaticData(const byte *odaList, 
												int oda_len,
												const ODA_KEY_INFO *IssuerKeyInfo,
												CryptoControlImpl *Crypto)
{
	int res;
	byte *staticData;
	unsigned int static_len;

	// Get Signed Static Application Data
	DataObject dob_SAD;
	if (EnvContext.getTagValue (0x93, &dob_SAD, true) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;


	// 1. Verify that the length of the Signed Static Application Data is equal to
	//	the length of the public key modulus
	// (Condition 1, ch 5.4, EMV book 2)
	if (IssuerKeyInfo->KeyLength != dob_SAD.len)
	{
		// Condition failed
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// 2. Recover Data from Issuer certificate
	// Initialize key to the Issuer key
	res = Crypto->initKey (IssuerKeyInfo->KeyModulus, IssuerKeyInfo->KeyLength, 
						   IssuerKeyInfo->dob_KeyExponent.Data, 
						   IssuerKeyInfo->dob_KeyExponent.len,
						   IssuerKeyInfo->uiCryptoAlgID, 
						   IssuerKeyInfo->uiHashAlgID);

	if (res != SUCCESS)
	{
		// Failed to initialize issuer pub key;
		// terminate the transaction
		return res;
	}
	// Apply RSA Recover algorithm to retreive data
	CryptoOperationEventImpl opEvent;
	Crypto->addOperationEvent(&opEvent);

	res = Crypto->decrypt(dob_SAD.Data, dob_SAD.len);
	Crypto->removeEvent();
	if (res != SUCCESS)
	{
		// Decryption error, terminate the transaction
		return res;
	}
	// Decryption succeeded; retreive the recovered data
	byte *recovData;
	int recovLen;

	opEvent.getByteString (&recovData);
	recovLen = opEvent.getLength ();

	// Check the recovered data
	SSADataRecov appData (recovLen);

	// Condition 2, 3, 4, 6 (ch 5.4, EMV book 2)
	if (recovData[appData.header] != 0x6a ||
		recovData[appData.trailer] != 0xbc ||
		recovData[appData.data_format] != 0x03 ||
		recovData[appData.hash_alg_id] != Crypto->getCryptoAlgID())
	{
		// Condition failed
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	if ((res = buildStaticData(odaList, oda_len, 
							   &staticData, &static_len)) != SUCCESS)
	{
		return res;
	}

	// Prepare condition 5; concatinate data to prepare it for a hash function
	int data_len = appData.hash_result - appData.data_format;
	byte *staticInData = new byte [data_len + static_len];
	if (!staticInData)
	{
		if (static_len > 0)
			delete [] staticData;
		return ERR_MEMORY_ALLOC;
	}

	memcpy(staticInData, recovData + appData.data_format, data_len);
	if (static_len > 0)
		memcpy (staticInData + data_len, staticData, static_len);

	// Verify rule 7 (ch 5.1, EMV book 2)
	if ((res = compareHash (staticInData, data_len + static_len, 
							recovData + appData.hash_result, 20)) != SUCCESS)
	{
		// Calculated hash is not the same as recovered;
		// Rule 7 is not satisfied
		if (static_len > 0)
			delete [] staticData;
		delete [] staticInData;
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// All checks are successfull !
	// Store Data Authentication code in the Context
	DataObject dob_DAC;
	dob_DAC.set (recovData + appData.data_auth_code, 2, CNFG_APPLICATION,
		"b");
	EnvContext.setTagValue (0x9f45, &dob_DAC, IO_CREATE | IO_UPDATE);

	if (static_len > 0)
		delete [] staticInData;
	delete [] staticData;
	return res;
}


// Dynamic Signature Verification
// According to EMV book 2, chapter 6.5.2
int OfflineDataAuthentication::verifyDynamicData(byte *dynoSig, 
												int dyno_len,
												ODA_KEY_INFO *ICCKeyInfo,
												const byte *ddol_data,
												const UNINT ddol_data_len,
												CryptoControlImpl *Crypto)
{
	int res;

	// 1. Verify that the length of the Signed Dynamic Data is equal to
	//	the ICC public key modulus
	// (Condition 1, ch 6.5.2, EMV book 2)
	if (ICCKeyInfo->KeyLength != dyno_len)
	{
		// Condition failed
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// 2. Recover Data 
	// Initialize key to the ICC public key
	res = Crypto->initKey (ICCKeyInfo->KeyModulus, ICCKeyInfo->KeyLength, 
						   ICCKeyInfo->dob_KeyExponent.Data, 
						   ICCKeyInfo->dob_KeyExponent.len,
						   ICCKeyInfo->uiCryptoAlgID, 
						   ICCKeyInfo->uiHashAlgID);

	if (res != SUCCESS)
	{
		// Failed to initialize the ICC pub key;
		// terminate the transaction
		return res;
	}
	// Apply RSA Recover algorithm to retreive data
	CryptoOperationEventImpl opEvent;
	Crypto->addOperationEvent(&opEvent);

	res = Crypto->decrypt(dynoSig, dyno_len);
	Crypto->removeEvent();
	if (res != SUCCESS)
	{
		// Decryption error, terminate the transaction
		return res;
	}
	// Decryption succeeded; retreive the recovered data
	byte *recovData;
	int recovLen;

	opEvent.getByteString (&recovData);
	recovLen = opEvent.getLength ();

	// 3 - 4. Check the recovered data
	SDADataRecov appData (recovLen);

	// Condition 2, 3, 4 (ch 6.5.2, EMV book 2)
	if (recovData[appData.header] != 0x6a ||
		recovData[appData.trailer] != 0xbc ||
		recovData[appData.data_format] != 0x05 ||
		recovData[appData.hash_alg_id] != Crypto->getCryptoAlgID())
	{
		// Condition failed
		return EMV_CONDITIONS_NOT_SATISFIED;
	}


	// 5. Concatinate data to prepare it for a hash function
	int data_len = appData.hash_result - appData.data_format;
	byte *dynamicInData = new byte [data_len + ddol_data_len];
	if (!dynamicInData)
	{
		return ERR_MEMORY_ALLOC;
	}

	memcpy(dynamicInData, recovData + appData.data_format, data_len);
	if (ddol_data_len > 0)
		memcpy (dynamicInData + data_len, ddol_data, ddol_data_len);

	// 6 - 7. Calculate and compare the hash
	if ((res = compareHash (dynamicInData, data_len + ddol_data_len, 
							recovData + appData.hash_result, 20)) != SUCCESS)
	{
		// Calculated hash is not the same as recovered;
		// Rule 7 is not satisfied
		delete [] dynamicInData;
		return EMV_CONDITIONS_NOT_SATISFIED;
	}

	// All checks are successfull !
	// 8. Extract and store the ICC Dynamic Number in the Context
	DataObject dob_DynNum;
	dob_DynNum.set (recovData + appData.dynamic_data + 1, //first byte is for length 
				 recovData[appData.dynamic_data_len] - 1, CNFG_APPLICATION,
				 "b");
	EnvContext.setTagValue (0x9f4C, &dob_DynNum, IO_CREATE | IO_UPDATE);

	delete [] dynamicInData;
	return res;
}


int OfflineDataAuthentication::buildStaticData(const byte *oda_list, int oda_len, 
							byte **staticData, unsigned int *static_len)
{
	int res;
	if (oda_len < 0)
		oda_len = 0;
	int data_len = oda_len;

	//Get Static Data Authentication Tag List
	DataObject dob_SDATagList;
	if (EnvContext.getTagValue (0x9F4A, &dob_SDATagList, true) != SUCCESS)
		dob_SDATagList.reset();

	DataObject dob_AIP;

	if (dob_SDATagList.len == 0)
	{
		// Do not add AIP to the static list
	}
	else
	{
		// Extract AIP tag from Static Data Tag list
		int tag_val;
		int tag_len;
		if ((res = tlv::parseTag (dob_SDATagList.Data, &tag_val, &tag_len)) 
			!= SUCCESS)
		{
			// Error parsing the data; terminate the transaction
			return res;
		}
		if (tag_len != dob_SDATagList.len || tag_val != 0x82)
		{
			// Condition specifying that if Static Data Authentication Tag List
			// is present, then it shall only contain the tag '82' identifying
			// teh AIP (book 2, ch 5.1, pg 19, or book 3, ch 6.3, page 47);
			return EMV_CONDITIONS_NOT_SATISFIED;
		}
		// Get AIP from the context
		if (EnvContext.getTagValue (0x82, &dob_AIP, true) != SUCCESS)
			return EMV_MISSING_MANDATORY_DATA;

		data_len += dob_AIP.len;
	}
	// Allocate space to hold static data buffer
	if (data_len > 0)
	{
		*staticData = new byte [data_len];
		if (!(*staticData))
			return ERR_MEMORY_ALLOC;

		memcpy (*staticData, oda_list, oda_len);
		if (data_len > oda_len)
			memcpy (*staticData + oda_len, dob_AIP.Data, dob_AIP.len);
	}

	*static_len = data_len;
	return SUCCESS;
}

// Returns True if the current certificate is not found in the 
// Certificate list that might be kept by the terminal.
// If the certificate is found in the list, then return false
bool OfflineDataAuthentication::isValidCertificate (const byte *rid, 
													byte capki, 
													const byte *serial_num)
{
	CnfgControlImpl *Cnfg = 
		(CnfgControlImpl*)EMV_Context::GetService (CNTXT_CNFG);
	int res;

	
	CnfgOperationEventImpl opEvent;
	
	if ((res = Cnfg->addOperationEvent (&opEvent)) != SUCCESS)
		return false;

	res = Cnfg->getValue (CNFG_TERMINAL, "EnableCertificateValidation",
						 "Crypto\\RevokedCertificates");
	Cnfg->removeEvent ();
	if (res != SUCCESS)
	{
		// Cannot find the registry key, concider the validation not successfull
		return false;
	}

	if (opEvent.getValueType() != OPEVENT_LONG)
	{
		// Invalid type of the expected value, concider the validation not successfull
		return false;
	}
	
	long enabled;
	opEvent.getLong (&enabled);

	// Check if validation is required
	if (enabled == 0)
		return true;

	// Retreive the validation list and see if the current certificate is valid
	opEvent.resetEvent (true);
	Cnfg->addOperationEvent (&opEvent);

	res = Cnfg->getValue (CNFG_TERMINAL, "RevokedCertificates",
						 "Crypto\\RevokedCertificates");
	Cnfg->removeEvent ();

	if (res != SUCCESS)
		return false;

	if (opEvent.getValueType () != OPEVENT_BINARY)
		return false;

	// Retreive certificat list
	byte *certList = 0;
	int cert_len;
	res = opEvent.getByteString (&certList);
	cert_len = opEvent.getLength ();
	if (res != SUCCESS || cert_len <= 0)
		return true;

	// Concatinate input data
	byte cur_cert[9];
	memcpy(cur_cert, rid, 5);
	cur_cert[5] = capki;
	memcpy (cur_cert + 6, serial_num, 3);

	// ***************
	// The following code is needed only for debug purpoces
	/*opEvent.resetEvent (true);
	Cnfg->addOperationEvent (&opEvent);
	res = Cnfg->setValueByteString(CNFG_TERMINAL, 
							 "Certificate", 
							 cur_cert, 9, 
							 true, "Crypto\\RevokedCertificates");
	opEvent.resetEvent (true);
	Cnfg->removeEvent ();
	*/
	// ***************

	int cur_indx = 0;
	while (cur_indx < cert_len)
	{
		if (memcmp(cur_cert, certList + cur_indx, 9) == 0)
		{
			// Certificate is found -- return false
			return false;
		}
		// Go to the next certificate
		cur_indx += 9;
	}
	// certificate is not found -- return true
	return true;
}

int OfflineDataAuthentication::GenDynamicSignature (byte **dynoSig, 
													unsigned int *dyno_len,
													byte **ddol_data,
													UNINT *ddol_data_len)
{
	int res;
	*ddol_data = 0;
	*ddol_data_len = 0;

	byte *auth_data = 0;
	UNINT auth_data_len = 0;

	// 1. Extract data to be used in Internal Authenticate command
	if ((res = getInternalAuthData(&auth_data, &auth_data_len)) != SUCCESS)
		return res;

	// 2. Run Command
	// Get a pointer to the card reader service
	SCRControlImpl *pSCR = (SCRControlImpl*) EnvContext.GetService(CNTXT_SCR);
	if (!pSCR)
	{
		if (auth_data_len > 0)
			delete [] auth_data;
		return ERR_SERVICE_NOT_CONNECTED;
	}

	// Set APDU command to send to the card
	scr_command command (pSCR);
	res = command.setInternalAuthenticate(auth_data, auth_data_len);
	if (res != SUCCESS)
	{
		if (auth_data_len > 0)
			delete [] auth_data;
		return res;
	}

	// Send the GetData command to the card
	R_APDU rapdu;
	if ((res = command.run (&rapdu, EMV_Context::TransactionToken)) != SUCCESS)
	{
		if (auth_data_len > 0)
			delete [] auth_data;
		return res;
	}

	if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
	{
		// The Data is successfully retreived
		// Parse the data
		tlv_parser parsed_data;
		byte *data = rapdu.copyData();
		if ((res = parsed_data.parse (data, rapdu.getDataLen())) == SUCCESS)
		{
			if (parsed_data.GetRoot ()->GetTagVal() == 0x80)
			{
				// Format 1 of data is returned.
				// See EMV book 3, ch 2.5.9.4
				res = ParseFormat1(&parsed_data, dynoSig, dyno_len);
			}
			else if (parsed_data.GetRoot ()->GetTagVal() == 0x77)
			{
				// Format 2 of data is returned.
				// See EMV book 3, ch 2.5.9.4
				res = ParseFormat2(&parsed_data, dynoSig, dyno_len);
			}
			else
			{
				// Unexpected value is returned
				res = ERR_CMD_INVALID_ICC_RESPONSE;
			}
		}
		else
		{
			// Failed to parse the data returned by the ICC
			res = ERR_CMD_INVALID_ICC_RESPONSE;
		}
		if (data)
			delete [] data;
	}
	else // Response from the card is not '9000'
	{
		res = EMV_CONDITIONS_NOT_SATISFIED;
	}

	if (res == SUCCESS)
	{
		*ddol_data = auth_data;
		*ddol_data_len = auth_data_len;
	}

	return res;
}

int OfflineDataAuthentication::getDDOL(DataObject *dob_DDOL)
{
	int res;
	// 1.1. Try to get DDOL from the context (read from the ICC in previous steps)
	res = EMV_Context::EnvContext.getTagValue (0x9f49, dob_DDOL, true);
	if (res != SUCCESS)
	{
		// DDOL has not been read from the ICC. Try to find default DDOL
		// From the terminal
		res = EMV_Context::EnvContext.getTagValue (CNFG_APPLICATION, 0x9f49,
			dob_DDOL);
		if (res != SUCCESS)
		{
			// There are no default DDOL in the Registry.
			res = EMV_CONDITIONS_NOT_SATISFIED;
		}
	}
	return res;
}

int OfflineDataAuthentication::getInternalAuthData (byte **auth_data, 
													UNINT *auth_data_len)
{
	int res;

	// 1. Get DDOL
	DataObject dob_DDOL;
	if ((res = getDDOL(&dob_DDOL)) != SUCCESS)
		return res;

	dol_parser parser(&(EMV_Context::EnvContext));
	DOL_ELEMENT dol;

	res = parser.parse_dol_tags (dob_DDOL.Data, dob_DDOL.len, &dol);
	if (res != SUCCESS)
		return EMV_CONDITIONS_NOT_SATISFIED;
	if (!IsUnpredNum(&dol))
	{
		// Unpredictable number is not found in DDOL
		return EMV_CONDITIONS_NOT_SATISFIED;
	}
	// Remove unpredictable number from the Context
	EMV_Context::EnvContext.removeTag (0x9f37);
	res = parser.fill_dol (0x9f49, &dol, auth_data, auth_data_len);
	if (dol.num_elements > 0)
	{
		delete [] dol.pTags;
		delete [] dol.pLength;
	}
	return SUCCESS;
}
	
bool OfflineDataAuthentication::IsUnpredNum(DOL_ELEMENT *dol)
{
	for (int i = 0; i < dol->num_elements; i++)
	{
		if (dol->pTags [i] == 0x9f37)
			return true;
	}
	return false;
}

int OfflineDataAuthentication::ParseFormat1(tlv_parser *parsed_data, 
											byte **dynoSig, UNINT *dyno_len)
{
	int res;
	if (parsed_data->GetRoot ()->GetLengthVal () > 0)
	{
		*dyno_len = parsed_data->GetRoot ()->GetLengthVal ();
		*dynoSig = new byte [*dyno_len];
		if (*dynoSig)
		{
			memcpy (*dynoSig, parsed_data->GetRoot ()->GetValue (),
				*dyno_len);
			res = SUCCESS;
		}
		else
			res = ERR_MEMORY_ALLOC;
	}
	else
	{
		*dynoSig = 0;
		*dyno_len = 0;
		res = SUCCESS;
	}
	return res;
}

int OfflineDataAuthentication::ParseFormat2(tlv_parser *parsed_data, 
											byte **dynoSig, UNINT *dyno_len)
{
	int res;
	*dynoSig = 0;
	*dyno_len = 0;

	EnvContext.removeTag (0x9f4b);
	if ((res = StoreInContext(parsed_data)) != SUCCESS)
		return res;

	// Check if Signed Dynamic Application Data is present
	DataObject dob_Sig;
	if ((res = EnvContext.getTagValue (0x9f4b, &dob_Sig, true)) != SUCCESS)
	{
		// Signed Dynamic Appl. Data is not returned by the ICC
		return ERR_CMD_INVALID_ICC_RESPONSE;
	}

	// Signed Dynamic Appl. Data is returned by the ICC
	if (dob_Sig.len <= 0)
		return SUCCESS;
	
	
	*dynoSig = new byte [dob_Sig.len];
	if (!(*dynoSig))
		return ERR_MEMORY_ALLOC;
	
	memcpy (*dynoSig, dob_Sig.Data, dob_Sig.len);
	*dyno_len = dob_Sig.len;
	return SUCCESS;
}

int OfflineDataAuthentication::StoreInContext (tlv_parser *parsed_data)
{
	int res;
	tlv_parser *tlvCurObject;
	tlvCurObject = parsed_data->GetFirstChild ();
	while (tlvCurObject)
	{
		// Save current child in registry
		DataObject dob_data;
		res = dob_data.set (tlvCurObject->GetRoot ()->GetValue (),
			       		    tlvCurObject->GetRoot ()->GetLengthVal (),
					        CNFG_TRANSACTION, NULL);
		if (res == SUCCESS)
		{
			res = EnvContext.setTagValue (tlvCurObject->GetRoot ()->GetTagVal (),
				&dob_data, IO_CREATE | IO_UPDATE);
		}
		// Go To the next child
		tlvCurObject = parsed_data->GetNext ();
	}
	return SUCCESS;
}
