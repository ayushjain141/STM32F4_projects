### Test Case Example(CE):<br>
# UART based printf test app for STM32F407

The CE demostrates UART peripheral example, in this example `printf()` is retargeted to work with <b>UART</b> peripheral. This is acheived by using <i>../libs/retarget_stdio</i> library.

NOTE: The system core clock is configured to use PLL at 100MHz, this is implemented in the file <i>\< application >\RTE\Device\STM32F407VETx\system_stm32f4xx.c</i> in the function `SystemInit()`, this file is a part of the application.

## Software(SW) Setup
- Tested with Keil uvision4 IDE: V5.22.0.0 (MDK522)
    - Device pack for STM32F407 in keil: STM32F4xx_DFP Version 2.14.0 (2019-07-24)
- Arm® Compiler V5.06
- Serial Terminal PC Application - Tera Term Version 5.2

## Hardware(HW) setup
- <b>MCU used</b>: STM32F407
- <b>Development Board</b>: STM32 Black board with STM32F407VET6 onboard
- ST-Link utility HW for program code download to STM32 MCU
- USB to serial(UART) converter hardware Ex: CP2102, PL2303, FT232RL, Arduino board's serial converter HW can also be used.

## Operation

The `printf()` function from the C language's <i>stdio.h</i> is redirected to use UART peripheral by using <i>../libs/retarget_stdio</i> library. After the program runs the following output is observed on the screen, a hello world message an `int` and a `float` value get's printed.
```
----------------------------------------------
Hello World !!!   int = 141, float = 235.893240
----------------------------------------------
```


<br><br>
---------------------------------------------------------
## Warning
The Software(s) assosciated and referred to in this repo, authored by ayushjain141 (Email: mr.ayush141@gmail.com) is intended to work in laboratory conditions only and are not tested for any security, safety and hazardous environment applications and is not intended to be used in any such cases. The referred software does not guarantee correct working in any safety-critical systems and in medical devices, the software should be used completely at user's risk only. In case of any form of failure or circumstances arising upon usage of this software the user is the only liable party and the author is not at all liable in any case. The referred software is liable to change without any notice to anyone and the author is not at all liable in any circusmtances arising because of these changes. For this or assosciated software, hardware and documents - any commercial logos, trademarks, copyrights, names and brands may be claimed as property of their respective owners.
