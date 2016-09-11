/*
 * usart.h
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <cstddef>
#include <inc/usartwriter.h>
#include <inc/queue.h>


namespace mcal {


class usart {
public:
    typedef usart *ptr;
    typedef uint16_t ID;

    static const uint8_t N_MAX_USARTS = 6;

    // callback interface for rx isr
    class IReaderCb {
    public:
        virtual void usart_update( usart &u, uint8_t data )=0;
    };

    static usart::ptr instance( ID id );
    void destroy();

    // readers shall inherit from this class which auto registers the reader
    // with the usart
    class reader : public IReaderCb {
    public:
        reader(usart& u);
        virtual ~reader(){}

    private:
        virtual void usart_update(usart& u, uint8_t data) {}
    };

    template<class C>
    class writer : public C {
        usart &home;
    public:
        writer( usart &u ): C(), home(u) {}
        uint16_t write( uint8_t *src, uint16_t len );
    };

    class impl_t;
    struct cfg_t;

private:

    impl_t *pimpl;
    usart( ID id );
    ~usart();

    static const cfg_t *settings[];
    static const uint16_t n_configured_usarts;
};


typedef usart::writer<mcal::hsframeprotocol> framewriter;
typedef usart::writer<mcal::noprotocol> rawwriter;


} /* namespace mcal */




#endif /* USART_H_ */
