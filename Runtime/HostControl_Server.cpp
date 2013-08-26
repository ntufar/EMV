#include "HostControl_Server.h"


HostControl_Server::HostControl_Server(void)
{
}

HostControl_Server::~HostControl_Server(void)
{
}

// Returns an array of tags for data required for online message.
int HostControl_Server::getOnlineDataTags (ONLINE_DATA_TAGS tagType)
{
	if (!AM)
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	if (!eventAttached())
		return opEvent->setError (ERR_EVT_NO_EVNT_OBJECT, RUNTIME_EXECUTION);

	int res;

	// Read data from the Registry
	CnfgControlImpl cnfg;
	if ((res = AM->open (&cnfg)) != SUCCESS)
		return opEvent->setError (res, AM_OPENNING_SERVICE);

	CnfgOperationEventImpl cnfgEvent;
	HostOperationEvent *pEvent = (HostOperationEvent*)opEvent;

	cnfg.addOperationEvent (&cnfgEvent);
	switch (tagType)
	{
	case AUTH_RQST_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", AUTH_RQST_REG_KEY);
		break;
	case RESP_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", RESP_REG_KEY);
		break;
	case FINANC_RQST_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", FINANC_RQST_REG_KEY);
		break;
	case ADVICE_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", ADVICE_REG_KEY);
		break;
	case REVERSAL_TAGS:
		res = cnfg.getValue (CNFG_APPLICATION, "Data", REVERSAL_REG_KEY);
		break;
	default:
		res = ERR_HOST_MSG_NOT_SUPPORTED;
	}

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
		return pEvent->setError (ERR_REG_VALUE_READ_FAILED, RUNTIME_EXECUTION);
	}
	else if (res == ERR_HOST_MSG_NOT_SUPPORTED)
	{
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}
	else
	{
		return pEvent->setError (cnfgEvent.getError (), RUNTIME_EXECUTION);
	}
}
