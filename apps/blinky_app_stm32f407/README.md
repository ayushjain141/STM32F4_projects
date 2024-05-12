### Code Example(CE):<br>
# RCC peripheral of STM32F407 

The CE demostrates several uses RCC peripheral of STM32F407 MCU.
The CE uses the library [rcc_stm32f407_lib](https://github.com/ayushjain141/rcc_stm32f407_lib) to configure the internal system clock to PLL and uses the MCO pins of STM32 to output the system clock signals, which can analyzed by logic analyzer or oscilloscope.
The systick timer of ARM© cortex© M4 in STM32 is also configured for 1 us time period and is used to generate micro-second (us) and mili-second delay (ms). To toggle GPIO, the following GPIO library in <i>\<application>/libs/gpio_stm32f407_lib </i> is used. 

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

The Following code flow is done in <i>\<application>/RTE/Device/STM32F407VETx/system_stm32f4xx.c</i><br>

1. The MCO2 channel of STM32 is configured to output the system clock on it's pin. This is done before system clock config to avoid glitches on respective pin of MCO2.

2. Flash latency configured for compensating CPU clock period and Flash memory access time, with respect to the clock which will be configured.

3. System clock is configured to run with PLL as it's source, the PLL is configured to give output clock frequency of 48MHz. Calculations for PLL configuration is done as per datasheet of STM32F407.

4. The system clock output can be measured on the MCO2 pin.

The Following code flow takes place in <i>\<application>/main.c</i>

5. The systick timer is configured for a 1 Mhz period and is used to create us and ms delay functions.

6. The macro `MILISECOND_TEST` can be used to test the milli-second or micro-second delay functionality. Please note that both the micro-second and mili-second delay can be used simultaneously also, based on the use-case. Here the macro is used for simplicity of this application only to allow uniform waveform on the GPIO pin mentioned below.

7. The pin `A7` is configured as output and is toggled with the specified delay, this pin can be probed over logic analyzer or oscilloscope for measurement of the delays.


<br><br>
---------------------------------------------------------
## Warning
The Software(s) assosciated and referred to in this repo, authored by ayushjain141 (Email: mr.ayush141@gmail.com) is intended to work in laboratory conditions only and are not tested for any security, safety and hazardous environment applications and is not intended to be used in any such cases. The referred software does not guarantee correct working in any safety-critical systems and in medical devices, the software should be used completely at user's risk only. In case of any form of failure or circumstances arising upon usage of this software the user is the only liable party and the author is not at all liable in any case. The referred software is liable to change without any notice to anyone and the author is not at all liable in any circusmtances arising because of these changes. For this or assosciated software, hardware and documents - any commercial logos, trademarks, copyrights, names and brands may be claimed as property of their respective owners.
