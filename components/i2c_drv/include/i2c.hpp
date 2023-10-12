#ifndef I2C_HPP_
#define I2C_HPP_

#include "driver/i2c.h"
#include "driver/gpio.h"
#include "semaphore.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace cpp_freertos;

#define ACK_CHECK_EN  0x01

 enum I2cCommandType : uint8_t
{
    NONE,
    WRITE,
    READ,
    START,
    STOP,
    DATA
};

struct I2cCommand
{
    I2cCommand(std::vector<I2cCommandType> &param) : commandParam(param) {}

    std::vector<I2cCommandType> &commandParam;

    uint8_t readLength = 0;
    uint8_t writeLength = 0;

    uint8_t *writeBuff = 0;
    uint8_t *readBuff = 0;
};

class I2cDriver : public BinarySemaphore
{
public:
    I2cDriver(uint8_t sdaPin = 21, uint8_t sclPin = 22, uint32_t busFreq = 200000U, uint8_t busNumber = 0)
        : BinarySemaphore(true)
    {

        _mSda = sdaPin;
        _mScl = sclPin;
        _mBusFreq = busFreq;
        _mBusNumber = busNumber;

        int i2c_master_port = busNumber;

        i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = _mSda,
            .scl_io_num = _mScl,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
        };
        conf.master.clk_speed = _mBusFreq;

        i2c_param_config(i2c_master_port, &conf);
        i2c_driver_install(i2c_master_port, conf.mode, 512, 512, 0);
    }

    virtual ~I2cDriver(){};

    bool TakeBus();
    bool ReleaseBus();
    void SetSlaveAddress(uint8_t slaveAddr);

    bool ReadDevice(uint8_t *data, uint16_t lenght, uint8_t slaveAddr = 0);
    bool WriteDevice(uint8_t *data, uint16_t lenght, uint8_t slaveAddr = 0);
    bool ExecuteCommand(I2cCommand &command, uint8_t slaveAddr = 0);

private:
    uint8_t _mSda = 21;
    uint8_t _mScl = 22;
    uint8_t _mBusNumber = 0;
    uint32_t _mBusFreq = 200000U;
    uint8_t _mAddress = 0x00;
};

#endif