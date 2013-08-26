// RefControl Service
// RefControl Interface Implementation -- Server Side
//

#include "stdafx.h"
#include "RefControlImpl.h"
#include "patch.h"

RefControlImpl::RefControlImpl(void)
{
}

RefControlImpl::~RefControlImpl(void)
{
}

// Returns an array of tags for data required for online message.
int RefControlImpl::getRefDataTags ()
{
	int res = checkInitialization (true);
	if (res != SUCCESS)
		return res;
	RefOperationEvent *pEvent = (RefOperationEvent*)opEvent;
	if (!AM)
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	if (!eventAttached())
		return opEvent->setError (ERR_EVT_NO_EVNT_OBJECT, RUNTIME_EXECUTION);


	// Read data from the Registry
	CnfgControlImpl cnfg;
	if ((res = AM->open (&cnfg)) != SUCCESS)
		return opEvent->setError (res, AM_OPENNING_SERVICE);

	CnfgOperationEventImpl cnfgEvent;

	cnfg.addOperationEvent (&cnfgEvent);

	res = cnfg.getValue (CNFG_APPLICATION, "Data", "4000000B");
	cnfg.removeEvent ();
	if (res == SUCCESS)
	{
		if (cnfgEvent.getValueType () == OPEVENT_BINARY)
		{
			if (cnfgEvent.getLength () > 0)
			{
				byte *byte_data = 0;
				cnfgEvent.getByteString (&byte_data);

				// Successfully read the value from the registry
				return pEvent->setByteString (byte_data, cnfgEvent.getLength ());
			}
		}
		// Unexpected type of the value read from the registry
		return ERR_REG_VALUE_READ_FAILED;
	}
	else
	{
		if (cnfgEvent.getError () != ERR_REG_VALUE_READ_FAILED)
		{
			return pEvent->setError (cnfgEvent.getError (), RUNTIME_EXECUTION);
		}
		else
		{
			return pEvent->setByteString (DEFAULT_LIST_OF_REF_DATA_TAGS,
									 DEFAULT_REF_SIZE);
		}
	}
}

int RefControlImpl::perform_referral(SOURCE_OF_REFERRAL srsReferral,
									 byte *ref_data, UNINT ref_len,
									 UNINT timeout)
{
	long res = checkInitialization (true);
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();
	// Cast the OperationEvent object to the appropriate type
	RefOperationEvent *pEvent = (RefOperationEvent*) opEvent;
	//Reset event
	pEvent->resetEvent();

	// Provide implementation here

	// Get Access to the UI server
	UIControlImpl ui;
	UIOperationEventImpl uiOpEvent;
	AccessManager *pAM = getAccessManager();

	if (!pAM)
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}

	// Open UI service
	if ((res = pAM->open (&ui)) != SUCCESS)
		return opEvent->setError (res, AM_OPENNING_SERVICE);
	ui.addOperationEvent (&uiOpEvent);


	// parse ref_data to retreive PAN
	tlv tlvObj;
	res = tlvObj.SetTlv (ref_data, ref_len);
	if (res != SUCCESS)
	{
		// Invalid Input Data
		pAM->close (ui);
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}

	// Check if the tag of retreived data is PAN ('5A')
	if (tlvObj.GetTagVal () != 0x5a)
	{
		// Invalid Input Data
		pAM->close (ui);
		return pEvent->setError (ERR_INVALID_TERMINAL_DATA, RUNTIME_EXECUTION);
	}

	// Output the prompt 'Call Your Bank'
	res = ui.setPrompt (Language::getString (MSG_ID__CALL_YOUR_BANK, DEFAULT_LANG));
	if (res != SUCCESS)
	{
		pAM->close (ui);
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}

	// Output data required for referral
	//Do not show trailing 'FF' ('FF' is padding)
	int trunk_sz;
	for ( trunk_sz = 0; trunk_sz < tlvObj.GetLengthVal (); trunk_sz++)
	{
		if (tlvObj.GetValue ()[trunk_sz] == 0xFF)
			break;
	}
	char *buff = DumpByteArr(tlvObj.GetValue (), trunk_sz);
	ui.writeStatus ("Referral Data (PAN):");
	ui.writeStatus (buff);
	delete [] buff;

	// Wait for Approval or Dissapproval on using the referral process
	int resEvID;
	int wait_events[2] = {BTN_ENTER, BTN_CANCEL};
	res = ui.waitForEvent(wait_events, 2, &resEvID);
	if (res == SUCCESS)
	{
		if (resEvID == BTN_ENTER)
		{
			// Proceed with referral process
			// Check If Transaction has been approved
			uiOpEvent.resetEvent (true);
			res = ui.getResponse ("Click the 'Enter' for the approval or 'Cancel' otherwise");
			if (res == SUCCESS)
			{
				int btn;
				uiOpEvent.getButton (&btn);
				if (btn == BTN_ENTER)
				{
					pEvent->setDisposition (REF_APPROVE);
					if (srsReferral == REF_INIT_BY_CARD)
					{
						// Set Authorisation Response Code to 'Approved (after 
						// card-initiated referral)'
						// Source: EMV book 3, Annex A6: value Y2
						byte arc[4] = {0x8A, 0x02, 0x59, 0x32}; // Tag-Length-Value
						pEvent->setByteString (arc, 4);
					}

					// Prompt to enter a referral data
					uiOpEvent.resetEvent (true);
					if ((res = ui.receiveString("Please, enter a referral data")) == SUCCESS)
					{
						char *refData;
						int refData_Len = uiOpEvent.getLength ();
						if (refData_Len > 0)
						{
							uiOpEvent.getString (&refData);
						}
						else
						{
							refData = 0;
							refData_Len = -1;
						}
						// Set Data to the opEvent
						// Create a TLV coding of the entered data.
						// Use tag '89' - Authorization Code (6-byte, "an6" format)
						tlv_creator tlv_crObj;
						res = tlv_crObj.SetTlv (0x89, refData_Len + 1, (byte*)refData);
						pEvent->setReferralResp (tlv_crObj.GetDataObject (), 
							tlv_crObj.GetDataObjectLen ());
					}
					return SUCCESS;
				}
				else // Transaction has been declined ('Cancel' button is clicked)
				{
					// Set disposition to Decline offline
					pEvent->setDisposition (0);
					if (srsReferral == REF_INIT_BY_CARD)
					{
						// Set Authorisation Response Code to 'Declined (after 
						// card-initiated referral)'
						// Source: EMV book 3, Annex A6: value Z2
						byte arc[4] = {0x8A, 0x02, 0x5A, 0x32}; // Tag-Length-Value
						pEvent->setByteString (arc, 4);
					}
				}
			}
			else
			{
				// Some error happened during waiting for Approval/Decline decision.
				// It might be a timeout, or some external cancel.
				// Use default processing, which is decline.
				// Set disposition to Decline offline
				pEvent->setDisposition (0);
				if (srsReferral == REF_INIT_BY_CARD)
				{
					// Set Authorisation Response Code to 'Declined (after 
					// card-initiated referral)'
					// Source: EMV book 3, Annex A6: value Z2
					byte arc[4] = {0x8A, 0x02, 0x5A, 0x32}; // Tag-Length-Value
					pEvent->setByteString (arc, 4);
				}
			}
		}
		else // if (resEvID == BTN_CANCEL)
		{
			// Referral process is bypassed.
			// Force online?
			uiOpEvent.resetEvent (true);
			if (srsReferral == REF_INIT_BY_CARD)
			{
				// Referral is initiated by the card (ICC)
				if ((res = ui.getResponse ("Force online?")) == SUCCESS)
				{
					int btn;
					if ((res = uiOpEvent.getButton (&btn)) == SUCCESS)
					{
						if (btn == BTN_ENTER)
						{
							// Set Online
							pAM->close (ui);
							return pEvent->setDisposition (REF_BYPASS | REF_ONLINE);
						}
					}
				}
			}

			// Force approve?
			uiOpEvent.resetEvent (true);
			if ((res = ui.getResponse ("Force Approval offline?")) == SUCCESS)
			{
				int btn;
				if ((res = uiOpEvent.getButton (&btn)) == SUCCESS)
				{
					if (btn == BTN_ENTER)
					{
						// Set Approved offline
						pAM->close (ui);
						if (srsReferral == REF_INIT_BY_CARD)
						{
							// Set Authorisation Response Code to 'Approved (after 
							// card-initiated referral)'
							// Source: EMV book 3, Annex A6: value Y2
							byte arc[4] = {0x8A, 0x02, 0x59, 0x32}; // Tag-Length-Value
							pEvent->setByteString (arc, 4);
						}
						return pEvent->setDisposition (REF_BYPASS | REF_APPROVE);
					}
				}
			}

			// Force decline?
			uiOpEvent.resetEvent (true);
			if ((res = ui.getResponse ("Force Decline offline?")) == SUCCESS)
			{
				int btn;
				if ((res = uiOpEvent.getButton (&btn)) == SUCCESS)
				{
					if (btn == BTN_ENTER)
					{
						// Set Decline offline.
						if (srsReferral == REF_INIT_BY_CARD)
						{
							// Set Authorisation Response Code to 'Declined (after 
							// card-initiated referral)'
							// Source: EMV book 3, Annex A6: value Z2
							byte arc[4] = {0x8A, 0x02, 0x5A, 0x32}; // Tag-Length-Value
							pEvent->setByteString (arc, 4);
						}
						return pEvent->setDisposition (REF_BYPASS);
					}
					else
						return pEvent->setDisposition (REF_BYPASS);
				}
			}
			// No Referral option has been selected. Use online as a default. 
			pAM->close (ui);
			return pEvent->setDisposition (REF_BYPASS | REF_ONLINE);
		}
	}
	else
	{
		if (res == OPERATION_CANCELED_BY_USER)
		{
			ui.setPrompt("Referral was not completed (canceled)");
			pAM->close (ui);
			return pEvent->setError (resEvID, RUNTIME_EXECUTION);
		}
		else
		{
			// Runtime error
			ui.setPrompt("Referral was not completed (run-time error)");
			pAM->close (ui);
			return pEvent->setError (res, RUNTIME_EXECUTION);
		}
	}
	
	return SUCCESS;
}

long RefControlImpl::checkInitialization (bool checkEvent)
{
	if (checkEvent)
	{
		// Check if the OperationEvent has been added to this object
		if (!this->opEvent )
			return ERR_EVT_NO_EVNT_OBJECT;

		if (opEvent->operation_running())
			return ERR_OPEVNT__ALREADY_RUNNING;
	}
	// Check if the Application Name has been added (call to the initialize() 
	// must be made before calling this function)
	if (!this->getAccessManager ())
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}
	return SUCCESS;
}
