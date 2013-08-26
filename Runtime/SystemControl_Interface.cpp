#include "SystemControl_Interface.h"

SystemControl_Interface::SystemControl_Interface(void):
	ServiceControl("SystemControl")
{
}

SystemControl_Interface::SystemControl_Interface (const char* path) : 
	ServiceControl("SystemControl", path)
{
}

SystemControl_Interface::~SystemControl_Interface(void)
{
}

short SystemControl_Interface::getInterfaceType ()
{
	return ServiceInterface::getInterfaceType();
}
