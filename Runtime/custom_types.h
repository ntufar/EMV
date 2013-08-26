#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#define SCS_TO_INFINITE 0x7fffffff

typedef unsigned char byte;
typedef unsigned int UINT_KEY;
typedef unsigned int UNINT;

typedef struct dateStruct
{
	byte DD; // : day (1 to 31) 
	byte MN; // : month (1 to 12) 
	byte CC; // : hundred of years (19, 20, 21, ...) 
	byte YY; // : year (0 to 99) 
	byte WD; // : day of the week (1 to 7, where 1 is Monday, 7 is Sunday) 
	byte HH; // : hour (0 to 23) 
	byte MM; // : minute (0 to 59) 
	byte SS; // : second (0 to 59) 
} DateStruct;

typedef struct
{
	double Amount;
	int LanguageID;
}INPUT_PARAM;


#define reverse_bits(val) ((val) ^ 0xffffffff)
#define check_bit(val,mask) ((((val) & (mask)) == (mask))? true: false)
#define check_bit_key(val,mask,key) ((((val) & (mask)) == (key))? true: false)
#define set_bit(val,mask) ((val) |= (mask))
#define reset_bit(val,mask) ((val) &= (reverse_bits(mask)))
#define get_bit(val,mask) ((val) & (mask))

#endif

