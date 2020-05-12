
#include "ee.h"
#include "eeConfig.h"
#include <string.h>

#define   PAGE                  0
#define   SECTOR                1

#if defined(STM32F103xB)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter currect address, maximum is (127)"
#endif
#endif

#if defined(STM32F103x8)
#define   _EE_MAX_SIZE          1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_MAX_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter currect address, maximum is (63)"
#endif
#endif

#if defined(STM32F103xC)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter currect address, maximum is (127)"
#endif
#endif

#if defined(STM32F103xD)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 191)
#error  "Please Enter currect address, maximum is (191)"
#endif
#endif

#if defined(STM32F103xE)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 255)
#error  "Please Enter currect address, maximum is (255)"
#endif
#endif

#if defined(STM32F030x4) || defined(STM32F042x4)  || defined(STM32F070x4)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 15)
#error  "Please Enter currect address, maximum is (15)"
#endif
#endif

#if  defined(STM32F030x6) || defined(STM32F042x6) || defined(STM32F070x6)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 31)
#error  "Please Enter currect address, maximum is (31)"
#endif
#endif

#if defined(STM32F030x8) || defined(STM32F042x8)
#define   _EE_SIZE              1024
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter currect address, maximum is (63)"
#endif
#endif

#if defined(STM32F070xB)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 63)
#error  "Please Enter currect address, maximum is (63)"
#endif
#endif

#if defined(STM32F070xC)
#define   _EE_SIZE              2048
#define   _EE_ADDR_INUSE        (((uint32_t)0x08000000) | (_EE_SIZE * _EE_USE_FLASH_PAGE_OR_SECTOR))
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 127)
#error  "Please Enter currect address, maximum is (127)"
#endif
#endif


#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
#define   _EE_SIZE              (1024 * 128)
#define   _EE_ADDR_INUSE        (((uint32_t)0x08020000) | (_EE_SIZE*(_EE_USE_FLASH_PAGE_OR_SECTOR - 5)))
#define   _EE_FLASH_BANK        FLASH_BANK_1
#define   _EE_VOLTAGE_RANGE     _EE_VOLTAGE
#define   _EE_PAGE_OR_SECTOR    PAGE
#if (_EE_USE_FLASH_PAGE_OR_SECTOR > 11)
#error  "Please Enter currect address, maximum is (11)"
#endif
#if (_EE_USE_FLASH_PAGE_OR_SECTOR < 5)
#error  "Please Enter currect address, minimum is (5)"
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
  uint32_t	error;
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef	flashErase;
  #if _EE_PAGE_OR_SECTOR == PAGE
	flashErase.NbPages = 1;
  flashErase.PageAddress = _EE_ADDR_INUSE;
  flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
  #else
  flashErase.NbSectors = 1;
  flashErase.Sector =  _EE_ADDR_INUSE;
  flashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
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
		if(error != 0xFFFFFFFF)
			return false;
		else
    {
      #if (_EE_USE_RAM_BYTE > 0)
      if (keepRamData == false)
        memset(ee_ram, 0xFF, _EE_USE_RAM_BYTE);
      #endif
			return true;	
    }
	}
	HAL_FLASH_Lock();
	return false;	
}
//##########################################################################################################
bool ee_read(uint32_t startVirtualAddress, uint32_t len, uint8_t* data)
{
	if ((startVirtualAddress + len) >	_EE_SIZE)
		return false;
	for (uint32_t	i = startVirtualAddress ; i < len + startVirtualAddress ; i++)
	{
    if (data != NULL)
    {
      *data =  (*(__IO uint8_t*)(i + _EE_ADDR_INUSE));
      data++;
    }
    #if (_EE_USE_RAM_BYTE > 0)
    if ( i < _EE_USE_RAM_BYTE)
      ee_ram[i] = (*(__IO uint8_t*)(i + _EE_ADDR_INUSE));
    #endif		
	}
	return true;
}
//##########################################################################################################
bool ee_write(uint32_t startVirtualAddress, uint32_t len, uint8_t* data)
{
	if ((startVirtualAddress + len) >	_EE_SIZE)
		return false;
  if (data == NULL)
    return false;
	HAL_FLASH_Unlock();
  #ifdef FLASH_TYPEPROGRAM_BYTE
  for (uint32_t i = 0; i < len ; i++)
	{		
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint64_t)(data[i])) != HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}
	}	
  #else
  for (uint32_t i = 0; i < len ; i+=2)
	{		
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((i + startVirtualAddress)) + _EE_ADDR_INUSE, (uint64_t)(data[i] | (data[i+1] << 8))) != HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}
	}	
  #endif  
	HAL_FLASH_Lock();
	return true;
}
//##########################################################################################################
bool ee_writeToRam(uint32_t startVirtualAddress, uint32_t len, uint8_t* data)
{
  #if (_EE_USE_RAM_BYTE > 0)
  if ((startVirtualAddress + len) >	_EE_USE_RAM_BYTE)
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
bool  ee_writeRamToFlash(void)
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
