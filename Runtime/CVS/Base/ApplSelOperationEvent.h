// Application Selection Interface
// Defines the interface for Operation Event class to be used with Application
// Selection.

#ifndef APPLSELOPERATIONEVENT_H
#define APPLSELOPERATIONEVENT_H


#include "OperationEventWithValue.h"

class ApplSelOperationEvent :
	public OperationEventWithValue
{
public:
	ApplSelOperationEvent(void);
	virtual ~ApplSelOperationEvent(void);

	int setValues (long TransToken, byte *sel_data, UNINT sel_len);
	void setTransactionToken(long TransToken);
	int getTransactionToken();

	virtual void resetEvent(bool withStop = false);

protected:
	long TransactionToken;
};

#endif

