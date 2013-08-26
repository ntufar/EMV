#include "dol_parser.h"


dol_parser::dol_parser(Context *pCntxt):
	pContext(pCntxt)
{
	AmountChanged = false;
}

dol_parser::~dol_parser(void)
{
	pContext = 0;
}

// Creates a concatinated list of TLV-coded data elements found in a Context or in
// the Registry from the list of tags (dol_list) passed as a first parameter.
// Parameters:
//	 dol_list - a concatinated list of tags for those elements the values of which
//		is to retun to the caller
//   dol_size - a size in bytes of the dol_list buffer
//   data - a concatinated list of TLV-coded data elements. Each element in this
//		list corresponds to the tag found in dol_list list. The value of the element
//		is found in the Context or in the Registry. If a value is not found for some
//		tag in dol_list, then this data element will not be included in a list
//	data_len - a size in bytes of the buffer to hold data list. Can be 0 if no values
//		are found.
// Returns:
//	SUCCESS - if operation completed successfully
//	error code - if some error occured.
int dol_parser::createTLVList(const byte *dol_list, UNINT dol_size, 
							  byte **data, UNINT *data_len)
{
	using namespace std;
	list <tlv_creator*> tlv_list;
	int res;
	
	if (!dol_list || dol_size == 0)
	{
		*data = 0;
		*data_len = 0;
		return SUCCESS;
	}

	// parse tags, find a value inside of the context, create a TLV value,
	// put it into the list
	UNINT curIndx = 0;
	int tag;
	int tag_len;
	DataObject dob;
	tlv_creator *tlvObj;
	UNINT total_len = 0;

	while (curIndx < dol_size)
	{
		// 1. Parse tag
		res = tlv::parseTag (dol_list + curIndx, &tag, &tag_len);
		if (res != SUCCESS)
		{
			// release the content of the list
			ReleaseList(tlv_list);
			return res;
		}
		// Go to the next tag in the list
		curIndx += tag_len;
		
		// 2. Find the value inside of the Context
		res = pContext->getTagValue (tag, &dob, false);
		if (res == SUCCESS)
		{
			// Tag is found!
			// Create a TLV object
			tlvObj = new tlv_creator();
			if (!tlvObj)
			{
				// Release memory
				ReleaseList(tlv_list);
				return ERR_MEMORY_ALLOC;
			}
			// set tlv object to the value found in the Context
			res = tlvObj->SetTlv (tag, dob.len, dob.Data);
			if (res == SUCCESS)
			{
				// TLV is successfully created!
				// put a TLV object into the the list
				tlv_list.push_back (tlvObj);
				total_len += tlvObj->GetDataObjectLen();
			}
			else
				delete tlvObj;
		}
	} // End OF WHILE loop


	if (tlv_list.empty () || total_len == 0)
	{
		// Handle a special case when no values have been found
		*data = 0;
		*data_len = 0;
		return SUCCESS;
	}

	// Allocate memory for a buffer to hold the entire list of TLV objects
	byte *buff = new byte [total_len];
	if (!buff)
	{
		//release list
		ReleaseList(tlv_list);
		return ERR_MEMORY_ALLOC;
	}

	// Walk through the list and copy each TLV object to the byte array
	curIndx = 0;
	while (!tlv_list.empty())
	{
		tlvObj = tlv_list.front();
		memcpy(buff + curIndx, tlvObj->GetDataObject(), 
			tlvObj->GetDataObjectLen ());
		curIndx += tlvObj->GetDataObjectLen ();
		delete tlvObj; // release a memory for a current TLV object
		tlv_list.pop_front(); // remove front element from the list
	}

	// Release the context of the list (although it must be empty at this point)
	ReleaseList(tlv_list);

	// Assign return values
	*data = buff;
	*data_len = curIndx;
	return SUCCESS;
}

void dol_parser::ReleaseList(list <tlv_creator*> &tlv_list)
{
	using namespace std;
	while (!tlv_list.empty())
	{
		delete tlv_list.front();
		tlv_list.pop_front();
	}
}

// Parses Data Object List (dol_list) and creates a concatinated list of values
// Source: EMV 4.0, book 3, ch 1.4
// Parameters:
//  dol_type - type of Data Object list (PDOL = 0x9F38, CDOL1 = 0x8C, or 
//			   CDOL2 = 0x8D, TDOL = 0x97)
//	dol_list - an array representing concatinated list of tags and lengths
//  dol_size - a number of bytes in dol_list
//  data - a concatinated list of values build and allocated by this function
//  data_len - length of concatinated list in bytes (number of elements in the data array)
// Returns:
//  SUCCESS - if the list is parsed successfully
//  Error code (negative number) - if there is an error
// Note:
//	data must be deallocated by a caller
int dol_parser::createDOL(const int dol_type, const byte *dol_list, 
						  UNINT dol_size, 
						  byte **data, UNINT *data_len)
{
	DOL_ELEMENT dol;
	int res;

	res = parse_dol_tags(dol_list, dol_size, &dol);
	if (res != SUCCESS)
		return res;

	res = fill_dol (dol_type, &dol, data, data_len);
	if (dol.num_elements > 0)
	{
		delete [] dol.pTags;
		delete [] dol.pLength;
	}
	return res;
}

// Parses Data Object List which is concatinated list of tags and lengths into
// DOL_ELEMENT structure which has two arrays - one for tags and one for lengths.
// Parameters:
//   header - an array representing concatinated list of tags and lengths
//   len - a number of bytes in the header
//   dol - a structure containing two arrays which have the parsed data - 
//		tags and lengths.
// Returns:
//  SUCCESS - if the list is parsed successfully
//  Error code (negative numver) - if there is an error
int dol_parser::parse_dol_tags (const byte *header, int len, DOL_ELEMENT *dol)
{
	int res;
	int curIndx = 0;
	int tag, tag_len;
	int elements = 0;

	if (!header || len <= 0)
	{
		// Input list of tags and length is empty
		dol->num_elements = 0;
		dol->pTags = 0;
		dol->pLength = 0;
		return SUCCESS;
	}

	// Loop first time to calculate the number of elements in PDOL
	while (curIndx < len)
	{
		res = tlv::parseTag (header + curIndx, &tag, &tag_len);
		if (res != SUCCESS)
			return res;
		curIndx += (tag_len + 1); // add one to account for one-byte-length field
		elements++;
	}
	if (curIndx != len)
	{
		// DOL object is not parsed correctly
		return ERR_INVALID_ICC_DATA;
	}

	dol->num_elements = elements;
	// Allocate memory
	if (elements > 0)
	{
		dol->pTags = new int [elements];
		dol->pLength = new byte [elements];
	

		curIndx = 0;
		elements = 0;
		// Loop the second time and get the values of the tags and lengths
		while (curIndx < len)
		{
			tlv::parseTag (header + curIndx, &tag, &tag_len);
			dol->pTags [elements] = tag;
			dol->pLength [elements] = header [curIndx + tag_len];
			curIndx += (tag_len + 1); // add one to account for one-byte-length field
			elements++;
		}
	}
	return SUCCESS;
}


// Traverces array of tags in dol and for each tag finds a value and puts it into
// a concatinated list of values (data_list).
// Source: EMV 4.0. book3, ch 1.4.
// Parameters:
//      dol_type - type of Data Object list (PDOL = 0x9F38, CDOL1 = 0x8C, or 
//			   CDOL2 = 0x8D, TDOL = 0x97)
//		dol - a structure containing two arrays which have the parsed data - 
//		tags and lengths.
//      data_list - a buffer which will contain the concatinated list of values. This
//			buffer is allocated inside of this function and must be freed by a caller.
//		dl_len - lengths of the data_list buffer.
// Returns:
//  SUCCESS - if the list is parsed successfully
//  Error code (negative numver) - if there is an error
int dol_parser::fill_dol (const int dol_type, DOL_ELEMENT *dol, 
								byte **data_list, UNINT *dl_len)
{
	int res;
	int tvr_indx = -1;
	int tvr_length = -1;
	int amount_indx = -1;
	int amount_length = -1;
	AmountChanged = false;


	if (dol->num_elements <= 0)
	{
		// Handle a special case when PDOL is empty
		*data_list = 0;
		*dl_len = 0;
		return SUCCESS;
	}

	// Calculate the size of the buffer to keep all the elements of PDOL
	int count = 0;
	for (int i = 0; i < dol->num_elements; i++)
		count += dol->pLength[i];

	// Allocate space for the buffer to hold a template for a concatenated list 
	// of data values
	*data_list = new byte [count]; 
	if (!(*data_list))
		return ERR_MEMORY_ALLOC;

	// Store the size of the buffer
	*dl_len = count;

	
	int cur_indx = 0; // current index in dol
	DataObject dob;

	// Delete Data Values from the Context for which values needs to be recalculated
	// dynamically
	RemoveDynamicData();

	cout << "Initializing DOL..." << endl;
	// Create a concatenated list of all data values requested by the card
	for (int i = 0; i < dol->num_elements; i++)
	{
		bool conctrFlag = false;
		if (check_bit(dol->pTags[i], 0x1f00))
		{
			if (check_bit (dol->pTags[i], 0x2000))
				conctrFlag = true;
		}
		else
		{
			if (check_bit (dol->pTags[i], 0x20))
				conctrFlag = true;
		}
			
		if (conctrFlag)
		{
			// The Tag is for constructed data object.
			// According to rule (a) of chaper 1.4, book 3, fill a value of this 
			// element with all 0's
			memset((*data_list) + cur_indx, 0, dol->pLength[i]);
		}
		else
		{
			cout << "DOL: Tag = " << hex << dol->pTags[i] << endl;
			if (dol->pTags[i] == 0x95)
			{
				// Save the index of TVR in case if it needs to be updated later
				tvr_indx = cur_indx;
				tvr_length = dol->pLength [i];
			}
			if (dol->pTags [i] == 0x9f02)
			{
				// Save the index of the Amount Authorized in case if it needs 
				// to be updated later
				amount_indx = cur_indx;
				amount_length = dol->pLength [i];
			}
			res = pContext->getTagValue(dol->pTags[i], &dob);
			if (res != SUCCESS)
			{
				// Value not found for this tag;
				// Check if additional actions should be taken to find a data
				res = DoAdditionalProc(dol_type, dol->pTags[i], dol->pLength [i], &dob);
				if (res != SUCCESS)
				{
					if (res == ERR_TERMINAL_WINDOW_IS_UNAVAILABLE ||
						res == OPERATION_CANCELED_BY_USER)
					{
						delete [] *data_list;
						*data_list = 0;
						return res;
					}
				}
			}

			// Format (if necessary) and write data to the array
			if (dol->pLength[i] == dob.len)
			{
				// Length is the same; just copy value
				memcpy ((*data_list) + cur_indx, dob.Data, dob.len);
			}
			else if (dol->pLength[i] > dob.len)
			{
				// padd value to match requested length
				if (strcmp(dob.Format, "n") == 0)
				{
					// Numeric format; padd with leading 0's
					memset (*data_list + cur_indx, 0, dol->pLength[i] - dob.len);
					memcpy (*data_list + cur_indx + (dol->pLength[i] - dob.len),
						dob.Data, dob.len);
				}
				else if (strcmp(dob.Format, "cn") == 0)
				{
					// Compressed numeric format; padd with trailing 0xFF's
					memcpy (*data_list + cur_indx, dob.Data, dob.len);
					memset (*data_list + cur_indx + dob.len, 0xFF,
							dol->pLength[i] - dob.len);
				}
				else
				{
					// any other format; padd with trailing 0's
					memcpy (*data_list + cur_indx, dob.Data, dob.len);
					memset (*data_list + cur_indx + dob.len, 0,
							dol->pLength[i] - dob.len);
				}		
			}
			else // (dol->pLength[i] < dob.len)
			{
				// truncate the value to match requested length
				if (strcmp(dob.Format, "n") == 0)
				{
					// Numeric format; truncate leftmost digits
					memcpy (*data_list + cur_indx, dob.Data + 
						(dob.len - dol->pLength[i]), dol->pLength[i]);
				}
				else
				{
					// Any other format; truncate the right most bytes
					memcpy (*data_list + cur_indx, dob.Data, dol->pLength[i]);
				}
			}
		}
		cur_indx += dol->pLength[i];
	}
	
	if (tvr_indx != -1)
	{
		// Update TVR in case it has been changed during TC calculation:
		// Get current TVR value
		// Set 'Default TDOL used' bit to '1' in the TVR
		if ((res = pContext->getTagValue(0x95, &dob, true)) == SUCCESS)
		{
			if (dob.len == 5)
			{
				if (tvr_length >= dob.len)
				{
					memcpy (*data_list + tvr_indx, dob.Data, dob.len);
					memset (*data_list + tvr_indx + dob.len, 0,
								tvr_length - dob.len);
				}
				else
					memcpy(*data_list + tvr_indx, dob.Data, tvr_length);
			}
		}
	}

	if (amount_indx != -1 && AmountChanged)
	{
		// Update Amount Authorized in case it has been changed:
		// Get current AmountAuthorized value
		if ((res = pContext->getTagValue(0x9f02, &dob, true)) == SUCCESS)
		{
			if (dob.len == 6)
			{
				if (amount_length >= dob.len)
				{
					memset (*data_list + amount_indx, 0, amount_length - dob.len);
					memcpy (*data_list + amount_indx + (amount_length - dob.len),
						dob.Data, dob.len);
				}
				else
				{
					memcpy(*data_list + amount_indx, dob.Data + 
						(dob.len - amount_length), dob.len);
				}
			}
		}
	}
	return SUCCESS;
}


void dol_parser::RemoveDynamicData()
{
	//pContext->removeTag(0x9f37); // Unpredictable Number
	pContext->removeTag(0x98);   // TC Hash
	// Add other values that needs to be recalculated
}

int dol_parser::DoAdditionalProc(const int dol_type, int tag, byte data_len, 
								  DataObject *dob)
{
	int res = -1;
	char format[4];
	
	if (tag == 0x9a)
	{
		res = getCurrentDate(dob);
		strcpy (format, "n");
	}
	else if (tag == 0x9f37)
	{
		res = getUnpredictableNumber(dob, data_len);
		strcpy (format, "b");
	}
	else if (tag == 0x98)
	{
		res = generateTCHash(dob);
		strcpy (format, "b");
	}
	else if (tag == 0x9f02) // Amount, Authorized
	{
		if (dol_type == 0x9F38) 
		{
			// Do only if PDOL is processed
			DataObject dob_cur;
			res = getAmount(true, dob, &dob_cur);
			if (res == SUCCESS)
				pContext->setTagValue (0x5f2a, &dob_cur, IO_CREATE | IO_UPDATE);
		}
		strcpy (format, "n");
	}
	else if (tag == 0x9f03) // Amount, Other
	{
		if (dol_type == 0x9F38) 
		{
			// Do only if PDOL is processed
			res = getAmount(false, dob, 0);
			if (res == SUCCESS)
			{
				//  Update Amount Authorized
				DataObject dob_AmAuth;
				res = pContext->getTagValue (0x9f02, &dob_AmAuth, true);
				if (res == SUCCESS)
				{
					// Add the Amount Other to the Amount Authorised
					if ((res = Add2numAmounts(dob_AmAuth.Data, dob->Data)) == SUCCESS)
					{
						// Update registry to keep transaction amount
						pContext->setTagValue (0x9f02, &dob_AmAuth, IO_UPDATE);
						AmountChanged = true;
					}
				}
			}
		}
		strcpy (format, "n");
	}
	else if (tag == 0x9c) // Transaction Type
	{
		if (dol_type == 0x9F38) 
		{
			// Do only if PDOL is processed
			res = getTransaction(dob);
		}
		strcpy (format, "n");
	}

	//Add Additional Tags for which some processing must be done here


	if (res == SUCCESS)
	{
		// Update Context
		pContext->setTagValue (tag, dob, IO_CREATE | IO_UPDATE);
	}
	else
	{
		// Set data object
		dob->set(NULL, data_len, CNFG_TRANSACTION, format);
	}
	return res;
}

// Get Current Date
int dol_parser::getCurrentDate(DataObject *dob_curDate)
{
	SystemControlImpl syst;// = 
		//(SystemControlInterface*)pContext->GetService (CNTXT_SYSTEM); 
	DateStruct curDate;
	int res = syst.retreiveDateEx(&curDate);
	if (res == SUCCESS)
	{
		byte byteDate [3];
		DateStruct2EMVDate(byteDate, curDate);
		dob_curDate->set (byteDate, 3, CNFG_TRANSACTION, "n");
	}
	return res;
}

// Get Unpredictable Number
int dol_parser::getUnpredictableNumber(DataObject *dob, byte data_len)
{
	CryptoControlImpl *crypt = 
		(CryptoControlImpl*)pContext->GetService (CNTXT_CRYPTO); 
	CryptoOperationEventImpl opEvent;
	int res;

	if ((res = crypt->addOperationEvent (&opEvent)) == SUCCESS)
	{
		if ((res = crypt->randomNumber (0x01/*crypt->getCryptoAlgID ()*/, data_len)) == SUCCESS)
		{
			byte *data;
			opEvent.getByteString(&data);
			res = dob->set (data, opEvent.getLength (), CNFG_TRANSACTION, "b");
		}
		crypt->removeEvent ();
	}
	return res;	
}

int dol_parser::generateTCHash(DataObject *dob)
{
	int res;
	bool HashOnly;

	// Get TDOL read from the card if present
	byte *pdol;
	int pdol_len;
	DataObject dob_tdol;
	HashOnly = true;
	res = pContext->getTagValue(0x97, &dob_tdol, HashOnly);
	if (res != SUCCESS)
	{
		// TDOL was not read from the ICC.
		// Get Default TDOL from the terminal must be present
		HashOnly = false;
		res = pContext->getTagValue(0x97, &dob_tdol, HashOnly);
		if (res != SUCCESS)
		{
			// Default TDOL is not present in the terminal,
			// default TDOL with no data objects in the list will be used
			// (see EMV 4.0, book 3, ch 5.2.2 (last sentence on the page)
			pdol = 0;
			pdol_len = 0;
			// Do not set 'Default TDOL used' bit to '1' in TVR (see
			// bulletin #11, www/emvco.com
		}
		else
		{
			// Default TDOL is found in the terminal
			pdol = dob_tdol.Data;
			pdol_len = dob_tdol.len;

			// Set 'Default TDOL used' bit to '1' in the TVR
			DataObject dob_tvr;
			if ((res = pContext->getTagValue(0x95, &dob_tvr, true)) == SUCCESS)
			{
				if (dob_tvr.len == 5)
				{
					set_bit (dob_tvr.Data [4], 0x80);
					pContext->setTagValue(0x95, &dob_tvr, IO_UPDATE);
				}
			}
		}
	}
	else
	{
		// TDOL is returned by ICC
		pdol = dob_tdol.Data;
		pdol_len = dob_tdol.len;
	}

	// Parse TDOL list into concatinated list of values to be used as input
	// to a hash algorithm.
	byte *value_list = 0;
	UNINT list_size;
	// First parameter indicates TDOL = 0x97:
	if ((res = createDOL(0x97, pdol, pdol_len, &value_list, &list_size)) != SUCCESS)
		return res;

	//----------
	// Testing, delete these lines after debug
	//DataObject dob_th;
	//dob_th.set (value_list, list_size, CNFG_TRANSACTION, "b");
	//pContext->setTagValue (0x90000002, &dob_th, IO_CREATE | IO_UPDATE);
	// ------------

	// Create a hash from the value_list data
	// Get reference to Crypto Service
	CryptoControlImpl *Crypto =
		(CryptoControlImpl*)pContext->GetService (CNTXT_CRYPTO);

	CryptoOperationEventImpl opEvent;

	if ((res = Crypto->addOperationEvent(&opEvent)) != SUCCESS)
	{
		delete [] value_list;
		return res;
	}
	
	res = Crypto->calcHash (value_list, list_size);
	Crypto->removeEvent();
	delete [] value_list;
	if (res != SUCCESS)
	{
		// Error while calculating the hash; terminate the transaction
		return res;
	}
	
	byte *new_hash;
	int new_len;
	opEvent.getByteString (&new_hash);
	new_len = opEvent.getLength ();
	
	res = dob->set (new_hash, new_len, CNFG_TRANSACTION, "b");
	return res;
}

int dol_parser::getAmount(bool AmountAuthorised, DataObject *dob, 
						  DataObject *dob_cur)
{
	int res;
	Prompter prompt (pContext->getAccessManager());
	byte Amount [6];
	byte CurCode [2];
	const byte zero_amount [6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	res = prompt.promptAmount(AmountAuthorised, Amount, CurCode, EMV_LANG_LATIN1);
	if (res == SUCCESS)
	{
		if (memcmp(Amount, zero_amount, 6) == 0)
			return EMV_MISSING_MANDATORY_DATA;

		// 4 most significant digits in CurCode keep the number of digits in
		// cents part of the Amount. These bits must be set to 0 prior saving 
		// the value in the context
		CurCode[0] &= 0x0f; 
		if (dob_cur)
			dob_cur -> set (CurCode, 2, CNFG_TRANSACTION, "n");

		// Set Amount
		res = dob->set (Amount, 6,CNFG_TRANSACTION, "n");
	}
	return res;
}

int dol_parser::getTransaction(DataObject *dob)
{
	int res;
	Prompter prompt (pContext->getAccessManager());
	byte TransType;
	byte TransInfo;
	
	const byte zero_amount [6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	res = prompt.promptTransactionType(&TransType, &TransInfo, EMV_LANG_LATIN1);
	if (res == SUCCESS)
		return dob->set(&TransType, 1, CNFG_TRANSACTION, "n");
	else 
		return res;
}
