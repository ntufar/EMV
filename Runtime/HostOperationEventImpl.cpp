#include <stdio.h>
#include <stdlib.h>
#include "HostOperationEventImpl.h"

HostOperationEventImpl::HostOperationEventImpl(void)
{
}

HostOperationEventImpl::~HostOperationEventImpl(void)
{
	resetEvent(true);
}

void HostOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* HostOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
