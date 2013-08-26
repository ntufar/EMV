// CryptoControl service
// Crypto Operation Event Interface

#ifndef CRYPTOOPERATIONEVENT_H
#define CRYPTOOPERATIONEVENT_H

#include "OperationEventWithValue.h"
#include "CryptoInterface.h"

class CryptoOperationEvent :
	public OperationEventWithValue
{
public:
	CryptoOperationEvent(void);
	virtual ~CryptoOperationEvent(void);
};

#endif

