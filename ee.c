
#include "ee.h"
#include "eeConfig.h"
#include <string.h>

#define   PAGE                  0
#define   SECTOR                1
#define   PAGE_NUM              2

#if defined(STM32F103xB)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter correct address, maximum is (127)"
#endif
#endif

#if defined(STM32F103x8)
#define   _EE_SIZE          	1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter correct address, maximum is (63)"
#endif
#endif

#if defined(STM32F103xC)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter correct address, maximum is (127)"
#endif
#endif

#if defined(STM32F103xD)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 191)
#error  "Please Enter correct address, maximum is (191)"
#endif
#endif

#if defined(STM32F103xE)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 255)
#error  "Please Enter correct address, maximum is (255)"
#endif
#endif

#if defined(STM32F030x4) || defined(STM32F042x4)  || defined(STM32F070x4)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 15)
#error  "Please Enter correct address, maximum is (15)"
#endif
#endif

#if  defined(STM32F030x6) || defined(STM32F042x6) || defined(STM32F070x6)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 31)
#error  "Please Enter correct address, maximum is (31)"
#endif
#endif

#if defined(STM32F030x8) || defined(STM32F042x8)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter correct address, maximum is (63)"
#endif
#endif

#if defined(STM32F070xB)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter correct address, maximum is (63)"
#endif
#endif

#if defined(STM32F070xC)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter correct address, maximum is (127)"
#endif
#endif

#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
#define   _EE_SIZE              (1024 * 128)
#define   _EE_ADDR_INUSE        (((uint32_t)0x08020000) | (_EE_SIZE*(_EE_USE_FLASH_PAGE_OR_SECTOR - 5)))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_VOLTAGE_RANGE     _EE_VOLTAGE
#define   _EE_PAGE_OR_SECTOR    SECTOR
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 11)
#error  "Please Enter correct address, maximum is (11)"
#endif
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 5)
#error  "Please Enter correct address, minimum is (5)"
#endif
#endif

#if defined(STM32F411xC)
#define   _EE_SIZE              (1024 * 128)
#define   _EE_ADDR_INUSE        (((uint32_t)0x08020000) | (_EE_SIZE*(_EE_USE_FLASH_PAGE_OR_SECTOR - 5)))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_VOLTAGE_RANGE     _EE_VOLTAGE
#define   _EE_PAGE_OR_SECTOR    SECTOR
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 5)
#error  "Please Enter correct address, maximum is (5)"
#endif
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 5)
#error  "Please Enter correct address, minimum is (5)"
#endif
#endif

#if defined(STM32F411xE)
#define   _EE_SIZE              (1024 * 128)
#define   _EE_ADDR_INUSE        (((uint32_t)0x08020000) | (_EE_SIZE*(_EE_USE_FLASH_PAGE_OR_SECTOR - 5)))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_VOLTAGE_RANGE     _EE_VOLTAGE
#define   _EE_PAGE_OR_SECTOR    SECTOR
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 7)
#error  "Please Enter correct address, maximum is (7)"
#endif
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 5)
#error  "Please Enter correct address, minimum is (5)"
#endif
#endif

#if defined(STM32G030xx) || defined(STM32G050xx)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE_NUM
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 31)
#error  "Please Enter correct address, maximum is (31)"
#endif
#endif

#if defined(STM32G070xx)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE_NUM
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter correct address, maximum is (63)"
#endif
#endif

#if defined(STM32L433xx)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE_NUM
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter correct address, maximum is (127)"
#endif
#endif

#if defined(STM32L476xx)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 256)
#define   _EE_FLASH_BANK        FLASH_BANK_1
#else
#define   _EE_FLASH_BANK        FLASH_BANK_2
#define   _EE_PAGE_OR_SECTOR    PAGE_NUM
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 511)
#error  "Please Enter correct address, maximum is (511)"
#endif
#endif
#endif

// 2MB version
#if defined(STM32U575xx) || defined(STM32U585xx)
#define   _EE_SIZE              8192
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_ICACHE_CTRL				1
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 128)
#define   _EE_FLASH_BANK        FLASH_BANK_1
#else
#define   _EE_FLASH_BANK        FLASH_BANK_2
#define   _EE_PAGE_OR_SECTOR    PAGE_NUM
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 256)
#error  "Please Enter correct address, maximum is (255)"
#endif
#endif
#endif

#if (_EE_USE_RAM_BYTE > 0)
uint8_t ee_ram[_EE_USE_RAM_BYTE];
#endif

//##########################################################################################################
bool ee_init(void)
{
#if (_EE_USE_RAM_BYTE > 0)
  return ee_read(0, _EE_USE_RAM_BYTE, NULL);
#else
  return true;
#endif
}
//##########################################################################################################
bool ee_format(bool keepRamData)
{
  uint32_t error;
  HAL_FLASH_Unlock();
#if _EE_ICACHE_CTRL == 1
  HAL_ICACHE_Disable();
#endif
  FLASH_EraseInitTypeDef flashErase;
#if _EE_PAGE_OR_SECTOR == PAGE
	flashErase.NbPages = 1;
  flashErase.PageAddress = _EE_ADDR_INUSE;
  flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
#elif _EE_PAGE_OR_SECTOR == SECTOR
  flashErase.NbSectors = 1;
  flashErase.Sector =  _EE_USE_FLASH_PAGE_OR_SECTOR;
  flashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
#elif _EE_PAGE_OR_SECTOR == PAGE_NUM
  flashErase.NbPages = 1;
  flashErase.Page = _EE_USE_FLASH_PAGE_OR_SECTOR;
  flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
#endif
#ifdef _EE_FLASH_BANK
  flashErase.Banks = _EE_FLASH_BANK;
#endif
#ifdef _EE_VOLTAGE_RANGE
  flashErase.VoltageRange = _EE_VOLTAGE_RANGE;
#endif
  if (HAL_FLASHEx_Erase(&flashErase, &error) == HAL_OK)
  {
    HAL_FLASH_Lock();
    if (error != 0xFFFFFFFF)
    {
#if _EE_ICACHE_CTRL == 1
    HAL_ICACHE_Enable();
#endif
    	return false;
    }
    else
    {
#if (_EE_USE_RAM_BYTE > 0)
      if (keepRamData == false)
        memset(ee_ram, 0xFF, _EE_USE_RAM_BYTE);
#endif
#if _EE_ICACHE_CTRL == 1
      HAL_ICACHE_Enable();
#endif
      return true;
    }
  }
  HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
  HAL_ICACHE_Enable();
#endif
  return false;
}
//##########################################################################################################
bool ee_read(uint32_t startVirtualAddress, uint32_t len, uint8_t* data)
{
  if ((startVirtualAddress + len) > _EE_SIZE)
    return false;
  for (uint32_t i = startVirtualAddress; i < len + startVirtualAddress; i++)
  {
    if (data != NULL)
    {
      *data = (*(__IO uint8_t*) (i + _EE_ADDR_INUSE));
      data++;
    }
#if (_EE_USE_RAM_BYTE > 0)
    if (i < _EE_USE_RAM_BYTE)
      ee_ram[i] = (*(__IO uint8_t*) (i + _EE_ADDR_INUSE));
#endif
  }
  return true;
}
//##########################################################################################################
bool ee_write(uint32_t startVirtualAddress, uint32_t len, uint8_t *data)
{
  if ((startVirtualAddress + len) > _EE_SIZE)
    return false;
  if (data == NULL)
    return false;
  HAL_FLASH_Unlock();
#if _EE_ICACHE_CTRL == 1
  HAL_ICACHE_Disable();
#endif
#ifdef FLASH_TYPEPROGRAM_BYTE
  for (uint32_t i = 0; i < len ; i++)
  {		
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint64_t)(data[i])) != HAL_OK)
    {
      HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
      HAL_ICACHE_Enable();
#endif
      return false;
    }
  }	
#endif
#ifdef FLASH_TYPEPROGRAM_HALFWORD
  for (uint32_t i = 0; i < len ; i+=2)
  {		
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint64_t)(data[i] | (data[i+1] << 8))) != HAL_OK)
    {
      HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
      HAL_ICACHE_Enable();
#endif
      return false;
    }
  }	
#endif
#ifdef FLASH_TYPEPROGRAM_DOUBLEWORD
  for (uint32_t i = 0; i < len; i += 8)
  {
  	uint8_t DoubleWord[8] =
		{
			data[i + 0], data[i + 1], data[i + 2], data[i + 3], data[i + 4],\
			data[i + 5], data[i + 6], data[i + 7]
		};
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint32_t)DoubleWord) != HAL_OK)
    {
      HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
      HAL_ICACHE_Enable();
#endif
      return false;
    }
  }
#endif
#ifdef FLASH_TYPEPROGRAM_QUADWORD
  for (uint32_t i = 0; i < len; i += 16)
  {
		uint8_t QuadWord[16] =
		{
			data[i + 0], data[i + 1], data[i + 2], data[i + 3], data[i + 4],\
			data[i + 5], data[i + 6], data[i + 7], data[i + 8], data[i + 9],\
			data[i + 10], data[i + 11], data[i + 12], data[i + 13], data[i + 14],\
			data[i + 15]
		};
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint32_t)QuadWord) != HAL_OK)
    {
      HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
      HAL_ICACHE_Enable();
#endif
      return false;
    }
  }
#endif
  HAL_FLASH_Lock();
#if _EE_ICACHE_CTRL == 1
  HAL_ICACHE_Enable();
#endif
  return true;
}
//##########################################################################################################
bool ee_writeToRam(uint32_t startVirtualAddress, uint32_t len, uint8_t* data)
{
#if (_EE_USE_RAM_BYTE > 0)
  if ((startVirtualAddress + len) > _EE_USE_RAM_BYTE)
    return false;
  if (data == NULL)
    return false;
  memcpy(&ee_ram[startVirtualAddress], data, len);
  return true;
#else
  return false;
#endif
}
//##########################################################################################################
bool  ee_commit(void)
{
#if (_EE_USE_RAM_BYTE > 0)
  if (ee_format(true) == false)
    return false;
  return ee_write(0, _EE_USE_RAM_BYTE, ee_ram);
#else
  return false;
#endif
}
//##########################################################################################################
uint32_t  ee_maxVirtualAddress(void)
{
  return (_EE_SIZE);  
}
//##########################################################################################################
