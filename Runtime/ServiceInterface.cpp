#include "ServiceInterface.h"

ServiceInterface::ServiceInterface(short interfaceType)
{
	switch (interfaceType)
	{
	case INTERFACE_TYPE_DEVICE:
	case INTERFACE_TYPE_OS_SERVICE:
	case INTERFACE_TYPE_CLC:
	case INTERFACE_TYPE_POS:
		InterfaceType = interfaceType;
		break;
	default:
		InterfaceType = INTERFACE_TYPE_INVALID;
	}
}

short ServiceInterface::getInterfaceType ()
{
	return InterfaceType;
}

ServiceInterface::~ServiceInterface(void)
{
}
