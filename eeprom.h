#ifndef __EEPROM_H
#define __EEPROM_H

#include <stdbool.h>
#include "gpio.h"


//################################################################################################################
bool			EE_Format(void);
bool 			EE_Read(uint16_t VirtualAddress, uint32_t* Data);
bool 			EE_Write(uint16_t VirtualAddress, uint32_t Data);
bool			EE_Reads(uint16_t StartVirtualAddress,uint16_t HowMuchToRead,uint32_t* Data);
bool 			EE_Writes(uint16_t StartVirtualAddress,uint16_t HowMuchToWrite,uint32_t* Data);
uint16_t	EE_GetSize(void);
//################################################################################################################

#endif
