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
 *******************************************************************************/
#define USER_LED_PORT                       (GPIOA)
#define USER_LED_PIN                        (7)
#define USER_BTN_PORT                       (GPIOE)
#define USER_BTN_PIN                        (4)
#define USER_BTN_INTR_INST                  (EXTI4_IRQn)
#define USR_BTN_INTR_PRIORITY               (3)
#define LED_BLINK_DELAY_NUM                 (3)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
const uint32_t toggle_delay[] = {50, 500, 2000};
volatile uint32_t delay_select = 0;

/*******************************************************************************
 * Function Name: EXTI4_IRQHandler()
 *******************************************************************************
 * Summary:
 *  ISR for user button interrupt.
 *
 * Parameters:
 *  void
 *
 * Return :
 *  void
 *
 ******************************************************************************/
void EXTI4_IRQHandler(void)
{
  /* Check if the desired user-button pressed */
  if (EXTI->PR & (1U << USER_BTN_PIN))
  {
    delay_select = (delay_select + 1) % LED_BLINK_DELAY_NUM;
  }

  /* Clear the pending interrupt bit. */
  EXTI->PR |= (1U << USER_BTN_PIN);
}

/*******************************************************************************
 * Function Name: main()
 *******************************************************************************
 * Summary:
 *  This is the main function. It initializes GPIO pin and BSP. Also configures
 *  interrupt for user button.
 *
 * Parameters:
 *
 * Return :
 *  int
 *
 ******************************************************************************/
int main()
{
  static gpio_intr_config_t usr_btn_intr_conf = {
      .rising_edge = 0,
      .falling_edge = 1,
  };

  /* Initialize the BSP */
  stm32f4_bsp_init();

  /* Config GPIO for LED */
  gpio_output_config(USER_LED_PORT, USER_LED_PIN, gpio_otyper_push_pull, gpio_ospeedr_high,
                     gpio_pupdr_float);

  /* Config GPIO for Input button */
  gpio_input_config(USER_BTN_PORT, USER_BTN_PIN, gpio_pupdr_pull_up);

  /* Config Input button interrupt */
  config_gpio_interrupt(USER_BTN_PORT, USER_BTN_PIN,
                        &usr_btn_intr_conf);

  __disable_irq();

  NVIC_SetPriority(USER_BTN_INTR_INST, USR_BTN_INTR_PRIORITY);

  NVIC_EnableIRQ(USER_BTN_INTR_INST);

  __enable_irq();

  while (true)
  {
    delay_ms(toggle_delay[delay_select]);
    SET(USER_LED_PORT, USER_LED_PIN);
    delay_ms(toggle_delay[delay_select]);
    RESET(USER_LED_PORT, USER_LED_PIN);
  }
}
