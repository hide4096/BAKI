#include "include/AS5047P.hpp"

AS5047P::AS5047P(){}
AS5047P::~AS5047P(){}

uint8_t AS5047P::CalcParity(uint16_t data){
    uint8_t even = 0;
    for(int i=0;i<16;i++){
        if((data & (1 << i)) & 1) even = 1 - even;
    }
    return even;
}

uint16_t AS5047P::read16(uint16_t reg){
    esp_err_t err;
    spi_transaction_t cmd;
    uint16_t _send = reg | AS5047P_READ_FLAG;
    _send = CalcParity(_send) << 15 | _send;
    _send = SPI_SWAP_DATA_TX(_send,16);

    memset(&cmd,0,sizeof(cmd));
    cmd.flags = SPI_TRANS_USE_RXDATA;
    cmd.length = 16;
    cmd.tx_buffer = &_send;
    err = spi_device_polling_transmit(_spi,&cmd);
    assert(err == ESP_OK);

    return SPI_SWAP_DATA_RX(*(uint16_t*)cmd.rx_data,16);

}

void AS5047P::init(spi_host_device_t bus,gpio_num_t cs){
    esp_err_t err;

    spi_device_interface_config_t dev_enc;
    memset(&dev_enc,0,sizeof(dev_enc));
    dev_enc.clock_speed_hz = 10*1000*1000;
    dev_enc.mode = 1;
    dev_enc.spics_io_num = cs;
    dev_enc.queue_size = 1;

    err = spi_bus_add_device(bus,&dev_enc,&_spi);
    ESP_ERROR_CHECK(err);

    printf("%x\r\n",read16(0x3FFC));
}


uint16_t AS5047P::readAngle(){
    return read16(0x3FFF) & 0x3FFF;
}
