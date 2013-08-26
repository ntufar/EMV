#include "CVM_List.h"

CVM_List::CVM_List(void)
{
	initFlag = false;
}

CVM_List::~CVM_List(void)
{
}

int CVM_List::parse (const byte *cvm_list, UNINT size)
{
	if (size < 10)
		return CVM_INVALID_LIST_SIZE;

	if ((size - 8) % 2 != 0)
		return CVM_INVALID_LIST_SIZE;

	AmountX = LongFromByte (cvm_list, 4);
	AmountY = LongFromByte (cvm_list + 4, 4);

	CVM_list.clear();
	for (UNINT indx = 8; indx < size; indx+=2)
	{
		short rule = (short)LongFromByte (cvm_list + indx, 2);
		CVM_list.push_back(rule);
	}
	initFlag = true;
	return SUCCESS;
}

int CVM_List::getAmountX()
{
	if (initFlag)
		return AmountX;
	else
		return CVM_NOT_INITIALIZED;
}

int CVM_List::getAmountY()
{
	if (initFlag)
		return AmountY;
	else
		return CVM_NOT_INITIALIZED;
}

int CVM_List::getFirstRule()
{
	curIndx = CVM_list.begin();
	if (curIndx == CVM_list.end())
		return RULE_EOF;
	int rule = (*curIndx & 0x0000ffff);
	curIndx++;
	return rule;
}

int CVM_List::getNextRule()
{
	if (curIndx == CVM_list.end())
		return RULE_EOF;
	
	int rule = (*curIndx & 0x0000ffff);
	curIndx++;
	return rule;
}

UNINT CVM_List::items()
{
	return (UNINT)CVM_list.size();
}
