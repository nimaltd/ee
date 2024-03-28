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
## Tested List:
- STM32F
  -  - [ ] dadad
  -  - [ ] dddddad
- [ ] STM32F0
- [ ] STM32F1
- [ ] STM32F2
- [ ] STM32F3
- [ ] STM32F4
- [ ] STM32F7
- [ ] STM32L0
- [ ] STM32L1
- [ ] STM32L4
- [ ] STM32L5 
- [x] STM32C0
- [ ] STM32G0
- [x] STM32G4
- [ ] STM32H5
- [x] STM32H7
- [ ] STM32U0
- [x] STM32U5
- [ ] STM32WB
- [ ] STM32WL
- [ ] STM32WBA
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

```
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
  EE_Write(true);
  while (1)
  {

  }
}
```
