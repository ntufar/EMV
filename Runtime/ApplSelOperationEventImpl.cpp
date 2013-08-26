#include <stdio.h>
#include <stdlib.h>
#include "ApplSelOperationEventImpl.h"

ApplSelOperationEventImpl::ApplSelOperationEventImpl(void)
{
}

ApplSelOperationEventImpl::~ApplSelOperationEventImpl(void)
{
	resetEvent(true);
}


void ApplSelOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* ApplSelOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
