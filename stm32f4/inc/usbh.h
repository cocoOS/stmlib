/*
 * usbh.h
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#ifndef USBH_H_
#define USBH_H_

#include <stdint.h>
#include <usbh_core.h>


namespace mcal {


class usbh {
public:
  usbh();
  ~usbh();

  void init(USBH_Usr_cb_TypeDef *usr_cb);
  uint8_t service();

private:
    usbh(const usbh&); ///< no copy
    const usbh &operator=(const usbh&);

};


} /* namespace mcal */




#endif /* USBH_H_ */
