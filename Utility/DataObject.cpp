#include "DataObject.h"

DataObject::DataObject(void)
{
	Data = 0;
	len = 0;
	Category = 0;
	Format [0] = '\0';
}

DataObject::~DataObject(void)
{
	reset();
}

void DataObject::reset()
{
	if (Data)
	{
		delete [] Data;
		Data = 0;
	}
	len = 0;
	Category = 0;
	Format [0] = '\0';
}

int DataObject::set(const byte *data, int data_len, int category, const char *format)
{
	if (Data)
		reset();

	if (data_len < 0)
		return ERR_BAD_ARGUMENT;

	if (data_len > 0)
	{
		Data = new byte [data_len];
		if (!Data)
			return ERR_MEMORY_ALLOC;

		if (data)
			memcpy (Data, data, data_len);
		else
			memset(Data, 0, data_len);
	}
	else // data_len == 0
		Data = 0;

	len = data_len;
	Category = category;
	setFormat (format);
	return SUCCESS;
}

void DataObject::setFormat (const char *format)
{
	if (!format)
		Format[0] = '\0';
	else
		strncpy(Format, format, 3);
	Format[3] = '\0';
}

int DataObject::updateData (const byte *Value, int ValLen)
{
	if (!Value || ValLen <= 0)
	{
		if (Data)
		{
			delete [] Data;
			Data = 0;
		}
		len = 0;
		return SUCCESS;
	}
	else
	{
		if (len < ValLen)
		{
			byte *bTemp = new byte [ValLen];
			if (!bTemp)
				return ERR_MEMORY_ALLOC;
			delete [] Data;
			Data = bTemp;
		}
		memcpy (Data, Value, ValLen);
		len = ValLen;
		return SUCCESS;
	}
}

const DataObject& DataObject::operator=(const DataObject &dob_right)
{
	if (&dob_right != this)
	{
		reset();
		set (dob_right.Data, dob_right.len, dob_right.Category, dob_right.Format);
	}
	return *this;
}
