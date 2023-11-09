#include "peripheral.hpp"
#include <cstring>

PCA9632 led(LED_PORT,LED_ADRS);

void initSensors() {
    esp_err_t ret;

    //I2C
    //LEDドライバ
    i2c_config_t i2c_conf;
    
    i2c_conf.mode = I2C_MODE_MASTER;
    i2c_conf.sda_io_num = LED_SDA;
    i2c_conf.scl_io_num = LED_SCL;
    i2c_conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.master.clk_speed = LED_FREQ;
    i2c_conf.clk_flags = 0;

    ret = i2c_param_config(I2C_NUM_0,&i2c_conf);
    ESP_ERROR_CHECK(ret);
    ret = i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER,0,0,0);
    ESP_ERROR_CHECK(ret);
    led.init();

    //SPI
    //MPU6500
    spi_bus_config_t bus_imu;
    bus_imu.mosi_io_num = IMU_MOSI;
    bus_imu.miso_io_num = IMU_MISO;
    bus_imu.sclk_io_num = IMU_CS;
    bus_imu.quadwp_io_num = -1;
    bus_imu.quadhd_io_num = -1;
    bus_imu.max_transfer_sz = 16;

    ret = spi_bus_initialize(SPI2_HOST,&bus_imu,SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

}