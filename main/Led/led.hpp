/**
 * @file led.hpp
 * @author Hamxa Islam {hamzaislam170@gamil.com}
 * @brief 
 * @version 2.0.0
 * @date 2023-09-09
 * 
 * @ copyright --->  EPTeck Tecnologies Gmbh   2023
 * 
 */
#ifndef LED_HPP_
#define LED_HPP_

#include "thread.hpp"
#include "gpio.hpp"
#include "driver/gpio.h"

#include <stdio.h>
#include <iostream>
#include "thread.hpp"
#include "gpio.hpp"

using namespace cpp_freertos;
using namespace std;

enum operationMode
{
    ACTIVE_HIGH = 0,
    ACTIVE_LOW = 1
};

class ledBlink : public Thread
{
public:
    ledBlink(uint16_t pin_num, operationMode mode, uint16_t on_time = 1000, uint16_t off_time = 1000, int led_core = 0)
        : Thread("LED", 1000 * 2, 4, core_id_t(led_core)),
          led_gpio((gpio_num_t)pin_num, GPIO_MODE_OUTPUT, (bool)mode)
    {
        on_time_ = on_time;
        off_time_ = off_time;
        mode_ = mode;
    }
    void ledStart();
    void setOnTime(uint16_t value);
    void ledOffTime(uint16_t value);

protected:
    virtual void Run();

private:
    Gpio led_gpio;
    uint16_t on_time_;
    uint16_t off_time_;
    operationMode mode_;
};

#endif