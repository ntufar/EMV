#ifndef SDA_DATA
#define SDA_DATA

#include "../Utility/utility.h"
#include "Context.h"

class SDA_Data
{
public:
	SDA_Data(Context *EnvContext);
	~SDA_Data(void);

	int init();

private:
	void reset();

public:
	// M - Mandatory Data Object
	// O - Optional Data Object
	// C - ICC Data Object
	// A - Application Data Object (Terminal)
	// T - Transaction related Data Object
	DataObject dob_IPKCert; // MC
	DataObject dob_AID;     // MA
	DataObject dob_CAPKI;   // MC
	DataObject dob_IPKRem;  // OC
	DataObject dob_IPKExp;  // MC
	DataObject dob_SAD;     // MC
	DataObject dob_PAN;     // MC
	DataObject dob_TSI;     // MT
	DataObject dob_TVR;     // MT
	DataObject dob_AIP;     // MC
	DataObject dob_SDATagList; // OC

private:
	Context *EnvContext;
};

#endif
