/*
 * mock.h
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#ifndef _MOCK_H
#define _MOCK_H

#include <stdint.h>
#include <inc/stm32f30x.h>

#define __IO volatile

#ifdef __cplusplus
extern "C" {
#endif

void setITstatus(uint8_t it, uint8_t state);

#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)
#define GPIO_AF_14            ((uint8_t)0x0E) /* USBDM, USBDP */



#ifdef __cplusplus
}
#endif

#endif
//#define SystemCoreClock  72000000


















