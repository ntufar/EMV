// PINControl Service
// PINControl Interface Declaration -- Server Side

#ifndef PINCONTROL_SERVER_H
#define PINCONTROL_SERVER_H

#include "EventAdder.h"
#include "amAdder.h"

#include "PINInterface.h"
#include "PINOperationEvent.h"

class PINControl_Server :
	public EventAdder,
	public PINInterface,
	public amAdder
{
public:
	PINControl_Server(void);
	virtual ~PINControl_Server(void);

};

#endif

