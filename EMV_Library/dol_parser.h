/*
dol_parser.h
This class parses Data object lists and based on the tags in this list it
builds a concatinated list of values.
It builds two types of concatinated lists:
 - createDOL function: is used to build a concatinated list of values only. It
 uses a Data Object List (Tag + Length) as input. This is per EMV 4.0, 
 book 3, ch 1.4).
 - createTLVList function: is used to build a concatinated list of TLV coded
 data objects. It uses a concatinated list of tags as input.
*/
#ifndef DOL_PARSER_H
#define DOL_PARSER_H


#include "Context.h"
#include "../Utility/tlv.h"
#include "../Utility/tlv_creator.h"
#include "../Runtime/custom_types.h"
#include "../Runtime/errors.h"
#include "../Utility/DataObject.h"
#include "Prompter.h"
#include "emv_constants.h"
#include <list>

#ifdef _DEBUG
	#include <iostream>
	using namespace std;
	#define COUT cout 
#else
	#define COUT /##/
#endif

class dol_parser
{
public: // Functions

	// Constructors/ Destructors
	dol_parser(Context *Cntxt);
	virtual ~dol_parser(void);

	// Modifiers
	// Parses Data Object List (dol_list) and creates a concatinated list of 
	// values (see EMV 4.0, book 3, ch 1.4)
	int createDOL(const int dol_type, const byte *dol_list, 
				  UNINT dol_size, byte **data, UNINT *data_len);

	// Cretaes a concatinated list of TLV coded values for each tag found in
	// dol_list. dol_list is concatinated list of tags only.
	int createTLVList(const byte *dol_list, UNINT dol_size, 
							  byte **data, UNINT *data_len);

	// Parses Data Object List which is concatinated list of tags and lengths into
	// DOL_ELEMENT structure which has two arrays - one for tags and one for lengths
	int parse_dol_tags (const byte *header, int len, DOL_ELEMENT *dol);

	// Traverces array of tags in dol and for each tag finds a value and puts it into
	// concatinated list of values (data_list).
	int fill_dol (const int dol_type, DOL_ELEMENT *dol, 
				  byte **data_list, UNINT *dl_len);
	
	// Accessors
	//--------------------------------
	// Returns a pointer to the buffer which keeps concatinated list of values 
	byte *getData();
	// Returns a length of the buffer which keeps concatinated list of values 
	UNINT getLength();

private: // Functions
	void release();
	int DoAdditionalProc(const int dol_type, int tag, byte data_len, 
						  DataObject *dob);
	int  getCurrentDate(DataObject *dob_curDate);
	int  getUnpredictableNumber(DataObject *dob, byte data_len);
	int  generateTCHash(DataObject *dob);
	void RemoveDynamicData();
	void ReleaseList(list <tlv_creator*> &tlv_list);
	int getTransaction(DataObject *dob);
	int getAmount(bool AmountAuthorised, DataObject *dob, DataObject *dob_cur);

private: // Members
	Context *pContext;
	bool AmountChanged;

};

#endif
