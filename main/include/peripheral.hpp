#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "sdkconfig.h"
#include "PCA9632.hpp"

constexpr gpio_num_t    LED_SDA = GPIO_NUM_45;
constexpr gpio_num_t    LED_SCL = GPIO_NUM_46;
constexpr int           LED_FREQ = 1000*1000;
constexpr uint8_t       LED_ADRS = 0x40;
constexpr uint8_t       LEDUT0 = 0x02;

constexpr gpio_num_t    IMU_MISO    = GPIO_NUM_11;
constexpr gpio_num_t    IMU_MOSI    = GPIO_NUM_12;
constexpr gpio_num_t    IMU_CLK     = GPIO_NUM_2;
constexpr gpio_num_t    IMU_CS      = GPIO_NUM_7;

extern PCA9632 led;

void initSensors();

#endif