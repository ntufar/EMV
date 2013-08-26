#include "CnfgInterface.h"

CnfgInterface::CnfgInterface(): 
	ServiceInterface (INTERFACE_TYPE_OS_SERVICE)//,
	//ApplicationName(NULL)
{
}

CnfgInterface::~CnfgInterface(void)
{
	//if (ApplicationName)
	//	delete [] ApplicationName;
	//ApplicationName = NULL;
}
