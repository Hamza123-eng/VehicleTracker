
/*
 * I2C Component for ESP-IDF with FreeRTOS Addon
 *
 * This component extends ESP32 development using ESP-IDF, incorporating C++ features and a FreeRTOS addon for multitasking.
 * It leverages the I2C ESP driver and provides a user-friendly interface to send commands to I2C devices.
 * The default constructor sets the SCL and SDA pins to their defaults if not specified by the user.
 * Users can then send desired commands to the I2C component, which are routed to the I2C HAL driver.
 * In the provided example, we demonstrate the usage of this component with an FRAM device, showcasing a write transaction
 * followed by a read transaction.
 *
 * Author: Hamza Islam
 * Organization: Epteck
 *
 * For more information and usage details, please refer to the README.md file and project documentation.
 *
 * License: MIT (See LICENSE file for details)
 */
#include <stdio.h>

#include "i2c.hpp"

#define PREPARE_FRAM_ADDR(reg_write_addr, write_addr)       \
    do                                                      \
    {                                                       \
        (write_addr)[0] = (((reg_write_addr) >> 8) & 0x1F); \
        (write_addr)[1] = (reg_write_addr)&0xFF;            \
    } while (0)

#define TEST_ADDR 0x0001

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

        printf("Recevied: Byte[0]  %X   Byte[1]   %X\n", readData[0], readData[1]);

        i2cdrv.ReleaseBus();
    }
}
