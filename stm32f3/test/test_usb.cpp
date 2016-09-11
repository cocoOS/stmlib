/**
 * @file       test_usb.cpp
 * @author     Peter Eckstrand
 * @version    $Revision$
 * @date       $Date$
 * @par        Copyright:
 * (c) Peter Eckstrand 2014
 *
 * Unit tests for the usb module
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
#include <inc/config.h>
#include "mock.h"
#include <inc/usb.h>
#include <hw_config_mock.h>


using namespace mcal;


/* Tests

Only one instance               OK
USB clock is enabled after instantiation

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



TEST_GROUP( usb );


/* TEST_SETUP is called before each test is run */
TEST_SETUP() {

}


/* TEST_TEARDOWN is called after each test is run */
TEST_TEARDOWN() {

}



TEST( oneInstance ) {
    usb::ptr u0 = usb::instance();
    usb::ptr u1 = usb::instance();
    CHECK_EQUAL( (uint32_t)u0, (uint32_t)u1 );
}

TEST( usbclock ) {
    usb::ptr u0 = usb::instance();
    CHECK( 1 == getUSBClockEnabled() );
}

void testGroup_usb( void ) {
    TEST_ADD(
            oneInstance,
            usbclock
            );
    TEST_GROUP_ADD();
}





