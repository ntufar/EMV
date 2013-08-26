// SystemControl Service
// SystemControl Interface Implementation -- Client Side

#ifndef SYSTEMCONTROLINTERFACE_H
#define SYSTEMCONTROLINTERFACE_H

#include "SystemControl_Interface.h"
#include "SystemOperationEventImpl.h"
#include "patch.h"


class SystemControlInterface :
	public SystemControl_Interface
{
public:
	SystemControlInterface(void);
	SystemControlInterface(const char* path);
	virtual ~SystemControlInterface(void);

	virtual int retreiveDate();
	virtual int retreiveDateEx(DateStruct *date);
	
	virtual int openFile (const char* pathname, int flags, int *fd);
	virtual int writeFile (int fd, const char* buf, UNINT count,
		int flags);
	virtual int readFile (int fd, UNINT count, int flags);
	virtual int closeFile (int fd);

	virtual unsigned int connectedServices ();
protected:
	virtual int openService(AccessManager* am);
	virtual void closeService(void);

private:
	HINSTANCE hDLL;               // Handle to DLL

	RETREIVEDATE _retreiveDate;
	RETREIVEDATEEX _retreiveDateEx;
	OPENFILE _openFile;
	WRITEFILE _writeFile;
	READFILE _readFile;
	CLOSEFILE _closeFile;
};

#endif

