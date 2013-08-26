#ifndef AMADDER_H
#define AMADDER_H

#include "ServiceInterface.h"

class AccessManager;

class amAdder 
{
public:
	friend class AccessManager;
	amAdder();
	virtual ~amAdder(void);
	AccessManager *getAccessManager();

//protected:
	AccessManager *AM;
};

#endif

