/*******************************************************************************
* File Name:	main.c
*
* Description:	This is the source code for the UART peripheral test application
* for STM32F407 MCU.
*
* Related Document: See README.md
*
*******************************************************************************/
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "bsp_aj_stm32f4.h"
#include "usart_aj_stm32f4.h"
#include "delay_aj_stm32f4.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define USART_INSTANCE                      (USART1)      
#define USART_TX_PORT						(GPIOA)
#define USART_TX_PIN						(9)
#define USART_RX_PORT						(GPIOA)
#define USART_RX_PIN						(10)
#define UART_RX_INTR_INST                   (USART1_IRQn)


/*******************************************************************************
 * Global Variables
 *******************************************************************************/
uint8_t rx_data = 0;
bool rx_intr_flag = 0;


/*******************************************************************************
 * Function Name: USART1_IRQHandler()
 *******************************************************************************
 * Summary:
 *  ISR for USART1 interrupt.
 *
 * Parameters:
 *  void
 *
 * Return :
 *  void
 *
 ******************************************************************************/
void USART1_IRQHandler(void)
{
    /* If RX operation complete, received data can be safely read. */
    if(USART1->SR & (1U << USART_SR_RXNE_Pos))
    {
        rx_data = USART1->DR;
        rx_intr_flag = 1;
    }
}

/*******************************************************************************
 * Function Name: main()
 *******************************************************************************
 * Summary:
 *  This is the main function. It prints a message on the serial terminal using
 *  re-targeted printf().
 *
 * Parameters:
 *
 * Return :
 *  int
 *
 ******************************************************************************/
int main()
{
    /* Initialize the BSP */
    stm32f4_bsp_init();

    /* Define the USART configs */
    usart_config_st_t usart1cfg = {
        .compatmode = USART_COMPATIBLE_MODE_ASYNC,
        .stopbits = USART_STOPBIT_1,
        .txrxmode = USART_TXRX_MODE_RX_TX_BOTH_EN,
        .hwflowctrl = USART_FLOWCTRL_NONE,
        .instance = USART_INSTANCE,
        .baudrate = 115200,
        .wordlen = USART_WORD_LEN_8_BIT,
        .oversample = USART_OVERSAMPLE_BY_16,
        .parity_en = USART_PARITY_DISABLE,
        .parity = 0,
    };

    usart_config_st_t *usart1cfg_ptr = &usart1cfg;

    /* Config the USART channel */
    usart_config(usart1cfg_ptr, USART_TX_PORT, USART_TX_PIN, USART_RX_PORT, USART_RX_PIN);

    /* Initialize the USART channel */
    usart_init(usart1cfg_ptr);

	/* Initialize the UART RX interrupt */
    uart_rx_interrupt_set(usart1cfg_ptr->instance, 1);

    __disable_irq();

	NVIC_SetPriority(UART_RX_INTR_INST, 3);
	
    NVIC_EnableIRQ(UART_RX_INTR_INST);

    __enable_irq();

    while(1)
    {
        if(1 == rx_intr_flag)
        {
            uart_transmit_blocking(usart1cfg_ptr, &rx_data, 1, 0);
            rx_intr_flag = 0;
        }
    }
}
