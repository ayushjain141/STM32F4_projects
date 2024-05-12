/*******************************************************************************
* File Name: bsp_aj_stm32f4.h
*
* Description:
*   Contains declarations for hardware initialization of STM32F4 hardware.
*
* Related Document: See README.md
*
*******************************************************************************/
#ifndef BSP_AJ_STM32F4
#define BSP_AJ_STM32F4

#include "rcc_aj_stm32f4.h"
#include "timer_aj_stm32f4.h"
#include "delay_aj_stm32f4.h"
#include "gpio_aj_stm32f4.h"
#include <limits.h>
#include <stdbool.h>

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void stm32f4_bsp_init(void);

#endif  /* End of file */
