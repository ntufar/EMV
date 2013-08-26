#include <stdio.h>
#include <string.h>
#include "ServiceInterface_Constants.h"
#include "ServiceControl.h"

ServiceControl::ServiceControl(): 
						pLibPath(NULL), 
						serviceStatus(0 | SERVICE_PATH_SET), 
						extendedError(0),
						ServiceName(0),
						_connectedServices(NULL),
						_open(NULL),
						_close(NULL),
						Key(0)
{
}
ServiceControl::ServiceControl(const char *service_name): 
						pLibPath(NULL), 
						serviceStatus(0 | SERVICE_PATH_SET), 
						extendedError(0),
						_connectedServices(NULL),
						_open(NULL),
						_close(NULL),
						Key(0)
{
	if (service_name)
	{
		ServiceName = new char [strlen (service_name) + 1];
		strcpy (ServiceName, service_name);
	}
	else
		ServiceName = 0;
}

ServiceControl::ServiceControl(const char *service_name, const char* pPath): 
						pLibPath(NULL), 
						serviceStatus(0), 
						extendedError(0),
						_connectedServices(NULL),
						_open(NULL),
						_close(NULL),
						Key(0)
{
	setPath (pPath);
	extendedError = SERVICE_SUCCESS;
	if (service_name)
	{
		ServiceName = new char [strlen (service_name) + 1];
		strcpy (ServiceName, service_name);
	}
	else
		ServiceName = 0;
}

ServiceControl::~ServiceControl(void)
{
	if (pLibPath)
	{
		delete [] pLibPath;
		pLibPath = NULL;
	}
	serviceStatus = SERVICE_SUCCESS;
	extendedError = SERVICE_SUCCESS;
	if (ServiceName)
	{
		delete [] ServiceName;
		ServiceName = 0;
	}
}

int ServiceControl::setPath(const char* pPath)
{
	// Check if the service is already opened and return SERVICE_BUSY if it is.
	if (opened())
		return SERVICE_BUSY;

	extendedError = SERVICE_SUCCESS;
	serviceStatus = resetBit (serviceStatus, SERVICE_ERROR);
	serviceStatus = resetBit (serviceStatus, SERVICE_PATH_SET);

	// Check if the path is already set. If it is, then remove the old path.
	if (pLibPath)
	{
		delete [] pLibPath;
		pLibPath = NULL;
	}

	//Check if the new path is not null. If it is then set error condition and exit
	if (pPath)
	{
		pLibPath = new char [strlen(pPath) + 1];
		// Check if memory is successfully allocated. If not then set the error condition.
		if (!pLibPath)
		{
			serviceStatus = setBit (serviceStatus, SERVICE_ERROR);
			return ERR_MEMORY_ALLOC;
		}
		else
		{
			// Set the new path
			strcpy(pLibPath, pPath);
			serviceStatus = setBit (serviceStatus, SERVICE_PATH_SET);
			return SUCCESS;
		}
	}
	else
	{
		serviceStatus = setBit (serviceStatus, SERVICE_ERROR);
		return ERR_BAD_ARGUMENT;
	}
}

int ServiceControl::getServiceStatus(void)
{
	return serviceStatus;
}


int ServiceControl::open(AccessManager *am)
{
	if (opened())
		return SERVICE_BUSY;

	if (!initialized())
		return SERVICE_ERR_NOT_INITIALIZED;

	resetBit (serviceStatus, SERVICE_ERROR);

	extendedError = openService (am);
	if (extendedError == SUCCESS)
	{
		serviceStatus = setBit (serviceStatus, SERVICE_OPENED);
		return SUCCESS;
	}
	else
	{
		serviceStatus = setBit (serviceStatus, SERVICE_ERROR);
		return extendedError;
	}
}

void ServiceControl::close()
{
	closeService();
	serviceStatus = resetBit (serviceStatus, SERVICE_OPENED);
}

int ServiceControl::getExtendedError()
{
	return extendedError;
}
bool ServiceControl::initialized(void)
{
	return (serviceStatus & SERVICE_PATH_SET) != 0;
}

bool ServiceControl::opened(void)
{
	return (serviceStatus & SERVICE_OPENED) != 0;
}

bool ServiceControl::success(void)
{
	return (serviceStatus & SERVICE_ERROR) == 0;
}

int ServiceControl::setBit(const int  status, const int mask)
{
	return (status | mask);
}

int ServiceControl::resetBit(const int status, const int mask)
{
	return (status & (~mask));
}

void ServiceControl::setServiceName (const char* pServName)
{
	if (ServiceName)
	{
		delete [] ServiceName;
		ServiceName = 0;
	}

	if (!pServName)
		return;

	ServiceName = new char [strlen (pServName) + 1];
	strcpy (ServiceName, pServName);
}

char* ServiceControl::getServiceName()
{
	return ServiceName;
}


short ServiceControl::getInterfaceType()
{
	return INTERFACE_TYPE_CLC;   //NT: ????
}

void ServiceControl::closeService()
{
}

int ServiceControl::openService(AccessManager* am)
{
	return SUCCESS;
}
