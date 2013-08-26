#ifndef EVENTADDER_H
#define EVENTADDER_H

#include "OperationEvent.h"
#include "errors.h"
#include "custom_types.h"
//#include "projects.h"
//#include "ServiceControlModules.h"

// Functions where errors are detected
//#define EVENTADDER_ADDOPERATIONEVENT 0x01

// Module specific errors
//#define ERR_EVT_ASSIGNED 0x01

class EventAdder
{
public:
	EventAdder(void);
	~EventAdder(void);

public:
	virtual int addOperationEvent(OperationEvent* pOpEvnt);
	virtual void removeEvent(void) ;
	virtual bool eventAttached(void) ;
        OperationEvent* opEvent;

//protected:

};

#endif 
