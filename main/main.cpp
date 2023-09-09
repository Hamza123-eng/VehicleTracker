
/*
 * ESP-IDF C++ Template with FreeRTOS Addon
 *
 * This project serves as a starting point for ESP32 development with ESP-IDF,
 * incorporating C++ features and a FreeRTOS addon for real-time multitasking.
 * The main application demonstrates how to use the `LedBlink` class to control
 * an LED on pin 2, utilizing an active-low input state.
 *
 * Author: Hamza Islam
 * Organization: Epteck
 *
 * For more details, please refer to the README.md file and project documentation.
 *
 * License: MIT (See LICENSE file for details)
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led.hpp"

ledBlink *myLed;

extern "C" void app_main(void)
{
    myLed = new ledBlink(2, ACTIVE_LOW);
    myLed->ledStart();

/**
 * @brief this this routine to set chage the on and off time 
 * 
 */

    // myLed->setOnTime(500);  // reconfigure led on time
    // myLed->ledOffTime(500); // reconfigure led off time
    // Thread::DelayMS(5000);
    // delete myLed;       // this will also delete the thask
}
