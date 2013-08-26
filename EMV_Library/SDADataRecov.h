/*
SDADataRecov.h
This class contains indexes (or offsets) of the data fields constituted
the Data Recovered from the Signed Dynamic Application Data.

Reference: EMV 4.0 book 2, ch 6.5.2 , table 13.
*/
#ifndef SDADATARECOV_H
#define SDADATARECOV_H

class SDADataRecov
{
public:
	SDADataRecov(int data_len);
	virtual ~SDADataRecov(void);

	const int header;
	const int data_format;
	const int hash_alg_id;
	const int dynamic_data_len;
	const int dynamic_data;
	const int hash_result;
	const int trailer;
};

#endif
