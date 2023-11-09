#ifndef MPU6500_HPP
#define MPU6500_HPP

#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <cstring>

#define MPU6500_WHO_AM_I 0x70
#define MPU6500_READ_FLAG 0x80
#define ICM20648_WHO_AM_I 0xE0


class MPU6500{
    public:
        MPU6500();
        ~MPU6500();
        void init(spi_host_device_t bus,gpio_num_t cs);
    private:
        spi_device_handle_t _spi;
        bool _init = false;
        uint8_t read(uint8_t reg);
        uint16_t read16(uint8_t reg);
        void write(uint8_t reg, uint8_t data);

};

#endif