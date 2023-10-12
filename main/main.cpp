
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
#include "i2c.hpp"

#define PREPARE_FRAM_ADDR(reg_write_addr, write_addr)       \
    do                                                      \
    {                                                       \
        (write_addr)[0] = (((reg_write_addr) >> 8) & 0x1F); \
        (write_addr)[1] = (reg_write_addr)&0xFF;            \
    } while (0)

#define TEST_ADDR 0x0001

ledBlink *myLed;

 std::vector<I2cCommandType> framReadCmd{START, WRITE, DATA, START, READ, DATA, STOP};
 std::vector<I2cCommandType> framWriteCmd{START, WRITE, DATA, STOP};

extern "C" void app_main(void)
{

    I2cDriver i2cdrv;

    I2cCommand framCmd(framWriteCmd);

    uint8_t writeData[4] = {0x00, 0x00, 0x11, 0x22};
    uint8_t readData[2] = {0x00};

    PREPARE_FRAM_ADDR(TEST_ADDR, writeData);

    if (i2cdrv.TakeBus())
    {
        //** Write tranction

        framCmd.writeBuff = writeData;
        framCmd.writeLength = 4;

        i2cdrv.ExecuteCommand(framCmd, 0x50);

        //** read Transction here

        framCmd.commandParam = framReadCmd;
        framCmd.writeBuff = writeData;
        framCmd.writeLength = 2;
        framCmd.readBuff = readData;
        framCmd.readLength = 2;

        i2cdrv.ExecuteCommand(framCmd, 0x50);

        printf("Recevied Byte %X ,  %X\n", readData[0], readData[1]);
    }
}
