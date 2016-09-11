/*
 * config.h
 *
 *  Created on: 10 nov 2013
 *      Author: peter
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#include <inc/stm32f30x.h>
#include <stdint.h>
#include <inc/pin.h>
#include <inc/mcu.h>
#include <inc/usart.h>
#include <inc/usb.h>
#include <inc/usb_type.h>



namespace mcal {

/*=====================  MCU CONFIGURATION  =====================*/

struct mcu::cfg_t {
    uint32_t systick_ms;
    bool interrupt_enable;
};

/*=====================  PORTS/PINS CONFIGURATION  =====================*/

struct af_t {
    uint16_t GPIO_PinSource;
    uint8_t GPIO_AF;
};

struct pin::cfg_t {
    GPIO_TypeDef* port;
    GPIO_InitTypeDef pcfg;
    af_t af;                ///< only used when pin configured as alternate function
};




/*=====================  USART CONFIGURATION  =====================*/

struct usart::cfg_t {
    USART_TypeDef* usart;
    USART_InitTypeDef init;
    NVIC_InitTypeDef nvic;
    uint8_t *out;
};

/*=====================  USB CONFIGURATION  =====================*/



struct usb::cfg_t {
    NVIC_InitTypeDef usbIrq;
    NVIC_InitTypeDef usbWakeupIrq;
    NVIC_InitTypeDef usbExtiIrq;
    uint8_t nEndpoints;
    const ep_t *endpoints;
};

}


#endif /* CONFIG_H_ */
