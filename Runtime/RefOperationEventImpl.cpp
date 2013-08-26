// RefControl Service
// Operation Event implementation

#include <stdio.h>
#include <stdlib.h>
#include "RefOperationEventImpl.h"

RefOperationEventImpl::RefOperationEventImpl(void)
{
}

RefOperationEventImpl::~RefOperationEventImpl(void)
{
	releaseRefString(&RefferalResp, &referral_len);
	resetEvent(true);
}

void RefOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* RefOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
