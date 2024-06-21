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

#include <limits.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "rcc_aj_stm32f4.h"
#include "timer_aj_stm32f4.h"
#include "delay_aj_stm32f4.h"
#include "gpio_aj_stm32f4.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
/* This is the value of HSE crystal for clock connected to STM32 MCU */
#define HSE_CLOCK_VAL                       ((uint32_t)8000000)
/* This is the value of HSI clock of STM32 MCU */
#define HSI_CLOCK_VAL                       ((uint32_t)16000000)

/*******************************************************************************
 * Function Prototypes
 *******************************************************************************/
void stm32f4_bsp_init(void);

#endif /* End of file */
