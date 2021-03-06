#include "ApplSelControlImpl.h"
#include "ApplSelOperationEventImpl.h"

ApplSelControlImpl::ApplSelControlImpl(void)
{
	opEvent = new ApplSelOperationEventImpl;
}

ApplSelControlImpl::~ApplSelControlImpl(void)
{
}

// Implements EMV's Application Selection process.
// If card support PSE method it is used first, otherwise List-Of-Directories
// method is used.
// Populates EventObject with the value returned by the card to the Select
// command to select chosen application
int ApplSelControlImpl::EMV_ApplicationSelection(long TransactionToken)
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	ApplSelOperationEventImpl *pEvent = (ApplSelOperationEventImpl*) opEvent;
	//Reset event
	pEvent->resetEvent();

	long TransToken = TransactionToken;
	tlv_parser tlv_Appl;
	res = Selector.ApplicationSelection(TransToken, &tlv_Appl);
	
	if (res == SUCCESS)
	{
		// Operation completed successfully.
		// Store data into Operation Event.
		return pEvent->setValues (TransToken, 
								  tlv_Appl.GetRoot ()->GetDataObject (),
								  tlv_Appl.GetRoot ()->GetDataObjectLen ());
	}
	else
	{
		// Error occured while executing application Selection
		return pEvent->setError (res, APPLICATION_SELECTION);
	}
}

// Build a list of applications supported by the terminal. Must be executed
// prior calling EMV_ApplicationSelection method
int ApplSelControlImpl::BuildTerminalApplList()
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	ApplSelOperationEventImpl *pEvent = (ApplSelOperationEventImpl*) opEvent;
	//Reset event
	pEvent->resetEvent();

	if ((res = Selector.BuildTerminalApplList ()) != SUCCESS)
		return pEvent->setError (res, APPLICATION_SELECTION);

	return pEvent->setSuccess ();
}

// Initializes (opens) the services used in Application Selection processing.
// Don't require OperationEvent.
// returns SUCCESS if Initialization is successfull or error code otherwise
int ApplSelControlImpl::Initialize()
{
	int res;
	res = Selector.InitServices (this->getAccessManager ());
	if (res != SUCCESS)
		return res;

	return Selector.GetPSE ();
}

// Selects an application based on AID passed as a parameter
int ApplSelControlImpl::SelectApplication(long TransactionToken,
										  byte *AID, int aid_len)
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	ApplSelOperationEventImpl *pEvent = (ApplSelOperationEventImpl*) opEvent;
	//Reset event
	pEvent->resetEvent();

	tlv_parser tlv_Appl;
	res = Selector.SelectApplication (TransactionToken, AID, aid_len, &tlv_Appl);
	if (res == SUCCESS)
	{
		// Operation completed successfully.
		// Store data into Operation Event.
		return pEvent->setValues (TransactionToken, 
								  tlv_Appl.GetRoot ()->GetDataObject (),
								  tlv_Appl.GetRoot ()->GetDataObjectLen ());
	}
	else
	{
		// Error occured while executing application Selection
		return pEvent->setError (res, APPLICATION_SELECTION);
	}
}


long ApplSelControlImpl::checkInitialization (bool checkEvent)
{
	if (checkEvent)
	{
		// Check if the OperationEvent has been added to this object
		if (!this->opEvent )
			return ERR_EVT_NO_EVNT_OBJECT;

		if (opEvent->operation_running())
			return ERR_OPEVNT__ALREADY_RUNNING;
	}
	// Check if the Application Name has been added (call to the initialize() 
	// must be made before calling this function)
	if (!this->getAccessManager ())
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}
	return SUCCESS;
}

// application cannot be executed.
int ApplSelControlImpl::EMV_SelectNext()
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	ApplSelOperationEventImpl *pEvent = (ApplSelOperationEventImpl*) opEvent;
	//Reset event
	pEvent->resetEvent();

	tlv_parser tlv_Appl;
	res = Selector.FinalSelection (&tlv_Appl);
	if (res == SUCCESS)
	{
		// Operation completed successfully.
		// Store data into Operation Event.
		long TranToken = Selector.getTransactionToken ();
		return pEvent->setValues (TranToken, 
								  tlv_Appl.GetRoot ()->GetDataObject (),
								  tlv_Appl.GetRoot ()->GetDataObjectLen ());
	}
	else
	{
		// Error occured while executing application Selection
		return pEvent->setError (res, APPLICATION_SELECTION);
	}
}

// Externally cancels a transaction. Used for example to terminate 
// an Application Selection process when the card is removed from 
// the Card Reader slot.
// This function doesn't require an Operation Event
int ApplSelControlImpl::CancelTransaction()
{
	Selector.CancelTransaction ();
	return SUCCESS;
}
