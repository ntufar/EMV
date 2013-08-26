// SystemControl Service
// SystemControl Interface Declaration -- Server Side

#ifndef SYSTEMCONTROL_SERVER_H
#define SYSTEMCONTROL_SERVER_H

#include "EventAdder.h"
#include "amAdder.h"
#include "SystemInterface.h"
#include "SystemOperationEvent.h"

class SystemControl_Server :
	public EventAdder, 
	public SystemInterface,
	public amAdder
{
public:
	SystemControl_Server(void);
	virtual ~SystemControl_Server(void);
};

#endif
