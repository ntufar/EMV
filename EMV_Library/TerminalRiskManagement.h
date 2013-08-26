/*
TerminalRiskManagement.h
Implements the "Terminal Risk Management" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.6; VIS 1.4.0, ch 9.

Note: Implements the following methods:
- Floor Limits,
- Random Transaction Selection,
- Velocity Checking
*/
#ifndef TERMINALRISKMANAGEMENT_H
#define TERMINALRISKMANAGEMENT_H

#include "EMV_Context.h"
#include "scr_command.h"
#include "emv_constants.h"


class TerminalRiskManagement :
	public EMV_Context
{
public:
	TerminalRiskManagement(void);
	virtual ~TerminalRiskManagement(void);

	int initData();

	int floorLimit();
	int randomTransactionSelection();
	int velocityChecking();
	void setTerminalRiskMangmntComplete();
	int checkExceptionFile();

	bool IsRiskManagementSupported();
	int IsFloorExceeded();

private:
	bool IsTransLogExist();
	int GenerateRandomNumber(byte *rand);
	int Binary2Numeric(const byte bin_data[], int bin_len, byte numData[], int num_len);
	int calcTransactionTargetPercent(const byte amount[],
								 const byte threshold[],
								 const byte floor[],
								 byte target_percent,
								 byte max_target_percent,
								 byte *TransactionTarget);
	int ReadFromTheCard (int tag, int *iVal);
	bool IsApplInExceptionFile(const byte *pan, int pan_len, 
							   const byte *seq, int seq_len);

	DataObject dob_TVR;
	DataObject dob_TSI;
};

#endif

