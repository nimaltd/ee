
/*
 * @file        ee_config.h
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

#ifndef _EE_CONFIG_H_
#define _EE_CONFIG_H_

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

/* USER CODE BEGIN EE_INCLUDES */

/* USER CODE END EE_INCLUDES */

/*************************************************************************************************/
/** Configurations **/
/*************************************************************************************************/

#define EE_PAGE_SECTOR_SIZE_1K            (1024 * 1)
#define EE_PAGE_SECTOR_SIZE_2K            (1024 * 2)
#define EE_PAGE_SECTOR_SIZE_4K            (1024 * 4)
#define EE_PAGE_SECTOR_SIZE_8K            (1024 * 8)
#define EE_PAGE_SECTOR_SIZE_16K           (1024 * 16)
#define EE_PAGE_SECTOR_SIZE_32K           (1024 * 32)
#define EE_PAGE_SECTOR_SIZE_64K           (1024 * 64)
#define EE_PAGE_SECTOR_SIZE_128K          (1024 * 128)
#define EE_PAGE_SECTOR_SIZE_256K          (1024 * 256)

/* USER CODE BEGIN EE_CONFIGURATION */

#define EE_MANUAL_CONFIG                  0
#if (EE_MANUAL_CONFIG == 1)
#define EE_SELECTED_PAGE_SECTOR_NUMBER    16
#define EE_SELECTED_PAGE_SECTOR_SIZE      EE_PAGE_SECTOR_SIZE_1K
#define EE_SELECTED_BANK                  FLASH_BANK_1
#define EE_SELECTED_ADDRESS               0x08000000
#endif

/* USER CODE END EE_CONFIGURATION */

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#endif /* _EE_CONFIG_H_ */

