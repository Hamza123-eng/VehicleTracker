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
    running_ = true;
}
/**
 * @brief
 *
 */
void ledBlink::blinkIterate(uint16_t &ontime, uint16_t &offtime, operationMode &mode)
{
    led_gpio.set(mode);
    DelayMS(ontime);
    led_gpio.set(!mode);
    DelayMS(offtime);
}
/**
 * @brief
 *
 * @param ontime
 * @param offtime
 * @param mode
 */
void ledBlink::ledStop()
{
    running_ = false;
}
/**
 * @brief
 *
 */
void ledBlink::Run()
{
    while (1)
    {
        if (running_)
        {
            switch (TYPE_)
            {
            case NONE:
                led_gpio.set(mode_);
                /* code */
                break;
            case EQUAL:
                blinkIterate(on_time_s, on_time_s, mode_);
                /* code */
                break;
            case UNEQUAL:
                blinkIterate(on_time_s, off_time_ms, mode_);
                /* code */
                break;
            case MULTIPLE_SHOT:
                for (uint8_t i = 0; i < shot_num_m; i++)
                {
                    blinkIterate(on_time_m, off_time_m, mode_);
                }
                DelayMS(off_time_ms);
                /* code */
                break;
            default:
                led_gpio.set(mode_);
                break;
            }
        }
        else
        {
            led_gpio.set(!mode_);
            DelayMS(1000);
        }
    }
}

/**
 * @brief
 *
 * @param ontime
 */
void ledBlink::setEqualLedMode(uint16_t ontime)
{
    TYPE_ = EQUAL;
    on_time_s = ontime;
}
/**
 * @brief
 *
 * @param ontime
 * @param offtime
 */
void ledBlink::setUnEqualLedMode(uint16_t ontime, uint16_t offtime)
{
    TYPE_ = UNEQUAL;
    on_time_s = ontime;
    off_time_ms = offtime;
}
/**
 * @brief
 *
 * @param shot
 * @param ontime
 * @param offtime
 */
void ledBlink::setMultiLedMode(uint16_t shot, uint16_t ontime, uint16_t offtime, uint16_t offtime_major)
{
    TYPE_ = MULTIPLE_SHOT;
    shot_num_m = shot;
    off_time_ms = offtime_major;
    on_time_m = ontime;
    off_time_m = offtime;
}