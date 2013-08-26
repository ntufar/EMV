/*
DataObject.h
The DataObject class encapsulates a data unit to be stored in the Context.
It includes Data field and its size, format, and Registry Category.
This class manages memory allocation and release.
*/
#ifndef DATAOBJECT1_H
#define DATAOBJECT1_H

#include "../Runtime/custom_types.h"
#include "../Runtime/errors.h"
#include <string>

class DataObject
{
public:
	DataObject(void);
	virtual ~DataObject(void);

	int set(const byte *data, int data_len, int category, const char *format);
	void setFormat (const char *format);
	void reset();
	int updateData (const byte *Value, int ValLen);
	const DataObject &operator=(const DataObject &dob_right);

	byte *Data;
	int len;
	int Category;
	char Format [4];
};

#endif
