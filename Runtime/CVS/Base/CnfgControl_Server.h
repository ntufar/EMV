// CnfgControl Service
// CnfgControl Interface Declaration -- Server Side.

#ifndef CNFGCONTROL_SERVER_H
#define CNFGCONTROL_SERVER_H

#include "CnfgInterface.h"
#include "EventAdder_Server.h"
#include "amAdder.h"

#include "CnfgInterface.h"
#include "CnfgOperationEvent.h"

class CnfgControl_Server :
	public EventAdder_Server,
	public CnfgInterface,
	public amAdder
{
public:
	CnfgControl_Server();
	virtual ~CnfgControl_Server(void);
};

#endif
