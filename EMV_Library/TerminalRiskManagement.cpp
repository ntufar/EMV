#include <stdio.h>
#include "TerminalRiskManagement.h"

TerminalRiskManagement::TerminalRiskManagement(void)
{
}

TerminalRiskManagement::~TerminalRiskManagement(void)
{
}

int TerminalRiskManagement::initData()
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

	// Transaction Status Information
	i++;
	tags[i] = 0x9b; 
	dob[i] = &dob_TSI;
	hashOnly[i] = true;
	mandatory[i] = true;

	return EMV_Context::initData (tags, dob, hashOnly, mandatory, size);
}

// Check if the currently selected application is in Exception File.
// Source: EMV Version 4.0, book 4, ch 2.3.5; 
// The 'Application Primary Account Number' (PAN), tag 5A data object must be 
// read from the file in previous steps.
// The Application PAN Sequence number (tag 5f34) is optional, and if exists then
// it must be read from the card in previous steps.
//
// Note: The Exception file is not supported in this release
int TerminalRiskManagement::checkExceptionFile()
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

	// Read PAN and PAN sequence number from the context
	DataObject dob_pan;
	DataObject dob_pan_seq;

	if ((res = EnvContext.getTagValue(0x5a, &dob_pan, true)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	byte *seq = 0;
	int seq_len = 0;
	if ((res = EnvContext.getTagValue(0x5f34, &dob_pan_seq, true)) == SUCCESS)
	{
		if (dob_pan_seq.len > 0)
		{
			seq = dob_pan_seq.Data;
			seq_len = dob_pan_seq.len;
		}
	}
	
	if (IsApplInExceptionFile(dob_pan.Data, dob_pan.len, seq, seq_len))
	{
		// Set the 'Card appears in exception file' bit to '1' in the TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 1, 0x10);
	}
	return SUCCESS;
}


// Performs Floor Limits checking as a part of Terminal Risk Management.
// Source: EMV Version 4.0, book 3, ch 6.6.1; VIS 1.4.0, ch 9.6.
// The following data objects required for this phase must be stored on the terminal
// with the following tags:
//   Terminal Floor Limit:                           Tag '9F1B'
//
// The 'Amount, Aiuthorized' data object (tag '9F02') must be initiolized prior to
// using this function.
//
// The Exception file and Transaction Log file are not supported in this release

int TerminalRiskManagement::floorLimit()
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

	if (!IsOfflineTerminal())
	{
		// Floor Limit checking has sense only for the terminals with offline 
		// capabilities. If the terminal is only online, then do nothing.
		return SUCCESS;
	}


	// Obtain Terminal Floor Limit Data Object
	DataObject dob_Floor;
	if ((res = EnvContext.getTagValue(0x9f1b, &dob_Floor, false)) != SUCCESS)
	{
		// Missing mandatory data -- exit the transaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_Floor.len != 4)
	{
		// invalid data
		return ERR_BAD_ARGUMENT;
	}

	// Obtain Amount,Authorized data object -- it must be initialized
	// in previous steps
	DataObject dob_Amount;
	if ((res = EnvContext.getTagValue(0x9f02, &dob_Amount, true)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_Amount.len != 6)
	{
		// Invalid data
		return ERR_BAD_ARGUMENT;
	}

	// Check if log file exists
	if (IsTransLogExist())
	{
		// Find a record for the current PAN and add amount to the Amount authorized
		// for this transaction
	}

	byte numFloor[6];
	// Convert Floor value from binary to a numeric value
	res = Binary2Numeric(dob_Floor.Data, dob_Floor.len, numFloor, 6);
	if (memcmp(dob_Amount.Data, numFloor, 6) >= 0)
	{
		// Set the 'Transaction Exceeds Floor Limit' bit to '1' in the TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x80);
	}
	return SUCCESS;
}

int TerminalRiskManagement::IsFloorExceeded()
{
	if (!dob_TVR.Data )
		return -1; // Not available
	if (check_bit(dob_TVR.Data [3], 0x80))
		return 0; // bit is set -- floor limit is exceeded!
	else
		return 1; // bit is not set
}

// Performs Random Transaction Selection as a part of Terminal Risk Management.
// Source: EMV Version 4.0, book 3, ch 6.6.2; VIS 1.4.0, ch. 9.7
// The following data objects required for this phase must be stored on the terminal
// with the following tags:
//   Terminal Floor Limit:                           Tag '9F1B'
//   Threshold Value for Biased Random Selection:    Tag '40000004'
//   Target Percentage to be used for Random 
//                               Selection (0 - 99): Tag '40000005'
//   Maximum Target Percentage to be used for Biased Random 
//                               Selection (0 - 99): Tag '40000006'
//
// The 'Amount, Aiuthorized' data object (tag '9F02') must be initiolized prior to
// using this function.
//
// The 'Threshold Value for Biased Random Selection' value must be stored in the same
// format as transaction Amount, which is numeric 6-byte value

int TerminalRiskManagement::randomTransactionSelection()
{
	// 1. Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// 2. Check the terminal type
	if (!(IsOfflineTerminal() && IsOnlineTerminal()))
	{
		// Random Transaction Selection checking has sense only for the terminals with 
		// both offline and online capabilities. 
		// Since we are here, it means that a terminal is either online only or offline only.
		// Therefore don't do anything
		return SUCCESS;
	}

	// 3. Read data objects required for the Random Transaction Selection procedure:

	// 3.1 Obtain Amount,Authorized data object -- it must be initialized
	// in previous steps
	DataObject dob_Amount;
	if ((res = EnvContext.getTagValue(0x9f02, &dob_Amount, true)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_Amount.len != 6)
	{
		// Invalid data
		return ERR_BAD_ARGUMENT;
	}

	// 3.2 Obtain Terminal Floor Limit Data Object
	DataObject dob_Floor;
	if ((res = EnvContext.getTagValue(0x9f1b, &dob_Floor, false)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_Floor.len != 4)
	{
		// invalid data
		return ERR_BAD_ARGUMENT;
	}

	// 3.3 Obtain Threshold for Biased Random Selection Data Object
	DataObject dob_threshRand;
	if ((res = EnvContext.getTagValue(0x40000004, &dob_threshRand, false)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_threshRand.len != 6)
	{
		// invalid data
		return ERR_UNEXPECTED_TYPE;
	}
	
	// 3.4 Obtain Target percentage for Random Selection Data Object
	DataObject dob_target;
	if ((res = EnvContext.getTagValue(0x40000005, &dob_target, false)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_target.len != 1)
		return ERR_UNEXPECTED_TYPE;
	else if (dob_target.Data [0] < 0 || dob_target.Data[0] > 99)
	{
		// Condition according to EMV 4.0, Book 3, ch 6.6.2, bullet 1 
		return ERR_INVALID_TERMINAL_DATA; 
	}

	// 3.5 Obtain Maximum Target percentage for Biased Random Selection Data Object
	DataObject dob_maxtarget;
	if ((res = EnvContext.getTagValue(0x40000006, &dob_maxtarget, false)) != SUCCESS)
	{
		// Missing mandatory data -- exit the ttransaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	else if (dob_maxtarget.len != 1)
		return ERR_UNEXPECTED_TYPE;
	else if (dob_maxtarget.Data [0] < 0 || dob_maxtarget.Data[0] > 99 ||
		dob_maxtarget.Data[0] < dob_target.Data [0])
	{
		// Condition according to EMV 4.0, Book 3, ch 6.6.2, bullet 3 
		return ERR_INVALID_TERMINAL_DATA; 
	}

	// 4. Calculate a random number in a range from 1 to 99
	byte randNum;
	if ((res = GenerateRandomNumber(&randNum)) != SUCCESS)
		return res;
	// Output the value of random number, so 2CJ.081.02 & 2CJ.082.04 
	// can be verified
	UIControlImpl *pUI = (UIControlImpl*)EMV_Context::EnvContext.GetService (CNTXT_UI);
	if (pUI && pUI->opened ())
	{
		char temp_char[32];
		sprintf (temp_char, "TRM - Random Number = %d", randNum);
		pUI->writeStatus (temp_char);
	}
	// 5. Check Transaction Amount and  the Threshold Value for Biased Random Selection
	
	if (memcmp(dob_Amount.Data, dob_threshRand.Data, 6) < 0)
	{
		// Transaction amount is less than Threshold value.
		// Randomly select transaction for online processing
		if (randNum <= dob_target.Data[0])
		{
			// Set the 'Transaction selected randomly for online processing' bit to '1'
			// in TVR (byte 4, bit 5)
			EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x10);
		}
	}
	else // Transaction amount is greater than or eqaul to Threshold value
	{
		// Convert Floor value from binary to a numeric value
		byte numFloor [6];
		res = Binary2Numeric(dob_Floor.Data, dob_Floor.len, numFloor, 6);

		if (memcmp(dob_Amount.Data, numFloor, 6) < 0)
		{
			// Amount is less than floor value.
			// ----  Selection with bias -------
			byte TransactionTarget;
			res = calcTransactionTargetPercent(dob_Amount.Data,
								 dob_threshRand.Data,
								 numFloor,
								 dob_target.Data[0],
								 dob_maxtarget.Data [0],
								 &TransactionTarget);
			if (res != SUCCESS)
				return res;
			else if (randNum <= TransactionTarget)
			{
				// Select a transaction for online processing:
				// Set the 'Transaction selected randomly for online processing' bit to '1'
				// in TVR (byte 4, bit 5)
				EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x10);
			}
		}
		else // Amount is greater than or equal to the Floor Limit value
		{
			// Do Nothing
			return SUCCESS;
		}
	}
	return SUCCESS;
}

// Performs Velocity Checking as a part of Terminal Risk Management.
// Source: EMV Version 4.0, book 3, ch 6.6.3; VIS 1.4.0, ch. 9.8
// The following data objects required for this phase must be stored on the terminal
// with the following tags:
//   Terminal Floor Limit:                           Tag '9F1B'
//   Threshold Value for Biased Random Selection:    Tag '40000004'
//   Target Percentage to be used for Random 
//                               Selection (0 - 99): Tag '40000005'
//   Maximum Target Percentage to be used for Biased Random 
//                               Selection (0 - 99): Tag '40000006'
//
// The 'Amount, Aiuthorized' data object (tag '9F02') must be initiolized prior to
// using this function.
//
// The 'Threshold Value for Biased Random Selection' value must be stored in the same
// format as transaction Amount, which is numeric 6-byte value

int TerminalRiskManagement::velocityChecking()
{
	// 1. Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// 2. Check the terminal type
	if (!IsOfflineTerminal())
	{
		// Velocity Checking has sense only for the offline capabale terminals 
		// Since we are here, it means that a terminal is online only.
		// Therefore don't do anything
		return SUCCESS;
	}

	// 4. Check if both the Lower Consecutive Offline Limit ('9F14') and Upper
	// Consecuitive Offline Limit ('9F23') exist (have been read from the ICC in
	// previous steps):
	DataObject dob_limit_lo;
	if ((res = EnvContext.getTagValue(0x9f14, &dob_limit_lo, true)) != SUCCESS)
	{
		// This data element is not present -- skip Velocity Checking..
		return SUCCESS;
	}
	DataObject dob_limit_hi;
	if ((res = EnvContext.getTagValue(0x9f23, &dob_limit_hi, true)) != SUCCESS)
	{
		// This data element is not present -- skip Velocity Checking..
		return SUCCESS;
	}

	// 5. Read Application Transaction Counter (ATC), tag 0x9f36, and Last online ATC
	// Register, tag 0x9f13, from the card:
	int atc;
	int last_atc;

	if ((res = ReadFromTheCard (0x9f36, &atc)) == SUCCESS)
		res = ReadFromTheCard (0x9f13, &last_atc);
	if (res != SUCCESS)
	{
		// Set both the 'Lower consecutive offline limit exceeded' and the 
		// 'Upper consecuitive limit exceeded' bits to '1' in the TVR:
		EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x60);

		// Set the 'ICC Data Missing' bit to '1' in TVR -- This rule is according
		// to VIS 1.4.0, ch 9.8, Figure 9-2.
		EMV_Context::updateDataObject(0x95, &dob_TVR, 1, 0x20);
		if (res == TRM_ERROR_DATA_NOT_FOUND)
			return SUCCESS;
		else
			return res;
	}

	// 6. Compare the difference between the ATC and the Last Online ATC RegbSdaData
	// with  the Lower and Upper Consecuitive Offline Limits:
	int diff = atc - last_atc;
	
	/* Activate the code below when draft bulletin #18 takes effect
	if (diff <= 0)
	{
		// ATC is less than or equal to the value if the Last Online ATC.
		// According to the draft bulletin #18 (July 2003), this condition 
		// requires to set both the 'Lower consequitive offline limit
		// exceeded' and the 'Upper consequitive offline limit exceeded'
		// to '1' in TVR and end velocity checking.
		EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x60);
		return SUCCESS;
	}
	*/
	int low = (int)LongFromByte(dob_limit_lo.Data, dob_limit_lo.len);
	int high = (int)LongFromByte(dob_limit_hi.Data, dob_limit_hi.len);
	
	if (diff > low)
	{
		// The lower limit of consecuitive offline transactions has been exceeded.
		// Set the 'Lower consecutive offline limit exceeded' bit to '1' in the TVR:
		EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x40);
	
		if (diff > high)
		{
			// The upper limit of consecuitive offline transactions has been exceeded.
			// Set the 'Upper consecutive offline limit exceeded' bit to '1' in the TVR:
			EMV_Context::updateDataObject(0x95, &dob_TVR, 4, 0x20);
		}
	}

	// 7. New Card checking (VIS 1.4.0 ch 9.9)
	if (last_atc == 0)
	{
		// Set the 'New card' bit to '1' in the TVR
		EMV_Context::updateDataObject(0x95, &dob_TVR, 2, 0x08);
	}

	return SUCCESS;
}

void TerminalRiskManagement::setTerminalRiskMangmntComplete()
{
	EMV_Context::updateDataObject(0x9B, &dob_TSI, 1, 0x08);
}

bool TerminalRiskManagement::IsRiskManagementSupported()
{
	int res;
	DataObject dob_AIP;

	// Get Application Interchange Profile from the hash
	res = EnvContext.getTagValue(0x82, &dob_AIP, true);
	if (res == SUCCESS)
	{
		// Check the 'Terminal risk management is supported' bit of AIP
		// (bit 4 of the first byte of AIP data object)
		if (check_bit(dob_AIP.Data [0], 0x08))
			return true;
	} 
	return false;
}

bool TerminalRiskManagement::IsTransLogExist()
{
	// Provide an implementation for checking the log support here
	return false;
}

int TerminalRiskManagement::GenerateRandomNumber(byte *rand)
{
	// Get a pointer to the Crypto service
	CryptoControlImpl *Crypto = (CryptoControlImpl*) EnvContext.GetService(CNTXT_CRYPTO);
	if (!Crypto)
		return ERR_SERVICE_NOT_CONNECTED;

	CryptoOperationEventImpl opEvent;
	int res;

	// Attach Operation event
	if ((res = Crypto->addOperationEvent(&opEvent)) != SUCCESS)
		return res;

	// Calculate a random number
	res = Crypto->randomNumber(1, 1);
	Crypto->removeEvent();

	if (res != SUCCESS)
		return opEvent.getError();

	// Get the length in bytes of the resulting random value
	int len = opEvent.getLength();
	if (len != 1)
		return ERR_UNEXPECTED_TYPE;

	// Extract a random number from the event object
	byte *btVal;
	opEvent.getByteString(&btVal);

	// Value must be in a range from 1 to 99
	*rand = (btVal[0] % 99) + 1;
	return SUCCESS;
}


int TerminalRiskManagement::Binary2Numeric(const byte bin_data[], int bin_len, 
										   byte numData[], int num_len)
{
	UNINT uiData = (UNINT)LongFromByte(bin_data, bin_len);
	char chData[32];
	//_ultoa(uiData, chData, 10);
	snprintf(chData, 32, "%lu", uiData);
	return asciStr2HexString (chData, (UNINT) strlen(chData),
						numData, num_len,
						0x00, false);
}

// Calculates the Transaction Target Percent.
// Source: EMV 4.0, book 3, ch 6.6.2, footnote 9 (page 55).
int TerminalRiskManagement::calcTransactionTargetPercent(const byte amount[],
								 const byte threshold[],
								 const byte floor[],
								 byte target,
								 byte max_target,
								 byte *TransactionTarget)
{
	double dbl_amount;
	double dbl_threshold;
	double dbl_floor;
	double interpolation;
	int res;

	if ((res = Numeric2Double(amount, 6, &dbl_amount)) != SUCCESS)
		return res;
	if ((res = Numeric2Double(threshold, 6, &dbl_threshold)) != SUCCESS)
		return res;
	if ((res = Numeric2Double(floor, 6, &dbl_floor)) != SUCCESS)
		return res;
	if (dbl_threshold < 0 || dbl_threshold >= dbl_floor)
	{
		// This condition is specified in EMV 4.0, book 3, ch 6.6.2, bullet 2
		return ERR_INVALID_TERMINAL_DATA;
	}

	interpolation = (dbl_amount - dbl_threshold) / (dbl_floor - dbl_threshold);
	*TransactionTarget = (byte)(((max_target - target) * interpolation) + target);

	return SUCCESS;
}

int TerminalRiskManagement::ReadFromTheCard (int tag, int *iVal)
{
	// Get a pointer to the card reader service
	SCRControlImpl *pSCR = (SCRControlImpl*) EnvContext.GetService(CNTXT_SCR);
	if (!pSCR)
		return ERR_SERVICE_NOT_CONNECTED;

	int res;

	// Set APDU command to send to the card
	scr_command command;
	command.setReader (pSCR);
	if ((res = command.setGetData(tag)) != SUCCESS)
		return res;

	// Send the GetData command to the card
	R_APDU rapdu;
	if ((res = command.run (&rapdu, TransactionToken)) != SUCCESS)
		return res;

	if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
	{
		// The Data is successfully retreived
		// Parse the data
		tlv_parser parsed_data;
		byte *data = rapdu.copyData();
		if ((res = parsed_data.parse (data, rapdu.getDataLen())) != SUCCESS)
		{
			// Failed to parse data returned from the card
			delete [] data;
			return TRM_ERROR_DATA_NOT_FOUND;
		}
		if (parsed_data.GetRoot ()->GetTagVal() != tag)
		{
			delete[] data;
			return TRM_ERROR_DATA_NOT_FOUND;
		}

		// Update Context by adding a data object with this tag
		EMV_Context::setDataObject (tag, parsed_data.GetRoot ()->GetValue (),
			parsed_data.GetRoot ()->GetLengthVal (), "", CNFG_TRANSACTION);

		// Set return value
		*iVal = (int)LongFromByte(parsed_data.GetRoot ()->GetValue(), 
							parsed_data.GetRoot()->GetLengthVal ());
		delete [] data;
		return SUCCESS;
	}
	else
		return TRM_ERROR_DATA_NOT_FOUND;
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
	else if ((rapdu.getSW1 () == 0x6A && rapdu.getSW2 () == 0x81) ||
			(rapdu.getSW1 () == 0x6A && rapdu.getSW2 () == 0x88))
	{
		// Valid response codes according to EMV book 3, table I-5)
		return TRM_ERROR_DATA_NOT_FOUND;
	}
	else
	{
		// Invalid response from the card
		return ERR_CMD_INVALID_ICC_RESPONSE;
	}
	*/
}

bool TerminalRiskManagement::IsApplInExceptionFile(const byte *pan, int pan_len, 
												   const byte *seq, int seq_len)
{
	// Provide an implementation of Exception file checking here.

	return false;
}
