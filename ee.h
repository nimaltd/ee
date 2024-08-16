#ifndef _EE_H_
#define _EE_H_

/***********************************************************************************************************

  Author:     Nima Askari
  Github:     https://www.github.com/NimaLTD
  LinkedIn:   https://www.linkedin.com/in/nimaltd
  Youtube:    https://www.youtube.com/@nimaltd
  Instagram:  https://instagram.com/github.NimaLTD

  Version:    3.2.1
  
  History:
              3.2.1
              - Fixed Selecting BANK for STM32W Series

              3.2.0
              - Added Manual Configuration

              3.1.3
              - Fixed L0, L1 configuration
        
              3.1.2
              - Fixed H5 configuration

              3.1.1
              - Fixed formatting F4

              3.1.0
              - Added Verify after Writing
              - Added Checking Pointer in Reading/Writing
              - Removed erasing buffer and formating before write

              3.0.2
              - Fixed Writing for H7B 

              3.0.1
              - Added comments
              
              3.0.0
              - Rewrite again
              - Support STM32CubeMx Packet installer

***********************************************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/************************************************************************************************************
**************    Include Headers
************************************************************************************************************/

#include <stdbool.h>
#include "main.h"

/************************************************************************************************************
**************    Public Definitions
************************************************************************************************************/

// none

/************************************************************************************************************
**************    Public struct/enum
************************************************************************************************************/

typedef struct
{
  uint8_t                *pData;
  uint32_t               Size;
  uint32_t               PageSectorSize;
  uint32_t               Address;
  uint8_t                PageSectorNumber;
#if (defined FLASH_BANK_1) || (defined FLASH_BANK_2)
  uint8_t                BankNumber;
#endif

} EE_HandleTypeDef;

/************************************************************************************************************
**************    Public Functions
************************************************************************************************************/

bool      EE_Init(void *pData, uint32_t Size);
uint32_t  EE_Capacity(void);
bool      EE_Format(void);
void      EE_Read(void);
bool      EE_Write(void);

#ifdef __cplusplus
}
#endif
#endif
