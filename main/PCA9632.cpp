#include "include/PCA9632.hpp"

PCA9632::PCA9632(i2c_port_t port, uint8_t adrs){
    _port = port;
    _adrs = adrs;
}

PCA9632::~PCA9632(){}

uint8_t PCA9632::read(uint8_t reg){
    uint8_t data;

    esp_err_t err = i2c_master_write_read_device(_port,_adrs,&reg,1,&data,1,1/portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(err);
    return data;
}

esp_err_t PCA9632::write(uint8_t reg,uint8_t data){
    uint8_t send[2] = {reg,data};
    return i2c_master_write_to_device(_port,_adrs,send,2,1/portTICK_PERIOD_MS);
}

void PCA9632::init(){
    write(0x00,0x01);
    _init = true;
}

void PCA9632::blink(){
    while(1){
        write(0x14,0x55);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        write(0x14,0x00);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}