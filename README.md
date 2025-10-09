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

Defines page/sector sizes and optional manual Flash configuration or Use Auto Selection (define EE_MANUAL_CONFIG = 0). See `ee_config.h`:

```c
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


## 🧩 API Overview

> **Note:** The library uses the `EE_*` naming convention in this (new) version:

```c
bool     EE_Init(void *data, uint32_t size);   // Initialize EEPROM emulation with a RAM data buffer
uint32_t EE_Capacity(void);                    // Get total emulated EEPROM capacity (bytes)
bool     EE_Format(void);                      // Erase/format EEPROM area
void     EE_Read(void);                        // Read Flash into the provided RAM buffer
bool     EE_Write(void);                       // Write the RAM buffer back to Flash
```

---

## 🚀 Quick Start 

Use your data structure and the `EE_*` API exactly like this:

```c
#include "ee.h"

typedef struct
{
 uint32_t val1;
 int16_t val2;
 int8_t val3;
 float val4;

} stotrage_t;

stotrage_t ee_data;

int main(void)
{
  // HAL / system init ...
  // ...

  ee_init(&ee_data, sizeof(stotrage_t));
  ee_read();

  ee_data.val1 = 10000;
  ee_data.val2 = -202;
  ee_data.val3 = -3;
  ee_data.val4 = 4.5f;

  ee_write();

  while (1)
  {
    // main loop...
  }
}
```

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
