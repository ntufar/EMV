// RefControl Service
// RefControl Interface Declaration
//
// RefControl Service allows to implement procedures necessary to complete
// a referral process for referrals initiated by the ICC or (and) by the Issuer.

#ifndef REFINTERFACE_H
#define REFINTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"
#include "errors.h"

#define REF_APPROVE 0x01
#define REF_BYPASS  0x02
#define REF_ONLINE  0x04

enum SOURCE_OF_REFERRAL {REF_INIT_BY_CARD, REF_INIT_BY_ISSUER};

class RefInterface :
	public ServiceInterface
{
public:
	RefInterface(void);
	virtual ~RefInterface(void);

	// Interface functions
	// Returns an array of tags for data required for referral process.
	virtual int getRefDataTags () = 0;

	// Performs referral processing, such as prompting attendant to call the bank,
	// and then prompt the attendant to enter some referral result data.
	// Parameters:
	// srsReferral - Indicates the source of initiating the referral (ICC or Issuer)
	// ref_data - a buffer with data to be used by a referral process
	// ref_len - the size of the ref_data in bytes
	// timeout - time im milliseconds to wait until referal is complete.
	//			Default value is SCS_TO_INFINITE (0x7fffffff)
	// Returns:
	//		SUCCESS (0) - operation succeeds. 
	//      error code - some other errors
	// Note: The function sets to values in OperationEvent:
	//  Disposition: Any combination of:
	//		REF_APPROVE 
	//		REF_BYPASS  
	//		REF_ONLINE  
	//  Authorization Response Code (2 bytes)
	virtual int perform_referral(SOURCE_OF_REFERRAL srsReferral,
						  byte *ref_data, UNINT ref_len,
				          UNINT timeout = SCS_TO_INFINITE) = 0;
	
};

#endif

