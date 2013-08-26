/*
Referral.h
Implements the "Referral Processing" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 5, book 4 ch 2.5.2.
*/

#ifndef REFFERAL_H
#define REFFERAL_h

#include "EMV_Context.h"
#include "../Runtime/RefControlImpl.h"
#include "../Runtime/RefOperationEventImpl.h"
#include "dol_parser.h"
#include "../Utility/tlv.h"


class Referral :
	public EMV_Context
{
public:
	Referral(void);
	virtual ~Referral(void);

	int execReferral(SOURCE_OF_REFERRAL srsReferral);

private:
	int SetDefaultResult(SOURCE_OF_REFERRAL srsReferral);
};

#endif

