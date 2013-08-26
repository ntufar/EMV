#include <stdio.h>
#include <stdlib.h>
#include "PINOperationEventImpl.h"

PINOperationEventImpl::PINOperationEventImpl(void)
{
}

PINOperationEventImpl::~PINOperationEventImpl(void)
{
	resetEvent(true);
}

void PINOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* PINOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
