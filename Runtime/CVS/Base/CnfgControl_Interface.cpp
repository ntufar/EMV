#include "CnfgControl_Interface.h"

CnfgControl_Interface::CnfgControl_Interface () : 
	ServiceControl("CnfgControl"),
	EventAdder_Interface(&Key)
{
}

CnfgControl_Interface::CnfgControl_Interface (const char* path) : 
	ServiceControl("CnfgControl", path),
	EventAdder_Interface(&Key)
{
}
CnfgControl_Interface::~CnfgControl_Interface(void)
{
}

short CnfgControl_Interface::getInterfaceType ()
{
	return ServiceInterface::getInterfaceType();
}
