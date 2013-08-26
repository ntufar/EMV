#include "ApplSelOperationEvent.h"

ApplSelOperationEvent::ApplSelOperationEvent(void):
	TransactionToken(0)
{
}

ApplSelOperationEvent::~ApplSelOperationEvent(void)
{
}

void ApplSelOperationEvent::resetEvent(bool withStop)
{
	TransactionToken = 0;
	OperationEventWithValue::resetEvent(withStop);
}

void ApplSelOperationEvent::setTransactionToken(long TransToken)
{
	TransactionToken = TransToken;
}

int ApplSelOperationEvent::getTransactionToken()
{
	return TransactionToken;
}

int ApplSelOperationEvent::setValues (long TransToken, 
									  byte *sel_data, UNINT sel_len)
{
	setTransactionToken(TransToken);
	return setByteString(sel_data, sel_len);
}
