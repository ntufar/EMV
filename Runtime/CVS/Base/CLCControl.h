#ifndef CLCCONTROL_H
#define CLCCONTROL_H

#include "ServiceControl.h"

class CLCControl: public ServiceControl
{
public:
	CLCControl(const char *clc_name);
	CLCControl(const char *clc_name, const char* pPath);
	virtual ~CLCControl();

	virtual int execute() = 0;
};


#endif

