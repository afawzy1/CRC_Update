/******************************************************************************/
/*                                                                            */
/* !Layer           : Services Layer                                   */
/*                                                                            */
/* !Component       : Crc                                                      */
/* !Description     : AutOSAR Cyclic Redundant Check component              */
/*                                                                            */
/* !Module          : Crc                                                      */
/* !Description     : Cyclic Redundant Check main module                          */
/*                                                                            */
/* !File            : Crc_Types.h                                              */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2008 VALEO - All Rights Reserved                                 */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* !Deviation : Inhibit MISRA rule [0288]: Dollar sign is needed by           */
/*              configuration management tool (PVCS)                          */
/* PRQA S 0288 ++                                                             */
/* $Header:   Y:/Prod_01/B791130I0/archives/B791130I0/03_Integration/04_Tools/Tresos/plugins/Crc_VALEO_AR402/include/Crc_Types.h-arc   1.0   Apr 04 2013 19:31:02   mashmawy  $
*******************************************************************************/
/* PRQA S 0288 --                                                             */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/* TFR        : None                                                          */
/* Rev        : 1.1             R1.0.0               AR4.0        */
/* Author     : M.Hegazy                                  Date : 14/09/2011  */
/* Description: - Removed "BASIS" word from the file.           */
/******************************************************************************/
/* TFR        : None                                                          */
/* Rev        : 1.0.0             R1.0.0               AR4.0        */
/* Author     : M.Hegazy                                  Date : 09/05/2011  */
/* Description: - Initial Release for AUTOSAR Release 4.0.           */
/******************************************************************************/
 
#ifndef CRC_TYPES_H
#define CRC_TYPES_H

/*-- Include Component Externals --*/
/* !Trace_To:  GSCSW-CRC-SDD-001-0030                                                 */
#include "Std_Types.h"


/*===========================================================================*/
/*=== Enumeration Defines ===================================================*/
/*===========================================================================*/
/* !MComment : Enumeration fields for CRC_8_MODE                  */
/* !Trace_To: GSCSW-CRC-SDD-001-0080                                      */
/* !Comment: Defines the value of the runtime mode for crc8                   */
#define CRC_8_RUNTIME                   0x00

/* !Comment:  Defines the value of the HW mode for crc8                       */
#define CRC_8_HARDWARE                  0x01

/* !Comment:  Defines the value of the table mode for crc8                    */
#define CRC_8_TABLE                     0x02
/******************************************************************************/
/* !MComment : Enumeration fields for CRC_8H2F_MODE                  */
/* !Trace_To: GSCSW-CRC-SDD-001-0087                                      */
/* !Comment: Defines the value of the runtime mode for crc8H2F                */
#define CRC_8H2F_RUNTIME                0x00

/* !Comment:  Defines the value of the HW mode for crc8H2F                    */
#define CRC_8H2F_HARDWARE               0x01

/* !Comment:  Defines the value of the table mode for crc8H2F                 */
#define CRC_8H2F_TABLE                  0x02
/******************************************************************************/
/* !MComment : Enumeration fields for CRC_16_MODE     */
/* !Trace_To:GSCSW-CRC-SDD-001-0083                                       */
/* !Comment:  Defines the value of the runtime mode for crc16                 */
#define CRC_16_RUNTIME                  0x00

/* !Comment: Defines the value of the HW mode for crc16                       */
#define CRC_16_HARDWARE                 0x01

/* !Comment: Defines the value of the TABLE mode for crc16                    */
#define CRC_16_TABLE                    0x02
/******************************************************************************/
/* !MComment : Enumeration fields for CRC_32_MODE            */
/* !Trace_To: GSCSW-CRC-SDD-001-0086                                      */
/* !Comment:  Defines the value of the runtime mode for crc32                 */
#define CRC_32_RUNTIME                  0x00

/* !Comment:  Defines the value of the HW mode for crc32                      */
#define CRC_32_HARDWARE                 0x01

/* !Comment:   Defines the value of the table mode for crc32                  */
#define CRC_32_TABLE                    0x02


#endif /* CRC_TYPES_H */

/*==== End of File ==========================================================*/
