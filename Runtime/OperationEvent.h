#ifndef OPERATIONEVENT_H
#define OPERATIONEVENT_H

#include "errors.h"
#include "custom_types.h"

// Bits used for op_status member
#define EVNT_NONE 0
#define EVNT_CONNECTED 0x00000001
#define EVNT_STARTED   0x00000002
#define EVNT_COMPLETED 0x00000004
#define EVNT_VALUE     0x00000008
#define EVNT_ERROR     0x80000000


class OperationEvent
{
public:
	OperationEvent(void);
	virtual ~OperationEvent(void);
	virtual void resetEvent(bool withStop = false);
private:
	// keeps the status of the completed operation
	int op_status;
	int op_error;
	int operation;

protected:
	// Call this function when interface method is terminated
	void end_operation();

	// Call this function when the value of the Event Object is set
	void set_value();
	void reset_value();

public:
	// Call these two functions to connect or release the Event object
	int connectEvent();
	void releaseEvent();

	// Call this function at the beginning of each interface method 
	int begin_operation();
	
	// Call the following functions to check the event object status
	bool eventConnected();
	bool operation_running();
	bool op_success(bool bCheckValue = true);
	
	// Call the following functions to get Error or Status information
	int getError();
	int getOperation();
	int getStatus();

	// Call this function to set the error and flag a completion of the operation
	int setError (int error, int operation);

	// Call this function to signal a successfull completion of an operation
	int setSuccess();

	// Call this function to check if the value of this EventObject is set
	bool IsValueSet();
};

#else
#endif

