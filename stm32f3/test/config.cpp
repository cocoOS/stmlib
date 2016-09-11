/*
 * config.cpp
 *
 *  Created on: 10 nov 2013
 *      Author: peter
 */

#include <inc/config.h>
#include <inc/pin.h>
#include <inc/mcu.h>
#include <inc/usart.h>
#include <inc/stm32f30x.h>
#include <mock.h>

uint32_t SystemCoreClock = 72000000;
namespace mcal {

mcu::cfg_t mcuCfg = {1,true};
mcu::cfg_t *mcu::settings = &mcuCfg;

const uint16_t mcal::pin::n_configured_pins = 7;
pin::cfg_t pinCfg1 = { GPIOA, {GPIO_Pin_0,  GPIO_Mode_IN, GPIO_Speed_Level_2, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {0,0}};
pin::cfg_t pinCfg2 = { GPIOE, {GPIO_Pin_15, GPIO_Mode_OUT, GPIO_Speed_Level_2, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {0,0}};
pin::cfg_t pinCfg3 = { GPIOE, {GPIO_Pin_14, GPIO_Mode_OUT, GPIO_Speed_Level_2, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {0,0}};
pin::cfg_t pinCfg4 = { GPIOA, {GPIO_Pin_11, GPIO_Mode_AF, GPIO_Speed_Level_3, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {GPIO_PinSource11, GPIO_AF_14}};   // USB
pin::cfg_t pinCfg5 = { GPIOA, {GPIO_Pin_12, GPIO_Mode_AF, GPIO_Speed_Level_3, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {GPIO_PinSource12, GPIO_AF_14}};   // USB
pin::cfg_t pinCfg6 = { GPIOE, {GPIO_Pin_10, GPIO_Mode_OUT, GPIO_Speed_Level_2, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {0,0}};
pin::cfg_t pinCfg7 = { GPIOE, {GPIO_Pin_11, GPIO_Mode_OUT, GPIO_Speed_Level_2, GPIO_OType_PP, GPIO_PuPd_NOPULL }, {0,0}};

pin::cfg_t *pin::pinConfigs[] = { &pinCfg1, &pinCfg2, &pinCfg3, &pinCfg4, &pinCfg5, &pinCfg6, &pinCfg7};

const usb::cfg_t usbCfg0 = { { USB_LP_CAN1_RX0_IRQn, 2, 0, ENABLE },
                             { USBWakeUp_IRQn, 1 ,0 , ENABLE },
                             { EXTI0_IRQn, 0, 0, DISABLE }
                           };

const usb::cfg_t *usb::settings[] = { &usbCfg0 };



}
