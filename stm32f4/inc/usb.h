/*
 * usart.h
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#ifndef USB_H_
#define USB_H_

#include <stdint.h>
#include <cstddef>



namespace mcal {


class usb {
public:
    typedef usb *ptr;

    struct observer {
        virtual void update( uint8_t id ) = 0;
    };

    static usb::ptr instance();
    void attach( usb::observer *ob );
    void write( uint8_t epi, const uint8_t data[], uint16_t len);
    uint16_t read(uint8_t epi, uint8_t data[]);

    class impl_t;
    struct cfg_t;

private:
    usb(const usb&); ///< no copy
    const usb &operator=(const usb&);
    impl_t *pimpl;
    usb();
    ~usb();

    static const cfg_t *settings[];
};


} /* namespace mcal */




#endif /* USB_H_ */
