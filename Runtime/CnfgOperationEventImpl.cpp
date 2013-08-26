#include <stdio.h>
#include <stdlib.h>
#include "CnfgOperationEventImpl.h"

CnfgOperationEventImpl::CnfgOperationEventImpl(void)
{
}

CnfgOperationEventImpl::~CnfgOperationEventImpl(void)
{
	resetEvent(true);
}


void CnfgOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* CnfgOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;
		
	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
