#include "include/MPU6500.hpp"

MPU6500::MPU6500(){}
MPU6500::~MPU6500(){}

float gyro_sensitivity = 1.;
float accel_sensitivity = 1.;

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

uint16_t MPU6500::read16(uint8_t Hreg,uint8_t Lreg){
    uint8_t Hrecv,Lrecv;
    Hrecv = read(Hreg);
    Lrecv = read(Lreg);
    return Hrecv << 8 | Lrecv;
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
    memset(&dev_imu,0,sizeof(dev_imu));
    dev_imu.clock_speed_hz = 7*1000*1000;
    dev_imu.mode = 3;
    dev_imu.spics_io_num = cs;
    dev_imu.queue_size = 7;

    err = spi_bus_add_device(bus,&dev_imu,&_spi);
    ESP_ERROR_CHECK(err);

    uint8_t whoami = read(0x00);
    if(whoami != ICM20648_WHO_AM_I){ //MPU6500 : read(0x75)  ICM20648 : read(0x00)
        printf("%d\r\n",whoami);
        printf("failed\r\n");
        return;
    }

    _init = true;
    printf("success");

    write(0x06,0b10000000);
    vTaskDelay(10/portTICK_PERIOD_MS);
    write(0x06,0b00001001);
    changesens(3,1);

}

int MPU6500::changesens(uint8_t _gyro,uint8_t _accel){
    if(_gyro > 0b11 || _accel > 0b11) return -1;
     
     uint8_t gyro_congig = _gyro << 1, accel_config = _accel << 1;

     write(0x7F,0x20);

     write(0x01,gyro_congig);
     write(0x14,accel_config);

     if((read(0x01) & 0b0110) != gyro_congig) return -1;
     if((read(0x01) & 0b0110) != accel_config) return -1;

     write(0x7F,0x00);
    
    switch (_gyro)
    {
    case 0:
        gyro_sensitivity = 250.0 /32767.;
        break;
    case 1:
        gyro_sensitivity = 500.0 /32767.;
        break;
    case 2:
        gyro_sensitivity = 1000.0/32767.;
        break;
    case 3:
        gyro_sensitivity = 500.0 /32767.;
        break;
    default:
        break;
    }
    switch (_accel)
    {
    case 0:
        accel_sensitivity = 2.0 / 32767.;
        break;
    case 1:
        accel_sensitivity = 2.0 / 32767.;
        break;
    case 2:
        accel_sensitivity = 2.0 / 32767.;
        break;
    case 3:
        accel_sensitivity = 2.0 / 32767.;
        break;
    
    default:
        break;
    }
    return 0;
}

float MPU6500::surveybias(int reftime){
    float r_yaw_ref_tmp = 0;
    for(uint16_t i = 0; i < reftime; i++){
        r_yaw_ref_tmp += gyroZ();
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
    return (float)(r_yaw_ref_tmp / reftime);
}

int16_t MPU6500::accelX_raw(){
    return read16(0x2D,0x2E);
}
int16_t MPU6500::accelY_raw(){
    return read16(0x2F,0x30);
}
int16_t MPU6500::accelZ_raw(){
    return read16(0x31,0x32);
}
int16_t MPU6500::gyroX_raw(){
    return read16(0x33,0x34);
}
int16_t MPU6500::gyroY_raw(){
    return read16(0x35,0x36);
}
int16_t MPU6500::gyroZ_raw(){
    return read16(0x37,0x38);
}
float MPU6500::accelX(){
    return (float)accelX_raw() * accel_sensitivity;
}
float MPU6500::accelY(){
    return (float)accelY_raw() * accel_sensitivity;
}
float MPU6500::accelZ(){
    return (float)accelZ_raw() * accel_sensitivity;
}
float MPU6500::gyroX(){
    return (float)gyroX_raw() * gyro_sensitivity;
}
float MPU6500::gyroY(){
    return (float)gyroX_raw() * gyro_sensitivity;
}
float MPU6500::gyroZ(){
    return (float)gyroX_raw() * gyro_sensitivity;
}


