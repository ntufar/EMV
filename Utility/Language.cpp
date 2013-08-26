#include "Language.h"
#include <stdio.h>
#include "Latin1.h"

Language::Language(void)
{
}

Language::~Language(void)
{
}

char* Language::getStdString (int StringID, int LangID, const char *amount)
{
	if (!getString (StringID, LangID))
		return 0;
	
	char *str;
	if (amount)
		str = new char [strlen(amount) + strlen (getString (StringID, LangID)) + 4];
	else
		str = new char[strlen (getString (StringID, LangID)) + 1];

	if (!str)
		return 0;

	if (!amount)
		strcpy(str, getString (StringID, LangID));
	else if (StringID == MSG_ID__AMOUNT_OK)
		sprintf (str, "(%s) %s", amount, getString (StringID, LangID));
	else if (StringID == MSG_ID__AMOUNT)
		sprintf (str, "%s: %s", getString (StringID, LangID), amount);
	else
		strcpy(str, getString (StringID, LangID));

	return str;
}

const char* Language::getString(int StringID, int LanguageID)
{
	if (!IsValidStringID(StringID))
	{
		return NULL;
	}
	// If other languages are supported, then create String Table similar to
	// STRING_TABLE_LATIN1 for all supported languages
	switch (LanguageID)
	{
	case EMV_LANG_LATIN2:   
	case EMV_LANG_LATIN3: 
	case EMV_LANG_LATIN4: 
	case EMV_LANG_CYRILLIC: 
	case EMV_LANG_ARABIC:   
	case EMV_LANG_GREEK:    
	case EMV_LANG_HEBREW:   
	case EMV_LANG_LATIN5:  
	case EMV_LANG_LATIN6: 
	case EMV_LANG_LATIN1:
		return STRING_TABLE_LATIN1[StringID];
	default:
		return STRING_TABLE_LATIN1[StringID];
	}
}

bool Language::IsValidStringID(int StringID)
{
	if (StringID > 0 && StringID <= MSG_ID__TRY_AGAIN || 
		StringID == MSG_ID_LAST_PIN_TRY)
		return true;
	else
		return false;
}

bool Language::IsValidCodeTable(unsigned char codeTable)
{
	switch (codeTable)
	{
	case EMV_LANG_LATIN1:
	case EMV_LANG_LATIN2:   
	case EMV_LANG_LATIN3: 
	case EMV_LANG_LATIN4: 
	case EMV_LANG_CYRILLIC: 
	case EMV_LANG_ARABIC:   
	case EMV_LANG_GREEK:    
	case EMV_LANG_HEBREW:   
	case EMV_LANG_LATIN5:  
	case EMV_LANG_LATIN6: 
		return true;
	default:
		return false;
	}
}

bool Language::IsCodeTableSupportedByTerminal(byte CodeTable, 
											  byte AddTermCap[])
{
	switch (CodeTable)
	{
	case 0x01:
		return check_bit(AddTermCap[4], 0x01);
	case 0x02:
		return check_bit(AddTermCap[4], 0x02);
	case 0x03:
		return check_bit(AddTermCap[4], 0x04);
	case 0x04:
		return check_bit(AddTermCap[4], 0x08);
	case 0x05:
		return check_bit(AddTermCap[4], 0x10);
	case 0x06:
		return check_bit(AddTermCap[4], 0x20);
	case 0x07:
		return check_bit(AddTermCap[4], 0x40);
	case 0x08:
		return check_bit(AddTermCap[4], 0x80);
	case 0x09:
		return check_bit(AddTermCap[3], 0x01);
	case 0x10:
		return check_bit(AddTermCap[3], 0x02);
	default:
		return false;
	}
}
