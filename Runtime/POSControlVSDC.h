// POSControlVSDC
// Defines the entry point for the DLL module which houses POSControlVSDC module
// implementation.

#ifndef POSCONTROLVSDC_H
#define POSCONTROLVSDC_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the POSCONTROLVSDC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// POSCONTROLVSDC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
/*
#ifdef POSCONTROLVSDC_EXPORTS
#define POSCONTROLVSDC_API __declspec(dllexport)
#else
#define POSCONTROLVSDC_API __declspec(dllimport)
#endif
*/

#define POSCONTROLVSDC_API

#include "POSControlVSDCImpl.h"

#include <map>


//using namespace std;
//typedef std::hash_set<CnfgControlImpl*>::iterator ITERATOR;
//typedef std::pair<hash_set <CnfgControlImpl*>::iterator, bool> RESULT;
typedef std::map<UINT_KEY, POSControlVSDCImpl*> MAP;

static MAP Map;


static void cleanMap();
POSControlVSDCImpl* getPointer(int key);

// Interface Function
extern "C" POSCONTROLVSDC_API int openPos(AccessManager *am, 
										  const byte *aid,
										  int aid_len,
										  UINT_KEY *Key);
extern "C" POSCONTROLVSDC_API void closePOS(UINT_KEY *key);
extern "C" POSCONTROLVSDC_API unsigned int connectedServices();

// 2. Add operation event object
extern "C" POSCONTROLVSDC_API int addOperationEvent(UINT_KEY Key,
													OperationEvent *opEvent);

// 3. Remove operation event object
extern "C" POSCONTROLVSDC_API void removeEvent (UINT_KEY Key);

extern "C" POSCONTROLVSDC_API bool eventAttached (UINT_KEY Key);


// INTERFACE FUNCTIONS
extern "C" POSCONTROLVSDC_API int execPOS(UINT_KEY Key,
										  byte *fci_data, int fci_len);
extern "C" POSCONTROLVSDC_API int initPOS (UINT_KEY Key,
										   void *Param);
extern "C" POSCONTROLVSDC_API void resetPOS (UINT_KEY Key);
extern "C" POSCONTROLVSDC_API int getTransData(
											UINT_KEY Key,
											int Tag, 
											byte *data_value, 
											int *data_sz,
											char format[],
											bool bTransactionDataOnly = true);

#endif
