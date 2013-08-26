/*
common_functions.h
This file contains the most common functions used across the project. Mostly,
it is conversion functions.
*/
#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include "../Runtime/custom_types.h"
#include "../Runtime/errors.h"
#include <stdlib.h>

// *** DumpByteArr ***
// Returns a byte array converted into hexadecimal reprisentation of the value
// in arr. Each byte is represented by two hexadecimal digits. There is one 
// space character between each byte.
// Important: Memory is allocated inside of this function to a buffer which 
// holds the hexadecimal value. The pointer to this buffer is returned by the
// function. Caller MUST release this memory by calling 'delete' operator.
// Parameters:
//    arr - a byte array with value to convert to hexadecimal represintation;
//	  size - a size of the buffer arr.
// Returns:
//    The buffer holding the hexadecimal value of arr as an ASCI string.
//    NULL (0) - if there is error
char* DumpByteArr (const byte *arr, int size);

// *** getHexChar ***
// Returns an ASCI character representing a hexadecimal digit (0 - 9, A - F) 
// for the 4 least significant bits of a byte.
// Parameters:
//	 bt - the input byte.
// Returns:
//	 an ASCI character representing a hexadecimal digit
char getHexChar (byte bt);

// *** Hex2ASCII ***
// Fills up asciiVal character array with a string where each character is
// hexadecimal representation of corresponding 4 bits in the integer Val.
// Example:
// Val = 87987221 (or 0x053E9415) will be converted to
// asciiVal = "53E9415".
// Parameters:
//		Val - an integer value to be converted to hexadecimal ascii string
//		asciiVal - a character array of size 9. Contains a converted hexadecimal
//		value.
// Returns:
//		'true' if conversion is successful, or 'false' otherwise.
bool Hex2ASCII (int Val, char asciiVal[]);

// *** getHexDigit ***
// Converts a character into hexadecimal digit.
// Parameters:
//		ch_hex - a character to be converted. Must be one of the following:
//				'1', '2', ... '9', 'a', 'b', ... 'f'.
//      bt_hex - a byte four least significant bits of which contain a 
//			hexadecimal value represented by the character in ch_hex.
// Returns:
//	'true' - if conversion is successful, 'false' - otherwise
bool getHexDigit(char ch_hex, byte *bt_hex);

// *** LongFromByte ***
// Converts a byte array into the value of type long
// Parameters:
//		arr - byte array to be converted to a long. Must have a size 
//         not greater then the size of long.
//		size - the size of the arr in bytes.
// Returns:
//		a value of type long which correspond to byte array arr
long LongFromByte(const byte *arr, int size);

// *** ByteFromLong ***
// Converts the value of type long into a byte array.
// Parameters:
//		lVal - a value of type long to be converted into byte array
//		arr - a byte array to receive a converted value from lVal
//		size - size of the array arr. Must be equal to 4.
// Returns:
//		SUCCESS - if conversion succeeds, Error code otherwise.
int ByteFromLong(long lVal, byte *arr, int size);

// *** Numeric2Double ***
// Converts a value stored in byte array in a numeric format (using only
// digits from '0' to '9') to a double.
// Parameters:
//		num_data - input byte array with value in a numeric format,
//		num_len - size of the num_data in bytes,
//		dbl_data - contains converted data (output value).
// Returns:
//		SUCCESS - id conversion succeeds, or Error Code otherwise.
int Numeric2Double(const byte *num_data, UNINT num_len, double *dbl_data);

// *** convertYear2to4 ***
// Converts a year represented with two digits to a year represented by 4 digits.
// Reference: EMV 4.0 book 4, ch 2.7.3 - Data Management:
//  * YY in the range 00-49 inclusive is treated as having the value 20YY,
//  * YY in the range 50-99 inclusive is treated as having the value 19YY.
// Parameters:
//		year2dig - a value represented a 2-digit year.
// Returns:
//		0 - if cannot convert,
//      4-digit year if conversion succeeded.
int convertYear2to4 (int year2dig);

// *** DateStruct2EMVDate ***
// Converts DateStruct date (declared in custom_types.h) to a EMV date (YYMMDD).
// Parameters:
//		byteDate - contains converted date in EMV format, where 
//			1st byte is YY (year), 2nd byte is MM (month), 3rd byte is DD (day).
//		dsDate - Date stored in DateStruct format.
// Returns:
//		true if conversion succeeds, false otherwise.
bool DateStruct2EMVDate(byte byteDate[], DateStruct &dsDate);

// *** DateStruct2EMVTime ***
// Converts DateStruct date (declared in custom_types.h) to a EMV time (HHMMSS).
// Parameters:
//		byteTime - contains converted time in EMV format, where 
//			1st byte is HH (hours), 2nd byte is MM (minutes), 
//			3rd byte is SS (seconds).
//		dsTime - Time stored in DateStruct format.
// Returns:
//		true if conversion succeeds, false otherwise.
bool DateStruct2EMVTime(byte byteTime[], DateStruct &dsTime);

// *** EmvDate2DateStruct ***
// Converts a date from EMV format (YYMMDD) to dateStruct.
// EMV format is a byte array of length 3, where each byte is in a numeric format.
// Thus, a first byte is a year. The value 0x99 represents year 99 (note that 
// hexadecimal number 0x99 is equal to 153 decimal)
// While converting to a dateStruct format the rule specified in EMV book 4, section
// 2.7.3. Years in a range from 0 to 49 are considered to be 2000's, while years
// in a range from 50 to 99 are considerd to be 1900's
// Parameters:
//		emv_date - contains an EMV date to be converted,
//		len - the size of emv_date in bytes (must be 3)
//		dsDate - Converted date stored in DateStruct format.
// Returns:
//		true if conversion succeeds, false otherwise.
bool EmvDate2DateStruct(byte emv_date[], int len, dateStruct *dsDate);

// *** compareDates ***
// Compares two dates.
// Parameters:
//		beforeDate - first Date,
//		afterDate  - second Date.
// Returns:
//	1 - afterDate > beforeDate,
// -1 - afterDate < beforeDate,
//  0 - afterDate == beforeDate.
int compareDates (dateStruct *beforeDate, dateStruct *afterDate);

// *** decimal2NumericByte ***
// Numeric byte is confirmed with numeric data type in EMV.
// 4 most significant bits represent one decimal digit, and 4 least significant
// bits represent another decimal digit.
// Therefore a numeric byte could represent the decimal numbers in a range
// from 0 to 99.
// Decimal 33. for example, will be represented by 0x33 as numeric byte.
// (note that 0x33 in decimal is 51).
// Parameters:
//		DecimalVal - a byte containing a decimal value in the range 0 - 99,
//      NumericVal - a byte which contains a DecimalVal converted to a numeric
//			format.
// Returns:
//		'true' - if conversion succeeded, 'false' - otherwise
bool decimal2NumericByte (byte DecimalVal, byte *NumericVal);

// *** numericByte2decimal ***
// Converts a byte containing a value in a numeric format to a corresponding
// decimal value.
// A byte in a numeric format can only have its most and least significant nimbles
// to be in a range from 0 to 9 (digital numbers).
// Parameters:
//      NumericVal - a byte which contains a value in a numeric format.
//		DecimalVal - a byte containing a decimal value converted from NumericVal
// Returns:
//		'true' - if conversion succeeded, 'false' - otherwise
bool numericByte2decimal(byte NumericVal, int *DecimalVal);

// *** asci2NumericByte ***
// Converts an ASCII string containing a number (e.g. "1234") to a byte array
// of numeric format. In such array each element (byte) contains two digits
// corresponding to two characters from the ASCII string. For example above this
// array will have the following elements: byteVal[0] = 0x12, byteVal[1] = 0x34.
// Parameters:
//		asciStr - an ASCII string containing a number (the only valid characters
//			are from '0' to '9'.
//		byteVal - a byte array with converted numeric value.
// Returns:
//		SUCCESS - if conversion succeeded,
//		Error Code - if conversion failed.
int asci2NumericByte (const char *asciStr, byte byteVal[], int size);

// *** HexByte2AsciiStr ***
// Converts a hexadecimal number stored in a byte array into the ASCII string.
// Important: a buffer containg a character string is allocated inside of 
//   this function. This buffer MUST be released by a caller of this function.
// Parameters:
//		hex_val - a byte array containing a hexadecimal value to be converted,
//		hex_len - a size of the byte array hex_val.
// Returns:
//		A pointer to a character string containg converted number. The memory
//			pointed by this pointer must be released by a caller.
//		0 - if conversion fails.
char* HexByte2AsciiStr(const byte *hex_val, int hex_len);

// *** AsciiStr2HexByte ***
// Converts ASCII string representing a hexadecimal number (valid characters
// '0' - '9', 'a' - 'f', 'A' - 'F') to a byte array where each byte consists 
// of binary code of the two digits represented by two characters in the ascii
// string. Example: ascii string "1231bc" becomes 0x12, 0x31, 0xbc.
// Parameters:
//		ascii_str - an ascii string to be converted.
//		ascii_len - a number of characters to convert
//		hex_val - a byte array containg a converted number,
//		hex_len - a size of the byte array in bytes (number of elements)
// Returns:
//		SUCCESS - if conversion succeeded
//		Error Code - if conversion failed.
int AsciiStr2HexByte(const char *ascii_str, int ascii_len, 
					 byte* hex_val, int *hex_len);

// *** AsciiStr2HexByte ***
// Converts ASCII string representing a hexadecimal number (valid characters
// '0' - '9', 'a' - 'f', 'A' - 'F') to a byte array where each byte consists 
// of binary code of the two digits represented by two characters in the ascii
// string. Example: ascii string "12 31 bc" becomes 0x12, 0x31, 0xbc.
// Parameters:
//		ascii_str - an ascii string to be converted.
//		ascii_len - a number of characters to convert
//		hex_val - a byte array containg a converted number,
//		hex_len - a size of the byte array in bytes (number of elements)
// Returns:
//		SUCCESS - if conversion succeeded
//		Error Code - if conversion failed.
int AsciiStrWithSpace2HexByte(const char *ascii_str, int ascii_len, 
					 byte* hex_val, int *hex_len);
					 
					 
					 
// *** asciStr2HexString *** 
// Converts ASCII string representing some number ('0' through '9' are only 
// valid characters!) to a hexadecimal string where the same number is represented
// in a numeric format (each byte contains two digits from ascii string -- ascii 
// code of a digit is replaced by the binary value of the digit in a range from
// '0000' to '1001').
// If the size of the hexStr buffer is greater than the size of converted value,
// the extra 4-digit nibbles are filled with the filler (the 5th parameter).
// If left_justify is true, then the value in hexStr is left justified, otherwise
// it is right justified.
// Parameters:
//		asciStr - an ascii string to be converted (valid characters '0' - '9')
//		asci_size - a number of characters to convert
//		hexStr - a byte array containg a converted number,
//		hex_size - a size of the byte array in bytes (number of elements)
//		filler - a byte containing a value to be copied into extra bytes of
//			the hexStr, when hex_size is greater than the size of converted
//			data
//		left_justify - justification flag. If it is 'true', then left 
//			justification is used, otherwise right justification is used.
// Returns:
//		SUCCESS - if conversion succeeded
//		Error Code - if conversion failed.
int asciStr2HexString (const char *asciStr, UNINT asci_size,
					   byte *hexStr, UNINT hex_size,
					   byte filler, bool left_justify);

// *** CompareByteArr ***
// Compares two byte arrays, byte by byte.
// If the sizes of both arrays are not the same, comparison is considered to fail.
// Parameters:
//		val1 - the first byte array,
//		val1_len - the size of the first byte array,
//		val2 - the second byte array,
//		val2_len - the size of the second byte array
// Returns:
//		true - if val1 and val2 are identical,
//		false - if val1 and val2 are not identical
bool CompareByteArr (const byte *val1, unsigned int val1_len,
					 const byte *val2, unsigned int val2_len);

// *** asciAmount2numeric ***
// Creates a binary Amount corresponding to a format specified for 'Transaction
// Amount' Data element (see EMV 4.0 book 3, Annex A).
// Created amount is in 4th parameter -- numAmount.
// Parameters:
// chAmount - ascii string containing a number (e.g. dollars) of the amount,
//			where each character represents a number.
// chAmountExp - ascii string containing a number (e.g. cents) of the minor 
//          part of the account
// cur_exp - the number of digits in minor part of the account (must be < 12)
// numAmount -- a six-byte array containing an account formated as specified
//			in EMV specification (n12)
// Returns:
//		'true' if conversion is successful,
//		'false' if conversion failed.
bool asciAmount2numeric (const char *chAmount, const char *chAmountExp,
						 byte cur_exp, byte *numAmount);

// *** numeric2asciAmount ***
// Converts from the amount stored in a numeric format in a byte array to
// two character stings containg the whole part of amount (dollars) and minor
// part of amount (cents).
// The amount in a Numeric format is according to 'Transaction
// Amount' Data element (see EMV 4.0 book 3, Annex A).
// Parameters:
//		chAmount - (out) a character string containing a whole part of the amount
//			(e.g. dollars),
//		chAmountExp - (out) a character string containing a minor part of the amount
//			(e.g. cents),
//		cur_exp - (in) a number of digits in minor part of the amount (e.g. 2 if minor
//			part is in cents),
//		numAmount - (in) a byte array containing an amount in a numeric format.
//			It must have 6 elemens.
// Returns:
//		SUCCESS - if conversion succeeded,
//		Error Code - if conversion failed.
int numeric2asciAmount(char *chAmount, char *chAmountExp,
						 byte cur_exp, const byte *numAmount);

// *** binaryAmount2Numeric ***
// Convert an Amount stored as a binary value in integer to an amount
// stored in a byte array in a numeric format.
// Parameters:
//		Amount - the Amount to be converted. Must be a positve number,
//		numAmount - a byte array which keeps a converted amount in a numeric
//			format.
//		size - number of elements in the byte array numAmount.
// Returns:
//		'true' - if conversion succeeded,
//		'fale' - if conversion failed.
bool binaryAmount2Numeric (int Amount, byte numAmount[], int size);

// *** Add2numAmounts ***
// Adds two Amounts stored in a numeric format and saves the result in the 
// first parameter.
// Parameters:
//		Amount1 - a byte array of six elements which holds the first Amount, and
//			after calculation is complete it holds the result of calculation,
//		Amount2 - a byte array of six elements which holds the second Amount.
// Returns:
//		SUCCESS - if addition completed successfully,
//		ERR_INVALID_AMOUNT - if any of the input Amounts is invalid
//		ERR_AMOUNT_OVERFLOW - addition resulted in overflow.
int Add2numAmounts (byte *Amount1, const byte *Amount2);


// *** init_buffer ***
// Initializes a byte array hexStr of a size hex_size to have all bytes equal
//	to 'filler'.
// Parameters:
//		hexStr - a buffer to be initialized,
//		hex_size - a size of the buffer,
//		filler - a byte value to be copied to each element of hexStr.
void init_buffer (byte *hexStr, UNINT hex_size, byte filler);


void printHex(byte *hexStr, int len);

#endif

