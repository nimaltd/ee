#ifndef _EE_H_
#define _EE_H_

/***********************************************************************************************************

  Author:     Nima Askari
  Github:     https://www.github.com/NimaLTD
  LinkedIn:   https://www.linkedin.com/in/nimaltd
  Youtube:    https://www.youtube.com/@nimaltd
  Instagram:  https://instagram.com/github.NimaLTD

  Version:    3.1.0

  History:
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


/************************************************************************************************************
**************    Public struct/enum
************************************************************************************************************/

typedef struct
{
  uint8_t                *DataPointer;
  uint32_t               Size;

} EE_HandleTypeDef;

/************************************************************************************************************
**************    Public Functions
************************************************************************************************************/

bool      EE_Init(void *StoragePointer, uint32_t Size);
uint32_t  EE_Capacity(void);
bool      EE_Format(void);
void      EE_Read(void);
bool      EE_Write(void);

#ifdef __cplusplus
}
#endif
#endif
