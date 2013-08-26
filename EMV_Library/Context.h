/*
Context.h
Implements a context where values can be stored and accessed using tag value
of TLV coded data object. 
Data is stored in the hash table for quick access. If the requested data 
is not found in the context it could be read from the registry and then stored
in the context for future accesses. Data could be also written back to 
the Registry.
*/
#ifndef SCS_CONTEXT_H
#define SCS_CONTEXT_H

#include <backward/hash_map.h>
#include <map>
#include "../Runtime/CnfgControlImpl.h"
#include "../Runtime/SCRControlImpl.h"
#include "../Runtime/CryptoControlImpl.h"
#include "../Runtime/SystemControlImpl.h"
#include "../Runtime/UIControlImpl.h"
#include "../Runtime/AccessManager.h"
#include "../Utility/common_functions.h"
#include "../Utility/DataObject.h"
#include "emv_constants.h"
#include "../Runtime/patch.h"

using namespace std;



typedef hash_map <int, DataObject*> HASH;
typedef pair <int, DataObject*> PAIR;
typedef hash_map<int, DataObject*>::iterator ITERATOR_DATA;
typedef pair <ITERATOR_DATA, bool> ITERATOR_RES;

#define DATA_IS_NOT_STORED			 0xb0000001
#define INVALID_CATEGORY			 0xb0000002
#define HASH_INSERT_FAILED			 0xb0000003
#define DUPLICATE_INSERT			 0xb0000004
#define SERVICE_NOT_FOUND_IN_CONTEXT 0xb0000005

// IO Flag
#define IO_WRITE_THROUGH  0x01
#define IO_CREATE         0x02
#define IO_UPDATE         0x04


// Service Types:
#define CNTXT_UI   0x01
#define CNTXT_SCR  0x02
#define CNTXT_CNFG 0x03
#define CNTXT_CRYPTO 0x04
#define CNTXT_SYSTEM 0x05
extern int HOLARIO;

class Context
{
public:
	
	Context(void);
	~Context(void);

	// Initializes a contex
	int initializeContext (AccessManager *pAM);
	void unInitializeContext (bool StopServices = true);

	ServiceControl* GetService(int ServiceType);
	AccessManager* getAccessManager();
	
	int getTagValue(int iCategory, int Tag, DataObject *dob);
	int getTagValue(int Tag, DataObject *dob, bool hash_only = false);
			
	int setTagValue(int Tag, DataObject *dob, 
					byte ioFlag = IO_WRITE_THROUGH | IO_CREATE);
	bool tagExist (int Tag, bool hashOnly = true);
	void removeTag(int Tag);
	int getDataFormat (int Tag, char *data_format);

private:
	int read_from_registry(int iCategory, int Tag, DataObject *dob);
	int write_to_registry (int iCategory, int Tag, 
		                   const byte *Value, int ValLen);
	int update_hash (ITERATOR_DATA &it_data, 
					 const byte *Value, int ValLen);
	int add_to_hash (HASH &hash,
					 int Tag, DataObject *dob);
private:
	// Common Services
	AccessManager *pAM;
	CnfgControlImpl CNFG;
	UIControlImpl UI;
	SCRControlImpl SCR;
	CryptoControlImpl Crypto;
	SystemControlImpl SYST;
	HASH hash;
};

#endif

