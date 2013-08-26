#include "common_functions.h"
#include  <string.h>
#include  <stdio.h>

char* DumpByteArr (const byte *arr, int size)
{
	if (size <= 0 || !arr)
		return 0;
	char *buff = new char [size * 3];
	if (!buff)
		return 0;
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		buff[j++] = getHexChar(arr[i] >> 4);
		buff[j++] = getHexChar((arr[i] & 0x0f));
		buff[j++] = ' ';
	}
	buff[--j] = '\0';
	return buff;
}

bool Hex2ASCII (int Val, char asciiVal[])
{
	byte ch [8];
	int i;
	for (i = 0; i < 8; i++)
	{
		ch[i] = (byte)(Val & 0x0f);
		Val >>= 4;
	}

	asciiVal[0] = '\0';
	i = 7;
	while (i >= 0)
	{
		if (ch[i] != 0)
			break;
		i--;
	}
	int k = 0;
	while (i >= 0)
	{
		asciiVal[k++] = getHexChar(ch[i--]);
	}
	asciiVal[k] = '\0';
	return true;
}

char getHexChar (byte bt)
{
	bt &= 0x0f;
	if ((char)bt >= 0 && (char)bt <= 9)
		return '0' + bt;
	else
		return 'A' + bt - 10;
}

bool getHexDigit(char ch_hex, byte *bt_hex)
{
	if (ch_hex >= '0' && ch_hex <= '9')
		*bt_hex = ch_hex - '0';
	else if (ch_hex >= 'A' && ch_hex <= 'F')
		*bt_hex = ch_hex - 'A' + 10;
	else if (ch_hex >= 'a' && ch_hex <= 'f')
		*bt_hex = ch_hex - 'a' + 10;
	else
		return false;
	return true;
}

char* HexByte2AsciiStr(const byte *hex_val, int hex_len)
{
	if (hex_len <= 0)
		return 0;

	char *str = new char [hex_len * 2 + 1];
	if (!str)
		return 0;
	int j = 0;
	for (int i = 0; i < hex_len; i++)
	{
		str[j++] = getHexChar(hex_val[i] >> 4);
		str[j++] = getHexChar(hex_val[i] & 0x0f);
	}
	str[j] = '\0';
	return str;
}

int AsciiStr2HexByte(const char *ascii_str, int ascii_len, 
					 byte* hex_val, int *hex_len)
{
	byte hex_digit;
	int j = 0;
	int i = 0;

	if (ascii_len > 0)
	{
		if ((ascii_len / 2 + (ascii_len % 2)) > *hex_len)
			return ERR_BAD_ARGUMENT;

		if (ascii_len % 2 != 0)
		{
			if (!getHexDigit(ascii_str[i++], &hex_digit))
				return -1;
			else
			{
				hex_val[j++] = 0x0f & hex_digit;
			}
		}
	}

	for (; i < ascii_len; i++)
	{
		// Get most significant hex digit
		if (!getHexDigit(ascii_str[i++], &hex_digit))
			return -1;
		else
		{
			hex_digit <<= 4;
			hex_val[j] = hex_digit;
		}
		if (i >= ascii_len) // This should never occur
			return -1;

		// Get least significant digit
		if (!getHexDigit(ascii_str[i], &hex_digit))
			return -1;
		else
		{
			hex_val[j++] |= hex_digit;
		}
	}
	*hex_len = j;
	return SUCCESS;
}


int AsciiStrWithSpace2HexByte(const char *ascii_str, int ascii_len, 
					 byte* hex_val, int *hex_len)
{
	byte hex_digit;
	int j = 0;
	int i = 0;

	while(ascii_str[i]==' ')
		i++;
	
	for (; i < ascii_len; i++)
	{
		while(ascii_str[i]==' ')
			i++;
		// Get most significant hex digit
		if (!getHexDigit(ascii_str[i++], &hex_digit))
			return -1;
		else
		{
			hex_digit <<= 4;
			hex_val[j] = hex_digit;
		}
		if (i >= ascii_len) // This should never occur
			return -1;

		// Get least significant digit
		if (!getHexDigit(ascii_str[i], &hex_digit))
			return -1;
		else
		{
			hex_val[j++] |= hex_digit;
		}
	}
	*hex_len = j;
	return SUCCESS;
}



long LongFromByte(const byte *arr, int size)
{
	long lValue = 0;
	for (int i = 0; i < size; i++)
	{
		lValue <<= 8;
		lValue |= (arr[i] & 0x000000FF);
	}
	return lValue;
}

int ByteFromLong(long lVal, byte *arr, int size)
{
	if (size != 4)
		return ERR_BAD_ARGUMENT;

	for (int i = size - 1; i >= 0; i--)
	{
		arr[i] = (byte)(lVal & 0x000000FF);
		lVal >>= 8;
	}
	return SUCCESS;
}

int convertYear2to4 (int year2dig)
{
	// This conversion is in accordance with EMV specification 
	// See book 4, section 7.4.3
	int year4dig = year2dig;
	if (year2dig >= 0 && year2dig <= 49)
		year4dig += 2000;
	else if (year2dig >= 50 && year2dig <= 99)
		year4dig += 1900;
	else
		year4dig = 0; // Should never happen
	return year4dig;
}

bool DateStruct2EMVDate(byte byteDate[], DateStruct &dsDate)
{
	// --------------------------------------------------------------------
	// EMV date is specified in the following format:
	// n6: YYMMDD
	// It is a three byte array, where each byte represents YY, MM, and DD.
	// Example: 021215
	// 1st byte is 0x02 - 2002 year
	// 2nd byte: 0x12 - 12th month, December (note, that in decimal it is 18!!!)
	// 3rd byte: 0x15 - 15th (note, that in decimal it is 21)
	// -----------------------------------------------------------------------

	// Convert year
	if (!decimal2NumericByte (dsDate.YY, byteDate))
		return false;
	// Convert month
	if (!decimal2NumericByte (dsDate.MN, byteDate + 1))
		return false;
	// Convert Day
	if (!decimal2NumericByte (dsDate.DD, byteDate + 2))
		return false;
	return true;
}

bool DateStruct2EMVTime(byte byteTime[], DateStruct &dsTime)
{
	// --------------------------------------------------------------------
	// EMV time is specified in the following format:
	// n6: HHMMSS
	// It is a three byte array, where each byte represents HH, MM, and SS.
	// Example: 061255
	// 1st byte: 0x06 is 6 Hours
	// 2nd byte: 0x12 - 12 minutes
	// 3rd byte: 0x55 - 55 seconds
	// -----------------------------------------------------------------------

	// Convert year
	if (!decimal2NumericByte (dsTime.HH, byteTime))
		return false;
	// Convert month
	if (!decimal2NumericByte (dsTime.MM, byteTime + 1))
		return false;
	// Convert Day
	if (!decimal2NumericByte (dsTime.SS, byteTime + 2))
		return false;
	return true;
}

// Numeric byte is confirmed with numeric data type in EMV.
// 4 most significant bits represent one decimal digit, and 4 least significant
// bits represent another decimal digit.
// Therefore a numeric byte could represent the decimal numbers in a range
// from 0 to 99.
// Decimal 33. for example, will be represented by 0x33 as numeric byte.
// (note that 0x33 in decimal is 51).
bool decimal2NumericByte (byte DecimalVal, byte *NumericByte)
{
	int val = 0x000000FF & DecimalVal;
	if (val < 10)
		NumericByte[0] = DecimalVal;
	else if (val >= 10 && val <= 99)
	{
		int dec = val / 10;
		NumericByte[0] = (byte)((dec) << 4);
		NumericByte[0] |= (byte)(val - dec * 10);
	}
	else
		return false;
	return true;
}

int asci2NumericByte (const char *asciStr, byte byteVal[], int size)
{
	int str_size = (int)strlen(asciStr);
	if (str_size / 2 != size)
		return ERR_BAD_ARGUMENT;

	int i = 0;
	for (int j = 0; j < size; j++)
	{
		if (asciStr[i] >= '0' && asciStr[i] <= '9')
		{
			byteVal[j] = asciStr[i] - '0';
			byteVal[j] <<= 4;

			i++;
			if (asciStr[i] >= '0' && asciStr[i] <= '9')
			{
				byteVal[j] |= ((asciStr[i] - '0') & 0x0f);
				i++;
			}
			else
				return ERR_BAD_ARGUMENT;
		}
		else
			return ERR_BAD_ARGUMENT;
	}
	return SUCCESS;
}

// Converts a byte containing a value in a numeric format to a corresponding
// decimal value.
// A byte in a numeric format can only have its most and least significant nimbles
// to be in a range from 0 to 9 (digital numbers).
// Function returns true if conversion succeeded, and false if an invalid digit is 
// encountered
bool numericByte2decimal(byte numeric, int *decimal)
{
	int left_digit = (numeric >> 4) & 0x0000000f;
	if (left_digit > 9)
		return false;

	left_digit *= 10;
	int right_digit = numeric & 0x0000000f;
	if (right_digit > 9)
		return false;

	*decimal = left_digit + right_digit;
	return true;
}


// Creates a binary Amount corresponding to a format specified for 'Transaction
// Amount' Data element (see EMV book 3, Annex A).
// Created amount is in 4th parameter -- numAmount.
// Input to this function:
// chAmount - ascii string containing a number (e.g. dollars) of the amount,
//			where each character represents a number.
// chAmountExp - ascii string containing a number (e.g. cents) of the minor 
//          part of the account
// cur_exp - the number of digits in minor part of the account (must be < 12)
// numAmount -- a six byte array containing an account formated as specified
//			in EMV specification (n12)
// Returns true if conversion is successful and false otherwise
bool asciAmount2numeric (const char *chAmount, const char *chAmountExp,
						 byte cur_exp, byte *numAmount)
{
	// Initialize Amount to 0;
	memset (numAmount, 0, 6);

	// Get the value of amount exponent (number of digits in exponent (e.g. in cents
	// if US dollars are used)
	int cent_digits = (0x0000000f & cur_exp);
	int dollar_size = 12 - cent_digits;
	int amount_size = (int)strlen (chAmount);
	int cent_size = (int)strlen(chAmountExp);

	if (amount_size > dollar_size ||
		cent_size > cent_digits ||
		cent_digits + dollar_size > 12)
		return false;

	int bt_sz = 5;

	// Write cents
	if (cent_size > 0)
	{
		for (int i = cent_size - 1; i >= 0; i--, bt_sz--)
		{
			if (bt_sz < 0)
				break;
			if (chAmountExp[i] >= '0' && chAmountExp[i] <= '9')
			{
				numAmount[bt_sz] = chAmountExp[i] - '0';
				i--;
				if (i < 0)
					break;
				if (chAmountExp[i] >= '0' && chAmountExp[i] <= '9')
					numAmount[bt_sz] |= (((chAmountExp[i] - '0') << 4) & 0xf0);
				else
					return false;
			}
			else
				return false;
		}
	}
	

	// Write dollars
	int start_indx = amount_size - 1;
	bt_sz = 5 - cent_digits / 2;
	if (amount_size > 0)
	{
		if (cent_digits % 2 != 0)
		{
			if (chAmount[start_indx] >= '0' && chAmount[start_indx] <= '9')
			{
				byte val = chAmount[start_indx] - '0';
				val <<= 4;
				numAmount[bt_sz] |= val;
				start_indx--;
				bt_sz--;
			}
			else
				return false;
		}

		for (int i = start_indx; i >= 0; i--, bt_sz--)
		{
			if (bt_sz < 0)
				break;
			if (chAmount[i] >= '0' && chAmount[i] <= '9')
			{
				numAmount[bt_sz] = chAmount[i] - '0';
				i--;
				if (i < 0)
					break;
				if (chAmount[i] >= '0' && chAmount[i] <= '9')
					numAmount[bt_sz] |= (((chAmount[i] - '0') << 4) & 0xf0);
				else
					return false;
			}
			else
				return false;
		}
	}
	return true;
} 


int numeric2asciAmount(char *chAmount, char *chAmountExp,
						 byte cur_exp, const byte *numAmount)
{
	// Get the value of amount exponent (number of digits in exponent (e.g. in cents
	// if US dollars are used)
	int cent_digits = cur_exp & 0x0000000f;
	if (cent_digits > 12)
		return ERR_INVALID_AMOUNT;

	int i = 0;
	int k = 0;
	int amount_digits = 12 - cent_digits;
	int running_digits = 0;
	bool leading0 = true;
	bool oddByte = false;
	byte tempDig;
	// Write Amount
	while (running_digits < amount_digits && i < 6)
	{
		tempDig = (numAmount[i] >> 4) & 0x0f;
		if (tempDig != 0)
		{
			leading0 = false;
			chAmount[k] = '0' + tempDig;
			k++;
		}
		else
		{
			if (!leading0)
			{
				chAmount[k] = '0';
				k++;
			}
		}
		running_digits++;
		if (running_digits >= amount_digits)
		{
			oddByte = true;
			break;
		}

		tempDig = numAmount[i] & 0x0f;
		if (tempDig != 0)
		{
			leading0 = false;
			chAmount[k] = '0' + tempDig;
			k++;
		}
		else
		{
			if (!leading0)
			{
				chAmount[k] = '0';
				k++;
			}
		}
		running_digits++;
		i++;
	}
	chAmount[k] = '\0';

	// Write cents;
	k = 0;
	if (i < 6 && oddByte)
	{
		tempDig = numAmount[i] & 0x0f;
		chAmountExp[k] = '0' + tempDig;
		k++;
		i++;
		running_digits = 1;
	}
	else
		running_digits = 0;
	
	while (running_digits < cent_digits && i < 6)
	{
		tempDig = (numAmount[i] >> 4) & 0x0f;
		chAmountExp[k] = '0' + tempDig;
		k++;
		running_digits++;
		if (running_digits >= cent_digits)
			break;

		tempDig = numAmount[i] & 0x0f;
		chAmountExp[k] = '0' + tempDig;
		k++;
		running_digits++;
		i++;
	}
	chAmountExp[k] = '\0';
	return SUCCESS;
}

bool binaryAmount2Numeric (int Amount, byte numAmount[], int size)
{
	// Convert an integer to a character (ascii) string
	char asciAmount[35];
	//_itoa(Amount, asciAmount, 10);  -- substituded to snprintf() in following line --NT
	snprintf(asciAmount, 35, "%d",Amount);
	int asciSize = (int)strlen(asciAmount);
	if (asciSize <= 0)
		return false;
	if (asciAmount[0] == '-')
		return false;

	int res = asciStr2HexString (asciAmount, (UNINT)asciSize,
					   numAmount, (UNINT) size,
					   0x00, false);
	if (res == SUCCESS)
		return true;
	else
		return false;
}

int Add2numAmounts (byte *Amount1, const byte *Amount2)
{
	int val1;
	int val2;
	int exp = 0;
	for (int i = 5; i >= 0; i--)
	{
		val1 = Amount1[i] & 0x0000000f;
		val2 = Amount2[i] & 0x0000000f;
		if (val1 > 10 || val2 > 10)
			return ERR_INVALID_AMOUNT;
		val1 += (val2 + exp);
		if (val1 >= 10)
		{
			val1 -= 10;
			exp = 1;
		}
		else
			exp = 0;
		
		Amount1[i] &= 0xf0;
		Amount1[i] |= (byte)val1;

		val1 = (Amount1[i] >> 4) & 0x0000000f;
		val2 = (Amount2[i] >> 4) & 0x0000000f;
		if (val1 > 10 || val2 > 10)
			return ERR_INVALID_AMOUNT;
		val1 += (val2 + exp);
		if (val1 >= 10)
		{
			val1 -= 10;
			exp = 1;
		}
		else
			exp = 0;
		val1 <<= 4;
		Amount1[i] &= 0x0f;
		Amount1[i] |= (byte)val1;
	}
	if (exp == 1)
	{
		// Amount overflow
		return ERR_AMOUNT_OVERFLOW;
	}
	return SUCCESS;
}

int Numeric2Double(const byte *num_data, UNINT num_len, double *dbl_data)
{
	if (!num_data || num_len == 0)
		return ERR_BAD_ARGUMENT;

	int char_size = num_len * 2;
	char *char_data = new char [char_size + 1];
	if (!char_data)
		return ERR_MEMORY_ALLOC;

	byte num_val;
	for (UNINT j = 0, i = 0; j < num_len; j++)
	{
		num_val = (num_data[j] >> 4) & 0x0f;
		if (num_val > 9)
		{
			delete [] char_data;
			return ERR_BAD_ARGUMENT;
		}
		char_data[i++] = num_val + '0';

		num_val = num_data[j] & 0x0f;
		if (num_val > 9)
		{
			delete [] char_data;
			return ERR_BAD_ARGUMENT;
		}
		char_data[i++] = num_val + '0';
	}
	char_data[char_size] = '\0';
	*dbl_data = atof(char_data);
	delete [] char_data;

	return SUCCESS;
}

// Converts a date from EMV format (YYMMDD) to dateStruct.
// EMV format is a byte array of length 3, where each byte is in a numeric format.
// Thus, a first byte is a year. The value 0x99 represents year 99 (note that 
// hexadecimal number 0x99 is equal to 153 decimal)
// While converting to a dateStruct format the rule specified in EMV book 4, section
// 2.7.3. Years in a range from 0 to 49 are considered to be 2000's, while years
// in a range from 50 to 99 are considerd to be 1900's
bool EmvDate2DateStruct(byte emv_date[], int len, dateStruct *date)
{
	int year;
	int month;
	int day;
	if (len != 3)
		return false;
	if (!numericByte2decimal(emv_date[0], &year))
		return false;
	if (year >= 0 && year <= 49)
		date->CC = 20; // hundreds field
	else if (year >= 50 && year <= 99)
		date->CC = 19;
	else
		return false;
	date->YY = year;

	if (!numericByte2decimal(emv_date[1], &month))
		return false;

	if (month > 0 && month <= 12)
		date->MN = month;
	else
		return false;

	if (!numericByte2decimal(emv_date[2], &day))
		return false;
	if (day > 0 && day <= 31)
		date->DD = day;
	else
		return false;
	
	return true;
}

int compareDates (dateStruct *beforeDate, dateStruct *afterDate)
{
	if (beforeDate->CC < afterDate->CC) // Compare hundred's of years
		return 1;
	else if (beforeDate->CC > afterDate->CC)
		return -1;
	else // (beforeDate->CC == afterDate->CC)
	{
		if (beforeDate->YY < afterDate->YY) // compare ten's of years
			return 1;
		else if (beforeDate->YY > afterDate->YY)
			return -1;
		else // (beforeDate->YY == afterDate->YY)
		{
			if (beforeDate->MN < afterDate->MN)  // compare months
				return 1;
			else if (beforeDate->MN > afterDate->MN)
				return -1;
			else // (beforeDate->MN == afterDate->MN)
			{
				if (beforeDate->DD < afterDate->DD) // compare days
					return 1;
				else if (beforeDate->DD > afterDate->DD)
					return -1;
				else // (beforeDate->DD == afterDate->DD)
					return 0; // Dates are identical!!
			}
		}
	}
}

// Compares two byte arrays, byte by byte.
// If lengths of both arrays are not the same, compare is considered to fail
bool CompareByteArr (const byte *val1, unsigned int val1_len,
					 const byte *val2, unsigned int val2_len)
{
	if (val1_len != val2_len)
		return false;
	for (unsigned int i = 0; i < val1_len; i++)
		if (val1[i] != val2[i])
			return false;
	return true;
}

// Converts ASCII string representing some number ('0' through '9' are only 
// valid characters!) to a hexadecimal string where the same number is represented
// in a numeric format (each byte contains two digits from ascii string -- ascii 
// code of a digit is replaced by the binary value of the digit in a range from
// '0000' to '1001').
// If the size of the hexStr buffer is bigger than the size of converted value,
// the extra 4-digit nibbles are filled with the filler (the 5th parameter).
// If left_justify is true, then the value in hexStr is left justified, otherwise
// it is right justified.
int asciStr2HexString (const char *asciStr, UNINT asci_size,
					   byte *hexStr, UNINT hex_size,
					   byte filler, bool left_justify)
{
	UNINT hex_cur;
	UNINT asc_cur;
	UNINT adjust;
	
	int mod = asci_size % 2;
	UNINT hex_req = asci_size / 2 + mod; // required size of hex array to hold converted ascii string

	// Check the size of the array to hold the result
	if (hex_req > hex_size)
		return ERR_BAD_ARGUMENT;

	// initialize buffer with filler character
	init_buffer (hexStr, hex_size, filler);

	asc_cur = 0;
	adjust = 0;
	if (left_justify)
	{
		// If left justified always start with left most digit
		hex_cur = 0;
	}
	else
	{	
		// If right justified, then calculate the start index
		hex_cur = hex_size - hex_req; 
		if (mod == 1)
			adjust = 1;
	}

	// For all characters in asciiStr array
	while (asc_cur < asci_size)
	{
		// Calculate a binary value of the digit represented by asci character code
		byte digit = asciStr[asc_cur] - '0';
		if ((char)digit < 0 || (char)digit > 9)
			return ERR_BAD_ARGUMENT;
		// determine wich 4 bits of a byte to write
		if ((asc_cur + adjust) % 2 == 0)
		{
			// update 4 most significant (left most) bits
			hexStr[hex_cur] = ((digit << 4) & 0xf0) | (hexStr[hex_cur] & 0x0f);
		}
		else
		{
			// update 4 least significant (right most) bits
			hexStr[hex_cur] = digit | (hexStr[hex_cur] & 0xf0);
			hex_cur++;
		}
		asc_cur++; // Go to the next character
	}
	return SUCCESS;
}

void init_buffer (byte *hexStr, UNINT hex_size, byte filler)
{
	for (UNINT i = 0; i < hex_size; i++)
		hexStr[i] = filler;
}





void printHex(byte *hexStr, int len)
{
	for (int i = 0; i < len; i++){
		printf("%.2x ",hexStr[i]);
		if(i%10 == 9)
			printf("\n");
	}
	printf("\n");
}

