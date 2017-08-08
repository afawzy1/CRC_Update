#include <stdlib.h>
#include "CRC.h"



/*
 * CRC32------------> CRC_TYPE = 1
 * CRC32_BZIP2------> CRC_TYPE = 2
 * CRC32_C----------> CRC_TYPE = 3
 * CRC32_D----------> CRC_TYPE = 4
 * */
#define CRC_TYPE			1U

#if CRC_TYPE == 1 || CRC_TYPE == 2
	#define POLYNOMIAL 			0x4C11DB7      // Standard CRC-32 polynomial
#elif CRC_TYPE == 3
	#define POLYNOMIAL			0x1EDC6F41
#elif CRC_TYPE == 4
	#define POLYNOMIAL			0xA833982B
#else
	#error "WRONG CRC TYPE"
#endif
#define CRC_LKUPT_LENGTH	256U
#define BUFFER_LEN       	4096L      // Length of buffer



MEM_BLOCKS CRC_MEMORY_SECTIONS [CRC_MAX_BLOCKS] = {
															 __CCB_BLOCK_START_ADDRESS,        
															 __EXCEPTION_TABLE_START,          
															 __INTC_TABLE_START,               
															 __MTEXT_BLOCK_A_START_ADDRESS,    		
															 __MTEXT_BLOCK_B_START_ADDRESS,    
												  };
blockboundies_Type crc_Add = { __CRC_START_ADDRESS, __CRC_END_ADDRESS };

static const uint32 aku32Table[Crc_u8TABLE32_SIZE] =
{
#if (Crc_u8TABLE32_SIZE == 16U)
  0x00000000UL, 0x1DB71064UL, 0x3B6E20C8UL, 0x26D930ACUL, 0x76DC4190UL,
  0x6B6B51F4UL, 0x4DB26158UL, 0x5005713CUL, 0xEDB88320UL, 0xF00F9344UL,
  0xD6D6A3E8UL, 0xCB61B38CUL, 0x9B64C2B0UL, 0x86D3D2D4UL, 0xA00AE278UL,
  0xBDBDF21CUL
#else
  0x00000000UL, 0x77073096UL, 0xEE0E612CUL, 0x990951BAUL, 0x076DC419UL,
  0x706AF48FUL, 0xE963A535UL, 0x9E6495A3UL, 0x0EDB8832UL, 0x79DCB8A4UL,
  0xE0D5E91EUL, 0x97D2D988UL, 0x09B64C2BUL, 0x7EB17CBDUL, 0xE7B82D07UL,
  0x90BF1D91UL, 0x1DB71064UL, 0x6AB020F2UL, 0xF3B97148UL, 0x84BE41DEUL,
  0x1ADAD47DUL, 0x6DDDE4EBUL, 0xF4D4B551UL, 0x83D385C7UL, 0x136C9856UL,
  0x646BA8C0UL, 0xFD62F97AUL, 0x8A65C9ECUL, 0x14015C4FUL, 0x63066CD9UL,
  0xFA0F3D63UL, 0x8D080DF5UL, 0x3B6E20C8UL, 0x4C69105EUL, 0xD56041E4UL,
  0xA2677172UL, 0x3C03E4D1UL, 0x4B04D447UL, 0xD20D85FDUL, 0xA50AB56BUL,
  0x35B5A8FAUL, 0x42B2986CUL, 0xDBBBC9D6UL, 0xACBCF940UL, 0x32D86CE3UL,
  0x45DF5C75UL, 0xDCD60DCFUL, 0xABD13D59UL, 0x26D930ACUL, 0x51DE003AUL,
  0xC8D75180UL, 0xBFD06116UL, 0x21B4F4B5UL, 0x56B3C423UL, 0xCFBA9599UL,
  0xB8BDA50FUL, 0x2802B89EUL, 0x5F058808UL, 0xC60CD9B2UL, 0xB10BE924UL,
  0x2F6F7C87UL, 0x58684C11UL, 0xC1611DABUL, 0xB6662D3DUL, 0x76DC4190UL,
  0x01DB7106UL, 0x98D220BCUL, 0xEFD5102AUL, 0x71B18589UL, 0x06B6B51FUL,
  0x9FBFE4A5UL, 0xE8B8D433UL, 0x7807C9A2UL, 0x0F00F934UL, 0x9609A88EUL,
  0xE10E9818UL, 0x7F6A0DBBUL, 0x086D3D2DUL, 0x91646C97UL, 0xE6635C01UL,
  0x6B6B51F4UL, 0x1C6C6162UL, 0x856530D8UL, 0xF262004EUL, 0x6C0695EDUL,
  0x1B01A57BUL, 0x8208F4C1UL, 0xF50FC457UL, 0x65B0D9C6UL, 0x12B7E950UL,
  0x8BBEB8EAUL, 0xFCB9887CUL, 0x62DD1DDFUL, 0x15DA2D49UL, 0x8CD37CF3UL,
  0xFBD44C65UL, 0x4DB26158UL, 0x3AB551CEUL, 0xA3BC0074UL, 0xD4BB30E2UL,
  0x4ADFA541UL, 0x3DD895D7UL, 0xA4D1C46DUL, 0xD3D6F4FBUL, 0x4369E96AUL,
  0x346ED9FCUL, 0xAD678846UL, 0xDA60B8D0UL, 0x44042D73UL, 0x33031DE5UL,
  0xAA0A4C5FUL, 0xDD0D7CC9UL, 0x5005713CUL, 0x270241AAUL, 0xBE0B1010UL,
  0xC90C2086UL, 0x5768B525UL, 0x206F85B3UL, 0xB966D409UL, 0xCE61E49FUL,
  0x5EDEF90EUL, 0x29D9C998UL, 0xB0D09822UL, 0xC7D7A8B4UL, 0x59B33D17UL,
  0x2EB40D81UL, 0xB7BD5C3BUL, 0xC0BA6CADUL, 0xEDB88320UL, 0x9ABFB3B6UL,
  0x03B6E20CUL, 0x74B1D29AUL, 0xEAD54739UL, 0x9DD277AFUL, 0x04DB2615UL,
  0x73DC1683UL, 0xE3630B12UL, 0x94643B84UL, 0x0D6D6A3EUL, 0x7A6A5AA8UL,
  0xE40ECF0BUL, 0x9309FF9DUL, 0x0A00AE27UL, 0x7D079EB1UL, 0xF00F9344UL,
  0x8708A3D2UL, 0x1E01F268UL, 0x6906C2FEUL, 0xF762575DUL, 0x806567CBUL,
  0x196C3671UL, 0x6E6B06E7UL, 0xFED41B76UL, 0x89D32BE0UL, 0x10DA7A5AUL,
  0x67DD4ACCUL, 0xF9B9DF6FUL, 0x8EBEEFF9UL, 0x17B7BE43UL, 0x60B08ED5UL,
  0xD6D6A3E8UL, 0xA1D1937EUL, 0x38D8C2C4UL, 0x4FDFF252UL, 0xD1BB67F1UL,
  0xA6BC5767UL, 0x3FB506DDUL, 0x48B2364BUL, 0xD80D2BDAUL, 0xAF0A1B4CUL,
  0x36034AF6UL, 0x41047A60UL, 0xDF60EFC3UL, 0xA867DF55UL, 0x316E8EEFUL,
  0x4669BE79UL, 0xCB61B38CUL, 0xBC66831AUL, 0x256FD2A0UL, 0x5268E236UL,
  0xCC0C7795UL, 0xBB0B4703UL, 0x220216B9UL, 0x5505262FUL, 0xC5BA3BBEUL,
  0xB2BD0B28UL, 0x2BB45A92UL, 0x5CB36A04UL, 0xC2D7FFA7UL, 0xB5D0CF31UL,
  0x2CD99E8BUL, 0x5BDEAE1DUL, 0x9B64C2B0UL, 0xEC63F226UL, 0x756AA39CUL,
  0x026D930AUL, 0x9C0906A9UL, 0xEB0E363FUL, 0x72076785UL, 0x05005713UL,
  0x95BF4A82UL, 0xE2B87A14UL, 0x7BB12BAEUL, 0x0CB61B38UL, 0x92D28E9BUL,
  0xE5D5BE0DUL, 0x7CDCEFB7UL, 0x0BDBDF21UL, 0x86D3D2D4UL, 0xF1D4E242UL,
  0x68DDB3F8UL, 0x1FDA836EUL, 0x81BE16CDUL, 0xF6B9265BUL, 0x6FB077E1UL,
  0x18B74777UL, 0x88085AE6UL, 0xFF0F6A70UL, 0x66063BCAUL, 0x11010B5CUL,
  0x8F659EFFUL, 0xF862AE69UL, 0x616BFFD3UL, 0x166CCF45UL, 0xA00AE278UL,
  0xD70DD2EEUL, 0x4E048354UL, 0x3903B3C2UL, 0xA7672661UL, 0xD06016F7UL,
  0x4969474DUL, 0x3E6E77DBUL, 0xAED16A4AUL, 0xD9D65ADCUL, 0x40DF0B66UL,
  0x37D83BF0UL, 0xA9BCAE53UL, 0xDEBB9EC5UL, 0x47B2CF7FUL, 0x30B5FFE9UL,
  0xBDBDF21CUL, 0xCABAC28AUL, 0x53B39330UL, 0x24B4A3A6UL, 0xBAD03605UL,
  0xCDD70693UL, 0x54DE5729UL, 0x23D967BFUL, 0xB3667A2EUL, 0xC4614AB8UL,
  0x5D681B02UL, 0x2A6F2B94UL, 0xB40BBE37UL, 0xC30C8EA1UL, 0x5A05DF1BUL,
  0x2D02EF8DUL
#endif
};




static uint8 CRC_Buffer[CRC_BUFFER_SIZE];
static uint32 CRC_accum = 0xFFFFFFFF;



uint32 crc32(uint32 crc_accum, uint8 *data_blk_ptr, uint32 data_blk_size);


static uint32 CRC_table[CRC_LKUPT_LENGTH];




void CRC_Init(void)
{
	register uint16 byte, indx;
	register uint32 crc_accum;

	for (byte=0;  byte<256;  byte++)
	{
	  crc_accum = ( (uint32) byte << 24 );
	  for ( indx = 0;  indx < 8;  indx++ )
	  {
	    if ( (crc_accum >> 31) & 1 )
	      crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
	    else
	      crc_accum = (crc_accum << 1);
	  }
	  CRC_table[byte] = crc_accum;
	}
	CRC_accum = 0xFFFFFFFF;
	memset(CRC_Buffer, ARRAY_SIZE(CRC_Buffer), MIN_UINT8);
}

uint32 crc32(uint32 crc_accum, uint8 *data_blk_ptr, uint32 data_blk_size)
{
   uint32 crc = MIN_UINT32, indx = MIN_UINT32;
   uint8 reversed_data;
   uint32 temp_crc = MIN_UINT32;
   if (crc_accum != 0xFFFFFFFF)
   {
	   FLIP_32(temp_crc, crc_accum);
	   crc_accum = ~crc_accum;
   }

   for (indx=0; indx<data_blk_size; indx++)
   {
#if CRC_TYPE == 1 || CRC_TYPE == 3 || CRC_TYPE == 4
	   FLIP_8(data_blk_ptr[indx], reversed_data);
	   /*printf("CRC_ACC = %X\n", crc_accum);*/
	   crc = ((crc_accum >> 24) ^ (uint32)reversed_data) & ((uint32)(0xFF));
	   crc_accum = (crc_accum << 8) ^ CRC_table[crc];
	}
	crc_accum = ~crc_accum;
	FLIP_32(crc_accum, crc);
	return crc;
#elif CRC_TYPE == 2

	   byte = ((uint16) (crc_accum >> 24) ^ data_blk_ptr[indx]) & 0xFF;
	   crc_accum = (crc_accum << 8) ^ CRC_table[byte];
	}
	crc_accum = ~crc_accum;

	return crc_accum;
#else
	}
#endif

}

uint32 CRC_CalculateCRC32(/*uint32 crc_accum,*/ uint8 *Start_address, uint32 blocksize)
{
	if (
			Start_address != NULL_PTR
	   )
	{
		CRC_accum = crc32(CRC_accum, Start_address, blocksize);
	}
	else
	{
		printf("General programming ERROR CODE:01 \n");
	}
	return CRC_accum;
}
uint32 CRC_CalculateMemCRC32(FILE *file, blockboundies_Type *buffer, uint8 blockLength)
 {
	 uint8 indx = MIN_UINT8;
	 uint8 pindx = MIN_UINT8;
	 uint32 Add2Start = NULL_PTR;
	 uint32 Add2Stop  = NULL_PTR;
	 uint32 blocksize = MIN_UINT32;
	 uint32 endChunkAdd = MIN_UINT32;
	 boolean firstCall = TRUE;
	 for (indx = MIN_UINT8; indx < blockLength; indx++)
	 {
		 Add2Start = buffer[indx].startAdd;
		 Add2Stop = buffer[indx].endAdd;
		 printf("**************START READING BLOCK %d************** \n", indx);
		 if (
				 __builtin_expect((Add2Start < __CRC_START_ADDRESS && Add2Stop >= __CRC_END_ADDRESS),0U)
			 )
		 {
			 printf("Not Implemented YET\n");
			 exit(1);
		 }
		 else if (
				 __builtin_expect((Add2Start == __CRC_START_ADDRESS && Add2Stop >= __CRC_END_ADDRESS),1U)
			     )
		 {
			 Add2Start = __CRC_END_ADDRESS + 1;
			 buffer[indx].startAdd = Add2Start;
			 /*printf("Check point2 \n");*/
		 }
		 else
		 {
		 }
		 printf("Start Add = %X \n", Add2Start);
		 printf("End Add = %X \n", Add2Stop);
		 while(Add2Start < Add2Stop)
		{
			 blocksize = ((Add2Stop - Add2Start + 1) >= CRC_BUFFER_SIZE) ? CRC_BUFFER_SIZE : (Add2Stop - Add2Start + 1);
			 firstCall = (Add2Start == buffer[MIN_UINT8].startAdd) ? TRUE : FALSE;
			 CRC_accum = (firstCall == TRUE) ?  0xFFFFFFFF : CRC_accum;

			 if (__builtin_expect((E_OK == SPR_RetrieveData(file, Add2Start, (Add2Start + blocksize - 1) , CRC_Buffer)),1U))
			 {
				/*printf("CRC = %X\n", CRC_accum);*/
				/*printf("data = 0x");
				for(pindx = MIN_UINT32; pindx < blocksize; pindx++)
				{
					printf("%X ", CRC_Buffer[pindx]);
				}
				printf("\n");*/
			 	/*CRC_accum = crc32(CRC_accum,CRC_Buffer, blocksize);*/
				 /*scanf("%S",CRC_Buffer);*/
				 CRC_accum = Crc_CalculateCRC32(CRC_Buffer, blocksize, CRC_accum, firstCall);

				 /*printf("Check point 1: %X \n", CRC_accum);
				 printf("Length = %d\n", blocksize);*/
				 /*scanf("%S",CRC_Buffer);*/
			 }
			 else
			 {
			 	printf("General programming ERROR CODE:02 \n");
			 	break;
			 }
			 Add2Start = ((Add2Stop - Add2Start + 1) >= CRC_BUFFER_SIZE) ? (Add2Start + CRC_BUFFER_SIZE) : (Add2Stop + 1);
		}
		 /*printf("CRC = %X\n", CRC_accum);*/
	 }
	 return CRC_accum;
 }


#if (Crc_bCALC_THIRTYTWO_API == STD_ON)

 uint32 Crc_CalculateCRC32(

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
 )
 /* PRQA S 0850 --                                                             */

 {
     /* !Pseudo:  If CRC_32_MODE = CRC_32_RUNTIME.(2)         */
     /* !Pseudo:  If Crc_IsFirstCall != FALSE.(12)                      */
     /* !Pseudo: Set CRC Start value to the intial value             */
     /* !Pseudo:  Else. (12)                      */
     /* !Pseudo:  The start value is XORed with the XOR value.             */
     /* !Pseudo:  The result is then reflected.                       */
     /* !Pseudo:  End If. (12)                      */
     /* !Pseudo:  Loop[1] on the u32Length byte by byte.                       */
     /* !Pseudo:  ReflectedDataByte=input data reflected.                      */
     /* !Pseudo:  Loop[2] on the byte bit by bit.                              */
     /* !Pseudo:  (Bit in role var)= Message AND 0x80000000                    */
     /* !Pseudo:  If the bit in role of ReflectedDataByte==1  (6)              */
     /* !Pseudo:  invert MSB of (Bit in role var).                             */
     /* !Pseudo:  End if(6).                                                   */
     /* !Pseudo:  If (Bit in role var) ==1  (7)                                */
     /* !Pseudo:  Message = (Message) XOR (POLYNOMIAL)                         */
     /* !Pseudo:  End if (7).                                                  */
     /* !Pseudo:  Get next bit in role                                         */
     /* !Pseudo:  End loop[2].                                                 */
     /* !Pseudo:  Get next byte in role                                        */
     /* !Pseudo:  End Loop[1].                                                 */
     /* !Pseudo:  CRCresult=CRCresult reflected                                */
     /* !Pseudo:  End if.(2)                                                   */
     /* !Pseudo:  if (CRC_32_MODE == CRC_32_TABLE)  (15)                 */
     /* !Pseudo:  Loop[3] on the u32Length byte by byte.                     */
     /* !Pseudo: Get the value of the table corresponding to the input dataByte*/
     /* !Pseudo:  Get next byte in role                                        */
     /* !Pseudo:  End Loop[3].                                               */
     /* !Pseudo:  end if(15)                                              */
     /* !Pseudo:  CRCresult=Message XOR(FINAL_XOR_VALUE)                       */
     /* !Pseudo:  Return Crcresult                                             */
     /* !Pseudo:  If the (CRC_32_MODE != CRC_32_RUNTIME)   &&   */
     /* !Pseudo:  (!= CRC_32_TABLE)  (11)          */
     /* !Pseudo:  report a compiler error of unsupported mode.                 */
     /* !Pseudo:  End if.(11)                                                  */

     /* !Deviation : Inhibit MISRA rule [94]: because the AUTOMATIC         */
        /*              Keyword is defined as empty                            */
        /* PRQA S 0850 ++                                                      */

     uint32 u32Index = MIN_UINT32;
     uint32 TEMP = MIN_UINT32;
	 /*printf("Check point 1: %X \n", Crc_StartValue32);*/
 #if (CRC_32_MODE == CRC_32_RUNTIME)
	 printf("I am HERE\n");
     uint32 u32Bit = MIN_UINT32;

     uint8 u8MaskBit = MIN_UINT8;
     uint8 u8TempValue = MIN_UINT8;
     uint32 temp32 = MIN_UINT32;
     /* PRQA S 0850 --                                                         */

     if (Crc_IsFirstCall != FALSE)
     {
         /* !Trace_To:  GSCSW-CRC-SDD-001-0076                             */
         /* !Set CRC Start value to the intial value						  */
         Crc_StartValue32 = CRC_INITIAL_VALUE32;
     }
     else
     {
         /* !Trace_To:  GSCSW-CRC-SDD-001-0077                             */
    	 /*Crc_StartValue32 = Crc_StartValue32 ^ u32THIRTYTWO_XOR;
    	 Crc_StartValue32 = u32ReflectData(Crc_StartValue32, u8RES_REFLECT_LENGTH);*/
    	 temp32 = Crc_StartValue32 ^ u32THIRTYTWO_XOR;
    	 FLIP_32(temp32, Crc_StartValue32)
     }

     for (u32Index = 0; u32Index < Crc_Length; u32Index++)
     {
 	 if (Crc_DataPtr != NULL_PTR )
 	 {
 		 /*u8TempValue = (uint8)(u32ReflectData((uint32)(Crc_DataPtr[u32Index]),
 		               u8INPUT_REFLECT_LENGTH) & u32MASK_32_REFLECT_DATA);*/
 		 FLIP_8((Crc_DataPtr[u32Index]), u8TempValue);

         u8MaskBit = u8BIT_IN_ROLE_COUNTER;

         while(u8MaskBit > 0)
         {
             u32Bit = Crc_StartValue32 & u32TOP_BIT_THIRTY_TWO;
             if ((u8TempValue & u8MaskBit) != 0)
             {
                 u32Bit = u32Bit ^ u32TOP_BIT_THIRTY_TWO;
             }
             else
             {
                 /* Do Nothing */
             }
     /* !Deviation : Inhibit message 3371: bits truncation is intended         */
     /* PRQA S 3371 ++                                                         */
             Crc_StartValue32 = (Crc_StartValue32 & u32MASK_32_TOP_BIT) << 1;
     /* PRQA S 3371 --                                                         */

             if (u32Bit != 0)
             {
                 Crc_StartValue32 = Crc_StartValue32 ^ u32THIRTYTWO_POLYNOMIAL;
             }
             else
             {
                 /* Do Nothing */
             }

             u8MaskBit = (u8MaskBit >> 1);
         }
      }
      else
      {
 	  /* Do Nothing */
 	 }

     }
     /*Crc_StartValue32 = u32ReflectData(Crc_StartValue32, u8RES_REFLECT_LENGTH);*/
     FLIP_32(Crc_StartValue32, temp32);
     Crc_StartValue32 = temp32;
 #endif

 #if (CRC_32_MODE == CRC_32_TABLE)
   if (TRUE == Crc_IsFirstCall)
   {
     /* !Set CRC Start value to the intial value						  */
     Crc_StartValue32 = CRC_INITIAL_VALUE32;
   }
   else
   {
     /* undo the XOR on the start value */
     Crc_StartValue32 ^= u32THIRTYTWO_XOR;
	 /*printf("Check point 2: %X \n", Crc_StartValue32);*/

     /* The reflection of the initial value is not necessary here as we used
      * the "reflected" algorithm and reflected table values. */
   }

   /* Process all data byte-wise */
   for (u32Index = 0; u32Index < Crc_Length; u32Index++)

   {

 #if (Crc_u8TABLE32_SIZE == 16U) /* CRC32 generation via small lookup table */

    /* Process Most Significant Four bits of the data byte */
     if (Crc_DataPtr != NULL_PTR )
 	 {
    Crc_StartValue32
      = aku32Table[(u8TABLE_32_MASK) & (Crc_StartValue32 ^ *Crc_DataPtr)]
      ^ (Crc_StartValue32 >> u8TABLE_32_SHIFT_FOUR);
	/*printf("Chck point 3: %X \n", Crc_StartValue32);
	if(Crc_StartValue32 == 0xF7E79BB6) printf("HERE : %X \n", *Crc_DataPtr);*/

    /* Process Least Significant Four bits of the data byte */
    Crc_StartValue32
      = aku32Table[
        (u8TABLE_32_MASK) & ((Crc_StartValue32) ^ ((uint32)(*Crc_DataPtr >> u8TABLE_32_SHIFT_FOUR)))]
      ^ (Crc_StartValue32 >> u8TABLE_32_SHIFT_FOUR);
		/*printf("Chck point 4: %X \n", Crc_StartValue32);*/
      }
 	else
 	{
 	/* Do  Nothing */
 	}


 #elif (Crc_u8TABLE32_SIZE == 256U) /* CRC32 generation via large lookup table */

    /* Process one byte of data */
       if (Crc_DataPtr != NULL_PTR )
 	 {
    Crc_StartValue32
      = aku32Table[((uint8)Crc_StartValue32) ^ *Crc_DataPtr]
      ^ (Crc_StartValue32 >> 8U);
      }
 	 else
 	 {
 	 /* Do Nothing */
 	 }
 #endif
      if (Crc_DataPtr != NULL_PTR )
 	 {
    	  ++Crc_DataPtr;
     }
 	 else
 	 {
 	 /*Do Nothing */
 	 }

 }

 #endif
     Crc_StartValue32 = Crc_StartValue32 ^ u32THIRTYTWO_XOR;
   return Crc_StartValue32; /* XOR crc value */

 #if (CRC_32_MODE != CRC_32_RUNTIME)&&(CRC_32_MODE != CRC_32_TABLE)

     #error "CRC32 mode not supported"
 #endif

 }
 #endif
