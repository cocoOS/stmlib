/*
 * main.cpp
 *
 *  Created on: 4 maj 2013
 *      Author: peter
 */
#include <stdio.h>
#include <stdlib.h>
#include <testgroups.h>
#include <test.h>

#include "mock.h"

int main()
{
  testGroup_mcal();
  testGroup_usart();
  testGroup_usb();
  
  return test_run();
}



