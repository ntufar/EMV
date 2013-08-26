// This class contains indexes (or offsets) of the data fields constituted
// the Data Recovered from the issuer Public Key Certificate
#ifndef IPKCERTDATA_H
#define IPKCERTDATA_H

class IPKCertData
{
public:
	IPKCertData(int data_len);
	virtual ~IPKCertData(void);

	const int header;
	const int cert_format;
	const int issuer_id;
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

