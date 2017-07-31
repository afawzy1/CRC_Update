#ifndef CRC_H
#define CRC_H

#include "SParser.h"
#include "Std_Types.h"
#include "Crc_Types.h"
#include "Crc_Cfg.h"                           

#define __CCB_BLOCK_START_ADDRESS 		0x00018000
#define __CCB_BLOCK_END_ADDRESS 		0x000180d2
#define __EXCEPTION_TABLE_START 		0x00019000
#define __EXCEPTION_TABLE_END 			0x000190f4
#define __INTC_TABLE_START 				0x0001a000
#define __INTC_TABLE_END 				0x0001a640
#define __MTEXT_BLOCK_A_START_ADDRESS 	0x0001a800
#define __MTEXT_BLOCK_A_END_ADDRESS 	0x0006a188
#define __MTEXT_BLOCK_B_START_ADDRESS 	0x0006a188
#define __MTEXT_BLOCK_B_END_ADDRESS 	0x0006b830

#define __CRC_START_ADDRESS 			0x0001a800
#define __CRC_END_ADDRESS				0x0001a803
#define CRC_MAX_BLOCKS					(uint8)6


#define CRC_BUFFER_SIZE					512U

#define u32THIRTYTWO_XOR                (0xFFFFFFFFUL)
#define  CRC_INITIAL_VALUE32        	(0xFFFFFFFFUL)
#define u32MASK_32_REFLECT_DATA         (0x000000FFUL)
#define u8BIT_IN_ROLE_COUNTER           (uint8)(0x80U)
#define u32TOP_BIT_THIRTY_TWO           (0x80000000UL)
#define u32MASK_32_TOP_BIT              (0x7FFFFFFFUL)
#define u32THIRTYTWO_POLYNOMIAL         (0x04C11DB7UL)
#define u8TABLE_32_MASK                  (uint8)(0x0FU)
#define u8TABLE_32_SHIFT_FOUR            (0x04U)
#define FT_START_CRC_VALUE          	0xFFFFFFFFU
#define u32REFLECT_DATA_LSB             (0x00000001UL)
#define u8THIRTYTHREE                   (uint8)33
#define u8RES_REFLECT_LENGTH            (uint8)(0x20U)
#define u8INPUT_REFLECT_LENGTH          (uint8)(0x08U)



typedef struct
{
	uint32 start_address;
	uint32 end_address;

}MEM_BLOCKS;

extern MEM_BLOCKS CRC_MEMORY_SECTIONS [CRC_MAX_BLOCKS];


extern void CRC_Init(void);
extern uint32 CRC_CalculateCRC32(/*uint32 crc_accum,*/ uint8 *Start_address, uint32 block_szie);
extern uint32 CRC_CalculateMemCRC32(FILE *file, blockboundies_Type *buffer, uint8 blockLength);
extern uint32 Crc_CalculateCRC32(

      /* !Comment :  Pointer to start address of data block to be  calculated. */
      /* !Range : NONIL                                                        */
   const uint8 *Crc_DataPtr,

     /* !Comment :  Length of data block to be calculated in bytes             */
     /* !Range :  1..429467295                                                 */
   uint32 Crc_Length,
    /* !Comment :  Initial value when the algorithm starts.                    */
    /* !Range : 0..429467295                                                */
   uint32 Crc_StartValue32,
     /* !Comment :  TRUE: First call in a sequence or individual CRC           */
     /*             calculation; start from initial value, ignore              */
     /*             Crc_StartValue32.                                         */
     /*             FALSE: Subsequent call in a call sequence; Crc_StartValue32*/
     /*             is interpreted to be the return value of the previous      */
     /*             function call.                                             */
     /* !Range :  TRUE,FALSE                                                   */
     boolean Crc_IsFirstCall
 );
extern uint32 crc32(uint32 crc_accum, uint8 *data_blk_ptr, uint32 data_blk_size);

#endif
