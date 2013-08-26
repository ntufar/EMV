#include <stdio.h>
#include <stdlib.h>
#include "CryptoOperationEventImpl.h"

CryptoOperationEventImpl::CryptoOperationEventImpl(void)
{
}

CryptoOperationEventImpl::~CryptoOperationEventImpl(void)
{
	resetEvent(true);
}

void CryptoOperationEventImpl::releaseResource(void **pBuffer)
{
	if (*pBuffer)
		free((*pBuffer));
	*pBuffer = NULL;
}

void* CryptoOperationEventImpl::allocateResource(int typeSize, int BufferSize)
{
	if (BufferSize <= 0 || typeSize <= 0)
		return NULL;

	void *pp = malloc( typeSize * BufferSize);
	return pp;
}
