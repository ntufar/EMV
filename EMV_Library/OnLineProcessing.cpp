#include "OnLineProcessing.h"

OnLineProcessing::OnLineProcessing(void)
{
	TerminationFlag = false;
}

OnLineProcessing::~OnLineProcessing(void)
{
	TerminationFlag = false;
}

int OnLineProcessing::initData()
{
	const int size = 3;
	int tags[size];
	DataObject *dob[size];
	bool hashOnly[size];
	bool mandatory[size];

	TerminationFlag = false;

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

int OnLineProcessing::goOnline()
{
	// Set a static varibale keeping the status of the online transaction to false
	EMV_Context::OnLineCompleted = false;
	EMV_Context::OnLineResult = ON_RES_UNKNOWN;
	TerminationFlag = false;

	// Check initialization of mandatory data objects
	if (InitStatus == EMV_DATA_ERROR)
		return EMV_MISSING_MANDATORY_DATA;

	int res;

	if (InitStatus == EMV_DATA_NOT_INITIALIZED)
	{
		if ((res = initData ()) != SUCCESS)
			return res;
	}

	// Check if the terminal has an online capability
	if (!IsOnlineTerminal())
		return SUCCESS;
	
	// Get the pointer to AccessManager
	AccessManager *pAM = EnvContext.getAccessManager();
	if (!pAM)
		return ERR_AM_NOT_INITIALIZED;

	// Open HostControl service
	HostControlImpl host;
	if ((res = pAM->open((ServiceControl*)&host)) != SUCCESS)
	{
		// DLL not found. Unable to go Online
		// Set a static varibale keeping the status of the online transaction to false
		EMV_Context::OnLineCompleted = false;
		// Continue transaction
		return res;
	}

	HostOperationEventImpl opEvent;
	host.addOperationEvent (&opEvent);

	res = host.getOnlineDataTags(AUTH_RQST_TAGS);
	host.removeEvent ();
	if (res != SUCCESS)
		return opEvent.getError();

	// Prepare data to be sent in online message
	byte *tags = 0;
	opEvent.getByteString(&tags);
	byte *onLineData = 0;
	UNINT data_len;
	if ((res = getOnLineData (tags, opEvent.getLength(),
							  &onLineData, &data_len)) != SUCCESS)
		return res;
 
	// Send online message and receive response
	OutputMsg ("EMV - Sending Online Message...");
	res = sendOnLineMsg(host, onLineData, data_len);
	delete [] onLineData;
	if (res != SUCCESS)
	{ 
		OutputMsg ("  EMV - Online FAILED");
		// Online processing failed (not online verification)
		EMV_Context::OnLineCompleted = false;
		EMV_Context::OnLineResult = ON_RES_UNKNOWN;
		return res;
	}
	
	// Check AIP if Issuer Authentication is supported
	if (check_bit(dob_AIP.Data[0], 0x04)) 
	{
		// Perform External Authentication
		if ((res = ExternalAuth()) != SUCCESS)
		{
			// This means that there were issuer authentication data
			// parsing error or sending data to the card error, or
			// invalid response from the card.
			// Either case requires a reversal message and termination of 
			// transaction
			if (EMV_Context::OnLineCompleted &&
				EMV_Context::OnLineResult == ONRES_APPROVE)
			{
				EMV_Context::ReversalNeeded = true;
			}
			TerminationFlag = true;
			return res;
		}
	}
	
	
	// Online processing is completed
	return SUCCESS;
}


int OnLineProcessing::sendOnLineMsg(HostControlImpl &host,
									const byte *onLineData, UNINT data_len)
{
	HostOperationEventImpl opEvent;
	int res;
	EMV_Context::OnLineCompleted = false;
	EMV_Context::OnLineResult = ON_RES_UNKNOWN;
	EMV_Context::ReversalNeeded = false;

	// Add operation event to the service
	if ((res = host.addOperationEvent (&opEvent)) != SUCCESS)
		return res;

	// Connect to the Acquirer 
	if ((res = host.host_connect()) != SUCCESS)
	{
		// Failed to connect to the Acquirer
		host.removeEvent ();
		return res;
	}

	// Get Timeout
	DataObject dob_to;
	int to;
	res = this->EnvContext.getTagValue (0x5000000B, &dob_to, false);
	if (res != SUCCESS || (dob_to.len <= 0 || dob_to.len > 4))
		to = SCS_TO_INFINITE;
	else
		to = LongFromByte(dob_to.Data, dob_to.len );
	
	DataObject dob_retr;
	int retrial;
	res = this->EnvContext.getTagValue (0x5000000C, &dob_retr, false);
	if (res != SUCCESS || (dob_retr.len <= 0 || dob_retr.len > 4))
		retrial = 3;
	else
	{
		retrial = LongFromByte(dob_retr.Data, dob_retr.len );
		if (retrial <= 0)
			retrial = 3;
	}
	
	while (retrial > 0)
	{
		// Load Authorization request message to a log file
		logDataRecord(EMV_LOG_AUTH_MSG, onLineData, data_len);

		opEvent.resetEvent (true);

		// Send message online and wait for the response
		res = host.send_data (MSG_AUTHORIZATION_REQUEST, onLineData, data_len, to);

		// Check the result of online execution
		if (res != SUCCESS)
		{
			// Error occured while sending a message.
			if (res == EVT_ERROR)
			{
				// this type of error requires a reversal message
				res =  opEvent.getError();
				retrial--;
				EMV_Context::ReversalNeeded = true;
				continue;
			}
			else
			{
				// This type of error doesn't require a reversal
				break;
			}
		}

		byte *buff = 0;
		int len = opEvent.getLength();
		if (len <= 0)
		{
			// No data has been returned by Issuer
			// This condition requires sending a reversal message
			res = ERR_HOST_INVALID_RESPONSE;
			EMV_Context::ReversalNeeded = true;
			retrial--;
			continue;
		}
		if ((res = opEvent.getByteString(&buff)) != SUCCESS)
		{
			// Some error retreiving data from the operation event.
			EMV_Context::ReversalNeeded = true;
			break;
		}

		// Log response to the log file
		logDataRecord(EMV_LOG_AUTH_MSG, buff, len);

		resetOnlineDataInContext(&host);
		if ((res = parseOnLineMsg (buff, (UNINT)len)) != SUCCESS)
		{
			// Failed to parse message
			// This condition requires sending a reversal message
			retrial--;
			EMV_Context::ReversalNeeded = true;
			continue;
		}
		
		// Get Authentication Response Code 
		DataObject dob_arc;
		if ((res = EnvContext.getTagValue (0x8a, &dob_arc, true)) != SUCCESS)
		{
			// Authentication Response Code is not received in Authentication Response
			res = ERR_HOST_INVALID_RESPONSE;
			retrial--;
			EMV_Context::ReversalNeeded = true;
			continue;
		}
		else
		{
			// Assign static variable to keep the result of online processing
			EMV_Context::OnLineResult = host.AnalyzeAuthResponse(dob_arc.Data);
			if (EMV_Context::OnLineResult == ON_RES_UNKNOWN)
			{
				// Unknown Authorization response
				res = ERR_HOST_UNKNOWN_AUTH_CODE;
				retrial--;
				EMV_Context::ReversalNeeded = true;
				continue;
			}
			else
			{
				EMV_Context::OnLineCompleted = true;
				EMV_Context::ReversalNeeded = false;
				break;
			}
		}
	} // retrial while loop

	// Disconnect from the server
	host.host_disconnect ();
	// Remove the event object from the Host service
	host.removeEvent ();

	return res;
}

int OnLineProcessing::parseOnLineMsg (byte *respData, UNINT resp_len)
{
	// Parse data, store in the Context
	int res;
	UNINT curIndx = 0;
	tlv tlvObj;
	int tag;
	int count71 = 0;
	int count72 = 0;
	int padOffset = 0;
	EMV_Context::IssuerScriptSize = 0;

#ifdef _DEBUG
	char *buff = DumpByteArr(respData, resp_len);
	printf ("Online Message:\n%s\n", buff);
	delete [] buff;
#endif
	
	while (curIndx < resp_len)
	{
		// Skip 0x00 or 0xff bytes
		padOffset = tlv::findDataStartPoint (respData + curIndx, 
			                               resp_len - curIndx);
		curIndx += padOffset;
		if (curIndx >= resp_len)
			break;

		res = tlvObj.SetTlv (respData + curIndx, resp_len - curIndx);
		if (res != SUCCESS)
		{
			// Failed to parse data received from the Issuer
			return ERR_INVALID_ISSUER_DATA;
		}
		// Put data into the Context
		// There are might be multiple scripts in the response. To store all 
		// of them into the Context we will keep the counter of the script in a tag 
		// value. The third byte keeps the counter of the script.
		if (tlvObj.GetTagVal () == 0x71)
		{
			tag = tlvObj.GetTagVal() | (count71 << 24);
			count71++;
			EMV_Context::IssuerScriptSize += tlvObj.GetLengthVal();
		}
		else if (tlvObj.GetTagVal () == 0x72)
		{
			tag = tlvObj.GetTagVal() | (count72 << 24);
			count72++;
			EMV_Context::IssuerScriptSize += tlvObj.GetLengthVal();
		}
		else
		{
			tag = tlvObj.GetTagVal ();
		}
		
		res = setDataObject(tag, tlvObj.GetValue (), 
			tlvObj.GetLengthVal (), "", CNFG_TRANSACTION);
		curIndx += tlvObj.GetDataObjectLen ();
	}
	return SUCCESS;
}

int OnLineProcessing::ExternalAuth()
{
	int res;

	// check if Issuer Authentication Data has been returned in online response
	DataObject dob_iad;
	res = EnvContext.getTagValue(0x91, &dob_iad, true);
	if (res != SUCCESS || dob_iad.len  == 0)
	{
		// Isuer Authentication Data is not found in the Context.
		// Do not send External Authenticate command.
		return SUCCESS;
	}

	// Get a pointer to the SCRControl
	SCRControlImpl *pSCR = (SCRControlImpl*)EnvContext.GetService(CNTXT_SCR);
	if (!pSCR)
	{
		// Cannot obtain a pointer to the SmartCard Reader service
		return SERVICE_NOT_FOUND_IN_CONTEXT;
	}

	// Prepare command for sending to the card
	scr_command command(pSCR);
	res = command.setExternalAuthenticate(dob_iad.Data, dob_iad.len);
	if (res != SUCCESS)
	{
		// Cannot set command
		return res;
	}

	// Send command to the card
	R_APDU rapdu;
	res = command.run (&rapdu, TransactionToken);
	if (res == SUCCESS)
	{
		// Set the 'Authorization Performed' bit in TSI to '1'
		EMV_Context::updateDataObject(0x9b, &dob_TSI, 1, 0x10);
		if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
		{
			// Authentication successfully verified.
			return SUCCESS;
		}
		else
		{
			// Authentication failed.
			// Set the 'Issuer Authentication was Unsuccessful' bit in TVR to '1'
			EMV_Context::updateDataObject(0x95, &dob_TVR, 5, 0x40);
			if ((rapdu.getSW1 () == 0x63 && rapdu.getSW2 () == 0x00) ||
				(rapdu.getSW1 () == 0x69 && rapdu.getSW2 () == 0x85))
			{
				// These are valid response codes defined in
				// EMV book 3 table I-5, section 2.3.5)
				return SUCCESS;
			}
			else
			{
				// Invalid codes are returned -- terminate transaction
				return ERR_CMD_INVALID_ICC_RESPONSE;
			}
		}
	}
	return res;
}

bool OnLineProcessing::IsCommError(int res)
{
	switch (res)
	{
	case ERR_HOST_COMM_ERROR:
	case ERR_HOST_DISCONNECT:
	case ERR_INVALID_HOST:
	case ERR_HOST_INVALID_PORT:
	case ERR_HOST_NO_CONNECTION:
	case ERR_HOST_NO_RESPONSE:
		return true;
	default:
		return false;
	}
}

void OnLineProcessing::resetOnlineDataInContext(HostControlImpl *host)
{
	HostOperationEventImpl opEvent;
	int res;

	if ((res = host->addOperationEvent(&opEvent)) != SUCCESS)
		return;

	res = host->getOnlineDataTags(RESP_TAGS);
	host->removeEvent();
	if (res != SUCCESS)
		return;

	int len = opEvent.getLength();
	if (len <= 0)
		return;

	byte *data = 0;
	if ((res = opEvent.getByteString (&data)) != SUCCESS)
		return;

	if (!data)
		return;

	int curIndx = 0;
	int tag_val, tag_len;

	while (curIndx < len)
	{
		res = tlv::parseTag (data + curIndx, &tag_val, &tag_len);
		if (res != SUCCESS)
		{
			// Failed to parse data received from the Issuer
			return;
		}
		// Remove data for this tag from the context
		if (tag_val == 0x71 || tag_val == 0x72)
			resetScriptTags(tag_val);
		else
			EnvContext.removeTag(tag_val);

		curIndx += tag_len;
	}
}

void OnLineProcessing::resetScriptTags(int tag)
{
	int counter = 0;
	int res;
	DataObject dob_script;
	// Get the script from the Context
	while (true)
	{
		tag = tag | (counter << 24);
		res = EnvContext.getTagValue(tag, &dob_script, true);
		if (res != SUCCESS)
		{
			// Script was not found.
			break;
		}
		else
			EnvContext.removeTag(tag);
		counter++;
	}
}


bool OnLineProcessing::IsTerminationRequested()
{
	return TerminationFlag;
}
