#include "POSInterface.h"

POSInterface::POSInterface(const byte *aid, int aid_len):
	ServiceInterface (INTERFACE_TYPE_POS)
{
	int length;
	if (aid_len <= AID_MAX_LEN)
		length = aid_len;
	else
		length = AID_MAX_LEN;

	for (int i = 0; i < length; i++)
		this->aid[i] = aid[i];
	this->aid_len = length; 
}

POSInterface::~POSInterface(void)
{
}
