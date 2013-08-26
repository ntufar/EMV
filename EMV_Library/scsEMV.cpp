// deneme
#include "scsEMV.h"

scsEMV::scsEMV(void)
{
	combinedDDA_AC = false;
}

scsEMV::~scsEMV(void)
{
}

int scsEMV::getTransactionData (int Tag, byte *data_value, int *data_len,
								char format[], bool bHashOnly)
{
	int res;
	DataObject dob_value;
	// Check parameters
	if (!data_value || *data_len <= 0)
		return ERR_BAD_ARGUMENT;

	// Find a value
	if ((res = EnvContext.getTagValue(Tag, &dob_value, bHashOnly)) != SUCCESS)
	{
		return res;
	}
	
	if (dob_value.len > *data_len)
	{
		*data_len = dob_value.len;
		return ERR_BUFFER_OVERFLOW;
	}
	else
	{
		memcpy(data_value, dob_value.Data, dob_value.len);
		*data_len = dob_value.len;
		strcpy (format, dob_value.Format);
		return SUCCESS;
	}
}

int scsEMV::ApplicationInit(tlv_parser *tlv_Appl, tlv_parser *tlv_AIP)
{
	ApplicationInitialization applInit;
	return applInit.ApplicationInit (tlv_Appl, tlv_AIP);
}

int scsEMV::ReadApplData (tlv_parser *tlv_AIP, byte **ppOdaList, int *oda_len)
{
	ReadApplicationData reader;
	return reader.ReadApplData (tlv_AIP, ppOdaList, oda_len);
}

// Offline Data Authentication
int scsEMV::offlineDA(const byte *odaList, int oda_len)
{
	OfflineDataAuthentication oda;
	int res = SUCCESS;
	int method;
	combinedDDA_AC = false;

	method = oda.determineCryptoMethod ();
	if (method < 0)
	{
		//Error determining the ODA method to use
		res = method;
	}
	else
	{
		switch (method)
		{
		case CRYPTO_NO_AUTHENTICATION:
			// No mutually supported ODA methods
			res = oda.setAuthStatus(CRYPTO_NO_AUTHENTICATION, 0);
			break;
		case CRYPTO_SDA:
			// Static Data Authentication
			res = oda.StaticDataAuth(odaList, oda_len);
			break;
		case CRYPTO_DDA:
			// Dynamic Data Authentication
			res = oda.DynamicDataAuth(odaList, oda_len);
			break;
		case CRYPTO_DDA_AC:
			// DDA/AC
			// -- not implemented yet
			res = oda.setAuthStatus(CRYPTO_DDA_AC, 0);
			combinedDDA_AC = true;
			break;
		default:
			//Invalid return value
			res = oda.setAuthStatus(res, 0);
			break;
		}
	}
	return res;
}


int scsEMV::ProcessRestrictions ()
{
	ProcessingRestrictions restr;
	int res;
	if ((res = restr.CheckVersion()) != SUCCESS)
		return res;

	if ((res = restr.CheckUsageControl()) != SUCCESS)
		return res;

	return restr.CheckApplicationDates();
}

int scsEMV::CardHolderVerification(const byte *odaList, int oda_len)
{
	CardholderVerification cvm(odaList, oda_len);
	return cvm.Verify();
}

int scsEMV::riskManagement()
{
	TerminalRiskManagement trm;
	int res = trm.checkExceptionFile();
	if (IsCardholderTerminal())
	{
		// A cardholder-controlled terminal need not support 
		//terminal risk management (see EMV book 4, ch 2.4)
		return SUCCESS;
	}
	if (trm.IsRiskManagementSupported())
	{
		if ((res = trm.floorLimit()) == SUCCESS)
		{
			if ((res = trm.randomTransactionSelection()) == SUCCESS)
				res = trm.velocityChecking();
		}

		if (res == SUCCESS)
			trm.setTerminalRiskMangmntComplete();
	}
	return res;
}

int scsEMV::makeTransactionDecision(TERMINAL_RESPONSE *term_resp)
{
	TransactionDecision trDes;
	return trDes.MakeTransactionDecision(combinedDDA_AC, term_resp);
}

int scsEMV::IncrementTransactionSeqCounter()
{
	int res;
	byte counter_one [] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
	// Get Current value of the counter (tag '9f41')
	DataObject dob_Counter;
	bool SetToOne = false;
	byte exp = 1;

	res = EMV_Context::EnvContext.getTagValue (CNFG_TERMINAL, 0x9f41, 
											   &dob_Counter);
	if (res != SUCCESS)
	{
		// Counter is not found.
		SetToOne = true;
	}
	else if (dob_Counter.len != 8)
	{
		// Invalid length of the counter, set it to 1
		SetToOne = true;
	}
	else
	{
		// Counter is found -- Increment it
		int val;
		exp = 1;
		for (int i = 7; i >= 0; i--)
		{
			val = dob_Counter.Data [i] & 0x0000000f;
			if (val > 10)
			{
				exp = 1; // Forse to set the Counter value to 1
				break;
			}
			val += exp;
			if (val >= 10)
			{
				val -= 10;
				exp = 1;
			}
			else
			{
				exp = 0;
			}
			
			dob_Counter.Data[i] &= 0xf0;
			dob_Counter.Data [i] |= (byte)val;

			if (exp == 0)
				break;
			val = (dob_Counter.Data[i] >> 4) & 0x0000000f;
			if (val > 10)
			{
				exp = 1; // Forse to set the Counter value to 1
				break;
			}
			val += exp;
			if (val >= 10)
			{
				val -= 10;
				exp = 1;
			}
			else
				exp = 0;
			val <<= 4;
			dob_Counter.Data[i] &= 0x0f;
			dob_Counter.Data[i] |= (byte)val;
			if (exp == 0)
				break;
		} // End Of For
	} // End Of Else (dob_counter.len == 8)

	if (SetToOne)
	{
		// Assign it to 1 and store to the registry
		res = dob_Counter.set (counter_one, 8, CNFG_TERMINAL, "n");
		if (res != SUCCESS)
		{
			return res;
		}
	}
	else if (exp == 1)
	{
		// Counter overflow (or invalid digit) -- set it to 1
		memset (dob_Counter.Data, 0, 8);
		dob_Counter.Data[7] = 1;
	}
	
	// Update Context and Registry
	res = EMV_Context::EnvContext.setTagValue (0x9f41, &dob_Counter,
				IO_WRITE_THROUGH | IO_CREATE | IO_UPDATE);
	return res;
}
