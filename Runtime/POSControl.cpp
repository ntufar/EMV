#include "POSControl.h"
#include "patch.h"

POSControl::POSControl(int aid, const char *pos_name):
	//ServiceControl(pos_name, SERVICE_TYPE_CLC),
	ServiceControl(pos_name),
	AID (aid)
{
}

POSControl::POSControl(int aid, const char *pos_name, const char *path):
	//ServiceControl(pos_name, SERVICE_TYPE_POS, path),
	ServiceControl(pos_name, path),
	AID (aid)
{
}

POSControl::~POSControl (void)
{
}
