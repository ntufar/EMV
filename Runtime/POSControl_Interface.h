// POSControl Service
// POSControl Interface Declaration -- Client Side

#ifndef POSCONTROL_INTERFACE_H
#define POSCONTROL_INTERFACE_H

#include "ServiceControl.h"
#include "EventAdder.h"
#include "POSInterface.h"

// Type definition of the pointer to the interface function.
// Is used when the function is exported from a DLL
typedef int (* EXECPOS)(UINT_KEY key, byte *fci_data, int fci_len);
typedef int (* INITPOS )(UINT_KEY key, void *Param);
typedef int (* RESETPOS)(UINT_KEY key);
typedef int (* GETTRANSDATA)( UINT_KEY key, int Tag, byte *data_value, 
							 int *data_sz, char format[], bool bTransactionDataOnly = true);

typedef int (* CLOSEPOS) (UINT_KEY *key);

class POSControl_Interface:
	public ServiceControl, 
	public EventAdder, 
	public POSInterface
{
public:
	POSControl_Interface(const byte *aid, int aid_len);
	POSControl_Interface (const byte *aid, int aid_len, const char* path);
	virtual ~POSControl_Interface(void);

	virtual short getInterfaceType ();
};

#endif

