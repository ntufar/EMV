// SCRControl Service
// SCRControl Interface Declaration.
//
// Defines an interface to the Smart Card Reader.

#ifndef SRCINTERFACE_H
#define SRCINTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"

// Events ID
#define ONINSERT 1
#define ONREMOVE 2

// Errors
#define SCR_INVALID_EVENT_ID             0x70000001
#define SCR_CARD_NOT_PRESENT             0x70000002
#define SCR_INVALID_APDU_CLASS           0x70000003
#define SCR_INVALID_PARAMETERS           0x70000004
#define SCR_CONNECTION_TO_CARD_FAILED    0x70000005
#define SCR_CARD_PROTOCOL_NOT_SUPPORTED  0x70000006
#define SCR_FAILED_TO_START_TRANSACTION  0x70000007
#define SCR_FAILED_SENDING_COMMAND       0x70000008
#define SCR_INVALID_RESPONSE_APDU_FORMAT 0x70000009
#define SCR_INVALID_CAPDU_TYPE           0x7000000A
#define SCR_MEMORY_ALLOCATION            0x7000000B
#define SCR_NO_READERS_AVAILABLE         0x7000000C
#define SCR_FAILED_TO_RETREIVE_READER    0x7000000D
#define SCR_FAILED_TO_ESTABLISH_CONTEXT  0x7000000E
#define SCR_INITIALIZATION_ERROR         0x7000000F
#define SCR_CARD_IN_USE                  0x70000010
#define SCR_CARD_NOT_CONNECTED           0x70000011
#define SCR_TRANSACTION_DISCONTINUED     0x70000012
#define SCR_INVALID_INSTRUCTION_CODE     0x70000013

#define SCR_SUCCESS 0

//CALLBACK function definition
typedef void (* CallBackFunc)();


class SCRInterface :
	public ServiceInterface
{
public:
	SCRInterface(void);
	virtual ~SCRInterface(void);

	// Interface Functions
	// -----------------------------------------------------
	// Establishes control with the Smart Card Reader service, such that the
	// service is ready to fire events notifying of the Smart Card Reader
	// status change (e.g. card insert or remove events)
	virtual int  EstablishConnection () = 0;

	// Destroys connection with the Smart Card Reader
	virtual void DestroyConnection () = 0;

	// Register a callback function to be executed when the eventID will fire
	virtual int  RegisterEvent (int eventID, 
								CallBackFunc pEvent) = 0;
	// Unregisters an event (callback function will not be executed anymore)
	virtual void  UnRegisterEvent (int eventID) = 0;

	// Sends command to a Smart Card inserted into the Smart Card Reader slot
	virtual int  SendCommand (const byte *capdu, 
							  unsigned int capdu_len,
							  const long TransactionToken) = 0;

	// Checks if the connection is established with the Smart Card Reader
    virtual bool IsInitialized() = 0;

	// Connects to the Smart Card inserted into the reader and begins a new 
	// transaction.
	// TransactionToken is initialized to the value to be used for all requests
	// sent to the card within this transaction
	virtual int BeginTransaction(long &TransactionToken) = 0;

	// Ends a transaction by disconnecting from the card and setting 
	// TransactionToken to '0'
	virtual void EndTransaction(long &TransactionToken) = 0;
	virtual bool IsTransactionAlive(long TransactionToken) = 0;
};

#endif

