
#include "ApplicationInitialization.h"

ApplicationInitialization::ApplicationInitialization(void)
{
}

ApplicationInitialization::~ApplicationInitialization(void)
{
}

int ApplicationInitialization::ApplicationInit(tlv_parser *tlv_Appl, 
											   tlv_parser *tlv_AIP)
{
	int res;
	byte TSI [2] = {0x00, 0x00};
	byte TVR [5] = {0x00, 0x00, 0x00, 0x00, 0x00};

	//UIControlInterface *pUI = (UIControlInterface*)EnvContext.GetService (CNTXT_UI);
	//pUI->writeStatus ("Inside ApplicationInit");

	DataObject dob;
	dob.set (TSI, 2, CNFG_APPLICATION, "b");
	EnvContext.setTagValue (0x9b, &dob, IO_CREATE | IO_UPDATE);
	dob.updateData (TVR, 5);
	EnvContext.setTagValue (0x95, &dob, IO_CREATE | IO_UPDATE);

	// Get custom Data Item Transaction Results (tag '50000004')
	DataObject dob_result;
	res = EnvContext.getTagValue (0x50000004, &dob_result, false);
	if (res != SUCCESS)
	{
		byte result [1] = {0x00};
		dob_result.set(result, 1, CNFG_TRANSACTION, "b");
	}
	else
	{
		memset(dob_result.Data, 0, dob_result.len);
	}
	EnvContext.setTagValue (0x50000004, &dob_result, IO_CREATE | IO_UPDATE);

	if ((res = storeFciItemsInContext(tlv_Appl)) != SUCCESS)
		return res;

	byte *data_list;
	int dl_len;
	
	tlv_parser *tlv_pdol = tlv_Appl->Find (0x9f38, true);
	if (!tlv_pdol)
	{
		// NO PDOL list is specified in ICC's SelectApplication response
		data_list = new byte [2];
		data_list[0] = 0x83;
		data_list[1] = 0x00;
		dl_len = 2;
	}
	else
	{
		// extract PDOL list
		if ((res = create_dol(tlv_pdol, &data_list, &dl_len)) != SUCCESS)
			return res;
	}
	// Issue GetProcessingOptions command
	scr_command command ((SCRControlImpl*)EnvContext.GetService(CNTXT_SCR));
	command.setGetProcessingOptions(data_list, dl_len);
	delete [] data_list;
	R_APDU rapdu;
	if ((res = command.run (&rapdu, TransactionToken)) == SUCCESS)
	{
		if (rapdu.getSW1 () == 0x90 && rapdu.getSW2 () == 0x00)
		{
			if ((res = tlv_AIP->parse (rapdu.copyData (), rapdu.getDataLen ()))
				!= SUCCESS)
			{
				return res;
			}
		}
		else if (rapdu.getSW1 () == 0x69 && rapdu.getSW2 () == 0x85)
		{
			// Error returned by the reader
			// This is the only valid response (except 9000) for this command.
			// See EMV book 3 table I-5
			res = ERR_APPL_INIT_CONDITIONS_NOT_SATISFIED;
		}
		else
			res = ERR_CMD_INVALID_ICC_RESPONSE;
	}

	return res;
}

int ApplicationInitialization::create_dol (tlv_parser *tlv_pdol, 
										   byte **data_list, int *dl_len)
{
	int res;
	UNINT data_len;
	byte *data = 0;

	dol_parser dolParser(&EnvContext);
	// Parse the dol and create a concatinated list of values
	if ((res = dolParser.createDOL(tlv_pdol->GetRoot()->GetTagVal (),
								   tlv_pdol->GetRoot ()->GetValue (), 
								   tlv_pdol->GetRoot ()->GetLengthVal(),
								   &data, &data_len))
								   != SUCCESS)
		return res;

	if ( data_len <= 0)
	{
		// Handle a special case when PDOL is empty
		*data_list = new byte [2];
		if (!(*data_list))
			return ERR_MEMORY_ALLOC;

		(*data_list)[0] = 0x83; // PDOL template label
		(*data_list)[1] = 0x00;
		*dl_len = 2;
		return SUCCESS;
	}

	// Find how many bytes are required to code the length value
	int len_size = 1; // at least one byte will be needed to code the length
	if (data_len >= 128)
		len_size += tlv_creator::GetNumberBytes(data_len);

	// Allocate space for the buffer to hold a template for a concatenated list 
	// of data values
	*data_list = new byte [data_len + len_size + 1]; // Adding one extra byte to keep a tag value
	if (!(*data_list))
	{
		delete [] data;
		return ERR_MEMORY_ALLOC;
	}

	// Store the size of the buffer
	*dl_len = data_len + len_size + 1;

	// Populate data list with the actual data
	int cur_indx = 0;
	// First byte is a tag of the template
	(*data_list)[cur_indx++] = 0x83; // PDOL template label

	// Write length
	if (len_size == 1)
		(*data_list)[cur_indx++] = data_len;
	else
	{
		(*data_list)[cur_indx] = (byte)(0x80 | (len_size - 1));
		for (int i = len_size - 1; i > 0; i--)
		{
			(*data_list)[cur_indx + i] = (byte)data_len;
			data_len >>= 8;
		}
		cur_indx += len_size;
	}

	// Copy a concatenated list of all data values requested by the card
	memcpy ((*data_list) + cur_indx, data, data_len);
	delete [] data;
	return SUCCESS;
}

int ApplicationInitialization::storeFciItemsInContext(tlv_parser *tlv_Appl)
{
	int res;
	DataObject dob_element;
	tlv_parser *tlv_template;
	// Check if it is FCI template
	if (tlv_Appl->GetRoot ()->GetTagVal () != 0x6f)
		return ERR_BAD_ARGUMENT;

	// Get DF Name
	if ((res = setValueToContext (tlv_Appl, 0x84, "b", true)) != SUCCESS)
		return res;

	// Get FCI Proprietary Template
	tlv_template = tlv_Appl->Find (0xa5, false);
	if (!tlv_template)
		return ERR_INVALID_ICC_DATA;

	// Get Application Label
	if ((res = setValueToContext (tlv_template, 0x50, "an", false)) != SUCCESS)
		return res;

	// Get Application Priority Indicator
	if ((res = setValueToContext (tlv_template, 0x87, "b", false)) != SUCCESS)
		return res;

	// Get PDOL
	if ((res = setValueToContext (tlv_template, 0x9f38, "b", false)) != SUCCESS)
		return res;

	// Get Language Preference
	if ((res = setValueToContext (tlv_template, 0x5f2d, "an", false)) != SUCCESS)
		return res;

	// Get Issuer Code Table Index
	if ((res = setValueToContext (tlv_template, 0x9f11, "n", false)) != SUCCESS)
		return res;

	// Get Application Preferred Name
	if ((res = setValueToContext (tlv_template, 0x9f12, "an", false)) != SUCCESS)
		return res;

	// Get FCI Issuer Discretionary Data
	if ((res = setValueToContext (tlv_template, 0xbf0c, "", false)) != SUCCESS)
		return res;
	return SUCCESS;
}

int ApplicationInitialization::setValueToContext (tlv_parser *tlv_template, 
												  int tag, char *format, 
												  bool mandatory)
{
	int res = SUCCESS;
	tlv_parser *tlv_child = tlv_template->Find (tag, false);
	if (!tlv_child && mandatory)
		res = EMV_MISSING_MANDATORY_DATA;
	else if (tlv_child)
	{
		// Store value in the context
		res = EMV_Context::setDataObject (tag, 
			tlv_child->GetRoot ()->GetValue (), 
			tlv_child->GetRoot ()->GetLengthVal (), format, CNFG_TRANSACTION);
		if (tag == 0x84)
		{
			// Current element is DF Name. Store it also as ICC's AID (tag '4F')
			res = EMV_Context::setDataObject (0x4f, 
			tlv_child->GetRoot ()->GetValue (), 
			tlv_child->GetRoot ()->GetLengthVal (), format, CNFG_TRANSACTION);
		}
	}
	return res;
}
