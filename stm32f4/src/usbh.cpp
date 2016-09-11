/*
 * usb.cpp
 *
 *  Created on: 14 sep 2014
 *      Author: peter
 */

#include <inc/usbh.h>
#include <usbh_core.h>
#include <usbh_msc_core.h>
#include <usbh_def.h>



USB_OTG_CORE_HANDLE USB_OTG_Core;
USBH_HOST USB_Host;

namespace mcal {


usbh::usbh() {
}


usbh::~usbh() {
}

void usbh::init(USBH_Usr_cb_TypeDef *usr_cb) {
  USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &USBH_MSC_cb, usr_cb);
}

uint8_t usbh::service() {
  USBH_Process(&USB_OTG_Core, &USB_Host);
  return 0;
}


}

