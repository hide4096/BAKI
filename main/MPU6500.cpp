#include "include/MPU6500.hpp"

MPU6500::MPU6500(){}
MPU6500::~MPU6500(){}

uint8_t MPU6500::read(uint8_t reg){
    esp_err_t err;
    spi_transaction_t cmd;
    uint16_t tx = (reg | MPU6500_READ_FLAG) << 8;
    tx = SPI_SWAP_DATA_TX(tx,16);

    memset(&cmd,0,sizeof(cmd));
    cmd.flags = SPI_TRANS_USE_RXDATA;
    cmd.length = 16;
    cmd.tx_buffer = &tx;
    err = spi_device_polling_transmit(_spi,&cmd);
    assert(err == ESP_OK);

    uint8_t rx = 
        SPI_SWAP_DATA_RX(*(uint16_t*)cmd.rx_data,16) & 0xFF;

    return rx;
}

void MPU6500::write(uint8_t reg,uint8_t data){
    esp_err_t err;
    spi_transaction_t cmd;

    memset(&cmd,0,sizeof(cmd));
    cmd.length = 24;
    cmd.tx_data[0] = reg;
    cmd.tx_data[1] = data;
    cmd.tx_data[2] = 0;
    err = spi_device_polling_transmit(_spi,&cmd);
    assert(err == ESP_OK);
    return;
}



void MPU6500::init(spi_host_device_t bus,gpio_num_t cs){
    esp_err_t err;

    spi_device_interface_config_t dev_imu;
    dev_imu.clock_speed_hz = 7*1000*1000;
    dev_imu.mode = 3;
    dev_imu.spics_io_num = cs;
    dev_imu.queue_size = 7;

    err = spi_bus_add_device(bus,&dev_imu,&_spi);
    ESP_ERROR_CHECK(err);

    if(read(0x00) != MPU6500_WHO_AM_I){ //MPU6500 : read(0x75)  ICM20648 : read(0x00)
        return;
    }

    _init = true;
}