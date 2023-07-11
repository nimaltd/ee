#ifndef __EEPROM_H
#define __EEPROM_H

/*
  Author:     Nima Askari
  WebSite:    http://www.github.com/NimaLTD
  Instagram:  http://instagram.com/github.NimaLTD
  Youtube:    https://www.youtube.com/@NimaLTD
  
  Version:    2.0.5

	(2.0.5)
  Add U575, U585.

  (2.0.4)
  Add G030, G050, G070.
	
  (2.0.3)
  Add F411.
  
  (2.0.2)
  Add L4.  
  
  (2.0.1)
  Change function name to ee_commit().
  
  Reversion History:
  (2.0.0)
  Rewrite again.

*/

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include "main.h"

//################################################################################################################
bool      ee_init(void);
bool      ee_format(bool keepRamData);
bool      ee_read(uint32_t startVirtualAddress, uint32_t len, uint8_t* data);
bool      ee_write(uint32_t startVirtualAddress, uint32_t len, uint8_t* data);
bool      ee_writeToRam(uint32_t startVirtualAddress, uint32_t len, uint8_t* data); //  only use when _EE_USE_RAM_BYTE is enabled
bool      ee_commit(void);  //  only use when _EE_USE_RAM_BYTE is enabled
uint32_t  ee_maxVirtualAddress(void);

//################################################################################################################

#ifdef __cplusplus
}
#endif

#endif
