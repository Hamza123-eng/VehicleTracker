/**
 * @file gpio.hpp
 * @author Hamxa Islam {hamzaislam170@gamil.com}
 * @brief
 * @version 2.0.0
 * @date 2023-09-09
 *
 * @ copyright --->  EPTeck Tecnologies Gmbh   2023
 *
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include "driver/gpio.h"

class Gpio
{
public:
    Gpio(gpio_num_t pin, gpio_mode_t mode, bool pull_up_state)
    {
        pin_ = pin;
        gpio_reset_pin(pin_);
        (mode != GPIO_MODE_OUTPUT) ? gpio_set_direction(pin_, GPIO_MODE_INPUT) : gpio_set_direction(pin_, GPIO_MODE_OUTPUT);
        pull_up_state ? gpio_set_pull_mode(pin_, GPIO_PULLUP_ONLY) : gpio_set_pull_mode(pin_, GPIO_PULLDOWN_ONLY);
    }
    virtual ~Gpio(){};

    void set(uint16_t value)
    {
        gpio_set_level(pin_, value);
    }
    bool get()
    {
        return gpio_get_level(pin_);
    }

private:
    gpio_num_t pin_;
};

#endif