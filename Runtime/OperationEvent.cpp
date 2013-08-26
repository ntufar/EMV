#include "OperationEvent.h"

OperationEvent::OperationEvent(void)
: op_status(0),
  op_error(0),
  operation(0)
{
}

OperationEvent::~OperationEvent(void)
{
	op_status = EVNT_NONE;
	op_error = 0;
	operation = 0;
}

int OperationEvent::connectEvent()
{
	if (check_bit(op_status, EVNT_CONNECTED))
		return ERR_OPEVNT__ALREADY_CONNECTED;
	set_bit(op_status,EVNT_CONNECTED);
	reset_bit(op_status, EVNT_STARTED | EVNT_COMPLETED | EVNT_ERROR);
	return EVT_SUCCESS;
}

void OperationEvent::releaseEvent()
{
	reset_bit(op_status,EVNT_CONNECTED);
}

int OperationEvent::begin_operation()
{
	if (check_bit(op_status, EVNT_STARTED))
		return ERR_OPEVNT__ALREADY_RUNNING;
	set_bit(op_status, EVNT_STARTED);
	reset_bit(op_status, EVNT_COMPLETED | EVNT_ERROR | EVNT_VALUE);
	return EVT_SUCCESS;
}

void OperationEvent::end_operation()
{
	set_bit(op_status,EVNT_COMPLETED);
}

void OperationEvent::set_value()
{
	set_bit(op_status, EVNT_VALUE);
}
	
void OperationEvent::reset_value()
{
	reset_bit(op_status, EVNT_VALUE);
}

bool OperationEvent::eventConnected()
{
	return check_bit(op_status,EVNT_CONNECTED);
}

bool OperationEvent::operation_running()
{
	if (check_bit(op_status, EVNT_STARTED) & !check_bit(op_status, EVNT_COMPLETED))
		return true;
	else
		return false;
}

bool OperationEvent::op_success(bool bCheckValue)
{
	int flags2check = EVNT_STARTED | EVNT_COMPLETED;
	if (bCheckValue)
		flags2check |= EVNT_VALUE;
	if (check_bit(op_status, flags2check) & !check_bit(op_status, EVNT_ERROR))
		return true;
	else
		return false;
}


int OperationEvent::getStatus(void)
{
	return op_status;
}

int OperationEvent::setError(int iError, int iOperation)
{
	set_bit(op_status, EVNT_ERROR | EVNT_COMPLETED | EVNT_VALUE); 
	this->op_error = iError;
	this->operation = iOperation;
	return EVT_ERROR;
}

int OperationEvent::setSuccess()
{
	set_bit(op_status, EVNT_COMPLETED); 
	reset_bit(op_status, EVNT_ERROR);
	this->op_error = EVNT_NONE;
	this->operation = EVNT_NONE;
	return SUCCESS;
}


int OperationEvent::getError()
{
	return op_error;
}

int OperationEvent::getOperation()
{
	return this->operation;
}

bool OperationEvent::IsValueSet()
{
	return (check_bit(op_status, EVNT_VALUE));
}

void OperationEvent::resetEvent(bool withStop)
{
	if (withStop)
		reset_bit (op_status, EVNT_COMPLETED | EVNT_STARTED);

	reset_bit (op_status, EVNT_VALUE | EVNT_ERROR);
	this->op_error =  EVNT_NONE;
	this->operation = EVNT_NONE;
}
