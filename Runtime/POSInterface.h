// POSControl Service
// POSControl Interface Declaration
//
// POSControl implements a logic of a particular POS Application. Each POS
// Application supported by a terminal must have a POSControl where the logic
// of this application is implemented. AccessManager, used to access all services
// and CLC modules, runs in a context of the POSControl Application. In other
// words, when AccessManager is used to open the same service from the two 
// different POSControl applications, the actual service loaded might be
// different depending on the settings of each POS Application.
// An example of using POSControl might be an execution of a purchase tran-
// saction using EMV standard: first do some pre-processing when selected, then 
// execute EMV transaction to see if transaction is approved or
// declined, finally, do some post-processing.
// Other POSControl Applications might use for example some other standards 
// instead of EMV to deside the transaction status, or do some other 
// processing like loyalty type application, ets.

#ifndef POSINTERFACE_H
#define POSINTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"
#include "POSOperationEvent.h"

#define AID_MAX_LEN 16

// Errors:
#define POS_BAD_ARGUMENT              0xCD000001
#define POS_MISSING_INIT_DATA         0xCD000002
#define POS_NOT_INITIALIZED           0xCD000003
#define POS_INPROGRESS                0xCD000004

class POSInterface :
	public ServiceInterface
{
public:
	POSInterface(const byte *AID, int aid_len);
	virtual ~POSInterface(void);

	// Executes POS application
	// Returns:
	//		SUCCESS - if operation completed successfully,
	//		Error Code - if operation Failed
	//		Additional Error information can be extracted from the OperationEvent
	//      object when available.
	virtual int execPOS(byte *fci_data, int fci_len) = 0;

	// Initializes POS module by setting initial parameters, openning 
	// the services, ets.
	virtual int initPOS (void *Param) = 0;

	// Resets POS module by setting it to the initial state
	virtual void resetPOS() = 0;
	
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
						     char format[],
							 bool bTransactionDataOnly = true) = 0;	

public:
	byte aid[AID_MAX_LEN];
	int aid_len;

protected:
	
};

#endif

