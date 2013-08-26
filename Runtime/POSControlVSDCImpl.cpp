#include "POSControlVSDCImpl.h"

POSControlVSDCImpl::POSControlVSDCImpl(const byte *aid, int aid_len)
{
	// Initialize global variables
	IsPOSInitialized = false;
	IsEMVProcInProgress = false;
	IsFirstTimeExecuted = true;
	memset (&TransactionParams, 0, sizeof(TRANS_STARTUP_PARAMS));
	opEvent = new POSOperationEventImpl;
	setServiceName("POSControlVSDCImpl");
	memcpy(this->aid, aid, aid_len);
	this->aid_len = aid_len;
	this->AM = new AccessManager(aid, aid_len);
}

POSControlVSDCImpl::~POSControlVSDCImpl(void)
{
	resetPOS();
	if (amAdder::AM)
		releaseAM(&(amAdder::AM));
}

void POSControlVSDCImpl::releaseAM(AccessManager **ppAM)
{
	if (*ppAM)
	{
		delete *ppAM;
		*ppAM = 0;
	}
}

int POSControlVSDCImpl::execPOS(byte *fci_data, int fci_len)
{
	int res = checkInitialization ();
	if (res != SUCCESS)
		return res;
	if (IsEMVProcInProgress)
	{
		return POS_INPROGRESS;
	}

	opEvent->begin_operation();

	IsEMVProcInProgress = true;

	// Cast the OperationEvent object to the appropriate type
	POSOperationEventImpl *pEvent = (POSOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	printf ("Starting POS application\n");
	outputPOSApplInfo();

	if (!IsFirstTimeExecuted)
	{
		// Reinitialize CLC module if execPOS is executed more than once
		res = clcControl.initCLC ((void*)&TransactionParams);
		if (res != SUCCESS)
			return pEvent->setError (res, POS_EXECUTION);
	}

	// Do some pre-processing here if desired
	// ...

	CLCOperationEventImpl clcOpEvent;
	clcControl.addOperationEvent (&clcOpEvent);

	// Execute EMV/VIS transaction verification
	res = clcControl.verifyTransaction (fci_data, fci_len);
	clcControl.removeEvent ();

	if (res == SUCCESS)
	{
		// Do some post-processing here if desired
		//...
		TERMINAL_RESPONSE des = clcOpEvent.getTransDecision();
		if (des == TERMINAL_APPROVE)
			printf ("Transaction is APPROVED by a terminal!!!");
		else
			printf ("Transaction is DECLINED by a terminal!!!");
		pEvent->setLong (des);
	}
	else
	{
		char buff[100];
		sprintf(buff, "Runtime error occured while executing CLC module,"
			"res = %#x, error = %#x", res, clcOpEvent.getError());
		printf (buff);
		pEvent->setError(clcOpEvent.getError (), clcOpEvent.getOperation ()); 
	}

	// End POS
	IsFirstTimeExecuted = false;
	IsEMVProcInProgress = false;
	return res;
}

int POSControlVSDCImpl::checkInitialization (bool checkEvent)
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
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}*/

	// Check if POSControl has been initialized
	if (!IsPOSInitialized)
		return POS_NOT_INITIALIZED;

	return SUCCESS;
}

int POSControlVSDCImpl::initPOS (void *Param)
{
	// Check if POS is already initialized and if it is, then reset it before
	// reinitializing
	if (IsPOSInitialized)
	{
		resetPOS();
	}

	// Initialize Parameters
	if (!Param)
		return POS_BAD_ARGUMENT;

	TRANS_STARTUP_PARAMS *TranParams = (TRANS_STARTUP_PARAMS*)Param;
	if (TranParams->TransactionToken == 0)
		return POS_MISSING_INIT_DATA;

	memcpy (TransactionParams.AmountAuthorized, TranParams->AmountAuthorized, 6);
	memcpy (TransactionParams.AmountOther, TranParams->AmountOther, 6);
	memcpy (TransactionParams.CurrencyCode, TranParams->CurrencyCode, 2);
	TransactionParams.TransactionInfo = TranParams->TransactionInfo;
	TransactionParams.TransactionToken  = TranParams->TransactionToken;
	TransactionParams.TransactionType = TranParams->TransactionType;
	TransactionParams.LanguageID = TranParams->LanguageID;

	int res;
	// Open UI service
/*
	if ((res = OpenServiceCntrl(&UI)) != SUCCESS)
		return res;
*/
	
	// Open CLC service
	if ((res = OpenServiceCntrl((ServiceControl*)&clcControl)) != SUCCESS)
		return res;

	// Initialize CLC control
	if ((res = clcControl.initCLC ((void*)&TransactionParams)) != SUCCESS)
	{
		resetPOS();
		return res;
	}

	IsPOSInitialized = true;
	return SUCCESS;
}

void POSControlVSDCImpl::resetPOS()
{
	memset (&TransactionParams, 0, sizeof(TRANS_STARTUP_PARAMS));
	IsPOSInitialized = false;
	IsEMVProcInProgress = false;
	clcControl.resetCLC ();
}

int POSControlVSDCImpl::getTransData(int Tag, byte *data_value, int *data_sz, 
						    char format[], bool bTransactionDataOnly)
{
	int res = checkInitialization (false);
	if (res != SUCCESS)
		return res;

	if (!IsPOSInitialized)
		return POS_NOT_INITIALIZED;

	return clcControl.getTransData (Tag, data_value, data_sz, 
									format, bTransactionDataOnly);
}

int POSControlVSDCImpl::OpenServiceCntrl (ServiceControl *sc)
{
	int res;
	// Open service control
	if (sc->opened ())
	{
		// Service already opened
		return SUCCESS;
	}
	if ((res = AM->open(sc)) != SUCCESS)
	{
		// Service open failed
		return res;
	}
	
	return SUCCESS;
}


void POSControlVSDCImpl::outputDataObject(scsEMV &EMV, int tag, const char *name)
{
	char *buff;
	int res;


	int value_sz = 10;
	byte *bt_value = new byte [value_sz];

	DataObject dob;
	char format [4];
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
		printf (buff);
		delete [] buff;
		delete bt_value;
		return;
	}
	
	printf (name);
	buff = DumpByteArr(bt_value, value_sz );
	printf (buff);
	delete [] buff;
	delete [] bt_value;
	return;
}

void POSControlVSDCImpl::outputPOSApplInfo()
{

	// Get Application Name
	const char *ApplName = AM->getApplicationName ();
	if (!ApplName)
		return;

	byte appl_aid [AID_MAX_LEN];
	int aid_len = AID_MAX_LEN;
	if (AM->getAID(appl_aid, &aid_len))
	{
		char *asci_aid = HexByte2AsciiStr(appl_aid, aid_len);
		if (asci_aid)
		{
			int sz1 = 19 + (int)strlen(ApplName);
			char *buff = new char [sz1];
			if (buff)
			{
				sprintf (buff, "Application Name: %s\n", ApplName);
				printf (buff);
			}
			int sz2 = (int)strlen (asci_aid) + 6;
			if (!buff)
				buff = new char [sz2];
			else if (sz1 < sz2)
			{
				delete [] buff;
				buff = new char [sz2];
			}
			if (buff)
			{
				sprintf (buff, "AID: %s\n",  asci_aid);
				printf (buff);
				delete [] buff;
			}
			delete [] asci_aid;
		}
	}
}
