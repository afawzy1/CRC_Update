#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <string.h>

#define ARRAY_SIZE(x)	((sizeof(x))/(sizeof(x[0])))
#define WIDTH(x)		(8*sizeof(x))
#define GET_TOPBIT(x)	((x) & (1 << (WIDTH(x) - 1)))
#define MIN_UINT8		(uint8)0
#define MAX_UINT8		(uint8)0xFF
#define MIN_UINT16		(uint16)0
#define MAX_UINT16		(uint16)0xFFFF
#define MIN_UINT32		(uint32)0
#define MAX_UINT32 		(uint32)0xFFFFFFFF
#define MIN_FLOAT		(float)0
#define OR 				|
#define AND 			&
#define XOR 			^
#define Inf				
#define BITS(x)			(1<<(x))
#define PRINT_B(x)		for (sint8 indx = ((sizeof(x)*8)-1); indx >= 0 ; indx--)\
						{\
							(((x) & (BITS(indx))) == 0) ? printf("0") : printf("1");\
							if(((sizeof(x)*8)/2) == indx) printf(" ");\
						}\
						printf("\n")

#define FLIP_32(y,x)	(x) = (y);\
						(x) = (((x) & 0x55555555) <<  1) | (((x) >> 1) & 0x55555555);\
						(x) = (((x) & 0x33333333) <<  2) | (((x) >> 2) & 0x33333333);\
						(x) = (((x) & 0x0F0F0F0F) <<  4) | (((x) >> 4) & 0x0F0F0F0F);\
						(x) = (((x) & 0x00FF00FF) <<  8) | (((x) >> 8) & 0x00FF00FF);\
						(x) = (((x) & 0x0000FFFF) << 16) | (((x) >> 16)& 0x0000FFFF);

#define FLIP_16(y,x)	(x) = (y);\
						(x) = (((x) & 0x5555) <<  1) | (((x) >> 1) & 0x5555);\
						(x) = (((x) & 0x3333) <<  2) | (((x) >> 2) & 0x3333);\
						(x) = (((x) & 0x0F0F) <<  4) | (((x) >> 4) & 0x0F0F);\
						(x) = (((x) & 0x00FF) <<  8) | (((x) >> 8) & 0x00FF);

#define FLIP_8(y, x)	(x) = (y);\
						(x) = (((x) & 0x55) <<  1) | (((x) >> 1) & 0x55);\
						(x) = (((x) & 0x33) <<  2) | (((x) >> 2) & 0x33);\
						(x) = (((x) & 0x0F) <<  4) | (((x) >> 4) & 0x0F);

#define FILL_ARRAY(a,v)              memset(a, v, sizeof(a))
#define MAX(a,b)                     ( (a) > (b) ? (a) : (b))
#define MIN(a,b)                     ( (a) < (b) ? (a) : (b))
#define CHECK_BIT(n,b)               ( (n >> b) & 1 )
#define LOW_BIT(x) 					 ((x)&((x)^((x)-1))) //get the lowest bit of x
#define ABS(x)						 ((x < 0)? (-x):(x))
/*get the highest bit of x, maybe the fastest*/
#define HIGH_BIT(msb,n) 			 asm("bsrl %1,%0" : "=r"(msb) : "r"(n))

#define UNUSED(x)					 (void)x

#define TRUE 			(uint8)1
#define FALSE			(uint8)0
#define NULL_PTR			0

typedef unsigned char 		uint8;
typedef char			 	sint8;
typedef unsigned char		boolean;
typedef unsigned short		uint16;
typedef short 				sint16;
typedef unsigned long		uint32;
typedef long				sint32;
typedef double 				sint64;
typedef enum
{
	E_OK,
	E_NOT_OK
}std_RetVal;



#endif
