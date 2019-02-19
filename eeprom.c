
#include "eeprom.h"
#include "eepromConfig.h"

#if 	( _EEPROM_F1_LOW_DESTINY==1)
#define		_EEPROM_FLASH_PAGE_SIZE								1024
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>31)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 31)"
#endif
#endif


#if  (_EEPROM_F1_MEDIUM_DESTINY==1)
#define		_EEPROM_FLASH_PAGE_SIZE								1024
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>127)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 127)"
#endif
#endif


#if  (_EEPROM_F1_HIGH_DESTINY==1)
#define		_EEPROM_FLASH_PAGE_SIZE								2048
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 2 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>255)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 255)"
#endif
#endif

#if (_EEPROM_F030x4_F030x6_F070x6_F030x8==1)
#define		_EEPROM_FLASH_PAGE_SIZE								1024
/* Base address of the Flash sectors */
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 2 Kbytes */
#define _EEPROM_FLASH_PAGE_ADDRESS    (ADDR_FLASH_PAGE_0|(_EEPROM_FLASH_PAGE_SIZE*_EEPROM_USE_FLASH_PAGE))
#if (_EEPROM_USE_FLASH_PAGE>63)
#error  "Please Enter currect value _EEPROM_USE_FLASH_PAGE  (0 to 63)"
#endif
#endif

#if (_EEPROM_AUTO_ERASE___NEED_MORE_RAM==1)
uint32_t	EEPROMPageBackup[_EEPROM_FLASH_PAGE_SIZE/4];
#endif

//##########################################################################################################
//##########################################################################################################
//##########################################################################################################
bool	EE_Format(void)
{
	uint32_t	error;
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef	flashErase;
	flashErase.NbPages=1;
	#if ( _EEPROM_F1_LOW_DESTINY==1 || _EEPROM_F1_MEDIUM_DESTINY==1 || _EEPROM_F1_HIGH_DESTINY==1 )
	flashErase.Banks = FLASH_BANK_1;
	#endif
	flashErase.PageAddress = _EEPROM_FLASH_PAGE_ADDRESS;
	flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
	if(HAL_FLASHEx_Erase(&flashErase,&error)==HAL_OK)
	{
		HAL_FLASH_Lock();
		if(error != 0xFFFFFFFF)
			return false;
		else
			return true;	
	}
	HAL_FLASH_Lock();
	return false;	
}
//##########################################################################################################
bool EE_Read(uint16_t VirtualAddress, uint32_t* Data)
{
	if(VirtualAddress >=	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	*Data =  (*(__IO uint32_t*)((VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS));
	return true;
}
//##########################################################################################################
bool EE_Write(uint16_t VirtualAddress, uint32_t Data)
{
	if(VirtualAddress >=	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;

	#if (_EEPROM_AUTO_ERASE___NEED_MORE_RAM==1)
	if((*(__IO uint32_t*)((VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS)) != 0xFFFFFFFF)
	{
		
		if( EE_Reads(0,(_EEPROM_FLASH_PAGE_SIZE/4),EEPROMPageBackup)==false)
		{
			HAL_FLASH_Lock();
			return false;
		}
		EEPROMPageBackup[VirtualAddress]=Data;
		EE_Format();
		
		HAL_FLASH_Unlock();
		for(uint16_t	i=0 ; i<_EEPROM_FLASH_PAGE_SIZE/4 ; i++)
		{
      if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(i*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)EEPROMPageBackup[i])!=HAL_OK)
			{
				HAL_FLASH_Lock();
				return false;
			}			
		}
	}	
	#endif
	HAL_FLASH_Unlock();
	if(Data!=0xFFFFFFFF)
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(VirtualAddress*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)Data)==HAL_OK)
		{
			HAL_FLASH_Lock();
			return true;
		}
		else
		{
			HAL_FLASH_Lock();
			return false;
		}
	}
	HAL_FLASH_Lock();
	return true;
}
//##########################################################################################################
bool EE_Reads(uint16_t StartVirtualAddress,uint16_t HowMuchToRead,uint32_t* Data)
{
	if((StartVirtualAddress+HowMuchToRead) >	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	for(uint16_t	i=StartVirtualAddress ; i<HowMuchToRead+StartVirtualAddress ; i++)
	{
		*Data =  (*(__IO uint32_t*)((i*4)+_EEPROM_FLASH_PAGE_ADDRESS));
		Data++;
	}
	return true;
}
//##########################################################################################################
bool 	EE_Writes(uint16_t StartVirtualAddress,uint16_t HowMuchToWrite,uint32_t* Data)
{
	if((StartVirtualAddress+HowMuchToWrite) >	(_EEPROM_FLASH_PAGE_SIZE/4))
		return false;
	#if (_EEPROM_AUTO_ERASE___NEED_MORE_RAM==1)
	if( EE_Reads(0,(_EEPROM_FLASH_PAGE_SIZE/4),EEPROMPageBackup)==false)
		return false;
	for(uint16_t	i=StartVirtualAddress ; i<HowMuchToWrite+StartVirtualAddress ; i++)
	{
		EEPROMPageBackup[i]=*Data;	
		Data++;
	}	
	if(EE_Format()==false)
		return false;
	#endif
	HAL_FLASH_Unlock();
	#if (_EEPROM_AUTO_ERASE___NEED_MORE_RAM==1)
	for(uint16_t	i=0 ; i<(_EEPROM_FLASH_PAGE_SIZE/4); i++)
	{		
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(i*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)EEPROMPageBackup[i])!=HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}
	}
	#else
	HAL_FLASH_Unlock();
	for(uint16_t i=0; i<HowMuchToWrite ; i++)
	{		
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,((i+StartVirtualAddress)*4)+_EEPROM_FLASH_PAGE_ADDRESS,(uint64_t)Data[i])!=HAL_OK)
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
uint16_t	EE_GetSize(void)
{
	return _EEPROM_FLASH_PAGE_SIZE;	
}
//##########################################################################################################
