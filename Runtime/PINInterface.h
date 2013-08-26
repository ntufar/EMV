// PINControl Service
// PINControl Interface Declaration.
//
// This control provides an interface for obtaining a PIN number 
// from a cardholder.

#ifndef PININTERFACE_H
#define PININTERFACE_H

#include "ServiceInterface.h"
#include "custom_types.h"
#include "../Utility/Language.h"

#define MAX_PIN_LENGTH 12
#define MIN_PIN_LENGTH 4

class PINInterface :
	public ServiceInterface
{
public:
	PINInterface(void);
	virtual ~PINInterface(void);

	virtual int getPIN(byte *pin, UNINT *size, 
		int StringID = MSG_ID__ENTER_PIN, int LanguageID = EMV_LANG_LATIN1) = 0;
};

#endif

