#ifndef MPU6500_HPP
#define MPU6500_HPP

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <cstring>

#define MPU6500_WHO_AM_I 0x70
#define MPU6500_READ_FLAG 0x80
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define GYRO_FS_SEL 3
#define ACCEL_FS_SEL 3


class MPU6500{
    public:
        MPU6500();
        ~MPU6500();

        void init(spi_host_device_t bus,gpio_num_t cs);
        float surveybias(int reftime);

        int16_t accelX_raw();
        int16_t accelY_raw();
        int16_t accelZ_raw();
        int16_t gyroX_raw();
        int16_t gyroY_raw();
        int16_t gyroZ_raw();

        float accelX();
        float accelY();
        float accelZ();
        float gyroX();
        float gyroY();
        float gyroZ();
    private:
        spi_device_handle_t _spi;
        float gyro_sensitivity=1,accel_sensitivity=1;

        uint8_t whoami();
        int changesens(uint8_t _gyro,uint8_t _accel);
        uint8_t read(uint8_t reg);
        uint16_t read16(uint8_t reg);
        void write(uint8_t reg, uint8_t data);

};

#endif