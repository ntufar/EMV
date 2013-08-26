// SCRControl Service
// Operation Event Interface Declaration

#ifndef SCROPERATIONEVENT_H
#define SCROPERATIONEVENT_H

#include "OperationEventWithValue.h"
#include "custom_types.h"

class SCROperationEvent :
	public OperationEventWithValue
{
public:
	SCROperationEvent(void);
	virtual ~SCROperationEvent(void);
};

#endif

