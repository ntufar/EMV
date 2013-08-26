/*
ReadApplicationData.h
Implements the "Read Application Data" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.2; VIS 1.4.0, ch 5.
*/
#include "EMV_Context.h"
#include "../Utility/utility.h"
#include "scr_command.h"

#include <list>
using namespace std;

#ifdef _DEBUG
	#include <iostream>
	#define COUT cout 
#else
	#define COUT /##/
#endif

// Type definitions
typedef struct AFL_ELEMENT
{
	byte sfi;
	byte first_byte;
	byte last_byte;
	byte oda_counter;
} Afl_Element;

typedef struct ODA_LIST_ELEMENT
{
	byte sfi;
	byte *oda_record;
} ODA_ELEMENT;

typedef list <byte> BYTE_LIST;


class ReadApplicationData :
	public EMV_Context
{
public:
	ReadApplicationData(void);
	virtual ~ReadApplicationData(void);
	int ReadApplData (tlv_parser *tlv_AIP, byte **ppOdaList, int *oda_len);

private:
	int parse_AIP_AFL(tlv_parser *tlv_AIP, byte **AIP, int *aip_len, 
						  byte **AFL, int *afl_len);
	int ReadDataFromICC (const byte *AFL, int afl_len, 
		byte **ppOdaList, int *oda_len);
	int ReadRecords (Afl_Element *pElement, BYTE_LIST &odaList);
	int add2OdaList (const byte *arr, int len, BYTE_LIST &odaList);
	int add2Context (tlv_parser *tlv_record);
	int createOdaList(BYTE_LIST &odaList, byte **ppOdaList, int *oda_len);
	int getMandatoryData( int **mandData, int *count);
	bool checkMandatoryData (const int *mandData, int count);
	int checkAflEntry (Afl_Element *pElement);

};

