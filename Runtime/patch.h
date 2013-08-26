#ifndef NT_PATCH
#define NT_PATCH

#define HKEY int
#define HANDLE void*
#define HINSTANCE void*
#define HWND void*
#define _VSDCAuthPtr void*
#define _com_error

//From Microsoft documentation:
typedef struct tagSAFEARRAYBOUND {
   unsigned long cElements;
   long lLbound;
} SAFEARRAYBOUND;

typedef struct tagSAFEARRAY {
   unsigned short cDims;       // Count of dimensions in this array.
   unsigned short fFeatures;   // Flags used by the SafeArray
                        // routines documented below.
   unsigned long cbElements;   // Size of an element of the array.
                        // Does not include size of
                        // pointed-to data.
   unsigned long cLocks;      // Number of times the array has been 
                        // locked without corresponding unlock.
   void * pvData;             // Pointer to the data.
   SAFEARRAYBOUND rgsabound[1];      // One bound for each dimension.
} SAFEARRAY;


#define SERVICE_TYPE_CLC "CLC"
#define SERVICE_TYPE_POS "POS"


#endif
