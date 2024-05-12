### Code Example(CE):<br>
# Blinky app for STM32F407

The CE demostrates GPIO peripheral example, here an led is toggled with a delay period which is controlled by a user button input.

NOTE: The system core clock is configured to use PLL at 100MHz, this is implemented in the file <i>\< application >\RTE\Device\STM32F407VETx\system_stm32f4xx.c</i> in the function `SystemInit()`, this file is a part of the application.

## Software Setup 
- Tested with Keil uvision4 IDE: V5.22.0.0 (MDK522)
    - Device pack for STM32F407 in keil: STM32F4xx_DFP Version 2.14.0 (2019-07-24)
- Arm® Compiler V5.06

## Hardware setup
- <b>MCU used</b>: STM32F407
- <b>Development Board</b>: STM32 Black board with STM32F407VET6 onboard
- ST-Link utility HW for program code download to STM32 
- Signal analysis/probe tools like Saleae logic analyzer or oscilloscope

## Operation

1. Upon the start of application the user led at pin `GPIOA7` starts to toggle at frequency of `1 Hz`.

2. On pressing and holding the user button at pin `GPIOE4` the frequency of toggling changes to `20 Hz` and the led toggles at this frequency till the user-button is held pressed.

3. When the button is released, the frequency is restored to `1 Hz`.

<br><br>
---------------------------------------------------------
## Warning
The Software(s) assosciated and referred to in this repo, authored by ayushjain141 (Email: mr.ayush141@gmail.com) is intended to work in laboratory conditions only and are not tested for any security, safety and hazardous environment applications and is not intended to be used in any such cases. The referred software does not guarantee correct working in any safety-critical systems and in medical devices, the software should be used completely at user's risk only. In case of any form of failure or circumstances arising upon usage of this software the user is the only liable party and the author is not at all liable in any case. The referred software is liable to change without any notice to anyone and the author is not at all liable in any circusmtances arising because of these changes. For this or assosciated software, hardware and documents - any commercial logos, trademarks, copyrights, names and brands may be claimed as property of their respective owners.
