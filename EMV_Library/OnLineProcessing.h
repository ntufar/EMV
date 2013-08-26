/*
OnLineProcessing.h
Implements the "Online Processing" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.9; VIS 1.4.0, ch 12.

Note: Connects and sends online message to the remote host
*/
#ifndef ONLINEPROCESSING_H
#define ONLINEPROCESSING_H

#include "EMV_Context.h"
#include "TerminalRiskManagement.h"
#include "../Runtime/HostControlImpl.h"
#include "../Utility/tlv.h"
#include "dol_parser.h"


class OnLineProcessing :
	public EMV_Context
{
public:
	OnLineProcessing(void);
	virtual ~OnLineProcessing(void);

	int goOnline();
	int initData();
	bool IsCommError(int res);

	int sendOnLineMsg(HostControlImpl &host,
		    		  const byte *onLineData, UNINT data_len);	
	int ExternalAuth();

	bool IsTerminationRequested();

private:
	int parseOnLineMsg (byte *respData, UNINT resp_len);
	void resetOnlineDataInContext(HostControlImpl *host);
	void resetScriptTags(int tag);

private:
	DataObject dob_TVR;
	DataObject dob_TSI;
	DataObject dob_AIP;

	bool TerminationFlag;
};

#endif

