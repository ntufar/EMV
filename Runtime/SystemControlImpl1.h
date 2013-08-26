// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SYSTEMCONTROLIMPL1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SYSTEMCONTROLIMPL1_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SYSTEMCONTROLIMPL1_EXPORTS
#define SYSTEMCONTROLIMPL1_API __declspec(dllexport)
#else
#define SYSTEMCONTROLIMPL1_API __declspec(dllimport)
#endif

#include "SystemControlImpl.h"

// This class is exported from the SystemControlImpl1.dll
class SYSTEMCONTROLIMPL1_API CSystemControlImpl1 {
public:
	CSystemControlImpl1(void);
	// TODO: add your methods here.
};

extern SYSTEMCONTROLIMPL1_API int nSystemControlImpl1;

SYSTEMCONTROLIMPL1_API int fnSystemControlImpl1(void);

SystemControlImpl systControl;
extern "C" SYSTEMCONTROLIMPL1_API int retreiveDate();
extern "C" SYSTEMCONTROLIMPL1_API int addOperationEvent(OperationEvent *opEvent);
extern "C" SYSTEMCONTROLIMPL1_API void removeEvent ();

