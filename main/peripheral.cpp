#include "peripheral.hpp"

PCA9632 led(LED_PORT,LED_ADRS);

void initSensors() {
    esp_err_t ret;

    //LEDドライバ
    i2c_config_t i2c_conf;
    i2c_conf.mode = I2C_MODE_MASTER;
    i2c_conf.sda_io_num = LED_SDA;
    i2c_conf.scl_io_num = LED_SCL;
    i2c_conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
    i2c_conf.master.clk_speed = LED_FREQ;

    ret = i2c_param_config(LED_PORT,&i2c_conf);
    ESP_ERROR_CHECK(ret);
    ret = i2c_driver_install(LED_PORT,I2C_MODE_MASTER,0,0,0);
    ESP_ERROR_CHECK(ret);
}