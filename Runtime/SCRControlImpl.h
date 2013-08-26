// SCRControl Service
// SCRControl Interface Implementation -- Server Side
//
// This service implements a Smart Card Reader interface. It uses PC/SC API 
// to communicate with a card.
// Services is built by using three threads.
// 1. Main thread - Dll entry function, Window Procedure
// 2. hWndThread - a thread that creates a message window. This window is used
//    to send / reeive message from other threads
// 3. hEventThread - Event tracker thread. This threads waits for a ststus change 
//    in a reader, and as soon as the status is changed, it sends a message to 
//    the Message Window.
// Before sending any command to the card inserted in a reader, connection
//	  must be established between reader and the DLL (EstablishConnection).
// To catch OnInsert and OnRemove events, a call back functions implemented
// this events must be defined in the caller and registered with the control.

#ifndef SCRCONTROLIMPL_H
#define SCRCONTROLIMPL_H

#include "SCROperationEventImpl.h"
#include "SCRInterface.h"
#include "EventAdder.h"
#include "ServiceControl.h"
#include "amAdder.h"

#define RECEIVER_BUFFER_SIZE 258 // 256 (max data size) + 2 (SW1 SW2)


class SCRControlImpl:
	public EventAdder,
	public OperationEvent,
	public amAdder,
	public ServiceControl
{
public:
	SCRControlImpl();
	virtual ~SCRControlImpl(void);

// Smart Card Reader interface functions
	bool isConnected();
	virtual int  EstablishConnection ();
	virtual void DestroyConnection ();
	virtual int  RegisterEvent (int eventID, CallBackFunc pEventFunc); 
	virtual void  UnRegisterEvent (int eventID);
	virtual int  SendCommand (const byte *capdu, 
							 unsigned int capdu_len,
							 const long TransactionToken);
	virtual bool IsInitialized();
	virtual int BeginTransaction(long &TransactionToken);
	virtual void EndTransaction(long &TransactionToken);
	virtual bool IsTransactionAlive(long TransactionToken);

	void FireEvent (int eventID);
	bool IsEventRegistered(int EventID);

private: //Private member functions
	long checkInitialization (bool checkEvent = true);

// Private members
	CallBackFunc pOnInsertFunc;
	CallBackFunc pOnRemoveFunc;
	int OnInsertMutex;
	int OnRemoveMutex;
	
};

#endif

