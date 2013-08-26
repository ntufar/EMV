#include "CardActionAnalysis.h"

CardActionAnalysis::CardActionAnalysis(void)
{
}

CardActionAnalysis::~CardActionAnalysis(void)
{
}

CRYPTOGRAM_TYPE CardActionAnalysis::getIccCryptogram()
{
	return icc_requested_cryptogram;
}

bool CardActionAnalysis::IsCombinedDDA_AC()
{
	return CombineDDA_AC;
}

bool CardActionAnalysis::IsAdviseRequired()
{
	return adviseRequired;
}

byte CardActionAnalysis::getRaf()
{
	return raf_code;
}

byte CardActionAnalysis::getpaymentSystCA()
{
	return paymentSystCA;
}


// Analysis a cryptogram returned from the call to the GenerateAC command.
// Source: VIS 1.4.0, ch 11.4, Table 11-4.
// Returns:
//	  SUCCESS - if cryptogram value is valid. 
//	  ERR_ICC_INVALID_CRYPTOGRAM_RESPONSE - if priority of the cryptogram
//				returned by the ICC is higher than the priority requested 
//				by the terminal.
// Note: This function shall be executed only after successful completion 
//		of the parseCardActAnlysResults() function.
int CardActionAnalysis::analyzeResults(CRYPTOGRAM_TYPE term_requested_cryptogram)
{
	if (term_requested_cryptogram == AAC &&
		icc_requested_cryptogram != AAC)
	{
		return ERR_ICC_INVALID_CRYPTOGRAM_RESPONSE;
	}
	if (term_requested_cryptogram == ARQC &&
		icc_requested_cryptogram == TC)
	{
		return ERR_ICC_INVALID_CRYPTOGRAM_RESPONSE;
	}
	return SUCCESS;
}

int CardActionAnalysis::parseCardActAnlysResults(
							 bool CombineDDA_AC,
							 byte *pGenACData, UNINT data_len)
{
	if (!pGenACData || data_len == 0)
		return ERR_BAD_ARGUMENT;

	int res;
	tlv_parser parser;

	// Remove mandatory objects expected in the reponse message from the hash
	// (they shouldn't be there, but do it just in case)
	EnvContext.removeTag(0x9f27); // CID
	EnvContext.removeTag(0x9f36); // ATC
	EnvContext.removeTag(0x9f26); // AC
	EnvContext.removeTag(0x9f10); // IAD

	// Parse data returned from the ICC in the responce to the GenerateAC command
	res = parser.parse (pGenACData, data_len);
	if (res != SUCCESS)
		return res;

	if (parser.GetRoot ()->GetTagVal () == 0x80)
	{
		// The data returned in the response message is primitive data object
		res = parsePrimitive(parser.GetRoot()->GetValue(), 
			parser.GetRoot ()->GetLengthVal ());
	}
	else if (parser.GetRoot ()->GetTagVal () == 0x77)
	{
		// The data object returned in the response message is a constructed 
		// data object. This response is used only in a case of the Combined DDA/AC
		// Generation.
		res = parseConstructed(&parser);
	}
	else
		return ERR_INVALID_ICC_DATA;

	if (res != SUCCESS)
		return res;

	// Read CID from the Context and populate the fields of this object
	DataObject dob_cid;
	res = EnvContext.getTagValue (0x9f27, &dob_cid, false);
	if (res != SUCCESS)
		return res;

	// set Cryptogram type requested by the ICC
	setCryptogramType (dob_cid.Data [0]);
	
	// Set Combined DDA/AC flag
	this->CombineDDA_AC = CombineDDA_AC;

	// Set if Advise is required
	if (check_bit(dob_cid.Data [0], 0x08))
	{
		adviseRequired = true;
	}
	else
	{
		adviseRequired = false;
	}

	// Set Reason/advice/referral code
	raf_code = dob_cid.Data [0] & 0x07;

	// Set Payment System specific cryptogram
	paymentSystCA = (dob_cid.Data [0] >> 4) & 0x03;

	return res;
}

// Parse primitive data object returned by the Generate AC command.
// Format of this data object is described in EMV book 3, ch 2.5.5.4, Format 1
// (Table I - 13), and consists of the following data elements:
// 1. Cryptogram Information Data (CID): tag '9f27', length 1, format "b";
// 2. Application Transaction Counter (ATC): tag '9f36', length 2, format "b";
// 3. Application Cryptogram (AC): tag '9f26', length 8, format "b";
// 4. Issuer Application Data (IAD): tag '9f10', length up to 32, format "b".
//
// Note: 4th parameter is optional.
//		 If parsing succeeded, the function saves the values of the retreived
//		 elements in the Context.
// Returns:
//  SUCCESS - if parsing is successful,
//  error Code - if parsing failed.
int CardActionAnalysis::parsePrimitive(const byte *resp_data, 
									   const int data_len)
{
	if (data_len < 11)
		return ERR_INVALID_ICC_DATA;

	int res;

	// save the value of CID to the context
	DataObject dob_cid;
	res = dob_cid.set(resp_data, 1, CNFG_TRANSACTION, "b");
	if (res != SUCCESS)
		return res;
	res = EnvContext.setTagValue(0x9f27, &dob_cid, IO_CREATE | IO_UPDATE);
	if (res != SUCCESS)
		return res;

	// save the value of ATC to the context
	DataObject dob_atc;
	res = dob_atc.set(resp_data + 1, 2, CNFG_TRANSACTION, "b");
	if (res != SUCCESS)
		return res;
	res = EnvContext.setTagValue(0x9f36, &dob_atc, IO_CREATE | IO_UPDATE);
	if (res != SUCCESS)
		return res;

	// save the value of Application Cryptogram to the context
	DataObject dob_ac;
	res = dob_ac.set(resp_data + 3, 8, CNFG_TRANSACTION, "b");
	if (res != SUCCESS)
		return res;
	res = EnvContext.setTagValue(0x9f26, &dob_ac, IO_CREATE | IO_UPDATE);
	if (res != SUCCESS)
		return res;

	if (data_len > 11)
	{
		// save the value of IAD to the context
		DataObject dob_iad;
		res = dob_iad.set(resp_data + 11, data_len - 11, CNFG_TRANSACTION, "b");
		if (res != SUCCESS)
			return res;
		res = EnvContext.setTagValue(0x9f10, &dob_iad, IO_CREATE | IO_UPDATE);
		if (res != SUCCESS)
			return res;
	}
	
	return res;
}

// Parse constructed data object returned by the Generate AC command.
// Format of this data object is described in EMV book 3, ch 2.5.5.4, Format 2, 
// and consists of at least the following data elements:
// 1. Cryptogram Information Data (CID): tag '9f27', length 1, format "b";
// 2. Application Transaction Counter (ATC): tag '9f36', length 2, format "b";
// 3. Application Cryptogram (AC): tag '9f26', length 8, format "b";
//
// Note: If parsing succeeded, the function saves all the values of the retreived
//		 elements in the Context.
// Returns:
//  SUCCESS - if parsing is successful,
//  error Code - if parsing failed.

int CardActionAnalysis::parseConstructed(tlv_parser *resp_data)
{
	//recersively parse resp_data and save all elements retreived
	tlv_parser *tlv_child;
	int res;

	tlv_child = resp_data->GetFirstChild ();
	while (tlv_child)
	{
		parse_tlv_element (tlv_child);
		tlv_child = resp_data->GetNext ();
	}

	// Check if mandatory objects are present
	DataObject dob_Data;
	// CID:
	if ((res = EnvContext.getTagValue (0x9f27, &dob_Data, true)) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;
	else
	{
		if (dob_Data.len != 1)
			return ERR_INVALID_ICC_DATA;
	}
	dob_Data.reset ();
	// ATC:
	if ((res = EnvContext.getTagValue (0x9f36, &dob_Data, true)) != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;
	else
	{
		if (dob_Data.len != 2)
			return ERR_INVALID_ICC_DATA;
	}
	
	dob_Data.reset ();
	// Application Cryptogram:
	// Do not return the error if Application Cryptogram (tag '9F26') is not present,
	// because there can be present a proprietary cryptogram with different
	// tag
	if ((res = EnvContext.getTagValue (0x9f26, &dob_Data, true)) == SUCCESS)
	{
		if (dob_Data.len != 8)
			return ERR_INVALID_ICC_DATA;
	}

	return SUCCESS;
}

// Recursive function.
// Implements preorder traversal of the tree
void CardActionAnalysis::parse_tlv_element(tlv_parser *tlv_data)
{
	if (!tlv_data)
		return;

	// save the value of the current object into the context
	DataObject dob;
	int res = dob.set(tlv_data->GetRoot ()->GetValue (), 
					  tlv_data->GetRoot ()->GetLengthVal(), 
					  CNFG_TRANSACTION, "b");
	if (res == SUCCESS)
	{
		res = EnvContext.setTagValue(tlv_data->GetRoot ()->GetTagVal(), 
									&dob, IO_CREATE | IO_UPDATE);
	}
	tlv_parser *tlv_child;
	tlv_child = tlv_data->GetFirstChild ();
	while (tlv_child)
	{
		parse_tlv_element (tlv_child);
		tlv_data->GetNext ();
	}
}

void CardActionAnalysis::setCryptogramType(byte cryptogram_type)
{
	switch (cryptogram_type >> 6)
	{
	case AAC:
		icc_requested_cryptogram = AAC;
		break;
	case TC:
		icc_requested_cryptogram = TC;
		break;
	case ARQC:
		icc_requested_cryptogram = ARQC;
		break;
	case AAR:
		icc_requested_cryptogram = AAR;
	default:
		break;
	}
}
