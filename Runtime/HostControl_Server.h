// HostControl Service
// HostControl Interface Declaration -- Server Side

#ifndef HOSTCONTROL_SERVER_H
#define HOSTCONTROL_SERVER_H


#include "EventAdder.h"
#include "HostInterface.h"
#include "amAdder.h"
#include "HostOperationEvent.h"
#include "CnfgControlImpl.h"
#include "AccessManager.h"

class HostControl_Server :
	public EventAdder,
	public HostInterface,
	public amAdder
{
public:
	HostControl_Server(void);
	virtual ~HostControl_Server(void);

	// Returns an array of tags for data required for online message.
	virtual int getOnlineDataTags (ONLINE_DATA_TAGS tagType);
};

#endif

