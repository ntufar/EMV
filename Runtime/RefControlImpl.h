#ifndef REFCONTROLIMPL_H
#define REFCONTROLIMPL_H

#include "../Utility/utility.h"
#include "UIControlImpl.h"
#include "EventAdder.h"
#include "RefInterface.h"
#include "amAdder.h"
#include "RefOperationEvent.h"
#include "CnfgControlImpl.h"
#include "AccessManager.h"
#include "patch.h"


const byte DEFAULT_LIST_OF_REF_DATA_TAGS[] =  {0x5a}; // PAN
#define DEFAULT_REF_SIZE 1

class RefControlImpl :
        public EventAdder,
        public RefInterface,
        public amAdder,
	public ServiceControl
{
public:
	RefControlImpl(void);
	virtual ~RefControlImpl(void);

	// Interface functions
	virtual int getRefDataTags ();
	virtual int perform_referral(SOURCE_OF_REFERRAL srsReferral,
								 byte *ref_data, UNINT ref_len,
								 UNINT timeout = SCS_TO_INFINITE);

private: //Private member functions
	long checkInitialization (bool checkEvent = true);
};

#endif

