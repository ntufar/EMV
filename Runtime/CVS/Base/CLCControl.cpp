#include "CLCControl.h"
#include "patch.h"

CLCControl::CLCControl(const char *service_name):
	//ServiceControl(service_name, SERVICE_TYPE_CLC)
	ServiceControl(service_name)
{
}

CLCControl::CLCControl(const char *service_name, const char *path):
	//ServiceControl(service_name, SERVICE_TYPE_CLC, path)
	ServiceControl(service_name, path)
{
}

CLCControl::~CLCControl (void)
{
}
