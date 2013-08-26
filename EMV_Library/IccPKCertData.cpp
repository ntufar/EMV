#include "IccPKCertData.h"

IccPKCertData::IccPKCertData(int Ni):
	header(0),
	cert_format(1),
	pan(2),
	exp_date(12),
	cert_serial_num(14),
	hash_alg(17),
	pub_key_alg(18),
	pub_key_len(19),
	pub_key_exp_len(20),
	pub_key(21),
	hash(Ni-21), //21 + Nca - 42
	trailer(Ni-1) // = Nca - 21 + 20
{
}

IccPKCertData::~IccPKCertData(void)
{
}
