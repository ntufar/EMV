#include "SSADataRecov.h"

SSADataRecov::SSADataRecov(int Ni):
	header(0),
	data_format(1),
	hash_alg_id(2),
	data_auth_code(3),
	pad_pattern(5),
	hash_result (Ni - 21), // = (5 + (Ni - 26)),
	trailer (Ni - 1) // = ((5 + (Ni - 26)) + 20)
{
}

SSADataRecov::~SSADataRecov(void)
{
}
