/*
Completion.h
Implements the "Completion" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.11; VIS 1.4.0, ch 13.
*/
#ifndef COMPLETION__H
#define COMPLETION__H

#include "EMV_Context.h"
#include "../Utility/Language.h"
#include "TerminalActionAnalysis.h"
#include "CardActionAnalysis.h"
#include "IssuerScriptProcessing.h"
#include "../Runtime/RefInterface.h"
#include "../Runtime/HostInterface.h"
#include "emv_constants.h"

class Completion :
	public EMV_Context
{
public:
	Completion(void);
	virtual ~Completion(void);

	int initData();
	int completeTransaction(TERMINAL_RESPONSE *term_resp);

private: // Private functions
	CRYPTOGRAM_TYPE getP1fromOnlineResp();
	int getP1 (CRYPTOGRAM_TYPE *p1);
	bool IsOnlineSucceeded ();
	void OutputMessage(UNINT msgID);
	int InitializeData();
	int complete_No2GAC(byte cid, CRYPTOGRAM_TYPE *FinalDecision,
		bool *AdviceNeeded);
	int complete_2GAC(byte cid, CRYPTOGRAM_TYPE *FinalDecision,
		bool *AdviceNeeded);

private: // Private members
	DataObject dob_TVR;
	DataObject dob_CID;
};

#endif

