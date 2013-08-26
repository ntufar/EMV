#ifndef PROMPTER_H
#define PROMPTER_H

#include "../Runtime/AccessManager.h"
#include "../Runtime/CnfgControlImpl.h"
#include "../Utility/utility.h"
#include "../Runtime/UIControlImpl.h"

class Prompter
{
public:
	Prompter(AccessManager *pAccessManager);
	~Prompter(void);

	// Prompt functions
	int promptAmount(bool AmountAuthorised, byte Amount[],  byte curCode[], 
					 int LangID);
	int promptAmountOther(byte Amount[], int LangID);
	int promptTransactionType(byte *trans, byte *trans_info, int LangID);

private:
	int getTransactions (int **codes, char ***transNames, int *size);
	int GetUIFlag(byte **data, int *len);
	int SelectFromAvailableOptions(UIControlImpl &UI, 
										 byte *trans, 
										 byte *trans_info, 
										 int LangID);
private:
	AccessManager *pAM;
};

#endif
