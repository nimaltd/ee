# 📘 EEPROM Emulation Library for STM32

A simple and reliable **EEPROM emulation library** written in C for STM32 (HAL-based).

This library allows you to **store and retrieve non-volatile data** using the STM32's internal Flash memory — ideal for devices that do not include dedicated EEPROM.

It provides a lightweight API for **initialization, read, write, format**, and **capacity management**, making it easy to integrate into any STM32 project.

It supports all STM32 series.

---

## ✨ Features

- 🧩 Fully **blocking, synchronous** operation
- 💾 Uses **internal Flash** for data storage
- 🧱 Configurable **page/sector size** and memory layout (Auto and Manual)
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

Defines page/sector sizes and optional manual Flash configuration or Use Auto Selection (define EE_MANUAL_CONFIG = 0).  

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

## 🧰 API Overview  

| Function | Description |
|----------|-------------|
| `ee_init()` | Initialize EEPROM emulation module with a data buffer |
| `ee_capacity()` | Get total emulated EEPROM capacity (in bytes) |
| `ee_format()` | Erase and format the EEPROM area in Flash memory |
| `ee_read()` | Load data from Flash into RAM buffer |
| `ee_write()` | Save (write) the RAM buffer back to Flash memory |


---

## 🚀 Quick Start 

Use your data structure like this:

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
- For some series should enable 'EE_MANUAL_CONFIG'.

---
# Watch the Video ( Previous version ):

<div align="center">
  <a href="https://www.youtube.com/watch?v=o80ugfjuZ-o"><img src="https://img.youtube.com/vi/o80ugfjuZ-o/0.jpg" alt="Video"></a>
</div>

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

