// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here

#include <stdlib.h>
#include <string.h>

#define BTN_ENTER   0x00000001
#define BTN_CANCEL  0x00000002
#define BTN_CLEAR   0x00000003
#define CANCEL_WAIT 0x00000004
#define BTN_EXIT    0x00000005

#define OPTIONLIST_APPLICATIONS  0x00000001
#define OPTIONLIST_TRANSACTIONS  0x00000002
#define OPTIONLIST_CURRENCY      0x00000003
#define TEXTBOX_AMOUNT           0x00000004
#define TEXTBOX_CASHAMOUNT       0x00000005
#define TEXTBOX_PROMPT           0x00000006
#define TEXTBOX_INPUT1           0x00000007
#define TEXTBOX_OUTPUT1          0x00000008
