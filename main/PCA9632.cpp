#include "include/PCA9632.hpp"

PCA9632::PCA9632(){}
PCA9632::~PCA9632(){}

uint8_t PCA9632::read(uint8_t reg){
    esp_err_t err;
    uint8_t data;

    err = i2c_master_write_read_device(_port,_adrs,&reg,1,&data,1,10/portTICK_PERIOD_MS);
    //ESP_ERROR_CHECK(err);
    return data;
}

esp_err_t PCA9632::write(uint8_t reg,uint8_t data){
    esp_err_t err;
    uint8_t send[2] = {reg,data};

    err = i2c_master_write_to_device(_port,_adrs,send,2,10/portTICK_PERIOD_MS);
    //ESP_ERROR_CHECK(err);
    return err;
}

void PCA9632::init(i2c_port_t port, uint8_t adrs){
    _port = port;
    _adrs = adrs;
    write(0x00,0x01);
    _init = true;
}

void PCA9632::blink(){
    while(1){
        write(0x08,0x55);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        write(0x08,0x00);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}