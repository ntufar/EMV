#include <stdio.h>
#include "SCRControlInterface.h"

SCRControlInterface::SCRControlInterface(void):
	//hDLL(NULL),
	_EstablishConnection(NULL),
	_DestroyConnection(NULL),
	_RegisterEvent(NULL),
	_UnRegisterEvent(NULL),
	_SendCommand(NULL),
	_IsInitialized(NULL),
	_BeginTransaction(NULL),
	_EndTransaction(NULL),
	_IsTransactionAlive(NULL)
{
}

SCRControlInterface::SCRControlInterface(const char *path):
	SCRControl_Interface(path),
	//hDLL(NULL),
	_EstablishConnection(NULL),
	_DestroyConnection(NULL),
	_RegisterEvent(NULL),
	_UnRegisterEvent(NULL),
	_SendCommand(NULL),
	_IsInitialized(NULL),
	_BeginTransaction(NULL),
	_EndTransaction(NULL),
	_IsTransactionAlive(NULL)
{
}

SCRControlInterface::~SCRControlInterface(void)
{
	closeService();
}


int SCRControlInterface::openService(AccessManager* am)
{
	//System dependent loading of the DLL where server is implemented
	//hDLL = LoadLibrary(pLibPath);
	if (!hDLL)
	{
		//Error loading the library
		return ERR_LOADING_LIBRARY; 
	}
	
	//Check the presence of all the functions in a library

	
// Interface Functions
	//_EstablishConnection = (ESTABLISHCONNECTION)GetProcAddress(hDLL, "EstablishConnection");
	if (!_EstablishConnection)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	
	//_DestroyConnection = (DESTROYCONNECTION)GetProcAddress(hDLL, "DestroyConnection");
	if (!_DestroyConnection)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_RegisterEvent = (REGISTEREVENT)GetProcAddress(hDLL, "RegisterEvent");
	if (!_RegisterEvent)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_UnRegisterEvent = (UNREGISTEREVENT)GetProcAddress(hDLL, "UnRegisterEvent");
	if (!_UnRegisterEvent)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_SendCommand = (SENDCOMMAND)GetProcAddress(hDLL, "SendCommand");
	if (!_SendCommand)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_IsInitialized = (ISINITIALIZED)GetProcAddress(hDLL, "IsInitialized");
	if (!_IsInitialized)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_BeginTransaction = (BEGINTRANSACTION)GetProcAddress(hDLL, "BeginTransaction");
	if (!_BeginTransaction)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_EndTransaction = (ENDTRANSACTION)GetProcAddress(hDLL, "EndTransaction");
	if (!_EndTransaction)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_IsTransactionAlive = (ISTRANSACTIONALIVE)GetProcAddress(hDLL, "IsTransactionAlive");
	if (!_IsTransactionAlive)
	{
		//Handle he error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

// Access Manager related functions
	//_connectedServices = (CONNECTEDSERVICES)GetProcAddress (hDLL, "connectedServices");
	if (!_connectedServices)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_close = (CLOSE)GetProcAddress(hDLL, "close");
	if (!_close)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_open = (OPEN)GetProcAddress(hDLL, "open");
	if (!_open)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	// Open the service
	return _open (am, &Key);
}

void SCRControlInterface::closeService(void)
{
	if (hDLL)
	{
		if (_close)
			_close(&Key);
		//FreeLibrary(hDLL);
	}
	
	//hDLL = NULL;

	
	// Interface functions
	_EstablishConnection = NULL;
	_DestroyConnection = NULL;
	_RegisterEvent = NULL;
	_SendCommand = NULL;
	_IsInitialized = NULL;
	_BeginTransaction = NULL;
	_EndTransaction = NULL;
	_IsTransactionAlive = NULL;

	// Access Manager related functions
	_connectedServices = NULL;
	_open = NULL;
	_close = NULL;
}

unsigned int SCRControlInterface::connectedServices ()
{
	if(!_connectedServices)
		return ERR_SERVICE_NOT_CONNECTED; 	
	return _connectedServices();
}


int  SCRControlInterface::EstablishConnection ()
{
	if (!_EstablishConnection)
		return ERR_SERVICE_NOT_CONNECTED;

	return _EstablishConnection(Key);
}

void SCRControlInterface::DestroyConnection ()
{
	if (!_DestroyConnection)
		return;

	_DestroyConnection(Key);
}

int  SCRControlInterface::RegisterEvent (/*[IN]*/int eventID, 
						/*[IN]*/CallBackFunc pEvent)
{
	if (!_RegisterEvent)
		return ERR_SERVICE_NOT_CONNECTED;

	return _RegisterEvent(Key, eventID, pEvent);
}

void  SCRControlInterface::UnRegisterEvent (/*[IN]*/int eventID)
{
	if (!_UnRegisterEvent)
		return;

	_UnRegisterEvent(Key, eventID);
}

int  SCRControlInterface::SendCommand (/*[IN]*/const byte *capdu, 
						/*[IN]*/unsigned int capdu_len,
						const long TransactionToken)
{
	if (!_SendCommand)
		return ERR_SERVICE_NOT_CONNECTED;

	return _SendCommand(Key, capdu, capdu_len, TransactionToken);
}

bool SCRControlInterface::IsInitialized()
{
	if (!_IsInitialized)
		return false;

	return _IsInitialized(Key);
}

int SCRControlInterface::BeginTransaction(long &TransactionToken)
{
	if (!_BeginTransaction)
		return ERR_SERVICE_NOT_CONNECTED;

	return _BeginTransaction(Key, TransactionToken);
}

void SCRControlInterface::EndTransaction(long &TransactionToken)
{
	if (!_EndTransaction)
		return;

	_EndTransaction(Key, TransactionToken);
}

bool SCRControlInterface::IsTransactionAlive(long TransactionToken)
{
	if (!_IsTransactionAlive)
		return false;

	return _IsTransactionAlive(Key, TransactionToken);
}

