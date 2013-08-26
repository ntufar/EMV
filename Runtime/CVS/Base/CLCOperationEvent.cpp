#include "CLCOperationEvent.h"

CLCOperationEvent::CLCOperationEvent(void)
{
}

CLCOperationEvent::~CLCOperationEvent(void)
{
}

int CLCOperationEvent::setTransDecision(TERMINAL_RESPONSE termResp)
{
	TerminalResponse = termResp;
	set_value();
	return setSuccess();
}

TERMINAL_RESPONSE CLCOperationEvent::getTransDecision()
{
	return TerminalResponse;
}
