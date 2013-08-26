#include "SCRControlImpl.h"
#include <stdio.h>
#define FALSE 0

#include "SCRControlServer.h"
#include "AccessManager.h"
#include "SCROperationEventImpl.h"

#define UM_QUIT WM_APP + 1
#define UM_READER_STATE_CHANGE WM_APP + 2

//ERRORS
#define SCR_FAILED_WIN_CLASS_REG 0xA0000001
#define SCR_FAILED_WIN_CREATE    0xA0000002

// Global variabled declaration
//HINSTANCE hInstance; // Keeps an Instance to this DLL
//HWND hMsgWnd;        // Handle to a message window
//HANDLE hWndThread;   // Handle to a thread that lounched the message window
//HANDLE hEventThread; // Handle to a thread that tracks a smart card insert/remove events

unsigned wndThreadID; // A thread id of the message thread
unsigned eventThreadID; // A thread id of the event tracker thread

//HANDLE WindExist; // Event Object: Signaled when a window exists
//HANDLE CntxExist; // Event Object: Signaled when a Context exists

BOOL bCardInserted;   // Indicates the current status of the card: TRUE when a card is present in the reader, FALSE when a card is not present

// PC/SC API defined data types
SCARDCONTEXT ThreadhContext;
SCARD_READERSTATE ThreadReaderState;
SCARDCONTEXT    hContext = 0;
SCARDHANDLE hCardHandle;
bool CancelEventTrack;

// Name of the reader. Currently the system searches for and uses the first 
//  available reader
//char *ReaderName;   <--- was this
char ReaderNameBuf[1024];
char *ReaderName = ReaderNameBuf;
int TransmitCommand (C_APDU *capdu, byte **rapdu, int *rapdu_len,
					 const long TransactionToken);

LPTSTR getPreferredReader();
bool IsPrefReaderFound(LPTSTR pmszReaders, DWORD dwBuffSz, 
					   LPTSTR pPrefReader, DWORD *dwCurStr);
int getReaderName (SCARDCONTEXT hContext, char **name);
static SCRControlImpl* getPointer(UINT_KEY key);
int appendArr(byte **finalResult, DWORD *finalLen, 
			   byte *bRecvBuffer, DWORD dwRecvLength);





SCRControlImpl::SCRControlImpl():
pOnInsertFunc(NULL),
pOnRemoveFunc(NULL)
{
	//OnInsertMutex = CreateMutex(0, FALSE, NULL);
	//OnRemoveMutex = CreateMutex(0, FALSE, NULL); 
	opEvent = new SCROperationEventImpl;
}


SCRControlImpl::~SCRControlImpl(void)
{
	//HANDLE hndlArr[] = {OnInsertMutex, OnRemoveMutex};
	//WaitForMultipleObjects(2, hndlArr, TRUE, INFINITE);
	delete opEvent;
	pOnInsertFunc = NULL;
	pOnRemoveFunc = NULL;
	//ReleaseMutex(OnInsertMutex);
	//ReleaseMutex(OnRemoveMutex);
	//CloseHandle(OnInsertMutex);
	//CloseHandle(OnRemoveMutex);
}

int  SCRControlImpl::EstablishConnection ()
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
	{
		return res;
	}
	if (IsInitialized())
	{
		return SUCCESS; // Already initialized, so return without doing anything
	}
	return SUCCESS;
}

void SCRControlImpl::DestroyConnection ()
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
	{
		return;
	}

	if (Map.size() > 1)
		return;
}

int SCRControlImpl::RegisterEvent (/*[IN]*/int eventID, 
						/*[IN]*/CallBackFunc pEventFunc)
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return res;

	switch (eventID)
	{
	case ONINSERT:
		pOnInsertFunc = pEventFunc;
		break;
	case ONREMOVE:
		pOnRemoveFunc= pEventFunc;
		break;
	default:
		return SCR_INVALID_EVENT_ID;
	}
	return SUCCESS;
}

void SCRControlImpl::UnRegisterEvent (/*[IN]*/int eventID)
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return;

	switch (eventID)
	{
	case ONINSERT:
		pOnInsertFunc = NULL;
		break;
	case ONREMOVE:
		pOnRemoveFunc = NULL;
		break;
	default:;
	}
}

bool SCRControlImpl::IsEventRegistered(int eventID)
{
	switch (eventID)
	{
	case ONINSERT:
		if (pOnInsertFunc)
			return true;
		break;
	case ONREMOVE:
		if (pOnRemoveFunc)
			return true;
		break;
	default:
		return false;
	}
	return false;
}

void SCRControlImpl::FireEvent (int eventID)
{
	switch (eventID)
	{
	case ONINSERT:
		if (pOnInsertFunc)
		{
			//WaitForSingleObject(OnInsertMutex, INFINITE);
			pOnInsertFunc();
			//ReleaseMutex(OnInsertMutex);
		}
		break;
	case ONREMOVE:
		if (pOnRemoveFunc)
		{
			//WaitForSingleObject(OnRemoveMutex, INFINITE);
			pOnRemoveFunc();			
			//ReleaseMutex(OnRemoveMutex);
		}
		break;
	default:;
	}
}



int _SendCommand (const byte *capdu,  unsigned int capdu_len,
				 byte **rapdu, unsigned int *rapdu_len, 
				 const long TransactionToken)
{
	if (!capdu || !rapdu || capdu_len < 4)
		return SCR_INVALID_PARAMETERS;

	// Parse capdu byte array into C_APDU object
	C_APDU o_apdu;
	int res = o_apdu.setApdu (capdu, capdu_len);
	if (res != SCR_SUCCESS)
		return res;

	if ((o_apdu.getINS() & 0xf0) == 0x60 ||
		(o_apdu.getINS() & 0xf0) == 0x90)
	{
		// This is invalid instruction for T=0 protocol.
		// Table 10 of the ISO 7816-4 says that the 6X or 9X values 
		// for the INS byte are invalid.
		return SCR_INVALID_INSTRUCTION_CODE;
	}
	
	// Send command to the card
	byte *resp_header = NULL;
	int resp_len;
	
	// Send Command to the card and receive a response
	res = TransmitCommand (&o_apdu, &resp_header, &resp_len, TransactionToken);
	if (res == SCR_SUCCESS)
	{
		*rapdu = resp_header;
		*rapdu_len = resp_len;
	}
	return res;
}



int  SCRControlImpl::SendCommand (const byte *capdu, 
							      unsigned int capdu_len,
								  const long TransactionToken)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	SCROperationEventImpl *pEvent = (SCROperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	byte *rapdu = NULL;
	unsigned int rapdu_len;

	if ((res = _SendCommand(capdu, capdu_len, 
			&rapdu, &rapdu_len, TransactionToken)) != SUCCESS)
		return pEvent->setError (res, RUNTIME_EXECUTION);
	else
	{	// SUCCESS
		res = pEvent->setByteString (rapdu, rapdu_len);
		delete [] rapdu;
		return res;
	}
}

bool SCRControlImpl::IsInitialized()
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return false;
// 
	return true;
}

int  SCRControlImpl::BeginTransaction (long &TransactionToken)
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return res;

	//Check if the card is inserted
	if (!bCardInserted)
		return SCR_CARD_NOT_PRESENT;

	if (hCardHandle)
	{
		if (TransactionToken == (long)hCardHandle)
			return SUCCESS;
		else
			return SCR_CARD_IN_USE;
	}

	long lReturn;
	DWORD dwAP;
	// Connect to the reader.
	// hContext is a SCARDCONTEXT previously set by 
	// a call to SCardEstablishContext.
	
	lReturn = SCardConnect( hContext, 
							ReaderName,
							SCARD_SHARE_SHARED, //SCARD_SHARE_EXCLUSIVE,
							SCARD_PROTOCOL_T0,
							&hCardHandle,
							&dwAP );
	if ( SCARD_S_SUCCESS != lReturn )
	{
		return SCR_CONNECTION_TO_CARD_FAILED;  // Or other appropriate action.
	}

	// Check the connection protocol. We support only T0 protocol
	if (dwAP != SCARD_PROTOCOL_T0)
	{
		// Disconnect from the card
		SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
		hCardHandle = 0;
		return SCR_CARD_PROTOCOL_NOT_SUPPORTED;
	}

	// Begin a transaction (No application can access a card during our transaction
	lReturn = SCardBeginTransaction(hCardHandle);
	if (lReturn != SCARD_S_SUCCESS)
	{
		SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
		hCardHandle = 0;
		return SCR_FAILED_TO_START_TRANSACTION;	
	}
	TransactionToken = (long)hCardHandle;
	return SUCCESS;
}

void SCRControlImpl::EndTransaction(long &TransactionToken)
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return;

	if (hCardHandle != 0 && (long)hCardHandle == TransactionToken)
	{
		SCardEndTransaction(hCardHandle, SCARD_LEAVE_CARD);
		SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
		hCardHandle = 0;
		TransactionToken = 0;
	}
}

bool SCRControlImpl::IsTransactionAlive(long TransactionToken)
{
	long res = checkInitialization (false);
	if (res != SUCCESS)
		return false;

	if (hCardHandle != 0 && (long)hCardHandle == TransactionToken)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// checkInitialization
// Purpose: Checks if the OperationEvent object is added to the service, and if 
//   the application name is initialized. 
// Returns SUCCESS if everything is initialized.
long SCRControlImpl::checkInitialization (bool checkEvent)
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
/*	
	if (!this->getAccessManager ())
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}
*/
	return SUCCESS;
}



// ---------------------------------------------------------
//
//    U t i l i t y    F u n c t i o n s
//
//----------------------------------------------------------
static void cleanMap()
{
	std::map<UINT_KEY, SCRControlImpl*>::iterator it;
	for (it = Map.begin ();it != Map.end(); it++)
		delete it->second;
	Map.clear ();
}

static SCRControlImpl* getPointer(UINT_KEY key)
{
	MAP::iterator it;
	SCRControlImpl *pScr = NULL;

	it = Map.find(key);
	if (it != Map.end())
	{
		pScr = it->second;
	}

	return pScr;
}



int getReaderName (SCARDCONTEXT hContext, char **name)
{
	#define SCARD_AUTOALLOCATE 10240    //oh dear
	char		buf[SCARD_AUTOALLOCATE];
	LPTSTR          pmszReaders = buf;
	LONG            lReturn;
	DWORD           cch = SCARD_AUTOALLOCATE;
	DWORD dwCurStr; 
	bool ReaderFound;

	// Initialize return parameter to NULL
	*name = NULL;

	// Retreive the name of preffered reader
	LPTSTR pPrefReader = NULL;
	pPrefReader = getPreferredReader();

	// Retrieve the list the readers.
	// hSC was set by a previous call to SCardEstablishContext.
	lReturn = SCardListReaders(hContext,
							   NULL,
							   (LPTSTR)pmszReaders,
							   &cch );
	switch( lReturn )
	{
		case SCARD_S_SUCCESS:
			// A double-null terminates the list of values.
			dwCurStr = 0;
			ReaderFound = false;

			if (pPrefReader)
			{
				ReaderFound = IsPrefReaderFound(pmszReaders, cch, pPrefReader, 
					&dwCurStr);
				if (ReaderFound == false)
				{
					//Requested reader is not found among registered readers
					lReturn = SCR_FAILED_TO_RETREIVE_READER;
				}
			}
			else
			{
				// No preferred reader is specified - use the first reader available
				ReaderFound = true;
				dwCurStr = 0;
			}
			
			if (ReaderFound)
			{
				*name = new char [strlen(pmszReaders + dwCurStr) + 1];
				if (*name != NULL)
				{
					strcpy (*name, pmszReaders + dwCurStr);
					lReturn = SUCCESS;
				}
				else
				{   // Memory allocation error
					lReturn = ERR_MEMORY_ALLOC;
				}
			}
			break;
	default:
			lReturn = SCR_FAILED_TO_RETREIVE_READER;
			break;
	}
	if (pPrefReader)
		delete [] pPrefReader;

	return lReturn;
}

bool IsPrefReaderFound(LPTSTR pmszReaders, DWORD dwBuffSz, LPTSTR pPrefReader, 
					DWORD *dwCurStr)
{
	return true;
}

/**
 * This function originally reads preferred name from registry
 * here for the sake of simplicity return just tge name of our 
 * preferred reader and nothing more 
 * @returns "Gemplus GemPC410 Reader" - the value entered in /etc/reader.conf
 */
LPTSTR getPreferredReader()
{
	// Open a registry key where preferred reader name is located
	LPTSTR lpData = "Gemplus GemPC410 Reader";
	return (LPTSTR) lpData;
}



int TransmitCommand (C_APDU *capdu, byte **rapdu, int *rapdu_len, 
					 const long TransactionToken)
{
	//Check if the card is inserted
	if (!bCardInserted)
		return SCR_CARD_NOT_PRESENT;
	if (hCardHandle == 0)
		return SCR_CARD_NOT_CONNECTED;
	if ((long)hCardHandle != TransactionToken)
		return SCR_CARD_IN_USE;

	C_APDU *send_apdu = capdu;
	long lReturn;
	
	DWORD dwAP;

	BYTE bRecvBuffer [RECEIVER_BUFFER_SIZE];  // A buffer which will contain 
											  // a data received from
											// the card. 
	DWORD dwRecvLength;	       // A length of dRecvBuffer
	bool bTransmit = true; // Controls exit status of the While loop
	BYTE *finalResult = NULL; // Contains a response received from the card
	DWORD finalLen = 0;  // Length of the finalResult buffer
	C_APDU capdu61;      // APDU containing Get Response command

	// Initialize APDU to be a Get Response command
	if ((lReturn = capdu61.setApdu (0x00, 0xC0, 0x00, 0x00, -1, 0, 0)) != 
		SCR_SUCCESS)
	{
		return lReturn;	
	}

	// Extract an APDU class for command APDU header
	int type = (capdu->getApduType () & (APDU_TYPE_COMMAND ^ 0xffffffff));

	bool keepConnection;
	if (hCardHandle)
		keepConnection = true;
	else
	{
		// Connect to the card
		lReturn = SCardConnect( hContext, 
								ReaderName,
								/*SCARD_SHARE_EXCLUSIVE,*/ SCARD_SHARE_SHARED,
								SCARD_PROTOCOL_T0,
								&hCardHandle,
								&dwAP );
		if ( SCARD_S_SUCCESS != lReturn )
		{
			return SCR_CONNECTION_TO_CARD_FAILED;  // Or other appropriate action.
		}

		// Check the connection protocol. We support only T0 protocol
		if (dwAP != SCARD_PROTOCOL_T0)
		{
			// Disconnect from the card
			SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
			return SCR_CARD_PROTOCOL_NOT_SUPPORTED;
		}
	}
	
	// The following two variables keep a current status info
	BYTE sw1 = 0;
	BYTE sw2 = 0;
	DWORD t_apdu_len;
	int loop_cntr = 0; // this counter prevents the terminal to go to the
					   // infinite loop if in response to a Warning Status
					   // ('62xx', or '63xx') the terminal issues GET RESPONSE
					   // command, which, in turn, responses with the same
					   // warning message.

	// Start the loop which implements the Terminal Transport Layer (TTL); 
	// see Book 1 (EMV 2000), Chapter 5.3, page 48. 
	while (bTransmit)
	{
		loop_cntr++;
		dwRecvLength = RECEIVER_BUFFER_SIZE;
		if (send_apdu->getApduType () == (APDU_TYPE_CLASS4 | APDU_TYPE_COMMAND))
		{
			// Command header of the Terminal Transport Layer (TTL) consists of
			// 5-byte header (CLA + INS + P1 + P2 + P3) + data (see EMV book 1,
			// section 5.2.2.2 Command header).
			// APDU header (in a case of case 4 command) consists additional 
			// byte following data - Le which indicates the size of expected
			// data (see EMV book 3, section 2.1 Command APDU format).
			// This additional byte in APDU header must not be conciderd during
			// mapping of APDU to TTL command, therefore we substract one byte
			// from APDU header for case 4 commands (see EMV book 1, 
			// section 5.3.1.1.5 Case 4).
			t_apdu_len = send_apdu->getApduLen () - 1;
		}
		else
			t_apdu_len = send_apdu->getApduLen ();

		// Send command to the card and receive a response
		lReturn = SCardTransmit(
			/*IN*/     hCardHandle,              // Card handle
			/*IN*/     SCARD_PCI_T0,             // Protocol type T=0
			/*IN*/     send_apdu->getApdu (),    // Send buffer
			/*IN*/     t_apdu_len,               // Length in bytes of the header sent to the card
			/*IN OUT*/ NULL,                     // Received control information
			/*OUT*/    bRecvBuffer,              // Received buffer
			/*IN OUT*/ &dwRecvLength             // Length of the received buffer
			);
		if (lReturn != SCARD_S_SUCCESS)
		{   // Error sending command to the card
			lReturn = SCR_FAILED_SENDING_COMMAND;
			break; // break out from the while loop
		}
		apdu_struct rapdu_info;
		int rapdu_type;

		// Parse response APDU received from the card
		lReturn = R_APDU::parseApdu (bRecvBuffer, dwRecvLength, 
									&rapdu_type, &rapdu_info);
		if (lReturn != SCR_SUCCESS)
		{   // Failed to parse data received from the card
			lReturn = SCR_INVALID_RESPONSE_APDU_FORMAT;
			break; // break out from the while loop
		}
		// Do processing of the received data depending on the class of the APDU type
		switch (type)
		{
		case APDU_TYPE_CLASS1:
			// Case 1. Book 1, page 49
			// No Data sent -- No data received
			// On receit of the status from the ICC, the TTL shall discontinue
			// processing of the command. The status is mapped into mandatory 
			// trailer of the R-APDU without change.
			lReturn = appendArr(&finalResult, &finalLen, bRecvBuffer, dwRecvLength);
			bTransmit = false; // Exit While loop
			break; // break from the switch statement
		case APDU_TYPE_CLASS2:
			// Case 2. Book 1, page 49-50, 52-53
			// No Data sent -- Data is received
			// 1) If the first procedure byte (bRecvBuffer[rapdu_info.SW1]) is equal 
			// to '6C', then resend the previous command with 
			// Le = <second procedure byte>.
			// 2) If the first proc. byte is '61', then send GET RESPONSE command header
			// to the card with Le = <second procedure byte>
			// 3) If two proc. bytes are '9000', which indicate success, then
			// return received data and status
			if (bRecvBuffer[rapdu_info.SW1] == 0x90 && 
				bRecvBuffer[rapdu_info.SW2] == 0x00)
			{
				// Success
				lReturn = appendArr(&finalResult, &finalLen, 
									bRecvBuffer, dwRecvLength);
				bTransmit = false; //Exit While Loop
			}
			else if (bRecvBuffer[rapdu_info.SW1] == 0x61)
			{
				// Issue GetResponce command
				if ((lReturn = appendArr (&finalResult, &finalLen, 
									 bRecvBuffer, dwRecvLength)) != SCR_SUCCESS)
				{
					bTransmit = false; // Exit While loop
					break; // exit switch statement
				}
				if ((lReturn = capdu61.updateLe (bRecvBuffer[rapdu_info.SW2])) !=
					SCR_SUCCESS)
				{
					bTransmit = false; // Exit While loop
					break;  // exit switch statement
				}
				send_apdu = &capdu61;
				// Continue going through the While loop
			}
			else if (bRecvBuffer[rapdu_info.SW1] == 0x6C)
			{
				//Resend Previous command with updated length
				send_apdu->updateLe (bRecvBuffer[rapdu_info.SW2]);
			}
			else
			{
				// Error or warning is detected
				lReturn = appendArr (&finalResult, &finalLen, bRecvBuffer, 
									 dwRecvLength);
				bTransmit = false; // Exit While loop
			}
			break;
		case APDU_TYPE_CLASS3:
			// Case 3, Book 1, page 50-51
			// Data is sent -- No data received
			lReturn = appendArr(&finalResult, &finalLen, bRecvBuffer, dwRecvLength);
			bTransmit = false; // Exit While loop
			break;   // exit switch statement
		case APDU_TYPE_CLASS4:
			// Case 4, Book 1, page 51-53
			// Data is sent -- Data is received
			if (bRecvBuffer[rapdu_info.SW1] == 0x90 && 
				bRecvBuffer[rapdu_info.SW2] == 0x00)
			{
				// Success
				if (sw1 != 0 || sw2 != 0)
				{
					bRecvBuffer[rapdu_info.SW1] = sw1;
					bRecvBuffer[rapdu_info.SW2] = sw2;
				}
				lReturn = appendArr(&finalResult, &finalLen, 
									bRecvBuffer, dwRecvLength);
				bTransmit = false; //Exit While Loop
			}
			else if (bRecvBuffer[rapdu_info.SW1] == 0x61)
			{
				// Issue GetResponce command
				if ((lReturn = appendArr (&finalResult, &finalLen, 
									 bRecvBuffer, dwRecvLength)) != SCR_SUCCESS)
				{
					bTransmit = false; // Exit While loop
					break;  // Exit switch statement
				}
				if ((lReturn = capdu61.updateLe (bRecvBuffer[rapdu_info.SW2])) !=
						SCR_SUCCESS)
				{
					bTransmit = false;  // Exit While loop
					break;  // Exit switch statement
				}
				send_apdu = &capdu61;
			}
			else if ( loop_cntr == 1 && 
					  ((bRecvBuffer[rapdu_info.SW1] == 0x62 ||
					   bRecvBuffer[rapdu_info.SW1] == 0x63) || 
					((bRecvBuffer[rapdu_info.SW1] & 0xf0) == 0x90 && 
					((bRecvBuffer[rapdu_info.SW1] & 0x0f) != 0x00 ||
					bRecvBuffer[rapdu_info.SW2] != 0x00))))
			{
				// Issue GetResponce command for status words:
				// '62xx', '63xx', and '9xxx' (except '9000').
				// Reference: EMV Book 1, section 5.3.1.1.4, item 4b.
				if ((lReturn = appendArr (&finalResult, &finalLen, 
									 bRecvBuffer, dwRecvLength)) != SCR_SUCCESS)
				{
					bTransmit = false;  // Exit while loop
					break; // Exit switch statement
				}
				if ((lReturn = capdu61.updateLe (0x00)) != SCR_SUCCESS)
				{
					bTransmit = false;  // Exit while loop
					break;  // Exit switch statement
				}
				send_apdu = &capdu61;
				sw1 = bRecvBuffer[rapdu_info.SW1];
				sw2 = bRecvBuffer[rapdu_info.SW2];
			}
			else if (bRecvBuffer[rapdu_info.SW1] == 0x6C)
			{
				//Resend Previous command with updated length
				send_apdu->updateLe (bRecvBuffer[rapdu_info.SW2]);
			}
			else
			{
				//Error
				lReturn = appendArr (&finalResult, &finalLen, bRecvBuffer, dwRecvLength);
				bTransmit = false; // Exit While loop
			}
			break;
		default:
			bTransmit = false;  // Exit While loop
			lReturn = SCR_INVALID_CAPDU_TYPE;
		}
	}  // While loop

	if (!keepConnection)
	{
		SCardDisconnect(hCardHandle, SCARD_LEAVE_CARD);
		hCardHandle = 0;
	}
	if (lReturn == SCR_SUCCESS)
	{
		*rapdu = finalResult;
		*rapdu_len = finalLen;
	}
	else
	{
		if (finalResult)
			delete [] finalResult;
	}
	return lReturn;
}

int appendArr(byte **finalResult, DWORD *finalLen, 
			   byte *bRecvBuffer, DWORD dwRecvLength)
{
	if (*finalResult == NULL)
	{
		//*finalResult = (byte*)allocateResource (sizeof(byte), dwRecvLength);
		*finalResult = new byte [dwRecvLength];
		if (*finalResult == NULL)
			return SCR_MEMORY_ALLOCATION;
		memcpy(*finalResult, bRecvBuffer, dwRecvLength);
		*finalLen = dwRecvLength;
		return 0;
	}
	else
	{
		*finalLen -= 2; // Do not preserve previously stored procedure bytes
		//byte *tmp = (byte*)allocateResource (sizeof(byte), *finalLen + dwRecvLength);
		byte *tmp = new byte [*finalLen + dwRecvLength];
		if (!tmp)
			return SCR_MEMORY_ALLOCATION;
		memcpy (tmp, *finalResult, *finalLen);
		memcpy (tmp + *finalLen, bRecvBuffer, dwRecvLength);
		//releaseResource ((void**)finalResult);
		delete [] *finalResult;
		*finalResult = tmp;
		*finalLen += dwRecvLength;
		return 0;
	}
}

bool SCRControlImpl::isConnected(){
	//HWND hwnd = (HWND)pArguments;
	LONG            lReturn;
	static bool	initialized = false;
	
	// Establish the context.

	if(!initialized){	
		initialized = true;
		lReturn = SCardEstablishContext(SCARD_SCOPE_SYSTEM,
										NULL,
										NULL,
										&hContext);
		if ( SCARD_S_SUCCESS != lReturn )
		{	
			//_endthreadex(SCR_FAILED_TO_ESTABLISH_CONTEXT);
			printf("%x\n",lReturn);
			return false;
		}
		
		// Find the reader name
		if ((lReturn = getReaderName (hContext, &ReaderName)) != SUCCESS)
		{
			SCardReleaseContext(hContext);
			hContext = (long)NULL;
			//_endthreadex(lReturn);
			return false;
		}
	}
	// Wait for the card to be inserted
	SCARD_READERSTATE rdState;
	rdState.szReader = ReaderName;
	rdState.dwCurrentState = SCARD_STATE_UNAWARE;
	rdState.pvUserData = NULL;


	if ((lReturn = SCardGetStatusChange(
				hContext,
				INFINITE,  // Timeout
				&rdState,
				1  // Number of elememnts in rdState
				)) == SCARD_S_SUCCESS )
	{
		rdState.dwCurrentState = rdState.dwEventState;
		if(rdState.dwEventState & SCARD_STATE_PRESENT){
			//printf("%x\n",rdState.dwEventState);
			bCardInserted = true;
			return true;
		}else{
			bCardInserted = false;
			return false;
		}
	}
	else
	{
		printf("Smart Card reader is not connected! Aborting\n");
		exit(0);
		return false;
	}	
}
