/*
 * usartwriter.h
 *
 *  Created on: 9 mar 2014
 *      Author: peter
 */

#ifndef USARTWRITER_H
#define USARTWRITER_H

#include <stdint.h>

namespace mcal {


struct IWrite {
    virtual uint16_t write( uint8_t *dst, const uint8_t *src, uint16_t len ) = 0;
};

class hsframeprotocol : public IWrite {
    static const uint8_t _sof = 0x7e;
    static const uint8_t _eof = 0x7f;
    static const uint8_t _dle = 0x7d;
public:
    hsframeprotocol();
    virtual ~hsframeprotocol();

protected:
    virtual uint16_t write( uint8_t *dst, const uint8_t *src, uint16_t len );

};


class noprotocol : public IWrite {

public:
    noprotocol();
    virtual ~noprotocol();

protected:
    virtual uint16_t write( uint8_t *dst, const uint8_t *src, uint16_t len );
};



} /* namespace mcal */

#endif /* USARTWRITER_H */
