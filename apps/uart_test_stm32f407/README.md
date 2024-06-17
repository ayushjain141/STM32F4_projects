### Test Case Example(CE):<br>
# UART test app for STM32F407

The CE demostrates GPIO peripheral example, here character inputs from PC keyboard are received by STM32 MCU and echoed back on a serial terminal program in PC. This communication takes place over a UART link between PC and keyboard.

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

1. The UART configuaration for the test case is defined in the structure `usart1cfg` in <i>\< application >/main.c</i>.

2. Connect the `RX and Tx` of the STM32 with the corresponding `Rx and Tx` of the serial converter, and connect the converter to the PC.

3. Configure the serial terminal program in PC with the configs specified in `usart1cfg` mentioned above.

4. Upon the start of application a `Hello World !!!` message appears on the serial terminal program as shown below.

    ```
    ================
     Hello World !!!
    ================
    ```

5. After the message appears, the user can start typing characters on the PC keyboard and the echoed character can be seen printed on the serial terminal program just below the above printed lines.

6. The STM32 MCU receives the serial input from PC via the serial link into it's Rx buffer and than transmits the same buffer data back to the serial converter over it's Tx.

7. Echo from the MCU can be validated by simply disconnecting the HW connection between Tx of MCU and Rx of serial converter, after this we notice that the characters are no longer echoed back on serial terminal when typed on PC keyboard. Upon re-connecting all Rx and Tx we see that now the characters echo back again on serial terminal when typed on PC keyboard.



<br><br>
---------------------------------------------------------
## Warning
The Software(s) assosciated and referred to in this repo, authored by ayushjain141 (Email: mr.ayush141@gmail.com) is intended to work in laboratory conditions only and are not tested for any security, safety and hazardous environment applications and is not intended to be used in any such cases. The referred software does not guarantee correct working in any safety-critical systems and in medical devices, the software should be used completely at user's risk only. In case of any form of failure or circumstances arising upon usage of this software the user is the only liable party and the author is not at all liable in any case. The referred software is liable to change without any notice to anyone and the author is not at all liable in any circusmtances arising because of these changes. For this or assosciated software, hardware and documents - any commercial logos, trademarks, copyrights, names and brands may be claimed as property of their respective owners.
