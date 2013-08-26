#include "POSControl_Interface.h"

POSControl_Interface::POSControl_Interface(const byte *aid, int aid_len):
	ServiceControl("POSControl"),
	POSInterface (aid, aid_len)
{
}

POSControl_Interface::POSControl_Interface(const byte *aid, int aid_len, 
										   const char* path):
	ServiceControl ("POSControl", path),
	POSInterface (aid, aid_len)
{
}

POSControl_Interface::~POSControl_Interface(void)
{
}

short POSControl_Interface::getInterfaceType ()
{
	return ServiceInterface::getInterfaceType();
}
