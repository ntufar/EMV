#ifndef REFOPERATIONEVENT_H
#define REFOPERATIONEVENT_H

#include "OperationEventWithValue.h"

class RefOperationEvent :
	public OperationEventWithValue
{
public:
	RefOperationEvent(void);
	virtual ~RefOperationEvent(void);

	int setDisposition(int disp);
	int getDisposition();

	int setReferralResp(const byte *resp_data, int resp_len);
	int getReferralLen ();
	byte *getReferralResp(int *len);
	
	void resetEvent(bool withStop = false);

protected:
	void releaseRefString (byte** pRef, int *len);

protected:
	int Disposition;
	byte *RefferalResp;
	int referral_len;
};

#endif

