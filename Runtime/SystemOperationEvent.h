#ifndef SYSTEMOPERATIONEVENT_H
#define SYSTEMOPERATIONEVENT_H

#include "OperationEventWithValue.h"
#include "custom_types.h"

class SystemOperationEvent :
	public OperationEventWithValue
{
public:
	SystemOperationEvent(void);
	virtual ~SystemOperationEvent(void);

private:
	DateStruct date;
public:
	virtual DateStruct getDate(void);
	virtual void setDate(const DateStruct &new_date);

	virtual int setText(const byte *byteText, UNINT size);
	virtual int getText(char *buff, UNINT *buff_size);
};

#endif

