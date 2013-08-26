// SCRControl Service
// SCRControl Interface Implementation -- Client Side

#ifndef SCRCONTROLINTERFACE_H
#define SCRCONTROLINTERFACE_H


#include "SCRControl_Interface.h"
#include "SCROperationEventImpl.h"

class SCRControlInterface :
	public SCRControl_Interface
{
public:
	SCRControlInterface(void);
	SCRControlInterface(const char* path);

	virtual ~SCRControlInterface(void);

// Interface methods

	virtual unsigned int connectedServices ();

// Smart Card Reader interface functions
	virtual int  EstablishConnection ();
	virtual void DestroyConnection ();
	virtual int  RegisterEvent (int eventID, 
								CallBackFunc pEvent); 
	virtual void  UnRegisterEvent (int eventID);
	virtual int  SendCommand (const byte *capdu, 
							 unsigned int capdu_len,
							 const long TransactionToken);
    virtual bool IsInitialized();
	virtual int BeginTransaction(long &TransactionToken);
	virtual void EndTransaction(long &TransactionToken);
	virtual bool IsTransactionAlive(long TransactionToken);

// Access Manager related functions
protected:
	virtual int openService(AccessManager* am);
	virtual void closeService(void);

private:
	int hDLL;               // Handle to DLL
	ESTABLISHCONNECTION _EstablishConnection;
	DESTROYCONNECTION _DestroyConnection;
	REGISTEREVENT _RegisterEvent;
	UNREGISTEREVENT _UnRegisterEvent;
	SENDCOMMAND _SendCommand;
	ISINITIALIZED _IsInitialized;
	BEGINTRANSACTION _BeginTransaction;
	ENDTRANSACTION _EndTransaction;
	ISTRANSACTIONALIVE _IsTransactionAlive;

};

#endif

