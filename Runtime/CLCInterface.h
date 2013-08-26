// CLCControl Service
// CLCControl Interface Declaration.
//
// A CLC module is a general purpose functionality implemented in a system 
// independent fashion. It is very similar to all other services, but 
// instead of providing interface to the peripheral devices (e.g. PIN pad, 
// card reader, ets.), CLC module provides an implementation of some logic 
// that can be reused accross POS applications. POS application can use 
// multiple CLC modules. CLC modules are loaded and used in exact same manner 
// as all other services (using AccessManager).

#ifndef CLCINTERFACE_H
#define CLCINTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"

// Errors:
#define CLC_BAD_ARGUMENT              0xCC000001
#define CLC_MISSING_INIT_DATA         0xCC000002
#define CLC_NOT_INITIALIZED           0xCC000003
#define CLC_INPROGRESS                0xCC000004
#define CLC_CNTXT_CANNOT_FIND_SERVICE 0xCC000005



class CLCInterface : public ServiceInterface
{
public:
	CLCInterface();
	virtual ~CLCInterface(void);

	// Initializes CLC module by setting initial parameters, openning 
	// the services, ets.
	virtual int initCLC (void *Param) = 0;
	// Resets CLC module by setting it to the initial state
	virtual void resetCLC() = 0;

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
						     char format[], bool bTransactionDataOnly = true) = 0;
};

#endif

