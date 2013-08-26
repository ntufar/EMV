// PINControl Service
// Operation Event definition for usage with PINControl.

#ifndef PINOPERATIONEVENT_H
#define PINOPERATIONEVENT_H
#include "OperationEventWithValue.h"
#include "PINInterface.h"

class PINOperationEvent :
	public OperationEventWithValue
{
public:
	PINOperationEvent(void);
	virtual ~PINOperationEvent(void);
};
#endif
