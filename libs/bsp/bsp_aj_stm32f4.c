/*******************************************************************************
 * File Name: bsp_aj_stm32f4.c
 *
 * Description:
 *  Contains code to initialize the STM32 board hardware.
 *
 * Related Document: See README.md
 *
 *******************************************************************************/
#include "bsp_aj_stm32f4.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/

/*******************************************************************************
 * Function Name: stm32f4_bsp_init()
 ********************************************************************************
 * Summary:
 *  Initiialzes the board hardware peripherals like delay timer, RCC etc. 
 *
 * Parameters:
 *  void
 * 
 * Return :
 *  void
 *
 *******************************************************************************/
void stm32f4_bsp_init(void)
{
    delay_init(DELAY_TIM_INST);
}
