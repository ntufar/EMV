#ifndef xCLCVSDCIMPL_H
#define xCLCVSDCIMPL_H

#include "clcVSDC_constants.h"
#include "../EMV_Library/scsEMV.h"
#include "../EMV_Library/Prompter.h"
#include "CLCOperationEvent.h"
#include "EventAdder.h"
#include "amAdder.h"

class clcVSDCImpl :
	public EventAdder,
	public amAdder
{
public:
	clcVSDCImpl(void);
	virtual ~clcVSDCImpl(void);

	virtual int initCLC (void *Param);
	// Resets CLC module by setting it to the initial state
	virtual void resetCLC();

	// Retrieves a value of the data specified by the Tag for a completed 
	// transaction.
	// Parameters:
	//	Tag - a tag of the data object the value of which is to return
	//	data_value - a buffer where data value is to be copied.
	//	data_sz - a size of the input buffer data_value
	//  format - an array of size 4 to keep the EMV format value (e.g. "n", "cn", ets.)
	//	bTransactionDataOnly - a flag which specifies the following:
	//		true - return data used in EMV transaction
	//		false - if data was not used during EMV transaction, try to find it
	//		in the storage (e.g. Registry)
	// Returns:
	//	SUCCESS - operation completed successfully, data_value is populate with 
	//			the value, data_sz is set to the number of bytes in the actual 
	//			data.
	//	ERR_BUFFER_OVERFLOW - data_value buffer is too small to keep the
	//			found value. The data_sz is set to the size of the buffer
	//			required to keep the value.
	//  TAG_NOT_FOUND - value is not found
	//  Error code - some runtime error
	virtual int getTransData(int Tag, byte *data_value, int *data_sz, 
						     char format[], bool bTransactionDataOnly = true);

	// implements a VSDC transaction according to EMV 2000 and 
	// VIS 1.4.0 specifications.
	// Parameters:
	//		fci_data - a data received from the SELECT application command,
	//				which is File Control Information (Tag '6F')
	//		fci_len - number of bytes in fci_data
	// Returns:
	//		SUCCESS - on successful completion of the operation
	//		error code - on error
	// Note:
	// To retrieve the status of transaction (Approved or Declined) use
	// getStatus method of the OperationEvent object 
	int verifyTransaction (byte *fci_data, int fci_len);

private:
	scsEMV EMV;

	bool IsCLCInitialized;
	bool IsEMVProcCompleted;
	bool IsEMVProcInProgress;

	TRANS_STARTUP_PARAMS TransactionParams;


// Private member functions
private:
	int GetTermCountryCode (byte *termCode);
	int OpenServiceCntrl (ServiceControl *sc);
	void outputDataObject(scsEMV &EMV, int tag, const char *name);
	int checkInitialization (bool checkEvent = true);
};

#endif

