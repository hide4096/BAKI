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

    memset(&cmd,0,sizeof(cmd));
    cmd.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
    cmd.length = 16;
    cmd.tx_data[0] = (_send >> 8) & 0xFF;
    cmd.tx_data[1] = _send & 0xFF;
    
    err = spi_device_polling_transmit(_spi,&cmd);
    assert(err == ESP_OK);

    cmd.length = 16;
    cmd.tx_data[0] = 0;
    cmd.tx_data[1] = 0;

    err = spi_device_polling_transmit(_spi,&cmd);
    assert(err == ESP_OK);

    uint16_t recv = cmd.rx_data[0] << 8 | cmd.rx_data[1];

    return recv & 0x3FFF;
}

void AS5047P::init(spi_host_device_t bus,gpio_num_t cs){
    esp_err_t err;
    _cs = cs;

    spi_device_interface_config_t dev_enc;
    memset(&dev_enc,0,sizeof(dev_enc));
    dev_enc.clock_speed_hz = 10*1000*1000;
    dev_enc.mode = 1;
    dev_enc.spics_io_num = _cs;
    dev_enc.queue_size = 1;
    dev_enc.cs_ena_pretrans = 4;

    err = spi_bus_add_device(bus,&dev_enc,&_spi);
    ESP_ERROR_CHECK(err);
}


uint16_t AS5047P::readAngle(){
    return read16(0x3FFF);
}
