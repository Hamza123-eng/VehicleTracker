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
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1
};

class ledBlink : public Thread
{
public:
    enum BLINK_TYPE
    {
        NONE,
        EQUAL,
        UNEQUAL,
        MULTIPLE_SHOT,
    };

    ledBlink(uint16_t pin_num, operationMode mode, int led_core = 0)
        : Thread("LED", 1000 * 2, 4, core_id_t(led_core)),
          led_gpio((gpio_num_t)pin_num, GPIO_MODE_OUTPUT, (bool)mode)
    {

        on_time_s = 500;
        off_time_ms = 300;
        on_time_m = 200;
        off_time_m = 200;
        shot_num_m = 2;

        this->Start();
    }

    void ledStart();
    void ledStop();
    void blinkIterate(uint16_t &ontime, uint16_t &offtime, operationMode &mode);
    void setEqualLedMode(uint16_t ontime = 500);
    void setUnEqualLedMode(uint16_t ontime = 500, uint16_t offtime = 300);
    void setMultiLedMode(uint16_t shot = 2, uint16_t ontime = 500, uint16_t offtime = 300, uint16_t offtime_major = 3000);

protected:
    virtual void Run();

private:
    Gpio led_gpio;
    uint16_t on_time_s;
    uint16_t off_time_ms;
    uint16_t on_time_m;
    uint16_t off_time_m;
    uint16_t shot_num_m;

    operationMode mode_;
    BLINK_TYPE TYPE_ = NONE;
    bool running_ = false;
};

#endif