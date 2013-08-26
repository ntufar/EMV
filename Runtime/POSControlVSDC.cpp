// POSControlVSDC.cpp : Defines the entry point for the DLL application.
//

#include "POSControlVSDC.h"
#include "AccessManager.h"


// -------------------------------------------------------
// Exported interface functions.
// Each function must have the same name and the same signature 
// as cooresponding interface function in POSControl object.
// In addition the interface functions from EventAdder object must be 
// provided (addOperationEvent and removeEvent)
// -------------------------------------------------------
// 1. Interface Function
extern "C" POSCONTROLVSDC_API int openPos(AccessManager *am, 
										  const byte *aid,
										  int aid_len,
										  UINT_KEY *Key)
{
	int ret;
	if (!Map.empty())
	{
		// Allow only one class instance to be used at any particular time
		ret = ERR_SERVICE_BUSY;
		return ret;
	}
	
	*Key = 0;
	POSControlVSDCImpl *posControl = new POSControlVSDCImpl(aid, aid_len);
	if (!posControl)
	{
		return ERR_MEMORY_ALLOC;
	}
	am->initPOS (aid, aid_len, posControl);
	//am->initControl(posControl);

	UINT_KEY ikey = (UINT_KEY)posControl;
	typedef std::pair <UINT_KEY, POSControlVSDCImpl*> Pair;
	
	std::pair <MAP::iterator, bool> res;
	res = Map.insert (Pair(ikey, posControl));
	
	if (res.second)
	{
		*Key = ikey;
		ret = SUCCESS;
	}
	else
	{
		*Key = 0;
		ret = ERR_MEMORY_ALLOC;
	}
	return ret;
}

static void cleanMap()
{
	std::map<UINT_KEY, POSControlVSDCImpl*>::iterator it;
	for (it = Map.begin ();it != Map.end(); it++)
		delete it->second;
	Map.clear ();
}

static POSControlVSDCImpl* getPointer(UINT_KEY key)
{
	MAP::iterator it;
	POSControlVSDCImpl *pos = NULL;

	it = Map.find(key);
	if (it != Map.end ())
		pos = it->second;
	return pos;
}

extern "C" POSCONTROLVSDC_API void closePOS(UINT_KEY *Key)
{
	std::map<UINT_KEY, POSControlVSDCImpl*>::iterator it;

	it = Map.find(*Key);
	if (it != Map.end ())
	{
		delete it->second;
		Map.erase(it);
	}
	*Key = 0;
}

extern "C" POSCONTROLVSDC_API unsigned int connectedServices()
{
	if (Map.empty ())
		return 0;
	else
		return (unsigned int)Map.size ();
}

// 2. Add operation event object
extern "C" POSCONTROLVSDC_API int addOperationEvent(UINT_KEY Key,
													OperationEvent *opEvent)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return ERR_INVALID_SERVICE_HANDLE;
	return posControl->addOperationEvent (opEvent);
}

// 3. Remove operation event object
extern "C" POSCONTROLVSDC_API void removeEvent (UINT_KEY Key)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return;
	posControl->removeEvent ();
}

extern "C" POSCONTROLVSDC_API bool eventAttached (UINT_KEY Key)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return false;
	return posControl->eventAttached ();
}

extern "C" POSCONTROLVSDC_API int execPOS(UINT_KEY Key,
										  byte *fci_data, int fci_len)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return ERR_INVALID_SERVICE_HANDLE;
	return posControl->execPOS (fci_data, fci_len);
}

extern "C" POSCONTROLVSDC_API int initPOS (UINT_KEY Key,
											  void *Param)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return ERR_INVALID_SERVICE_HANDLE;
	return posControl->initPOS(Param);
}

extern "C" POSCONTROLVSDC_API void resetPOS (UINT_KEY Key)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return;
	posControl->resetPOS();
}

extern "C" POSCONTROLVSDC_API int getTransData(
											UINT_KEY Key,
											int Tag, 
											byte *data_value, 
											int *data_sz, 
											char format[],
											bool bTransactionDataOnly)
{
	POSControlVSDCImpl *posControl = getPointer(Key);
	if (!posControl)
		return ERR_INVALID_SERVICE_HANDLE;
	return posControl->getTransData (Tag, data_value, data_sz, 
		format, bTransactionDataOnly);
}
