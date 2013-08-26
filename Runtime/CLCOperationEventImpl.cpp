#include <stdio.h>
#include <stdlib.h>
#include "CLCOperationEventImpl.h"

CLCOperationEventImpl::CLCOperationEventImpl(void)
{
}

CLCOperationEventImpl::~CLCOperationEventImpl(void)
{
	resetEvent(true);
}

void CLCOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* CLCOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
