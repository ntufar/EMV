/*
ProcessingRestrictions.h
Implements the "Processing Restrictions" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.4; VIS 1.4.0, ch 7.
*/
#ifndef PROCESSINGRESTRICTIONS_H
#define PROCESSINGRESTRICTIONS_H

#include "EMV_Context.h"
#include "../Utility/utility.h"

class ProcessingRestrictions :
	public EMV_Context
{
public:
	ProcessingRestrictions(void);
	virtual ~ProcessingRestrictions(void);

	int CheckVersion();
	int CheckUsageControl();
	int CheckApplicationDates();
	int initData();

private:
	int checkTransaction (byte termCap, 
						  byte transType, 
						  byte dom_trans, 
						  byte inter_truns,
		                  byte auc, 
						  bool IsCountryCodeMatch);
	bool IsATM(DataObject *dob_TermType, 
			   DataObject *dob_TermCap);

private:
	DataObject dob_TVR;
	DataObject dob_TermCountryCode;
};

#endif
