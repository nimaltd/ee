
/************************************************************************************************************
**************    Include Headers
************************************************************************************************************/

#include "ee.h"
#include <string.h>

/************************************************************************************************************
**************    Private Definitions
************************************************************************************************************/

#define EE_ERASE_PAGE_ADDRESS               0
#define EE_ERASE_PAGE_NUMBER                1
#define EE_ERASE_SECTOR_NUMBER              2

#ifdef  STM32F0
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F1
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F2
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F3
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F4
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
#define EE_SIZE                             0x20000
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F7
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
#define EE_SIZE                             0x20000
#endif

#ifdef  STM32H5
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
#endif

#ifdef  STM32H7
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
#endif

#ifdef  STM32G0
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32G4
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32U0
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32U5
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32L0
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32L1
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32L4
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32L5
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32WB
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32W0
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32WBA
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#undef  FLASH_BANK_1
#endif

#ifdef  STM32WL
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifdef  STM32C0
#define EE_ERASE                            EE_ERASE_PAGE_NUMBER
#endif

#ifndef EE_SIZE
#if (EE_ERASE == EE_ERASE_PAGE_NUMBER) || (EE_ERASE == EE_ERASE_PAGE_ADDRESS)
#define EE_SIZE                           FLASH_PAGE_SIZE
#elif (EE_ERASE == EE_ERASE_SECTOR_NUMBER)
#define EE_SIZE                           FLASH_SECTOR_SIZE
#endif
#endif

#if    defined FLASH_BANK_2)
#define  EE_BANK_SELECT                     FLASH_BANK_2
#elif  (defined FLASH_BANK_1)
#define EE_BANK_SELECT                      FLASH_BANK_1
#endif

#ifndef EE_PAGE_SECTOR
#if (EE_BANK_SELECT ==  FLASH_BANK_2)
#define EE_PAGE_SECTOR                      ((FLASH_SIZE / EE_SIZE / 2) - 1)
#else
#define EE_PAGE_SECTOR                      ((FLASH_SIZE / EE_SIZE) - 1)
#endif
#endif

#ifndef EE_ADDRESS
#if (EE_BANK_SELECT !=  FLASH_BANK_2)
#define EE_ADDRESS                          (FLASH_BASE + EE_SIZE * EE_PAGE_SECTOR)
#else
#define EE_ADDRESS                          (FLASH_BASE + EE_SIZE * (EE_PAGE_SECTOR * 2 + 1))
#endif
#endif

#ifndef EE_ERASE
#error "Not Supported MCU!"
#endif

/************************************************************************************************************
**************    Private Variables
************************************************************************************************************/

EE_HandleTypeDef eeHandle;

/************************************************************************************************************
**************    Private Functions
************************************************************************************************************/


/************************************************************************************************************
**************    Public Functions
************************************************************************************************************/

/**
  * @brief  Initialize the EEPROM.
  * @note   Assign a struct/array for storing your data
  *
  * @param  StoragePointer: Pointer to Storing data
  * @param  Size: Size of Storage, It should be equal or lower than latest sector/page of selected MCU
  *
  * @retval bool: true or false
  */
bool EE_Init(void *StoragePointer, uint32_t Size)
{
  bool answer = false;
  do
  {
    if (Size > EE_SIZE)
    {
      break;
    }
    eeHandle.Size = Size;
    eeHandle.DataPointer = (uint8_t*)StoragePointer;
    answer = true;

  } while (0);

  return answer;
}

/***********************************************************************************************************/

/**
  * @brief  Get Capacity of EEPROM
  * @note   It shall return the latest sector/page size
  *
  * @retval uint32_t: Returned size in bytes
  */
uint32_t EE_Capacity(void)
{
  return EE_SIZE;
}

/***********************************************************************************************************/

/**
  * @brief  Get Capacity of EEPROM
  * @note   It shall return the latest sector/page size
  *
  * @param  EraseBuffer: Erase data buffer of Storage or not
  *
  * @retval bool: true or false
  */
bool EE_Format(bool EraseBuffer)
{
  bool answer = false;
  uint32_t error;
  FLASH_EraseInitTypeDef flashErase;
  do
  {
    HAL_FLASH_Unlock();
#ifdef HAL_ICACHE_MODULE_ENABLED
    HAL_ICACHE_Disable();
#endif
#if EE_ERASE == EE_ERASE_PAGE_ADDRESS
    flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
    flashErase.PageAddress = EE_ADDRESS;
    flashErase.NbPages = 1;
#elif EE_ERASE == EE_ERASE_PAGE_NUMBER
    flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
    flashErase.Page = EE_PAGE_SECTOR;
    flashErase.NbPages = 1;
#else
    flashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
    flashErase.Sector = EE_PAGE_SECTOR;
    flashErase.NbSectors = 1;
#endif
#ifdef EE_BANK_SELECT
    flashErase.Banks = EE_BANK_SELECT;
#endif
#ifdef FLASH_VOLTAGE_RANGE_3
    flashErase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
    if (HAL_FLASHEx_Erase(&flashErase, &error) != HAL_OK)
    {
      break;
    }
    if (error != 0xFFFFFFFF)
    {
      break;
    }
    answer = true;

  } while (0);

  HAL_FLASH_Lock();
#ifdef HAL_ICACHE_MODULE_ENABLED
  HAL_ICACHE_Enable();
#endif
  return answer;
}

/***********************************************************************************************************/

/**
  * @brief  Read all data
  * @note   Read from flash memory and fill up the buffer
  *
  * @param  none
  *
  * @retval none
  */
void EE_Read(void)
{
  uint8_t *data = eeHandle.DataPointer;
  for (uint32_t i = 0; i < eeHandle.Size; i++)
  {
    *data = (*(__IO uint8_t*) (EE_ADDRESS + i));
    data++;
  }
}

/***********************************************************************************************************/

/**
  * @brief  Write Buffer to flash memory
  * @note
  *
  * @param  FormatFirst: Format the flash before writing
  *
  * @retval bool: true or false
  */
bool EE_Write(bool FormatFirst)
{
  bool answer = true;
  uint8_t *data = eeHandle.DataPointer;
  do
  {
    if (FormatFirst)
    {
      if (EE_Format(false) == false)
      {
        answer = false;
        break;
      }
    }
    HAL_FLASH_Unlock();
#ifdef HAL_ICACHE_MODULE_ENABLED
    HAL_ICACHE_Disable();
#endif
#if (defined FLASH_TYPEPROGRAM_HALFWORD)
    for (uint32_t i = 0; i < eeHandle.Size ; i += 2)
    {
      uint64_t halfWord;
      memcpy((uint8_t*)&halfWord, data, 2);
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, EE_ADDRESS + i, halfWord) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 2;
    }
#elif (defined FLASH_TYPEPROGRAM_DOUBLEWORD)
    for (uint32_t i = 0; i < eeHandle.Size; i += 8)
    {
      uint64_t doubleWord;
      memcpy((uint8_t*)&doubleWord, data, 8);
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, EE_ADDRESS + i, doubleWord) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 8;
    }
#elif (defined FLASH_TYPEPROGRAM_QUADWORD)
    for (uint32_t i = 0; i < eeHandle.Size; i += 16)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, EE_ADDRESS + i, (uint32_t)data) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 16;
    }
#elif (defined FLASH_TYPEPROGRAM_FLASHWORD)
    for (uint32_t i = 0; i < eeHandle.Size; i += 32)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, EE_ADDRESS + i, (uint32_t)data) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 32;
    }
#endif

  } while (0);

  HAL_FLASH_Lock();
#ifdef HAL_ICACHE_MODULE_ENABLED
  HAL_ICACHE_Enable();
#endif
  return answer;
}

/***********************************************************************************************************/
