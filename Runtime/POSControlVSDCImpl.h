// POSControlVSDC
//
// This POSControl implements a demo application the main pupose of which is
// to demonstrate SmartPOS functionality. It implements an EMV and 
// VSDC transactions.
// This POSControl is not intended to run on a real-life terminal. It doesn't
// do any pre- or post- processing. All it does it executes an EMV transaction,
// and returns the result of ether APPROVE or DECLINE. It doesn't perform any
// houskeeping features like saving logs, data capture, sending reversal or
// advise messages and such.

#ifndef POSCONTROLVSDCIMPL_H
#define POSCONTROLVSDCIMPL_H

#include "../EMV_Library/scsEMV.h"
#include "../EMV_Library/Prompter.h"
#include "clcVSDCImpl.h"
#include "POSInterface.h"
#include "POSOperationEventImpl.h"
#include "CLCOperationEventImpl.h"
#include "ServiceControl.h"
#include "amAdder.h"

class POSControlVSDCImpl :
	public EventAdder,
	public OperationEvent,
	public amAdder,
	public ServiceControl
{
public:
	int aid_len;
	byte aid[20];
	POSControlVSDCImpl(const byte *aid, int aid_len);
	virtual ~POSControlVSDCImpl(void);

	// Interface Functions
	// ---------------------------------------------------------------
	virtual int execPOS(byte *fci_data, int fci_len);
	virtual int initPOS (void *Param);
	virtual void resetPOS();
	virtual int getTransData(int Tag, byte *data_value, int *data_sz, 
						     char format[], bool bTransactionDataOnly = true);
	// ----------------------------------------------------------------
private:
	void releaseAM(AccessManager **ppAM);
	int checkInitialization (bool checkEvent = true);
	void outputPOSApplInfo();

	//UIControlInterface UI;
	bool IsEMVProcInProgress;
	bool IsPOSInitialized;
	bool IsFirstTimeExecuted;
	TRANS_STARTUP_PARAMS TransactionParams;
	clcVSDCImpl clcControl;

	int OpenServiceCntrl (ServiceControl *sc);
	void outputDataObject(scsEMV &EMV, int tag, const char *name);

};

#endif
