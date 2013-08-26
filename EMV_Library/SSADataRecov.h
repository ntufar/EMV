/*
SSADataRecov.h
This class contains indexes (or offsets) of the data fields constituted
the Data Recovered from the Signed Static Application Data.

Reference: EMV 4.0 book 2, ch 5.4 , table 5.
*/
#ifndef SSADATARECOV_H
#define SSADATARECOV_H

class SSADataRecov
{
public:
	SSADataRecov(int data_len);
	~SSADataRecov(void);

	const int header;
	const int data_format;
	const int hash_alg_id;
	const int data_auth_code;
	const int pad_pattern;
	const int hash_result;
	const int trailer;
};

#endif

