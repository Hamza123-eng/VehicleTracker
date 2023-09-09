/**
 * @file led.cpp
 * @author Hamxa Islam {hamzaislam170@gamil.com}
 * @brief
 * @version 2.0.0
 * @date 2023-09-08
 *
 * @ copyright --->  EPTeck Tecnologies Gmbh   2023
 *
 */

#include "led.hpp"

/**
 * @brief
 *
 */
void ledBlink::ledStart()
{
    this->Start();
}
/**
 * @brief
 *
 */
void ledBlink::Run()
{
    while (1)
    {
        led_gpio.set(false);
        mode_ == ACTIVE_LOW ? DelayMS(on_time_) : DelayMS(off_time_);
        led_gpio.set(true);
        mode_ != ACTIVE_LOW ? DelayMS(on_time_) : DelayMS(off_time_);
    }
}
/**
 * @brief
 *
 * @param value
 */
void ledBlink::setOnTime(uint16_t value)
{
    on_time_ = value;
}
/**
 * @brief
 *
 */
void ledBlink::ledOffTime(uint16_t value)
{
    off_time_ = value;
}