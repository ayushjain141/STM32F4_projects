/*******************************************************************************
 * File Name:    main.c
 *
 * Description:  This is the source code for the GPIO peripheral test application
 *               for STM32F407 MCU.
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
#define USER_LED_PORT                       (GPIOA)
#define USER_LED_PIN                        (7U)
#define USER_BTN_PORT                       (GPIOE)
#define USER_BTN_PIN                        (4U)
#define USER_BTN_INTR_INST                  (EXTI4_IRQn)
#define USR_BTN_INTR_PRIORITY               (3U)
#define LED_BLINK_DELAY_NUM                 (3U)
#define LED_BLINK_FIRST_DELAY               (50U)
#define LED_BLINK_SECOND_DELAY              (500U)
#define LED_BLINK_THIRD_DELAY               (2000U)


/*******************************************************************************
 * Global Variables
 ******************************************************************************/
/* Contains delay values for LED blinking, will be used like a cicrcular buffer.
 */
const uint32_t delay_arr[] = {LED_BLINK_FIRST_DELAY, LED_BLINK_SECOND_DELAY,
                              LED_BLINK_THIRD_DELAY};

volatile uint32_t delay_select = 0;


/*******************************************************************************
 * Function Name: EXTI4_IRQHandler()
 *******************************************************************************
 * Summary:
 * ISR for user button interrupt. When the user button is pressed this ISR
 * modifies the delay value.
 *
 * Parameters:
 * void
 *
 * Return :
 * void
 *
 ******************************************************************************/
void EXTI4_IRQHandler(void)
{
  /* Check if the desired user-button pressed. */
  if (EXTI->PR & (1U << USER_BTN_PIN))
  {
    /* Change the delay to next value. Here "delay_arr" used like a circular
     * buffer. */
    delay_select = (delay_select + 1) % LED_BLINK_DELAY_NUM;
  }

  /* Clear the pending interrupt bit. */
  EXTI->PR |= (1U << USER_BTN_PIN);
}


/*******************************************************************************
 * Function Name: main()
 *******************************************************************************
 * Summary:
 * This is the main function. It initializes GPIO pin and BSP. Also configures
 * interrupt for user button. The defined user LED blinks with a delay interval,
 * which can be modified by the user button press.
 *
 * Parameters:
 *
 * Return :
 * int
 *
 ******************************************************************************/
int main()
{
  /* User-button interrupt configuration settings. */
  static gpio_intr_config_t usr_btn_intr_conf = {
      .rising_edge = 0,
      .falling_edge = 1,
  };

  /* Initialize the BSP. */
  stm32f4_bsp_init();

  /* Config GPIO for LED. */
  gpio_output_config(USER_LED_PORT, USER_LED_PIN, gpio_otyper_push_pull,
                     gpio_ospeedr_high, gpio_pupdr_float);

  /* Config GPIO for Input button. */
  gpio_input_config(USER_BTN_PORT, USER_BTN_PIN, gpio_pupdr_pull_up);

  /* Config Input button interrupt. */
  config_gpio_interrupt(USER_BTN_PORT, USER_BTN_PIN,
                        &usr_btn_intr_conf);

  /* Disable global interrupts. */
  __disable_irq();

  /* Set user button (GPIO) priority. */
  NVIC_SetPriority(USER_BTN_INTR_INST, USR_BTN_INTR_PRIORITY);

  /* Enable user button (GPIO). */
  NVIC_EnableIRQ(USER_BTN_INTR_INST);

  /* Enable global interrupts. */
  __enable_irq();

  while (true)
  {
    delay_ms(delay_arr[delay_select]);
    SET_PIN(USER_LED_PORT, USER_LED_PIN);
    delay_ms(delay_arr[delay_select]);
    RESET_PIN(USER_LED_PORT, USER_LED_PIN);
  }
}
