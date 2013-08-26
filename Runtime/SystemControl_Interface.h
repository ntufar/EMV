// SystemControl Service
// SystemControl Interface Declaration -- Client Side

#ifndef SYSTEMCONTROL_INTERFACE_H
#define SYSTEMCONTROL_INTERFACE_H

#include "ServiceControl.h"
#include "EventAdder.h"
#include "SystemInterface.h"
#include "SystemOperationEvent.h"

// Type definition of the pointer to the interface function.
// Is used when the function is exported from a DLL
typedef int (* RETREIVEDATE)(UINT_KEY key);
typedef int (* RETREIVEDATEEX) (UINT_KEY key, DateStruct *ds);
typedef int (* OPENFILE) (UINT_KEY key, const char* pathname, 
						  int flags, int *fd);
typedef int (* WRITEFILE) (UINT_KEY key, int fd, 
						   const char* buf, UNINT count, int flags);
typedef int (* READFILE) (UINT_KEY key, int fd, UNINT count, int flags);
typedef int (* CLOSEFILE) (UINT_KEY key, int fd);

class SystemControl_Interface :
	public ServiceControl, public EventAdder, public SystemInterface
{
public:
	SystemControl_Interface(void);
	SystemControl_Interface (const char* path);
	virtual ~SystemControl_Interface(void);
	virtual short getInterfaceType ();
};

#endif

