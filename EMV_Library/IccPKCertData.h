// This class contains indexes (or offsets) of the data fields constituted
// the Data Recovered from the ICC Public Key Certificate
#ifndef ICCPKCERTDATA_H
#define ICCPKCERTDATA_H

class IccPKCertData
{
public:
	IccPKCertData(int data_len);
	virtual ~IccPKCertData(void);

	const int header;
	const int cert_format;
	const int pan;
	const int exp_date;
	const int cert_serial_num;
	const int hash_alg;
	const int pub_key_alg;
	const int pub_key_len;
	const int pub_key_exp_len;
	const int pub_key;
	const int hash;
	const int trailer;
};

#endif

