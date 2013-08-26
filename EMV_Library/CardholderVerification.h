/*
CardholderVerification.h
Implements the "Cardholder Verification" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.5; VIS 1.4.0, ch 8.

Note: Implements the following methods:
- Offline plaintext PIN,
- Offline enciphered PIN,
- Signature,
- Offline plaintext PIN & Signature,
- Offline enciphered PIN & Signature,
- CVM Failed,
- No CVM required
*/
#include "EMV_Context.h"
#include "CVM_List.h"
#include "CVM_Rules.h"
#include "../Runtime/PINControlImpl.h"
#include "../Utility/utility.h"
#include "scr_command.h"
#include "emv_constants.h"
#include "OfflineDataAuthentication.h"

enum COMPARE_FLAG {LESS_THAN, MORE_THAN};
enum CVM_RESULT_CODING {CVM_CODE=0, CVM_COND, CVM_RESULT};
enum PIN_OFFLINE_TYPE {PIN_OFFLINE_PLAINTEXT, PIN_OFFLINE_ENCIPHERED};

class CardholderVerification :
	public EMV_Context
{
public:
	CardholderVerification(void);
	CardholderVerification(const byte *odaList, int oda_len);
	virtual ~CardholderVerification(void);

	int initData();

	int Verify();
	int VisaDefaultCVM();

	int checkCondition (short rule, int AmountX, int AmountY);
	int executeCVM(short rule);

	// Offline PIN verification performed by ICC
	int offlinePinICC(PIN_OFFLINE_TYPE offline_pin_type);
	// Enciphered PIN verification online
	int encipheredPinOnline();
	// Plaintext PIN verification performed by ICC and Signature (paper
	int plaintextPinICC_Sign();
	// Enciphered PIN verification performed by ICC and signature (paper)
	int encipheredPinICC_Sign();
	// Signature (paper)
	int signature();


private:
	int checkTransType(bool cash);
	int checkIfSupported (short rule);
	int checkBit (const byte key, const byte mask);
	int checkAmount(int ThresholdAmount, COMPARE_FLAG comp_flag);

	bool IsOfflineSupported();
	int getPinCounter (byte *tryCounter);
	int verifyPIN (PIN_OFFLINE_TYPE offline_pin_type, 
				   const byte pin[], UNINT pin_size, byte *tryCounter);
	int createPlaintextBlock(const byte plaintextPIN[], 
							 const int size, 
							 byte pin_block[], 
							 const int block_size);
	int EncipherPin(const byte pin_block[], 
					const int block_size, 
					byte **enciph_pin, 
					UNINT *enciph_pin_len);

	void updateCvmResult(byte cvm_code, 
						 byte cvm_condition, 
						 byte cvm_result);
	// Shift byte array of size 'size' to the right number of positions in 'adjustment'.
	// Each position is 4 bits.
	void shiftAmount (byte Amount[], int size, int adjustment);

	int InitPubKey(bool *bEncipheredCert,
				   DataObject *pdob_IccPKCert, 
		 		   DataObject *pdob_IccPKrem, 
				   ODA_KEY_INFO *IccKeyInfo);
	int retreiveIccPK(CryptoControlImpl *Crypto,
					bool bEncipheredCert,
					DataObject *pdob_IccPKCert, 
					DataObject *pdob_IccPKrem, 
					ODA_KEY_INFO *IccKeyInfo);
	int getUnpredictableNumber(byte UnpredNumber[], const int *UnpredLen);
	int getRandomPattern (CryptoControlImpl *Crypto,
						  byte **randPattern, int *randLen, UNINT KeyLength);
	int encipherPinBlock (CryptoControlImpl *Crypto, 
						  ODA_KEY_INFO *IccKeyInfo,
						  byte *plaintextData, 
						  int data_len,
						  byte **enciph_pin, 
						  UNINT *enciph_pin_len);
	
private:
	DataObject dob_TVR;
	DataObject dob_TSI;
	DataObject dob_AIP;

	DataObject dob_cvmRes;

	CVM_List cvm_list;
	byte CVMResult[3];
	const byte *ODA_list;
	byte ODA_len;
};
