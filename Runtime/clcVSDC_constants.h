#ifndef CLCVSDC_CONSTANTS_H
#define CLCVSDC_CONSTANTS_H
#include <wintypes.h>
#include "custom_types.h"

const byte zero_amount [6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

struct TRANS_STARTUP_PARAMS
{
	byte AmountAuthorized[6];
	byte AmountOther[6];
	byte CurrencyCode [2];
	byte TransactionType;
	byte TransactionInfo;
	long TransactionToken;
	int LanguageID;
};

#endif

