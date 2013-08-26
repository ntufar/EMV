#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include "ServiceInterface_Constants.h"

class ServiceInterface
{
public:
	ServiceInterface(short interfaceType);
	virtual ~ServiceInterface(void);
	short getInterfaceType ();
protected:
	short InterfaceType;
};

#endif

