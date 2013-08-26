// AppSelect.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "Runtime/AccessManager.h"
#include "Runtime/UIControlInterface.h"
#include "Runtime/SCRControlInterface.h"
#include "Runtime/ApplSelControlInterface.h"
#include "Runtime/clcVSDC_constants.h"
#include "Runtime/POSControlVSDCImpl.h"
#include "EMV_Library/Prompter.h"
#include "EMV_Library/emv_constants.h"
#include "Runtime/CnfgControlImpl.h"
#include "Runtime/CryptoControlImpl.h"

#include "Utility/utility.h"
#ifdef _DEBUG
	using namespace std;
	#define PRINTF printf 
#else
	#define PRINTF /##/
#endif

#define TRUE 1
#define FALSE 0

int OpenServiceCntrl (ServiceControl *sc);
int OpenServices();
void outputDataObject(int tag, const byte *value, int value_sz);
void releasePOS (POSControlVSDCImpl **ppPOSControl);
char *createDataStr(const char *data_name, int Tag);
void outputDataItems ();

byte main_aid[] = {0x01}; //, {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10};
AccessManager AM(main_aid, 1);
UIControlInterface UI;
SCRControlInterface SCR;
//const byte zero_amount [6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

ApplSelControlInterface Selector;
POSControlVSDCImpl *POSControl;

HANDLE hThreadExit;
unsigned int threadExitID;
HANDLE hThreadSelect;
unsigned int threadSelectID;

bool retreiveByteData(int Tag, byte **data, int *data_len, char format[]);
void PrintReceipt(long TermDes);
unsigned  ThreadFunc_Exit( void* pArguments );
unsigned  ThreadFunc_SelectTrans( void* pArguments );
int MessageLoop (HANDLE* lphObjects, int cObjects);

int getNumberOfCents (byte curCode[]);

byte Amount[6];
byte AmountOther[6];
byte CurCode [2];
byte TransType;
byte TransInfo;
bool IsTransInitialized;
bool IsAmountInitialized;
bool IsAmountOtherInitialized;

// Event handlers for the reader control
void onInsert();
void onRemove();

bool TransInProgress;
long TransactionToken;
HANDLE hEventOnInsertExit;
HANDLE hRemove;

int _tmain(int argc, char* argv[])
{	
	printf ("Starting the SmartPOS Demo Terminal Application...\n");
	int res;

	// Initialize global variables
	IsTransInitialized = false;
	IsAmountInitialized = false;
	IsAmountOtherInitialized = false;
	memset(Amount, 0, 6);
	memset(AmountOther, 0, 6);


	// Check the integrity of the Certification Authority Public Keys
	CryptoControlImpl crypto;
	if ((res = OpenServiceCntrl(&crypto)) != SUCCESS)
		return res;

	int KeysVerified;
	if ((res = crypto.checkCAIntegrity (&KeysVerified)) != SUCCESS)
	{
		printf ("Certification Authority Public Key verification failed (%x, %d)\n", 
			res, KeysVerified);
		return res;
	}
	else
	{
		printf ("Public keys integrity is successfully verified (%d)\n",
				KeysVerified);
	}

	if ((res = OpenServices()) != SUCCESS)
		return res;

	if ((res = Selector.Initialize ()) != SUCCESS)
		return res;
	
	hEventOnInsertExit = CreateEvent(NULL, TRUE, FALSE, "ON_INSERT_EXIT");
	hRemove =            CreateEvent(NULL, TRUE, FALSE, "ON_REMOVE");

	// Build a list of terminal supported applications (read from the registry)
	ApplSelOperationEventImpl selOpEvent;

	Selector.addOperationEvent (&selOpEvent);
	
	res = Selector.BuildTerminalApplList ();

	if (res != SUCCESS)
	{
		printf ("Failed building the Terminal Application list.\n");
		printf ("  Error: %x\n", selOpEvent.getError());
		return selOpEvent.getError();
	}
	Selector.removeEvent ();
	PRINTF ("Terminal Application list is built successfully.\n");

	TransInProgress = false;
	

	// Register event handler functions with Smart Card Reader service
	SCR.RegisterEvent (ONINSERT, onInsert);
	SCR.RegisterEvent (ONREMOVE, onRemove);

	res = SCR.EstablishConnection ();
	if (res != SUCCESS)
	{
		printf ("Failed to establish connection with the card reader (%x)\n",
			res);
		Selector.CancelTransaction();
		AM.close (UI);
		AM.close (SCR);
		return res;
	}

	// Start new threads:
	// Thread tracking exit condition
	hThreadExit = (HANDLE)_beginthreadex( NULL, 0, &ThreadFunc_Exit, 
		0, 0, &threadExitID );
	// Thread prompting a user to select transaction and/or enter Amount
	hThreadSelect = (HANDLE)_beginthreadex( NULL, 0, &ThreadFunc_SelectTrans, 
		0, 0, &threadSelectID );
	
	printf ("Terminal is ready...\n");
	HANDLE hArr[] = {hThreadExit, hThreadSelect, hEventOnInsertExit};
	
	res = MessageLoop(hArr, 3);
	
	Selector.CancelTransaction();
	AM.close (UI);
	SCR.DestroyConnection ();
	AM.close (SCR);

	releasePOS(&POSControl);

	CloseHandle (hThreadExit);
	CloseHandle (hEventOnInsertExit);
	CloseHandle (hRemove);
	printf("Thank you for using the SmartPOS Demo Terminal Application.\n");
	return 0;
}


// This is event handler for the 'OnCardInsert' event
void onInsert ()
{
	if (TransInProgress) // Only one transaction allowed at a time
	{
		return;
	}
	TransInProgress = true;
	
	ResetEvent(hEventOnInsertExit);

	releasePOS (&POSControl);

	// Cancel Wait operation, so ThreadFunc_SelectTrans thread will terminate
	UI.cancelWait ();
	Sleep(100);
	
	Prompter prompt (&AM);
	tlv_parser tlv_AIP;
	TransactionToken = 0;
	int res;
	char str[80];

	if (!IsTransInitialized)
	{	// Transaction is not initialized -- prompt a user to select a transaction type
		res = prompt.promptTransactionType(&TransType, &TransInfo, EMV_LANG_LATIN1);
		if (res == SUCCESS)
		{
			IsTransInitialized = true;
		}
		else
		{
			// Exit transaction if transaction type cannot be retreived
			UI.writeStatus ("(OnInsert) Failed getting a Transaction Code");
			UI.setPrompt("(OnInsert) Remove the card");
			TransInProgress = false;
			SetEvent(hEventOnInsertExit); // Notify that the OnInsert function is done
			return;
		}
	}
	
	// Start a new transaction
	TransactionToken = 0;
	res = SCR.BeginTransaction (TransactionToken);
	if (res != SUCCESS && res != SCR_CARD_NOT_PRESENT)
	{
		UI.writeStatus ("(OnOnsert) Failed starting a new transaction");
		UI.setPrompt("(OnInsert) Remove the card");
		TransInProgress = false;
		SetEvent(hEventOnInsertExit); // Notify that the OnInsert function is done
		return;
	}
	
	tlv_parser tlv_Appl;
	ApplSelOperationEventImpl selOpEvent;
	
	// Add Operation Event to Selector
	if ((res = Selector.addOperationEvent (&selOpEvent)) != SUCCESS)
	{
		UI.writeStatus ("Failed to add Operation Event to the Application Select control");
		TransInProgress = false;
		SCR.EndTransaction (TransactionToken);
		SetEvent(hEventOnInsertExit); // Notify that the OnInsert function is done
		return;
	}
	UI.setPrompt("Processing...");

	// SELECT APPLICATION
	res = Selector.EMV_ApplicationSelection(TransactionToken);
	Selector.removeEvent ();
	if (res != SUCCESS)
	{
		sprintf (str, "Select Application Error: %#X", selOpEvent.getError());
		UI.writeStatus (str);
	}

	POSOperationEventImpl posOpEvent;
	bool bApplicationSelected = false;
	TransactionToken = selOpEvent.getTransactionToken();
	while (res == SUCCESS)
	{
		int sel_data_len = selOpEvent.getLength();
		if (sel_data_len <= 0)
		{
			UI.writeStatus ("(MAIN) Unexpected data (Application Selection)");
			res = -1;
			break;
		}
		byte *sel_data = 0;
		selOpEvent.getByteString(&sel_data);

		if ((res = tlv_Appl.parse (sel_data, sel_data_len)) != SUCCESS)
		{
			UI.writeStatus ("Failed to parse data (Application Selection)");
			break;
		}
		// Start EMV transaction
		// -----------------------------------
		// Initiate Application Processing
		//------------------------------------
		
		// Extract Application Identifier (wich is stored in
		// DF Name of FCI of a selected ADF (tag '84')
		tlv_parser *parser_aid = tlv_Appl.Find (0x84);
		if (!parser_aid)
		{
			UI.writeStatus ("(MAIN) Unexpected data (Cannot find DF Name)");
			res = -1;
			break;
		}
		// Create a POS module
		POSControl = new POSControlInterface(parser_aid->GetRoot ()->GetValue (),
										parser_aid->GetRoot ()->GetLengthVal ());
		if (!POSControl)
		{
			UI.writeStatus ("(MAIN) Failed to create POS Control");
			res = ERR_MEMORY_ALLOC;
			break;
		}
		
		// Load appropriate POSControl
		if ((res = OpenServiceCntrl(POSControl)) != SUCCESS)
		{
			UI.writeStatus ("(MAIN) Failed to open POSControl");
			delete POSControl;
			POSControl = 0;
			// Continue With the next application in the candidate list
			//Attempting to select the next application in a list
			selOpEvent.resetEvent(true);
			Selector.addOperationEvent (&selOpEvent);
			res = Selector.EMV_SelectNext();
			Selector.removeEvent ();
			if (res != SUCCESS)
			{
				sprintf (str, "Select Application Error: %#X", selOpEvent.getError());
				UI.writeStatus (str);
				break;
			}
			continue;
		}
		
		TRANS_STARTUP_PARAMS params;
		memset (&params, 0, sizeof(TRANS_STARTUP_PARAMS));
		params.TransactionType = TransType;
		params.TransactionInfo = TransInfo;
		params.TransactionToken = TransactionToken;
		if (IsAmountInitialized)
		{
			memcpy (params.AmountAuthorized, Amount, 6);
			memcpy (params.CurrencyCode, CurCode, 2);
		}
		else
		{
			memset (params.AmountAuthorized, 0, 6);
			memset (params.CurrencyCode, 0, 2);
		}
		if (IsAmountOtherInitialized)
			memcpy (params.AmountOther, AmountOther, 6);
		else
			memset (params.AmountOther, 0, 6);
		
		UI.setPrompt ("Processing...");
		
		if ((res = POSControl->initPOS(&params)) != SUCCESS)
		{
			UI.writeStatus ("(MAIN) Failed to initialize POS");
			AM.close(*POSControl);
			delete POSControl;
			POSControl = 0;
			break;
		}

		// Add operation Event to POSControl
		posOpEvent.resetEvent(true);
		POSControl->addOperationEvent (&posOpEvent);

		// Initiate Application Processing
		res = POSControl->execPOS (tlv_Appl.GetRoot ()->GetDataObject (),
								   tlv_Appl.GetRoot ()->GetDataObjectLen ());
		POSControl->removeEvent ();
		if (res == SUCCESS)
		{
			break;
		}
		else
		{
			UI.writeStatus ("(MAIN) Application Selection FAILED");
			if (posOpEvent.getError() == ERR_APPL_INIT_CONDITIONS_NOT_SATISFIED)
			{
				releasePOS(&POSControl);
				// Continue With the next application in the candidate list
				//Attempting to select the next application in a list
				selOpEvent.resetEvent(true);
				Selector.addOperationEvent (&selOpEvent);
				res = Selector.EMV_SelectNext();
				Selector.removeEvent ();
				if (res != SUCCESS)
				{
					UI.writeStatus ("Failed to initialize Application");
					UI.writeStatus ("No Application is selected");
					break;
				}
			}
			else
			{
				break;
			}
		}
	} // End Of While Loop

	if (res == SUCCESS && POSControl)
	{
		long TermDes;
		posOpEvent.getLong(&TermDes);
		PrintReceipt(TermDes);
		outputDataItems();
		//MessageBox (NULL, "After outputDataItems", "MAIN", MB_OK);
		UI.writeStatus ("", false);
	}
	else
	{
		if (POSControl)
		{
			char bf[100];
			sprintf (bf, "Error while executing POS. res = %#X, error = %#X, operation = %#X",
				res, posOpEvent.getError(), posOpEvent.getOperation());
			UI.writeStatus (bf);
		}
	}
	
	// End Transaction
	UI.setPrompt ("Remove Card");
	SCR.EndTransaction(TransactionToken);
	releasePOS (&POSControl);
	TransInProgress = false;
	SetEvent(hEventOnInsertExit); // Notify that the OnInsert function is done
}

void onRemove ()
{
	if (WaitForSingleObject(hRemove, 0) == WAIT_OBJECT_0)
		return;
	else
		SetEvent(hRemove);

	Selector.CancelTransaction();
	SCR.EndTransaction (TransactionToken);
	Sleep(100);
	SCR.DestroyConnection ();
	UI.cancelWait();
	WaitForSingleObject(hEventOnInsertExit, INFINITE); // Wait Until OnInsert is done
	UI.writeStatus ("", false);
	//UI.resetOption (OPTIONLIST_TRANSACTIONS);
	UI.resetAmount(PURCHASE_AMOUNT);
	UI.resetAmount(CASHBACK_AMOUNT);
	
	hThreadSelect = (HANDLE)_beginthreadex( NULL, 0, &ThreadFunc_SelectTrans, 
		0, 0, &threadSelectID );
	CloseHandle (hThreadSelect);
	ResetEvent(hRemove);
	PRINTF("OnRemove is done\n");
}

int OpenServices()
{
	int res;
	// Open UI service and start the application window
	if ((res = OpenServiceCntrl(&UI)) != SUCCESS)
		return res;

	// Open SCR service
	if ((res = OpenServiceCntrl(&SCR)) != SUCCESS)
		return res;

	// Open Application Selection Control
	if ((res = OpenServiceCntrl(&Selector)) != SUCCESS)
		return res;
	return SUCCESS;
}

int OpenServiceCntrl (ServiceControl *sc)
{
	int res;
	// Open UI service and start the application window
	printf("Opening the Service: %s\n", sc->getServiceName());
	if (sc->getInterfaceType () == INTERFACE_TYPE_POS)
		res = AM.open((POSControlInterface*)sc);
	else
		res = AM.open(sc);
	if (res != SUCCESS)
	{
		printf ("FAIED to open, ERROR: %x\n", res);
		return res;
	}
	else
	{ 
		printf("    Opened successfully!\n");
	}
	return SUCCESS;
}


void outputDataObject(int tag, const byte *value, int value_sz)
{
	char *buff;
	
	char str [80];
	sprintf (str, "Data Object Tag [%X]:", tag);
	UI.writeStatus (str);
	if (!value || value_sz <= 0)
	{
		UI.writeStatus ("Data is not found");
	}
	else
	{
		buff = DumpByteArr(value, value_sz );
		UI.writeStatus (buff);
		delete [] buff;
	}
	return;
}

unsigned  ThreadFunc_Exit( void* pArguments )
{
	// Wait for Cancel button to exit an application
	int btn = 0;
	int EventID;
	int res;
	int waitingEvent;
	UI.setLanguage (EMV_LANG_LATIN1);
	while (true)
	{
		//UI.setPrompt ("To exit the application close the window");
		waitingEvent = BTN_EXIT;
		res = UI.waitForEvent (&waitingEvent, 1, &EventID);
		if (res == SUCCESS)
		{
			// Confirm exit
			btn = MessageBox (NULL, "Are you sure you want to leave an application?",
					"Conformation", MB_YESNO);
			if (btn == IDYES)
			{	
				UI.cancelWait();
				Sleep(100);
				break;
			}
			else 
				continue;
		}
		else 
		{
			if (res == OPERATION_CANCELED_BY_USER &&
				EventID == CANCEL_WAIT)
				continue;
			else
				break;
		}
	}
	if (TransInProgress == false)
		SetEvent(hEventOnInsertExit);
	PRINTF ("*****   Exiting ThreadFunc_Exit function  (%x) ****\n", res);
	_endthreadex(0);
	return 0;
}

unsigned  ThreadFunc_SelectTrans( void* pArguments )
{
	Prompter prompt (&AM);
	IsTransInitialized = false;
	IsAmountInitialized = false;
	int res;
	memset(Amount, 0, 6);
	memset(CurCode, 0, 2);
	memset(AmountOther, 0, 6);

	res = prompt.promptTransactionType(&TransType, &TransInfo, EMV_LANG_LATIN1);
	if (res == SUCCESS)
	{
		IsTransInitialized = true;
	
		if (check_bit(TransInfo, 0x01)) // Amount required
		{
			res = prompt.promptAmount(true, Amount, CurCode, EMV_LANG_LATIN1);
			if (res == SUCCESS)
			{
				if (memcmp(Amount, zero_amount, 6) != 0)
				{
					IsAmountInitialized = true;
					if (check_bit(TransInfo, 0x02)) // Cashback -- AmountOther required
					{
						res = prompt.promptAmount (false, AmountOther, NULL, EMV_LANG_LATIN1);
						if (res == SUCCESS)
						{
							IsAmountOtherInitialized = true;
						}
					}
				}
			}
		}
	}

	if (res == SUCCESS && !TransInProgress)
		UI.setPrompt ("Please insert the card");
	PRINTF ("*****   Exiting ThreadFunc_SelectTrans function  (%x) ****\n", res);
	
	_endthreadex(0);
	return 0;
}


void releasePOS (POSControlVSDCImpl **ppPOSControl)
{ 
	if (*ppPOSControl)
	{
		if ((*ppPOSControl)->opened ())
		{
			AM.close(**ppPOSControl);
			delete *ppPOSControl;
			*ppPOSControl = 0;
		}
	}
}

void outputDataItems ()
{
	int res, btn, iTag;
	char *cTag;
	int initSize = 10;
	byte *data_value = new byte [initSize];
	UIOperationEventImpl opEvent;
	UI.addOperationEvent (&opEvent);
	
	res = UI.receiveString ("Enter a tag (decimal) of the Data Object to see the value", INFINITE);
	while (res == SUCCESS)
	{
		opEvent.getButton (&btn);
		if (btn != BTN_ENTER)
		{
			break;
		}
		else
		{
			opEvent.getString(&cTag);
			iTag = atoi(cTag);
			char *str_val = 0;
			str_val = createDataStr("Data Object:", iTag);
			if (str_val)
			{
				UI.writeStatus (str_val);
				delete [] str_val;
				str_val = 0;
			}
			opEvent.resetEvent (true);
			res = UI.receiveString ("Enter a tag (decimal) of the Data Object to see the value", INFINITE);
			continue;
		}
	}
	if (data_value)
		delete [] data_value;
	UI.removeEvent ();
}

void PrintReceipt(long TermDes)
{
	if (!UI.opened())
		return;

	byte trans_results [1];
	int size = 1;
	char format[4];

	if (!POSControl)
	{
		UI.writeStatus ("POS not initialized");
		return;
	}
	if( !POSControl->opened ())
	{
		UI.writeStatus ("POS Control not opened");
		return;
	}
	int res = POSControl->getTransData(0x50000004, trans_results, &size, 
									   format, true);
	if (res != SUCCESS || size != 1)
	{
		UI.writeStatus ("Cannot retreive transaction results");
		return;
	}



	char *str_val;
	UI.writeStatus ("");
	UI.writeStatus ("---- Transaction Receipt ----");
	
	str_val = createDataStr("Application:", 0x9f12);
	if (strcmp(str_val, "Application: (0x9F12):") == 0)
	{
		delete [] str_val;
		str_val = createDataStr("Application:", 0x50);
	}
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	if (TermDes == TERMINAL_APPROVE)
		UI.writeStatus (Language::getString (MSG_ID__APPROVED, DEFAULT_LANG));
	else
		UI.writeStatus(Language::getString (MSG_ID__DECLINED, DEFAULT_LANG));

	str_val = createDataStr("Transaction Date", 0x9a);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("Transaction Time", 0x9f21);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("Transaction Amount", 0x9f02);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}
	byte data_value[6];
	char frmt[4];
	int data_size = 6;
	if (POSControl->getTransData(0x9f03, data_value, &data_size, frmt, true) == SUCCESS)
	{
		str_val = createDataStr("Cashback Amount", 0x9f03);
		if (str_val)
		{
			UI.writeStatus (str_val);
			delete [] str_val;
		}
	}

	str_val = createDataStr("Application Identifier", 0x4f);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("Primary Account Number", 0x5a);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("Authorization Response Code", 0x8a);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("TVR", 0x95);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("TSI", 0x9b);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	if (check_bit(trans_results[0], 0x02))
	{
		UI.writeStatus ("Advice is required");
		if (((trans_results[0]>>2) & 0x07) == 0x01)
			UI.writeStatus ("Advice reason: Service not allowed");
		else if (((trans_results[0]>>2) & 0x07) == 0x02)
			UI.writeStatus ("Advice reason: PIN Try Limit exceeded");
		else if (((trans_results[0]>>2) & 0x07) == 0x03)
			UI.writeStatus ("Advice reason: Issuer authentication Failed");
	}
	if (check_bit(trans_results[0], 0x20))
	{
		str_val = createDataStr("Signature is required for", 0x5f20);
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	str_val = createDataStr("Issuer Script Result:", 0x9F5B);
	if (str_val)
	{
		UI.writeStatus (str_val);
		delete [] str_val;
	}

	UI.writeStatus ("------------------------------------");
}

char *createDataStr(const char *data_name, int Tag)
{
	byte *buff;
	int buff_len;
	char *full_str;
	char data_format[4];
	if (retreiveByteData (Tag, &buff, &buff_len, data_format))
	{
		if (buff && buff_len > 0)
		{
			char *str_val = 0;
			bool am_failed = true;
			if (Tag == 0x9f02 || Tag == 0x9f03)
			{
				// Convert Amount numeric to character string
				str_val = new char [14];
				char dlrAmount[13];
				char ctsAmount[13];
				byte curCode[2];
				int res = getNumberOfCents (curCode);
				if (res != SUCCESS)
				{
					am_failed = true;
				}
				else
				{
					res = numeric2asciAmount(dlrAmount, ctsAmount,
										 (curCode[0] >> 4), buff);
					if (res == SUCCESS)
					{
						am_failed = false;
						sprintf (str_val, "%s.%s", dlrAmount, ctsAmount);
					}
					else
						am_failed = true;
				}
			}
			if (am_failed)
			{
				if (strcmp(data_format, "an") == 0 ||
					strcmp(data_format, "ans") == 0)
				{
					str_val = new char [buff_len + 1];
					if (str_val)
					{
						for (int i = 0; i < buff_len; i++)
							str_val[i] = (char)(buff[i]);
						str_val[buff_len] = '\0';
					}
				}
				else if (data_format[0] == 'd')
				{
					long lVal = LongFromByte(buff, buff_len);
					str_val = new char [32];
					if (str_val)
						sprintf(str_val, "%d", lVal);
				}
				else
					str_val = DumpByteArr (buff, buff_len);
			}
			if (str_val)
			{
				full_str = new char [strlen(str_val) + strlen(data_name) + 14];
				sprintf (full_str, "%s (%X): %s", data_name, Tag, str_val);
				delete [] str_val;
				return full_str;
			}
			delete [] buff;
		}
	}
	full_str = new char [strlen(data_name) + 13];
	sprintf (full_str, "%s (%X):", data_name, Tag);
	return full_str;
}

bool retreiveByteData(int Tag, byte **data, int *data_len, char format[])
{
	*data_len = 0;
	*data = 0;
	int init_len = 10;
	byte *data_val = new byte [init_len];
	if (!POSControl && !POSControl->opened ())
	{
		return false;
	}
			
	int res = POSControl->getTransData(Tag, data_val, &init_len, format, false);
	if (res == ERR_BUFFER_OVERFLOW)
	{
		delete [] data_val;
		data_val = new byte [init_len];
		res = POSControl->getTransData(Tag, data_val, &init_len, format, false);
	}

	if (res == SUCCESS)
	{
		*data_len = init_len;
		*data = data_val;
		return true;
	}
	else
	{
		delete [] data_val;
		return false;
	}
}

int getNumberOfCents (byte curCode[])
{
	byte *data;
	int data_len;
	char format [5];
	int res;
	CnfgControlInterface Cnfg;
	CnfgOperationEventImpl opEventKey;
	CnfgOperationEventImpl opEventVal;

	// Get Transaction Currency from the Context
	if (retreiveByteData(0x5f2a, &data, &data_len, format))
	{
		if (data_len != 2)
		{
			delete [] data;
			return -1;
		}
		if ((res = AM.open(&Cnfg)) != SUCCESS)
		{
			delete [] data;
			return res;
		}

		Cnfg.addOperationEvent(&opEventKey);
		res = Cnfg.enumKeys (CNFG_TERMINAL, "CurrencyCodes");
		Cnfg.removeEvent();
		if (res != SUCCESS)
		{
			delete [] data;
			return opEventKey.getError ();
		}
	
		int numTypes;
		if ((numTypes = opEventKey.getLength ()) <= 0)
		{
			delete [] data;
			return -1;
		}

		char **trCode;
		if ((res = opEventKey.getStringArray (&trCode)) != SUCCESS)
		{
			delete [] data;
			return opEventKey.getError ();
		}
	
		Cnfg.addOperationEvent (&opEventVal);
	
		res = SUCCESS;
		int i = 0;
		for (int k = 0; k < numTypes; k++)
		{
			opEventVal.resetEvent (true);
			// Build a sub key for current currency
			char *subKey = new char [15 + strlen (trCode[k])];
			if (!subKey)
			{
				// Memory allocation error
				delete [] data;
				return ERR_MEMORY_ALLOC;
			}

			strcpy (subKey, "CurrencyCodes");
			strcat(subKey, "\\");
			strcat (subKey, trCode[k]);
			res = Cnfg.getValue (CNFG_TERMINAL, "Data", subKey);
			delete [] subKey;
			if (res != SUCCESS)
			{
				delete [] data;
				return res;
			}

			byte *curData;
			opEventVal.getByteString (&curData);
			int data_sz = opEventVal.getLength ();
			if (data_sz != data_len)
			{
				delete []data;
				return res;
			}
			if ((curData[0] & 0x0f) == data[0] &&
				curData[1] == data[1])
			{
				// Found match
				curCode[0] = curData[0];
				curCode[1] = curData[1];
				delete [] data;
				return SUCCESS;
			}
		}
	}
	delete [] data;
	return -1;
}

int MessageLoop ( 
    HANDLE* lphObjects,  // handles that need to be waited on 
    int     cObjects     // number of handles to wait on 
  )
{ 
    // The message loop lasts until we get a WM_QUIT message,
    // upon which we shall return from the function.
    while (TRUE)
    {
        // block-local variable 
        DWORD result ; 
        MSG msg ; 

        // Read all of the messages in this next loop, 
        // removing each message as we read it.
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        { 
            // If it's a quit message, we're out of here.
            if (msg.message == WM_QUIT)  
                return 0; // Quit
            // Otherwise, dispatch the message.
			DispatchMessage(&msg); 
        } // End of PeekMessage while loop.

        // Wait for any message sent or posted to this queue 
        // or for one of the passed handles be set to signaled.
        result = WaitForMultipleObjects(cObjects, lphObjects, 
                 TRUE, 100/*, QS_ALLINPUT*/); 
		
        // The result tells us the type of event we have.
		if (result == WAIT_TIMEOUT)
		{
			// Timeout elapsed, continue waiting
			continue;
		}
        else if (result == (WAIT_OBJECT_0 + cObjects))
        {
			// New messages have arrived. 
            // Continue to the top of the always while loop to 
            // dispatch them and resume waiting.
            continue;
        } 
        else 
        { 
            // All of the handles became signaled. 
            return 1; // All of the handles are signaled 
        } // End of else clause.
    } // End of the always while loop. 
} // End of function.
