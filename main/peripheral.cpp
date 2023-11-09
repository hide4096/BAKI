#include "peripheral.hpp"
#include <cstring>

PCA9632 led;

void initSensors() {
    esp_err_t ret;

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

    led.init(I2C_NUM_0,LED_ADRS);
}