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

const uint8 CCB_Start[]  = { " __CCB_BLOCK_START_ADDRESS \n" };
const uint8 CCB_Stop []  = { " __CCB_BLOCK_END_ADDRESS \n" };
const uint8 Exp_Start[]  = { " __EXCEPTION_TABLE_START \n" };
const uint8 Exp_Stop []  = { "__EXCEPTION_TABLE_END \n" };
const uint8 Int_Start[]  = { "__INTC_TABLE_START \n" };
const uint8 Int_Stop[]   = { "__INTC_TABLE_END \n" };
const uint8 BlkA_Start[] = { "__MTEXT_BLOCK_A_START_ADDRESS \n" };
const uint8 BlkA_Stop[]  = { "__MTEXT_BLOCK_A_END_ADDRESS \n" };
const uint8 BlkB_Start[] = { "__MTEXT_BLOCK_B_START_ADDRESS \n" };
const uint8 BlkB_Stop[]  = { "__MTEXT_BLOCK_B_END_ADDRESS \n" };
const uint8 CRC_Start[] =  {"__CRC_START_ADDRESS \n"};
const uint8 CRC_Stop[] =   {"__CRC_END_ADDRESS \n"};

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
static std_RetVal hex2uint8(uint8 *hex, uint8 *data);
static void spr_uint32Tohexstr(uint32 num, uint8 *buffer);
static void spr_ConcBlocks(blockboundies_Type *buffer, uint8 blocknumber, uint8 *concBlocks);
static std_RetVal spr_updateRecordCkSum(uint8 *record);
static void spr_uint8Tohexstr(uint32 num, uint8 *buffer);
static uint8 spr_GetRecordByteLgth(const uint8 *record);




/* ==================================================================== */
/* ============================ functions ============================= */
/* ==================================================================== */
std_RetVal SPR_GetBlocksBoundries(FILE *file, uint8 *BlocksNumber, blockboundies_Type *buffer)
{
	static uint8 record[MAX_LINE_LENGTH];
	static uint8 firstCall = TRUE;
	static uint8 AddfoundLater = FALSE;
	static uint32 lastRecordAdd = MIN_UINT32;
	static uint8 lastRecordDataLngh = MIN_UINT8;
	std_RetVal retval = E_NOT_OK;
	uint8 rdatalength = MIN_UINT8;
	uint32 raddress = MIN_UINT8;
	uint8 stdata[CORE_DATA_LNTH];
	uint8 dataoffset = MIN_UINT8;
	uint8 addIndex = MIN_UINT8;
	uint8 indx = MIN_UINT8;
	uint8 concBlocks = MIN_UINT8;
	if (file != NULL_PTR && BlocksNumber != NULL_PTR)
	{
		if (firstCall == TRUE)
		{
			do
			{
				if (!fgets(record, sizeof(record), file))
				{
					printf("S19 file format error \n");
					exit(1);
				}
				else
				{
					raddress = spr_GetRecordAddress(record);
					rdatalength = spr_GetRecordDataLength(record);
				}
			} while (raddress == MIN_UINT32);
			buffer[addIndex].startAdd = raddress;
			/*printf("startadd = %X\n", buffer[addIndex].startAdd);*/
		}
		else
		{
			/*do nothing*/
		}
		do
		{
			if (firstCall == FALSE)
			{
				rdatalength = spr_GetRecordDataLength(record);
				raddress = spr_GetRecordAddress(record);
			}
			firstCall = FALSE;
			/*printf("Record = %s \n", record);*/
			/*printf("rdatalength = %X,raddress = %X & last_address = %X\n ", rdatalength, raddress, lastRecordAdd);*/
			if (
					lastRecordAdd != MIN_UINT32
					&&
					(lastRecordDataLngh + lastRecordAdd) != raddress
				)
			{
				buffer[addIndex].endAdd = (lastRecordDataLngh + lastRecordAdd - 1);
				/*printf("endAdd = %X\n", buffer[addIndex].endAdd);*/
				if (raddress == MIN_UINT32)
				{
					/*ignore that address*/
				}
				else
				{
					addIndex++;
					buffer[addIndex].startAdd = raddress;
					/*printf("startadd = %X\n", buffer[addIndex].startAdd);*/
				}
				
			}
			else
			{
				/*the address in not in this record*/
			}
			lastRecordAdd = raddress;
			lastRecordDataLngh = rdatalength;
		} while (fgets(record, sizeof(record), file));
		addIndex++;
		printf("******************************************************\n");
		spr_ConcBlocks(buffer, addIndex , &concBlocks);
		/*printf("blocks number = %d\n", addIndex);
		printf("Conc = %d\n", concBlocks);*/
		BlocksNumber[0] = (addIndex - concBlocks);
		/*for (indx = MIN_UINT8; indx < BlocksNumber[0]; indx++)
		{
			printf("startadd = %X\n", buffer[indx].startAdd);
			printf("endAdd = %X\n", buffer[indx].endAdd);
		}*/

	}
	rewind(file);
	return retval;
}

static void spr_ConcBlocks(blockboundies_Type *buffer, uint8 blocknumber, uint8 *concBlocks)
{
	uint8 indx1 = MIN_UINT8;
	uint8 indx2 = MIN_UINT8;
	concBlocks[0] = MIN_UINT8;
	/*printf("blocks number = %d\n", blocknumber);*/
	for (indx1 = MIN_UINT8; indx1 < blocknumber; indx1++)
	{
		for (indx2 = MIN_UINT8; indx2 < blocknumber; indx2++)
		{
			if ((buffer[indx1].endAdd + 1) == buffer[indx2].startAdd)
			{
				/*printf("indx1 = %d, indx2 = %d\n", indx1, indx2);*/
				buffer[indx1].endAdd = buffer[indx2].endAdd;
				concBlocks[0] +=1;
				/*printf("Conc = %d\n", concBlocks[0]);*/
			}
			else
			{
			}
		}
	}
	blocknumber -= concBlocks[0];
	for (indx1 = MIN_UINT8; indx1 < blocknumber; indx1++)
	{
		if (buffer[indx1].startAdd > RAM_START_ADDRESS)
		{
			concBlocks[0] += 1;
			for (indx2 = indx1 + 1; indx2 < blocknumber; indx2++)
			{
				buffer[indx2 - 1].startAdd = buffer[indx2].startAdd;
				buffer[indx2 - 1].endAdd = buffer[indx2].endAdd;
			}
		}
	}

}

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
				indx++;
				/*printf("Add: %X, Data: %X \n",startAddress + indx,  buffer[indx]);*/
				/*if(indx == 60) scanf("%s",indx);*/
			}
			else
			{
				printf("Failure to retrieve data \n");
				exit(1);
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

static void spr_uint8Tohexstr(uint32 num, uint8 *buffer)
{
	char hexlookup[] = { '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	uint8 indx = MIN_UINT8;
	for (indx = MIN_UINT8; indx < TWO_STEPS; indx++)
	{
		buffer[(TWO_STEPS - 1 - indx)] = hexlookup[((num >> (indx * 4))&(FOUR_BIT_MSK))];
	}
	buffer[TWO_STEPS] = '\0';
}

static std_RetVal spr_updateRecordCkSum(uint8 *record)
{
	uint32 sum = MIN_UINT32;
	uint8 rdatalength = MIN_UINT8;
	uint32 raddress = MIN_UINT8;
	uint8 indx = MIN_UINT8;
	uint8 dataoffset = MIN_UINT8;
	uint8 stdata[CORE_DATA_LNTH];
	uint8 checksum = MIN_UINT8;
	uint8 CKS[CORE_DATA_LNTH + 1];
	rdatalength = spr_GetRecordByteLgth(record);
	/*printf("record bytes = %d\n", rdatalength);*/
	for (indx = MIN_UINT8; indx < (rdatalength * 2); indx+=2)
	{
		dataoffset = REC_HEADER_OFFEST + indx;
		memcpy(stdata, (record + dataoffset), sizeof(stdata));
		sum += strtoul(stdata, NULL, 16);
		/*printf("sum = %X ,byte = %s\n", sum, stdata);*/
	}
	checksum = ~((uint8)sum);
	/*printf("sum = %X\n", checksum);*/
	spr_uint8Tohexstr(checksum, CKS);
	memcpy((record + REC_HEADER_OFFEST + indx), CKS, sizeof(CKS));
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
				/*printf("record = %s\n", record);*/
				memcpy((record + dataoffset), CRC, CRC_HEXSTR_LNTH);
				/*printf("record = %s\n", record);*/
				(void)spr_updateRecordCkSum(record);
				/*printf("record = %s\n", record);*/
				fprintf(file, "%s", record);
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
				dataoffset = REC_ADD_OFFSET + (spr_MapAddLength(record[1])) + ((saddress - raddress)*2);
				memcpy(stdata, (record + dataoffset), sizeof(stdata));
				/*data[0] = strtoul(stdata, NULL, 16);*/
				if(E_OK != hex2uint8(stdata, data))
				{
					printf("General programming error CODE:04 \n");
					exit(1);
				}
				else
				{
					/*if(saddress == 0x18022)
					{
						printf("0x18022:%s \n", stdata);
						printf("0x18022:%X \n", data[0]);

					}*/
					/*rewind(file);*/
					retval = E_OK;
					break;
				}
			}
			else
			{
				/*the address in not in this record*/
			}
		}while(fgets(record, sizeof(record), file));
	}
	else
	{
		printf("General programming error CODE:05 \n");
		exit(1);
	}
	return retval;
}

static std_RetVal hex2uint8(uint8 *hex, uint8 *data) {
	std_RetVal retval = E_OK;
	uint8 indx = MIN_UINT8;
	uint8 byte = MIN_UINT8;
    for(indx = MIN_UINT8; indx < TWO_STEPS; indx++)
    {
        // get current character then increment
        byte = hex[indx];
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        else
        {
        	retval = E_NOT_OK;
        	break;
        }
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        data[0] = (data[0] << 4) | (byte & 0xF);
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

static uint8 spr_GetRecordByteLgth(const uint8 *record)
{
	uint8 stdatalength[] = { MIN_UINT8, MIN_UINT8 };
	uint8 datalength = MIN_UINT8;
	memcpy(stdatalength, (record + 2), sizeof(stdatalength));
	datalength = (uint8)strtoul(stdatalength, NULL, 16);
	return datalength;
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

