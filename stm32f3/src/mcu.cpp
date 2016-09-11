/*
 * mcu.cpp
 *
 *  Created on: 31 okt 2013
 *      Author: peter
 */

#include <inc/mcu.h>
#include <inc/config.h>
#include <inc/stm32f30x.h>


static void initRCC();
static void runISR();

void (*callback)(void) = 0;
static uint32_t user_ticks = 0xffffffff;
static uint32_t reload = 0xffffffff;

namespace mcal {

mcu::mcu()
{
}



void mcu::initSystemClocks() {

    /* Enable the peripheral clocks */
    initRCC();

    /* Set SysTick according to the configuration */
    if ( SysTick_Config( (SystemCoreClock / 1000 ) * mcu::settings->systick_ms ) ) {
        /* Capture error */
        while (1);
    }
    NVIC_SetPriority (SysTick_IRQn, 0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}


void mcu::registerUserTick( uint32_t ticks, void (*cb)(void)) {
    user_ticks = ticks;
    callback = cb;
    reload = ticks;
}

} /* namespace mcal */



static void runISR() {

    if ( --user_ticks == 0 ) {
        user_ticks = reload;
        if ( callback ) {
            callback();
        }
    }
}

extern "C"
{
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    runISR();
}


}

static void initRCC() {
    /* GPIOE Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |
                          RCC_AHBPeriph_GPIOB |
                          RCC_AHBPeriph_GPIOC |
                          RCC_AHBPeriph_GPIOD |
                          RCC_AHBPeriph_GPIOE |
                          RCC_AHBPeriph_GPIOF, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |
                           RCC_APB1Periph_USART3 |
                           RCC_APB1Periph_UART4  |
                           RCC_APB1Periph_UART5, ENABLE);
}
