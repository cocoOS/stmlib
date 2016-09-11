/**
 * @file       test_mcal.cpp
 * @author     Peter Eckstrand
 * @version    $Revision$
 * @date       $Date$
 * @par        Copyright:
 * (c) Peter Eckstrand 2013
 *
 * Unit tests for the mcal module
 */

 /*
**================================================================================
** Include files
**================================================================================
*/
#include <string.h>
#include <stdint.h>
#include "test.h"
#include "testgroups.h"
#include <inc/usart.h>
#include <inc/usartwriter.h>
#include <inc/config.h>
#include "mock.h"


using namespace mcal;


/* Tests

Instances with same ID return equal pointers                        OK
Instances with unequal ID return unequal pointers                   OK
The id can not be higher than max number of usarts                  OK
It is not possible to instantiate more than max number of usarts    OK
After deleting one usart, that one can be recreated
Reader callback called upon rx
Received data is passed to reader





*/

/*
**================================================================================
** Private type definitions
**================================================================================
*/

/*
**================================================================================
** Private constant definitions
**================================================================================
*/

/*
**================================================================================
** Private function prototypes
**================================================================================
*/



/*
**================================================================================
** Private variable declarations
**================================================================================
*/

extern "C" {
void USART1_IRQHandler(void);
}


namespace mcal {


static uint8_t txbuf[32];

usart::cfg_t usartCfg1 = {USART1,{0},{USART1_IRQn,0,0,ENABLE},txbuf};
usart::cfg_t usartCfg2 = {USART2,{0},{USART2_IRQn,0,0,ENABLE},txbuf};
usart::cfg_t usartCfg3 = {USART3,{0},{USART3_IRQn,0,0,ENABLE},txbuf};
usart::cfg_t usartCfg4 = {UART4,{0},{UART4_IRQn,0,0,ENABLE},txbuf};
usart::cfg_t usartCfg5 = {UART5,{0},{UART5_IRQn,0,0,ENABLE},txbuf};

const usart::cfg_t *usart::settings[] = { &usartCfg1, &usartCfg2, &usartCfg3, &usartCfg4, &usartCfg5 };
const uint16_t usart::n_configured_usarts = 5;

}

class testreader : public mcal::usart::reader {
public:
    testreader(mcal::usart& u) : mcal::usart::reader(u), called(false) {}
    virtual void usart_update( usart &u, uint8_t data ) {
        called = true;
        rxData = data;
    }

    bool called;
    uint8_t rxData;
};

TEST_GROUP( usart );


/* TEST_SETUP is called before each test is run */
TEST_SETUP() {

}


/* TEST_TEARDOWN is called after each test is run */
TEST_TEARDOWN() {

}



TEST( sameID ) {
    usart::ptr u0 = usart::instance(0);
    usart::ptr u1 = usart::instance(0);
    CHECK_EQUAL( (uint32_t)u0, (uint32_t)u1 );
}

TEST( unequalID ) {
    usart::ptr u0 = usart::instance(0);
    usart::ptr u1 = usart::instance(1);
    CHECK( ((uint32_t)u0 != (uint32_t)u1) );
}

TEST( tooHighID ) {
    usart::ptr u0 = usart::instance(6);
    CHECK( ((uint32_t)u0 == 0) );
}

TEST( maxNusarts ) {
    usart::ptr u0 = usart::instance(0);
    CHECK( ((uint32_t)u0 != 0) );

    usart::ptr u1 = usart::instance(1);
    CHECK( ((uint32_t)u1 != 0) );

    usart::ptr u2 = usart::instance(2);
    CHECK( ((uint32_t)u2 != 0) );

    usart::ptr u3 = usart::instance(3);
    CHECK( ((uint32_t)u3 != 0) );

    usart::ptr u4 = usart::instance(4);
    CHECK( ((uint32_t)u4 != 0) );

    usart::ptr u5 = usart::instance(5);
    CHECK( ((uint32_t)u5 == 0) );

    usart::ptr u6 = usart::instance(6);
    CHECK( ((uint32_t)u6 == 0) );
}

TEST( returnOne ) {
    usart::ptr u4 = usart::instance(4);
    CHECK( ((uint32_t)u4 != 0) );

    u4->destroy();
    u4 = usart::instance(4);
    CHECK( ((uint32_t)u4 != 0) );

    usart::ptr u5 = usart::instance(5);
    CHECK( ((uint32_t)u5 == 0) );

    usart::ptr u6 = usart::instance(6);
    CHECK( ((uint32_t)u6 == 0) );

}

TEST( writeRawDataToOutputBuffer ) {
    usart::ptr u0 = usart::instance(0);
    mcal::rawwriter f(*u0);

    uint8_t data[] = {1,2,3};
    uint16_t len = f.write(data,3);

    CHECK( len == 3 );
    //CHECK( (memcmp(txbuf,data,3)==0) );
}

TEST( framingProtoAddsSOFandEOF ) {
    usart::ptr u0 = usart::instance(0);
    mcal::framewriter f(*u0);

    uint8_t data[] = {0x7e,1,2,3,0x7f};
    uint16_t len = f.write(&data[1],3);

    CHECK_EQUAL( 5,len );
   // CHECK( (memcmp(txbuf,data,5)==0) );
}

TEST( framingProtoEscapesData ) {
    usart::ptr u0 = usart::instance(0);
    mcal::framewriter f(*u0);

    uint8_t data[] = {0x7e,0x7d,1,0x7d,0x7e,0x7f,0x7f};
    uint8_t resulting[] = {0x7e,0x7d,0x5d,1,0x7d,0x5d,0x7d,0x5e,0x7d,0x5f,0x7f};
    uint16_t len = f.write(&data[1],5);

    CHECK_EQUAL( 11,len );
    //CHECK( (memcmp(txbuf,resulting,11)==0) );
}



TEST( readerCallbackOnRx ) {
    // a registered reader gets called on rx
    usart::ptr pu = usart::instance(0);
    testreader t(*pu);

    setITstatus(USART_IT_RXNE,SET);

    USART1_IRQHandler();

    CHECK( t.called );
}



void testGroup_usart( void ) {
    TEST_ADD(
            sameID,
            unequalID,
            tooHighID,
            maxNusarts,
            returnOne,
            writeRawDataToOutputBuffer,
            framingProtoAddsSOFandEOF,
            framingProtoEscapesData,
            readerCallbackOnRx
    );
    TEST_GROUP_ADD();
}





