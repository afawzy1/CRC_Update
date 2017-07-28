#include <stdio.h>
#include "Std_Types.h"
#include "CRC.h"
#include "SParser.h"


uint32 main(uint32 argc, uint8 *argv[])
{
	const uint8 *const filename = argv[1];
	FILE *file = fopen(filename, "r+");
	uint8 buffer[MAX_LINE_LENGTH];
	uint32 startAddress = 0x13800;
	uint32 endAddress = 0x13813;
	uint32 indx = MIN_UINT32;
	uint8 pindx = MIN_UINT8;
	uint32 CRC = 0xFFFFFFFFU;
	uint8 firstCall = TRUE;
	uint32 temp_CRC = MIN_UINT32;
	CRC_Init();
	if (file == NULL)
	{
	    printf("file not found !\n");
	    exit(1);
	}

	/*while(fgets(line, sizeof(line), file))
	{
		(void)spr_ReadRecord(line);
	}*/
	/*for (pindx = MIN_UINT8; pindx < 2; pindx++)
	{
		if (E_OK == SPR_RetrieveData(file, startAddress, endAddress, buffer))
		{
			printf("data = 0x");
			for (indx = MIN_UINT32; (startAddress + indx) <= endAddress; indx++)
			{
				printf("%X ", buffer[indx]);
			}
			printf("\n");
			CRC = crc32(CRC, buffer, (endAddress - startAddress +1));
			firstCall = FALSE;
			printf("CRC = %X \n", CRC);
			temp_CRC = CRC;
			FLIP_32(temp_CRC, CRC);
			CRC = ~CRC;
			startAddress = 0x13814;
			endAddress = 0x13827;
		}
		else
		{
			printf("data is not here \n");
		}
	}*/
	CRC = CRC_CalculateMemCRC32(file);
	printf("CRC = %X \n", CRC);
	(void)spr_Write_uint32ToFile(file, __CRC_START_ADDRESS, CRC);
	fclose(file);

    return 0;
}
