#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "sdkconfig.h"
#include "PCA9632.hpp"
#include "MPU6500.hpp"

constexpr gpio_num_t    LED_SDA = GPIO_NUM_37;
constexpr gpio_num_t    LED_SCL = GPIO_NUM_38;
constexpr int           LED_FREQ = 1000000;
constexpr uint8_t       LED_ADRS = 0x62;

extern PCA9632 led;
extern MPU6500 gyro;

void initSensors();

#endif