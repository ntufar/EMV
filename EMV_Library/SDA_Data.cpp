#include "SDA_Data.h"

SDA_Data::SDA_Data(Context *EnvContext)
{
	this->EnvContext = EnvContext;
}

SDA_Data::~SDA_Data(void)
{
}

int SDA_Data::init()
{
	int res;
	if ((res = EnvContext->getTagValue (0x9b, &dob_TSI, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x95, &dob_TVR, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x90, &dob_IPKCert, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x9f06, &dob_AID, false)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x8f, &dob_CAPKI, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x9f32, &dob_IPKExp, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x93, &dob_SAD, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x5a, &dob_PAN, true)) != SUCCESS)
		return res;
	if ((res = EnvContext->getTagValue (0x82, &dob_AIP, true)) != SUCCESS)
		return res;

	// Optional data
	EnvContext->getTagValue (0x92, &dob_IPKRem);
	EnvContext->getTagValue (0x9f4a, &dob_SDATagList, true);
	
	return SUCCESS;
}
