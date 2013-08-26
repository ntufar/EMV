/*
CardActionAnalysis.h
Implements the "Card Action Analysis" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.8; VIS 1.4.0, ch 11.

Note: This class is used to analyse the results returned by the card in 
response to Generate AC command.
*/
#ifndef CARDACTIONANALYSIS_H
#define CARDACTIONANALYSIS_H

#include "EMV_Context.h"
#include "emv_constants.h"

class CardActionAnalysis :
	public EMV_Context
{
public:
	CardActionAnalysis(void);
	virtual ~CardActionAnalysis(void);

// Modifiers:
//------------------------------------------------------------------
	int analyzeResults(CRYPTOGRAM_TYPE term_requested_cryptogram);

	int parseCardActAnlysResults(bool CombineDDA_AC,
								 byte *pGenACData, UNINT data_len);

	int parsePrimitive(const byte *resp_data, const int data_len);
	int parseConstructed(tlv_parser *resp_data);

private:
	void setCryptogramType(byte cryptogram_type);
	void parse_tlv_element(tlv_parser *tlv_data);
//-------------------------------------------------------------------

// Accessors:
// -------------------------------------------------------------
public:
	CRYPTOGRAM_TYPE getIccCryptogram();
	bool IsCombinedDDA_AC();
	bool IsAdviseRequired();
	byte getRaf();
	byte getpaymentSystCA();
// -------------------------------------------------------------

// Members:
// -------------------------------------------------------------
private:
	CRYPTOGRAM_TYPE term_requested_cryptogram; // cryptogram requested by the terminal
	CRYPTOGRAM_TYPE icc_requested_cryptogram; // Cryptogram returned by the ICC
	bool CombineDDA_AC;  // true if Combined DDA/AC is to be performed
	bool adviseRequired; // true if advise is required
	byte raf_code; // Reason/Advice/Referral code
	byte paymentSystCA; // Payment System specific cryptogram
// ------------------------------------------------------------
};

#endif

