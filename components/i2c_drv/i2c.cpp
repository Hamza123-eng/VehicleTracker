/**
 * @file i2c.cpp
 * @author Hamxa Islam {hamzaislam170@gamil.com}
 * @brief
 * @version 2.0.0
 * @date 2023-10-11
 *
 * @ copyright --->  EPTeck Tecnologies Gmbh   2023
 *
 */
#include "i2c.hpp"
#include "driver/i2c.h"
#include "driver/gpio.h"

bool I2cDriver::TakeBus()
{
    return this->Take(10);
}

bool I2cDriver::ReleaseBus()
{
    return this->Give();
}

bool I2cDriver::ReadDevice(uint8_t *data, uint16_t lenght, uint8_t slaveAddr)
{
    slaveAddr = (slaveAddr == 0) ? _mAddress : slaveAddr;
    esp_err_t err = i2c_master_read_from_device(_mBusNumber, slaveAddr, data, lenght, 1000 / portTICK_RATE_MS);
    return err == ESP_OK ? true : false;
}

bool I2cDriver::WriteDevice( uint8_t *data, uint16_t lenght, uint8_t slaveAddr)
{
    slaveAddr = (slaveAddr == 0) ? _mAddress : slaveAddr;
    esp_err_t err = i2c_master_write_to_device(_mBusNumber, slaveAddr, data, lenght, 1000 / portTICK_RATE_MS);
    return err == ESP_OK ? true : false;
}

bool I2cDriver::ExecuteCommand(I2cCommand &command, uint8_t slaveAddr)
{
    size_t size = command.commandParam.size();
    esp_err_t ret = ESP_FAIL;

    if (size)
    {
        I2cCommandType activeCmd = I2cCommandType::NONE;

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        for (size_t i = 0; i < size; i++)
        {
            switch (command.commandParam[i])
            {
            case I2cCommandType::WRITE:
            {
                activeCmd = I2cCommandType::WRITE;
                slaveAddr = (slaveAddr == 0) ? _mAddress : slaveAddr;
                i2c_master_write_byte(cmd, (slaveAddr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
            }
            break;
            case I2cCommandType::READ:
            {
                slaveAddr = (slaveAddr == 0) ? _mAddress : slaveAddr;
                i2c_master_write_byte(cmd, (slaveAddr << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
                activeCmd = I2cCommandType::READ;
            }
            break;
            case I2cCommandType::STOP:
            {
                i2c_master_stop(cmd);
            }
            break;
            case I2cCommandType::START:
            {
                i2c_master_start(cmd);
            }
            break;
            case I2cCommandType::DATA:
            {
                if (activeCmd == I2cCommandType::WRITE)
                {
                    i2c_master_write(cmd, command.writeBuff, command.writeLength, ACK_CHECK_EN);
                }
                else
                {
                    i2c_master_read(cmd, command.readBuff, command.readLength, I2C_MASTER_ACK);
                }
            }
            break;
            default:
                break;
            }
        }
        ret = i2c_master_cmd_begin(_mBusNumber, cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);
    }

    return ret == ESP_OK ? true : false;
}

void I2cDriver::SetSlaveAddress(uint8_t slaveAddr)
{
    _mAddress = slaveAddr;
}
