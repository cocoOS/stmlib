/*
 * mcu.h
 *
 *  Created on: 31 okt 2013
 *      Author: peter
 */

#ifndef mcu_h_
#define mcu_h_

#include <stdint.h>

namespace mcal {

class mcu {
public:
    static void initSystemClocks();
    static void registerUserTick( uint32_t ticks, void (*cb)(void) );
    struct cfg_t;
private:
    mcu();
    static cfg_t *settings;
};

} /* namespace mcal */
#endif /* mcu_h_ */
