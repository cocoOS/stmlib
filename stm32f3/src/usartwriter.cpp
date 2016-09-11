/*
 * usartwriter.cpp
 *
 *  Created on: 9 mar 2014
 *      Author: peter
 */

#include <inc/usartwriter.h>
#include <string.h>

namespace mcal {



hsframeprotocol::hsframeprotocol()  {
}

hsframeprotocol::~hsframeprotocol() {
}

uint16_t hsframeprotocol::write(uint8_t *dst, const uint8_t *src, uint16_t len) {
    const uint8_t *d = src;
    uint8_t *o = dst;

    *o++ = _sof;
    while ( len ) {
        if (( _sof == *d ) || ( _eof == *d ) || ( _dle == *d )) {
            *o++ = _dle;
            *o++ = *d ^ 0x20;
        }
        else {
            *o++ = *d;
        }
        d++;
        len--;
    }

    *o++ = _eof;
    return (o-dst);
}




noprotocol::noprotocol()  {
}

noprotocol::~noprotocol() {
}

uint16_t noprotocol::write(uint8_t *dst, const uint8_t *src, uint16_t len) {

    memcpy(dst,src,len);

    return len;
}




} /* namespace mcal */
