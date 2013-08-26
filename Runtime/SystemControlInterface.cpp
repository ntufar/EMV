#include <stdio.h>
#include "SystemControlInterface.h"

SystemControlInterface::SystemControlInterface(void) : 
	hDLL(NULL),
	_retreiveDate(NULL),
	_retreiveDateEx(NULL)
{
}

SystemControlInterface::SystemControlInterface(const char* path): 
	SystemControl_Interface(path),
	hDLL(NULL),
	_retreiveDate(NULL),
	_retreiveDateEx(NULL)
{
}

SystemControlInterface::~SystemControlInterface(void)
{
	closeService();
}

int SystemControlInterface::openService(AccessManager* am)
{
	//Check the presence of all functions in a library
	//_retreiveDate = (RETREIVEDATE)GetProcAddress(hDLL, "retreiveDate");
	if (!_retreiveDate)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_retreiveDateEx = (RETREIVEDATEEX)GetProcAddress(hDLL, "retreiveDateEx");
	if (!_retreiveDateEx)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_openFile = (OPENFILE)GetProcAddress(hDLL, "openFile");
	if (!_openFile)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_writeFile = (WRITEFILE)GetProcAddress(hDLL, "writeFile");
	if (!_writeFile)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_readFile = (READFILE)GetProcAddress(hDLL, "readFile");
	if (!_readFile)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}
	//_closeFile = (CLOSEFILE)GetProcAddress(hDLL, "closeFile");
	if (!_closeFile)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}


	//_connectedServices = (CONNECTEDSERVICES)GetProcAddress (hDLL, "connectedServices");
	if (!_connectedServices)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_close = (CLOSE)GetProcAddress(hDLL, "scs_close");
	if (!_close)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	//_open = (OPEN)GetProcAddress(hDLL, "scs_open");
	if (!_open)
	{
		// handle the error
		closeService();
		return ERR_INCOMPATIBLE_INTERFACE;
	}

	return _open (am, &Key);
}

void SystemControlInterface::closeService(void)
{
	if (hDLL)
	{
		if (_close)
			_close(&Key);
	}
	hDLL = NULL;
	_retreiveDate = NULL;
	_retreiveDateEx = NULL;
	_openFile = NULL;
	_writeFile = NULL;
	_readFile = NULL;
	_closeFile = NULL;

	_connectedServices = NULL;
	_open = NULL;
	_close = NULL;
}

unsigned int SystemControlInterface::connectedServices ()
{
	if(!_connectedServices)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _connectedServices();
}


int SystemControlInterface::retreiveDate(void)
{
	if (!_retreiveDate)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _retreiveDate(Key);
}

int SystemControlInterface::retreiveDateEx(DateStruct *date)
{
	if (!_retreiveDateEx)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _retreiveDateEx(Key, date);
}

int SystemControlInterface::openFile(const char* pathname, 
									 int flags, int *fd)
{
	if (!_openFile)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _openFile(Key, pathname, flags, fd);
}

int SystemControlInterface::writeFile(int fd, 
									  const char* buf, 
									  UNINT count,
									  int flags)
{
	if (!_writeFile)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _writeFile(Key, fd, buf, count, flags);
}

int SystemControlInterface::readFile(int fd, UNINT count, int flags)
{
	if (!_readFile)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _readFile(Key, fd, count, flags);
}

int SystemControlInterface::closeFile(int fd)
{
	if (!_closeFile)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _closeFile(Key, fd);
}
