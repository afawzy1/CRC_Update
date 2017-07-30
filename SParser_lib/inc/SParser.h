#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SPR_H
#define SPR_H


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include <stdio.h>
#include "Std_Types.h"




/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

#define MAX_LINE_LENGTH 	256
#define MAX_BLOCK_BOUNDRIES 15
#define REC_ADD_OFFSET 		4
#define REC_HEADER_OFFEST	2
#define ADD_16BIT			1
#define ADD_24BIT			2
#define ADD_32BIT			3
#define MAX_ST_ADD_LNTH		8
#define CORE_DATA_LNTH		2
#define EIGHT_STEPS			8
#define TWO_STEPS			2
#define FOUR_BIT_MSK		0x0F
#define CRC_HEXSTR_LNTH		8
#define CHAR2INT(character) (character - '0')
#define BLOCK_NUM			(uint8)6
#define RAM_START_ADDRESS	0x40000000





/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */
typedef struct
{
	uint32 startAdd;
	uint32 endAdd;
}blockboundies_Type;





/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */

extern std_RetVal SPR_RetrieveData(FILE *file, uint32 startAddress, uint32 endAddress, uint8 *buffer);
extern std_RetVal spr_Write_uint32ToFile(FILE *file, uint32 saddress, uint32 data);
extern std_RetVal SPR_GetBlocksBoundries(FILE *file, uint8 *BlocksNumber, blockboundies_Type *buffer);

#endif
#ifdef __cplusplus
}
#endif
