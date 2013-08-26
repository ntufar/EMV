
#ifndef SERVICECONTROL_H
#define SERVICECONTROL_H

#include "errors.h"
#include "custom_types.h"
#include "projects.h"
#include "ServiceControlModules.h"

// Functions where errors are detected
//#define SERVICECONTROL_SETPATH 0x00
//#define SERVICECONTROL_OPEN    0x01


// Service Status Codes
#define SERVICE_PATH_SET            0x00000001
#define SERVICE_OPENED              0x00000002
#define SERVICE_ERROR               0x80000000

// Service Return Codes
#define SERVICE_SUCCESS             0x00000000
#define SERVICE_ERR_OPEN_FAILED     0x80000001
#define SERVICE_BUSY                0x80000002
#define SERVICE_ERR_NOT_INITIALIZED 0x80000003

class AccessManager;

typedef UINT_KEY (* OPEN)(AccessManager *am,
						  UINT_KEY *Key);
typedef int (* OPENPOS)(AccessManager *am,
							 const byte *aid,
							 int aid_len,
						     UINT_KEY *Key);
typedef unsigned int (* CONNECTEDSERVICES)(); 
typedef int (* CLOSE) (UINT_KEY *key);

class ServiceControl
{
public:
	friend class AccessManager;
	ServiceControl();
	ServiceControl(const char *service_name);
	ServiceControl(const char *service_name, const char* pPath);
	virtual ~ServiceControl(void);

// Call these 2 functions to open and close the service
//---------------------------------------------------
	virtual int open(AccessManager* am);
	virtual void close();
//---------------------------------------------------

    int setPath(const char* pPath);

	int getServiceStatus(void);
	int getExtendedError();
	
	bool initialized(void);
	bool opened(void);
	bool success(void);

	char* getServiceName();
	
// Bizim eklediğimiz
	short getInterfaceType () ;
	void setServiceName (const char* pServName);
protected:
// Provide implementation of these 2 functions.
// -------------------------------------------
//böyleyken:
	//virtual int openService(AccessManager* am);
	//virtual void closeService() ;

//böyle oldu:
	int openService(AccessManager* am);
	void closeService() ;
// -------------------------------------------


	char* pLibPath;
	int errorInfo;
	char *ServiceName;

private:
	int setBit(const int status, const int mask);
	int resetBit(const int status, const int mask);

	// keeps the current status of the service
	int serviceStatus;

	// keeps an error code resulted from the execution of service opening
	int extendedError;

protected:
	CONNECTEDSERVICES _connectedServices;
	OPEN _open;
	OPENPOS _openPos;
	CLOSE _close;
	UINT_KEY Key;
};

#else
#endif

