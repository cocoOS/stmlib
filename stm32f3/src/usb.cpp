/*
 * usb.cpp
 *
 *  Created on: 14 sep 2014
 *      Author: peter
 */

#include <inc/usb.h>
#include <inc/config.h>
#include <new>
#include <inc/stm32f30x.h>
#include <string.h>
#include <inc/hw_config.h>
#include <inc/usb_init.h>
#include <inc/usb_pwr.h>
#include <inc/usb_desc.h>
#include <inc/usb_istr.h>
#include <inc/usb_regs.h>
#include <inc/usb_sil.h>

extern __IO uint8_t PrevXferComplete;

namespace mcal {

class usb::impl_t {

    public:
    friend class usb;

    impl_t();
    ~impl_t();

    void init();
    void isr( uint8_t id );

    private:
    void write( uint8_t epi, const uint8_t data[], uint16_t len);
    uint16_t read( uint8_t epi, uint8_t data[] );
    usb::observer *observer;

};

static usb::impl_t *p_impl = 0;

usb::usb() {
    static usb::impl_t impl;
    this->pimpl = &impl;
    p_impl = &impl;
}


usb::~usb() {
    this->pimpl->~impl_t();
}


usb::ptr usb::instance() {
    static usb u;
    return &u;
}


void usb::attach(usb::observer *ob) {
    pimpl->observer = ob;
}


void usb::write( uint8_t epi, const uint8_t data[], uint16_t len) {
    pimpl->write(epi,data,len);
}

uint16_t usb::read(uint8_t epi, uint8_t data[]) {
    return pimpl->read(epi,data);
}

usb::impl_t::~impl_t() {
}


usb::impl_t::impl_t() : observer(0) {
    init();
}


void usb::impl_t::init() {
    // It is assumed the pins are already setup
    Set_System();

    Set_USBClock();

    NVIC_InitTypeDef nvic = usb::settings[0]->usbIrq;
    NVIC_Init( &nvic );

    nvic = usb::settings[0]->usbWakeupIrq;
    NVIC_Init( &nvic );

    nvic = usb::settings[0]->usbExtiIrq;
    NVIC_Init( &nvic );

    // Create the configuration descriptor
    desc_InitConfigDescriptor();

    for ( int i = 0; i != usb::settings[0]->nEndpoints; ++i ) {
        desc_AddEndpoint( &usb::settings[0]->endpoints[i] );
    }

    USB_Init();

    ::mcal::pin::setPin( 3 );
    ::mcal::pin::resetPin( 1 );
    while (usbPwr_getDeviceState() != CONFIGURED ) {
    }

    ::mcal::pin::setPin( 1 );
    ::mcal::pin::resetPin( 3 );
}


void usb::impl_t::isr(uint8_t id) {
    if (observer) {
        observer->update(id);
    }
}


void usb::impl_t::write(uint8_t epi, const uint8_t data[], uint16_t len) {
    USB_SIL_Write(usb::settings[0]->endpoints[epi].number, (uint8_t*)data, len);
    SetEPTxValid(usb::settings[0]->endpoints[epi].number);
}

uint16_t usb::impl_t::read( uint8_t epi, uint8_t data[] ) {
    uint16_t result = USB_SIL_Read(usb::settings[0]->endpoints[epi].number, data);
    SetEPRxValid(usb::settings[0]->endpoints[epi].number);
    return result;
}


} /* namespace mcal */


extern "C" {

/**
  * @brief  EP1 OUT Callback Routine.
  * @param  None
  * @retval None
  */
void EP1_IN_Callback(void)
{
  mcal::p_impl->isr(1);
}

void EP2_IN_Callback(void)
{
  mcal::p_impl->isr(2);
}

void EP3_IN_Callback(void)
{
  mcal::p_impl->isr(3);
}

void EP4_IN_Callback(void)
{
  mcal::p_impl->isr(4);
}

void EP5_IN_Callback(void)
{
  mcal::p_impl->isr(5);
}

void EP6_IN_Callback(void)
{
  mcal::p_impl->isr(6);
}

void EP7_IN_Callback(void)
{
  mcal::p_impl->isr(7);
}

void EP1_OUT_Callback(void)
{
  mcal::p_impl->isr(1);
}

void EP2_OUT_Callback(void)
{
  mcal::p_impl->isr(2);
}

void EP3_OUT_Callback(void)
{
  mcal::p_impl->isr(3);
}

void EP4_OUT_Callback(void)
{
  mcal::p_impl->isr(4);
}

void EP5_OUT_Callback(void)
{
  mcal::p_impl->isr(5);
}

void EP6_OUT_Callback(void)
{
  mcal::p_impl->isr(6);
}

void EP7_OUT_Callback(void)
{
  mcal::p_impl->isr(7);
}


}
