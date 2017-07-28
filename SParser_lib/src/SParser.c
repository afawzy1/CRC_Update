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

#include "SParser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */



/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */


static uint8 spr_record[MAX_LINE_LENGTH];

/* ==================================================================== */
/* ============================== data ================================ */
/* ==================================================================== */

/* Definition of datatypes go here */



/* ==================================================================== */
/* ==================== function prototypes =========================== */
/* ==================================================================== */
static std_RetVal spr_CheckValidRecord(const uint8 *line);
static uint8 spr_GetRecordDataLength(const uint8 *record);
static uint32 spr_GetRecordAddress(const uint8 *line);
static uint8 spr_MapAddLength(uint8 length);
static uint8 spr_GetAddLnth(uint8 length);
static std_RetVal spr_GetAddData(FILE *file, uint32 saddress, uint8 *data);
static void spr_uint32Tohexstr(uint32 num, uint8 *buffer);



/* ==================================================================== */
/* ============================ functions ============================= */
/* ==================================================================== */


std_RetVal SPR_RetrieveData(FILE *file, uint32 startAddress, uint32 endAddress, uint8 *buffer)
{
	std_RetVal retval = E_NOT_OK;
	uint32 indx = MIN_UINT32;
	if (buffer != NULL_PTR && file != NULL_PTR && startAddress <= endAddress)
	{
		/*printf("start address = %X & end address = %X \n",startAddress, endAddress);*/
		while((startAddress + indx) <= endAddress)
		{
			if(E_OK == spr_GetAddData(file, (startAddress + indx), (buffer+indx)))
			{
				if((startAddress + indx) == endAddress)
				{
					retval = E_OK;
					break;
				}
				else
				{
					/*still there is data to be retreived*/
				}
				indx ++;
			}
			else
			{
				printf("Failure to retrieve data \n");
				/*printf("startAdd = 0x%X and endAdd = 0x%X \n", startAddress, endAddress);*/
				break;
			}
		}
		rewind(file);
	}
	else
	{
		printf("General programming ERROR CODE:01 \n");
	}
	return retval;
}

static void spr_uint32Tohexstr(uint32 num, uint8 *buffer)
{
	char hexlookup[] = { '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	uint8 indx = MIN_UINT8;
	for (indx = MIN_UINT8; indx < EIGHT_STEPS; indx++)
	{
		buffer[(EIGHT_STEPS - 1 - indx)] = hexlookup[((num >> (indx * 4))&(FOUR_BIT_MSK))];
	}
	buffer[EIGHT_STEPS] = '\0';
}

std_RetVal spr_Write_uint32ToFile(FILE *file, uint32 saddress, uint32 data)
{
	static uint8 record[MAX_LINE_LENGTH];
	static uint8 firstCall = TRUE;
	std_RetVal retval = E_NOT_OK;
	uint8 rdatalength = MIN_UINT8;
	uint32 raddress = MIN_UINT8;
	uint8 CRC[CRC_HEXSTR_LNTH + 1];
	uint8 dataoffset = MIN_UINT8;
	uint32 data_location = MIN_UINT32;
	rewind(file);
	spr_uint32Tohexstr(data, CRC);
	/*printf("0x%s\n", CRC);*/
	if (firstCall == TRUE)
	{
		fgets(record, sizeof(record), file);
		firstCall = FALSE;
	}
	else
	{
		/*do nothing*/
	}

	if (file != NULL_PTR && data != NULL_PTR)
	{
		do
		{
			rdatalength = spr_GetRecordDataLength(record);
			raddress = spr_GetRecordAddress(record);
			/*printf("Record = %s \n", record);
			printf("data_length = %X,address = %X & saddress = %X\n ",rdatalength, raddress, saddress);*/
			if (saddress >= raddress && saddress < (raddress + rdatalength))
			{
				/*printf("CHECK POINT \n");*/
				data_location = ftell(file);
				data_location -= (strlen(record) + 1);
				/*printf("record location = %d\n", data_location);*/
				fseek(file, data_location,SEEK_SET);
				dataoffset = REC_ADD_OFFSET + spr_MapAddLength(record[1]) + ((saddress - raddress) * 2);
				memcpy((record + dataoffset), CRC, CRC_HEXSTR_LNTH);
				/*printf("record = %s\n", record);*/
				fprintf(file, "%s", record);
				/*rewind(file);*/
				retval = E_OK;
				break;

			}
			else
			{
				/*the address in not in this record*/
			}
		} while (fgets(record, sizeof(record), file));
	}

	return retval;
}

static std_RetVal spr_GetAddData(FILE *file, uint32 saddress, uint8 *data)
{
	static uint8 record[MAX_LINE_LENGTH];
	static uint8 firstCall = TRUE;
	std_RetVal retval = E_NOT_OK;
	uint8 rdatalength = MIN_UINT8;
	uint32 raddress = MIN_UINT8;
	uint8 stdata[CORE_DATA_LNTH];
	uint8 dataoffset = MIN_UINT8;
	if (firstCall == TRUE)
	{
		fgets(record, sizeof(record), file);
		firstCall = FALSE;
	}
	else
	{
		/*do nothing*/
	}

	if (file != NULL_PTR && data != NULL_PTR)
	{
		do
		{
			rdatalength = spr_GetRecordDataLength(record);
			raddress = spr_GetRecordAddress(record);
			/*printf("Record = %s \n", record);
			printf("data_length = %X,address = %X & saddress = %X\n ",rdatalength, raddress, saddress);*/
			if (saddress >= raddress && saddress < (raddress +  rdatalength))
			{
				/*printf("CHECK POINT \n");*/
				dataoffset = REC_ADD_OFFSET + spr_MapAddLength(record[1]) + (saddress - raddress)*2;
				memcpy(stdata, (record + dataoffset), sizeof(stdata));
				data[0] = strtoul(stdata, NULL, 16);
				/*rewind(file);*/
				retval = E_OK;
				break;

			}
			else
			{
				/*the address in not in this record*/
			}
		}while(fgets(record, sizeof(record), file));
	}
	else
	{
		printf("General prgramming error \n");
	}
	return retval;
}

static uint8 spr_MapAddLength(uint8 length)
{
	uint8 addlength = MIN_UINT8;
	switch(CHAR2INT(length))
	{
	case ADD_16BIT:
		addlength = (uint8)4;
		break;
	case ADD_24BIT:
		addlength = (uint8)6;
		break;
	case ADD_32BIT:
		addlength = (uint8)8;
		break;
	default:
		addlength = MIN_UINT8;
		break;
	}
	return addlength;
}

static uint8 spr_GetAddLnth(uint8 length)
{
	uint8 addlength = MIN_UINT8;
	switch(CHAR2INT(length))
	{
	case ADD_16BIT:
		addlength = (uint8)2;
		break;
	case ADD_24BIT:
		addlength = (uint8)3;
		break;
	case ADD_32BIT:
		addlength = (uint8)4;
		break;
	default:
		addlength = MIN_UINT8;
		break;
	}
	return addlength;
}


static uint32 spr_GetRecordAddress(const uint8 *line)
{
	uint8 staddress[MAX_ST_ADD_LNTH];
	uint32 address = MIN_UINT32;
	uint8 add_length = spr_MapAddLength(line[1]);
	uint8 indx = MIN_UINT8;
	memcpy(staddress, (line + REC_ADD_OFFSET), add_length);
	address = strtoul(staddress, NULL, 16);
	return address;
}

static uint8 spr_GetRecordDataLength(const uint8 *record)
{
	uint8 stdatalength[] = {MIN_UINT8, MIN_UINT8};
	uint8 datalength = MIN_UINT8;
	memcpy(stdatalength, (record + 2), sizeof(stdatalength));
	datalength = (uint8)strtoul(stdatalength, NULL, 16);
	return datalength - 1 - spr_GetAddLnth(record[1]);
}

static std_RetVal spr_CheckValidRecord(const uint8 *line)
{
	std_RetVal retval = E_NOT_OK;
	uint16 indx = MIN_UINT16;
	if (line[0] == 'S')
	{
		while (indx < MAX_LINE_LENGTH)
		{
			if (line[indx] != '\n')
			{
				retval = E_OK;
				break;
			}
			else
			{
				/*do nothing*/
			}
			indx ++;
		}
	}
	else
	{
		/*the record is corrupted*/
	}
	return retval;
}

