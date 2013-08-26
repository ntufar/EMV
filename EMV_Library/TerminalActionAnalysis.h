/*
TerminalActionAnalysis.h
Implements the "Terminal Action Analysis" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.7; VIS 1.4.0, ch 10.
*/
#ifndef TERMINALACTIONANALYSIS_H
#define TERMINALACTIONANALYSIS_H


#include "EMV_Context.h"
#include "emv_constants.h"
#include "TerminalRiskManagement.h"
#include "dol_parser.h"

enum ANALYSIS_RESULT {MATCHED_BITS_FOUND, MATCHED_BITS_NOT_FOUND};

#define CHECK_CYPTO_TYPE (CryptoTypeVal, CryptoType)(((((CryptoTypeVal) >> 6) & 0x03) == (CryptoType))? true: false)

static const byte ALL_0[] = {0x00, 0x00, 0x00, 0x00, 0x00};
static const byte ALL_1[] = {0xff, 0xff, 0xff, 0xff, 0xff};

class TerminalActionAnalysis :
	public EMV_Context
{
public:
	TerminalActionAnalysis(void);
	virtual ~TerminalActionAnalysis(void);

	int initData();

	// Implements Offline processing results as it defenied in:
	// VIS 1.4.0, ch 10.4.1 (see Figure 10-1), or in
	// EMV 4.0, book 3, ch 6.7.
	int OfflineProcessingResults(CRYPTOGRAM_TYPE *crypto_type);

	// Implements 1st call to GenerateAC command - requesting Application
	// Cryptogram.
	// Sources: VIS 1.4.0, ch 10.4.2, and
	// EMV 4.0, book 3, ch 6.7.
	int RequestApplCryptogram (byte issuance,
							   CRYPTOGRAM_TYPE crypto_type, 
		     				   bool combinedDDA_AC,
							   byte **pGenACData, UNINT *data_len);

	int CheckOfflineDenial(ANALYSIS_RESULT *ansisRes);
	int CheckOnline(ANALYSIS_RESULT *ansisRes);
	int CheckDefault(ANALYSIS_RESULT *ansisRes, bool AfterOnlineFailed);

private:
	DataObject dob_TVR;
	
private:
	int getActionCode(int Tag, DataObject *dob, 
					  const byte default_val[], 
					  bool from_icc);
	int updateAuthRespCode(const char* code);
};

#endif

