#include "RefOperationEvent.h"

RefOperationEvent::RefOperationEvent(void)
{
	Disposition = -1;
	RefferalResp = 0;
	referral_len = -1;
}

RefOperationEvent::~RefOperationEvent(void)
{
	Disposition = -1;
	RefferalResp = 0;
	referral_len = -1;
}

int RefOperationEvent::setDisposition(int disp)
{
	Disposition = disp;
	set_value();
	return setSuccess();
}

int RefOperationEvent::getDisposition()
{
	if (Disposition == -1)
		return ERR_OPEVNT__VALUE_IS_NOT_SET;
	else
		return Disposition;
}

int RefOperationEvent::setReferralResp(const byte *resp_data, int resp_len)
{
	releaseRefString(&RefferalResp, &referral_len);
	if (resp_len <= 0)
		return setError(ERR_BAD_ARGUMENT, SETTING_OPERATION_EVENT);

	RefferalResp = (byte*) allocateResource (sizeof (byte), resp_len);
	if (!RefferalResp)
	{
		return setError(ERR_MEMORY_ALLOC, SETTING_OPERATION_EVENT);
	}

	//Manually copy bytes of data.
	// Don't use memcpy here, it will cause an error when run outside of development
	// environment! 
	// This is due to the face that buffer is allocated in a process Heap, and memcpy
	// cannot access that memory.
	for (int i = 0; i < resp_len; i++)
		RefferalResp[i] = resp_data[i];


	referral_len = resp_len;
	set_value();
	return setSuccess();
}

int RefOperationEvent::getReferralLen ()
{
	return referral_len;
}

byte* RefOperationEvent::getReferralResp(int *len)
{
	if (RefferalResp && referral_len > 0)
	{
		*len = referral_len;
		return RefferalResp;
	}
	else
	{
		*len = 0;
		return 0;
	}
}

void RefOperationEvent::resetEvent(bool withStop)
{
	releaseRefString(&RefferalResp, &referral_len);
	OperationEventWithValue::resetEvent(withStop);
}


void RefOperationEvent::releaseRefString (byte** pRef, int *len)
{
	if (pRef && *len > 0)
		releaseResource ((void**)pRef);
	*pRef = 0;
	*len = 0;
}
