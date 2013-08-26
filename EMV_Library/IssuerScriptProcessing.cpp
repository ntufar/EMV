#include "IssuerScriptProcessing.h"

IssuerScriptProcessing::IssuerScriptProcessing(void)
{
}

IssuerScriptProcessing::~IssuerScriptProcessing(void)
{
	resetList();
}

void IssuerScriptProcessing::resetList()
{
	while (!IssuerScriptResultList.empty())
	{
		byte *btElement = IssuerScriptResultList.front();
		if (btElement)
			delete [] btElement;
		IssuerScriptResultList.pop_front();
	}
}

int IssuerScriptProcessing::processScript (SCS_SCRIPT_TYPE scriptType)
{
	int res;
	DataObject dob_script;
	byte *IssScrRes = 0;
	
	resetList();

	byte fail_bit;
	int tag;
	int script_tag = 0;
	if (scriptType == SCS_BEFORE_GENERATE_AC)
	{
		script_tag |= 0x71;
		fail_bit = 0x20;
	}
	else
	{
		script_tag |= 0x72;
		fail_bit = 0x10;
	}
	int counter = 0;
	bool errorFlag = false;

	// Get the script from the Context
	while (true)
	{
		tag = script_tag | (counter << 24);
		res = EnvContext.getTagValue(tag, &dob_script, true);
		if (res != SUCCESS)
		{
			// Script was not found.
			// If the first time through the loop -- return SUCCESS,
			// Otherwise break the loop and set TSI status info
			if (counter == 0)
			{
				// Reset TVR to indicate that no erros are found
				updateDataObject (0x95, 5, fail_bit, false);
				return SUCCESS;
			}
			else
			{
				res = SUCCESS;
				break;
			}
		}
				
		byte *isr = new byte [5];
		if (!isr)
		{
			res = ERR_MEMORY_ALLOC;
			break;
		}
		memset (isr, 0, 5);

		tlv_creator tlvObj;
		res = tlvObj.SetTlv ((0x000000ff & tag), dob_script.len, dob_script.Data);
		if (res != SUCCESS)
		{
			// Failed to parse the data under the Script tag. This means that
			// the ISSUER has sent an invalid data. 
			//set Issuer script result to 'Issuer Script is not performed'
			isr[0] = 0x00;
			IssuerScriptResultList.push_back (isr);
			//Return an Error
			res = ERR_INVALID_ISSUER_DATA;
			counter++;
			continue;
		}

		OutputMsg ("EMV - executing issuer script");
		res = parseScript (tlvObj.GetDataObject (), tlvObj.GetDataObjectLen (),
			isr);
		IssuerScriptResultList.push_back (isr);
		if (res != SUCCESS)
		{
			errorFlag = true;
			if (res == ERR_INVALID_SCRIPT_LENGTH)
			{
				OutputMsg ("   NOK");
				break;
			}
		}		
		counter++;
	}

	// Set TSI bit 'Script Processing was performed' to '1'
	updateDataObject (0x9b, 1, 0x04, true);

	size_t result_size = IssuerScriptResultList.size();
	if (result_size > 0)
	{
		// Create Issuer Script Result value
		IssScrRes = new byte [result_size * 5];
		if (!IssScrRes)
		{
			res = ERR_MEMORY_ALLOC;
		}

		int indx = 0;
		while (!IssuerScriptResultList.empty ())
		{
			byte *isr = IssuerScriptResultList.front();
			if (IssScrRes)
				memcpy (IssScrRes + indx, isr, 5);
			delete [] isr;
			IssuerScriptResultList.pop_front ();
			indx += 5;
		}
	}

	if (result_size > 0)
	{
		// Store Issuer Script Results data element in the context
		setDataObject(0x9F5B, IssScrRes, (int)result_size * 5,
		              "b", CNFG_TRANSACTION);
	}

	if (IssScrRes)
		delete [] IssScrRes;
	if (res != SUCCESS || errorFlag)
	{
		// Set the TVR bit 'Script processing failed...' to '1' 
		updateDataObject (0x95, 5, fail_bit, true);
	}
	return res;
}

int IssuerScriptProcessing::parseScript(byte *data, 
										UNINT data_len, byte *isr)
{
	tlv_parser parser;
	int res;

	// Parse the script and all embedded TLV-coded data objects
	res = parser.parse (data, data_len);
	if (res != SUCCESS)
	{
		// Failed to parse the script data object,
		// Set Issuer Script Result to 'not performed'
		isr[0] = 0x00;
		return ERR_INVALID_ISSUER_DATA;
	}

	// Find a script tag
	tlv_parser *scriptTag = parser.Find (0x9f18, true);
	if (scriptTag)
	{
		// Script tag is found.
		// Set the Script ID to the Issuer Script Result
		int indx = 4;
		for (int i = scriptTag->GetRoot ()->GetLengthVal () - 1; 
			i >= 0; i--)
		{
			isr[indx] = scriptTag->GetRoot ()->GetValue ()[i];
			indx--;
			if (indx == 0)
				break;
		}
	}

	// Check the cumulative total length of all issuer scripts
	// See EMV book 4, ch 8.2.4
	// Get Max Issuer script size allowed by a terminal.
	// If cannot get the max issuer script length, then do not check
	// the script length (whatever comes will be parsed and processed)
	DataObject dob_maxSize;
	int iss_script_size = 0; // = MAX_ISSUER_SCRIPT_SIZE;
	res = EnvContext.getTagValue(CNFG_TERMINAL, 0x50000006, &dob_maxSize);
	if (res == SUCCESS)
	{
		if (dob_maxSize.len > 0 && dob_maxSize.len <= 4)
		{
			iss_script_size = LongFromByte(dob_maxSize.Data, 
				dob_maxSize.len);
		}
		
		if (iss_script_size > 0 && EMV_Context::IssuerScriptSize > iss_script_size)
		{
			// Set Issuer Script Result to 'not performed'
			isr[0] = 0x00;
			return ERR_INVALID_SCRIPT_LENGTH;
		}
	}

	// Find the first command
	tlv_parser *tlvCommand = parser.FindFirst (0x86);
	if (!tlvCommand)
	{
		// The current script doesn't have any commands
		// Set Issuer Script Result to 'not performed'
		isr[0] = 0x00;
		return ERR_INVALID_ISSUER_DATA;
	}

	byte command_cntr = 1;
	while (tlvCommand)
	{
		// Parse and execute command
		res = execCommand (tlvCommand->GetRoot ()->GetValue (), 
						   tlvCommand->GetRoot ()->GetLengthVal ());
		if (res != SUCCESS)
		{
			// The command execution by ICC failed.
			// Set Issuer Script Results
			if (res == ERR_FAILED_SCRIPT_PROCESSING)
				isr[0] = 0x10; // Issuer Script Processing Failed
			else
				isr[0] = 0x00; // Issuer Script not performed

			if (command_cntr <= 14)
				isr[0] |= command_cntr;
			else
				isr[0] |= 0x0f;
			return res;
		}
		
		// Current command succeeded!

		// Go to the next command 
		tlvCommand = parser.GetNext ();
		command_cntr++;
	}
	// Set Issuer Script Results to SUCCESS
	isr[0] = 0x20;
	return SUCCESS;
}


int IssuerScriptProcessing::execCommand (const byte *data, UNINT data_len)
{
	int res;
	scr_command command;

	// Parse command
	command.setReader ((SCRControlImpl*)EnvContext.GetService (CNTXT_SCR));
	res = command.setScript(data, data_len);
	if (res != SUCCESS)
		return res;

	R_APDU rapdu;
	// Execute command
	res = command.run (&rapdu, EMV_Context::TransactionToken);
	if (res == SUCCESS)
	{
		if (rapdu.getSW1() == 0x90 || 
			rapdu.getSW1() == 0x62 ||
			rapdu.getSW1() == 0x63)
		{
			return SUCCESS; // Script command completed successfully
		}
		else
		{
			return ERR_FAILED_SCRIPT_PROCESSING;
		}
	}
	else if (res == SCR_INVALID_INSTRUCTION_CODE)
		res = ERR_FAILED_SCRIPT_PROCESSING;
	return res;
}
