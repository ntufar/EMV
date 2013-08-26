// UIControl Service
// UI Operation Event declaration

#ifndef UIOPERATIONEVENT
#define UIOPERATIONEVENT

#include "OperationEvent.h"
#include "custom_types.h"


#define UI_NONE    -1
#define UI_INT     10
#define UI_STRING  20

class UIOperationEvent :
	public OperationEvent
{
public:
	UIOperationEvent(void);
	virtual ~UIOperationEvent(void);

	virtual void resetEvent(bool withStop = false);

protected:
	int valueType;

private:
	int intButton;
	int intIndex;
	char *stringValue;
	int length;
	int intData;


protected:
	// Releases a dynamically allocated resource.
	// This function needs to be implemented per every new environment.
	virtual void releaseResource(void **pBuffer) = 0;
	// Dynamically allocates resource.
	// This function needs to be implemented per every new environment.
	virtual void* allocateResource(int typeSize, int bufferSize) = 0;

	void releaseAllResources ();

public:
	// Sets the ID of the Button clicked
	int setButton(int iValue);
	// Returns an ID of the the button clicked.
	int getButton(int* iValue);
	// Sets the value of the Data field
	int setData(int iValue);
	// Returns a value of the Data field
	int getData(int* iValue);
	// Sets the index of the selected item 
	int setIndex(int iValue);
	// Returns the index of the selected item
	int getIndex(int* iValue);
	// Sets a value of the object to string
	int setString(const char* pString);
	// Returns a pointer to the string contained in this object 
	int getString(char **Value);
	// Sets a value of this object to a byte string
	
	// Retreives the length of the string stored by this object
	int getLength(void);
};

#endif

