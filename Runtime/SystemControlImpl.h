// SystemControl Service
// SystemControl Interface Implementation -- Server Side

#ifndef SYSTEMCONTROLIMPL_H
#define SYSTEMCONTROLIMPL_H
#include "SystemControl_Server.h"
#include "SystemOperationEventImpl.h"
#include "ServiceControl.h"
#include "EventAdder.h"
#include "ServiceControl.h"
#include "ServiceControl.h"
#include "amAdder.h"


//#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


// This class derives from the SystemControl_Server interface of SystemContol.lib
// library, and must provide implementation for all interface functions. For 
// SystemControl interface only one interface function is defined - retreiveDate.
// This is an implementation of the interface defined in SystemContol.lib.
class SystemControlImpl :
	public EventAdder, 
	public SystemInterface,
        public OperationEvent,
        public amAdder,
        public ServiceControl
{
public:
	SystemControlImpl(void);
	virtual ~SystemControlImpl(void);
	
	//Interface methods
	virtual int retreiveDate(void);
	virtual int retreiveDateEx(DateStruct *date);

	virtual int openFile (const char* pathname, int flags, int *fd);
	virtual int writeFile (int fd, const char* buf, UNINT count, 
		int flags);
	virtual int readFile (int fd, UNINT count, int flags);
	virtual int closeFile (int fd);

private:
	int setIOflag (int scs_flag, int *std_flag);
	int mapError(int err);
	int readOneLine(int fd, SystemOperationEventImpl *pEvent);
	int readAllFile(int fd, SystemOperationEventImpl *pEvent);
	int readBytes(int fd, UNINT count, SystemOperationEventImpl *pEvent);
};

#endif
