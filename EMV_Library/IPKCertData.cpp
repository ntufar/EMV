#include "IPKCertData.h"

IPKCertData::IPKCertData(int Nca):
	header(0),
	cert_format(1),
	issuer_id(2),
	exp_date(6),
	cert_serial_num(8),
	hash_alg(11),
	pub_key_alg(12),
	pub_key_len(13),
	pub_key_exp_len(14),
	pub_key(15),
	hash(Nca-21), //15 + Nca - 36
	trailer(Nca-1) // = Nca - 21 + 20
{
}

IPKCertData::~IPKCertData(void)
{
}
