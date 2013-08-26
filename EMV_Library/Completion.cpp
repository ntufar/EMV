#include "Completion.h"
#include "../Runtime/UIControlImpl.h"


Completion::Completion(void)
{
}

Completion::~Completion(void)
{
}

int Completion::initData()
{
	const int size = 2;
	int tags[size];
	DataObject *dob[size];
	bool hashOnly[size];
	bool mandatory[size];

	int i = 0;

	// TVR
	tags[i] = 0x95; 
	dob[i] = &dob_TVR;
	hashOnly[i] = true;
	mandatory[i] = true;

	i++;
	// Cryptogram Information Data
	tags[i] = 0x9f27; 
	dob[i] = &dob_CID;
	hashOnly[i] = true;
	mandatory[i] = true;

	return EMV_Context::initData (tags, dob, hashOnly, mandatory, size);
}

// Performs Completion phase of EMV transaction
// Source: VIS 1.4.0, ch 14, Figure 13-1.
int Completion::completeTransaction(TERMINAL_RESPONSE *term_resp)
{
	int res;
	byte cid = 0;
	byte cd = 0;
	CRYPTOGRAM_TYPE FinalDecision;
	bool AdviceNeeded = false;

	if ((res = InitializeData()) == SUCCESS)
	{
		cid = dob_CID.Data [0];
		cd = cid >> 6;
		if (cd == AAC || cd == TC)
			res = complete_No2GAC(dob_CID.Data[0], &FinalDecision, &AdviceNeeded);
		else
			res = complete_2GAC(dob_CID.Data[0], &FinalDecision, &AdviceNeeded);
	}

	if (res == SUCCESS)
	{
		if (FinalDecision == TC)
		{
			// Transaction is APPROVED!!!
			OutputMessage (MSG_ID__APPROVED);
			*term_resp = TERMINAL_APPROVE;
			// Update Transaction Results to indicate that transaction is approved
			EMV_Context::updateDataObject (0x50000004, 1, 0x01, true);

			// Log Data Batch
			logDataRecord (EMV_LOG_DATA_BATCH, MSG_DATA_BATCH, BATCH_FIN_REC);
		}
		else //(FinalDecision == AAC)
		{
			// Transaction is DECLINED!!!
			OutputMessage (MSG_ID__DECLINED);
			*term_resp = TERMINAL_DECLINE;
			// Update Transaction Results to indicate that transaction is declined
			EMV_Context::updateDataObject (0x50000004, 1, 0x01, false);
			
			// Log data required
			if (AdviceNeeded)
				logDataRecord (EMV_LOG_DATA_BATCH, MSG_DATA_BATCH, BATCH_ADV_REC);
		}
		if (EMV_Context::ReversalNeeded)
		{
			// This condition requires sending a reversal message
			logDataRecord (EMV_LOG_REVERSAL, MSG_REVERSAL);
		}
		return SUCCESS;
	}
	else // res != SUCCESS
	{
		// Either Data is not initialized, or there were some error
		// during final steps of transaction.
		// Check if reversal is required
		if (EMV_Context::ReversalNeeded)
		{
			// This condition requires sending a reversal message
			logDataRecord (EMV_LOG_REVERSAL, MSG_REVERSAL);
		}
	}	
	return res;
}

// Initialize mandatory data objects
int Completion::InitializeData()
{
	int res;
	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		res = EMV_MISSING_MANDATORY_DATA;
	else if (InitStatus == EMV_DATA_NOT_INITIALIZED)
		res = initData ();
	else // InitStatus == EMV_DATA_INITIALIZED
		res = SUCCESS;

	return res;
}

// Complets transaction without issuing 2nd GenerateAC command.
// Valid only for transactions for which the response to 1st GenerateAC
// comand returned either AAC or TC (Offline decline or Offline Approve)
int Completion::complete_No2GAC(byte cid, CRYPTOGRAM_TYPE *FinalDecision,
								bool *AdviceNeeded)
{
	int res;
	*AdviceNeeded = false;
	// Is cryptogram type AAC?
	if ((cid >> 6) == AAC)
	{
		// Set Authorization Response Code to Z1 (decline)
		res = EMV_Context::setDataObject(0x8a, 
			(byte*)SCS_OFFLINE_DECLINED, 
			(int)strlen(SCS_OFFLINE_DECLINED), "an", CNFG_TRANSACTION);
		*FinalDecision = AAC;

		if (check_bit(cid, 0x08))
		{
			// Advice is required
			*AdviceNeeded = true;
		}
	}
	else //if ((cid >> 6) == TC)
	{
		// Check the result of combined DDA/AC
		if (check_bit(cid, 0x04))
		{
			// Combined DDA/AC failed!
			// Set Auth. Resp. Code to Z1 (decline)
			res = EMV_Context::setDataObject(0x8a, 
				(byte*)SCS_OFFLINE_DECLINED, 
				(int)strlen(SCS_OFFLINE_DECLINED), "an", CNFG_TRANSACTION);
			*FinalDecision = AAC;
		}
		else
		{
			// Combined DDA/AC suceeded!
			// Set Auth. Resp. Code to Y1 (approve)
			res = EMV_Context::setDataObject(0x8a, 
				(byte*)SCS_OFFLINE_APPROVED, 
				(int)strlen(SCS_OFFLINE_APPROVED), "an", CNFG_TRANSACTION);
			*FinalDecision = TC;
		}
	}
	return SUCCESS;
}

// Complets transaction after issuing 2nd GenerateAC command.
// Valid only for transactions for which the response to 1st GenerateAC
// comand returned either AAR or ARQS (Referral or Online request)
int Completion::complete_2GAC(byte cid, CRYPTOGRAM_TYPE *FinalDecision,
							  bool *AdviceNeeded)
{
	int res;
	*AdviceNeeded = false;
	TerminalActionAnalysis taa;
	IssuerScriptProcessing isp;
	bool onLineForsed = false;
	bool referral = false;
	bool online = false;
	CRYPTOGRAM_TYPE p1;

	// Is AAR (Referral)
	if ((cid >> 6) == AAR)
	{
		referral = true;
		if (check_bit(EMV_Context::ReferralResponseCode, REF_ONLINE))
		{
			// Online has been forsed
			onLineForsed = true;
		}
	}
	if ((dob_CID.Data [0] >> 6) == ARQC) 
		online = true;
			
	if (online || onLineForsed)
	{
		// Set result of online
		if ((res = getP1(&p1)) != SUCCESS)
		{
			// Failed to process Authorization response,
			// Attempt to complete transaction by requesting
			// Decline from 2nd GenerateAC
			p1 = AAC;
		}
	}
	else // (referral == true)
	{
		// Set result of referral
		if (check_bit(EMV_Context::ReferralResponseCode, REF_APPROVE))
			p1 = TC;
		else
			p1 = AAC;
	}
	
	if (IsOnlineSucceeded() && (online || onLineForsed))
	{
		// Execute Issuer scripts with tag 0x71 - scripts to be executed
		// prior final Generate AC command
		isp.processScript(SCS_BEFORE_GENERATE_AC);
	}

	// Issue Final Generate AC command
	byte *pGenACData = 0;
	UNINT data_len;
	OutputMsg("EMV - Second GenerateAC command");
	res = taa.RequestApplCryptogram (2, p1, false, &pGenACData, &data_len);
	if (res != SUCCESS)
	{
		if ((online || onLineForsed) && 
			EMV_Context::OnLineResult == ONRES_APPROVE)
		{
			// Reverse message is required
			EMV_Context::ReversalNeeded = true;
		}
		return res;
	}

	if (IsOnlineSucceeded() && (online || onLineForsed))
	{
		// Execute Issuer scripts with tag 0x72 - scripts to be executed
		// after final Generate AC command
		isp.processScript(SCS_AFTER_GENERATE_AC);
	}

	CardActionAnalysis caa;
	res = caa.parseCardActAnlysResults (false, pGenACData, data_len);
	delete [] pGenACData;
	if (res != SUCCESS)
	{
		if ((online || onLineForsed) && 
			EMV_Context::OnLineResult == ONRES_APPROVE)
		{
			// Reverse message is required
			EMV_Context::ReversalNeeded = true;
		}
		return res;
	}

	if (caa.getIccCryptogram () == TC && p1 == TC)
	{
		// Terminal responds with approval
		*FinalDecision = TC;
	}
	else // caa.getIccCryptogram () != TC || p1 != TC
	{
		//Terminal responds with a decline
		*FinalDecision = AAC;
		
		bool log = false;

		if ((online || onLineForsed) && 
			EMV_Context::OnLineResult == ONRES_APPROVE)
		{
			// Reverse message is required
			EMV_Context::ReversalNeeded = true;
			log = true;
		}

		if (caa.IsAdviseRequired () || check_bit(cid, 0x08))
		{
			*AdviceNeeded = true;
			log = true;
		}
		if (EnvContext.tagExist(0x9F5B, true) && !log)
		{
			// No Message is created for current transaction (transaction
			// is declined. Therefore, use offline advice to pass the
			// results of the issuer script execution (tag '9F5B').
			// Per test case 2CM.052.00, EMV book 4, section 2.3.9
			*AdviceNeeded = true;
		}
	}
	return SUCCESS;
}


void Completion::OutputMessage(UNINT msgID)
{
	UIControlImpl *pUI = (UIControlImpl *)EnvContext.GetService(CNTXT_UI);
	switch (msgID)
	{
	case MSG_ID__DECLINED:
		pUI->setPrompt (Language::getString(MSG_ID__DECLINED, pUI->getLanguage()));
		break;
	case MSG_ID__APPROVED:
		pUI->setPrompt (Language::getString(MSG_ID__APPROVED, pUI->getLanguage()));
		break;
	default:
		break;
	}
}

CRYPTOGRAM_TYPE Completion::getP1fromOnlineResp()
{	
	if (EMV_Context::OnLineResult == ONRES_APPROVE)
		return TC;
	else if (EMV_Context::OnLineResult == ONRES_DECLINE)
		return AAC;
	else if (EMV_Context::OnLineResult == ONRES_REFERRAL)
	{
		if (check_bit(EMV_Context::ReferralResponseCode, REF_APPROVE))
		{
			return TC; // Approve
		}
		else 
		{
			// Decline
			return AAC;
		}
	}
	else //if (EMV_Context::OnLineResult == ONRES_UNKNOWN)
	{
		// Unrecognized Auth. Resp. Code -- Decline
		return AAC;
	}
}

bool Completion::IsOnlineSucceeded ()
{
	return EMV_Context::OnLineCompleted;
}

int Completion::getP1 (CRYPTOGRAM_TYPE *p1)
{
	int res;
	TerminalActionAnalysis taa;

	// Check the result of combined DDA/AC
	if (check_bit(dob_TVR.Data[0], 0x04))
	{
		// Combined DDA/AC failed!
		*p1 = AAC;	
	}
	else
	{
		// Combined DDA/AC suceeded!
		if (IsOnlineSucceeded ())
		{
			*p1 = getP1fromOnlineResp();
		}
		else
		{
			// Online processing failed.
			// Check Default Action Codes
			ANALYSIS_RESULT ansisRes;
			res = taa.CheckDefault (&ansisRes, true);
			if (res != SUCCESS)
				return res;
			if (ansisRes == MATCHED_BITS_FOUND)
			{
				// Set Auth. Resp. Code to Z3 (set inside of the CheckDefault
				// function) & P1 to AAC
				*p1 = AAC;
			}
			else // ansisRes == MATCHED_BITS_NOT_FOUND
			{
				// Set Auth. Resp. Code to Y3 (set inside of the CheckDefault
				// function) & P1 to TC
				*p1 = TC;
			}
		}
	}
	return SUCCESS;
}
