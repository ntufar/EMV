#include "SDADataRecov.h"

SDADataRecov::SDADataRecov(int Nic):
	header(0),
	data_format(1),
	hash_alg_id(2),
	dynamic_data_len(3),
	dynamic_data(4),
	hash_result (Nic - 21), // = (4 + (Nic - 25)),
	trailer (Nic - 1) // = ((Nic - 21) + 20)
{
}

SDADataRecov::~SDADataRecov(void)
{
}
