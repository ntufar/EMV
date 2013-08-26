#include <stdio.h>
#include <string.h>
#include "mp.h"
#include "libcat.h"
//#include "utils.h"
#include "emv.h"

#define XDIGIT 1
#define IDIGIT 1
#define uchar unsigned char
#define MAX(x,y) x>y?x:y
#define MIN(x,y) x<y?x:y

typedef unsigned long int UINT4;

typedef struct {
  UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
  UINT4 buf[4];                                    /* scratch buffer */
  unsigned char in[64];                              /* input buffer */
  unsigned char digest[16];     /* actual digest after MD5Final call */
} MD5_CTX;

typedef union{
	unsigned int x;
	unsigned char b[2];
} CHAR2BYTES;

CHAR2BYTES a;


uchar ucCAPubKeyMod[PUB_KEY_MODULO_LEN];
uchar ucIssPubKeyMod[PUB_KEY_MODULO_LEN];
uchar ucICCPubKeyMod[PUB_KEY_MODULO_LEN];
uchar ucRecPubKeyMod[PUB_KEY_MODULO_LEN];
uchar ucRecoveredData[PUB_KEY_MODULO_LEN];
uchar ucICCPINEncPubKeyMod[PUB_KEY_MODULO_LEN];


int mpDivShort( unsigned char dividend[],
                unsigned char divisor,
                unsigned char quotient[],
                unsigned char remainder[]);
int mpMulShort( unsigned char multiplicand[],
                unsigned char multiplier,
                unsigned char product[]);
unsigned char *mpLeftByteShift( unsigned char x[],
                                unsigned int  s);
int mpSubShort( unsigned char minuend[],
                unsigned char subtrahend,
                unsigned char difference[]);

				
void MD5Init (void);
void MD5Update (MD5_CTX *mdContext, unsigned char *inBuf, unsigned int inLen);
void MD5Final (MD5_CTX *mdContext);

unsigned char pucDum1[XDIGIT],pucDum2[XDIGIT],pucOne[XDIGIT];


/* F, G and H are basic MD5 functions: selection, majority, parity */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) {(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }

#define GG(a, b, c, d, x, s, ac) {(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define HH(a, b, c, d, x, s, ac) {(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); (a) = ROTATE_LEFT ((a), (s)); (a) += (b); }
#define II(a, b, c, d, x, s, ac) {(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); (a) = ROTATE_LEFT ((a), (s));(a) += (b); }


void memrev(unsigned char *indata, unsigned char *outdata, int inlen)
{
	int i;

	for (i=0;i<inlen;i++)
		outdata[i] = indata[inlen-i-1];
}



char * strrev(char * string)
{
	char *p;
	int len,i;
	short sRet;

	len = strlen(string);

        /*    sRet = sMemAlloc(len, (char **)&p);
  MGG*/
            p=(unsigned char *)malloc(len);
	for (i=0;i<len;i++)
	{
		p[len-i-1] = string[i];
	}
	p[len] = 0;
	strcpy(string, p);
	return string;
}


#define isEven(x) ((x & 0x01)==0)
#define isOdd(x)  (x & 0x01)

int FindModulus( unsigned char *, unsigned char *, unsigned  char * );
void MD5TestSuite( void );
void MDFile (char *);
void MDTimeTrial( void );

unsigned char pucVersion[]="0.01";


int FastExpMP( unsigned char *pucX, unsigned char *pucY,

			   unsigned char *pucN, unsigned char *pucResult ) {

	static unsigned char pucTemp[XDIGIT];
	int m,n;

	if (mpCompare(pucY,pucOne)==0) {
            mpMod( pucX, pucN, pucResult );
            return 0;
	}

	if ((pucY[0]&1)==0) {
		mpDivShort( pucY,2,pucDum1,pucDum2 );
		FastExpMP( pucX,pucDum1,pucN,pucTemp );
		mpMul( pucTemp,pucTemp,pucDum2 );
		mpMod( pucDum2,pucN,pucResult );
		return(0);
	}
	else {
		mpSubShort( pucY,1,pucDum1 );
		mpDivShort( pucDum1,2,pucDum1,pucDum2 );
		FastExpMP( pucX,pucDum1,pucN,pucTemp );
		mpMul( pucTemp,pucTemp,pucDum2 );
		mpMod( pucDum2,pucN,pucTemp);
		mpMul( pucTemp,pucX,pucDum2 );
		mpMod( pucDum2,pucN,pucResult);
		return(0);
	}
}


void burnfree( unsigned char *pucA, int nSize ) {
// Safe Free, zero memory block before freeing....
	memset( pucA, 0, nSize );
	free ((char *)pucA);
}

void swap( unsigned char *pucX, unsigned char *pucY ) {
	int i;
	unsigned char ucTemp;

	for (i=0; i<IDIGIT; i++) {
		ucTemp=pucX[i];
		pucX[i]=pucY[i];
		pucY[i]=ucTemp;
	}
    ucTemp=0;
}


/*char *fgets(char * pReadData, int iMaxLen, HFILE hFile)
{
	int i=0;
	ulong ReadByte;

	do
	{
		sFileRead (hFile, &pReadData[i], 2, &ReadByte);
		i+=2;
	}while (pReadData[i] != 0x0D);
	return pReadData;
}
*/

uchar RSAEncrypt(unsigned char ucPubKeyType, uchar PubKeyLen, unsigned char *exp, int expLen, unsigned char *mesaj, uchar mesajLen)
{
	static unsigned char pucM[IDIGIT], pucMR[IDIGIT], pucNR[IDIGIT];
	static unsigned char pucN[IDIGIT],  pucR[IDIGIT], pucRR[IDIGIT];
	static unsigned char pucE[IDIGIT];
        short sRet;
	int m,n;

	//memset( pucOne,0,XDIGIT );
	//pucOne[0]=1;

/*vPrintMsg("ucPubKeyType", &ucPubKeyType, 1);
vPrintMsg("PubKeyLen", &PubKeyLen, 1);
vPrintMsg("exp", exp, 3);
vPrintMsg("mesaj", mesaj, mesajLen);*/
	//memset(pucN,0,sizeof(pucN));
	switch (ucPubKeyType)
	{
		case CA_PUBLIC_KEY_MOD:
			memcpy(pucN, ucCAPubKeyMod, PubKeyLen);
			break;
		case ICC_PUBLIC_KEY_MOD:
			memcpy(pucN, ucICCPubKeyMod, PubKeyLen);
			break;
		case ISS_PUBLIC_KEY_MOD:
			memcpy(pucN, ucIssPubKeyMod, PubKeyLen);
			break;
		case ICC_PIN_ENC_PUBLIC_KEY_MOD:
			memcpy(pucN, ucICCPINEncPubKeyMod, PubKeyLen);
			break;
	}

//vPrintMsg("pucN", pucN, PubKeyLen);
	memset(pucE,0,sizeof(pucE));
	memcpy(pucE, exp, expLen);
	memset(pucM,0,sizeof(pucM));
	memcpy(pucM, mesaj, mesajLen);
	memset(pucNR,0,sizeof(pucNR));
	memset(pucMR,0,sizeof(pucMR));
	memset(pucRR,0,sizeof(pucRR));
	memrev(pucM, pucMR, mesajLen);
	memrev(pucN, pucNR, PubKeyLen);
	FastExpMP( pucMR,pucE,pucNR,pucR );
	memrev(pucR, pucRR, PubKeyLen);

	memcpy(ucRecoveredData, pucRR, PubKeyLen);
//vPrintMsg("ucRecoveredData", ucRecoveredData, PubKeyLen);

	return TRUE;

}

/*
int RSADecrypt(void)

{
	static unsigned char *pucS, *pucM;
	static unsigned char *pucN,  *pucR;
	static unsigned char *pucE;
	static unsigned char pucFii[1024];
	SHORT sRet;
	CHAR str[1024];
     HFILE fpi,fpo;
	int i,j,nBlockSize,nModulusSize;

//	printf("Verisoft RSA Library %s (c) RSA Decryption Executing.\n",pucVersion );
	memset( pucOne,0,XDIGIT );
	pucOne[0]=1;
	memset(pucDum1,0,XDIGIT);
	memset(pucDum2,0,XDIGIT);


	sRet = sMemAlloc(ADIGIT, (char **)&pucS);
	if (sRet != ERR_NONE)
		return FALSE;

	sRet = sMemAlloc(XDIGIT, (char **)&pucM);
	if (sRet != ERR_NONE)
		return FALSE;

	sRet = sMemAlloc(XDIGIT, (char **)&pucN);
	if (sRet != ERR_NONE)
		return FALSE;

	sRet = sMemAlloc(XDIGIT, (char **)&pucE);
	if (sRet != ERR_NONE)
		return FALSE;

	sRet = sMemAlloc(XDIGIT, (char **)&pucR);
	if (sRet != ERR_NONE)
		return FALSE;


	if (sFileOpen ("private.key", FILE_READ, &fpi) == ERR_NONE)
	{
	// Read key values
//		printf("Reading Private Keys\n");

		fgets((char *)pucS,ADIGIT,fpi);
		PackASCIINumber((char *)pucS);
		nBlockSize=atoi((char *)pucS);

		fgets((char *)pucS,ADIGIT,fpi);
		PackASCIINumber((char *)pucS);
		ConvertASCIItoMP( pucN, pucS );
		nModulusSize=strlen((char *)pucS );

//		printf("Modulus Size:%d decimal digits.\n",nModulusSize);

		fgets((char *)pucS,ADIGIT,fpi); // ignore
		fgets((char *)pucS,ADIGIT,fpi);
		PackASCIINumber((char *)pucS);

		ConvertASCIItoMP( pucE, pucS );
//		printf("Public Key succesfully read.\n");
		sFileClose (fpi);
	}

	// Run the RSA procedure M^e mod n
if (sFileOpen ("gmesaj.txt", FILE_READ, &fpi) == ERR_NONE)
{
//	printf("Input file opened.\n");
	if (sFileOpen ("amesaj.txt", FILE_WRITE, &fpo) == ERR_NONE)
	{
//		printf("Output file opened.\n");
//		MDFile("gmesaj.txt");
			while ( fgets( (char *)pucFii, sizeof(pucFii), fpi )!=NULL )
				for ( i=0; i<(int)strlen((char *)pucFii); i+=nModulusSize ) {
					memset(pucDum1,0,sizeof(pucDum1));
					strncpy((char *)pucDum1,(char *)pucFii+i,nModulusSize);
					if (!isdigit(pucDum1[0])) continue;
//					printf("Encrypted Block:\n[%s]\nDecrytpted Block:\n",pucDum1);
					ConvertASCIItoMP( pucM,pucDum1);
					FastExpMP( pucM,pucE,pucN,pucR );
					ConvertMPtoASCII( pucS,pucR );
					for (j=strlen((char *)pucS); j<nBlockSize; j++ )
						sFileWrite (fpo, "0",1);
					sprintf(str,"%s",pucS);
					sFileWrite (fpo, str, strlen(str));
//					printf("[%s]\n",pucS);
				}
			sFileClose (fpo);
			sFileClose (fpi);

//    MDFile("amesaj.txt");
//	printf("Verisoft RSA Library %s (c) RSA Decryption Done.\n",pucVersion );
	}
}

// Make sure nothing remains in memory
	burnfree(pucS ,ADIGIT);
	burnfree(pucN ,XDIGIT);
	burnfree(pucE ,XDIGIT);
	burnfree(pucM ,XDIGIT);
	burnfree(pucR ,XDIGIT);
	return TRUE;
}
*/
/*
**  test Mersenne numbers for primality using the
**  optimized Lucas test
*/



int MostSignificantDigit( unsigned char x[],
                          unsigned int  m)
{
  if (m)
  {
    m--;
    while (m && (x[m] == 0)) m--;
  }

  return(m);
}


/*
** mpCopy - copy one multiple precision integer to another
**
** return value: *to = base address of 'to' MP integer
*/

unsigned char *mpCopy( unsigned char to[],
                       unsigned char fr[])
{
  memcpy( to, fr, IDIGIT);
  return( to );
}
/*
** ConvertASCIItoMP -- convert from ASCII number string to
**                     a multiple precision integer
**
** return value: base address of MP integer
*/



int mpAddShort( unsigned char augend[],
                unsigned char addend,
                unsigned char sum[])
{
  int i, m;

  m = MostSignificantDigit(augend, IDIGIT);

  sum[0] = a.x = augend[0] + addend;

  for ( i = 1; i <= m; i++)
    sum[i] = a.x = a.b[1] + augend[i];

  if (i < IDIGIT)
    sum[i] = a.x = a.b[1];

  for ( i++; i < IDIGIT; i++) sum[i] = 0;

  return(a.b[1]);
}



/*
** mpAdd      -- add two multiple precision integers
** mpAddShort -- add a short integer to a multiple precision integer
**
** return value: 0 if ok; not 0 if overflow
*/

int mpAdd( unsigned char augend[],
           unsigned char addend[],
           unsigned char sum[])
{
  int i, m;
  unsigned char t[XDIGIT];              /* temporary result */

  if ((m = MostSignificantDigit(addend, IDIGIT)) == 0)
    return( mpAddShort(augend, addend[0], sum));

  m = MAX(m, MostSignificantDigit(augend, IDIGIT));

  memset(t, 0, IDIGIT);                 /* clear sum */

  for ( i = 0, a.x = 0; i <= m; i++)
    t[i] = a.x = a.b[1] + augend[i] + addend[i];

  if (i < IDIGIT)
    t[i] = a.x = a.b[1];

  mpCopy(sum, t);

  return(a.b[1]);
}


/*
** mpAnd - bitwise AND between two multiple precision integers
**
** return value: always 0
*/

int mpAnd( unsigned char and1[],
           unsigned char and2[],
           unsigned char result[])
{
  int i, m;

  m = MAX(MostSignificantDigit(and1, IDIGIT),
          MostSignificantDigit(and2, IDIGIT));

  for ( i = 0; i <= m; i++)
    result[i] = and1[i] & and2[i];

  if (i < IDIGIT)
    result[i] = 0;

  return(0);
}


/*
** mpCompare -- compare one multiple precision integer to another
**
** return value: 1 if x > y
**               0 if x == y
**              -1 if x < y
*/

int mpCompare( unsigned char x[], unsigned char y[])
{
  int m;
  char str[32];

  m = MAX(MostSignificantDigit(x, IDIGIT),
          MostSignificantDigit(y, IDIGIT));

  while (m >= 0)
  {
    if (x[m] > y[m]) return(1);
    if (x[m] < y[m]) return(-1);
    m--;
  }

  return(0);
}

/*
** mpDiv      -- divide two multiple precision integers
** mpDivShort -- divide a multiple precision integer with a short integer
**
** return value: 0 if ok; 1 if division by zero (overflow)
*/

int mpDiv( unsigned char dividend[],
           unsigned char divisor[],
           unsigned char quotient[],
           unsigned char remainder[])
{
  unsigned char u[XDIGIT], v[XDIGIT], w[XDIGIT], d, q;
  int  j, m, n;
  int  st;                               /* status */
  char str[64];

  if ((n = MostSignificantDigit(divisor, IDIGIT)) == 0)
    return( mpDivShort(dividend, divisor[0], quotient, remainder));

  mpCopy(u, dividend);                  /* dividend - do not destroy */
  mpCopy(v, divisor);                   /* divisor  - do not destroy */

  memset( quotient, 0, IDIGIT);         /* clear quotient */
  memset( remainder, 0, IDIGIT);        /* clear remainder */

  if ((st = mpCompare(u, v)) < 0) {
    mpCopy(remainder, u);
    return(0);
  } else if (st == 0) {
    quotient[0] = 1;
    return(0);
  }

  if ((d = 256L / (v[n] + 1)) > 1)      /* normalize */
  {
    mpMulShort(u, d, u);
    mpMulShort(v, d, v);
  }
  n = MostSignificantDigit(v, IDIGIT);
  m = MostSignificantDigit(u, IDIGIT);

  for (j = m - n; j >= 0; j--)
  {
    q = MIN( (u[m] * 256L + u[m-1]) / v[n], 255);
    do
    {
      mpMulShort(v, q, w);
      mpLeftByteShift(w, j);
      if (st = mpSub(u, w, w)) q--;
    } while (st);
    quotient[j] = q;
    if (mpCompare(w, v) < 0) break;
    mpCopy(u, w);
    m = MostSignificantDigit(u, IDIGIT);
  }

  mpDivShort(w, d, remainder, w);

  return(0);
}


int mpDivShort( unsigned char dividend[],
                unsigned char divisor,
                unsigned char quotient[],
                unsigned char remainder[])
{
  int i,m;
  char str[32];

  if (divisor == 0) return(1);

  m = MostSignificantDigit(dividend, IDIGIT);

  for (i = m, a.x = 0; i >= 0; i--)
  {
    a.b[0] = dividend[i];
    quotient[i] = a.x / divisor;
    a.b[1] = a.x % divisor;
  }
  remainder[0] = a.b[1];

  for ( i = 1; i < IDIGIT; i++)
  {
    if (i > m)
      quotient[i] = 0;
    remainder[i] = 0;
  }

  return(0);
}

int mpMulShort( unsigned char multiplicand[],
                unsigned char multiplier,
                unsigned char product[])
{
  int i, m;

  m = MostSignificantDigit(multiplicand, IDIGIT);

  for ( i = 0, a.x = 0; i <= m; i++)
    product[i] = a.x = a.b[1] + multiplicand[i] * multiplier;


  if (i < IDIGIT)
    product[i] = a.x = a.b[1];

  for ( i++; i < IDIGIT; i++) product[i] = 0;

  return(a.b[1]);
}

/*
** mpLeftByteShift - left byte shift a multiple precision integer
** mpLeftBitShift  - left bit shift a multiple precision integer
**
** input:        x[]    MP integer
**               s      number of BYTES or BITS to shift
**
** return value: base address of MP integer
*/

unsigned char *mpLeftByteShift( unsigned char x[],
                                unsigned int  s)
{
  int i, j;

  if (s > 0)
    for ( i = IDIGIT; i >= 0; i--)
      if ((j = i - s) >= 0)
        x[i] = x[j];
      else
        x[i] = 0;

  return(x);
}


unsigned char *mpLeftBitShift( unsigned char x[],
                               unsigned int  s)
{
  int i, j,  ls, rs;

  ls = s & 7;           /* left shift amount per byte */
  rs = 8 - ls;          /* right shift amount per byte */

  if (s > 0)
    for ( i = IDIGIT; i >= 0; i--)
      if ((j = i - (s / 8)) > 0)
        x[i] = (x[j] << ls) | (x[j-1] >> rs);
      else if (j == 0)
        x[i] = (x[0] << ls);
      else
        x[i] = 0;

  return(x);
}


/*
** mpSub      -- subtract one multiple precision integer from another
** mpSubShort -- subtract a multiple precision integer from a short integer
**
** return value: 0 if ok; not 0 if overflow
*/

int mpSub( unsigned char minuend[],
           unsigned char subtrahend[],
           unsigned char difference[])
{
  int i, m;
  unsigned char t[XDIGIT];              /* temporary result */

  if ((m = MostSignificantDigit(subtrahend, IDIGIT)) == 0)
    return( mpSubShort(minuend, subtrahend[0], difference));

  m = MAX(m, MostSignificantDigit(minuend, IDIGIT));

  memset(t, 0, IDIGIT);                 /* clear difference */

  for ( i = 0, a.x = 256; i <= m; i++)
    t[i] = a.x = 255 + a.b[1] + minuend[i] - subtrahend[i];

  if (i < IDIGIT) t[i] = a.x = 255 + a.b[1];

  mpCopy(difference, t);

  return(a.b[1]-1);
}


int mpSubShort( unsigned char minuend[],
                unsigned char subtrahend,
                unsigned char difference[])
{
  int i, m;

  m = MostSignificantDigit(minuend, IDIGIT);

  difference[0] = a.x = 256 + minuend[0] - subtrahend;

  for ( i = 1; i <= m; i++)
    difference[i] = a.x = 255 + a.b[1] + minuend[i];

  if (i < IDIGIT) difference[i] = a.x = 255 + a.b[1];

  for ( i++; i < IDIGIT; i++)
    difference[i] = 0;

  return(a.b[1]-1);
}


/*
** mpMod     -- find the remainder of two integers, calls Div
** return value: 0 if ok; 1 if division by zero (overflow)
*/

int mpMod( unsigned char dividend[],
           unsigned char divisor[],
           unsigned char remainder[])
{
  unsigned char quotient[XDIGIT];
  return mpDiv( dividend,divisor,quotient,remainder);
}

/*
** mpIsZero -- tests if a multiple precision integer is zero
**
** return value: 1 if x == 0, 0 otherwise
*/

int mpIsZero( unsigned char x[])
{
  int m;

  m = MostSignificantDigit(x, IDIGIT);

  while (m >= 0)
  {
    if (x[m]) return(0);
    m--;
  }

  return(1);
}


/*
** mpMul      -- multiply two multiple precision integers
** mpMulShort -- multiply a multiple precision integer by a short integer
**
** return value: 0 if ok; not 0 if overflow
*/

int mpMul( unsigned char multiplicand[],
           unsigned char multiplier[],
           unsigned char product[])
{
  int i, j, m, n;
  unsigned char t[XDIGIT];              /* temporary result */

  if ((n = MostSignificantDigit(multiplier, IDIGIT)) == 0)
    return( mpMulShort(multiplicand, multiplier[0], product));

  m = MostSignificantDigit(multiplicand, IDIGIT);
  if ((m + n) >= IDIGIT) return(1);

  memset(t, 0, IDIGIT);                 /* clear product */

  for ( i = 0; i <= m; i++)
  {
    for ( j = 0, a.x = 0; j <= n; j++)
      t[i+j] = a.x = a.b[1] + t[i+j] + multiplicand[i] * multiplier[j];
    for ( ; a.b[1] > 0; j++)
      t[i+j] = a.x = a.b[1] + t[i+j];
  }

  mpCopy(product, t);

  return(a.b[1]);
}


/*
** PackASCIINumber -- squeeze all of the non-digits out of a number string
**
** return value: base address of packed string
*/

char *PackASCIINumber( char *str)
{
  char *pi = str;
  char *pj = str;

  while ( *pi ) {
    if ( isdigit(*pi) )
      *pj++ = *pi;
    pi++;
  }
  *pj = '\0';

  return(str);
}


/*
** mpRightByteShift - right byte shift a multiple precision integer
** mpRightBitShift -  right bit shift a multiple precision integer
**
** input:        x[]    MP integer
**               s      number of BYTES or BITS to shift
**
** return value: base address of MP integer
*/

unsigned char *mpRightByteShift( unsigned char x[],
                                 unsigned int  s)
{
  int i, j;

  if (s > 0)
    for ( i = 0; i <= IDIGIT; i++)
      if ((j = i + s) <= IDIGIT)
        x[i] = x[j];
      else
        x[i] = 0;

  return(x);
}

unsigned char *mpRightBitShift( unsigned char x[],
                                unsigned int  s)
{
  int i, j, ls, rs;

  rs = s & 7;           /* right shift amount per byte */
  ls = 8 - rs;          /* left shift amount per byte */

  if (s > 0)
    for (i = 0; i <= IDIGIT; i++)
      if ((j = i + (s >> 3)) < IDIGIT)
        x[i] = (x[j] >> rs) | (x[j+1] << ls);
      else if (j == IDIGIT)
        x[i] = (x[j] >> rs);
      else
        x[i] = 0;

  return(x);
}
/*
** mpScan - read an ASCII number and convert it to a
**          multiple precision integer
**
** return value: base address of input ASCII string
*/

int mpSquareRoot(unsigned char a[],
                 unsigned char q[],
                 unsigned char r[])
{
  unsigned char t[XDIGIT];      /* temp MP integer */

  mpCopy(q, a);

  if (! mpIsZero(a))
  {
    mpDiv(a, q, r, t);
    while (mpCompare(q, r) > 0)
    {
      mpAdd(q, r, q);
      mpDivShort(q, 2, q, r);
      mpDiv(a, q, r, t);
    }
  }

  mpMul(q, q, t);
  mpSub(a, t, r);

  return(0);
}




