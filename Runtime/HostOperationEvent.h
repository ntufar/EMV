// HostControl Service
// Operation Event used with HostControl
#ifndef HOSTOPERATIONEVENT_H
#define HOSTOPERATIONEVENT_H
#include "OperationEventWithValue.h"

class HostOperationEvent :
	public OperationEventWithValue
{
public:
	HostOperationEvent(void);
	virtual ~HostOperationEvent(void);
};

#endif

