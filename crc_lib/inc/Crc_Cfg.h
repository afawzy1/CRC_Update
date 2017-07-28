
/******************************************************************************/
/*                                                                            */
/* !Layer           : System Services Layer                                   */
/*                                                                            */
/* !Component       : Crc                                                     */
/* !Description     : The CRC SW Library is an AUTOSAR compliant Library      */
/*                    that offers services to calculate the CRC code to be    */
/*                    concatenated with data messages during communication    */
/*                    sessions.                                               */
/*                                                                            */
/* !Module          : Crc                                                     */
/* !Description     : The CRC module offers services to calculate CRC8 code,  */
/*                    CRC16 code, and CRC32 code. it also offers a serivce    */
/*                    to provide SW version information.                      */
/* !File            : Crc_Cfg.h                                               */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2008 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */

/******************************************************************************/
/* !Deviation : inhibit MISRA rule [5]: because Required for PVCS versioning  */
/* PRQA S 0288 ++                                                             */
/* PVCS Information                                                           */
/* $Archive::                                                                 */
/* $Revision::                                                                */
/*$Header:   Y:/Prod_01/B791130I0/archives/B791130I0/02_Modules/15_Crc/02_Development/02_Source_Code/01_Config_Files/Crc_Cfg.h-arc   1.2   Aug 28 2011 16:24:48   mhegazy  $                                                               */
/* PRQA S 0288 --                                                             */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/* TFR        : None                                                          */
/* Rev        : 1.1.0             R1.0.0               AR4.0        */
/* Author     : M.Hegazy                                  Date : 28/08/2011  */
/* Description: - Removed the parameter "Crc_DEV_ERROR_DETECT".           */
/******************************************************************************/
/* TFR        : None                                                          */
/* Rev        : 1.0.0             R1.0.0               AR4.0        */
/* Author     : M.Hegazy                                  Date : 09/05/2011  */
/* Description: - Added modification log.           */
/******************************************************************************/
/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

#ifndef CRC_CFG_H_
#define CRC_CFG_H_

/*============================================================================*/
/*=== Configuration Version Information ======================================*/
/*============================================================================*/
/* !Trace_To: GSCSW-CRC-SDD-001-0025                                           */

/* !Comment: This defines the value of the configuration major version        */
#define Crc_CFG_MAJOR_VERSION               0x01U

/* !Comment: This defines the value of the Configuration minor version        */
#define Crc_CFG_MINOR_VERSION               0x00U

/*===========================================================================*/
/*=== AUTOSAR Pre-Compile Attributes ========================================*/
/*===========================================================================*/

/* !Parameter: This defines the value of the preprocessor switch that           */
/*           enables or disables the usage of the GetVersion Info service.    */
/* !Range:  STD_ON,STD_OFF                                                    */
/* !Trace_To: GSCSW-CRC-SDD-001-0039                                                 */

#define CRC_VERSION_INFO_API              STD_OFF
/******************************************************************************/
/******************************************************************************/
/* !Parameter: This defines the value of the CRC_8_MODE that is supported       */
/*           by the CRC_CalculateCRC8 service.                                */
/* !Range:  CRC_8_RUNTIME,CRC_8_TABLE,CRC_8_HARDWARE            */
/* !Trace_To: GSCSW-CRC-SDD-001-0033        */

#define CRC_8_MODE                  CRC_8_RUNTIME
/******************************************************************************/
/* !Parameter: This defines the value of the CRC_8H2F_MODE that is supported  */
/*           by the CRC_CalculateCRC8H2F service.                           */
/* !Range:  CRC_8H2F_RUNTIME,CRC_8H2F_TABLE,CRC_8H2F_HARDWARE      */
/* !Trace_To: GSCSW-CRC-SDD-001-0037        */

#define CRC_8H2F_MODE               CRC_8H2F_RUNTIME
/******************************************************************************/
/* !Parameter: This defines the value of the CRC_16_MODE that is supported    */
/*           by the CRC_CalculateCRC16 service.                               */
/* !Range:  CRC_16_RUNTIME,CRC_16_TABLE,CRC_16_HARDWARE                                                              */
/* !Trace_To: GSCSW-CRC-SDD-001-0034           */

#define CRC_16_MODE                CRC_16_TABLE
/******************************************************************************/
/* !Parameter: This defines the value of the CRC_32_MODE that is supported      */
/*           by the CRC_CalculateCRC32 service.                               */
/* !Range:  CRC_32_RUNTIME,CRC_32_TABLE,CRC_32_HARDWARE                                                              */
/* !Trace_To: GSCSW-CRC-SDD-001-0035           */

#define CRC_32_MODE              CRC_32_TABLE
/******************************************************************************/
/******************************************************************************/
/* !Parameter: This defines the value of preprocessor switch that enables or    */
/*           disables the usage of CRC_u8CalculateCrcEight service            */
/* !Range:  STD_ON,STD_OFF                                                    */
/* !Trace_To:GSCSW-CRC-SDD-001-0066                                           */

#define Crc_bCALC_EIGHT_API       STD_OFF     
/******************************************************************************/
/******************************************************************************/
/* !Parameter: This defines the value of preprocessor switch that enables or    */
/*           disables the usage of CRC_u8CalculateCrcEightH2F service         */
/* !Range:  STD_ON,STD_OFF                                                    */
/* !Trace_To:GSCSW-CRC-SDD-001-0069                                           */

#define Crc_bCALC_EIGHTH2F_API    STD_OFF
/******************************************************************************/
/******************************************************************************/ 
/* !Parameter: This defines the value of preprocessor switch that enables or    */
/*           disables the usage of CRC_u16CalculateCrcSixteen service         */
/* !Range:  STD_ON,STD_OFF                                                    */
/* !Trace_To:GSCSW-CRC-SDD-001-0067                                           */

#define Crc_bCALC_SIXTEEN_API     STD_ON
/******************************************************************************/
/******************************************************************************/
/* !Parameter: This defines the value of preprocessor switch that enables or    */
/*           disables the usage of CRC_u32CalculateCrcThirtyTwo service       */
/* !Range:  STD_ON,STD_OFF                                                    */
/* !Trace_To: GSCSW-CRC-SDD-001-0068                                          */

#define Crc_bCALC_THIRTYTWO_API   STD_ON
/******************************************************************************/
/******************************************************************************/
/* !Parameter: This defines the size of the CRC_8_TABLE used                  */
/*           if the CRC_CalculateCRC8 service is enabled.                     */
/* !Range:  16 or 256                                                         */
#define Crc_u8TABLE8_SIZE          0U

/******************************************************************************/
/* !Parameter: This defines the size of of the CRC_8H2F_TABLE used            */
/*           if the CRC_CalculateCRC8H2F service is enabled                   */
/* !Range:  16 or 256                                                         */
#define Crc_u8TABLE8H2F_SIZE       0U

/******************************************************************************/
/* !Parameter: This defines the size of of the CRC_16_TABLE used              */
/*           if the CRC_CalculateCRC16 service is enabled.                    */
/* !Range:  16 or 256                                                         */
#define Crc_u8TABLE16_SIZE         16U

/******************************************************************************/
/* !Parameter: This defines the size of of the CRC_32_TABLE used              */
/*           if the CRC_CalculateCRC32 service is enabled.                    */
/* !Range:  16 or 256                                                         */
#define Crc_u8TABLE32_SIZE         16U



#endif /*CRC_CFG_H_*/

      
