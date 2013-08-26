#include "ProcessingRestrictions.h"

ProcessingRestrictions::ProcessingRestrictions(void)
{
}

ProcessingRestrictions::~ProcessingRestrictions(void)
{
}

int ProcessingRestrictions::initData()
{
	int tags[2];
	DataObject *dob[2];
	bool hashOnly[2];
	bool mandatory[2];

	// TVR
	tags[0] = 0x95; 
	dob[0] = &dob_TVR;
	hashOnly[0] = true;
	mandatory[0] = true;

	// Terminal Country Code
	tags[1] = 0x9f1a; 
	dob[1] = &dob_TermCountryCode;
	hashOnly[1] = false;
	mandatory[1] = true;

	return EMV_Context::initData (tags, dob, hashOnly, mandatory, 2);
}

// Implements section 6.4.1, book 3 of EMV spec
int ProcessingRestrictions::CheckVersion()
{
	int res;

	if (InitStatus == EMV_DATA_ERROR)
		return initError;
	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if (initData() != SUCCESS)
			return initError;
	}

	//1 Get an application version number read from the ICC
	DataObject dob_icc;
	res = EnvContext.getTagValue (0x9f08, &dob_icc, true);
	if (res != SUCCESS || dob_icc.len == 0)
	{
		// If Appl Version number is not present in the ICC, simply return
		return SUCCESS;
	}

	//2 Get an application version number from the terminal
	DataObject dob_term;
	res = EnvContext.getTagValue (0x9f09, &dob_term, false);
	if (res != SUCCESS || dob_term.len == 0)
	{
		// If Appl Version number is not present on the terminal, simply return
		return SUCCESS;
	}

	if (dob_icc.len != dob_term.len)
		set_bit (dob_TVR.Data [1], 0x80); // Versions are different
	else if (memcmp(dob_icc.Data, dob_term.Data, dob_icc.len) != 0)
		set_bit (dob_TVR.Data [1], 0x80); // versions are different
	else
	{
		// Versions are identical
		reset_bit (dob_TVR.Data [1], 0x80);
	}

	// Update TVR
	EnvContext.setTagValue (0x95, &dob_TVR, IO_UPDATE);
	return SUCCESS;
}

int ProcessingRestrictions::CheckUsageControl()
{
	DataObject dob_auc; // Application Usage Control
	int res;

	if (InitStatus == EMV_DATA_ERROR)
		return initError;
	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if (initData() != SUCCESS)
			return initError;
	}

	res = EnvContext.getTagValue (0x9f07, &dob_auc, true);
	if (res == SUCCESS && dob_auc.len > 0)
	{
		// DO checking according to section 6.4.2, EMV book 3 - 
		//  Application Usage Control)

		// Get Terminal Type and additional terminal capabilities
		DataObject dob_termType;
		DataObject dob_addTermCap;
		if ((res = EnvContext.getTagValue (0x9f35, &dob_termType, false))
			!= SUCCESS)
			return EMV_MISSING_MANDATORY_DATA;
		
		if ((res = EnvContext.getTagValue (0x9f40, &dob_addTermCap, false))
			!= SUCCESS)
			return EMV_MISSING_MANDATORY_DATA;

		// Check condition 1 (section 6.4.2, EMV book 3)
		if (IsATM(&dob_termType, &dob_addTermCap))
		{
			// Terminal type is ATM
			if (!check_bit(dob_auc.Data[0], 0x02))
			{
				//Appl Usage Control doesn't have 'Valid for ATMs' bit set
				updateDataObject (0x95, &dob_TVR, 2, 0x10);
			}
		}
		else
		{
			// Terminal is not an ATM
			// Check condition 2 (section 6.4.2, EMV book 3)
			if (!check_bit(dob_auc.Data[0], 0x01))
			{
				// Appl Usage Control doesn't have 'Valid for terminals
				// other than ATMs' bit set
				updateDataObject (0x95, &dob_TVR, 2, 0x10);
			}
		}

		// Get Issuer Country Code
		DataObject dob_issCntryCode;
		if ((res = EnvContext.getTagValue (0x5f28, &dob_issCntryCode, true))
			!= SUCCESS)
		{
			// Issuer Country code is conditional if Application Usage Control is
			// present. Since it is not found, do not continue with additional
			// checking
			return SUCCESS;
			//return EMV_MISSING_MANDATORY_DATA;
		}
		
		// Get Transaction Info (tag '60000001' in TransactionTypes). This data type
		// must be initialized during TransactionType initialization
		DataObject dob_transInfo;
		if ((res = EnvContext.getTagValue (0x60000001, &dob_transInfo, true))
			!= SUCCESS)
		{
			// Transaction Info is mandatory. 
			//Since it is not found, exit the transaction
			return EMV_MISSING_MANDATORY_DATA;
		}

		byte cash = 0x20;
		byte goods = 0x04;
		byte services = 0x08;
		byte cashback = 0x02;

		byte dom_cash = 0x80;
		byte int_cash = 0x40;
		byte dom_goods = 0x20;
		byte int_goods = 0x10;
		byte dom_serv = 0x08;
		byte int_serv = 0x04;
		byte dom_csh_back = 0x80;
		byte int_csh_back = 0x40;

		bool IsCountryCodeMatch = CompareByteArr (dob_issCntryCode.Data,
												  dob_issCntryCode.len,
												  dob_TermCountryCode.Data,
												  dob_TermCountryCode.len);
		
		if (checkTransaction (dob_transInfo.Data [0], 
							    cash, dom_cash, int_cash,
						        dob_auc.Data[0], IsCountryCodeMatch) != SUCCESS)
			return updateDataObject (0x95, &dob_TVR, 2, 0x10);
		if (checkTransaction (dob_transInfo.Data [0], 
								goods, dom_goods, int_goods,
						        dob_auc.Data[0], IsCountryCodeMatch) != SUCCESS)
			return updateDataObject (0x95, &dob_TVR, 2, 0x10);
		if (checkTransaction (dob_transInfo.Data [0], 
							  services, dom_serv, int_serv,
						      dob_auc.Data[0], IsCountryCodeMatch) != SUCCESS)
			return updateDataObject (0x95, &dob_TVR, 2, 0x10);
		// Check if cashback amount (Amount Other, tag '9F03') is present
		DataObject dob_cashBack;
		if ((res = EnvContext.getTagValue (0x9f03, &dob_cashBack, true))
			== SUCCESS)
		{
			if (checkTransaction (dob_transInfo.Data [0], 
								  cashback, dom_csh_back, 
								  int_csh_back, dob_auc.Data[1], 
								  IsCountryCodeMatch) != SUCCESS)
				return updateDataObject (0x95, &dob_TVR, 2, 0x10);
		}
	}
	return SUCCESS;

}


int ProcessingRestrictions::CheckApplicationDates()
{
	int res;

	// 1. Get current (transaction) date
		AddCurTime2Hash();
	DataObject dob_transDate;     //NTNTNTNT
	res = EnvContext.getTagValue (0x9a, &dob_transDate, true);
	if (res != SUCCESS)
	{
		// Date is not in the hash; try to add it and retreive again
		AddCurTime2Hash();
		res = EnvContext.getTagValue (0x9a, &dob_transDate, true);
		if (res != SUCCESS)
			return EMV_DATA_NOT_FOUND;
	}
	dateStruct transDate;
	if (!EmvDate2DateStruct(dob_transDate.Data, dob_transDate.len, &transDate))
		return EMV_INVALID_FORMAT;


	// 2. Get application effective date from the hash
	DataObject dob_effectDate;
	res = EnvContext.getTagValue (0x5f25, &dob_effectDate, true);
	if (res == SUCCESS && dob_effectDate.len > 0)
	{
		// Application effective date exists; verify that the current date
		// is greater than or equal to the Application Effective date
		// (section 6.4.3, EMV book 3)

		// Convert dates to dateStruct format
		dateStruct effDate;
		if (!EmvDate2DateStruct(dob_effectDate.Data, dob_effectDate.len, &effDate))
			return EMV_INVALID_FORMAT;
		if (compareDates (&effDate, &transDate) < 0)
		{
			// effDate > transDate
			// Set 'Application not yet effective' bit in TVR to '1'
			updateDataObject (0x95, &dob_TVR, 2, 0x20);
		}
	}

	// 3. Get Application Expiration Date from the hash
	DataObject dob_expDate;
	res = EnvContext.getTagValue (0x5f24, &dob_expDate, true);
	if (res != SUCCESS)
	{
		// Application Expiration Date is a mandatory data object.
		// It is missing from the hash (meaning it was not read from the card
		// in  previous steps).
		// Exit transaction
		return EMV_MISSING_MANDATORY_DATA;
	}
	// Convert Appl Expiration date to dateStruct format
	dateStruct expDate;
	if (!EmvDate2DateStruct(dob_expDate.Data, dob_expDate.len, &expDate))
		return EMV_INVALID_FORMAT;
	if (compareDates (&transDate, &expDate) < 0)
	{
		// transDate > expDate
		// Set 'Expired Application' bit in TVR to '1'
		updateDataObject (0x95, &dob_TVR, 2, 0x40);
	}
	return SUCCESS;		
}


int ProcessingRestrictions::checkTransaction (byte termCap, 
											  byte transType, 
											  byte dom_trans, 
											  byte inter_truns,
						                      byte auc, 
											  bool IsCountryCodeMatch)
{
	if (check_bit(termCap, transType))
	{
		if (IsCountryCodeMatch)
		{
			// Issuer Country Code == Term Country Code
			if (!check_bit(auc, dom_trans)) // Is Not Vaild for Domestic Transactions
			{
				// Condition is not satisfied
				return EMV_CONDITIONS_NOT_SATISFIED;
			}
		}
		else
		{
			// Issuer Country Code != Term Country Code
			if (!check_bit(auc, inter_truns)) // Is Not Vaild for International Transactions
			{
				// Condition is not satisfied
				return EMV_CONDITIONS_NOT_SATISFIED;
			}
		}
	}
	return SUCCESS;
}

// This function determines whether or not the terminal is ATM.
// This check is performed based on the rule specified in
// EMV book 4 (Cardholder, Attendant and Acquirer Interface Requirements),
// Annex A, A1.
// Terminal types '14', '15', and '16' with cash disbursment capability 
//(Additional terminal capabilities, byte 1, 'cash' bit = '1') are considered
// to be ATMs. All other terminal types are not considered to be ATMs.
bool ProcessingRestrictions::IsATM(DataObject *dob_TermType, 
								   DataObject *dob_TermCap)
{
	if (((dob_TermType->Data[0] == 0x14) ||
		 (dob_TermType->Data[0] == 0x15) ||
		 (dob_TermType->Data[0] == 0x16)) &&
		check_bit(dob_TermCap->Data [0], 0x80))
		return true;
	else
		return false;
}
