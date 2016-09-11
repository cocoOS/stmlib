

/* Includes ------------------------------------------------------------------*/

#include <inc/hw_config.h>

static uint8_t systemSet = 0;
static uint8_t usbClockEnabled = 1;

/**
  * @brief  Configures Main system clocks & power.
  * @param  None
  * @retval None
  */
void Set_System(void) {
    systemSet = 1;
}

void Set_USBClock(void)
{
    usbClockEnabled = 1;
}


uint8_t getUSBClockEnabled() {
    return usbClockEnabled;
}
