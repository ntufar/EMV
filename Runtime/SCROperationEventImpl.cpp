#include <stdio.h>
#include <stdlib.h>
#include "SCROperationEventImpl.h"

SCROperationEventImpl::SCROperationEventImpl(void)
{
}

SCROperationEventImpl::~SCROperationEventImpl(void)
{
	resetEvent(true);
}

void SCROperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* SCROperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
