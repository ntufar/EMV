// CLC module Interface
// Defines the Operation Event Interface to be used with CLC module.

#ifndef VSDCOPERATIONEVENT_H
#define VSDCOPERATIONEVENT_H

#include "OperationEventWithValue.h"
#include "../EMV_Library/emv_constants.h"

class CLCOperationEvent :
	public OperationEventWithValue
{
public:
	CLCOperationEvent(void);
	virtual ~CLCOperationEvent(void);

	int setTransDecision(TERMINAL_RESPONSE termResp);
	TERMINAL_RESPONSE getTransDecision();

private:
	TERMINAL_RESPONSE TerminalResponse;
};

#endif
