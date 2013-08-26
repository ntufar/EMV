// AppSelControl Service
// AppSelControl Interface Implementation -- Server Side

#ifndef APPLSELCONTROLIMPL_H
#define APPLSELCONTROLIMPL_H

#include "ApplSelOperationEventImpl.h"
#include "../EMV_Library/ApplSelector.h"
#include "ServiceControl.h"
#include "EventAdder.h"
#include "ApplSelInterface.h"
#include "ApplSelOperationEvent.h"


class ApplSelControlImpl :
        public ServiceControl,
        public EventAdder,
	public amAdder
//        public ApplSelInterface
{
public:
	ApplSelControlImpl(void);
	virtual ~ApplSelControlImpl(void);

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

private: //Private member functions
	long checkInitialization (bool checkEvent = true);

private:
	ApplSelector Selector;
};

#endif

