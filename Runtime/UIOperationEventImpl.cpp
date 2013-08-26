#include <stdio.h>
#include <stdlib.h>
#include "UIOperationEventImpl.h"

UIOperationEventImpl::UIOperationEventImpl(void)
{
}

UIOperationEventImpl::~UIOperationEventImpl(void)
{
	releaseAllResources();
	valueType = UI_NONE;
}

void UIOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* UIOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
