/*
ApplSelector.h
This calss implements two methods of application selection:
- Payment System Directory (PSE) method
- List-of-IDs method.
Unless Payment System Directory method is disabled 
(Registry key SCS\SmartPOS\TerminalInfo\DirectorySelection\EnablePSE == 0),
PSE method is attemted first and then the List-Of-IDs method.
Terminal GUI capabilities affect the final selection of the application. 
The Terminal GUI capabilities flag is stored in registry under the following key:
SCS\SmartPOS\TerminalInfo\50000002.
Bit 1: =1, a terminal is capable of confirming the application selection,
Bit 2: =1, capable of presenting list of applications to chose from,

Reference: EMV 4.0, book 1, ch 8.
*/
#ifndef APPLSELCTOR_H
#define APPLSELCTOR_H

#include <list>

#include "../Runtime/AccessManager.h"
#include "../Runtime/CnfgControlImpl.h"
#include "../Runtime/UIControlImpl.h"
#include "../Runtime/SCRControlImpl.h"
#include "../Utility/utility.h"
#include "scr_command.h"

using namespace std;

#define APPLICATION_NOT_SELECTED    0xA0000001
#define ERR_TRANSACTION_IN_PROGRESS 0xA0000002
#define ERR_INVALID_PSE_FORMAT      0xA0000003
#define TERMINAL_APPL_LIST_IS_EMPTY 0xA0000004
#define CANDIDATE_LIST_IS_EMPTY     0xA0000005
#define NO_TRANSACTION              0xA0000006
#define NO_COMMON_APPLICATIONS      0xA0000007
#define TRANSACTION_CANCELED        0xA0000008
#define AID_PARSE_ERROR             0xA0000009

#define CODE_TABLE_INDX_NOT_FOUND   0xA000000A

#define USER_RESPONSE_TO 30000
#define DIRECTORY_READ 22

typedef struct ApplInfo
{
	byte* AID;
	int aid_len;
	byte  ASI;
} APPL_INFO;

typedef list<APPL_INFO*> APPL_LIST;
typedef list<tlv_parser*> PARSER_LIST;


class ApplSelector
{
public:
	ApplSelector();
	virtual ~ApplSelector(void);

// Interface Methods:
public:
	// Open all services
	int InitServices (AccessManager *AM);
	// Initializes transaction
	int InitializeTransaction(long &TransactionToken);

	int ApplicationSelection (long &TransactionToken,  tlv_parser *tlv_Appl);
	// Builds a list of applications supported by a terminal
	int BuildTerminalApplList ();
	// Finds a name of the PSE directory in a Registry
	int GetPSE();
	// Implements a List-of-AIDs application selection method
	int ListOfAID();
	// Implements a Payment-System-Directory application selection method
	int PaymentDirectorySelection();
	// Implements a final selection of the application
	int FinalSelection(tlv_parser *tlv_Appl);


	// Sorts a candidate list in a priority order where priority 1 is the highest priority
	void SortCandidateList();

	// Prompts a user to Confirm currently selected application
	int ConfirmApplSelection (tlv_parser *parser, bool *bSelected);
	// Automatically selects an application from the candidate list 
	//  (used when a terminal doesn't support selction)
	int SelectAutomatic(tlv_parser *tlv_Appl);
	// Presents a list of mutually supported applications to the user for selection
	int SelectFromList(tlv_parser *tlv_Appl);
	// Selects an application AID of which is stored inside parser.
	int SelectApplication (tlv_parser *parser, tlv_parser *tlv_Appl);
	// Selects an application AID of which is passed as a byte array.
	int SelectApplication (long TransactionToken, 
						   byte *aid, int aid_len, tlv_parser *tlv_Appl);
	// Allows externally cancel a transaction
	void CancelTransaction();
	// Sets a prompt whether based on MsgID or a string Msg
	void SetPrompt(int MsgID, const char *Msg);

	// Returns the TransactionToken used for connecting to card
	long getTransactionToken();

	// Check if terminal supports Payment Directory Selection
	bool IsPSESupported();
private:
	// releases a memory allocated by PSE
	void resetPSE();
	// releases memory allocated to the list of type PARSER_LIST
	void ResetList(PARSER_LIST &parser_list);
	// releases memory allocated for the List of terminal AIDs
	void ResetAIDList ();
	// compare 2 tlv_parser objects to have the same value (used in comparing AIDs)
	int Compare (tlv_parser *val1, tlv_parser *val2);

	// checks if teh application requires confirmation
	bool IsApplReqConfirm(tlv_parser *parser);
	// Reads all records from the file identified by SFI and stores those records
	// in a RecordStack
	int ReadRecords (byte SFI, scr_command &command, PARSER_LIST &RecordsStack);
	int ReadDirRecord (byte SFI, byte record, 
					   scr_command &command, 
					   tlv_parser **tlv_Dir);
	// Finds a prefered name if it exists in FCI represented by parser
	char *GetPreferedName(tlv_parser *parser);
	// Finds an application label if it exists in FCI represented by parser
	char *GetApplLabel(tlv_parser *parser);
	// Finds AID and returns the value as a string
	char *GetAIDasStr(tlv_parser *parser);
	// extracts an ASCII string from the element identified by Tag
	char *extractString (tlv_parser *parser, int Tag);

	// Retreives the language id identified in FCI
	int GetLanguage(tlv_parser *parser);
	
	// closes all services
	void closeServices();
	// Compares two AIDs stored as byte arrays
	// Returns:
	//  0 - AIDs are identical and application is not blocked
	// -1 - AIDs are identical and application is blocked or
	//		AIDs are different
	//  1 - AIDs are identical up to the length of the terminal AID.
	//		partial selection is allowed, 
	//		application is not blocked
	// -2 - same as 1, but application is blocked, or 
	//		partial selection is not allowed
	int CompareAID(R_APDU *rapdu, byte *dfName, int dfName_len, 
				byte *aid_term, int aid_len, int asi);

	// Finds AID in a list of application supported bt a terminal 
	bool FindAID (byte *aid, int aid_len, APPL_LIST *ApplList);

	// Compares two AIDs stored as byte arrays. Returns:
	//  0 - AIDs are identical
	//  1 - AIDs are identical up to the lenghth of the terminal AID (len_term)
	// -1 - AIDs are different
	int IsSameAID (const byte *aid_icc, int len_icc, const byte *aid_term, int len_term);

	// Recursivley goes through the directory structure, finds all matching to 
	// the terminal ADFs, and adds them to the Canidate list
	int SelectDirectories (byte sfi);

	void RemoveFromList (PARSER_LIST::iterator &it,
				PARSER_LIST &CandList, char **ApplArr, int *LangArr, 
				int curIndx, int maxIndx);

	int CheckFCITemplateDir (bool pse, tlv_parser *tlv_dir, byte *sfi);
	int CheckFCITemplateAdf (tlv_parser *tlv_dir, tlv_parser **tlv_DFName);
	int CheckDDFTemplate (tlv_parser *tlv_ddf);
	int CheckADFTemplate (tlv_parser *tlv_adf);
	void OutputMsg(const char* msg);

	int GetIssuerCodeIndx(tlv_parser *parser, byte *CodeIndx);
// Members:
private:
	// Keeps the list of applications supported by a terminal
	APPL_LIST ApplList;
	// Keeps the mutually supported applications
	PARSER_LIST CandList;
	// AccessManager for accessing runtime services
	AccessManager *pAM;
	// UI control
	UIControlImpl UI;
	UIOperationEventImpl uiEvent;
	// SmartCardReader control
	SCRControlImpl SCR;
	// Configuration control (to access configuration data)
	CnfgControlImpl CNFG;
	// Transaction token
	long m_TransactionToken;
	//Terminal select and confirm flags
	bool Terminal_Select;
	bool Terminal_Confirm;

	// Language ID used for output
	int LanguageID;

	// Keeps flags for AdditionalTerminalCapabilities field
	byte AdditionalTerminalCapabilities [5];

	// A pointer to the byte array which keeps a PSE name
	byte *btPSE;
	int PSE_len; // length of the btPSE array

	bool PSEMethod;
	char msg_buff[80];
	byte pseIssuerCodeIndx;
public:
	// Flag indicating a status of the transaction. If TRUE - then transaction is in
	// progress
//	bool TransInProgress;
	// Flag indicating whether or not transaction has been disconnected
//	bool TransDisconnected;
};

#endif
