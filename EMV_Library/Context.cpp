#include "Context.h"

Context::Context(void)
{
	pAM = 0;
}

Context::~Context(void)
{
	unInitializeContext();
}

int Context::initializeContext (AccessManager *pAM)
{
	int res;
	this->pAM = pAM;
	if (!UI.opened ())
	{
		if ((res = pAM->open (&UI)) != SUCCESS)
			return res;
	}
	if (!SCR.opened ())
	{
		if ((res = pAM->open (&SCR)) != SUCCESS)
			return res;
	}
	if (!Crypto.opened ())
	{
		if ((res = pAM->open (&Crypto)) != SUCCESS)
			return res;
	}
	if (!SYST.opened ())
	{
		if ((res = pAM->open (&SYST)) != SUCCESS)
			return res;
	}
	return SUCCESS;
}

void Context::unInitializeContext (bool StopServices)
{
	if (StopServices)
	{
		if (pAM)
		{
			if (UI.opened ())
				pAM->close (UI);
			if (SCR.opened())
				pAM->close (SCR);
			if (Crypto.opened ())
				pAM->close (Crypto);
			if (SYST.opened())
				pAM->close (SYST);
		}
		pAM = 0;
	}
	
	ITERATOR_DATA it;
	it = hash.begin();
	while (it != hash.end())
	{
		delete it->second;
		hash.erase(it);
		it = hash.begin();
	}
}


ServiceControl* Context::GetService(int ServiceType)
{
	switch (ServiceType)
	{
	case CNTXT_UI:
		return &UI;
	case CNTXT_SCR:
		return &SCR;
	case CNTXT_CNFG:
		return (ServiceControl*)&CNFG;
	case CNTXT_CRYPTO:
		return &Crypto;
	case CNTXT_SYSTEM:
		return &SYST;
	default:
		return 0;
	}
}

AccessManager* Context::getAccessManager()
{
	return pAM;
}
// This function checks first CNFG_APPLICATION directory for a value, and 
// then the CNFG_TERMINAL directory
int Context::getTagValue(int Tag, DataObject *dob, bool hash_only)
{
	ITERATOR_DATA it_data;
	ITERATOR_RES  it_res;
	int res;
	PAIR pr;
	byte buf[100];

	it_data = hash.find(Tag);

	if (it_data != hash.end())
	{
		// Data is found in the hash
		return dob->set (it_data->second->Data, it_data->second->len,
				it_data->second->Category, it_data->second->Format);
	}
	else if (hash_only == false)
	{
		// Data is not found in a map
		// Read Data from a registry
		// value found in registry is 0:
	if(Tag == 0x50000004){
		/*
		[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\TerminalInfo\50000004]
		"Data"=hex:00
		"Byte1Bit1"="=1 Approved, =0 Declined"
		"Format"="b"
		"Byte1Bit6"="=1 Signature is required; =0 Signature is not required"
		@="Transaction Results"
		"Byte1Bit2"="=1 Advise Required; =0 Advise not required"
		"Byte1Bits3_5"="Reason/advice/referral code"
		*/
		buf[0] == 0;
		dob->set(buf, 1, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	if(Tag == 0x40000002){
		buf[0] = 0x5a;
		buf[1] = 0x5f;
		buf[2] = 0x24;
		buf[3] = 0x8c;
		buf[4] = 0x8d;
		dob->set(buf, 5, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}

	if(Tag == 0x40000004){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\POSApplications\A0000000041010\ApplicationInfo\40000004]
"Data"=hex:00,00,00,00,40,00
"Format"="n"
@="Threshold Value for Biased Random Selection"
*/
		buf[0] = 0x00;
		buf[1] = 0x00;
		buf[2] = 0x00;
		buf[3] = 0x00;
		buf[4] = 0x40;
		buf[5] = 0x00;
		dob->set(buf, 6, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}

	if(Tag == 0x40000005){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\POSApplications\A0000000041010\ApplicationInfo\40000005]
"Data"=hex:32
@="Target Percentage to be used for Random Selection (0 - 99 dec, or 0 -63 hex)"
"Format"="b"
*/
		buf[0] = 0x32;
		dob->set(buf, 1, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
	if(Tag == 0x40000006){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\POSApplications\A0000000041010\ApplicationInfo\40000006]
"Data"=hex:46
@="Maximum Target Percentage to be used for Biased Random Selection (0 - 99 decimal, or 0 - 63 hex)"
"Format"="b"
*/
		buf[0] = 0x46;
		dob->set(buf, 1, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
		
	if(Tag == 0x9f33){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\TerminalInfo\9F33]
"Byte3Bit8"="1 = Offline static data authentication"
"Format"="b"
"Byte2Bit6"="1 = Signature (paper)"
@="Terminal Capabilities"
"Byte2Bit8"="1 = Plaintext PIN for offline CC verification"
"Byte2Bit7"="1 = Enciphered PIN for online verification"
"Byte1Bit8"="1= Manual key entry"
"Byte1Bit7"="1 = Magnetic stripe"
"Byte2Bit4"="1 = No CVM required"
"Byte3Bit7"="1 = Offline dynamic data authentication"
"Data"=hex:20,b8,c0
"Byte3Bit6"="1 = Card capture"
"Byte2Bit5"="1 = Enciphered PIN for offline verification"
"Byte1Bit6"="1 = IC with contacts"
"Byte3Bit4"="1 = Combined dynamic data authentication / application cryptogram generation"
*/		
		buf[0] = 0x20;
		buf[1] = 0xb8;
		buf[2] = 0xc0;
		dob->set(buf, 3, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
	if(Tag == 0x9f1a){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\TerminalInfo\9F1A]
"Data"=hex:08,40
"FormatSize"=dword:00000003
"Format"="n"
@="Terminal Country Code"
*/		
		buf[0] = 0x08;
		buf[1] = 0x40;
		buf[2] = 0x00;
		dob->set(buf, 3, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
	if(Tag == 0x9f1b){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\POSApplications\A0000000031010\ApplicationInfo\9F1B]
"Format"="b"
"Data"=hex:00,00,27,10
@="Terminal Floor Limit"
*/		
		buf[0] = 0x00;
		buf[1] = 0x00;
		buf[2] = 0x27;
		buf[3] = 0x10;    // 0x2710 = 10000
		dob->set(buf, 4, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}

	
	
	
	
		
	if(Tag == 0x9f35){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\TerminalInfo\9F35]
"35"="unatt, offl &onl, ch"
"23"="att, offlo, merch"
"14"="unatt, onlo, fi"
"22"="att, offl &onl, merch"
"21"="att, onlo, merch"
"12"="att, offl & onl, fi"
"Data"=hex:22
"36"="unatt, oflo, ch"
"26"="unatt, offlo, merch"
"24"="unatt, onlo, merch"
"15"="unatt, offl &onl, fi"
@="Terminal Type"
"16"="unatt, offlo, fi"
"11"="att, onlo, fi"
"13"="att, offlo, fi"
"34"="unatt, onlo, ch"
"25"="unatt, offl & onl, merch"

*/		
		buf[0] = 0x22;
		dob->set(buf, 1, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}

	if(Tag == 0x9f40){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\TerminalInfo\9F40]
"Byte4Bit6"="display, attendant"
"Byte5Bit8toBit1"="code table 8 to code table 1"
@="Additional Terminal Capabilities"
"Byte1Bit7"="goods"
"Byte4Bit7"="print, cardholder"
"Byte1Bit6"="services"
"Byte1Bit3"="transfer"
"Byte1Bit5"="cashback"
"Byte4Bit5"="display, cardholder"
"Byte1Bit2"="payment"
"Byte1Bit4"="inquiry"
"Byte3Bit8"="numeric keys"
"Byte3Bit5"="function keys"
"Byte1Bit1"="administrative"
"Byte4Bit2"="code table 10"
"Byte3Bit6"="command keys"
"Byte4Bit1"="code table 9"
"Byte3Bit7"="alphabetic and special characters keys"
"Byte4Bit8"="print, attendant"
"Byte1Bit8"="cash"
"Format"="b"
"Data"=hex:72,00,c0,a0,01

*/		
		buf[0] = 0x72;
		buf[1] = 0x00;
		buf[2] = 0xc0;
		buf[2] = 0xa0;
		buf[2] = 0x01;
		dob->set(buf, 5, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
	if(Tag == 0x9f09){
/*
[HKEY_LOCAL_MACHINE\SOFTWARE\SCS\SmartPOS\POSApplications\A0000000031010\ApplicationInfo\9F09]
@="Application Version Number"
"Format"="b"
"Data"=hex:00,8c

*/		
		buf[0] = 0x00;
		buf[1] = 0x08;
		dob->set(buf, 2, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	
		
	if(Tag = 0x9f06){
		dob->set(GLOBAL_AID, GLOBAL_AID_LEN,1,"b");
		return add_to_hash (hash, Tag, dob);
	}
	
	if(Tag == 0x9a){
		buf[0] = 'n';
		buf[1] = 0;
		dob->set(buf, 3, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
		/*
		if ((res = read_from_registry(CNFG_APPLICATION, Tag, dob)) == SUCCESS)
		{
			// Add Data to hash
			dob->Category = CNFG_APPLICATION;
			return add_to_hash (hash, Tag, dob);
		}
		else
		{   // Not found in ApplicationInfo, try terminal Info
			if ((res = read_from_registry(CNFG_TERMINAL, Tag, dob)) == SUCCESS)
			{
				// Add Data to hash
				dob->Category = CNFG_TERMINAL;
				return add_to_hash (hash, Tag, dob);
			}
			else
			{
				// Not found in ApplicationInfo and not found in TerminalInfo,
				// try TransactionInfo
				if ((res = read_from_registry(CNFG_TRANSACTION, Tag, dob)) == SUCCESS)
				{	
					// Add Data to hash
					dob->Category = CNFG_TRANSACTION;
					return add_to_hash (hash, Tag, dob);
				}
			}
		}
		*/
		return NO_TAG_FOUND;
	}
	else // (hash_only == true)
	{
	if(Tag == 0x9a){
		buf[0] = 'n';
		buf[1] = 0;
		dob->set(buf,3 , 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
	if(Tag == 0x9f02){
/*
	Amount,Authorized data object
	THIS VALUE IS NOT PRESENT IN REGISTRY!!!!
	I AM NOT SURE WHERE IT COMES FROM!!!
	I ENTERED IT HERE. PLEASE INVESTIGATE!!!
	     --NICOLAI
*/		
		buf[0] = 0x00;
		buf[1] = 0x00;
		buf[2] = 0x00;
		buf[3] = 0x00;
		buf[4] = 0x27;
		buf[5] = 0x10;    // 0x2710 = 10000
		dob->set(buf, 6, 1, "b");
		return add_to_hash (hash, Tag, dob);
	}
		
		
		
		
		return NO_TAG_FOUND;
	}
}

int Context::getTagValue(int iCategory, int Tag, DataObject *dob)
{
	ITERATOR_DATA it_data;
	ITERATOR_RES  it_res;
	int res;
	PAIR pr;

	it_data = hash.find(Tag);

	if (it_data == hash.end())
	{
		// Data is not found in a hash
		// Read Data from a registry
		if ((res = read_from_registry(iCategory, Tag, dob)) == SUCCESS)
		{
			// Add Data to hash
			dob->Category = iCategory;
			return add_to_hash (hash, Tag, dob);
		}
		else
			return NO_TAG_FOUND;
	}
	else
	{
		// Data is found in the hash
		return dob->set (it_data->second->Data, it_data->second->len,
				it_data->second->Category, it_data->second->Format);
	}
	return SUCCESS;
}


int Context::setTagValue(int Tag, DataObject *dob, byte ioFlag)
{
	ITERATOR_DATA it_data;
	PAIR pr;

	it_data = hash.find(Tag);
	
	if (it_data == hash.end())
	{
		// Tag is NOT found in a hash
		if (!check_bit(ioFlag, IO_CREATE))
		{
			// DO Not ADD a value to the HASH
			if (!check_bit(ioFlag, IO_WRITE_THROUGH))
			{
				// Do not write to a storage device
				return DATA_IS_NOT_STORED;
			}
			else // check_bit(ioFlag, IO_WRITE_THROUGH)) == true
			{
				// Store value to a storage device
				return write_to_registry (dob->Category, Tag, dob->Data, dob->len);
			}
		}
		else // check_bit (ioFlag, IO_CREATE) == true
		{
			// Add Value to the hash
			add_to_hash (hash, Tag, dob);
			if (check_bit(ioFlag, IO_WRITE_THROUGH))
			{
				return write_to_registry (dob->Category, Tag, dob->Data, dob->len);
			}
		}
	}
	else // it_data != hash.end()
	{
		// A Tag is found in the hash
		if (check_bit(ioFlag, IO_UPDATE))
		{
			update_hash (it_data, dob->Data, dob->len);
			if (check_bit(ioFlag, IO_WRITE_THROUGH))
			{
				return write_to_registry (dob->Category, Tag, dob->Data, dob->len);
			}
		}
		else
		{
			// Do not allow updating existing value
			return DUPLICATE_INSERT;
		}
	}
	return SUCCESS;
}


int Context::read_from_registry(int iCategory, int Tag, DataObject *dob)
{
	int res;
	CnfgOperationEventImpl opEvent;
	char asciiTag [9]; // Max # of characters in hex representation of the integer (8 + 1(for null terminating character))

	if (iCategory == CNFG_TERMINAL || iCategory == CNFG_APPLICATION ||
		iCategory == CNFG_TRANSACTION)
	{
		CNFG.addOperationEvent(&opEvent);
		Hex2ASCII (Tag, asciiTag);

		// Get Data
		res = CNFG.getValue(iCategory, "Data", asciiTag);
		if (res == SUCCESS)
		{			
			if (opEvent.getValueType() == OPEVENT_BINARY)
			{				
				byte *val;
				opEvent.getByteString (&val);
				int val_len = opEvent.getLength ();
				res = dob->set(val, val_len, iCategory, "b");
				if (res != SUCCESS)
					return res;
			}
			else if(opEvent.getValueType() == OPEVENT_STRING)
			{				
				char *val;
				opEvent.getString(&val);
				int val_len = opEvent.getLength ();
				res = dob->set((byte*)val, val_len + 1, iCategory, "an");
				if (res != SUCCESS)
					return res;
			}
			else if(opEvent.getValueType() == OPEVENT_LONG)
			{				
				long val;
				opEvent.getLong (&val);
				byte byte_val [4];
				ByteFromLong(val, byte_val, 4);
				res = dob->set(byte_val, 4, iCategory, "d");
				if (res != SUCCESS)
					return res;
			}
			else
			{
				CNFG.removeEvent ();
				return DATA_INCOMPATIBLE_TYPE;
			}

			// Get Format
			opEvent.resetEvent (true);
			res = CNFG.getValue(iCategory, "Format", asciiTag);
			if (res == SUCCESS)
			{			
				if (opEvent.getValueType() == OPEVENT_STRING)
				{				
					char *str;
					opEvent.getString (&str);
					dob->setFormat (str);
				}
			}
			res = SUCCESS;
		}
		else 
			res = NO_TAG_FOUND;
		CNFG.removeEvent ();
	}
	else
		res = INVALID_CATEGORY; 
	
	return res;
}

int Context::write_to_registry (int iCategory, int Tag, const byte *Value, 
								int ValLen)
{
	int res;
	CnfgOperationEventImpl opEvent;
	char asciiTag [9]; // Max # of Hex characters in hex representation of the integer (8 + 1(for null terminating character))

	if (iCategory == CNFG_TERMINAL || iCategory == CNFG_APPLICATION)
	{
		Hex2ASCII (Tag, asciiTag);
		CNFG.addOperationEvent(&opEvent);
		res = CNFG.setValueByteString(iCategory, "Data", Value, 
			ValLen, true, asciiTag);
		CNFG.removeEvent();
		return res;
	}
	else
		return INVALID_CATEGORY;
}

int Context::update_hash (ITERATOR_DATA &it_data, 
						  const byte *Value, int ValLen)
{
	DataObject *dob = it_data->second;
	return dob->updateData (Value, ValLen);
}


int Context::add_to_hash (HASH &hash,
						  int Tag, DataObject *dob_new)
{
	DataObject *dob;
	ITERATOR_RES  it_res;

	// Add Data to hash
	dob = new DataObject;
	if (!dob)
		return HASH_INSERT_FAILED;
	else
	{
		*dob = *dob_new;
		// Check if format is present. If not, check the registry to find out
		// the format for a given Tag value. If format is not found in a registry,
		// use default value of "b" (binary)
		if (dob->Format[0] == '\0')
		{
			char data_format[4] = {'\0'};
			getDataFormat (Tag, data_format);
			if (data_format[0] != '\0')
				dob->setFormat(data_format);
			else
				dob->setFormat("b");
		}

		it_res = hash.insert(PAIR(Tag, dob));
		if (it_res.second == false)
		{
			// This condition should never happen
			delete dob;
			return HASH_INSERT_FAILED;
		}
	}
	return SUCCESS;
}

int Context::getDataFormat (int Tag, char *data_format)
{
	int res;
	CnfgOperationEventImpl opEvent;
	
	CNFG.addOperationEvent(&opEvent);
	char asciiTag [9]; // Max # of characters in hex representation of the integer (8 + 1(for null terminating character))

	Hex2ASCII (Tag, asciiTag);

	// Get Data
	res = CNFG.getValue(CNFG_TERMINAL, asciiTag, "DataFormats");
	CNFG.removeEvent();
	if (res == SUCCESS)
	{			
		if (opEvent.getValueType() == OPEVENT_STRING)
		{				
			char *val;
			opEvent.getString (&val);
			strncpy(data_format, val, 3);
			data_format[3] = '\0';
			return SUCCESS;
		}
	}
	
	data_format[0] = '\0';
	return SUCCESS;
}

void Context::removeTag(int Tag)
{
	ITERATOR_DATA it_data;
	it_data = hash.find(Tag);
	if (it_data != hash.end())
	{
		hash.erase(it_data);
	}
}

bool Context::tagExist (int Tag, bool hashOnly)
{
	ITERATOR_DATA it_data;
	ITERATOR_RES  it_res;
	int res;
	DataObject dob;

	it_data = hash.find(Tag);

	if (it_data == hash.end())
	{
		// Data is not found in a map
		if (hashOnly)
			return false;
		else
		{
			// Check the registry
			if(Tag == 0x9f06){
				//AID is always with us
				return true;
			}
			if ((res = read_from_registry(CNFG_APPLICATION, Tag, &dob)) == SUCCESS)
			{
				// Found in registry
				return true;
			}
			else if ((res = read_from_registry(CNFG_TERMINAL, Tag, &dob)) 
				== SUCCESS)
			{
				// Found in registry
				return true;
			}
		}
	}
	else
		return true;
	return false;
}
