// CLCControl Service
// CLCControl Interface Implementation -- Client Side.

#ifndef CLCCONTROLINTERFACE_H
#define CLCCONTROLINTERFACE_H

#include "CLCControl_Interface.h"
#include "CLCOperationEventImpl.h"
#include "patch.h"

class CLCControlInterface :
	public CLCControl_Interface
{
public:
	CLCControlInterface(const char *clcName);
	CLCControlInterface(const char *clcName, const char *path);
	virtual ~CLCControlInterface(void);
	
	// ----- I N T E R F A C E    F U N C T I O N S ---------
	// Initializes CLC module by setting initial parameters, openning 
	// the services, ets.
	virtual int initCLC (void *Param);
	// Resets CLC module by setting it to the initial state
	virtual void resetCLC();
	// Retreive data element from the CLC Context
	virtual int getTransData(int Tag, byte *data_value, int *data_sz, 
						     char format[], bool bTransactionDataOnly = true);

	// ----- O P E R A T I O N   E V E N T   A D D E R    F U N C T I O N S
	virtual int addOperationEvent(OperationEvent *pOpEvent);
	virtual void removeEvent ();
	virtual bool eventAttached();

	virtual unsigned int connectedServices ();

protected:
	// Service control functions
	virtual int openService(AccessManager* am);
	virtual void closeService(void);

protected:
	HINSTANCE hDLL;               // Handle to DLL
	INITCLC _initCLC;
	RESETCLC _resetCLC;
	GETTRANSDATA _getTransData;
};

#endif

