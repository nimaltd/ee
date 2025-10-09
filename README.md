# 📘 EEPROM Emulation Library for STM32

A simple and reliable **EEPROM emulation library** written in C for STM32 (HAL-based).

This library allows you to **store and retrieve non-volatile data** using the STM32's internal Flash memory — ideal for devices that do not include dedicated EEPROM.

It provides a lightweight API for **initialization, read, write, format**, and **capacity management**, making it easy to integrate into any STM32 project.

It supports all STM32 series that include programmable Flash memory:

- 🔹 **STM32F0 / F1 / F3 / F4 / F7 / G0 / G4 / H7**
- 🔹 **STM32L0 / L4 / L5** and others

---

## ✨ Features

- 🧩 Fully **blocking, synchronous** operation
- 💾 Uses **internal Flash** for data storage
- 🧱 Configurable **page/sector size** and memory layout
- 🧠 Supports **data structure mapping** for easy use
- ⚙️ Works with both **single-bank and dual-bank Flash** configurations
- 🔐 Safe write mechanism to protect existing data
- 📂 Clean, modular, and portable API

---

## ⚙️ Installation

You can add the library to your STM32 project in two ways:

### 1. Copy files directly
Add these files to your project:
- `ee.h`
- `ee.c`
- `ee_config.h`

Include them in your application source files and compile.

### 2. STM32Cube Pack Installer (optional)
Future support will be available via the official STM32 pack repository.

---

## 🔧 Configuration (`ee_config.h`)

Defines page/sector sizes and optional manual Flash configuration.

```c
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
```

---

## 🔧 EEPROM Structure (`ee_t`)

```c
typedef struct
{
  uint8_t   *data;               // Pointer to data buffer
  uint32_t   size;               // Total data size
  uint32_t   page_sector_size;   // Flash sector/page size
  uint32_t   address;            // Base flash address
  uint8_t    page_sector_number; // Number of pages/sectors used
#if (defined FLASH_BANK_1) || (defined FLASH_BANK_2)
  uint8_t    bank_number;        // Flash bank (if dual-bank available)
#endif
} ee_t;
```

Example configuration:
```c
ee_t eeprom;
eeprom.data = my_data;
eeprom.size = sizeof(my_data);
eeprom.page_sector_size = EE_SELECTED_PAGE_SECTOR_SIZE;
eeprom.address = EE_SELECTED_ADDRESS;
eeprom.page_sector_number = EE_SELECTED_PAGE_SECTOR_NUMBER;
```

---

## 🧩 API Overview

| Function | Description |
|-----------|-------------|
| `bool ee_init(void *data, uint32_t size)` | Initializes the EEPROM emulation module |
| `uint32_t ee_capacity(void)` | Returns total emulated EEPROM capacity |
| `bool ee_format(void)` | Formats the EEPROM area (erases sectors) |
| `void ee_read(void)` | Reads data from Flash to buffer |
| `bool ee_write(void)` | Writes data buffer to Flash memory |

---

## 🚀 Quick Start

### 1. Include header
```c
#include "ee.h"
```

### 2. Define data structure
```c
uint8_t user_settings[128];
```

### 3. Initialize EEPROM
```c
ee_init(user_settings, sizeof(user_settings));
```

### 4. Read stored data
```c
ee_read();
```

### 5. Modify and write new data
```c
user_settings[0] = 0x55;
ee_write();
```

### 6. Format EEPROM (optional)
```c
ee_format();
```

---

## ⚙️ STM32CubeMX Setup

1. **Flash Configuration**
   - Ensure Flash programming is enabled.
   - Disable write protection for the EEPROM region.

2. **Memory Address**
   - Choose a free Flash area (e.g., last 2 KB).
   - Example: For STM32F103C8 (64 KB Flash) → Use `0x0800F800`.

3. **Project Settings**
   - Enable **HAL Flash** driver.
   - Use **"Generate peripheral initialization as .c/.h files per peripheral"** option in CubeMX.

---

## 💡 Notes

- Flash erase/write cycles are **limited** — avoid frequent writes.
- Use RAM buffers and **write only when data changes**.
- For dual-bank devices, use `bank_number` to select target bank.
- Supports both **small data arrays** and **structured types**.

---

## 💖 Support

If this project helped you, please **⭐ star** the repo and consider supporting:

- [![GitHub](https://img.shields.io/badge/GitHub-Follow-black?style=for-the-badge&logo=github)](https://github.com/NimaLTD)
- [![YouTube](https://img.shields.io/badge/YouTube-Subscribe-red?style=for-the-badge&logo=youtube)](https://youtube.com/@nimaltd)
- [![Instagram](https://img.shields.io/badge/Instagram-Follow-blue?style=for-the-badge&logo=instagram)](https://instagram.com/github.nimaltd)
- [![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/nimaltd)
- [![Email](https://img.shields.io/badge/Email-Contact-red?style=for-the-badge&logo=gmail)](mailto:nima.askari@gmail.com)
- [![Ko-fi](https://img.shields.io/badge/Ko--fi-Support-orange?style=for-the-badge&logo=ko-fi)](https://ko-fi.com/nimaltd)

---

## 📜 License

Licensed under the terms in the [LICENSE](./LICENSE.TXT).






















# EEPROM EMULATION Library for STM32  
---  
## Please Do not Forget to get STAR, DONATE and support me on social networks. Thank you. :sparkling_heart:  
---   
-  Author:     Nima Askari  
-  Github:     https://www.github.com/NimaLTD
-  Youtube:    https://www.youtube.com/@nimaltd  
-  LinkedIn:   https://www.linkedin.com/in/nimaltd  
-  Instagram:  https://instagram.com/github.NimaLTD  
---
> [!NOTE]
> Please Test Any MCU you have and tell me the result.

> [!CAUTION]
> EEPROM Emulation Library may not be suitable for frequent data alterations.  
---
This library facilitates EEPROM emulation on microcontrollers by selecting the latest sector or page for emulation space.
---
* Install Library from https://github.com/nimaltd/STM32-PACK/raw/main/EE/NimaLTD.I-CUBE-EE.pdsc
* Add and enable it.
* It does not need to any configuration. This Library Select the latest page/sector of the MCU.
* Generate Code.
* Set a buffer for Storing the Data ( array, struct, ...)
* Call EE_Init()

---
# Watch the Video:

<div align="center">
  <a href="https://www.youtube.com/watch?v=o80ugfjuZ-o"><img src="https://img.youtube.com/vi/o80ugfjuZ-o/0.jpg" alt="Video"></a>
</div>

---
The old Version: https://github.com/nimaltd/ee/archive/refs/tags/V2.0.6.zip

``` c
#include "ee.h"
typedef struct
{
 uint32_t val1;
 uint32_t val2;
 uint32_t val3;
 uint32_t val4;
 uint32_t val5;
 uint32_t val6;
 uint32_t val7;
 uint32_t val8;

} Stotrage_t;

Stotrage_t ee;

.
.

int main(void)
{
  .
  .
  EE_Init(&ee, sizeof(Stotrage_t));
  EE_Read();
  ee.val1 = 1;
  ee.val2 = 2;
  ee.val3 = 3;
  ee.val4 = 4;
  ee.val5 = 5;
  ee.val6 = 6;
  ee.val7 = 7;
  ee.val8 = 8;
  EE_Write();
  while (1)
  {

  }
}
```
