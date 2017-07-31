/** @source __ApplicationName__
**
** __ShortDescription__
**
** @author Copyright (C) 16/4/2017 __Amr_Fawzy__
** @version 1.0
** @@
********************************************************************/


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include <stdio.h>
#include "Std_Types.h"
#include "CRC.h"
#include "SParser.h"


uint32 main(uint32 argc, uint8 *argv[])
{
	const uint8 *const Image = argv[1];
	FILE *Ifile = fopen(Image, "r+");
	uint8 buffer[MAX_LINE_LENGTH];
	blockboundies_Type blocksboundries[MAX_BLOCK_BOUNDRIES];
	uint8 blockNumber = MIN_UINT8;
	uint32 CRC = MIN_UINT32;
	uint8 firstCall = TRUE;
	uint32 temp_CRC = MIN_UINT32;
	CRC_Init();
	(void)SPR_GetBlocksBoundries(Ifile, &blockNumber, blocksboundries);
	if (Ifile == NULL)
	{
	    printf("s19 file not found !\n");
	    exit(1);
	}
	else
	{
		/*do nothing*/
	}
	CRC = CRC_CalculateMemCRC32(Ifile, blocksboundries, blockNumber);
	printf("CRC = %X \n", CRC);
	(void)spr_Write_uint32ToFile(Ifile, __CRC_START_ADDRESS, CRC);
	printf("*************************************\n");
	printf("******CRC UPDATED SUCCESSFULLY*******\n");
	printf("*************************************\n");
	fclose(Ifile);

    return 0;
}
