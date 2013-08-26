// PINControl Service
// PINControl Interface Implementation -- Server Side.
//
// This service is implemented in such a manner, that when a PIN number is
// requested (getPIN function), it creates a PIN pad window and prompts a card-
// holder to enter a PIN number. PIN number is received in plaintext form.

#ifndef PINCONTROLIMPL_H
#define PINCONTROLIMPL_H

#define TERMINAL_WINDOW_NAME "SmartPOS Terminal Demo"

#include "PINControl_Server.h"
#include "PINOperationEventImpl.h"
#include "resource.h"
#include "patch.h"

typedef int (* GETPIN)(UINT_KEY Key,
                                                byte *pin,
                                                UNINT *size,
                                                int StringID = MSG_ID__ENTER_PIN,
                                                int LanguageID = EMV_LANG_LATIN1);


class PINControlImpl :
	public PINControl_Server
{
public:
	PINControlImpl(HANDLE hModule);
	PINControlImpl();
	virtual ~PINControlImpl(void);

	virtual int getPIN(byte *pin, UNINT *size, 
		int StringID = MSG_ID__ENTER_PIN, int LanguageID = EMV_LANG_LATIN1);
private:
	HINSTANCE hModule;
};

#endif

