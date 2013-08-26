/*
TransactionDecision.h
Implements the following phases of EMV transaction:
- Terminal Action Analysis,
- Requesting Card Cryptogram (issuing Generate AC command),
- Card Action Analysis (Analysing the card response to Generate AC command),
- Going Online if necessary,
- Performing Referral processing if necessary,
- Completing transaction

Reference: EMV 4.0 book 3, ch 6.1; VIS 1.4.0, ch 4.
*/
#ifndef TRANSACTIONDECISION_H
#define TRANSACTIONDECISION_H

#include "EMV_Context.h"
#include "TerminalActionAnalysis.h"
#include "CardActionAnalysis.h"
#include "Completion.h"
#include "OnLineProcessing.h"
#include "Referral.h"

class TransactionDecision :
	public EMV_Context
{
public:
	TransactionDecision(void);
	virtual ~TransactionDecision(void);

	int MakeTransactionDecision(bool combinedDDA_AC, TERMINAL_RESPONSE *term_resp);
	
	int ValidateDynamicSignature(bool *IsValid);

private:
	int goOnline ();

private:
	TerminalActionAnalysis taa;
	CardActionAnalysis caa;
};

#endif

