/******************************************************************************
* File Name: gpio_aj_stm32f4.c
*
* Description:
* The file contains functions related to GPIO peripheral of STM32f407.
*
* Related Document: See README.md
*
*******************************************************************************/
#include "gpio_aj_stm32f4.h"

/*******************************************************************************
* File Name: gpio_output_config()
*
* Description:
*   Configures the pin in the output mode.
*
* Related Document: See README.md
*
*******************************************************************************/
void gpio_output_config(GPIO_TypeDef* GPIOx, uint32_t gpio_pin,
                      gpio_otyper_t otyper, gpio_ospeedr_t ospeedr,
                                            gpio_pupdr_t pupdr)
{
    /* Enable clock for the GPIO, simple arithematic operations used on the 
     * GPIOx address and the hard-coded GPIO base addresses in the STM32 BSP, 
     * for ports A,B,C,D etc, see file "stm32f407xx.h" for these base addresses.
     */
    RCC->AHB1ENR |= (1 << ((GPIOx - GPIOA)/(GPIOB-GPIOA)));

    /* config mode as output in GPIO MODER config */
    GPIOx->MODER |= (GPIOx->MODER & (~(3 << gpio_pin * 2))) |
                    (1 << (gpio_pin * 2));

    /* config output type in GPIO OTYPER config */
    GPIOx->OTYPER |= (((GPIOx->OTYPER) & (~(1 << gpio_pin))) |
                     (otyper << gpio_pin));

    /* config outputspeed in GPIO OSPEEDR config */
    GPIOx->OSPEEDR |= ((GPIOx->OSPEEDR & (~(3 << (gpio_pin * 2)))) |
                      (ospeedr << (gpio_pin * 2)));

    /* config no pull-up/pull-down in GPIO PUPDR config */
    GPIOx->PUPDR |= ((GPIOx->PUPDR & (~(3 << (gpio_pin * 2)))) |
                                    (pupdr << (gpio_pin * 2)));
}

/*******************************************************************************
* File Name: gpio_input_config()
*
* Description:
*   Configures the pin in the input mode.
*
* Related Document: See README.md
*
*******************************************************************************/
void gpio_input_config(GPIO_TypeDef* GPIOx, uint32_t gpio_pin,
                       gpio_pupdr_t pupdr)
{
    /* Enable clock for the GPIO, simple arithematic operations used on the
     * GPIOx address and the hard-coded GPIO base addresses in the STM32 BSP,
     * for ports A,B,C,D etc, see file "stm32f407xx.h" for these base addresses.
     */
    RCC->AHB1ENR |= (1 << (uint8_t)((GPIOx - GPIOA)/(GPIOB-GPIOA)));

    /* config mode as input in GPIO MODER config */
    GPIOx->MODER |= ((GPIOx->MODER & (~(3 << gpio_pin * 2))) |
                    (0 << (gpio_pin * 2)));

    /* config no pull-up/pull-down in GPIO PUPDR config */
    GPIOx->PUPDR |= ((GPIOx->PUPDR & (~(3 << (gpio_pin * 2)))) |
                                    (pupdr << (gpio_pin * 2)));
}
