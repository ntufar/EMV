/*
CVM_List.h
Parses CVM list into separate rules. The rules can be accessed using 
getFirstRule() and getNextRule() methods.

Reference: EMV 4.0 book 3, ch 6.5
*/
#ifndef CVM_LIST_H
#define CVM_LIST_H

#include "../Runtime/custom_types.h"
#include "../Utility/common_functions.h"
#include <list>
using namespace std;

typedef list<short> CVM_LIST;
typedef list<short>::iterator ITERATOR;

#define RULE_EOF              0xAB000000
#define CVM_NOT_INITIALIZED   0xAB000001
#define CVM_INVALID_LIST_SIZE 0xAB000002

class CVM_List
{
public:
	CVM_List(void);
	~CVM_List(void);

	int parse (const byte *cvm_list, UNINT size);
	int getAmountX();
	int getAmountY();

	int getFirstRule();
	int getNextRule();
	UNINT items();

private:
	bool initFlag;
	int AmountX;
	int AmountY;
	ITERATOR curIndx;
	CVM_LIST CVM_list;
};

#endif

