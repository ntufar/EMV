#include "amAdder.h"

amAdder::amAdder(): AM(0)
{
}

amAdder::~amAdder(void)
{
}

AccessManager* amAdder::getAccessManager()
{
	return AM;
}
