#include "SCRControl_Interface.h"

SCRControl_Interface::SCRControl_Interface(void): 
	ServiceControl("SCRControl")
{
}

SCRControl_Interface::SCRControl_Interface(const char* path): 
	ServiceControl("SCRControl", path)
{
}

SCRControl_Interface::~SCRControl_Interface(void)
{
}

short SCRControl_Interface::getInterfaceType ()
{
	return ServiceInterface::getInterfaceType();
}
