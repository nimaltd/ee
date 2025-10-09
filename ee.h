
/*
 * @file        ee.h
 * @brief       EEPROM Emulation Library
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

#ifndef _EE_H_
#define _EE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include <stdbool.h>
#include "main.h"

/*************************************************************************************************/
/** Typedef/Struct/Enum **/
/*************************************************************************************************/

/*************************************************************************************************/
/* Handle struct of EEPROM */
typedef struct
{
  uint8_t                *data;
  uint32_t               size;
  uint32_t               page_sector_size;
  uint32_t               address;
  uint8_t                page_sector_number;
#if (defined FLASH_BANK_1) || (defined FLASH_BANK_2)
  uint8_t                bank_number;
#endif

} ee_t;

/*************************************************************************************************/
/** API Functions **/
/*************************************************************************************************/

/* Initializes the EEPROM emulation module */
bool      ee_init(void *data, uint32_t size);

/* Retrieves the capacity of the EEPROM emulation area */
uint32_t  ee_capacity(void);

/* Formats the EEPROM emulation area */
bool      ee_format(void);

/* Reads data from the EEPROM emulation area */
void      ee_read(void);

/* Writes data to the EEPROM emulation area */
bool      ee_write(void);

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif
