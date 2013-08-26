// UIControl Service
// UIControl Interface Declaration
//
// Defines an interface to the UI service. This service is necessary to handle
// all communication with attendant or cardholder.

#ifndef UIINTERFACE_H
#define UIINTERFACE_H

#include "custom_types.h"
#include "ServiceInterface.h"
#include "../Utility/Language.h"

//Errors
#define ERR_APPLICATION_IS_CLOSING         0xF0000001
#define ERR_TERMINAL_WINDOW_IS_UNAVAILABLE 0xF0000002
#define ERR_UNSPECIFIED_WAITING_ERROR      0xF0000003
#define ERR_SETTING_PROMPT                 0xF0000004
#define ERR_WAIT_TIMEOUT                   0xF0000005
#define ERR_UNSPECIFIED_WAIT_EXIT_EVENT    0xF0000006
#define ERR_TERMINAL_WINDOW_IS_NOT_RUNNING 0xF0000007
#define ERR_FAILED_TO_RETREIVE_DATA        0xF0000008
#define ERR_SETTING_STRING                 0xF0000009
#define ERR_INVALID_MESSAGE_ID             0xF000000A
#define ERR_INVALID_LANGUAGE_ID            0xF000000B
#define OPERATION_CANCELED_BY_USER         0xF000000C
#define ERR_INVALID_EVENT_ID               0xF000000D
#define ERR_MISSING_CURRENCY_CODE          0xF000000E
#define ERR_INVALID_CONTROL_ID             0xF000000F

#define OPTIONLIST_INVALID_INDX            0xF0000010
#define OPTIONLIST_VALUE_NOT_FOUND         0xF0000011
#define OPTIONLIST_NO_SELECTION            0xF0000012

enum AMOUNT_TYPE {PURCHASE_AMOUNT, CASHBACK_AMOUNT};

class UIInterface :
	public ServiceInterface
{
public:
	UIInterface(void);
	virtual ~UIInterface(void);

	// UI Interface Definition
	// Outputs a string and returns without waiting for a user response
	virtual int setPrompt(const char* str, int LangID = 0) = 0;

	// UI Interface Definition
	// Sets the value of the text box
	virtual int setText(const int TextBoxID, 
						const char* text, int LangID = 0) = 0;
	// UI Interface Definition
	// Sets the value of the text box
	virtual int getText(const int TextBoxID) = 0;

	// Outputs a prompt to the user, and then waits for user input. The user's input
	// is in a form of a string
	virtual int receiveString(const char *prompt, 
		int timeout = SCS_TO_INFINITE, int LangID = 0) = 0;

	// Promts a user to enter an amount of transaction and the currency code,
	// and waits until the user enters the amount and clicks a button
	virtual int getAmount(AMOUNT_TYPE amount_type, 
						  byte Amount[6], byte CurrencyCode [2],
						  int timeout = SCS_TO_INFINITE, int LangID = 0) = 0;

	// Reads the amount from the Amount field - doesn't prompt a 
	// user and doesn't wait for a user input
	virtual int readAmount(AMOUNT_TYPE amount_type,
						   byte Amount[6], byte CurrencyCode [2]) = 0;
	
	// Clears the amount field
	virtual void resetAmount(AMOUNT_TYPE amount_type) = 0;

	// Outputs a question to the user, and then waits for user to click
	// a button
	virtual int getResponse(const char *strQuestion, 
		int timeout = SCS_TO_INFINITE, int LangID = 0) = 0;

	// Outputs a prompt together with a set of options to the user,
	// and then waits until the user selects one of the options
	virtual int selectOption(int OptionBoxID,
							 const char *prompt,
							 const char * const optionList[],
							 const int dataList[],
							 const unsigned int numberOfOptions,
							 int timeout = SCS_TO_INFINITE,
							 int *LangID = 0) = 0;

	// Outputs a prompt and then waits until the user selects one of the
	// options from the pre-populated list (or combo) box
	virtual int getOption (int OptionBoxID,
						   const char *prompt, 
						   int timeout = SCS_TO_INFINITE,
						   int LangID = 0) = 0;
	
	// Reads data from the Option box at the specified index (indx)
	virtual int readOptionItem (int OptionBoxID,
								int indx) = 0;

	// Reads currently selected item in the Option box
	virtual int readCurSelOptionItem (int OptionBoxID) = 0;

	// Selects the item in the Option box based on the item value
	virtual int selectOptionItem (int OptionBoxID,
								  const char* value) = 0;

	// Appends str to an existing string (can be used for outputting
	// status and error messages during transaction).
	virtual int writeStatus(const char *str, bool concatinate = true, int LangID = 0) = 0;
	
	// Returns the string corresponding to the StringID in a currently selected Language
	virtual char* getStdString (int StringID, const char *amount = 0) = 0;

	// Sets the Language to be used for outputting the standard strings
	virtual int setLanguage(int LanguageID) = 0;

	// Sets the Language to be used for outputting the standard strings
	virtual int getLanguage() = 0;

	// Cancel all outstanding waiting events
	virtual void cancelWait() = 0;

	// Waits for a specific event to be fired (e.g. button click, window close, etc.)
	virtual int waitForEvent(int wait_EventID[], int num_events, 
							int *received_EventID, 
							int timeout = SCS_TO_INFINITE) = 0;

	// Resets (clears) the box which displays options (which is populated by the 
	//	selectOption function)
	virtual void resetOption(int OptionBoxID) = 0;
};

#endif

