#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "soc/gpio_struct.h"
#include "sdkconfig.h"
#include "PCA9632.hpp"

constexpr gpio_num_t    LED_SDA = GPIO_NUM_45;
constexpr gpio_num_t    LED_SCL = GPIO_NUM_46;
constexpr int           LED_FREQ = 100000;
constexpr uint8_t       LED_ADRS = 0x40;
constexpr i2c_port_t    LED_PORT = I2C_NUM_0;
constexpr uint8_t       LEDUT0 = 0x02;

extern PCA9632 led;

void initSensors();

#endif