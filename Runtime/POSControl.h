#ifndef POSCONTROL_H
#define POSCONTROL_H

#include "ServiceControl.h"

class POSControl: public ServiceControl
{
public:
	POSControl(int aid, const char *pos_name);
	POSControl(int aid, const char *pos_name, const char* pPath);
	virtual ~POSControl();

	virtual int execute() = 0;
	const int AID;
};

#endif
