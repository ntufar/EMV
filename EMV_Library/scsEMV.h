/*
scsEMV.h
This class contains the methods necessary to execute an EMV transaction. 
Each method, when called, instantiates an appropriate class which implements
corresponding EMV transaction phase.

*/
#ifndef SCSEMV_H
#define SCSEMV_H

#include "EMV_Context.h"

#include "ApplicationInitialization.h"
#include "ReadApplicationData.h"
#include "OfflineDataAuthentication.h"
#include "ProcessingRestrictions.h"
#include "CardholderVerification.h"
#include "TerminalRiskManagement.h"
#include "TerminalActionAnalysis.h"
#include "CardActionAnalysis.h"
#include "TransactionDecision.h"

class scsEMV: public EMV_Context
{
public:
	scsEMV();
	virtual ~scsEMV(void);

	int ApplicationInit(tlv_parser *tlv_Appl, tlv_parser *tlv_AIP);
	int ReadApplData (tlv_parser *tlv_AIP, byte **ppOdaList, int *oda_len);
	int offlineDA(const byte *odaList, int oda_len);
	int ProcessRestrictions ();
	int CardHolderVerification(const byte *odaList, int oda_len);
	int riskManagement();
	int makeTransactionDecision(TERMINAL_RESPONSE *term_resp);
	int getTransactionData (int Tag, byte *data_value, int *data_len, 
						    char format[], bool bHashOnly = true);
	int IncrementTransactionSeqCounter();
private:
	bool combinedDDA_AC;
};

#endif
