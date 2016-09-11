/*
 * init.cpp
 *
 *  Created on: 10 nov 2013
 *      Author: peter
 *
 *  Initialization of the mcal layer
 *
 */

#include <inc/mcu.h>
#include <inc/pin.h>

namespace mcal {

void init() {
    mcu::initSystemClocks();
    pin::init();
}

} /* Namespace mcal */



