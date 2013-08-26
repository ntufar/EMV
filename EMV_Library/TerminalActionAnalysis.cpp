#include "TerminalActionAnalysis.h"

TerminalActionAnalysis::TerminalActionAnalysis(void)
{
}

TerminalActionAnalysis::~TerminalActionAnalysis(void)
{
}

int TerminalActionAnalysis::initData()
{
	const int size = 1;
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

	return EMV_Context::initData (tags, dob, hashOnly, mandatory, size);
}

// Implements Terminal Action Analysis as it defenied in:
// EMV 4.0, book 3, ch 6.7, or
// VIS 1.4.0, ch 10.4.1 (see Figure 10-1).
int TerminalActionAnalysis::OfflineProcessingResults(CRYPTOGRAM_TYPE *crypto_type)
{
	int res;
	ANALYSIS_RESULT analysisRes;

	if ((res = CheckOfflineDenial(&analysisRes)) != SUCCESS)
		return res;
	if (analysisRes == MATCHED_BITS_FOUND)
	{
		// Offline declined
		// Set Cryptogram type to ACC
		*crypto_type = AAC;
	}
	else
	{
		// analysisRes == MATCHED_BITS_NOT_FOUND
		if (IsOnlineTerminal ())
		{
			// Online capable terminal
			if ((res = CheckOnline(&analysisRes)) != SUCCESS)
				return res;
			if (analysisRes == MATCHED_BITS_NOT_FOUND)
			{
				// Offline Approved.
				// Set Cryptogram to TC
				*crypto_type = TC;
			}
			else // analysisRes == MATCHED_BITS_FOUND
			{
				// Send Online.
				// Set Cryptogram to ARQC
				*crypto_type = ARQC;
			}
		}
		else // Offline only terminal
		{
			if ((res = CheckDefault(&analysisRes, false)) != SUCCESS)
				return res;
			if (analysisRes == MATCHED_BITS_FOUND)
			{
				// Offline declined.
				// Set Cryptogram to AAC
				*crypto_type = AAC;
			}
			else // analysisRes == MATCHED_BITS_NOT_FOUND
			{
				// Offline approved.
				// Set Cryptogram to TC
				*crypto_type = TC;
			}
		}
	}
	return SUCCESS;
}

// Implements 1st call to GenerateAC command - requesting Application
// Cryptogram.
// Sources: VIS 1.4.0, ch 10.4.2, and
// EMV 4.0, book 3, ch 6.7.
// Parameters:
//    instance - must be 1 or 2 corresponding to the first or second issuance of
//			the GenerateAC command
//	  crypto_type - type of cryptogram to send to GenerateAC command
//					can be one of the following: AAC, TC, ARQC
//	  pGenACData - a buffer containing the data field returned by the GenerateAC
//					command. This buffer is allocated inside of this function
//					and it must be freed by a caller
//	  data_len - a length of the pGenACData buffer (number of elements in the array)
// Returns:
//	  SUCCESS - in case of successful completion of the function
//	  Error code - in a case of the failure
int TerminalActionAnalysis::RequestApplCryptogram (byte issuance,
												   CRYPTOGRAM_TYPE crypto_type, 
												   bool combinedDDA_AC,
												   byte **pGenACData, 
												   UNINT *data_len)
{
	// Prepare data for sending with Generate AC command

	int res;
	byte *cdol = 0;
	UNINT cdol_size;


	// Get Card Risk Management Data List (CDOL1) from the context. 
	// This data must have been read from the card in previous steps. 
	DataObject dob_cdol;
	int cdol_tag;
	if (issuance == 1)
	{
		cdol_tag = 0x8c;
	}
	else if (issuance == 2)
	{
		cdol_tag = 0x8d;
	}
	else
	{
		return ERR_BAD_ARGUMENT;
	}

	if ((res = EnvContext.getTagValue (cdol_tag, &dob_cdol, true)) != SUCCESS)
		return res;

	dol_parser dolParser(&EnvContext);
	if ((res = dolParser.createDOL (cdol_tag, dob_cdol.Data, dob_cdol.len,
									&cdol, &cdol_size)) != SUCCESS)
		return res;
	
	//----------
	// Testing, delete these lines after debug
	//DataObject dob;
	//dob.set (cdol, cdol_size, CNFG_TRANSACTION, "b");
	//EnvContext.setTagValue (0x90000001, &dob, IO_CREATE | IO_UPDATE);
	// ------------

	// Issue GenerateAC command
	scr_command command ((SCRControlImpl*)EnvContext.GetService(CNTXT_SCR));
	command.setGenerateAC(cdol, cdol_size, 
					      crypto_type, combinedDDA_AC);
	//release cdol buffer (don't need anymore)
	if (cdol)
		delete [] cdol;

	R_APDU rapdu;
	if ((res = command.run (&rapdu, TransactionToken)) != SUCCESS)
	{
		// GenerateAC command Failed
		return res;
	}
	else
	{
		// GenerateAC command completed successfully
		if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
		{
			// GenerateAC returned SUCCESS
			*data_len = rapdu.getDataLen ();
			if (*data_len > 0)
				*pGenACData = rapdu.copyData ();
			else
				*pGenACData = 0;
		}
		else if (rapdu.getSW1 () == 0x69 && rapdu.getSW2 () == 0x85)
		{
			// Error returned by the reader.
			// Generate AC command is called more than 2 times in the current transaction
			*data_len = 0;
			*pGenACData = 0;
			return ERR_EXCESSIVE_USE_GENERATEAC;
		}
		else
		{
			// Invalid response from ICC
			*data_len = 0;
			*pGenACData = 0;
			return ERR_CMD_INVALID_ICC_RESPONSE;
		}
	}
	return res;
}


// Check the Offline action codes.
// Source: VIS 1.4.0, ch 10.4.1, or EMV 4.0, ch 6.7
// Returns SUCCESS if operation is completed successfully, and error code otherwise.
// Sets ansisRes to MATCHED_BITS_FOUND if there are matching 1's and 
// to MATCHED_BITS_NOT_FOUND otherwise. 
int TerminalActionAnalysis::CheckOfflineDenial(ANALYSIS_RESULT *ansisRes)
{
	int res;

	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;
	else if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// Get IAC-Denial (Issuer Action Codes)
	DataObject dob_iacDenial;
	if ((res = getActionCode(0x00009f0e, &dob_iacDenial, ALL_0, true)) != SUCCESS)
		return res;

	// Get TAC-Denial (Terminal Action Codes)
	DataObject dob_tacDenial;
	if ((res = getActionCode(0x40000008, &dob_tacDenial, ALL_0, false)) != SUCCESS)
		return res;
	
	if (dob_iacDenial.len != 5)
		return ERR_INVALID_ICC_DATA;
	if (dob_tacDenial.len != 5 || dob_TVR.len != 5)
		return ERR_INVALID_TERMINAL_DATA;

	for (int i = 0; i < dob_iacDenial.len; i++)
	{
		if (((dob_iacDenial.Data [i] | dob_tacDenial.Data [i]) & 
			 dob_TVR.Data[i]) != 0x00)
		{
			// Set the Authorization response Code to "Z1" (Offline Decline)
			// VIS 1.4.0, ch 10.4.1, item 1
			if ((res = updateAuthRespCode(SCS_OFFLINE_DECLINED)) != SUCCESS)
				return res;
			*ansisRes = MATCHED_BITS_FOUND;
			return SUCCESS;
		}
	}
	*ansisRes = MATCHED_BITS_NOT_FOUND;
	return SUCCESS;
}

// Check the Online Action codes.
// Source: VIS 1.4.0, ch 10.4.1, or EMV 4.0, ch 6.7
// Returns SUCCESS if operation is completed successfully, and error code otherwise.
// Sets ansisRes to MATCHED_BITS_FOUND if there are matching 1's and 
// to MATCHED_BITS_NOT_FOUND otherwise. 
int TerminalActionAnalysis::CheckOnline(ANALYSIS_RESULT *ansisRes)
{
	int res;
	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;
	else if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// Get IAC-Online (Issuer Action Codes)
	DataObject dob_iacOnline;
	if ((res = getActionCode(0x00009f0f, &dob_iacOnline, ALL_1, true)) != SUCCESS)
		return res;

	// Get TAC-Online (Terminal Action Codes)
	DataObject dob_tacOnline;
	if ((res = getActionCode(0x40000009, &dob_tacOnline, ALL_0, false)) != SUCCESS)
		return res;
	
	if (dob_iacOnline.len != 5)
		return ERR_INVALID_ICC_DATA;
	if (dob_tacOnline.len != 5 || dob_TVR.len != 5)
		return ERR_INVALID_TERMINAL_DATA;

	for (int i = 0; i < dob_iacOnline.len; i++)
	{
		if (((dob_iacOnline.Data [i] | dob_tacOnline.Data [i]) & 
			 dob_TVR.Data[i]) != 0x00)
		{
			*ansisRes = MATCHED_BITS_FOUND;
			return SUCCESS;
		}
	}
	*ansisRes = MATCHED_BITS_NOT_FOUND;
	// Set the Authorization response Code to "Y1" (Offline Approved)
	// VIS 1.4.0, ch 10.4.1, item 1
	return updateAuthRespCode(SCS_OFFLINE_APPROVED);
}

// Check the Default Action codes.
// Source: VIS 1.4.0, ch 10.4.1, or EMV 4.0, ch 6.7
// Returns SUCCESS if operation is completed successfully, and error code otherwise.
// Sets ansisRes to MATCHED_BITS_FOUND if there are matching 1's and 
// to MATCHED_BITS_NOT_FOUND otherwise. 
int TerminalActionAnalysis::CheckDefault(ANALYSIS_RESULT *ansisRes, 
										 bool AfterOnlineFailed)
{
	int res;

	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;
	else if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// Get IAC-Default (Issuer Action Codes)
	DataObject dob_iacDefault;
	if ((res = getActionCode(0x00009f0d, &dob_iacDefault, ALL_1, true)) != SUCCESS)
		return res;

	// Get TAC-Default (Terminal Action Codes)
	DataObject dob_tacDefault;
	if ((res = getActionCode(0x40000007, &dob_tacDefault, ALL_0, false)) != SUCCESS)
		return res;
	
	if (dob_iacDefault.len != 5)
		return ERR_INVALID_ICC_DATA;
	if (dob_tacDefault.len != 5 || dob_TVR.len != 5)
		return ERR_INVALID_TERMINAL_DATA;

	*ansisRes = MATCHED_BITS_NOT_FOUND;
	for (int i = 0; i < dob_iacDefault.len; i++)
	{
		if (((dob_iacDefault.Data [i] | dob_tacDefault.Data [i]) & 
			 dob_TVR.Data[i]) != 0x00)
		{
			// Set the Authorization response Code to "Z3" (Unable
			// to go online, Offline Decline)
			// VIS 1.4.0, ch 10.4.1, item 1
			char *authCode;
			//if (AfterOnlineFailed)
				authCode = SCS_OFFLINE_DECLINED_NO_ONLINE;
			//else
			//	authCode = SCS_OFFLINE_DECLINED;
			if ((res = updateAuthRespCode(authCode)) != SUCCESS)
				return res;
			*ansisRes = MATCHED_BITS_FOUND;
			break;
		}
	}
	if (*ansisRes == MATCHED_BITS_NOT_FOUND)
	{
		// Set the Authorization response Code to "Y3" (Unable
		// to go online, Offline Approved)
		// VIS 1.4.0, ch 10.4.1, item 5
		char *authCode;
		//if (AfterOnlineFailed)
			authCode = SCS_OFFLINE_APPROVED_NO_ONLINE;
		//else
		//	authCode = SCS_OFFLINE_APPROVED;
		if ((res = updateAuthRespCode(authCode)) != SUCCESS)
			return res;
	}
	return SUCCESS;
}


// Finds the Action code corresponding to the Tag, and if it cannot find one,
// then it uses a default value
int TerminalActionAnalysis::getActionCode(int Tag, DataObject *dob, 
										  const byte default_val[], 
										  bool from_icc)
{
	int res;

	res = EnvContext.getTagValue (Tag, dob, from_icc);
	if (res != SUCCESS)
	{
		// Action Code is not in the hash -- use a default value 
		dob->set (default_val, 5, CNFG_APPLICATION, "b");
		res = EnvContext.setTagValue(Tag, dob, IO_CREATE);
	}
	return res;
}

int TerminalActionAnalysis::updateAuthRespCode(const char* code)
{
	return setDataObject(0x8a, (byte*)code, (int)strlen (code),
							   "an", CNFG_TRANSACTION);
}

