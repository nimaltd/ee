
/*
 * @file        ee.c
 * @brief       EEPROM Emulation library
 * @author      Nima Askari
 * @version     4.0.0
 * @license     See the LICENSE file in the root folder.
 *
 * @note        All my libraries are dual-licensed.
 *              Please review the licensing terms before using them.
 *              For any inquiries, feel free to contact me.
 *
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * Copyright (C) 2025 Nima Askari - NimaLTD. All rights reserved.
 */

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include "ee_config.h"
#include "ee.h"
#include <string.h>

/*************************************************************************************************/
/** Private Definitions **/
/*************************************************************************************************/

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
#define FLASH_SIZE                          ((((uint32_t)(*((uint16_t *)FLASHSIZE_BASE)) & (0xFFFFU))) * 1024)
#endif

#ifdef  STM32F7
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
#endif

#ifdef  STM32H5
#define EE_ERASE                            EE_ERASE_SECTOR_NUMBER
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
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
#endif

#ifdef  STM32L1
#define EE_ERASE                            EE_ERASE_PAGE_ADDRESS
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

#ifndef EE_ERASE
#error "Not Supported MCU!"
#endif

/*************************************************************************************************/
/** Private Variables **/
/*************************************************************************************************/

ee_t ee_handle;

/*************************************************************************************************/
/** Function Implementations **/
/*************************************************************************************************/

/*************************************************************************************************/
/**
 * @brief Initializes the EEPROM emulation module.
 * @param[in] data: Pointer to the start address of the EEPROM emulation area.
 * @param[in] size: Size of the EEPROM emulation area in bytes.
 * @return bool true if successful.
 */
bool ee_init(void *data, uint32_t size)
{
  bool answer = false;
  assert_param(data != NULL);
  assert_param(size != 0);

  do
  {
#if (EE_MANUAL_CONFIG == 0)
#if (EE_ERASE == EE_ERASE_PAGE_NUMBER) || (EE_ERASE == EE_ERASE_PAGE_ADDRESS)
#ifdef FLASH_PAGE_SIZE
    ee_handle.page_sector_size = FLASH_PAGE_SIZE;
#endif
#elif (EE_ERASE == EE_ERASE_SECTOR_NUMBER)
#if defined FLASH_SECTOR_SIZE
    ee_handle.page_sector_size = FLASH_SECTOR_SIZE;
#else
#error EE Library should be set manually for your MCU!
#endif
#endif
#if defined FLASH_BANK_2
    ee_handle.bank_number = FLASH_BANK_2;
    ee_handle.page_sector_number = ((FLASH_SIZE / ee_handle.page_sector_size / 2) - 1);
    ee_handle.address = (FLASH_BASE + ee_handle.page_sector_size * (ee_handle.page_sector_number * 2 + 1));
#elif defined FLASH_BANK_1
    ee_handle.bank_number = FLASH_BANK_1;
    ee_handle.page_sector_number = ((FLASH_SIZE / ee_handle.page_sector_size) - 1);
    ee_handle.address = (FLASH_BASE + ee_handle.page_sector_size * ee_handle.page_sector_number);
#else
    ee_handle.page_sector_number = ((FLASH_SIZE / ee_handle.page_sector_size) - 1);
    ee_handle.address = (FLASH_BASE + ee_handle.page_sector_size * ee_handle.page_sector_number);
#endif
/* Manual Config */
#else
#if (defined FLASH_BANK_1) || (defined FLASH_BANK_2)
    ee_handle.bank_number = EE_SELECTED_BANK;
#endif
    ee_handle.page_sector_number = EE_SELECTED_PAGE_SECTOR_NUMBER;
    ee_handle.page_sector_size = EE_SELECTED_PAGE_SECTOR_SIZE;
    ee_handle.address = EE_SELECTED_ADDRESS;
#endif
    /* checking size of eeprom area*/
    if (size > ee_handle.page_sector_size)
    {
      ee_handle.size = 0;
      ee_handle.data = NULL;
      break;
    }
    ee_handle.size = size;
    ee_handle.data = (uint8_t*)data;
    answer = true;

  } while (0);

  return answer;
}

/*************************************************************************************************/
/**
 * @brief Retrieves the capacity of the EEPROM emulation area.
 * @return uint32_t Capacity of the EEPROM emulation area in bytes.
 */
uint32_t ee_capacity(void)
{
  return ee_handle.page_sector_size;
}

/*************************************************************************************************/
/**
 * @brief Formats the EEPROM emulation area.
 * @return bool true if successful.
 */
bool ee_format(void)
{
  bool answer = false;
  uint32_t error;
  FLASH_EraseInitTypeDef flash_erase;
  do
  {
    HAL_FLASH_Unlock();
#ifdef HAL_ICACHE_MODULE_ENABLED

    /* disabling ICACHE if enabled*/
    HAL_ICACHE_Disable();
#endif
#if EE_ERASE == EE_ERASE_PAGE_ADDRESS
    flash_erase.TypeErase = FLASH_TYPEERASE_PAGES;
    flash_erase.PageAddress = ee_handle.address;
    flash_erase.NbPages = 1;
#elif EE_ERASE == EE_ERASE_PAGE_NUMBER
    flash_erase.TypeErase = FLASH_TYPEERASE_PAGES;
    flash_erase.Page = ee_handle.page_sector_number;
    flash_erase.NbPages = 1;
#else
    flash_erase.TypeErase = FLASH_TYPEERASE_SECTORS;
    flash_erase.Sector = ee_handle.page_sector_number;
    flash_erase.NbSectors = 1;
#endif
#if (defined FLASH_BANK_1) || (defined FLASH_BANK_2)
    flash_erase.Banks = ee_handle.bank_number;
#endif
#ifdef FLASH_VOLTAGE_RANGE_3
    flash_erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
    /* erasing page/sector */
    if (HAL_FLASHEx_Erase(&flash_erase, &error) != HAL_OK)
    {
      break;
    }

    /* checking result */
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

/*************************************************************************************************/
/**
 * @brief Reads data from the EEPROM emulation area.
 */
void ee_read(void)
{
  uint8_t *data = ee_handle.data;
#ifdef HAL_ICACHE_MODULE_ENABLED
    /* disabling ICACHE if enabled*/
    HAL_ICACHE_Disable();
#endif
  if (data != NULL)
  {
    /* reading flash */
    for (uint32_t i = 0; i < ee_handle.size; i++)
    {
      *data = (*(__IO uint8_t*) (ee_handle.address + i));
      data++;
    }
  }
#ifdef HAL_ICACHE_MODULE_ENABLED

    /* disabling ICACHE if enabled*/
    HAL_ICACHE_Enable();
#endif
}

/*************************************************************************************************/
/**
 * @brief Writes data to the EEPROM emulation area.
 * @retval true if the write operation is successful, false otherwise.
 */
bool ee_write(void)
{
  bool answer = true;
  uint8_t *data = ee_handle.data;
  do
  {
    /* checking eeprom is initialize correctly */
    if (data == NULL)
    {
      answer = false;
      break;
    }

    /* formating flash area before writing */
    if (ee_format() == false)
    {
      answer = false;
      break;
    }
    HAL_FLASH_Unlock();
#ifdef HAL_ICACHE_MODULE_ENABLED

    /* disabling ICACHE if enabled*/
    HAL_ICACHE_Disable();
#endif
#if (defined FLASH_TYPEPROGRAM_HALFWORD)

    /* writing buffer to flash */
    for (uint32_t i = 0; i < ee_handle.size ; i += 2)
    {
      uint64_t half_word;
      memcpy((uint8_t*)&half_word, data, 2);
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ee_handle.address + i, half_word) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 2;
    }
#elif (defined FLASH_TYPEPROGRAM_DOUBLEWORD)

    /* writing buffer to flash */
    for (uint32_t i = 0; i < ee_handle.size; i += 8)
    {
      uint64_t double_word;
      memcpy((uint8_t*)&double_word, data, 8);
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, ee_handle.address + i, doubleWord) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 8;
    }
#elif (defined FLASH_TYPEPROGRAM_QUADWORD)

    /* writing buffer to flash */
    for (uint32_t i = 0; i < ee_handle.size; i += 16)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, ee_handle.address + i, (uint32_t)data) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += 16;
    }
#elif (defined FLASH_TYPEPROGRAM_FLASHWORD)

    /* writing buffer to flash */
    for (uint32_t i = 0; i < ee_handle.size; i += FLASH_NB_32BITWORD_IN_FLASHWORD * 4)
    {
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, ee_handle.address + i, (uint32_t)data) != HAL_OK)
      {
        answer = false;
        break;
      }
      data += FLASH_NB_32BITWORD_IN_FLASHWORD * 4;
    }
#endif
    /* verifying Flash content */
    data = ee_handle.data;
    for (uint32_t i = 0; i < ee_handle.size; i++)
    {
      if (*data != (*(__IO uint8_t*) (ee_handle.address + i)))
      {
        answer = false;
        break;
      }
      data++;
    }

  } while (0);

  HAL_FLASH_Lock();
#ifdef HAL_ICACHE_MODULE_ENABLED
  HAL_ICACHE_Enable();
#endif
  return answer;
}

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/
