// POSControl Service
// Operation Event definition

#ifndef POSOPERATIONEVENT_H
#define POSOPERATIONEVENT_H


#include "OperationEventWithValue.h"

class POSOperationEvent :
	public OperationEventWithValue
{
public:
	POSOperationEvent(void);
	virtual ~POSOperationEvent(void);
};

#endif

