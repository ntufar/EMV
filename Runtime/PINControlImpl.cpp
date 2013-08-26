#include <wintypes.h>
#include "PINControlImpl.h"
#include "../Utility/Language.h"
#include "patch.h"

HWND hwndDlg;
HANDLE hThread;
int STRING_ID;
int LANG_ID;

int DialogExitCode;
byte PIN_BUFFER [MAX_PIN_LENGTH + 1];
UNINT PIN_BUFFER_SIZE;


PINControlImpl::PINControlImpl(HANDLE hModule)
{
	this->hModule = (HINSTANCE)hModule;
	hThread = 0;
	PIN_BUFFER_SIZE = 0;
	STRING_ID = MSG_ID__ENTER_PIN;
	LANG_ID = EMV_LANG_LATIN1;
}

PINControlImpl::PINControlImpl()
{
	hThread = 0;
	PIN_BUFFER_SIZE = 0;
	STRING_ID = MSG_ID__ENTER_PIN;
	LANG_ID = EMV_LANG_LATIN1;
}

PINControlImpl::~PINControlImpl(void)
{
	DWORD ExitCode;
        hThread = NULL;
}

int PINControlImpl::getPIN(byte *pin, UNINT *size, int StringID, int LanguageID)
{
	
	//memcpy(pin, PIN_BUFFER, PIN_BUFFER_SIZE);
	memcpy(pin, "TESTING TESTING", PIN_BUFFER_SIZE);
	return SUCCESS;
}
