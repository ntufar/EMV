#ifndef LANGUAGE123_H
#define LANGUAGE123_H

#include <string.h>
#include "../Runtime/custom_types.h"


// Character Tables code indexes
#define EMV_LANG_LATIN1   0x01 // ISO ISO 8859-1 Latin I 
#define EMV_LANG_LATIN2   0x02 // ISO ISO 8859-2 Eastern Europe 
#define EMV_LANG_LATIN3   0x03 // ISO ISO 8859-3 Turkish 
#define EMV_LANG_LATIN4   0x04 // ISO ISO 8859-4 Baltic 
#define EMV_LANG_CYRILLIC 0x05 // ISO ISO 8859-5 Cyrillic 
#define EMV_LANG_ARABIC   0x06 // ISO ISO 8859-6 Arabic 
#define EMV_LANG_GREEK    0x07 // ISO ISO 8859-7 Greek 
#define EMV_LANG_HEBREW   0x08 // ISO ISO 8859-8 Hebrew 
#define EMV_LANG_LATIN5   0x09 // ISO ISO 8859-9 Latin Alphabet No.5 
#define EMV_LANG_LATIN6   0x10 // ISO ISO 8859-10 Latin Alphabet No.5
#define DEFAULT_LANG      EMV_LANG_LATIN1 // Default language to be used if no language preferences are setup

// Standard Messages ID
#define MSG_ID__AMOUNT			 0x01
#define MSG_ID__AMOUNT_OK		 0x02
#define MSG_ID__APPROVED		 0x03
#define MSG_ID__CALL_YOUR_BANK   0x04
#define MSG_ID__CANCEL_OR_ENTER  0x05
#define MSG_ID__CARD_ERROR		 0x06
#define MSG_ID__DECLINED		 0x07
#define MSG_ID__ENTER_AMOUNT	 0x08
#define MSG_ID__ENTER_PIN        0x09
#define MSG_ID__INCORRECT_PIN    0x0A
#define MSG_ID__INSERT_CARD      0x0B
#define MSG_ID__NOT_ACCEPTED     0x0C
#define MSG_ID__PIN_OK           0x0D
#define MSG_ID__PLEASE_WAIT      0x0E
#define MSG_ID__PROCESSING_ERROR 0x0F
#define MSG_ID__REMOVE_CARD      0x10
#define MSG_ID__USE_CHIP_READER  0x11
#define MSG_ID__USE_MAG_STRIPE   0x12
#define MSG_ID__TRY_AGAIN        0x13

//VISA proprietary message:
#define MSG_ID_LAST_PIN_TRY      0x20

class Language
{
public:
	Language(void);
	~Language(void);

	static char* getStdString (int StringID, int LanguageID, const char *amount = 0);
	static bool IsValidStringID(int StringID);
	static const char* getString(int StringID, int LanguageID);
	static bool IsValidCodeTable(byte codeTable);
	static bool IsCodeTableSupportedByTerminal(byte CodeTable, 
											  byte AddTermCap[]);
};

#endif
