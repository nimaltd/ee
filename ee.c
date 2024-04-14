
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
#define EE_SIZE                             FLASH_PAGE_SIZE
#elif (EE_ERASE == EE_ERASE_SECTOR_NUMBER)
#define EE_SIZE                             FLASH_SECTOR_SIZE
#endif
#endif

#if    defined FLASH_BANK_2
#define  EE_BANK_SELECT                     FLASH_BANK_2
#elif  defined FLASH_BANK_1
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
  * @brief Initializes the EEPROM emulation module.
  * @note This function initializes the EEPROM emulation module to enable read and write operations.
  * @param StoragePointer: Pointer to the start address of the EEPROM emulation area.
  * @param Size: Size of the EEPROM emulation area in bytes.
  * @return Boolean value indicating the success of the initialization:
  *       - true: Initialization successful.
  *       - false: Initialization failed.
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
  * @brief Retrieves the capacity of the EEPROM emulation area.
  * @note This function returns the total capacity of the EEPROM emulation area in bytes.
  * @return Capacity of the EEPROM emulation area in bytes.
  */
uint32_t EE_Capacity(void)
{
  return EE_SIZE;
}

/***********************************************************************************************************/

/**
  * @brief Formats the EEPROM emulation area.
  * @note This function formats the EEPROM emulation area,
  * optionally erasing its content.
  * @param EraseBuffer Indicates whether to erase the content of the EEPROM emulation area:
  *    - true: Erase the content of the EEPROM emulation area(In RAM).
  *     - false: Do not erase the content (only format Flash).
  * @return bool Boolean value indicating the success of the operation:
  *     - true: Formatting successful.
  *     - false: Formatting failed.
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
  * @brief Reads data from the EEPROM emulation area.
  * @note This function reads data from the EEPROM emulation area
  *  and loads it into the specified storage pointer.
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
  * @brief Writes data to the EEPROM emulation area.
  * @note This function writes data to the EEPROM emulation area.
  *       Optionally, the area can be formatted first before writing.
  * @param FormatFirst: Indicates whether to format the EEPROM emulation area before writing:
  *       - true: Format the Flash area before writing.
  *       - false: Do not format the Flash area before writing.
  * @retval true if the write operation is successful, false otherwise.
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
    for (uint32_t i = 0; i < eeHandle.Size; i += FLASH_NB_32BITWORD_IN_FLASHWORD * 4)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, EE_ADDRESS + i, (uint32_t)data) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += FLASH_NB_32BITWORD_IN_FLASHWORD * 4;
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
