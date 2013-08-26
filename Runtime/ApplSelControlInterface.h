// AppSelControl Service
// AppSelControl Interface Implementation -- Client Side

#ifndef APPLSELCONTROLINTERFACE_H
#define APPLSELCONTROLINTERFACE_H

#include "ApplSelOperationEventImpl.h"
#include "patch.h"

typedef int (* EMV_APPLICATIONSELECTION)(UINT_KEY Key, long TransactionToken = 0);
typedef int (* BUILDTERMINALAPPLLIST)(UINT_KEY Key);
typedef int (* INITIALIZE)(UINT_KEY Key);
typedef int (* SELECTAPPLICATION)(UINT_KEY Key, long TransactionToken, 
								  byte *AID, int aid_len);
typedef int (* EMV_SELECTNEXT)(UINT_KEY Key);
typedef int (* CANCELTRANSACTION)(UINT_KEY Key);


class ApplSelControlInterface 
{
public:
	ApplSelControlInterface(void);
	ApplSelControlInterface(const char* path);
	virtual ~ApplSelControlInterface(void);

	virtual unsigned int connectedServices ();

// Implements EMV's Application Selection process.
	// If card support PSE method it is used first, otherwise List-Of-Directories
	// method is used.
	// Populates EventObject with the value returned by the card to the Select
	// command to select chosen application
	virtual int EMV_ApplicationSelection(long TransactionToken = 0);

	// Build a list of applications supported by the terminal. Must be executed
	// prior calling EMV_ApplicationSelection method
	virtual int BuildTerminalApplList();

	// Initializes (opens) the services used in Application Selection processing.
	virtual int Initialize();

	// Selects an application based on AID passed as a parameter
	virtual int SelectApplication(long TransactionToken, byte *AID, int aid_len);

	// application cannot be executed.
	virtual int EMV_SelectNext();

	// Externally cancels a transaction. Used for example to terminate 
	// an Application Selection process when the card is removed from 
	// the Card Reader slot.
	virtual int CancelTransaction();


protected:
	virtual void closeService(void);

private:
	HINSTANCE hDLL;
	EMV_APPLICATIONSELECTION _EMV_ApplicationSelection;
	BUILDTERMINALAPPLLIST _BuildTerminalApplList;
	INITIALIZE _Initialize;
	SELECTAPPLICATION _SelectApplication;
	EMV_SELECTNEXT _EMV_SelectNext;
	CANCELTRANSACTION _CancelTransaction;
};

#endif

