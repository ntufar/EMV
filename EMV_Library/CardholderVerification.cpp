#include "CardholderVerification.h"
#include "../Runtime/UIControlImpl.h"
//#include <iostream>

CardholderVerification::CardholderVerification(void):
	ODA_list(0),
	ODA_len(0)
{
	dob_cvmRes.set (0, 3, CNFG_TERMINAL, "b");
}
CardholderVerification::CardholderVerification(const byte *odaList, int oda_len):
	ODA_list(odaList),
	ODA_len(oda_len)
{
	dob_cvmRes.set (0, 3, CNFG_TERMINAL, "b");
}

CardholderVerification::~CardholderVerification(void)
{
}

int CardholderVerification::initData()
{
	const int size = 3;
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

	// Application Interchange Profile
	i++;
	tags[i] = 0x82; 
	dob[i] = &dob_AIP;
	hashOnly[i] = true;
	mandatory[i] = true;

	// Transaction Status Information
	i++;
	tags[i] = 0x9b; 
	dob[i] = &dob_TSI;
	hashOnly[i] = true;
	mandatory[i] = true;

	return EMV_Context::initData (tags, dob, hashOnly, mandatory, size);
}

int CardholderVerification::Verify()
{
	// Initialize CVM result DataObject (CVM, condition, result)
	// '3F' means 'No CVM performed' 
	updateCvmResult(0x3f, 0x00, 0x00);
	CVMResult[CVM_CODE] = 0x3f; 
	CVMResult[CVM_COND] = 0x00; 
	CVMResult[CVM_RESULT] = 0x00;

	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	if (!check_bit(dob_AIP.Data [0], 0x10))
	{
		//AIP indicates that CVM processing is not supported
		// Perform the CVM designated for Visa magnetic stripe transactions
		// See VIS 1.4.0, section 8.5.1
		res = VisaDefaultCVM();
	}
	else
	{
		DataObject dob_CVMList;
		res = EnvContext.getTagValue (0x8e, &dob_CVMList, true);
		if (res != SUCCESS)
		{
			// CVM list has not been read from the card in the previous steps.
			// Set 'ICC data Missing' bit in the TVR
			EMV_Context::updateDataObject(0x95, &dob_TVR, 1, 0x20);
			return SUCCESS;
		}

		// Parse CVM list
		res = cvm_list.parse (dob_CVMList.Data, dob_CVMList.len);
		if (res != SUCCESS)
		{
			// The CVM list cannot be parsed. Terminate a transaction
			return EMV_INVALID_FORMAT;
		}

		int rule = cvm_list.getFirstRule ();

		while (rule != RULE_EOF)
		{
			if ((res = checkCondition( 
				rule, cvm_list.getAmountX(), cvm_list.getAmountY() )) == SUCCESS)
			{
				// Condition satisfied
				// Update CMV Result to include the code of the current CVM
				CVMResult[CVM_CODE] = (byte)((rule & 0x7f00) >> 8); // include "next CVM" bit into the CVM code
				CVMResult[CVM_COND] = (byte)(rule & 0x00ff);
				CVMResult[CVM_RESULT] = (byte)0xff; // Indicates that result is not set
				// Perform Cardholder Verification method
				res = executeCVM(rule);
				if (res == SUCCESS || res == CVM_FORSED_FAILURE)
				{
					// Successful completion of CVM rule
					break;
				}
				else if (res == CVM_METHOD_NOT_RECOGNIZED)
				{
					// The current CVM rule is not supported by this implementation
					// EMV Book 3, chapter 6.5, page 51, or
					// VIS 1.4.0, ch 8.5.1, item 2.
					// Set 'Unrecognized CVM bit' to 1 in the TVR
					EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x40);
				}
				else if (res != CVM_FAILED)
				{
					// Runtime error occured. Stop further execution
					break;
				}

				// If we reach this pointit means either (res == CVM_FAILED) or
				// (res == CVM_RULE_NOT_RECOGNIZED).

				// Check bit 7 of byte 1 of CVM field; if it is 1 - continue with
				// the next CVM entry, if it is '0', then fail the CVM
				if (!check_bit (rule, CVM_APPLY_NEXT))
				{
					// This will break the while loop, and since none of the
					// CVM was successful (otherwise we wouldn't be here),
					// the 'Cardholder verification was not successful' bit will
					// be set to '1' at the end of this function
					//res = SUCCESS;
					break;
				}
			} // End Of If CheckCondition
			//res = SUCCESS;
			
			// Go to the next rule
			rule = cvm_list.getNextRule ();
		}

		// Set TSI to 'Cardholder verification was performed'
		EMV_Context::updateDataObject(0x9b, &dob_TSI, 1, 0x40);

		if (res == SUCCESS && dob_cvmRes.Data[0] == 0x1f) // Is last rule == 'No CVM Required'? 
		{
			res = VisaDefaultCVM();
		}
	}

	// Set CVM Result value
	if (CVMResult[CVM_RESULT] != 0x00 && CVMResult[CVM_RESULT] != 0x02)
		CVMResult[CVM_RESULT] = 0x01; // Set to 'failed'

	// Update CVM Result in context
	updateCvmResult(CVMResult[CVM_CODE], CVMResult[CVM_COND], CVMResult[CVM_RESULT]);
	
	if (res != SUCCESS)
	{
		// There were no successful CVMs, therefore set the 
		// 'Cardholder verification was not successful' bit to '1' in TVR:
		EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x80);
	}
	
	if (res == CVM_FAILED || res == CVM_FORSED_FAILURE ||
		res == CVM_CONDITION_NOT_RECOGNIZED || res == CVM_CONDITION_FAILED ||
		res == CVM_METHOD_NOT_RECOGNIZED || res == CVM_METHOD_NOT_SUPPORETED)
	{
		res = SUCCESS;
	}

	return res;
}

// Performs the CVM designated for Visa magnetic stripe transactions
int CardholderVerification::VisaDefaultCVM()
{
	int res;
	
	// Read the application default CVM from the terminal
	DataObject dob_defaultCVM;
	res = EnvContext.getTagValue (0x40000003, &dob_defaultCVM, false);
	if (res != SUCCESS)
	{
		// Default CVM method is not specified for this application
		return SUCCESS;
	}
	if (dob_defaultCVM.len == 0 || !dob_defaultCVM.Data)
	{
		// Default CVM method is not specified for this application
		return SUCCESS;
	}
	
	byte cvm_code = dob_defaultCVM.Data [0];
	short rule = 0;
	rule |= (cvm_code & 0x3f);
	rule <<= 8;
	CVMResult[CVM_CODE] = (cvm_code & 0x3f); 
	CVMResult[CVM_COND] = 0x00; 
	CVMResult[CVM_RESULT] = 0xff;

	res = executeCVM(rule);
	// Set TSI to 'Cardholder verification was performed'
	EMV_Context::updateDataObject(0x9b, &dob_TSI, 1, 0x40);
	if (res == CVM_METHOD_NOT_RECOGNIZED)
	{
		// The current CVM rule is not supported by this implementation
		// EMV Book 3, chapter 6.5, page 51, or
		// VIS 1.4.0, ch 8.5.1, item 2.
		// Set 'Unrecognized CVM bit' to 1 in the TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x40);
	}
	
	// Default CVM is completed
	return res;
}

int CardholderVerification::checkCondition (short rule, int AmountX,
											int AmountY)
{
	int res = CVM_CONDITION_FAILED;
	switch (rule & 0x00ff)
	{
	case COND_ALWAYS:
		// For this condition always return SUCCESS
		res = SUCCESS;
		break;
	case COND_CASH:
		// Check if transaction type is cash or cashback
		res = checkTransType (true);
		break;
	case COND_NOTCASH:
		// Check if condition tyoe is not cash and is not cashback
		res = checkTransType (false);
		break;
	case COND_IF_SUPPORTED:
		// Check if condition is supported by the terminal
		res = checkIfSupported (rule);
		break;
	case COND_UNDER_X_AMOUNT:
		res = checkAmount(AmountX, LESS_THAN);
		break;
	case COND_OVER_X_AMOUNT:
		res = checkAmount(AmountX, MORE_THAN);
		break;
	case COND_UNDER_Y_AMOUNT:
		res = checkAmount(AmountY, LESS_THAN);
		break;
	case COND_OVER_Y_AMOUNT:
		res = checkAmount(AmountY, MORE_THAN);
		break;
	default:
		res = CVM_CONDITION_NOT_RECOGNIZED;
	}
	return res;
}

int CardholderVerification::executeCVM(short rule)
{
	int res;
	// If the rule is known - execute it
	switch (rule & 0x3f00)
	{
	case CVM_TYPE_FAIL: 
		// Fail CVM Processing
		// Set byte 3 of the CVM results to 'failed' (0x01)
		// (see EMB book 4, ch 2.3.4.5 and Annex A4)
		//updateCvmResult((byte)(CVM_TYPE_FAIL >> 8), (byte) rule, 0x01);
		//CVMResult[CVM_RESULT] = (byte)0x01; // Set to Failed
		return CVM_FORSED_FAILURE;
	case CVM_TYPE_PLAINTEXT_PIN_ICC:
		// Plaintext PIN verification performed by ICC
		if ((res = offlinePinICC(PIN_OFFLINE_PLAINTEXT)) == PIN_MATCH)
		{
			// Set byte 3 of the CVM results to 'successful' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC >> 8), 
			//	(byte) rule, 0x02);
			CVMResult[CVM_RESULT] = (byte)0x02; // Set to SUCCEEDED
			res = SUCCESS;
		}
		else if (res == PIN_NOT_MATCH || res == EXCEEDED_PIN_TRY_LIMIT)
		{
			// Set byte 3 of the CVM results to 'failed' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC >> 8), 
			//	(byte) rule, 0x01);
			res = CVM_FAILED;
		}
		return res;
	case CVM_TYPE_ENCIPH_PIN_ONLINE:
		// Enciphered PIN verification online
		return encipheredPinOnline();
	case CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN:
		// Plaintext PIN verification performed by ICC and Signature (paper
		if ((res = plaintextPinICC_Sign()) == SUCCESS)
		{
			// Set byte 3 of the CVM results to 'Unknown' (0x01)
			// (see EMB book 4, ch 2.3.4.4 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN >> 8), 
			//	(byte) rule, 0x00);
			CVMResult[CVM_RESULT] = (byte)0x00; // Set to Unknown
		}
		else if (res == PIN_NOT_MATCH || res == EXCEEDED_PIN_TRY_LIMIT)
		{
			// Set byte 3 of the CVM results to 'failed' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN >> 8), 
			//	(byte) rule, 0x01);
			res = CVM_FAILED;
		}
		return res;
	case CVM_TYPE_ENCIPH_PIN_ICC:
		// Enciphered PIN verification performed by ICC
		if ((res = offlinePinICC(PIN_OFFLINE_ENCIPHERED)) == PIN_MATCH)
		{
			// Set byte 3 of the CVM results to 'successful' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC >> 8), 
			//	(byte) rule, 0x02);
			CVMResult[CVM_RESULT] = (byte)0x02; // Set to SUCCEEDED
			res = SUCCESS;
		}
		else if (res == PIN_NOT_MATCH || res == EXCEEDED_PIN_TRY_LIMIT)
		{
			// Set byte 3 of the CVM results to 'failed' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC >> 8), 
			//	(byte) rule, 0x01);
			res = CVM_FAILED;
		}
		return res;
	case CVM_TYPE_ENCIPH_PIN_ICC_SIGN:
		// Enciphered PIN verification performed by ICC and signature (paper)
		if ((res = encipheredPinICC_Sign()) == SUCCESS)
		{
			// Set byte 3 of the CVM results to 'Unknown' (0x01)
			// (see EMB book 4, ch 2.3.4.4 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN >> 8), 
			//	(byte) rule, 0x00);
			CVMResult[CVM_RESULT] = (byte)0x00; // Set to Unknown
		}
		else if (res == PIN_NOT_MATCH || res == EXCEEDED_PIN_TRY_LIMIT)
		{
			// Set byte 3 of the CVM results to 'failed' (0x01)
			// (see EMB book 4, ch 2.3.4.5 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN >> 8), 
			//	(byte) rule, 0x01);
			res = CVM_FAILED;
		}
		return res;
	case CVM_TYPE_SIGN:
		// Signature (paper)
		if ((res = signature()) == SUCCESS)
		{
			// Set byte 3 of the CVM results to 'Unknown' (0x00)
			// (see EMB book 4, ch 2.3.4.4 and Annex A4)
			//updateCvmResult((byte)(CVM_TYPE_SIGN >> 8), (byte) rule, 0x00);
			CVMResult[CVM_RESULT] = (byte)0x00; // Set to Unknwn
		}
		return res;
	case CVM_TYPE_NO_CVM:
		// No CVM required
		if (checkIfSupported(CVM_TYPE_NO_CVM) != SUCCESS)
			return CVM_METHOD_NOT_SUPPORETED;
		// Set byte 3 of the CVM results to 'successful' (0x02)
		// (see EMB book 4, ch 2.3.4.5 and Annex A4)
		//updateCvmResult((byte)(CVM_TYPE_NO_CVM >> 8), (byte) rule, 0x02);
		CVMResult[CVM_RESULT] = (byte)0x02; // Set to Succeeded
		return SUCCESS;
	default:
		// CVM is not supported by this implementation
		return CVM_METHOD_NOT_RECOGNIZED;
	}
	return CVM_FAILED; // Should never come to this point
}

int CardholderVerification::checkTransType(bool cash)
{
	DataObject dob_transInfo;
	int res;

	// Get Transaction Info object (must be initialized in previous steps
	// along with setting Transaction Type element
	res = EnvContext.getTagValue (0x60000001, &dob_transInfo, false);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	if (cash)
	{
		if (check_bit(dob_transInfo.Data [0], 0x20) ||
			check_bit(dob_transInfo.Data [0], 0x02))
			return SUCCESS;
		else
			return CVM_CONDITION_FAILED;
	}
	else // (not cash)
	{
		if (!check_bit(dob_transInfo.Data [0], 0x20) &&
			!check_bit(dob_transInfo.Data [0], 0x02))
			return SUCCESS;
		else
			return CVM_CONDITION_FAILED;
	}
}

int CardholderVerification::checkIfSupported (short rule)
{
	int res;
	DataObject dob_TermCAP;

	// Get Terminal Capabilities data element from the hash
	res = EnvContext.getTagValue (0x9f33, &dob_TermCAP, false);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;
	byte CVM_Capability = dob_TermCAP.Data [1]; // 2nd byte in TerminalCapabilities data object
	switch (rule & 0x3f00)
	{
	case CVM_TYPE_FAIL: // Fail CVM Processing
		return SUCCESS;
	case CVM_TYPE_NO_CVM: // No CVM required
		return checkBit(CVM_Capability, 0x08);
	case CVM_TYPE_PLAINTEXT_PIN_ICC: // Plaintext PIN verification performed by ICC (offline)
		return checkBit(CVM_Capability, 0x80);
	case CVM_TYPE_ENCIPH_PIN_ONLINE: // Enciphered PIN verified online
		return checkBit(CVM_Capability, 0x40);
	case CVM_TYPE_SIGN: // Signature (paper)
		return checkBit(CVM_Capability, 0x20);
	case CVM_TYPE_ENCIPH_PIN_ICC: // Enciphered PIN verification performed by ICC (offline)
		return checkBit(CVM_Capability, 0x10);
	case CVM_TYPE_PLAINTEXT_PIN_ICC_SIGN:
		// Plaintext PIN verification performed by ICC (offline) AND
		// Signature (paper)
		if (checkBit(CVM_Capability, 0x80) == SUCCESS)
			return checkBit(CVM_Capability, 0x20);
		else
			return CVM_METHOD_NOT_SUPPORETED;
	case CVM_TYPE_ENCIPH_PIN_ICC_SIGN:
		// Enciphered PIN verification performed by ICC (offline) and Signature (paper)
		if (checkBit(CVM_Capability, 0x10) == SUCCESS)
			return checkBit(CVM_Capability, 0x20);
		else
			return CVM_METHOD_NOT_SUPPORETED;
	default:
		return CVM_METHOD_NOT_RECOGNIZED;
	}
	return CVM_METHOD_NOT_RECOGNIZED; // should never come to this point
}

int CardholderVerification::checkBit (const byte key, const byte mask)
{
	if (check_bit (key, mask))
		return SUCCESS;
	else
		return CVM_METHOD_NOT_SUPPORETED;
}

int CardholderVerification::checkAmount(int ThresholdAmount, 
										COMPARE_FLAG comp_flag)
{
	int res;
	DataObject dob_Amount;
	DataObject dob_transCurID;
	DataObject dob_applCurID;

	// Get Transaction currency code from the hash
	// It has to be initialized by a user in previous steps
	res = EnvContext.getTagValue (0x5f2A, &dob_transCurID, true);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	// Get Application Currency Code from the hash.
	// It must be read from the card in previous steps
	res = EnvContext.getTagValue (0x9f42, &dob_applCurID, true);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	if (dob_applCurID.len != 2 ||
		dob_transCurID.len != 2)
	{	
		return CVM_CONDITION_FAILED;
	}

	// Compare Transaction Currency Code and Application Currency Code
	if (!CompareByteArr (dob_transCurID.Data, dob_transCurID.len,
						 dob_applCurID.Data, dob_applCurID.len))
		return CVM_CONDITION_FAILED;

	// convert an integer Amount to a numeric format
	byte numTAmount[6];
	if (!binaryAmount2Numeric (ThresholdAmount, numTAmount, 6))
		return CVM_CONDITION_FAILED;

	// Get Amount from the hash (using Amount, Authorized data object, tag '9f02').
	// It has to be initialized by a user in previous steps
	res = EnvContext.getTagValue (0x9f02, &dob_Amount, true);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	if (dob_Amount.len != 6)
		return CVM_CONDITION_FAILED;
	
	// Compare Amounts
	for (int i = 0; i < dob_Amount.len; i++)
	{
		if (numTAmount[i] > dob_Amount.Data [i])
		{
			if (comp_flag == LESS_THAN)
				return SUCCESS;
			else
				return CVM_CONDITION_FAILED;
		}
		else if (numTAmount[i] < dob_Amount.Data [i])
		{
			if (comp_flag == MORE_THAN)
				return SUCCESS;
			else
				return CVM_CONDITION_FAILED;
		}
	}
	return CVM_CONDITION_FAILED;
}


// ---------------------------------------------------
// C a r d h o l d e r   V e r i f i c a t i o n
//
//  M e t h o d s   I m p l e m e n t a t i o n
// ---------------------------------------------------

// Plaintext PIN verification performed by ICC
int CardholderVerification::offlinePinICC(PIN_OFFLINE_TYPE offline_pin_type)
{
	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// Get a pointer to UI service
	UIControlImpl *pUI = (UIControlImpl*) EnvContext.GetService (CNTXT_UI);

	// Check if Offline PIN Processing is supported
	// (EMV book 3, ch 6.5.1 - first bullet; or
	//	VIS 1.4.0, ch 8.5.2.1 - first bullet)
	// ---------------------------------------------------------
	if ((offline_pin_type == PIN_OFFLINE_PLAINTEXT &&
		checkIfSupported(CVM_TYPE_PLAINTEXT_PIN_ICC) != SUCCESS) ||
		(offline_pin_type == PIN_OFFLINE_ENCIPHERED &&
		checkIfSupported(CVM_TYPE_ENCIPH_PIN_ICC) != SUCCESS))
	{
		// Set 'PIN Entry Required and PIN Pad not Present or not Working' to "1"
		// in TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x10);
		return CVM_METHOD_NOT_SUPPORETED;
	}

	// Initialize and open the PIN pad service
	PINControlImpl pinControl;
	AccessManager *pAM = EnvContext.getAccessManager();
	if ((res = pAM->open ((ServiceControl*)&pinControl)) != SUCCESS)
	{
		// Set 'PIN Entry Required and PIN Pad not Present or not Working' to "1"
		// in TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x10);
		return CVM_FAILED;
	}
	// ----------------------------------------------------------


	// Check the PIN Try Counter
	// -------------------------------------------
	byte tryCounter;
	
	if ((res = getPinCounter(&tryCounter)) == SUCCESS)
	{
		if (tryCounter == 0)
		{
			// No remaining PIN tries 
			// (VIS 1.4.0, ch 8.5.2.1, item 1.b)
			// Set 'PIN Try Limit Exceeded' to "1" in TVR
			EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x20);
			return EXCEEDED_PIN_TRY_LIMIT;
		}
		else if (tryCounter == 1)
		{
			// Last PIN try 
			// (VIS 1.4.0, ch 8.5.2.1, item 1.c)
			// Terminal should display "Last PIN Try" message and prompt
			// the user to enter PIN number
			pUI->setPrompt (Language::getString
				(MSG_ID_LAST_PIN_TRY, EMV_LANG_LATIN1));
		}
	}
	
	// ----------------------------------------------------------------

	
	byte pin[MAX_PIN_LENGTH];
	UNINT pin_size;
	
	// Loop until PIN is not verified and PIN TRY Counter is not equal to 0.
	while (true)
	{
		// Promt the user to enter a PIN number
		pUI->setPrompt (Language::getString (MSG_ID__ENTER_PIN, EMV_LANG_LATIN1),
			EMV_LANG_LATIN1);
		// --------------------------------------
		pin_size = MAX_PIN_LENGTH;
		if ((res = pinControl.getPIN(pin, &pin_size)) != SUCCESS)
		{
			// a user decided to bypass PIN entry
			// (EMV book 3, ch 6.5.2, 3rd bullet, or
			// VIS 1.4.0, ch 8.5.2.1)
			// Set 'PIN entry required, PIN Pad Present, but PIN was not entered'
			// bit to "1" in TVR
			EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x08);
			res = CVM_FAILED;
			break;
		}
		// Send PIN to the card for verification
		if ((res = verifyPIN (offline_pin_type, pin, pin_size, &tryCounter)) 
						== SUCCESS)
		{
			// PIN verified Successfully
			// Pause for a 3 seconds to give a user a chance to see the result
			UIOperationEventImpl uiOE;
			pUI->addOperationEvent (&uiOE);
			res = pUI->getResponse (Language::getString (MSG_ID__PIN_OK, EMV_LANG_LATIN1),
				3000, EMV_LANG_LATIN1);
			if (res != SUCCESS)
			{
				pUI->writeStatus (Language::getString (MSG_ID__PIN_OK, EMV_LANG_LATIN1),
				true, EMV_LANG_LATIN1);
			}
			res = PIN_MATCH;
			break;
		}
		else if (res == EXCEEDED_PIN_TRY_LIMIT)
		{
			// (VIS 1.4.0, ch 8.5.2.1, item 3.c)
			// Set 'PIN Try Limit Exceeded' bit to "1" in TVR
			EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x20);
			res = EXCEEDED_PIN_TRY_LIMIT;
			break;
		}
		else if (res == PIN_NOT_MATCH)
		{
			// Display 'Incorrect PIN' message
			pUI->writeStatus (Language::getString 
				(MSG_ID__INCORRECT_PIN, EMV_LANG_LATIN1), 
				true, EMV_LANG_LATIN1);

			if (tryCounter == 0xff)
			{
				// A PIN number with invalid length has been entered
				pUI->writeStatus ("  Invalid PIN length",
					true, EMV_LANG_LATIN1);
			}
			else if (tryCounter == 0)
			{
				// No remaining PIN tries 
				// (VIS 1.4.0, ch 8.5.2.1, item 3.d)
				// Set 'PIN Try Limit Exceeded' to "1" in TVR
				EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x20);
				break;
			}
			else if (tryCounter == 1)
			{
				// Display the VISA's proprietary message "Last PIN Try"
				pUI->writeStatus (Language::getString
					(MSG_ID_LAST_PIN_TRY, EMV_LANG_LATIN1),
					true, EMV_LANG_LATIN1);
			}
		}
		else
		{
			// Some runtime error, exit this transaction without updating anything
			break;
		}
	} // End While loop

	pUI->setPrompt ("Processing...", EMV_LANG_LATIN1);
	return res;
}

// Enciphered PIN verification online
int CardholderVerification::encipheredPinOnline()
{
	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	if ((res = checkIfSupported(CVM_TYPE_ENCIPH_PIN_ONLINE))
		!= SUCCESS)
	{
		// Set 'PIN Entry Required and PIN Pad not Present or not Working' to "1"
		// in TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x10);
		return res;
	}

	// --------------------------------------------
	// Provide implementation of this method here
	// --------------------------------------------
	// . . . .

	// Set 'PIN Entry Required and PIN Pad not Present or not Working' to "1"
	// in TVR
	EMV_Context::updateDataObject(0x95, &dob_TVR, 3, 0x10);
	return CVM_METHOD_NOT_SUPPORETED;
}

// Plaintext PIN verification performed by ICC and Signature (paper)
int CardholderVerification::plaintextPinICC_Sign()
{
	int res;

	if ((res = offlinePinICC(PIN_OFFLINE_PLAINTEXT)) == PIN_MATCH)
		res = signature();

	return res;
	
}


// Enciphered PIN verification performed by ICC and signature (paper)
int CardholderVerification::encipheredPinICC_Sign()
{
	int res;
	
	if ((res = offlinePinICC(PIN_OFFLINE_ENCIPHERED)) == PIN_MATCH)
		res = signature();
	

	return res;
}

// Signature (paper)
int CardholderVerification::signature()
{
	// Check if Signature is supported by a terminal
	if (checkIfSupported(CVM_TYPE_SIGN) == SUCCESS)
	{
		// Update Transaction Results to indicate that signature is required
		EMV_Context::updateDataObject (0x50000004, 1, 0x20, true);
		return SUCCESS;
	}
	else
		return CVM_METHOD_NOT_SUPPORETED;
}

// ----------------------------------------------------------
//
// H e l p e r    F u n c t i o n s
//
//-----------------------------------------------------------

bool CardholderVerification::IsOfflineSupported()
{
	if (checkIfSupported(CVM_TYPE_PLAINTEXT_PIN_ICC) == SUCCESS ||
		checkIfSupported(CVM_TYPE_ENCIPH_PIN_ICC) == SUCCESS)
		return true;
	else
		return false;
}

int CardholderVerification::getPinCounter (byte *tryCounter)
{
	int res;
	short TryCounterTag = (short)0x9f17;
	*tryCounter = -1;
	// Get a pointer to Smart Card Reader service
	SCRControlImpl *pSCR = (SCRControlImpl*)EnvContext.GetService (CNTXT_SCR);

	// Set APDU command to send to the card
	scr_command command;
	command.setReader (pSCR);
	if ((res = command.setGetData(TryCounterTag)) != SUCCESS)
		return res;

	// Send the command to the card
	R_APDU rapdu;
	if ((res = command.run (&rapdu, TransactionToken)) != SUCCESS)
		return res;

	if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
	{
		// The value of the Try Counter is successfully retreived,
		// Get Data returned by the card
		byte *data = rapdu.copyData ();
		if (!data)
			return ERR_MEMORY_ALLOC;

		// Now try to parse this data
		tlv_parser tlv_data;
		if ((res = tlv_data.parse (data, rapdu.getDataLen ()))
			!= SUCCESS)
		{
			// cannot parse data returned by the ICC
			delete [] data;
			return EMV_INVALID_FORMAT;
		}

		// Check if returned data has the correct tag value
		if ((short)(tlv_data.GetRoot ()->GetTagVal ()) != TryCounterTag)
		{
			delete [] data;
			return EMV_INVALID_FORMAT;
		}

		// Check the length of the returned data (must be 1)
		if (tlv_data.GetRoot ()->GetLengthVal() != 1)
		{
			delete [] data;
			return EMV_INVALID_FORMAT;
		}

		// Retreive the value of the Try Counter
		*tryCounter = tlv_data.GetRoot ()->GetValue()[0];
		delete [] data;
		return SUCCESS;
	}
	else // Failed to retreive a PIN Try Counter
	{
		// VIS 1.4.0, ch 8.5.2.1, item 1.a
		return ERR_CMD_INVALID_ICC_RESPONSE;
		/*
		// This portion of code is consistent with EMV spec, however, the 
		// following is explanation why the check for "transaction termination"
		// condition is comented out here.
		// EMV is confusing on this issue.  Book 3 Section 4.1 says 'Unless otherwise 
		// specified ...' so this includes Table I - 5 and any other actions 
		// described in the spec.  Book 3 Section 6.6.3 second paragraph says 
		// when describing the GET DATA for the ATC and Last Online ATC Register 
		// says "If either of the required data ojbects are not returned by 
		// the ICC ... ', terminal velocity checking shall end so this section 
		// does not require terminating the transaction.  The wording in 
		// Book 4 Section 2.3.4.1 seems to indicate that the return code must be 
		// either 6A81 or 6A88.  However, this is an optional function for 
		// both the card and terminal that is not critical to risk analysis 
		// and should not cause a transaction termination if it fails.  
		// Therefore, code the terminal according to the test script. 
		if ((rapdu.getSW1 () == 0x6A && rapdu.getSW2 () == 0x81) ||
			(rapdu.getSW1 () == 0x6A && rapdu.getSW2 () == 0x88))
		{
			// Valid response codes according to EMV book 3, table I-5)
			return SUCCESS;
		}
		else
		{
			// Invalid response from the card
			return ERR_CMD_INVALID_ICC_RESPONSE;
		}
		*/
	}
}

int CardholderVerification::verifyPIN (PIN_OFFLINE_TYPE offline_pin_type,
									   const byte pin[], UNINT pin_size, 
									   byte *tryCounter)
{
	int res;
	
	// Check if PIN number has a valid length
	if (pin_size < MIN_PIN_LENGTH || pin_size > MAX_PIN_LENGTH)
	{
		*tryCounter = 0xff;
		return PIN_NOT_MATCH; 
	}

	// Get a pointer to Smart Card Reader service
	SCRControlImpl *pSCR = (SCRControlImpl*)EnvContext.GetService (CNTXT_SCR);

	//Create a Plaintext PIN block
	const int block_size = MAX_PIN_LENGTH/2 + 2;
	byte pin_block [block_size];
	// Create a Plaintext PIN block
	res = createPlaintextBlock(pin, pin_size, pin_block, block_size);
	if (res != SUCCESS)
	{
		// Failed to create a pin block for sending PIN to the card.
		// Consider this as fatal error and exit the transaction
		return res;
	}
	byte *enciph_pin = 0;
	UNINT enciph_pin_len = 0;
	if (offline_pin_type == PIN_OFFLINE_ENCIPHERED)
	{
		// Create Enciphered PIN block
		res = EncipherPin(pin_block, block_size, 
						   &enciph_pin, &enciph_pin_len);
	}
	if (res != SUCCESS)
	{
		// Failed to create a pin block for sending PIN to the card.
		// Consider this as fatal error and exit the transaction
		return res;
	}

	// Set APDU command to send to the card
	scr_command command;
	command.setReader (pSCR);
	if (offline_pin_type == PIN_OFFLINE_PLAINTEXT)
        res = command.setVerifyPlaintext(pin_block, block_size);
	else // if (offline_pin_type == PIN_OFFLINE_ENCIPHERED)
	{
		res = command.setVerifyEnciphered(enciph_pin, enciph_pin_len);
		delete [] enciph_pin;
	}
	
	if (res != SUCCESS)
		return res;

	// Send the Verify command to the card
	R_APDU rapdu;
	if ((res = command.run (&rapdu, TransactionToken)) != SUCCESS)
		return res;

	if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
	{
		// The PIN is successfully verified
		// Update Context by adding a data object with tag 0x99 --
		// Transaction Personal Identification Number (PIN) Data
		/*DataObject dob_pin;
		if (dob_pin.set (pin_block, block_size, CNFG_TRANSACTION, "b") == SUCCESS)
			EnvContext.setTagValue(0x99,&dob_pin, IO_CREATE | IO_UPDATE);
		*/
		return SUCCESS;
	}
	else if ((rapdu.getSW1 () == 0x69 && rapdu.getSW2 () == 0x83) ||
			 (rapdu.getSW1 () == 0x69 && rapdu.getSW2 () == 0x84))
	{
		// VIS 1.4.0, ch 8.5.2.1, item 3.c -
		// PIN Try Limit Exceeded on Previous Transaction
		return EXCEEDED_PIN_TRY_LIMIT;
	}
	else if (rapdu.getSW1 () == 0x63 && check_bit(rapdu.getSW2 (),0xC0))
	{
		// VIS 1.4.0 ch 8.5.2.1, item 3.d - 
		// PIN does not match
		*tryCounter = (rapdu.getSW2() & 0x0f);
		return PIN_NOT_MATCH;
	}
	else
	{
		// undefined error returned from the card
		return ERR_CMD_INVALID_ICC_RESPONSE;
	}
}

// Format a plaintext offline PIN block (book 3, ch 2.5.12.2)
int CardholderVerification::createPlaintextBlock(const byte plaintextPIN[], 
												 const int size, 
												 byte pin_block[], 
												 const int block_size)
{
	// C control field == '0010'
	pin_block[0] = 0x02;
	pin_block[0] <<= 4;

	// N PIN length
	if (size < 0 || size > ((block_size - 2) * 2))
		return ERR_INVALID_PIN_LENGTH;
	pin_block[0] = size | (pin_block[0] & 0xf0);
	
	// Write PIN digits
	return asciStr2HexString ((const char *)plaintextPIN, (UNINT)size,
					   pin_block + 1, block_size - 1, 0xff, true);
}

void CardholderVerification::updateCvmResult(byte cvm_code, 
											 byte cvm_condition, 
											 byte cvm_result)
{
	dob_cvmRes.Data[0] = cvm_code; //CVM performed
	dob_cvmRes.Data[1] = cvm_condition; //CVM condition
	dob_cvmRes.Data[2] = cvm_result; //CVM result
	EnvContext.setTagValue (0x9f34, &dob_cvmRes, IO_CREATE | IO_UPDATE);
}


// Shift byte array of size 'size' to the right number of positions in 'adjustment'.
// Each position is 4 bits.
void CardholderVerification::shiftAmount (byte Amount[], int size, 
										  int adjustment)
{
	int step;
	if (adjustment % 2 == 0)
	{
		// even
		step = adjustment / 2;
		for (int i = size - step - 1; i >= 0; i--)
			Amount[i + step] = Amount[i];
		for (int i = 0; i < step; i++)
			Amount[i] = 0x00;
	}
	else
	{
		// odd
		step = adjustment / 2;
		byte temp = 0x00;
		for (int i = size - step - 1; i >= 0; i--)
		{
			Amount[i + step] = Amount[i];
			temp = Amount[i + step];
			temp <<= 4;

			Amount[i + step] >>= 4;
			Amount[i + step] &= 0x0f;

			if (i < size - 1 - step)
				Amount[i+step+1] |= temp;
		}
		for (int i = 0; i < step; i++)
			Amount[i] = 0x00;
	}
}


// Format an enciphered offline PIN block (book 2, ch 7)
int CardholderVerification::EncipherPin(const byte pin_block[], 
										const int block_size, 
										byte **enciph_pin, 
										UNINT *enciph_pin_len)
{
	int res;

	// Get reference to Crypto Service
	CryptoControlImpl *Crypto =
		(CryptoControlImpl*)EnvContext.GetService (CNTXT_CRYPTO);

	CryptoOperationEventImpl opEvent;

	// 1. Get Public Key to be used in encipherement
	DataObject dob_IccPKCert;
	DataObject dob_IccPKrem;
	ODA_KEY_INFO IccKeyInfo;
	bool bEncipheredCert;

	// 1.1 Initialize Public key (it can be either ICC PK or ICC Enciphered PK)
	res = InitPubKey(&bEncipheredCert, 
				     &dob_IccPKCert, &dob_IccPKrem, &IccKeyInfo);
	if (res != SUCCESS)
		return CVM_FAILED;

	// 1.2 retreive ICC public key
	res = retreiveIccPK(Crypto, bEncipheredCert, &dob_IccPKCert, 
					    &dob_IccPKrem, &IccKeyInfo);
	if (res != SUCCESS)
		return CVM_FAILED;

	// 2. Get Unpredictable number from the ICC
	const int UnpredLen = 8;
	byte UnpredNumber [UnpredLen];

	res = getUnpredictableNumber(UnpredNumber, &UnpredLen);
	if (res != SUCCESS)
	{
		delete [] IccKeyInfo.KeyModulus;
		return res;
	}

	// 3. Generate a Random Pad pattern consisting of N - 17 bytes,
	// where N is the length in bytes of the public key to be used for PIN
	// encipherement.
	byte *randPattern = 0;
	int randLen = 0;
	res = getRandomPattern (Crypto, &randPattern, &randLen, IccKeyInfo.KeyLength); 
	if (res != SUCCESS)
	{
		delete [] IccKeyInfo.KeyModulus;
		return res;
	}

	// 4. Concatinate data to be enciphered (see emv book 2, ch 7.2, table 21).
	byte *plaintextData = new byte [IccKeyInfo.KeyLength];
	if (!plaintextData)
	{
		delete [] randPattern;
		delete [] IccKeyInfo.KeyModulus;
		return ERR_MEMORY_ALLOC;
	}
	plaintextData[0] = 0x7F; // Data Header
	// Copy PIN block
	memcpy (plaintextData + 1, pin_block, block_size);
	// Add ICC Unpredicatble Number
	memcpy (plaintextData + 1 + block_size, UnpredNumber, UnpredLen);
	// Add Random Pad Pattern 
	memcpy (plaintextData + 1 + block_size + UnpredLen, randPattern, randLen);

	// Release Random Pad Pattern buffer
	delete [] randPattern;

	// 5. Encipher the PIN
	res = encipherPinBlock (Crypto, &IccKeyInfo, plaintextData, 
							IccKeyInfo.KeyLength,
							enciph_pin, enciph_pin_len);
	
	// Relese allocated memory 
	delete [] plaintextData;
	delete [] IccKeyInfo.KeyModulus;
	return res;
}

int CardholderVerification::InitPubKey(bool *bEncipheredCert,
									   DataObject *pdob_IccPKCert, 
									   DataObject *pdob_IccPKrem, 
									   ODA_KEY_INFO *IccKeyInfo)
{
	int res;
	
	// Get the ICC Enciphered PIN PK Certificate
	if ((res = EnvContext.getTagValue (0x9f2d, pdob_IccPKCert, true)) == SUCCESS)
	{
		// Get the ICC Enciphered PIN PK Exponent
		res = EnvContext.getTagValue (0x9f2e, 
			&(IccKeyInfo->dob_KeyExponent), true);
		if (res != SUCCESS)
			return CVM_FAILED;

		// Get the ICC Enciphered PIN PK reminder
		if (EnvContext.getTagValue (0x9f2f, pdob_IccPKrem, true) != SUCCESS)
			pdob_IccPKrem->reset ();
		*bEncipheredCert = true;
	}
	else
	{
		// The ICC Enciphered PIN PK Certificate is not present in the ICC.
		// Try to use the ICC  PK Certificate (used for dynamic data auth.).
		if ((res = EnvContext.getTagValue (0x9f46, pdob_IccPKCert, true)) 
			== SUCCESS)
		{
			// Get the ICC PK Exponent
			res = EnvContext.getTagValue (0x9f47, 
				&(IccKeyInfo->dob_KeyExponent), true);
			if (res != SUCCESS)
				return CVM_FAILED;

			// Get the ICC Enciphered PIN PK reminder
			if (EnvContext.getTagValue (0x9f48, pdob_IccPKrem, true) != SUCCESS)
				pdob_IccPKrem->reset ();

			*bEncipheredCert = false;
		}
		else
		{
			// Neither the ICC Enciphered PK Certificate nor 
			// the ICC PK Certificate are found. Fail CVM processing.
			// (see VIS 1.4.0, ch 8.5.2.2, Figure 8-4).
			return CVM_FAILED;
		}
	}
	return SUCCESS;
}

int CardholderVerification::retreiveIccPK(CryptoControlImpl *Crypto,
										  bool bEncipheredCert,
										  DataObject *pdob_IccPKCert, 
										  DataObject *pdob_IccPKrem, 
										  ODA_KEY_INFO *IccKeyInfo)
{
	int res;
	byte bCAPKI;
	OfflineDataAuthentication oda;
	unsigned int CAPK_modulus;

	// 1.Retrieve the Certification Authority Public Key stored on the terminal
	if ((res = oda.InitCertAuthPubKey (Crypto, &CAPK_modulus, &bCAPKI)) != SUCCESS)
	{
		if (res != SUCCESS)
			return res;
	}

	// 2. Retreive Issuer Public Key
	ODA_KEY_INFO IssuerKeyInfo;
	res = oda.retrieveIssuerPubKey(Crypto, CAPK_modulus, bCAPKI, &IssuerKeyInfo);
	if (res != SUCCESS)
	{
		return res;
	}

	// 3. Retreive ICC Public Key
	if (bEncipheredCert)
	{
		res = oda.retreiveIccPubKey(Crypto,
							NULL, 0, // Do not use static data for enciphered certificate
							&IssuerKeyInfo,
							pdob_IccPKCert,
							pdob_IccPKrem,
							IccKeyInfo);
	}
	else
	{
		res = oda.retreiveIccPubKey(Crypto,
							ODA_list, ODA_len,
							&IssuerKeyInfo,
							pdob_IccPKCert,
							pdob_IccPKrem,
							IccKeyInfo);
	}

	delete [] IssuerKeyInfo.KeyModulus;
	return res;
}

int CardholderVerification::getUnpredictableNumber(byte UnpredNumber[], 
												   const int *UnpredLen)
{
	int res;

	// Get a pointer to the card reader service
	SCRControlImpl *pSCR = (SCRControlImpl*) EnvContext.GetService(CNTXT_SCR);
	if (!pSCR)
		return ERR_SERVICE_NOT_CONNECTED;

	// Set APDU command to send to the card
	scr_command command;
	command.setReader (pSCR);
	if ((res = command.setGetChallenge ()) != SUCCESS)
		return res;

	// Send the GetData command to the card
	R_APDU rapdu;
	if ((res = command.run (&rapdu, EMV_Context::TransactionToken)) != SUCCESS)
		return res;

	if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
	{
		// The Data is successfully retreived
		if (rapdu.getDataLen() != *UnpredLen)
			return ERR_INVALID_ICC_DATA;
		
		memcpy (UnpredNumber, rapdu.getData (), *UnpredLen);
		return SUCCESS;
	}
	else
		return ERR_CMD_INVALID_ICC_RESPONSE;
}

// Generate a Random Pad pattern consisting of N - 17 bytes,
// where N is the length in bytes of the public key to be used for PIN
// encipherement.
int CardholderVerification::getRandomPattern (CryptoControlImpl *Crypto,
											  byte **randPattern, 
											  int *randLen, 
											  UNINT KeyLength)
{
	int size = KeyLength - 17;
	if (size <= 0)
		return CVM_FAILED;

	CryptoOperationEventImpl opEvent;
	int res;

	// Attach Operation event
	if ((res = Crypto->addOperationEvent(&opEvent)) != SUCCESS)
		return res;

	// Calculate a random number
	res = Crypto->randomNumber(Crypto->getCryptoAlgID(), size);
	Crypto->removeEvent();

	if (res != SUCCESS)
		return opEvent.getError();

	// Get the length in bytes of the resulting random value
	int len = opEvent.getLength();
	if (len != size)
		return ERR_UNEXPECTED_TYPE;

	// Extract a random number from the event object
	byte *btVal;
	opEvent.getByteString(&btVal);

	// save it to the return parameter
	*randPattern = new byte [size];
	if (!(*randPattern))
		return ERR_MEMORY_ALLOC;
	
	memcpy (*randPattern, btVal, size);
	*randLen = size;

	return SUCCESS;
}

// Apply RSA Recover algorithm to encipher a PIN block
int CardholderVerification::encipherPinBlock (CryptoControlImpl *Crypto, 
											  ODA_KEY_INFO *IccKeyInfo,
											  byte *plaintextData, 
											  int data_len,
											  byte **enciph_pin, 
											  UNINT *enciph_pin_len)
{
	int res;

	// Initialize Key
	res = Crypto->initKey (IccKeyInfo->KeyModulus, 
						   IccKeyInfo->KeyLength, 
						   IccKeyInfo->dob_KeyExponent.Data,
						   IccKeyInfo->dob_KeyExponent.len,
						   IccKeyInfo->uiCryptoAlgID, 
						   IccKeyInfo->uiHashAlgID);
	if (res != SUCCESS)
		return CVM_FAILED;

	CryptoOperationEventImpl opEvent;
	Crypto->addOperationEvent(&opEvent);

	res = Crypto->encrypt(plaintextData, data_len);
	Crypto->removeEvent();
	if (res != SUCCESS)
	{
		// Encryption error, terminate the transaction
		return CVM_FAILED;
	}

	// Decryption succeeded; retreive the recovered data
	if (opEvent.getValueType() != OPEVENT_BINARY)
		return ERR_UNEXPECTED_TYPE;

	*enciph_pin_len = opEvent.getLength ();
	if (*enciph_pin_len > 0)
	{
		byte *data = 0;
		if ((res = opEvent.getByteString (&data)) == SUCCESS)
		{
			*enciph_pin = new byte [*enciph_pin_len];
			if (!(*enciph_pin_len))
				return ERR_MEMORY_ALLOC;
			memcpy (*enciph_pin, data, *enciph_pin_len);
			return SUCCESS;
		}
		else
			return res;
	}	
	else
		return CVM_FAILED;
}
