// AppSelControl Service
// AppSelControl Interface Declaration.
//
// Implements Application Selection procedures according to EMV specification
// Reference: EMV 4.0 book 1, Part II.
#ifndef APPLSELINTERFACE_H
#define APPLSELINTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"
#include "errors.h"

class ApplSelInterface :
	public ServiceInterface
{
public:
	ApplSelInterface(void);
	virtual ~ApplSelInterface(void);

	// Implements EMV's Application Selection process.
	// If card support PSE method it is used first, otherwise List-Of-Directories
	// method is used.
	// Populates EventObject with the value returned by the card to the Select
	// command to select chosen application
	virtual int EMV_ApplicationSelection(long TransactionToken = 0) = 0;

	// Selects next available application out of the common applications
	// selected by call to EMV_ApplicationSelection if currently selected
	// application cannot be executed.
	virtual int EMV_SelectNext() = 0;

	// Build a list of applications supported by the terminal. Must be executed
	// prior calling EMV_ApplicationSelection method
	virtual int BuildTerminalApplList() = 0;

	// Initializes (opens) the services used in Application Selection processing.
	virtual int Initialize() = 0;

	// Selects an application based on AID passed as a parameter
	virtual int SelectApplication(long TransactionToken, 
								  byte *AID, int aid_len) = 0;

	// Externally cancels a transaction. Used for example to terminate 
	// an Application Selection process when the card is removed from 
	// the Card Reader slot.
	virtual int CancelTransaction() = 0;
};

#endif

