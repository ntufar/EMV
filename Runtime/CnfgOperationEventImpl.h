// CnfgControl service
// Operation Event implementation.

#ifndef CNFGOPERATIONEVENTIMPL_H
#define CNFGOPERATIONEVENTIMPL_H

#include "CnfgOperationEvent.h"

class CnfgOperationEventImpl: 
	public CnfgOperationEvent
{
public:
	CnfgOperationEventImpl(void);
	virtual ~CnfgOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

