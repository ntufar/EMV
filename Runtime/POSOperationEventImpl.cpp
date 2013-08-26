#include <stdio.h>
#include <stdlib.h>
#include "POSOperationEventImpl.h"

POSOperationEventImpl::POSOperationEventImpl(void)
{
}

POSOperationEventImpl::~POSOperationEventImpl(void)
{
	resetEvent(true);
}

void POSOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* POSOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}

