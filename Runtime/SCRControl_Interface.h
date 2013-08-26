// SCRControl Service
// SCRControl Interface Declaration -- Client Side

#ifndef SCRCONTROL_INTERFACE_H
#define SCRCONTROL_INTERFACE_H

#include "ServiceControl.h"
#include "EventAdder.h"
#include "SCRInterface.h"

// Type definition of the pointers to the interface functions.
// Used when the functions are exported from a DLL
typedef int (* ESTABLISHCONNECTION)(UINT_KEY Key);
typedef void (* DESTROYCONNECTION)(UINT_KEY Key);
typedef int (* REGISTEREVENT) (UINT_KEY Key, int eventID, CallBackFunc pEventFunc);
typedef void (* UNREGISTEREVENT) (UINT_KEY Key, int eventID);
typedef int (* SENDCOMMAND)(UINT_KEY Key, 
							const byte *capdu, 
						    unsigned int capdu_len,
							const long TransactionToken);
typedef bool (* ISINITIALIZED)(UINT_KEY Key);
typedef int (* BEGINTRANSACTION)(UINT_KEY Key, long &TransactionToken);
typedef void (* ENDTRANSACTION)(UINT_KEY Key, long &TransactionToken);
typedef bool (*ISTRANSACTIONALIVE)(UINT_KEY Key, long TransactionToken);

class SCRControl_Interface :
	public ServiceControl, 
	public EventAdder, 
	public SCRInterface
{
public:
	SCRControl_Interface(void);
	SCRControl_Interface(const char* path);
	virtual ~SCRControl_Interface(void);

	virtual short getInterfaceType ();
};

#endif

