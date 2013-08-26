// CLCControlVSDC Service
// CLCControlVSDC Interface Implementation -- Server Side.
// This class implements a VSDC transaction as defined by EMV 4.0 and VIS 1.4.0.

#include "clcVSDCImpl.h"
#include "UIControlImpl.h"
#include "CLCInterface.h"

clcVSDCImpl::clcVSDCImpl(void)
{
	// Initialize global variables
	IsCLCInitialized = false;
	IsEMVProcCompleted = false;
	IsEMVProcInProgress = false;
	memset (&TransactionParams, 0, sizeof(TRANS_STARTUP_PARAMS));
}

clcVSDCImpl::~clcVSDCImpl(void)
{
	resetCLC();
}

int clcVSDCImpl::checkInitialization (bool checkEvent)
{
	if (checkEvent)
	{
		// Check if the OperationEvent has been added to this object
		if (!this->opEvent )
			return ERR_EVT_NO_EVNT_OBJECT;

		if (opEvent->operation_running())
			return ERR_OPEVNT__ALREADY_RUNNING;
	}

	// Check if Access Manager has been added
/*	if (!this->getAccessManager ())
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, CLC_EXECUTION);
	}
*/
	// Check if POSControl has been initialized
	if (!IsCLCInitialized)
		return CLC_NOT_INITIALIZED;

	return SUCCESS;
}

int clcVSDCImpl::initCLC (void *Param)
{
	// Check if POS is already initialized and if it is, then reset it before
	// reinitializing
	if (IsCLCInitialized)
	{
		resetCLC();
	}

	// Initialize Parameters
	if (!Param)
		return CLC_BAD_ARGUMENT;

	TRANS_STARTUP_PARAMS *TranParams = (TRANS_STARTUP_PARAMS*)Param;
	if (TranParams->TransactionToken == 0)
		return CLC_MISSING_INIT_DATA;

	int res;

	memcpy (TransactionParams.AmountAuthorized, TranParams->AmountAuthorized, 6);
	memcpy (TransactionParams.AmountOther, TranParams->AmountOther, 6);
	memcpy (TransactionParams.CurrencyCode, TranParams->CurrencyCode, 2);
	TransactionParams.TransactionInfo = TranParams->TransactionInfo;
	TransactionParams.TransactionToken  = TranParams->TransactionToken;
	TransactionParams.TransactionType = TranParams->TransactionType;
	TransactionParams.LanguageID = TranParams->LanguageID;

	// Verify parameters and Initialize Context:
	if ((res = EMV.initContext (AM, TransactionParams.TransactionToken)) 
		!= SUCCESS)
	{
		resetCLC();
		return res;
	}
	
	if ((res = EMV.initTransactionType (TransactionParams.TransactionType)) 
		!= SUCCESS)
	{
		resetCLC();
		return res;
	}

	// Check if the Amount is present
	if (memcmp(TransactionParams.AmountAuthorized, zero_amount, 6) != 0)
	{
		// Amount is specified
		// Check CurrencyCode -- must be present!
		if (memcmp(TransactionParams.CurrencyCode, zero_amount, 2) == 0)
		{
			// Currency Code is not present -- try to get Terminal Country Code
			// (tag '9F1A')
			byte termCode[2];
			if ((res = GetTermCountryCode (termCode)) != SUCCESS)
			{
				// Cannot continue execution without this value
				resetCLC();
				return res;
			}
			else
			{
				memcpy(TransactionParams.CurrencyCode, termCode, 2);
			}
		}

		// Check if Transaction Type specified uses cashback amount, and
		// if this so, add the AmountAuthorized and Cashback Amount and 
		// store the sum under the AmountAuthorized field
		if (check_bit(TransactionParams.TransactionInfo, 0x02))
		{
			// Cashback amount is expected
			// Check if the Amount Other is present
			if (memcmp(TransactionParams.AmountOther, zero_amount, 6) != 0)
			{
				// Initialize Context to hold Amount, Other
				if ((res = EMV.initAmountOther  (TransactionParams.AmountOther)) 
					!= SUCCESS)
				{
					// Cannot continue execution without this value
					resetCLC();
					return res;
				}
			}

			// Add Cashback amount to the Amount Authorized
			res = Add2numAmounts (TransactionParams.AmountAuthorized, 
								  TransactionParams.AmountOther);
			if (res != SUCCESS)
			{
				//Some error occured during this operation. stop execution
				resetCLC();
				return res;
			}
		}
		
		// Initialize Context to hold Amount
		if ((res = EMV.initAmount (TransactionParams.AmountAuthorized, 
			TransactionParams.CurrencyCode)) != SUCCESS)
		{
			// Cannot continue execution without this value
			resetCLC();
			return res;
		}
	}

	IsCLCInitialized = true;
	return SUCCESS;
}

void clcVSDCImpl::resetCLC()
{
	memset (&TransactionParams, 0, sizeof(TRANS_STARTUP_PARAMS));
	EMV.UninitContext ();
	IsCLCInitialized = false;
	IsEMVProcCompleted = false;
	IsEMVProcInProgress = false;
}


int clcVSDCImpl::verifyTransaction (byte *fci_data, int fci_len)
{
	int res = checkInitialization ();
	if (res != SUCCESS)
		return res;
	if (IsEMVProcInProgress)
	{
		return CLC_INPROGRESS;
	}

	opEvent->begin_operation();

	IsEMVProcCompleted = false;
	IsEMVProcInProgress = true;

	// Cast the OperationEvent object to the appropriate type
	CLCOperationEvent *pEvent = (CLCOperationEvent*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Get a pointer to the UIControl service
	UIControlImpl *UI = (UIControlImpl*)EMV.GetService (CNTXT_UI);
	if (!UI)
		return pEvent->setError (CLC_CNTXT_CANNOT_FIND_SERVICE, POS_EXECUTION);
	if (!UI->opened())
	{
		if ((res = this->AM->open (UI)) != SUCCESS)
			return pEvent->setError (res, POS_EXECUTION);
	}

	// Get a pointer to the SCRControl service
	SCRControlImpl *SCR = (SCRControlImpl*)EMV.GetService (CNTXT_SCR);
	if (!SCR)
		return pEvent->setError (CLC_CNTXT_CANNOT_FIND_SERVICE, POS_EXECUTION);
	if (!SCR->opened())
	{
		if ((res = this->AM->open (SCR)) != SUCCESS)
			return pEvent->setError (res, POS_EXECUTION);
	}

	UI->writeStatus ("CLC - clcVSDC Module started");

	// Parse input data (File Control Information) into tlv_parser object
	tlv_parser tlv_Appl, tlv_AIP;
	res = tlv_Appl.parse(fci_data, fci_len);
	if (res != SUCCESS)
		return pEvent->setError (res, CLC_EXECUTION);

	// -----------------------------------
	// 1. Initiate Application Processing
	// -----------------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Initiate Application");
	if ((res = EMV.ApplicationInit (&tlv_Appl, &tlv_AIP)) != SUCCESS)
	{
		// Failed to initialize the Application.
		UI->writeStatus ("   CLC - Initiate Application FAILED");
		// Reset a context
		resetCLC();
		return pEvent->setError(res, CLC_EXECUTION);
	}

	// Increment Transaction Sequence Counter
	EMV.IncrementTransactionSeqCounter();

	// Application selected successfully -- continue transaction

	// -----------------------------------
	// 2. Read Application Data
	//------------------------------------
	byte *odaList;
	int oda_len;
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Read Application Data");
	res = EMV.ReadApplData (&tlv_AIP, &odaList, &oda_len);
	if (res != SUCCESS)
	{
		UI->writeStatus ("   CLC - Read Application Data FAILED");
		IsEMVProcInProgress = false;
		return pEvent->setError (res, POS_EXECUTION);
	}
	
	// Data is successfully read from the card
	
	// Go to the next step; determine which crypto method to execute
	// -----------------------------------
	// 3. Offline Data Authentication
	//------------------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Offline Data Authentication");
	res = EMV.offlineDA(odaList, oda_len);
	
	if (res != SUCCESS)
	{
		UI->writeStatus ("   CLC - ODA Failed");
		IsEMVProcInProgress = false;
		delete [] odaList;
		return pEvent->setError (res, POS_EXECUTION);
	}
	
	// Continue processing

	// ------------------------------------
	// 4. Process Restrictions
	// ------------------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		delete [] odaList;
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Process Restrictions");
	if ((res = EMV.ProcessRestrictions()) != SUCCESS)
	{
		UI->writeStatus ("   CLC - Process Restrictions FAILED");
		IsEMVProcInProgress = false;
		delete [] odaList;
		return pEvent->setError (res, POS_EXECUTION);
	}

	// Continue processing

	// ------------------------------
	// 5. Cardholder verification
	// ------------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		delete [] odaList;
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Carholder Verification");
	if ((res = EMV.CardHolderVerification(odaList, oda_len)) != SUCCESS)
	{
		UI->writeStatus ("CLC Cardholder Verification FAILED");
		IsEMVProcInProgress = false;
		delete [] odaList;
		return pEvent->setError (res, POS_EXECUTION);
	}

	// Release odaList
	delete [] odaList;

	// Cardholder Verification succeeded. Continue transaction
	
	// -----------------------------
	// 6. Terminal Risk Management
	// -----------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Terminal Risk Management");
	if ((res = EMV.riskManagement ()) != SUCCESS)
	{
		UI->writeStatus ("CLC - Terminal Risk Management Failed");
		IsEMVProcInProgress = false;
		return pEvent->setError (res, POS_EXECUTION);
	}
	
	// Terminal Risk Management succeeded. Continue transaction
				
	// -----------------------------
	// 7. Make a final decision on whether or not to Accept or Decline
	//	a transaction
	// -----------------------------
	if (!SCR->IsTransactionAlive (this->TransactionParams.TransactionToken))
	{
		resetCLC();
		return pEvent->setError(SCR_TRANSACTION_DISCONTINUED, CLC_EXECUTION);
	}
	UI->writeStatus ("CLC - Make Transaction Decision");
	TERMINAL_RESPONSE term_resp;
	if ((res = EMV.makeTransactionDecision (&term_resp)) != SUCCESS)
	{
		UI->writeStatus ("CLC - makeTransactionDecision Failed");
		IsEMVProcInProgress = false;
		return pEvent->setError (res, POS_EXECUTION);
	}

	// makeTransactionDecision Succeeded. Continue transaction
									
	// End Transaction
	IsEMVProcInProgress = false;
	IsEMVProcCompleted = true;
	res = pEvent->setTransDecision (term_resp);
	return res;
}


int clcVSDCImpl::getTransData(int Tag, byte *data_value, int *data_sz, 
						    char format[], bool bTransactionDataOnly)
{
	int res = checkInitialization (false);
	if (res != SUCCESS)
		return res;

	if (!IsCLCInitialized)
		return CLC_NOT_INITIALIZED;

	DataObject dob;
	res = EMV.getTransactionData (Tag, data_value, data_sz, format,
								  bTransactionDataOnly);
	return res;
}

int clcVSDCImpl::OpenServiceCntrl (ServiceControl *sc)
{
	int res;
	// Open service control
	if ((res = AM->open(sc)) != SUCCESS)
	{
		//cout << "ERROR: Service open failed: " << res << endl;
		return res;
	}
	return SUCCESS;
}

int clcVSDCImpl::GetTermCountryCode (byte *termCode)
{
	// Initialize CnfgControl
	CnfgControlImpl cnfg;
	int res = AM->open (&cnfg);
	if (res != SUCCESS)
		return res;

	// Add operation event
	CnfgOperationEventImpl opEvent;
	cnfg.addOperationEvent (&opEvent);

	// Get value from registry
	res = cnfg.getValue (CNFG_TERMINAL, "Data", "9F1A");
	cnfg.removeEvent ();
	AM->close (cnfg);
	if (res != SUCCESS)
		return res;

	if (opEvent.getValueType() != CNFG_BINARY ||
		opEvent.getLength () != 2)
		return ERR_UNEXPECTED_TYPE;

	byte *val = 0;
	res = opEvent.getByteString (&val);
	memcpy (termCode, val, 2);
	return res;
}

void clcVSDCImpl::outputDataObject(scsEMV &EMV, int tag, const char *name)
{	
	// Continue only in Debug mode 
	char *buff;
	int res;

	// Get pointer to UIControl
	UIControlImpl *UI = (UIControlImpl*)EMV.GetService (CNTXT_UI);
	if (!UI)
		return;
	if (!UI->opened())
	{
		if ((res = this->AM->open (UI)) != SUCCESS)
			return;
	}

	int value_sz = 10;
	byte *bt_value = new byte [value_sz];

	DataObject dob;
	char format[4];
	res = EMV.getTransactionData (tag, bt_value, &value_sz, format);
	if (res == ERR_BUFFER_OVERFLOW)
	{
		delete [] bt_value;
		bt_value = new byte [value_sz];
		res = EMV.getTransactionData (tag, bt_value, &value_sz, format);
	}
	if (res != SUCCESS)
	{
		buff = new char [strlen ("Cannot retreive") + strlen (name) + 1];
		strcpy (buff, "Cannot retreive");
		strcat(buff, name);
		UI->writeStatus (buff);
		delete [] buff;
		delete bt_value;
		return;
	}
	
	UI->writeStatus (name);
	buff = DumpByteArr(bt_value, value_sz );
	UI->writeStatus (buff);
	delete [] buff;
	delete [] bt_value;
	return;
}


