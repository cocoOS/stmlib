/*
 * usart.cpp
 *
 *  Created on: 24 nov 2013
 *      Author: peter
 */

#include <inc/usart.h>
#include <inc/config.h>
#include <new>
#include <inc/stm32f30x.h>
#include <string.h>
#include <inc/usartwriter.h>
#include <inc/queue.h>
#include <inc/utilstypes.h>

namespace mcal {



static uint8_t mempool[ mcal::usart::N_MAX_USARTS * sizeof(usart)] = {0};
static usart::ptr usart_inst[ mcal::usart::N_MAX_USARTS ] = {0};


class usart::impl_t {
    friend class usart;
    impl_t(ID id);
    ~impl_t();
    void init();
    uint8_t irqnum(ID id);
    usart::IReaderCb *reader;

public:
    void isr();
    uint8_t *out;       ///< The writer will put processed data here to be sent on usart. From cfg
    uint16_t n_write;   ///< Number of bytes to be sent from the out buffer
    uint8_t *next;      ///< Points to next byte to be sent
    uint8_t m_id;
    utils::StringMsg buffer[32];
    utils::StrQueue q;
    bool sending;
    utils::StringMsg outMsg;
};

static uint8_t implpool[ mcal::usart::N_MAX_USARTS * sizeof(usart::impl_t)] = {0};
static usart::impl_t *irq_inst[ mcal::usart::N_MAX_USARTS ] = {0};


usart::usart( ID id ) : pimpl( new( &implpool[id * sizeof(impl_t)] ) usart::impl_t(id)) {
    usart_inst[ id ] = this;
}


usart::~usart() {
    usart_inst[ pimpl->m_id ] = 0;
    this->pimpl->~impl_t();
}


usart::ptr usart::instance( ID id ) {

    if (( id >= mcal::usart::N_MAX_USARTS ) || ( id > mcal::usart::n_configured_usarts - 1 )) return 0;

    usart::ptr u = usart_inst[ id ];
    if ( u == 0 ) {
        // use placement new to create usart in the pool
        u = new( &mempool[ id * sizeof(usart) ] ) usart(id);

    }

    return u;
}


void usart::destroy() {
    if ( this ) {
        this->~usart();
    }
}

usart::impl_t::~impl_t() {
}


usart::impl_t::impl_t( ID id ) : reader(0), out(settings[id]->out), n_write(0), next(0), m_id(id), q(buffer,32), sending(false) {
    init();
    irq_inst[ irqnum(id) ] = this;
}


uint8_t usart::impl_t::irqnum( ID id ) {
    uint8_t irqn = settings[id]->nvic.NVIC_IRQChannel;
    switch (irqn) {
        case USART1_IRQn: return 0;
        case USART2_IRQn: return 1;
        case USART3_IRQn: return 2;
        case UART4_IRQn: return 3;
        case UART5_IRQn: return 4;
    }
    return 0;
}

void usart::impl_t::init() {
    USART_Init(settings[m_id]->usart, (USART_InitTypeDef*)&(settings[m_id]->init));
    NVIC_Init((NVIC_InitTypeDef*)&(settings[m_id]->nvic));
    USART_OverrunDetectionConfig(settings[m_id]->usart, USART_OVRDetection_Enable);

    // Clear RXNE flag by reading the rx register
    USART_ReceiveData(settings[m_id]->usart);

    // clear pending interrupts
    USART_ClearITPendingBit(settings[m_id]->usart,USART_IT_ORE);
    USART_ClearITPendingBit(settings[m_id]->usart,USART_IT_NE);
    USART_ClearITPendingBit(settings[m_id]->usart,USART_IT_FE);
    USART_ClearITPendingBit(settings[m_id]->usart,USART_IT_PE);

    // enable interrupts
    USART_ITConfig(settings[m_id]->usart, USART_IT_RXNE, ENABLE);
    USART_ITConfig(settings[m_id]->usart, USART_IT_PE, ENABLE);
    USART_ITConfig(settings[m_id]->usart, USART_IT_ERR, ENABLE);

    USART_ClockInitTypeDef USART_ClockInitStruct;
    USART_ClockStructInit(&USART_ClockInitStruct);
    USART_ClockInit(settings[m_id]->usart, &USART_ClockInitStruct);

    USART_Cmd(settings[m_id]->usart, ENABLE);
}

//void usart::impl_t::isr() {
//    // tx?
//    if ( SET == USART_GetITStatus(settings[m_id]->usart,USART_IT_TXE) ) {
//        if (n_write--) {
//            USART_SendData(settings[m_id]->usart, *next++);
//        }
//        else {
//            USART_ClearITPendingBit(settings[m_id]->usart, USART_IT_TXE);
//            USART_ITConfig(settings[m_id]->usart, USART_IT_TXE, DISABLE);
//        }
//
//    }
//    else if ( SET == USART_GetITStatus(settings[m_id]->usart,USART_IT_RXNE) ) {
//        uint16_t data = USART_ReceiveData(settings[m_id]->usart);
//        if ( reader ) {
//            reader->usart_update( *usart_inst[m_id], data );
//        }
//        else {
//
//        }
//    }
//}

void usart::impl_t::isr() {
    // tx?
    if ( SET == USART_GetITStatus(settings[m_id]->usart,USART_IT_TXE) ) {
        if ( n_write == 0 ) {
        	// are there messages in queue?
        	if ( q.pop(&outMsg) ) {
        		next = (uint8_t*)outMsg.data;
        		n_write = outMsg.len;

        		USART_SendData(settings[m_id]->usart, *next++);
        		n_write--;
        	}
        	else {
        		// finished
        		USART_ClearITPendingBit(settings[m_id]->usart, USART_IT_TXE);
        		USART_ITConfig(settings[m_id]->usart, USART_IT_TXE, DISABLE);
        		sending = false;
        	}
        }
        else  {
            USART_SendData(settings[m_id]->usart, *next++);
            n_write--;
        }
    }
    else if ( SET == USART_GetITStatus(settings[m_id]->usart,USART_IT_RXNE) ) {
        uint16_t data = USART_ReceiveData(settings[m_id]->usart);
        if ( reader ) {
            reader->usart_update( *usart_inst[m_id], data );
        }
        else {

        }
    }
}

usart::reader::reader(usart& u) {
    u.pimpl->reader = this;
}

//template<class C>
//uint16_t usart::writer<C>::write( uint8_t *src, uint16_t len ) {
//    home.pimpl->n_write = C::write(home.pimpl->out, src, len);
//    home.pimpl->next = home.pimpl->out;
//    if ( home.pimpl->n_write > 0 ) {
//        USART_ClearITPendingBit(settings[home.pimpl->m_id]->usart, USART_IT_TXE);
//        USART_ITConfig(settings[home.pimpl->m_id]->usart, USART_IT_TXE, ENABLE);
//    }
//
//    return home.pimpl->n_write;
//}

template<class C>
uint16_t usart::writer<C>::write( uint8_t *src, uint16_t len ) {
	utils::StringMsg msg;

	msg.len = C::write((uint8_t*)&msg.data[0], src, len);

	if (home.pimpl->q.push(msg)) {
		if (not home.pimpl->sending) {
			home.pimpl->sending = true;
			USART_ClearITPendingBit(settings[home.pimpl->m_id]->usart, USART_IT_TXE);
			USART_ITConfig(settings[home.pimpl->m_id]->usart, USART_IT_TXE, ENABLE);
		}
		return msg.len;
	}

    return 0;
}


//template<class C>
//bool usart::writer<C>::push(const UsartMsg *msg) {
//	if ( home.pimpl->q.push(msg) ) {
//		if (false == home.pimpl->sending) {
//			home.pimpl->sending = true;
//			USART_ClearITPendingBit(settings[home.pimpl->m_id]->usart, USART_IT_TXE);
//			USART_ITConfig(settings[home.pimpl->m_id]->usart, USART_IT_TXE, ENABLE);
//		}
//		return true;
//	}
//	return false;
//}

} /* namespace mcal */

template class mcal::usart::writer<mcal::hsframeprotocol>;
template class mcal::usart::writer<mcal::noprotocol>;


extern "C" {

void USART1_IRQHandler() {
    ::mcal::irq_inst[ 0 ]->isr();
}


void USART2_IRQHandler() {

}


void USART3_IRQHandler() {

}


void UART4_IRQHandler() {

}


void UART5_IRQHandler() {

}

}
