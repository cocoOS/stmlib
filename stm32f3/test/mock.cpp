/*
 * mock.c
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#include "mock.h"
#include <inc/stm32f30x.h>
#include <stdint.h>
#include <inc/usb_pwr.h>
#include <inc/queue.h>
#include <inc/utilstypes.h>
#include <inc/usart.h>

static ITStatus itstatus[7] = {RESET,RESET,RESET,RESET,RESET,RESET,RESET};

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {

}


void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct) {

}


void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

}


void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

}

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    return 0;
}

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState) {
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState) {

}

void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState) {

}

void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF) {

}
uint32_t SysTick_Config(uint32_t ticks) {
 return 0;
}

void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct) {
    USARTx = USARTx;
}

void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState) {

}

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup) {

}

void NVIC_SetPriority(uint8_t IRQn, uint32_t priority) {

}

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct) {

}

uint16_t USART_ReceiveData(USART_TypeDef* USARTx) {
    return 0;
}

void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT) {

}

void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection ) {

}

void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct) {

}

void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct) {

}

void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState) {

}

ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT) {
    return itstatus[USART_IT];
}

void USART_SendData(USART_TypeDef* USARTx, uint16_t Data) {

}

void setITstatus(uint8_t it, uint8_t state) {
    itstatus[it] = state;
}

void desc_InitConfigDescriptor(void) {
}

uint8_t desc_AddEndpoint( const ep_t *ep ) {
  return 1;
}

void USB_Init(void) {
}

uint32_t usbPwr_getDeviceState() {
  return CONFIGURED;
}

uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize) {
  return 1;
}

void SetEPTxValid(uint8_t) {
}

uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer) {
  return 1;
}

void SetEPRxValid(uint8_t /*bEpNum*/) {
}

namespace utils {

template<typename T>
Queue<T>::Queue(T *buf, uint32_t sz): size(sz), head(1), tail(0), list(buf) {}

template<typename T>
Queue<T>::~Queue() {}

template<typename T>
bool Queue<T>::push(const T val) {
	if ( 0 == size ) return false;

	if (head == tail) return false;
	list[head] = val;
	head = (head+1) % size;
	return true;
}

template<typename T>
bool Queue<T>::pop(T *v) {
	uint32_t tmp = (tail+1) % size;
	if (tmp == head) return false;
	*v = list[tmp];
	tail = tmp;
	return true;
}



}

template class utils::Queue<int>;
template class utils::Queue<utils::StringMsg>;
