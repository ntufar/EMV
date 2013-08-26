#ifndef _EMV_H_
#define _EMV_H_

#ifdef __cplusplus
extern "C" {
#endif


#define EVAL_TEST


typedef unsigned char uchar;
typedef unsigned short ushort;

//#include "utils.h"

#define max(a,b)	(a > b ? a: b)
// Menu structure
typedef struct
{
	char * const pcText; 	// item text
	uchar ucVal;		// item index
} MENU2;

extern void vWait (uchar ucTime);

//extern uchar ucDispMenu (char *pcTitle, const MENU *pxMenu, uchar ucSize);


#define TRUE  1
#define FALSE 0

#define CONFIG_SET 1 //For Fill Term Params Function MGG



// CVM Results
#define CVM_SUCCESS		0x02
#define CVM_FAIL		0x01
#define CVM_UNKNOWN		0x0
#define CVM_NOT_SUPPORTED	0x03

// Application Selection Types
#define	SELECT_PSE  0
#define	SELECT_DDF  1
#define	SELECT_ADF  2


// DOL Types
#define	DOL_PDOL	0
#define	DOL_CDOL1	1
#define	DOL_CDOL2	2
#define	DOL_TDOL	3
#define	DOL_DDOL	4


#define	APP_SELECT_PSE			0
#define	APP_SELECT_LIST_OF_AID	1
#define APP_INF_LEN	18	

// Stack for PSE
#define MAX_STACK_SIZE		5

#define STACK_EMPTY			0
#define STACK_FULL			1

// DOL formats
#define DOL_FORMAT_TLV		0	// For Europay DOL should be in TLV format
#define DOL_FORMAT_NONTLV	1   // For VISA

// Card Brands
#define	BRAND_VISA			1
#define	BRAND_EUROPAY		2
#define	BRAND_MASTER		3

#define	CA_PUBLIC_KEY_MOD	0
#define	ICC_PUBLIC_KEY_MOD	1
#define	ISS_PUBLIC_KEY_MOD	2
#define	ICC_PIN_ENC_PUBLIC_KEY_MOD	3


// Error Codes
#define PROCESS_OK 					100
#define SET_PROTOCOL_ERROR 			101
#define CARD_COM_ERROR 				102
#define CARD_REJECTED 				103
#define TERM_PARAM_NOT_SET 			104
#define NO_MATCHING_APP 			105
#define DATA_FORMAT_INCORRECT 		106
#define ISS_COD_TBL_OUT_OF_RANGE 	107
#define DUPLICATE_CARD_DATA_ELEMENT 108
#define GET_AMOUNT_ERROR 			109
#define AMOUNT_CANCELLED 			110
#define LEN_INCORRECT 				111
#define AIP_NOT_RECEIVED 			112
#define AFL_NOT_RECEIVED 			113
#define AFL_LEN_OUT_OF_RANGE 		114
#define SFI_OUT_OF_RANGE 			115
#define AFL_INCORRECT 				116
#define EXP_DATE_INCORRECT 			117
#define EFF_DATE_INCORRECT 			118
#define MISSING_MANDATORY_OBJECT 	119
#define CA_PUBKEY_NOT_FOUND 		120
#define CVMLIST_LEN_INCORRECT 		121
#define CRYPTOGRAM_TYPE_INCORRECT 	122
#define SERVIC_NOT_ALLOWED 			123
#define APPLIST_PARSE_ERROR 		124
#define NO_SELECTED_APP             125
#define CARD_ERROR                  126
#define PSE_NOT_SUPPORTED_BY_CARD   127
#define COND_NOT_SATISFIED			128
#define NO_TERM_APP					129
#define CARD_CHECK_ERROR            130
#define APP_SELECT_PSE_ERROR        131
#define DATA_ELEMENT_OUT_OF_RANGE   132
#define PIN_TRY_LIMIT_EXC           133 // EVAL1.6




// The Tag list definition is necessary for the Generic module
// If a tag will be changed the value is modified here and the
// Generic module is not modified
// TAG DEFINITION

#define TAG_AppIdentIcc         0x004F /* Application Identifier (AID)      */
#define TAG_AppLab              0x0050 /* Application Label                 */
#define TAG_CmdToPerf           0x0052 /* Command tp Perform                */
#define TAG_Trk2EquDat          0x0057 /* Track 2 Equivalent Date           */
#define TAG_AppPan              0x005A /* Application Primary Account       */
                                       /*    Number (PAN)                   */
#define TAG_CarHolNam           0x5F20 /* Cardholder Name                   */
#define TAG_AppExpDat           0x5F24 /* Application expiration Date       */
#define TAG_AppEffDat           0x5F25 /* Application Effective Date        */
#define TAG_IssCouCod           0x5F28 /* Issuer Country Code               */
#define TAG_TraCurCod           0x5F2A /* Transaction Currency Code         */
#define TAG_LanPre              0x5F2D /* Language Preference               */
#define TAG_SerCod              0x5F30 /* Service Code                      */
#define TAG_AppPanSeqNbr        0x5F34 /* Application Primary Account Number*/
                                       /*     (PAN) Sequence Number         */
#define TAG_TraCurExp           0x5F36 /* Transaction Currency Exponent     */
#define TAG_AppTemplate         0x0061 /* Application Template              */
#define TAG_FCITemplate         0x006F /* File Control Information (FCI)    */
                                       /*     Template                      */
#define TAG_AEFTemplate         0x0070 /* Application Elementary File (AEF) */
                                       /*     Data Template                 */
#define TAG_IssuerScript1       0x0071 /* Issuer Script Template 1          */
#define TAG_IssuerScript2       0x0072 /* Issuer Script Template 2          */
#define TAG_DirDisTmp           0x0073 /* Directory Discretionary Template  */
#define TAG_RespMesTmp2         0x0077 /* Response Message Template Format 2*/
#define TAG_RespMesTmp1         0x0080 /* Response Message Template Format 1*/
#define TAG_AmtAuthorBin        0x0081 /* Amount, Authorised (Binary)       */
#define TAG_AppIntPro           0x0082 /* Application Interchange Profile   */
#define TAG_CmdeTemplate        0x0083 /* Command Template                  */
#define TAG_DFName              0x0084 /* Dedicated File (DF) Name          */
#define TAG_IssuerScriptCmde    0x0086 /* Issuer Script Command             */
#define TAG_AppPriInd           0x0087 /* Application Priority Indicator    */
#define TAG_SFI                 0x0088 /* Short File Identifier (SFI)       */
#define TAG_AuthoCode           0x0089 /* Authorisation Code                */
#define TAG_AuthoRespCode       0x008A /* Authorisation Response Code       */
#define TAG_CDOL1               0x008C /* Card Risk Management Data Object  */
                                       /*    List 1 (CDOL1)                 */
#define TAG_CDOL2               0x008D /* Card Risk Management Data Object  */
                                       /*    List 2 (CDOL2)                 */
#define TAG_CVMList             0x008E /* Cardholder Verification Metod     */
                                       /*    (CVM) List                     */
#define TAG_CerAutPubKeyIndIcc  0x008F /* Certification Authority Public Key*/
                                       /*    Index                          */
#define TAG_IssPubKeyCer        0x0090 /* Issuer Public Key Certificat      */
#define TAG_IssAuthDat          0x0091 /* Issuer Authentication Data        */
#define TAG_IssPubKeyRem        0x0092 /* Issuer Public Key Remainder       */
#define TAG_SigStaAppDat        0x0093 /* Signed Static Application Data    */
#define TAG_AppFilLoc           0x0094 /* Application File Locator (AFL)    */
#define TAG_TerVerRes           0x0095 /* Terminal Verification Results     */
#define TAG_TDOL                0x0097 /* Transaction Certificate Data      */
                                       /*    Object List (TDOL)             */
#define TAG_TCHashVal           0x0098 /* Transaction Certificate (TC) Hash */
                                       /*    Value                          */
#define TAG_TraPINDat           0x0099 /* Transaction Personal Identificati-*/
                                       /*    on Number (PIN) Data           */
#define TAG_TraDat              0x009A /* Transactin Datec                  */
#define TAG_TraStaInf           0x009B /* Transaction Status Information    */
#define TAG_TraType             0x009C /* Transaction Type                  */
#define TAG_DDFName             0x009D /* Directory Definition File (DDF)   */
                                       /*    Name                           */
#define TAG_AcqID               0x9F01 /* Acquirer Identifier               */
#define TAG_AmtAuthorNum        0x9F02 /* Amount, Authorised (Numeric)      */
#define TAG_AmtOtherNum         0x9F03 /* Amount, Other (Numeric)           */
#define TAG_AmtOtherBin         0x9F04 /* Amount, Other (Binary)            */
#define TAG_AppDisDat           0x9F05 /* Application Discretionary Data    */
#define TAG_AIDTer              0x9F06 /* Application Identifier (AID)      */
#define TAG_AppUsaCon           0x9F07 /* Application Usage Controm         */
#define TAG_AppVerNbrICC        0x9F08 /* Application Version Number        */
#define TAG_AppVerNbrTer        0x9F09 /* Application Version Number        */
#define TAG_CarHolNamExt        0x9F0B /* Cardholder Name - Extended        */
#define TAG_IssActCodDef        0x9F0D /* Issuer Action Code - Default      */
#define TAG_IssActCodDen        0x9F0E /* Issuer Action Code - Denial       */
#define TAG_IssActCodOnl        0x9F0F /* Issuer Action Code - online       */
#define TAG_IssAppDat           0x9F10 /* Issuer Application Data           */
#define TAG_IssCodTabInd        0x9F11 /* Issuer Code Table Index           */
#define TAG_AppPreNam           0x9F12 /* Application Preferred Name        */
#define TAG_LasOnlATCReg        0x9F13 /* Last Online Application Transacti-*/
                                       /*    on Counter(ATC) Registr        */
#define TAG_LowConOffLim        0x9F14 /* Lower Consecutive Offline Limit   */
#define TAG_MerCatCod           0x9F15 /* Merchant Category Code            */
#define TAG_MerID               0x9F16 /* Merchant Identifier               */
#define TAG_PinTryCou           0x9F17 /* Personal Identification Number    */
                                       /*    (PIN) Try Counter              */
#define TAG_IssuerScriptID      0x9F18 /* Issuer Script Identifier          */
#define TAG_TerCouCod           0x9F1A /* Terminal Country Code             */
#define TAG_TerFloorLimit       0x9F1B /* Terminal Floor Limit              */
#define TAG_TerID               0x9F1C /* Terminal Identification           */
#define TAG_TerRiskManDat       0x9F1D /* Terminal Risk Management Data     */
#define TAG_IFDSerNum           0x9F1E /* Interface Device (IFD) Serial     */
                                       /*     Number                        */
#define TAG_Trk1DisDat          0x9F1F /* Track 1 Discretionary Data        */
#define TAG_Trk2DisDat          0x9F20 /* Track 2 Discretionary Data        */
#define TAG_TraTim              0x9F21 /* Transaction Time                  */
#define TAG_CerAutPubKeyIndTer  0x9F22 /* Certification Authority Public Key*/
                                       /*     Index                         */
#define TAG_UppConOffLim        0x9F23 /* Upper Consecutive Offline Limit   */
#define TAG_AppCryptogram       0x9F26 /* Application Cryptogram            */
#define TAG_CryptInfDat         0x9F27 /* Cryptogramm Information Data      */
#define TAG_ICCPinPubKeyCer     0x9F2D /* ICC PIN Encipherment Public Key   */
                                       /*     Certificate                   */
#define TAG_ICCPinPubKeyExp     0x9F2E /* ICC PIN Encipherment Public Key   */
                                       /*     Exponent                      */
#define TAG_ICCPinPubKeyRem     0x9F2F /* ICC PIN Encipherment Public Key   */
                                       /*     Remainder                     */
#define TAG_IssPubKeyExp        0x9F32 /* Issuer Public Key Exponent        */
#define TAG_TerCap              0x9F33 /* Terminal Capabilities             */
#define TAG_CVMResults          0x9F34 /* Cardholder Verification Method    */
                                       /*     (CVM) Result                  */
#define TAG_TerTyp              0x9F35 /* Terminal Type                     */
#define TAG_AppTraCou           0x9F36 /* Application Trznsaction Counter   */
                                       /*     (ATC)                         */
#define TAG_UnpreNumber         0x9F37 /* Unpredictable Number              */
#define TAG_PDOL                0x9F38 /* Processing Options Data Object    */
                                       /*     List (PDOL)                   */
#define TAG_POSEntryMod         0x9F39 /* Point-of-Service (POS) Entry Mode */
#define TAG_AmtRefCur           0x9F3A /* Amount, Reference Currency        */
#define TAG_AppRefCur           0x9F3B /* Application Reference Currency    */
#define TAG_TraRefCurCod        0x9F3C /* Transaction Reference Currency    */
#define TAG_TraRefCurExp        0x9F3D /* Trancaction Reference Currency    */
                                       /*     Exponent                      */
#define TAG_AddTerCap           0x9F40 /* Additional Teminal Capabilities   */
#define TAG_TraSeqCou           0x9F41 /* Transaction seauence Counter      */
#define TAG_AppCurCod           0x9F42 /* Application Currency Code         */
#define TAG_AppRefCurExp        0x9F43 /* Application Reference Currency    */
                                       /*     Exponent                      */
#define TAG_AppCurExp           0x9F44 /* Application Currency Exponent     */
#define TAG_DatAuthCod          0x9F45 /* Data Authentication Code          */
#define TAG_ICCPubKeyCer        0x9F46 /* ICC Public Key Certificate        */
#define TAG_ICCPubKeyExp        0x9F47 /* ICC Public Key Exponent           */
#define TAG_ICCPubKeyRem        0x9F48 /* ICC Public Key Remainder          */
#define TAG_DDOL                0x9F49 /* Dynamic Data Object List (DDOL)   */
#define TAG_StaDatAuthTagLst    0x9F4A /* Static Data Authentication Tag    */
                                       /*     List                          */
#define TAG_SigDynAppDat        0x9F4B /* Signed Dynamic Application Data   */
#define TAG_ICCDynNum           0x9F4C /* ICC Dynamic Number                */
#define TAG_TraCatCode          0x9F53 /* Tansaction Category Code          */
                                       /*   !!!! Europay only !!!!          */
                                       /*   !!!! NOT used in Generic !!!!   */
#define TAG_FCIPropTmp          0x00A5 /* File Control Information (FCI)    */
                                       /*     Proprietary Template          */
#define TAG_FCIIssDisDat        0xBF0C /* File Control Information (FCI)    */
                                       /*     Issuer Discretionary Data     */

// The Tag list definition is necessary for the Generic module
// If a tag will be changed the value is modified here and the
// Generic module is not modified
// TAG DEFINITION starting to DF80, end DFFE

// Proprietary Tags :

#define TAG_Language            0xDF80 /* Languages defined in the terminal */
                                       /*     (according to ISO 639)        */
#define TAG_MerNam              0xDF81 /* Merchant Name                     */
#define TAG_MerLoc              0xDF82 /* Merchant Location                 */
#define TAG_TerActCodDef        0xDF83 /* Terminal Action Code - Default    */
#define TAG_TerActCodDen        0xDF84 /* Terminal Action Code - Denial     */
#define TAG_TerActCodOnl        0xDF85 /* Terminal Action Code - Online     */
#define TAG_ReferralRequired    0xDF86
#define TAG_Threshold           0xDF87 /* Threshold Value for Biased Random */
                                       /*     Selection                     */
#define TAG_TargetPercent       0xDF88 /* Target Percentage to be used for  */
                                       /*     Random Selection              */
#define TAG_MaxTarget           0xDF89 /* Maximum Target Percentage to be   */
                                       /*     used for Biased Random        */
                                       /*     Selection                     */
#define TAG_PinResult           0xDF8A
#define TAG_TerOptSelGen        0xDF8B /* Terminal options (online forced,  */
                                       /*     amount acquisition ,easy entry*/
                                       /*     management)                   */
#define TAG_TerminalOptGen      0xDF8C
#define TAG_AIDTerList          0xDF8D
#define TAG_DEBUGTrace          0xDF8E /* Code for printing trace required  */
                                       /*     by VISA and useful in any appl*/
#define TAG_TAGErrDisplay       0xDF8F

#define TAG_SignatRequired      0xDF90
#define TAG_IssScriptRes        0xDF91 /* Issuer Script Results             */
#define TAG_LanguageUsed        0xDF92 /* Language used in the transaction  */
                                       /*     flow (cardholder language)    */
#define TAG_EasyEntryCard       0xDF93
#define TAG_TraTypSrv           0xDF94
#define TAG_DDOL_Default        0xDF95 /* Default Dynamic Data Authenticati-*/
                                       /*     on Data Object list (DDOL)    */
#define TAG_AuthoRespCod_List   0xDF96 /* Authorisation Response Codes List */
                                       /*     define by the acquirer        */
#define TAG_Flag_Auto           0xDF97 /* Flag for Forcing the Online tran- */
                                       /*     saction, from the Associate   */
#define TAG_TDOL_Default        0xDF98 /* Default Transaction Certificate   */
                                       /*     Data Object List (TDOL)       */


// !!!  The following constant are used in i_init.c !!!
// Old specific Tag ... The values are fixed in the MP3S protocole !!!

#define TAG_TabTerFloorLimit    0xDF99          /* CM 000214 These values must not be changed */
#define TAG_TabThreshold        0xDF9A
#define TAG_TerOptSelAss        0xDF9B
#define TAG_TerminalOptAss      0xDF9C
#define TAG_ReversalPIN         0xDF9E
#define TAG_Key_Rsa             0xDF9F

#define TAG_Key_ODOL            0xDFA0



// For getting trace of the commands between card and terminal set COMMAND_GET_TRACE
#define COMMAND_GET_TRACE		1
#define COMMAND_NOTGET_TRACE	0
#define COMMAND_TRACE			COMMAND_GET_TRACE


// EMV Page
#define EMV_PAGE	2

/*enum ACCESS_REPORT {
	ACCESS_OK,
	NO_LENGTH,
	TAG_NOT_FOUND
};
*/
// APP Len ranges
#define	MIN_APP_LEN		5
#define	MAX_APP_LEN		16


// Transaction type codification
/*#define TRN_TYPE_DEBIT       0x00
#define TRN_TYPE_CASH        0x01
#define TRN_TYPE_REVERSAL    0x02
#define TRN_TYPE_PWCB        0x09
// AK 020225 it is not only for CB #ifdef COMPIL_CB
#define TRN_TYPE_CREDIT      0x20
// AK 020225 it is not only for CB #endif
*/

// Max Lengths
#define	MAX_MODULUS_LEN			256
#define	MAX_ISSUER_SCRIPT_LEN	128
#define	MAX_PDOL_LEN			128
#define	MAX_SDA_TAG_LIST_LEN	128


// AIP bits
#define	AIP_SDA		0x40
#define	AIP_DDA		0x20
#define	AIP_VERIF	0x10
#define	AIP_TRMNG	0x08		// Terminal Risk Management bit
#define	AIP_ISSAUTH	0x04		// Issuer Authentication bit


// TVR bits
// byte 1
#define	TVR_AUTH_NOT_PERFORMED		0x080
#define	TVR_SDA_FAILED				0x040
#define	TVR_ICC_DATA_MISSING		0x020
#define	TVR_CARD_IN_EXCEPT_FILE		0x010
#define	TVR_DDA_FAILED				0x008
// byte 2
#define	TVR_DIFF_APP_VERSION		0x180
#define	TVR_EXPIRED_APP				0x140
#define	TVR_APP_NOT_EFFECTIVE		0x120
#define	TVR_SERVICE_NOT_ALLOWED		0x110
#define	TVR_NEW_CARD				0x108
// byte 3
#define	TVR_VERIF_NOT_SUCCESS		0x280
#define	TVR_UNRECOG_CVM				0x240
#define	TVR_PIN_TRY_EXCEEDED		0x220
#define	TVR_PINPAD_NOT_PRESENT		0x210
#define	TVR_PIN_NOT_ENTERED			0x208
#define	TVR_ONLINE_PIN_ENTERED		0x204
// byte 4
#define	TVR_FLOOR_LIMIT_EXCEEDED	0x380
#define	TVR_LCOL_EXCEEDED			0x340
#define	TVR_UCOL_EXCEEDED			0x320
#define	TVR_TRAN_RANDOM_SELECTED	0x310
#define	TVR_MERCH_FORCED_ONLINE		0x308
// byte 5
#define	TVR_DEFAULT_TDOL_USED		0x480
#define	TVR_ISSUER_AUTH_UNSUCCESS	0x440
#define	TVR_ISSUER_SCRIPT_FAILED1	0x420
#define	TVR_ISSUER_SCRIPT_FAILED2	0x410


// TSI bits
// byte 1
#define	TSI_AUTH_PERFORMED			0x80
#define	TSI_VERIF_PERFORMED			0x40
#define	TSI_CARD_RISKMNG_PERFORMED	0x20
#define	TSI_ISSUER_AUTH_PERFORMED	0x10
#define	TSI_TERM_RISKMNG_PERFORMED	0x08
#define	TSI_ISSUER_SCRIPT_PERFORMED 0x04


// Terminal Capabilities (9F33) bits
// byte 1
#define TERMCAP_MAN_KEY_ENTRY		0x80
#define TERMCAP_MAGNETIC_STRIPE		0x40
#define TERMCAP_IC_WITH_CONTACTS	0x20
// byte 2
#define TERMCAP_PLAINTEXT_PIN_OFF	0x180
#define TERMCAP_ENCHIPERED_PIN_ONL	0x140
#define TERMCAP_SIGNATURE			0x120
#define TERMCAP_ENCHIPERED_PIN_OFF	0x110
#define TERMCAP_NO_CVM_SUPPORTED	0x108
// byte 3
#define TERMCAP_SDA					0x280
#define TERMCAP_DDA					0x240
#define TERMCAP_CARD_CAPTURE		0x220




// AUC (Application Usage Control) bits (9F07)
#define AUC_VALID_DOMESTIC_CASH				0x80
#define AUC_VALID_INTERNATIONAL_CASH 		0x40
#define AUC_VALID_DOMESTIC_GOODS			0x20
#define AUC_VALID_INTERNATIONAL_GOODS 		0x10
#define AUC_VALID_DOMESTIC_SERVICES 		0x08
#define AUC_VALID_INTERNATIONAL_SERVICES 	0x04
#define AUC_VALID_ATMS						0x02
#define AUC_VALID_NONATMS					0x01
#define AUC_ALLOWED_DOMESTIC_CASHBACK		0x180
#define AUC_ALLOWED_INTERNATIONAL_CASHBACK	0x140


// Additional Terminal Capabilities bits (9F40)
#define	ATC_CASH				0x80
#define	ATC_GOODS				0x40
#define	ATC_SERVICES			0x20
#define	ATC_CASHBACK			0x10
#define	ATC_INQUIRY				0x08
#define	ATC_TRANSFER			0x04
#define	ATC_PAYMENT				0x02
#define	ATC_ADMIN				0x01
#define	ATC_NUMERIC_KEYS		0x280
#define	ATC_ALPHABETIC_KEYS		0x240
#define	ATC_COMMAND_KEYS		0x220
#define	ATC_FUNCTION_KEYS		0x210
#define	ATC_PRINT_ATTENDANT		0x380
#define	ATC_PRINT_CARDHOLDER	0x340
#define	ATC_DISPLAY_ATTENDANT	0x320
#define	ATC_DISPLAY_CARDHOLDER	0x310
#define	ATC_CODE_TABLE_10		0x302
#define	ATC_CODE_TABLE_9		0x301
#define	ATC_CODE_TABLE_8		0x480
#define	ATC_CODE_TABLE_7		0x440
#define	ATC_CODE_TABLE_6		0x420
#define	ATC_CODE_TABLE_5		0x410
#define	ATC_CODE_TABLE_4		0x408
#define	ATC_CODE_TABLE_3		0x404
#define	ATC_CODE_TABLE_2		0x402
#define	ATC_CODE_TABLE_1		0x401

// Transaction type codification
#define TRXN_TYPE_SALE  	0x00
#define TRXN_TYPE_CASH      0x01
#define TRXN_TYPE_REFUND    0x20
#define TRXN_TYPE_CASHBACK  0x09

// Transaction Types
#define TRANTYPE_SALE  			0x00
#define	TRANTYPE_CASH			0x01
//#define	TRANTYPE_GOODS			0x01
//#define	TRANTYPE_SERVICES		0x02
#define	TRANTYPE_ATM			0x03
#define	TRANTYPE_CASHBACK		0x09

// CVM Codes
// bit 7
#define  CVM_APLY_SUCCEEDING			0x40
#define  CVM_FAIL_VERIFICATION			0x00
// bit 6-0
#define  CVM_FAIL_CVM					0x00
#define  PLAINTEXT_PIN_ICC				0x01
#define  ENCIPHERED_PIN_ONLINE			0x02
#define  PLAINTEXT_PIN_ICC_SIGNATURE 	0x03
#define  ENCIPHERED_PIN_ICC				0x04
#define  ENCIPHERED_PIN_ICC_SIGNATURE 	0x05
#define  SIGNATURE						0x1E
#define  NO_CVM							0x1F


// Data Sources
#define CARD		'C'
#define ISSUER		'I'
#define TERMINAL	'T'
#define CARD2		'D'

#define MAX_DATA_LEN			512
#define MAX_MATCHING_APP_CNT 	10

#define	MAX_SAD_LEN		  		512

#define MAX_ISS_SCRIPT_CNT   5
#define MAX_ISS_SCRIPT_LEN   128

// Data formats
/*#define	BIN		0	// Binary
#define	AN		1	// Alphanumeric
#define	ANS		2	// Alphanumeric Special
#define	N		3	// Numeric
#define	CN		4	// Compressed Numeric
*/


/* VERIFY								*/
/* QUALIFIERS						*/
#define PLAINTEXT_PIN		0x80
#define ENCHIPERED_PIN		0x88

#define MIN_PIN_LEN		4
#define MAX_PIN_LEN		12

// GENERATE AC Cryptogram Information Types
#define	AAC			0x00
#define	TC			0x40
#define	ARQC			0x80
#define	AAR			0xC0
#define	SERVICE_NOT_ALLOWED	0x01
#define	PIN_TRY_LIMIT_EXCEEDED	0x02 // EVAL1.6 





// GET DATA Parameters
#define GET_PIN_TRY_COUNTER	0
#define GET_ATC			1
#define GET_LAST_ONL_ATC	2


#define HASH_DATA_MODULO_LEN	512
#define PUB_KEY_MODULO_LEN	256
#define MAX_DOL_LEN		512

#define NOT_PRESENT		0x000000FF
#define MAX_TERMINAL_APP_CNT 	3


typedef struct
{
    uchar   ucRID[5];
    uchar   ucPKI;
    uchar   ucPKSerial[3];
}REVOC_TABLE;

    
typedef struct
{
	uchar ucDirEntries[128];
	uchar ucDirEntriesLen;
	uchar ucSFI;
	uchar ucRecNo;
	uchar ucIndex;
}STACK;

typedef struct
{
	char ucCurStr[10];
	char ucCurCode[5];
}CURRENCY2;


typedef struct
{
	unsigned char	CLA;
	unsigned char	INS;
	unsigned char	P1;
	unsigned char	P2;
	unsigned char	Lc;
	unsigned char	send_data[MAX_DATA_LEN];
	unsigned char	Le;
	unsigned char	read_data[MAX_DATA_LEN];
	int		        read_len;
	unsigned char	SW1;
	unsigned char	SW2;
}T0_APDU;


typedef struct
{
	unsigned char	Descriptor;
	unsigned char	Id[2];
	unsigned char	Attr;
}FILES;

typedef struct

{
	unsigned char	SFI;
	unsigned char	First_Record;
	unsigned char	Last_Record;
	unsigned char	Offline_Record;
}FILES_ON_CARD;


typedef struct
{
	uchar	Tag[2];
	uchar	*Address;
	char  	Requirement;		// 'C' : Conditional
							// 'M' : Mandatory
							// 'R' : Required
							// 'O' : Optional
	uchar	ucFormat;		// N: Numeric
							// CN: Compressed Numeric
							// AN : Alphanumeric
							// ANS: Alphanumeric Special
							// BIN: Binary
	uchar	ucSource;		// Card : 'C'
							// Terminal : 'T'
							// Issuer : 'I'
}TAG_ADDRESS;


typedef struct
{
// Terminal Tags
	uchar	t5F2A[64+3];
	uchar	t5F36[1  +3];
	uchar	t81[4  +3];
	uchar	t8A[2  +3];
	uchar	t95[5  +3];
	uchar	t98[20 +3];
	uchar	t99[64+3];
	uchar	t9A[3  +3];
	uchar	t9B[2  +3];
	uchar	t9C[1  +3];
	uchar	t9F01[11 +3];
	uchar	t9F02[6  +3];
	uchar	t9F03[6  +3];
	uchar	t9F04[4  +3];
	uchar	t9F06[16 +3];
	uchar	t9F09[2  +3];
	uchar	t9F15[2  +3];
	uchar	t9F16[15 +3];
	uchar	t9F1A[2  +3];
	uchar	t9F1B[4  +3];
	uchar	t9F1C[8  +3];
	uchar	t9F1D[8  +3];
	uchar	t9F1E[8  +3];
	uchar	t9F21[3  +3];
	uchar	t9F22[1  +3];
	uchar	t9F33[3  +3];
	uchar	t9F34[3  +3];
	uchar	t9F35[1  +3];
	uchar	t9F37[4  +3];
	uchar	t9F39[1  +3];
	uchar	t9F3A[4  +3];
	uchar	t9F3C[2  +3];
	uchar	t9F3D[1  +3];
	uchar	t9F40[5  +3];
	uchar	t9F41[4  +3];
// Terminal proprietary tags
	uchar	tDF81[1+3];  // ByPass PIN	T: DF80, L:1, V:1,0, Type : Binary
	uchar	tDF83[5+3];  // TAC-Default
	uchar	tDF84[5+3];  // TAC-Denial
	uchar	tDF85[5+3];  // TAC-Online
	uchar	tDF87[5+3];  // Threshold Value for Biased Random Selection
	uchar	tDF88[256+3]; // Target Percentage For Random Transaction Selection
	uchar	tDF89[64+3]; // Maksimum Target Percentage For Random Transaction Selection
	uchar	tDF90[1+3];	 // Trace
	uchar	tDF91[1+3];  // Merchant forces transaction online
// Issuer Script Tags
	uchar	tDF92[128+3]; // Issuer Script Results
	uchar	tDF95[32+3]; // Default DDOL
        uchar	tDF98[32+3]; // Default TDOL
        uchar   tDFA0[256+3]; // Online DOL
}EMV_TERM_TAGS;


typedef struct
{
// Card Tags
	uchar	t4F[16 +3];
	uchar	t50[16 +3];
	uchar	t57[19+3];
	uchar	t5A[10+3];
	uchar	t5D[16+3];
	uchar	t5F20[26 +3];
	uchar	t5F24[3  +3];
	uchar	t5F25[3  +3];
	uchar	t5F28[2  +3];
	uchar	t5F2D[8  +3];
	uchar	t5F30[2  +3];
	uchar	t5F34[1  +3];
	uchar	t6F[252+3];
	uchar	t71[MAX_ISSUER_SCRIPT_LEN+3];
	uchar	t72[MAX_ISSUER_SCRIPT_LEN+3];
	uchar	t73[32];
	uchar	t82[2  +3];
	uchar	t84[16 +3];
	uchar	t87[1  +3];
	uchar	t88[1  +3];
	uchar	t8C[252+3];
	uchar	t8D[252+3];
	uchar	t8E[252+3];
	uchar	t8F[1  +3];
	uchar	t90[MAX_MODULUS_LEN+3];
	uchar	t91[16 +3];
	uchar	t92[MAX_MODULUS_LEN +3+ 36];
	uchar	t93[MAX_MODULUS_LEN+3];
	uchar	t94[252+3];
	uchar	t97[252+3];
	uchar	t9F05[32 +3];
	uchar	t9F07[2  +3];
	uchar	t9F08[2  +3];
	uchar	t9F0B[45 +3];
	uchar	t9F0D[5  +3];
	uchar	t9F0E[5  +3];
	uchar	t9F0F[5  +3];
	uchar	t9F10[32+3];
	uchar	t9F11[1  +3];
	uchar	t9F12[16 +3];
	uchar	t9F13[2  +3];
	uchar	t9F14[1  +3];
	uchar	t9F17[1  +3];
	uchar	t9F19[252+3];
	uchar	t9F1F[256+3];
	uchar	t9F20[256+3];
	uchar	t9F23[1  +3];
	uchar	t9F26[8  +3];
	uchar	t9F27[1  +3];
	uchar	t9F2D[MAX_MODULUS_LEN+3];
	uchar	t9F2E[3+3];
	uchar	t9F2F[MAX_MODULUS_LEN +3+ 42];
	uchar	t9F30[2  +3];
	uchar	t9F32[3+3];
	uchar	t9F36[2  +3];
	uchar	t9F38[MAX_PDOL_LEN+3];
	uchar	t9F3B[2 +3];				// Application Reference Currency
	uchar	t9F43[1 +3];				// Application Reference Currency Exponent
	uchar	t9F42[2 +3];
	uchar	t9F44[1  +3];
	uchar	t9F45[2  +3];
	uchar	t9F46[MAX_MODULUS_LEN+3];
	uchar	t9F47[3+3];
	uchar	t9F48[MAX_MODULUS_LEN +3+ 42];
	uchar	t9F49[252+3];
	uchar	t9F4A[MAX_SDA_TAG_LIST_LEN+3];
	uchar	t9F4B[MAX_MODULUS_LEN+3];
	uchar	t9F4C[8  +3];
	uchar	t9F51[2  +3];
	uchar	t9F52[2  +3];
	uchar	t9F53[1  +3];
	uchar	t9F54[6  +3];
	uchar	t9F55[1  +3];
	uchar	t9F56[1  +3];
	uchar	t9F57[2  +3];
	uchar	t9F58[1  +3];
	uchar	t9F59[1  +3];
	uchar	t9F72[1  +3];
	uchar	t9F73[4  +3];
	uchar	t9F75[6  +3];
	uchar	t9F76[2  +3];
	uchar	t9F7F[42 +3];
	uchar	tBF0C[222+3];
}EMV_CARD_TAGS;



typedef struct
{
	char * pcText; 	// item text
	uchar ucVal;		// item index
} CHIPMENU;


typedef struct
{
	uchar p9F06[16];
	int	   l9F06;
// DF Name
	uchar p84[16];
	int	   l84;
// Application Id
	uchar p4F[16];
	int	   l4F;
// Application Label
	char p50[16];
	int	   l50;
// Application Priority Indicator
        uchar l87;
	uchar p87;
// PDOL
	uchar p9F38[32];
	int	   l9F38;
// Language Preference
	uchar p5F2D[8];
	int	   l5F2D;
// Issuer Code Table Index
	uchar p9F11;
// Application Preffered Name
	char p9F12[16];
	int	   l9F12;
// FCI Issuer Discreationary Data
	uchar pBF0C[222];
	int	   lBF0C;
	int	  TermParamIndex;
	int	  Deleted;
}SELECT_RESPONSE;


typedef struct
{
	uchar	ucRid[5];
	uchar	ucPKExp[3];
	uchar	ucPKExpLen;		//1 or 3
	uchar	ucPKModulo[256];
	uchar	ucPKModuloLen;
	uchar	ucPKIndex;
}CAKEYS;


typedef struct
{
	char pDFA0[32]; // Enter PIN Msg
	char pDFA1[32]; // Enter Amount Msg
	char pDFA2[32]; // PIN OK Msg
	char pDFA3[32]; // PIN NOK Msg
	char pDFA4[32]; // Last PIN Try Msg
	char pDFA5[32]; // Transaction Declined Msg
	char pDFA6[32]; // Transaction Online Msg
	char pDFA7[32]; // Transaction Approved Msg
	char pDFA8[32]; // The List Of Applications Msg
	char pDFA9[32]; // Transaction Terminated Msg
	char pDFB0[32]; // Enter PIN Again Msg
	char pDFB1[32]; // Application Not Accepted Msg
	char pDFB2[32]; // Call Your Bank Msg
	char pDFB3[32]; // Insert Card
	char pDFB4[32]; // Remove Card
	char pDFB5[32]; // Amount OK ?
	char pDFB6[32]; // Card Error
	char pDFB7[32]; // Please Wait
	char pDFB8[32]; // Use Chip Reader
	char pDFB9[32]; // Use Mag Stripe
}TERMINAL_PARAMS;

/*********************/



// DEVICE use for displaying (PinPad, Terminal)
// a bit to '1' indicates that the option is enabled
// Displays on the PinPad          (bit 0: 0000 0001)
#define PPAD            0x01
// Displays on the Terminal        (bit 1: 0000 0010)

#define TERM            0x02
// Displays on the two peripherals (bit0 & bit 1: 0000 0011)
#define PPAD_TERM			0x03

/****************************************************************
* Structure and type definitions                                *
****************************************************************/
// Alpha Numeric Special
#define ans     uchar
// Alpha Numeric
#define anu     uchar
// Numeric
#define num     uchar
// Compressed Numeric
#define cnu     uchar
// Binary
#define bin     uchar


typedef struct
{
	uchar  lng_aid;               // Lng of the AID
	uchar  appli_id[MAX_APP_LEN];     // AID
#ifdef SELECTEMV
	uchar  no_appli_present[MAX_TERMINAL_APP_CNT];
	uchar  term_priority[MAX_TERMINAL_APP_CNT];
#endif
} tAID_GLOBAL_TABLE;


// Access mode to data elements
enum ACCESS_MODE {
ADE_READ,
ADE_READ_LENGTH,
ADE_WRITE
};


// Data object format
enum FORMAT {
	ANS,					/* AlphaNumeric Special      */
	ANU,					/* AlphaNumeric              */
	NUM,					/* Numeric                   */
	CNU,					/* Compressed Numeric        */
	BIN,					/* Binary                    */
	HEX					/* No specific format (HEXA) */
};

// ACCESS RIGHTS FOR THE DATA
enum ACCESS_RIGHTS {
	NONE,            /* no access authorised */
	READ,            /* access authorised in read mode only */
	WRITE,           /* access authorised in write mode only  */
	R_W              /* access authorised in read and write mode */
};

// ACCESS RESULT
enum ACCESS_REPORT {
	ACCESS_OK,
	ACCESS_VIOLATION,
	NO_LENGTH,
	TAG_NOT_FOUND,
	FORMAT_KO
};

#define _YES	0x31
#define _NO		0x30

//##################################################################################
//##################################################################################
//##################################################################################
//##################################################################################

// MODULE which reads or writes the data
#define GEN             0
#define ASS             1

#ifndef SELECTEMV

// Trace code define to enable VISA trace (for the tests)
#define TRACE_CODE   0xAF2CDFE8

// Flag for Authorisation, from the associated
#define FORCE_AUTO   0x01               // CME 2000.09.08

#define NB_MAX_KEYS             8

// diplay_message function (options byte)
// a bit to '0' indicates that the option is enabled
// clear line 1         (bit 0:  1111 1110)
#define CLR_LINE1          0xFE
// clear line 2         (bit 1:  1111 1101)
#define CLR_LINE2          0xFD
// clear the 2 lines    (bit 0 & bit 1:  1111 1100)
#define CLR_2LINES         0xFC


// wait for a key       (bit 2:  1111 1011)
#define WAIT_KEY           0xFB
// delay                (bit 3:  1111 0111)
#define WAIT_DELAY         0xF7
// wait card removed    (bit 4:  1110 1111)
#define WAIT_CARD_REMOVED  0xEF
// alarm bip            (bit 5:  1101 1111)
#define ALARM_BIP          0xDF


// Number of Maximal PIN digits that can be entered		// AK 010927
#define MAX_PINDIGIT				12									/* AK 010927 */

// Terminal options definition for Generic module
//-----------------------------------------------

// if set means that the amount is already available
#define  TOB_AmountBefore	0x01
// if set means that the Easy Entry cards are managed
#define  TOB_EasyEntry   	0x02
// if set means that the shop keeper may force online transactions
#define  TOB_OnlineForce        0x04
// Amount Confirmation Forced just before PIN entry
#define  TOB_AmountConfirmationForced 0x08

#endif


// Languages
#define TURKISH 	0x00
#define ENGLISH 	0x01
#define LANGUAGE	ENGLISH

// Messages Nos :
enum
{
    EMV_MSG_ENTER_PIN,
    EMV_MSG_ENTER_AMOUNT,
    EMV_MSG_PIN_OK,
    EMV_MSG_PIN_NOK,
    EMV_MSG_PIN_TRY_LIMIT_EXCEEDED,
    EMV_MSG_PIN_LAST_TRY,
    EMV_MSG_REJECTED,
    EMV_MSG_APPROVED,
    EMV_MSG_APPL_LIST,
    EMV_MSG_TRAN_ABORTED,
    EMV_MSG_TRY_AGAIN,
    EMV_MSG_NOT_ACCEPTED,
    EMV_MSG_CALL_YOUR_BANK,
    EMV_MSG_INSERT_CARD,
    EMV_MSG_REMOVE_CARD,
    EMV_MSG_AMOUNT_OK,
    EMV_MSG_CARD_ERROR,
    EMV_MSG_PLEASE_WAIT,
    EMV_MSG_CHIP_READER,
    EMV_MSG_USE,
    EMV_MSG_MAGSTRIPE
};



extern int DEBUGTrace;
extern uchar ApplBuffer[512];
extern CAKEYS cakeys[20];
extern EMV_CARD_TAGS	EMVCardTags;
extern EMV_TERM_TAGS	EMVTermTags;
extern uchar ucIssScriptMsg[MAX_ISS_SCRIPT_LEN*MAX_ISS_SCRIPT_CNT];
extern TAG_ADDRESS TagAddress[256];
extern  uchar	ucStaticAppData[MAX_SAD_LEN];
extern int iStaticAppDataLen;
extern T0_APDU Apdu;
extern SELECT_RESPONSE sCandList[MAX_MATCHING_APP_CNT];

extern uchar ucCAPubKeyMod[PUB_KEY_MODULO_LEN];
extern uchar ucIssPubKeyMod[PUB_KEY_MODULO_LEN];
extern uchar ucICCPubKeyMod[PUB_KEY_MODULO_LEN];
extern uchar ucRecPubKeyMod[PUB_KEY_MODULO_LEN];
extern uchar ucRecoveredData[PUB_KEY_MODULO_LEN];

extern uchar ucICCPINEncPubKeyMod[PUB_KEY_MODULO_LEN];
extern uchar ucPINEncData[PUB_KEY_MODULO_LEN];
extern uchar ucEncryptedPINData[PUB_KEY_MODULO_LEN];

void GetEMVMsg(uchar ucLanguage, uchar ucMsgNo, uchar *ucMsg);

//uchar SelectFromMenu (CHIPMENU *xMenu, uchar *tucTitle, int currItem, int maxItem);






int FillTermParams();
uchar CheckCertSerialNo(uchar *ucRID, uchar *ucSerialNo, uchar ucPKIIndex);


// Utility Functions
uchar 	GetConfigNo(unsigned char *ucConfigNo);
uchar 	PutConfigNo(unsigned char ucConfigNo);
uchar 	BuildTermAIDList(uchar *ucAppList);
int 	FillTermParams();
uchar 	EMVTransaction(uchar ucEMVTranType);
int 	CheckSmartCard();
void 	SetNextDataEl(uchar *ucData, int *iDataIndex);
uchar 	GetIssuerData();
void 	PrintCardTags();
void 	PrintTermTags();
int 	FillCommonParams();
uchar 	GetCardBrand();
void 	PrintTags2();
void 	InitEMVTable();
void 	EMV_Set_Environment(uchar ucPageNo);
uchar 	GetDataElement (ushort usTag, uchar *ucTagValue, ushort *ucLenTag);
uchar 	GetDataLen(ushort usTag, uchar *ucLenOfLen, ushort *usLen);
void 	GetByteNoAndValue(int iDefineValue, uchar *ucValue, int *iByteNo);
void 	printBinary ( uchar *tucBin, int len );
int     PrepOnlineData(uchar *ucOnlineTags, uchar *ucOnlineMsg, int *iOnlineMsgLen);
void 	PrepTDOLData(int iDOL, uchar *pucDOL, uchar *pucDOLData, uchar *ucDOLDataLen);
void 	PrepDOLData(int iDOL, uchar *pucDOL, uchar *pucDOLData, uchar *ucDOLDataLen, uchar ucDOLType);
void 	PrintTags();
uchar 	GetTableIndex(uchar *ucTag);
int 	GetLenOfDataEl(uchar *ucDataEl, uchar *ucLenOfLen);
uchar 	AddToEmvTAGS(uchar *Msg, int MsgLen, char cDataSource);
void 	vPrintMsg (char *zMsgName, uchar const *pucBuf, ushort usLen);
int 	ucDispAppMenu (char *pcTitle, CHIPMENU *pxMenu, uchar ucSize);
void 	CalculateTCHash(uchar *ucTCHash);
uchar 	waitAck ( void );

// Authentication Functions
void  PrepCAKEYS();
uchar PrepStaticTagListData(int *iStaticTagListLen);
uchar RecoverICCPubKeyCert(uchar ucIssPubKeyModLen, uchar *ucICCPubKeyModLen);
uchar RecoverICCPINEncPubKeyCert(uchar ucIssPubKeyModLen, uchar *ucICCPINEncPubKeyModLen);
uchar RecoverPubKeyCert(uchar ucPubKeyType, uchar ucPublicKeyModLen, uchar *ucExp, int iExpLen, uchar ucCertLen, uchar *ucCertValue, uchar *ucIssPubKeyModLen);
uchar VerifyDynamicSign(uchar ucPubKeyModType, uchar ucICCPubKeyModLen, uchar *ucDDOLData, uchar ucDDOLDataLen);
uchar RecoverStaticAppData(uchar ucPubKeyModType, uchar ucIssPubKeyModLen);
uchar VerifyStaticAppData(uchar ucPubKeyModType, uchar ucIssPubKeyModLen, int iCAIndex);
uchar DetermineSDAorDDA(char *pcTypeOfAuth);
uchar PerformDDA();
uchar PerformSDA();
uchar OfflineDataAuth();


uchar PrepCandListPSE(uchar ucAppList[MAX_TERMINAL_APP_CNT][APP_INF_LEN], int iAppCnt, int *iMatchAppCnt);
uchar PrepCandList(uchar ucAppList[MAX_TERMINAL_APP_CNT][APP_INF_LEN], int iAppCnt, int *iMatchAppCnt);
uchar SelectApp(uchar ucAppList[MAX_TERMINAL_APP_CNT][APP_INF_LEN], int iAppCnt);
uchar InitAppProcess(uchar ucTranType);
uchar ReadAppData(void);
uchar ProcessRestrict(void);
uchar CardholderVerify(void);
uchar TerminalRiskMng(void);
uchar TermActionAnalysis(uchar *ucTermDesicion);
uchar TermActionAnalysisDefault(uchar *ucTermDesicion);
uchar CardActionAnalysis(uchar ucTermDesicion, uchar *ucCardDesicion);
uchar OnlineProcessing(uchar *ucOnlineError, uchar *ucTermDesicion);
uchar IssuerScriptProcessing1(void);

uchar IssuerScriptProcessing2(void);
uchar Completion(uchar ucOnlineError, uchar *ucDecision);

uchar EMV_AppSelect(uchar *ucAppListBuf, int iAppCnt, uchar *ucSelectedApp);
uchar EMV_Tran(uchar ucTranType, uchar *ucDecision);
uchar EMV_Complete(uchar isOnlineError, uchar *ucIssuerData, ushort usIssuerDataLen, uchar *ucDecision);


uchar SELECT(unsigned char *pucAppName, unsigned char ucAppLen, uchar MultOccurence, uchar ucSelectType);

uchar EXTERNAL_AUTHENTICATE();
uchar GET_PROCESSING_OPTIONS(uchar *pPDOLData, uchar ucPDOLDataLen);
uchar READ_RECORD(uchar ucSFI, uchar ucRecordNo);
uchar GET_DATA(int iNameOfData);
uchar VERIFY(uchar TypeOfPIN, uchar *ucPINData, uchar ucPINLen);
uchar INTERNAL_AUTHENTICATE(uchar *ucAuthData, uchar iAuthDataLen);
uchar GET_CHALLENGE();
uchar GENERATE_AC(uchar *ucCDOLData, uchar ucCDOLDataLen, uchar ucCryptInfData);
uchar RSAEncrypt(unsigned char ucPubKeyType, uchar PubKeyLen, unsigned char *exp, int expLen, unsigned char *mesaj, uchar mesajLen);

int DeleteTransLogAmount();
int GetTransLogAmount(char *Amount);
int InsertTransLogAmount();

#ifdef __cplusplus
}
#endif


#endif
