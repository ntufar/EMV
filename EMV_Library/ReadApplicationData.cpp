#include "ReadApplicationData.h"

ReadApplicationData::ReadApplicationData(void)
{
}

ReadApplicationData::~ReadApplicationData(void)
{
}

int ReadApplicationData::ReadApplData (tlv_parser *tlv_AIP, 
									   byte **ppOdaList, int *oda_len)
{
	int res;
	byte *AIP;
	int aip_len;
	byte *AFL;
	int afl_len;

	res = parse_AIP_AFL(tlv_AIP, &AIP, &aip_len, &AFL, &afl_len);
	if (res != SUCCESS)
		return res;

	// Check the size of the retreived data:
	if (aip_len != 2 || afl_len == 0)
		return ERR_INVALID_ICC_DATA;

	// Store Application Interchange Profile into the hash
	DataObject dob;
	dob.set(AIP, aip_len, CNFG_APPLICATION, "b");
	EnvContext.setTagValue (0x82, &dob, IO_CREATE);
	
	// Read Data from ICC
	if ((res = ReadDataFromICC (AFL, afl_len, ppOdaList, oda_len)) != SUCCESS)
		return res;

	// Get Mandatory Data
	int *mandData;
	int count;
	if ((res = getMandatoryData(&mandData, &count)) != SUCCESS)
		return res;

	// Check if all mandatory data objects are present
	if (checkMandatoryData (mandData, count))
		res = SUCCESS;
	else
		res = EMV_MISSING_MANDATORY_DATA;

	delete [] mandData;
	return res;
}

int ReadApplicationData::parse_AIP_AFL(tlv_parser *tlv_AIP, byte **AIP, 
									   int *aip_len, 
									   byte **AFL, int *afl_len)
{
	tlv_parser *tlv_format;
	tlv_format = tlv_AIP->Find (0x80, true);
	if (tlv_format)
	{
		// Format 1: see book 3, chapter 2.5.8.4 EMV specs
		*AIP = tlv_format->GetRoot ()->GetValue ();
		*aip_len = 2;
		*afl_len = tlv_format->GetRoot ()->GetLengthVal () - *aip_len;
		if (*afl_len <= 0)
		{
			*AFL = 0;
			*afl_len = 0;
		}
		else
			*AFL = tlv_format->GetRoot ()->GetValue () + *aip_len;
		return SUCCESS;
	}
	else
	{
		tlv_format = tlv_AIP->Find (0x77, true);
		if (tlv_format)
		{
			// Format 2: see book 3, chapter 2.5.8.4 EMV specs
			// Find Application Interchanfe Profile
			tlv_parser *tlv_aip = tlv_format->Find (0x82);
			if (!tlv_aip)
				return EMV_AIP_NOT_FOUND;
			*AIP = tlv_aip->GetRoot ()->GetValue ();
			*aip_len = tlv_aip->GetRoot ()->GetLengthVal();

			tlv_parser *tlv_afl = tlv_format->Find (0x94);
			if (!tlv_afl)
				return EMV_AFL_NOT_FOUND;

			*AFL = tlv_afl->GetRoot ()->GetValue ();
			*afl_len = tlv_afl->GetRoot()->GetLengthVal ();
			return SUCCESS;
		}
		else
			return EMV_INVALID_FORMAT;
	}
}


int ReadApplicationData::ReadDataFromICC (const byte *AFL, int afl_len, 
							 byte **ppOdaList, int *oda_len)
{
	if ((afl_len % 4) != 0)
		return EMV_AFL_INVALID_FORMAT;
	//UIControlInterface *pUI = (UIControlInterface*)EnvContext.GetService (CNTXT_UI);
	//pUI->writeStatus ("Inside ReadDataFromICC");
	
	int res;
	int i;
	BYTE_LIST odaList;
		
	Afl_Element *pElement = 0;

	// Before issuing the first READ RECORD command, check if all 
	// data elements in the AFL list are valid. This condition is
	// checked by KaNest-ICC tool.
	i = 0;
	for (; i < afl_len; i+=4)
	{
		pElement = (Afl_Element*)(AFL + i);				      
		if ((res = checkAflEntry(pElement)) != SUCCESS)
		{
			return res;
		}
	}
	// Read Records
	i = 0;
	for (; i < afl_len; i+=4)
	{
		pElement = (Afl_Element*)(AFL + i);	
		if ((res = ReadRecords (pElement, odaList)) 
			!= SUCCESS)
		{
			return res;
		}
	}
	
	return createOdaList(odaList, ppOdaList, oda_len);
}

int ReadApplicationData::checkAflEntry (Afl_Element *pElement)
{
	byte sfi = pElement->sfi >> 3;
	
	// Check validity of data in AFL (see section 3.4, EMB book 3)
	if (sfi == 0 || sfi == 31)
	{
		// Invalid value for SFI.
		return ERR_INVALID_ICC_DATA;
	}

	if (pElement->first_byte == 0 || pElement->first_byte > pElement->last_byte)
	{
		// The first record number is 0 or the last record number is less than the
		// first one. 
		return ERR_INVALID_ICC_DATA;
	}

	if (pElement->oda_counter > pElement->last_byte - pElement->first_byte + 1)
	{
		// Number of records participating in offline data auth. greater than
		// the number of record. 
		return ERR_INVALID_ICC_DATA;
	}
	return SUCCESS;
}

int ReadApplicationData::ReadRecords (Afl_Element *pElement, BYTE_LIST &odaList)
{
	int res;
	byte sfi = pElement->sfi >> 3;
	bool odaListError = false;
/*
	// Check validity of data in AFL (see section 3.4, EMB book 3)
	if (sfi == 0 || sfi == 31)
	{
		// Invalid value for SFI.
		return ERR_INVALID_ICC_DATA;
	}

	if (pElement->first_byte == 0 || pElement->first_byte > pElement->last_byte)
	{
		// The first record number is 0 or the last record number is less than the
		// first one. 
		return ERR_INVALID_ICC_DATA;
	}

	if (pElement->oda_counter > pElement->last_byte - pElement->first_byte + 1)
	{
		// Number of records participating in offline data auth. greater than
		// the number of record. 
		return ERR_INVALID_ICC_DATA;
	}
*/
	int counter = pElement->oda_counter;
	scr_command command ((SCRControlImpl*)EnvContext.GetService(CNTXT_SCR));
	R_APDU rapdu;
	tlv_parser tlv_record;

	cout << "Starting reading records for a SFI " << (int)sfi << ":" << endl;

	for (int i = pElement->first_byte; i <= pElement->last_byte; i++)
	{
		command.setReadRecord ((byte)i, sfi);
		if ((res = command.run (&rapdu, TransactionToken)) != SUCCESS)
		{
			// Command execution returned an error
			cout << "ReadRecord Failed (" << hex << res << ")" << endl;			
			return res;
		}
		if (rapdu.getSW1 () != 0x90 || rapdu.getSW2() != 0x00)
		{
			// The ICC returned an error
			cout << "ReadRecord Failed (0x" << hex << rapdu.getSW1 ();
			cout << rapdu.getSW2 ()<< ")" << endl;
						
			return EMV_READ_RECORD_FAILED;
		}
		
		byte *data = rapdu.copyData ();
		if (!data)
			return ERR_MEMORY_ALLOC;

		if ((res = tlv_record.parse (data, rapdu.getDataLen ()))
			!= SUCCESS)
		{
			// cannot parse data returned by the ICC
			delete [] data;
			return EMV_INVALID_FORMAT;
		}
		if ((sfi >= 1 && sfi <= 10) && 
			(tlv_record.GetRoot ()->GetTagVal () != 0x70 ||
			tlv_record.GetTlvDataObjectLen() != rapdu.getDataLen ()))
		{
			// Either record template is not 0x70 or record has some values
			// defined outside of the template.
			delete [] data;
			return EMV_INVALID_FORMAT;
		}
		cout << "Parsing succeeded" << endl;
		
		if (counter > 0 && !odaListError)
		{
			// Add data to a list of SDA data
			if (sfi >= 1 && sfi <= 10)
			{
				// Exclude the record tag ('70') and the record length from the
				// offline data authentication list (see book 3, ch 6.3, page 47)
				add2OdaList (tlv_record.GetRoot ()->GetValue (),
					tlv_record.GetRoot ()->GetLengthVal (), odaList);
			}
			else
			{
				if (tlv_record.GetRoot ()->GetTagVal () != 0x70)
				{
					// See EMV Bulletin #12 second bullet (www.emvco.com):
					// If the records read for offline data authentication are 
					// not TLV-coded with Tag equal to '70' then offline data 
					// authentication shall be considered to have been 
					// performed and to have failed.
					odaListError = true;
				}
				else
				{
					// Include the entire record into Offline Data authentication process
					add2OdaList (tlv_record.GetRoot ()->GetDataObject (),
						tlv_record.GetRoot ()->GetDataObjectLen (), odaList);
				}
			}
			counter--;
		}

		res = add2Context (&tlv_record);
		delete [] data;
		if (res != SUCCESS)
			return res;		
	}
	if (odaListError)
	{
		// Remove all data from odaList
		odaList.clear ();
	}
	cout << "Done with a current element." << endl;
	return SUCCESS;

}

int ReadApplicationData::add2OdaList (const byte *arr, int len, BYTE_LIST &odaList)
{
	for (int i = 0; i < len; i++)
		odaList.push_back(arr[i]);
	return SUCCESS;
}

int ReadApplicationData::add2Context (tlv_parser *tlv_record)
{
	int res;
	DataObject dob;
	dob.Category = CNFG_APPLICATION;
	dob.setFormat ("");
	tlv_parser *tlv_element = tlv_record->GetFirstChild();
	
	while (tlv_element)
	{
		if (tlv_element->GetRoot ()->IsPrimitive ())
		{
			// Primitive Data type -- store it in a Context
			dob.updateData (tlv_element->GetRoot ()->GetValue (),
							tlv_element->GetRoot ()->GetLengthVal ());
			if ((res = EnvContext.setTagValue(tlv_element->GetRoot ()->GetTagVal (), 
					&dob, 
					IO_CREATE)) == DUPLICATE_INSERT)
			{
					cout << "VALUE " << hex << tlv_element->GetRoot ()->GetTagVal ();
					cout << " already exists in a hash" << endl;
					// Redundant primitive data objects are not permitted!
					// Transaction is terminated
					// see book 3, ch 6.2, page45
					return EMV_REDUNDANT_PRIMITIVE_DATA;
			}
			else if (res != SUCCESS)
			{
				cout << "FAILED to insert a value " << hex;
				cout << tlv_element->GetRoot ()->GetTagVal () << " into the hash" << endl;
				return res;
			}
			else
			{
				// SUCCESS
				cout << "SUCCEEDED in inserting a value " << hex;
				cout << tlv_element->GetRoot ()->GetTagVal () << " into the hash" << endl;
			}
		}
		else
		{ 
			// Constructed Data object -- parse it
			if ((res = add2Context (tlv_element)) != SUCCESS)
				return res;
		}
		tlv_element = tlv_record->GetNext ();
	}
	return SUCCESS;
}

int ReadApplicationData::createOdaList(BYTE_LIST &odaList, byte **ppOdaList, int *oda_len)
{
	if (odaList.size () > 0)
	{
		*ppOdaList = new byte [odaList.size ()];
		if (!(*ppOdaList))
			return ERR_MEMORY_ALLOC;

		BYTE_LIST::iterator it;
		it = odaList.begin ();
		for (unsigned int j = 0; j < odaList.size (); j++)
		{
			(*ppOdaList)[j] = *it;
			it++;
		}
		*oda_len = (int)odaList.size ();
	}
	else
	{
		*oda_len = 0;
		*ppOdaList = 0;
	}
	return SUCCESS;
}

int ReadApplicationData::getMandatoryData( int **mandData, int *count)
{
	int res;
	DataObject dob;

	res = EnvContext.getTagValue(0x40000002, &dob);
	if (res != SUCCESS)
		return res;

	if ( dob.len <= 0)
	{
		*count = 0;
		return SUCCESS;
	}

    // Loop the first time and calculate the number of tags in a byte array
	int cur_indx = 0;
	int tag_val;
	int tag_len;
	int i = 0;
	while (cur_indx < dob.len)
	{
		res = tlv::parseTag (dob.Data + cur_indx, &tag_val, &tag_len);
		cur_indx += tag_len;
		i++;
	}

	// Allocate space to hold the tags
	int *arr = new int[i];
	if (!arr)
	{
		return ERR_MEMORY_ALLOC;
	}

	// Loop 2nd time in order to get all the tags
	cur_indx = 0;
	i = 0;
	while (cur_indx < dob.len)
	{
		res = tlv::parseTag (dob.Data + cur_indx, &tag_val, &tag_len);
		cur_indx += tag_len;
		arr[i++] = tag_val;
	}
	*mandData = arr;
	*count = i;
	return SUCCESS;
}

bool ReadApplicationData::checkMandatoryData (const int *mandData, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!EnvContext.tagExist(mandData[i], true))
			return false;
	}
	return true;
}

