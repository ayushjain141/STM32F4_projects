/*******************************************************************************
 * File Name:    main.c
 *
 * Description:  This is the source code for the RCC peripheral test application
 * for STM32F407 MCU.
 *
 * Related Document: See README.md
 *
 ******************************************************************************/
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "bsp_aj_stm32f4.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Function Name: main()
 *******************************************************************************
 * Summary:
 *  This is the main function. It initializes GPIO pin. It also configures
 *  systick timer and initializes it.
 *
 * Parameters:
 *
 * Return :
 *  int
 *
 ******************************************************************************/
int main()
{
  bool input_btn_read = 0;
	uint32_t toggle_delay = 0;

	/* Config GPIO for LED */
	gpio_output_config(GPIOA, 7, gpio_otyper_push_pull, gpio_ospeedr_high,
										gpio_pupdr_float);
  
	/* Config GPIO for Input button */
  gpio_input_config(GPIOE, 4, gpio_pupdr_pull_up);

	/* Initialize the BSP */
  stm32f4_bsp_init();

  while (true)
  {
    input_btn_read = !(pin_read(GPIOE, 4));

    if(input_btn_read)
    {
      toggle_delay = 50;
    }

    else
    {
      toggle_delay = 2000;
    }

    #if 0
    delay_us(150);
    SET(GPIOE, 12);
    delay_us(150);
    RESET(GPIOE, 12);
    #else
    delay_ms(toggle_delay);
    SET(GPIOA, 7);
    delay_ms(toggle_delay);
    RESET(GPIOA, 7);
    #endif
  }
}
