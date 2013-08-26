#include "Referral.h"

Referral::Referral(void)
{
}

Referral::~Referral(void)
{
}

int Referral::execReferral(SOURCE_OF_REFERRAL srsReferral)
{
	int res;
	
	// Get Terminal Type information ('9f35')
	DataObject dob_termType;
	res = EnvContext.getTagValue (0x9f35, &dob_termType, false);
	if (res != SUCCESS)
		return EMV_MISSING_MANDATORY_DATA;

	// Check if the terminal is attended terminal
	byte termType = dob_termType.Data [0] & 0x0f;
	if (termType != 0x01 && termType != 0x02 && termType != 0x03)
	{
		// Terminal is not attended. Cannot perform referral.
		// Use Default processing -- Decline
		return SetDefaultResult(srsReferral);
	}

	RefControlImpl refControl;
	RefOperationEventImpl refOpEvent;
	AccessManager *pAM;
	pAM = EnvContext.getAccessManager();
	if (!pAM)
		return ERR_AM_NOT_INITIALIZED;

	// Open Referral Control Service
	if ((res = pAM->open(&refControl)) != SUCCESS)
	{
		// Failed to open a referral service. 
		// Use default processing - Decline
		return SetDefaultResult(srsReferral);
	}

	refControl.addOperationEvent (&refOpEvent);
	if ((res = refControl.getRefDataTags ()) != SUCCESS)
	{
		refControl.removeEvent ();
		pAM->close (refControl);
		// Failed to get refernce data from the Referral service. 
		// Without this data cannot perform referral, therefore Decline
		return SetDefaultResult(srsReferral);
	}

	byte *btData = 0;
	int bt_len = refOpEvent.getLength ();
	refOpEvent.getByteString (&btData);

	byte *ref_data = 0;
	UNINT ref_len = 0;
	dol_parser parser(&EnvContext);

	res = parser.createTLVList(btData, bt_len, 
									&ref_data, &ref_len);
	if (res != SUCCESS)
	{
		ref_data = 0;
		ref_len = 0;
	}
	refOpEvent.resetEvent(false);
	res = refControl.perform_referral (srsReferral, ref_data, ref_len);
	if (ref_data)
		delete [] ref_data;
	refControl.removeEvent ();

	if (res != SUCCESS)
	{
		pAM->close (refControl);
		return refOpEvent.getError();
	}
	
	// Referral SUCCESSFULLY completed. Process the results.
	EMV_Context::ReferralResponseCode = refOpEvent.getDisposition();
	if (check_bit(EMV_Context::ReferralResponseCode, REF_ONLINE))
	{
		// Online has been requested. 
		// Update TVR to set the bit 'Merchant forsed transaction online' to '1'
		EMV_Context::updateDataObject (0x95, 4, 0x08, true);

		//Do nothing else here
		return SUCCESS;
	}

	if (srsReferral == REF_INIT_BY_CARD)
	{
		// Retreive Autherisation Response Code and save it to the context
		byte *authResp = 0;
		int auth_len = refOpEvent.getLength();
		refOpEvent.getByteString(&authResp);
		tlv tlvObj;
		res = tlvObj.SetTlv (authResp, auth_len);
		if (res != SUCCESS)
		{
			// Failed to parse the returned data
			return ERR_INVALID_TERMINAL_DATA;
		}
		if (tlvObj.GetTagVal () != 0x8a)
		{
			// Unexpected data -- must be Authorisation Response code (tag '8A')
			return ERR_INVALID_TERMINAL_DATA;
		}
		// Save Auth. Resp. Code to the Context
		res = setDataObject(tlvObj.GetTagVal (), tlvObj.GetValue (), 
			tlvObj.GetLengthVal (), "an", CNFG_TRANSACTION);
	}

	if (check_bit(EMV_Context::ReferralResponseCode, REF_APPROVE) &&
		!check_bit(EMV_Context::ReferralResponseCode, REF_BYPASS))
	{
		// Referral has been APPROVED. Retreive Authorization code
		byte *authCode = 0;
		int auth_len;
		authCode = refOpEvent.getReferralResp(&auth_len);

		tlv tlvObj;
		res = tlvObj.SetTlv (authCode, auth_len);
		if (res != SUCCESS)
		{
			// Failed to parse the returned data
			return ERR_INVALID_TERMINAL_DATA;
		}
		if (tlvObj.GetTagVal () != 0x89)
		{
			// Unexpected data -- must be Authorisation Code (tag '89')
			return ERR_INVALID_TERMINAL_DATA;
		}
		// Save Auth. Code to the Context
		res = setDataObject(tlvObj.GetTagVal (), tlvObj.GetValue (), 
			tlvObj.GetLengthVal (), "an", CNFG_TRANSACTION);
		return SUCCESS;
	}
	return SUCCESS;
	
}

int Referral::SetDefaultResult(SOURCE_OF_REFERRAL srsReferral)
{
	// Set Referral result code to REF_BYPASS
	EMV_Context::ReferralResponseCode = REF_BYPASS;
	if (srsReferral == REF_INIT_BY_CARD)
	{
		// Set Authorisation Response Code to 'Declined (after 
		// card-initiated referral)'
		// Source: EMV book 3, Annex A6: value Z2
				
		return EMV_Context::setDataObject (0x8a, 
			(byte*)SCS_DECLINED_AFTER_ICC_REFERRAL, 2, "an", CNFG_TRANSACTION);
	}
	return SUCCESS;
}
