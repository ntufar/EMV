/*
ApplicationInitialization.h
Implements the "Initiate Application Processing" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.1; VIS 1.4.0, ch 4.
*/
#include "EMV_Context.h"
#include "../Utility/utility.h"
#include "scr_command.h"
#include "dol_parser.h"
#include "emv_constants.h"

//#include <iostream>
//using namespace std;

class ApplicationInitialization :
	public EMV_Context
{
public:
	ApplicationInitialization(void);
	virtual ~ApplicationInitialization(void);

	int ApplicationInit(tlv_parser *tlv_Appl, tlv_parser *tlv_AIP);
	//int extractPDOL(tlv_parser *tlv_pdol, byte **data_list, int *dl_len);
	int create_dol (tlv_parser *tlv_pdol, byte **data_list, int *dl_len);

private:
	int storeFciItemsInContext(tlv_parser *tlv_Appl);
	int setValueToContext (tlv_parser *tlv_template, int tag, 
		char *format, bool mandatory);
};
