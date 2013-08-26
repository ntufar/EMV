// HostControl Service
// HostControl Interface Implementation -- Server Side

#include "HostControlImpl.h"

HostControlImpl::HostControlImpl(void)
{
}

HostControlImpl::~HostControlImpl(void)
{
	DestroyHostObject();
}


int HostControlImpl::host_connect()
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return res;

	if (CreateHostObject () != SUCCESS)
		return res;

	// Provide implementation of this method here
	AccessManager *pAM = this->getAccessManager ();
	if (!pAM)
		return ERR_AM_NOT_INITIALIZED;

	byte bAID[AID_MAX_LEN];
	int aid_sz = AID_MAX_LEN;
	if (!pAM->getAID(bAID, &aid_sz))
		return ERR_AM_NOT_INITIALIZED;

	char *cAID = HexByte2AsciiStr(bAID, aid_sz);
	if (!cAID)
		return ERR_AM_NOT_INITIALIZED;

	// Provide additional implementation here
	res = connect2host (cAID);
	delete [] cAID;
	return res;
}


// Analyzes a Response Code and returns ONLINE_RESULT indicating whether
// the transaction is approved, declined, or required a referral
// Source: VIS 1.4.0, Ch 13.5.1
// Parameter:
//	AuthRespCode - Authorization Response Code to analyze 2-byte array
ONLINE_RESULT HostControlImpl::AnalyzeAuthResponse (const byte* const AuthRespCode)
{
	if ((strncmp((char*)AuthRespCode, "00", 2) == 0) ||
		(strncmp((char*)AuthRespCode, "10", 2) == 0) ||
		(strncmp((char*)AuthRespCode, "11", 2) == 0))
	{
		// The issuer has approved the transaction
		return ONRES_APPROVE; // Approve 
	}
	else if ((strncmp((char*)AuthRespCode, "01", 2) == 0) ||
			 (strncmp((char*)AuthRespCode, "02", 2) == 0))
	{
		// The issuer has requested a referral
		return ONRES_REFERRAL; // Referral
	}
	else if (strncmp((char*)AuthRespCode, "05", 2) == 0)
	{
		// The transaction is declined
		return ONRES_DECLINE; // Decline
	}
	else
	{
		// Unrecognized transaction
		return ON_RES_UNKNOWN;
	}
}

int HostControlImpl::send_data(int msg_type,
							   const byte *out_data, UNINT out_len, 
							   UNINT timeout)
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	OperationEventWithValue *pEvent = (OperationEventWithValue*) opEvent;
	//Reset event
	pEvent->resetEvent();
	
	if (msg_type != MSG_AUTHORIZATION_REQUEST)
		return ERR_HOST_MSG_NOT_SUPPORTED;

/*
	if (!ptrHost.GetInterfacePtr ())
	{
		// Host Object is not created
		return ERR_HOST_OBJECT_NOT_LOADED;
	}
*/

	// Provide implementation of this method here
	// Create a safe array for outgoing data
	SAFEARRAY *psaArrayOut = CreateSafeArray(out_data, out_len);
	if (!psaArrayOut)
	{
		return ERR_MEMORY_ALLOC;
	}
	
	// Create a safe array for incoming data
	unsigned long in_len = 500;
	SAFEARRAY *psaArrayIn = CreateSafeArray(NULL, in_len);
	if (!psaArrayIn)
	{
		//SafeArrayDestroy(psaArrayOut);
		return ERR_MEMORY_ALLOC;
	}

	// Send Data
	try
	{
		//res = ptrHost->send_data(&psaArrayOut, out_len, &psaArrayIn, &in_len, timeout);
		if (res == SPERR_BUFFER_OVERFLOW)
		{
			// Buffer overflow
			return pEvent->setLong (in_len);
		}
		if (res == SUCCESS)
		{
			if (in_len > 0)
			{
				byte *buff = ParseSafeArr (psaArrayIn, in_len);
				res = pEvent->setByteString (buff, in_len);
				delete [] buff;
			}
			else
				res = pEvent->setByteString (NULL, 0);
		}
		else
		{
			res = pEvent->setError (mapError(res), HOST_EXECUTION);
		}
	}
	catch (...)
	{
		//cout << "send_data FAILED" << endl;
		//cout << "HRESULT message is " << e.ErrorMessage () << endl;
		res = pEvent->setError (ERR_HOST_COM_EXCEPTION, HOST_EXECUTION);
	}
	
	//SafeArrayDestroy(psaArrayOut);
	//SafeArrayDestroy(psaArrayIn);

	return res;
}
	
// Disconnects from the host
void HostControlImpl::host_disconnect()
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return;

	// Provide implementation of this method here
	//if (!ptrHost.GetInterfacePtr ())
	//	return;
/*
	try
	{
		HRESULT hr = ptrHost->host_disconnect();
	}
	catch (...)
	{
	}
	DestroyHostObject();
*/
}

long HostControlImpl::checkInitialization (bool checkEvent)
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
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, HOST_EXECUTION);
	}
	return SUCCESS;
}

int HostControlImpl::mapError(long res)
{
	switch (res)
	{
	case SPERR_SUCCESS:
		return SUCCESS;
		break;
	case SPERR_COMM_ERROR:
		return ERR_HOST_COMM_ERROR;
		break;
	case SPERR_HOST_DISCONNECT:
		return ERR_HOST_DISCONNECT;
		break;
	case SPERR_INVALID_HOST:
		return ERR_INVALID_HOST;
		break;
	case SPERR_INVALID_PORT:
		return ERR_HOST_INVALID_PORT;
		break;
	case SPERR_INVALID_RESPONSE:
		return ERR_HOST_INVALID_RESPONSE;
		break;
	case SPERR_NO_CONNECTION:
		return ERR_HOST_NO_CONNECTION;
		break;
	case SPERR_NO_RESPONSE:
		return ERR_HOST_NO_RESPONSE;
		break;
	case SPERR_PROCESSING_ERROR:
		return ERR_HOST_PROCESSING_ERROR;
		break;
	case SPERR_INVALID_AID:
		return ERR_HOST_INVALID_AID;
		break;
	case SPERR_BUFFER_OVERFLOW:
		return ERR_HOST_BUFFER_OVERFLOW;
		break;
	default:
		return ERR_HOST_UNSPECIFIED_ERROR;
	}
}

int HostControlImpl::CreateHostObject ()
{
/*
	HRESULT hr;
	if (ptrHost.GetInterfacePtr ())
	{
		// Host Object is already created-- do nothing
		return SUCCESS;
	}

	// Initialize COM
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		// Unable to initialize COM
		return ERR_HOST_LOADING_COM_LIB;
	}

	//Create an instance of the server
	try
	{
		hr = ptrHost.CreateInstance (CLSID_VSDCAuth);
		if (FAILED(hr))
			_com_issue_error (hr);
	}
	catch (_com_error &e)
	{
		//cout << "Error creating instance" << endl;
		//cout << "HRESULT message is " << e.ErrorMessage () << endl;
		CoUninitialize();
		return ERR_HOST_LOADING_COM_LIB;
	}
*/
	return SUCCESS;
	
}

void HostControlImpl::DestroyHostObject()
{
/*
	if (ptrHost.GetInterfacePtr ())
	{
		// Release object
		ptrHost = 0;
		CoUninitialize();
	}
*/
}

int HostControlImpl::connect2host (const char *aid)
{
/*
	if (!ptrHost.GetInterfacePtr ())
	{
		return ERR_HOST_OBJECT_NOT_LOADED;
	}

	//Access the ptrHost interface
	long res;
	try
	{
		_bstr_t bstrAID (aid);
		res = ptrHost->host_connect(&(bstrAID.GetBSTR ()));
		return mapError(res);
	}
	catch (_com_error &e)
	{
		//cout << "Error accessing Host interface" << endl;
		//cout << "HRESULT message is " << e.ErrorMessage () << endl;
		return ERR_HOST_COM_EXCEPTION;
	}
*/
}

SAFEARRAY* HostControlImpl::CreateSafeArray(const byte *fillArr, UNINT size)
{
	SAFEARRAY *psaArray = 0;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = size;
	//psaArray = SafeArrayCreate(VT_UI1, 1, rgsabound);
	
	if (!psaArray)
		return NULL;

	// Fill array with values
	byte FillVal;
	for (UNINT i = 0; i < size; i++)
	{
		if (fillArr)
			FillVal = fillArr[i];
		else
			FillVal = 0;

		//SafeArrayPutElement(psaArray, (long*) &i, (void*) &FillVal);
	}
	return psaArray;
}

byte* HostControlImpl::ParseSafeArr (SAFEARRAY *psaArray, unsigned long size)
{
	if (size == 0 || !psaArray)
		return NULL;

	long lLBound, lUBound;
	//SafeArrayGetLBound(psaArray, 1, &lLBound);
	//SafeArrayGetUBound(psaArray, 1, &lUBound);

	unsigned long arrSize = lUBound - lLBound;
	if (arrSize < size)
		return NULL;

	byte *buff = new byte [size];
	if (!buff)
		return NULL;

	byte bValue;
	for (long i = lLBound; i < (long)size; i++)
	{
		//SafeArrayGetElement (psaArray, &i, &bValue);
		buff[i] = bValue;
	}
	return buff;
}


// Returns an array of tags for data required for online message.
int HostControlImpl::getOnlineDataTags (ONLINE_DATA_TAGS tagType)
{
	if (!AM)
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	if (!eventAttached())
		return opEvent->setError (ERR_EVT_NO_EVNT_OBJECT, RUNTIME_EXECUTION);

	int res;

	// Read data from the Registry
	CnfgControlImpl cnfg;
	if ((res = AM->open (&cnfg)) != SUCCESS)
		return opEvent->setError (res, AM_OPENNING_SERVICE);

	CnfgOperationEventImpl cnfgEvent;
	HostOperationEvent *pEvent = (HostOperationEvent*)opEvent;

	cnfg.addOperationEvent (&cnfgEvent);
	switch (tagType)
	{
	case AUTH_RQST_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", AUTH_RQST_REG_KEY);
		break;
	case RESP_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", RESP_REG_KEY);
		break;
	case FINANC_RQST_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", FINANC_RQST_REG_KEY);
		break;
	case ADVICE_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", ADVICE_REG_KEY);
		break;
	case REVERSAL_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", REVERSAL_REG_KEY);
		break;
	default:
		res = ERR_HOST_MSG_NOT_SUPPORTED;
	}

	cnfg.removeEvent ();
	if (res == SUCCESS)
	{
		if (cnfgEvent.getValueType () == OPEVENT_BINARY)
		{
			if (cnfgEvent.getLength () > 0)
			{
				byte *byte_data = 0;
				cnfgEvent.getByteString (&byte_data);

				// Successfully read the value from the registry
				return pEvent->setByteString (byte_data, cnfgEvent.getLength ());
			}
		}
		// Unexpected type of the value read from the registry
		return pEvent->setError (ERR_REG_VALUE_READ_FAILED, RUNTIME_EXECUTION);
	}
	else if (res == ERR_HOST_MSG_NOT_SUPPORTED)
	{
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}
	else
	{
		return pEvent->setError (cnfgEvent.getError (), RUNTIME_EXECUTION);
	}
}
