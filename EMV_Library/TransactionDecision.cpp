#include "TransactionDecision.h"
#include "Completion.h"

TransactionDecision::TransactionDecision(void)
{
}

TransactionDecision::~TransactionDecision(void)
{
}

int TransactionDecision::MakeTransactionDecision(bool combinedDDA_AC,
												 TERMINAL_RESPONSE *term_resp)
{
	int res;
	CRYPTOGRAM_TYPE term_cryptogram;
	
	byte *pGenACData;
	UNINT data_size;
	Completion comple;
	Referral ref;

	SCRControlImpl *pSCR = (SCRControlImpl*)EnvContext.GetService(CNTXT_SCR);
	if (!pSCR)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;

	// Perform Terminal Action Analysis and issue first GenerateAC command

	// 1. Perform a Terminal Action Analysis in order to get a terminal decision 
	// on the displacement of the current transaction (approve or decline offline, or
	// send online)
	OutputMsg ("EMV - Terminal Action Analysis");
	if ((res = taa.OfflineProcessingResults (&term_cryptogram)) != SUCCESS)
	{
		// Run time error deected. Exit the transaction
		return res;
	}

	// 2. Send 1st GenerateAC command to request the card to perform 
	// Card Action Analysis and respond with ICC's decision on whether 
	// to approve or decline transaction offline, or go online.
	OutputMsg ("EMV - First GenerateAC command");
	res = taa.RequestApplCryptogram (1,
									 term_cryptogram,
									 combinedDDA_AC,
									 &pGenACData,
									 &data_size);
	if (res != SUCCESS)
	{
		// Runtime error -- exit the transaction
		return res;
	}

	// 3. Parse the results of Card Action Analysis
	res = caa.parseCardActAnlysResults (combinedDDA_AC,
										pGenACData, data_size);
	if (res == SUCCESS)
	{
		if ((res = caa.analyzeResults(term_cryptogram)) == SUCCESS)
		{
			// Set the 'Card risk management was performed' bit in the TSI
			updateDataObject (0x9b, 1, 0x20);
		}
	}
	
	// Release buffer for pGenACData - don't need anymore
	delete [] pGenACData;

	// Check the result of parsing Card Action Analysis result
	if (res != SUCCESS)
	{
		// Runtime error. Terminate the current transaction
		return res;
	}

	// Set transaction results based on the Card Action Analysis Results
	if (caa.IsAdviseRequired ())
	{
		// Update Transaction Results to indicate that advice is required
		EMV_Context::updateDataObject (0x50000004, 1, 0x02, true);
	}
	if (caa.getRaf () != 0x00)
	{
		// Update Transaction Results to indicate reason for advice or referral
		EMV_Context::updateDataObject (0x50000004, 1, ((caa.getRaf () & 0x07)<<2), true);
	}

	// 4. Check if combined DDA/AC needs to be performed
	if ((caa.getIccCryptogram () == TC ||
		caa.getIccCryptogram () == ARQC) && combinedDDA_AC)
	{
		OutputMsg ("EMV: Combined DDA/AC - Validate Dynamic Signature");
		// Validate dynamic signature & hash of static data
		bool IsValid;
		res = ValidateDynamicSignature(&IsValid);
		if (!IsValid)
		{
			// Set the 'DDA/AC Generation failed in TVR
			updateDataObject (0x95, 1, 0x04);
			// Go To Completion
			return comple.completeTransaction (term_resp);
		}
	}
	if (caa.getIccCryptogram () == ARQC)
	{
		// Go Online
		res = goOnline ();
		
		if (res != SUCCESS)
		{
			if (EMV_Context::ReversalNeeded)
			{
				// This condition requires sending a reversal message
				logDataRecord (EMV_LOG_REVERSAL, MSG_REVERSAL);
			}
			return res;
		}
		if (!pSCR->IsTransactionAlive(TransactionToken))
		{
			if (EMV_Context::OnLineCompleted && 
				EMV_Context::OnLineResult == ONRES_APPROVE)
			{
				// Send reversal first and then exit
				logDataRecord (EMV_LOG_REVERSAL, MSG_REVERSAL);
				EMV_Context::OnLineCompleted = false;
				EMV_Context::OnLineResult = ON_RES_UNKNOWN;
			}
			return SCR_TRANSACTION_DISCONTINUED;
		}

		if (EMV_Context::OnLineCompleted == true &&
			EMV_Context::OnLineResult == ONRES_REFERRAL)
		{
			// Issuer requested a referral
			res = ref.execReferral (REF_INIT_BY_ISSUER);
		}
		// Go to Completion
	}
	else if (caa.getIccCryptogram() == AAR)
	{
		// Referral
		if ((res = ref.execReferral (REF_INIT_BY_CARD)) != SUCCESS)
			return res;
		if (check_bit(EMV_Context::ReferralResponseCode, REF_ONLINE))
		{
			res = goOnline ();
			if (res != SUCCESS)
			{
				if (EMV_Context::ReversalNeeded)
				{
					// This condition requires sending a reversal message
					logDataRecord (EMV_LOG_REVERSAL, MSG_REVERSAL);
				}
			}
			// Go To Completion
		}
	}
	else if (caa.getIccCryptogram () == AAC)
	{
		if (caa.getRaf() == 0x01)
		{
			// Output message 'SERVICE NOT ALLOWED'
			UIControlImpl *pUI = (UIControlImpl*)EMV_Context::GetService (CNTXT_UI);
			if (pUI && pUI->opened ())
			{
				pUI->writeStatus (Language::getString (MSG_ID__NOT_ACCEPTED, DEFAULT_LANG), true);
			}
			
		}
	}
	if (res != SUCCESS)
		return res; // Exit transaction

	// Go to Completion
	return comple.completeTransaction (term_resp);
}

int TransactionDecision::ValidateDynamicSignature(bool *IsValid)
{
	// Implement Validation of Static data here
	*IsValid = false;
	return SUCCESS;
}

int TransactionDecision::goOnline ()
{
	OutputMsg ("EMV - Attempt to go Online");
	OnLineProcessing onLine;
	int res = onLine.goOnline ();
	if (res != SUCCESS)
	{
		char buff [80];
		sprintf (buff, "Failed sending online message (%x)", res);
		OutputMsg(buff);
		if (onLine.IsTerminationRequested ())
		{
			return res;
		}
	}
	// Always return Success here, so transaction will not terminate
	// in a case of the error, but will attempt to complete transaction
	// offline.
	// Static flag OnLineCompleted of the class EMV_Context 
	// keeps the status of the online communication 
	return SUCCESS;
}
