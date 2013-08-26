#include <stdio.h>
#include <stdlib.h>
#include "SystemOperationEventImpl.h"

SystemOperationEventImpl::SystemOperationEventImpl(void)
{
}

SystemOperationEventImpl::~SystemOperationEventImpl(void)
{
	resetEvent(true);
}


void SystemOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* SystemOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
