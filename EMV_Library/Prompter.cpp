#include "Prompter.h"
#include "../Runtime/stdafx.h"

Prompter::Prompter(AccessManager *pAccessManager)
{
	pAM = pAccessManager;
}

Prompter::~Prompter(void)
{
}

// Prompts a user to enter an amount of transaction 
int Prompter::promptAmount(bool AmountAuthorised, 
						   byte Amount[], byte curCode[], int LangID)
{
	int res;
	UIControlImpl UI;

	if ((res = pAM->open (&UI)) != SUCCESS)
		return res;
	
	byte amount [6]; // Amount is defined as a 6-byte data element
	byte currency[2]; // Currency code is dfined as a 2-byte element
	UIOperationEventImpl opEvent;

	bool flgConfirm = false;
	byte *UIFlag = 0;
	int len;
	res = GetUIFlag (&UIFlag, &len);
	if (res == SUCCESS)
	{
		if (len > 0)
		{
			if (check_bit(UIFlag [0], 0x04))
				flgConfirm = true;
			delete [] UIFlag;
		}
	}

	// Prompt the user to enter the amount and wait for the response
	if (AmountAuthorised)
		UI.writeStatus ("Enter the Amount of transaction");
	else
		UI.writeStatus ("Enter the Cashback Amount");

	while (true)
	{
		opEvent.resetEvent (true);
		if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
		{
			pAM->close(UI);
			return res;
		}

		if (AmountAuthorised)
			res = UI.getAmount (PURCHASE_AMOUNT, amount, currency, SCS_TO_INFINITE, LangID);
		else
			res = UI.getAmount (CASHBACK_AMOUNT, amount, currency, SCS_TO_INFINITE, LangID);
		UI.removeEvent ();
		
		if (res == SUCCESS)
		{
			int btn;
			opEvent.getButton (&btn);
			if (btn == BTN_ENTER)
			{
				bool ConfirmOK = false;
				if (flgConfirm)
				{
					// Verify the entered amount
					// Convert Amount numeric to character string
					char charAmount[14];
					char dlrAmount[13];
					char ctsAmount[13];
					res = numeric2asciAmount(dlrAmount, ctsAmount,
											(currency[0] >> 4), amount);
					if (res != SUCCESS)
					{
						pAM->close(UI);
						return res;
					}
					sprintf (charAmount, "%s.%s", dlrAmount, ctsAmount);
					char *amountStr = Language::getStdString (MSG_ID__AMOUNT_OK, 
						DEFAULT_LANG, charAmount);
					if (!amountStr)
					{
						pAM->close(UI);
						return ERR_MEMORY_ALLOC;
					}

					opEvent.resetEvent (true);
					if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
					{
						pAM->close(UI);
						delete [] amountStr;
						return res;
					}
					res = UI.getResponse (amountStr, SCS_TO_INFINITE);
					UI.removeEvent ();
					delete [] amountStr;

					if (res == SUCCESS)
					{
						opEvent.getButton (&btn);
						if (btn == BTN_ENTER)
						{
							ConfirmOK = true;
						}
						else if (btn == BTN_CANCEL)
							continue;
						else if (btn == BTN_CLEAR)
						{
							if (AmountAuthorised)
								UI.resetAmount(PURCHASE_AMOUNT);
							else
								UI.resetAmount(CASHBACK_AMOUNT);
							continue;
						}
						else
						{
							res = OPERATION_CANCELED_BY_USER;
							break;
						}
					} 
					else // GetResponse retuned Error
					{
						if (res == EVT_ERROR)
							res = opEvent.getError ();
						break;
					}
				} // End of Conformation
				if (!flgConfirm || ConfirmOK)
				{
					memcpy (Amount, amount, 6);
					if (curCode)
						memcpy (curCode, currency, 2);
					pAM->close(UI);
					return SUCCESS;
				}
				else
					break;
			} // End Of Enter click button
			else // Cliked button is not BTN_ENTER
			{
				memset (Amount, 0, 6);
				if (curCode)
					memset (curCode, 0, 2);
				break;
			}
		}
		else // getAmount returned Error
		{
			if (res == EVT_ERROR)
				res = opEvent.getError ();
			break;
		}
	} // While loop
	pAM->close(UI);
	return res;
}

// Prompts a user to enter amount for a cashback transaction
int Prompter::promptAmountOther(byte Amount[], int LangID)
{
	int res;
	UIControlImpl UI;
	if ((res = pAM->open (&UI)) != SUCCESS)
		return res;

	byte amount [6]; // Amount is defined as a 6-byte data element
	byte curCode[2]; // Currency code is dfined as a 2-byte element
	UIOperationEventImpl opEvent;
	if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
	{
		pAM->close(UI);
		return res;
	}

	// Prompt the user to enter the amount and wait for the response
	res = UI.getAmount (CASHBACK_AMOUNT, amount, curCode, SCS_TO_INFINITE, LangID);
	UI.removeEvent ();
	
	if (res == SUCCESS)
	{
		int btn;
		opEvent.getButton (&btn);
		if (btn == BTN_ENTER)
		{
			memcpy (Amount, amount, 6);
		}
		else
		{
			memset (Amount, 0, 6);
		}
	}
	pAM->close(UI);
	return res;
}

int Prompter::promptTransactionType(byte *trans, byte *trans_info, int LangID)
{
	int res;
	UIControlImpl UI;

	if ((res = pAM->open (&UI)) != SUCCESS)
		return res;

	UIOperationEventImpl opEvent;
	if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
		return res;

	// Check if the Transaction type box is empty
	res = UI.readOptionItem (OPTIONLIST_TRANSACTIONS, 0);
	UI.removeEvent ();
	if (res == SUCCESS)
	{
		// Option box is not empty, do not populate it.
		res = SelectFromAvailableOptions(UI, trans, trans_info, LangID);
		pAM->close(UI);
		return res;
	}
	else if (res == ERR_TERMINAL_WINDOW_IS_UNAVAILABLE)
	{
		pAM->close(UI);
		return res;
	}

	int *codes;
	char **transNames;
	int size;

	// Get a list of all transactions types supported by a terminal
	res = getTransactions (&codes, &transNames, &size);
	if (res != SUCCESS)
	{
		pAM->close(UI);
		return res;
	}

	
	opEvent.resetEvent (true);
	if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
	{
		pAM->close(UI);
		return res;
	}
/*
	res = UI.selectOption (OPTIONLIST_TRANSACTIONS, "Select transaction type", 
		transNames, codes, size, 
		SCS_TO_INFINITE, &LangID);
	UI.removeEvent ();

	if (res != SUCCESS)
	{
		if (res == EVT_ERROR)
			res = opEvent.getError ();
	}
	else // res == SUCCESS
	{
		int selected;
		opEvent.getButton(&selected);
		if (selected == BTN_ENTER)
		{
			// Enter button is clicked, find out the index of the selected application
			opEvent.getIndex (&selected);
			if (selected >= 0)
			{
				// Get Selected Data
				int data_val;
				opEvent.getData(&data_val);

				// Assign the extracted values to the return parameters
				*trans = (byte)(data_val >> 8);
				*trans_info = (byte)data_val;
			}
			else
				res = OPERATION_CANCELED_BY_USER;
		}
		else
			res = OPERATION_CANCELED_BY_USER;
	}
	
	for (int i = 0; i < size; i++)
	{
		delete [] transNames [i];
	}
*/
	printf("Please select transaction type:\n");
	int i;
	for( i = 0; i < size; i++){
		printf("%d: (0x%04x)%s\n", i, codes[i], transNames[i]);
	}
	//printf("?");
	//scanf("%d",&i);
	i = 23;
	*trans = (byte)(codes[i] >> 8);
	*trans_info = (byte)codes[i];
	delete [] transNames;
	delete [] codes;
	pAM->close(UI);
	return res;
}

int Prompter::SelectFromAvailableOptions(UIControlImpl &UI, 
										 byte *trans, 
										 byte *trans_info, 
										 int LangID)
{
	UIOperationEventImpl opEvent;
	int res;
	if ((res = UI.addOperationEvent (&opEvent)) != SUCCESS)
		return res;

	res = UI.getOption(OPTIONLIST_TRANSACTIONS, "Select transaction type",
			SCS_TO_INFINITE, LangID);
	UI.removeEvent ();
	if (res == SUCCESS)
	{
		// getOption SUCCEEDED
		int btn;
		opEvent.getButton (&btn);
		if (btn == BTN_ENTER)
		{
			// Option is successfully selected.
			// Get data for the selected item.
			int item_data;
			opEvent.getData(&item_data);
			*trans = (byte)((item_data >> 8) & 0x000000ff);
			*trans_info = (byte) (item_data & 0x000000ff);
		}
		else
		{
			// Some other button is clicked by a user
			res = OPERATION_CANCELED_BY_USER;
		}
	}
	else
	{
		if (res == EVT_ERROR)
			res = opEvent.getError ();
	}
	return res;
}

int Prompter::getTransactions (int **codes, char ***transNames, int *size)
{
	int res;
	char **asciCode;
	char **trName;
	int *hexCode;
	
	CnfgControlImpl CNFG;
	
	if (( res = pAM->open(&CNFG)) != SUCCESS)
		return res;

	CnfgOperationEventImpl opEvent;

	CNFG.addOperationEvent (&opEvent);
	res = CNFG.enumKeys (CNFG_TERMINAL, "TransactionTypes");
	CNFG.removeEvent();
	if (res != SUCCESS)
	{
		if (res == EVT_ERROR)
			res = opEvent.getError ();
	}
	
	int numTypes;
	if ((numTypes = opEvent.getLength ()) <= 0)
		return ERR_TRANSACTION_TYPES_MISSING;

	if ((res = opEvent.getStringArray (&asciCode)) != SUCCESS)
	{
		if (res == EVT_ERROR)
			res = opEvent.getError ();
	}
	
	hexCode = new int [numTypes];
	if (!hexCode)
		return ERR_MEMORY_ALLOC;
	trName = new char* [numTypes];
	if (!trName)
	{
		delete [] hexCode;
		return ERR_MEMORY_ALLOC;
	}

	CnfgOperationEventImpl op;
	CNFG.addOperationEvent (&op);
	
	res = SUCCESS;
	int i = 0;
	int k;
	for ( k = 0; k < numTypes; k++)
	{
		trName[i] = 0;
		hexCode[i] = 0;

		op.resetEvent (true);
		
		// Get the transaction Type code
		byte hex_val;
		int hex_len = 1;    //strlen("TransactionTypes") = 16
		res = AsciiStr2HexByte(asciCode[k]+16, 2,   
			    	     	     &hex_val, &hex_len);
		if (res != SUCCESS)
		{
			res = SUCCESS;
			continue;
		}
		hexCode[i] = 0x000000ff & hex_val;
		hexCode[i] <<= 8;

		// reset Transaction type
		CNFG.setTransactionType("");

		// Get Transaction name
		res = CNFG.getValueString(CNFG_TRANSACTION, asciCode[k]);
		if (res != SUCCESS)
		{
			res = SUCCESS;
			continue;
		}
		
		int len = op.getLength ();
		if (len <= 0)
		{
			continue;
		}
		trName[i] = new char [len + 1];
		if (!trName[i])
		{
			res = ERR_MEMORY_ALLOC;
			break;
		}

		char *zz;
		op.getString (&zz);
		strcpy (trName[i], zz);

		// Get Transaction details  //strlen("TransactionTypes") = 16
		res = CNFG.setTransactionType(asciCode[k] + 16);
		if (res != SUCCESS)
		{
			delete [] trName[i];
			res = SUCCESS;
			continue;
		}
		op.resetEvent (true);
		char xbuf[20];
		strcpy(xbuf,"TransactionData");
		strcat(xbuf,asciCode[k] + 16);
		res = CNFG.getValue (CNFG_TRANSACTION, xbuf);
		if (res != SUCCESS)
		{
			delete [] trName[i];
			res = SUCCESS;
			continue;
		}
		if ((op.getValueType() == CNFG_BINARY) &&
			(op.getLength() == 2))
		{
			byte *val;
			char ybuf[3];
			char *ybufp = ybuf;
			op.getByteString( &val );
			res = AsciiStr2HexByte((const char*)val, 2,   
			    	     	     &hex_val, &hex_len);
			hexCode[i] |= (0x000000ff & hex_val);
			i++;
		}
		else
		{
			delete [] trName[i];
		}
	}
	if (res != SUCCESS)
	{
		for (int j = 0; j < k; j++)
		{	
			if (trName[j])
				delete [] trName[j];
		}
		delete [] hexCode;
		delete [] trName;
	}
	else
	{
		*codes = hexCode;
		*transNames = trName;
		*size = i;
	}
	CNFG.removeEvent ();
	return res;
}

int Prompter::GetUIFlag(byte **data, int *len)
{
	int res;
	CnfgControlImpl cnfg;
	CnfgOperationEventImpl op;

	// Initialize return parameters
	*data = 0;
	*len = -1;

	// Open CnfgControl service
	if ((res = pAM->open (&cnfg)) != SUCCESS)
		return res;

	// Add Operation Event
	if ((res = cnfg.addOperationEvent (&op)) != SUCCESS)
		return res;

	// Read Value from Registry
	if ((res = cnfg.getValue (CNFG_TERMINAL, "Data", "50000002")) != SUCCESS)
		return res;

	cnfg.removeEvent ();

	// Check type of returned data
	if (op.getValueType () != OPEVENT_BINARY)
		return ERR_UNEXPECTED_TYPE;

	// Check length of returned data
	int data_len = op.getLength();
	if (data_len <= 0)
		return ERR_INVALID_TERMINAL_DATA;

	byte *retrievedData = 0;
	// Retreive data from Operation event
	if ((res = op.getByteString (&retrievedData)) != SUCCESS)
		return res;

	byte *dt = new byte [data_len];
	if (!dt)
		return ERR_MEMORY_ALLOC;

	memcpy (dt, retrievedData, data_len);

	*data = dt;
	*len = data_len;
	return SUCCESS;
}
