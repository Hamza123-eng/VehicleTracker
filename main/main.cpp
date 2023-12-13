
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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <mpu.hpp>


MPU6050 mpu;

void checkSettings()
{
  
 printf(" * Sleep Mode:            ");
 printf(mpu.getSleepEnabled() ? "Enabled \n" : "Disabled \n");
  
 printf(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:    printf("Stops the clock and keeps the timing generator in reset \n"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ:printf("PLL with external 19.2MHz reference \n"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ:printf("PLL with external 32.768kHz reference \n"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:     printf("PLL with Z axis gyroscope reference \n"); break;
    case MPU6050_CLOCK_PLL_YGYRO:     printf("PLL with Y axis gyroscope reference \n"); break;
    case MPU6050_CLOCK_PLL_XGYRO:     printf("PLL with X axis gyroscope reference \n"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ: printf("Internal 8MHz oscillator \n"); break;
  }
  
 printf(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:           printf("+/- 16 g\n"); break;
    case MPU6050_RANGE_8G:            printf("+/- 8 g\n"); break;
    case MPU6050_RANGE_4G:            printf("+/- 4 g\n"); break;
    case MPU6050_RANGE_2G:            printf("+/- 2 g\n"); break;
  }  

 printf(" * Accelerometer offsets X: %d ",mpu.getAccelOffsetX());
 printf(" * Accelerometer offsets Y: %d ",mpu.getAccelOffsetY());
 printf(" * Accelerometer offsets Z: %d ",mpu.getAccelOffsetZ());

}

void setup() 
{
  
  printf("Initialize MPU6050...\n");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
   printf("Could not find a valid MPU6050 sensor, check wiring!\n");
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();
}

extern "C" void app_main(void)
{

setup();

while(1)
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

 printf(" Xraw = %.3f \n" ,rawAccel.XAxis);
 printf(" Yraw = %.3f \n" ,rawAccel.YAxis);
 printf(" Zraw = %.3f \n" ,rawAccel.ZAxis);

 printf(" Xnorm = %.3f \n" ,normAccel.XAxis);
 printf(" Ynorm = %.3f \n" ,normAccel.XAxis);
 printf(" Znorm = %.3f \n" ,normAccel.XAxis);

 vTaskDelay(10 / portTICK_PERIOD_MS);

}
 


}
