// UIControl Service
// UIControl Interface Implementation -- Server Side
//
// UI is implemented as a terminal Window. It provides basic functionality 
// for user to be able to select an application, enter amount, click 
// buttons in response to prompts, see the execution status.

#ifndef UICONTROLIMPL_H
#define UICONTROLIMPL_H

#include "UIOperationEventImpl.h"
#include "../Utility/utility.h"
#include "CnfgControlImpl.h"
#include "AccessManager.h"
#include "resource.h"
#include "custom_resource.h"
#include "UIInterface.h"
#include "EventAdder.h"
#include "amAdder.h"



#define AMOUNT_SIZE          12
#define CENTS_SIZE           2
#define TRANSACTION_STATUS_SIZE  10000


#define _timeout(timeout) (timeout == SCS_TO_INFINITE) ? INFINITE: timeout

class UIControlImpl :
	public EventAdder,
	public OperationEvent,
	public amAdder,
	public ServiceControl,
	public UIInterface
{
public:
	UIControlImpl();

	virtual ~UIControlImpl(void);

	// Outputs string and returns
	virtual int setPrompt(const char* prompt, int LangID = 0);
	// Outputs a prompt to the user, and then waits for user input
	virtual int receiveString(const char *prompt, int timeout = SCS_TO_INFINITE,
									int LangID = 0);

	// Promts a user to enter an amount of transaction and the currency code,
	// and waits until the user enters the amount and clicks a button
	virtual int getAmount(AMOUNT_TYPE amount_type,
						  byte Amount[], 
						  byte CurrencyCode [], 
						  int timeout = SCS_TO_INFINITE, int LangID = 0);
	// Just reads the amount from the Amount field - doesn't prompt a 
	// user and doesn't wait for a user input
	virtual int readAmount(AMOUNT_TYPE amount_type,
						   byte Amount[], byte CurrencyCode []);
	// Clears the amount field
	virtual void resetAmount(AMOUNT_TYPE amount_type);
	// Outputs a question to the user, and then waits for user to click
	// a button
	virtual int getResponse(const char *strQuestion, int timeout = SCS_TO_INFINITE,
						  int LangID = 0);
	// Outputs a prompt together with a set of options to the user,
	// and then waits until the user selects one of the options
	virtual int selectOption(int OptionBoxID,
							 const char *prompt,
							 const char * const optionList[],
							 const int dataList[],
							 const unsigned int numberOfOptions,
							 int timeout = SCS_TO_INFINITE,
							 int *LangID = 0);
	// Clears an OptionList box
	virtual void resetOption(int OptionBoxID);
	// Appends str to an existing string (can be used for outputting
	// status and error messages during transaction).
	virtual int writeStatus(const char *str, bool concatinate = true,
		int LangID = 0);
	virtual char* getStdString (int StringID, const char *amount = 0);
	//Sets the language, but doesn't do anything with it in this implementation;
	// This implementation uses ASCII character set for output, which is for all 
	// printable characters is same as ISO 8859-1 Latin 1.
	virtual int setLanguage(int LanguageID);
	virtual int getLanguage();
	virtual void cancelWait();
	virtual int waitForEvent(int wait_EventID[], int num_events, 
		int *received_EventID, int timeout = SCS_TO_INFINITE);
	// Outputs a prompt and then waits until the user selects one of the
	// options from the pre-populated list (or combo) box
	virtual int getOption (int OptionBoxID,
						   const char *prompt, 
						   int timeout = SCS_TO_INFINITE,
						   int LangID = 0);
	// Reads data from the Option box at the specified index (indx)
	virtual int readOptionItem (int OptionBoxID, int indx);
	// Reads currently selected item in the Option box
	virtual int readCurSelOptionItem (int OptionBoxID);
	// Selects the item in the Option box based on the item value
	virtual int selectOptionItem (int OptionBoxID,
								  const char* value);

	// UI Interface Definition
	// Sets the value of the text box
	virtual int setText(const int TextBoxID, 
						const char* text, int LangID = 0);
	// UI Interface Definition
	// Sets the value of the text box
	virtual int getText(const int TextBoxID);

private: //Private member functions
	long checkInitialization (bool checkEvent = true);
	bool IsWindow ();
	int WaitForButtonClick (DWORD timeout);
	int WaitForEvent (HANDLE *pHandles, DWORD nCount, DWORD timeout);
	bool IsValidEvent (int EventID);
	UNINT handle2event (HANDLE hndl);
	HANDLE event2handle(UNINT eventID);
	int SetDefaultCurrencyID(byte CurrencyCode[]);
	bool checkEvent(int wait_EventID[], int num_events, int event_id, int *indx);
	int readOptionItem (HWND &hwndList, int item_indx, 
						char **item_text, int *item_data);
	int GetControlID(const int ControlID);
	int setControlText(const int TextBoxID, 
					const char* text, int LangID);
private: //Private members
	HWND *hwndDlg; // Handle to a dialog window
	HANDLE *hThread; // handle to a thread where dialog window is running
	HANDLE *EventIDC_ENTER;
	HANDLE *EventIDC_CANCEL;
	HANDLE *EventIDC_CLEAR;
	HANDLE *EventIDC_EXTERNAL_CANCEL;
	HANDLE *EventIDC_EXIT;
protected:
        int LanguageID;
	bool IsValidLanguage(int LangID);

};

#endif
