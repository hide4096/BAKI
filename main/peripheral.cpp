#include "peripheral.hpp"
#include <cstring>

PCA9632 led;
MPU6500 imu;
BUZZER buzz;
AS5047P encR;
AS5047P encL;

void initSensors()
{
    esp_err_t ret;

    // I2C
    // LEDドライバ
    i2c_config_t i2c_conf;
    memset(&i2c_conf, 0, sizeof(i2c_conf));
    i2c_conf.mode = I2C_MODE_MASTER;
    i2c_conf.sda_io_num = LED_SDA;
    i2c_conf.scl_io_num = LED_SCL;
    i2c_conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_conf.master.clk_speed = LED_FREQ;
    i2c_conf.clk_flags = 0;

    ret = i2c_param_config(I2C_NUM_0, &i2c_conf);
    ESP_ERROR_CHECK(ret);
    ret = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    ESP_ERROR_CHECK(ret);

    led.init(I2C_NUM_0, LED_ADRS);

    // SPI
    // MPU6500
    spi_bus_config_t bus_imu;
    memset(&bus_imu, 0, sizeof(bus_imu));
    bus_imu.mosi_io_num = IMU_MOSI;
    bus_imu.miso_io_num = IMU_MISO;
    bus_imu.sclk_io_num = IMU_CLK;
    bus_imu.quadwp_io_num = -1;
    bus_imu.quadhd_io_num = -1;
    bus_imu.max_transfer_sz = 16;
    bus_imu.intr_flags = 0;

    ret = spi_bus_initialize(SPI2_HOST, &bus_imu, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    imu.init(SPI2_HOST, IMU_CS);

    // AS5047P
    spi_bus_config_t bus_enc;
    memset(&bus_enc, 0, sizeof(bus_enc));
    bus_enc.mosi_io_num = ENC_MOSI;
    bus_enc.miso_io_num = ENC_MISO;
    bus_enc.sclk_io_num = ENC_CLK;
    bus_enc.quadwp_io_num = -1;
    bus_enc.quadhd_io_num = -1;
    bus_enc.max_transfer_sz = 4;
    bus_enc.flags = SPICOMMON_BUSFLAG_MASTER;
    bus_enc.intr_flags = 0;

    ret = spi_bus_initialize(SPI3_HOST, &bus_enc, SPI_DMA_DISABLED);
    ESP_ERROR_CHECK(ret);
    encR.init(SPI3_HOST, ENC_CS_R);
    encL.init(SPI3_HOST, ENC_CS_L);
}

void initPeripherals()
{
    buzz.init(BUZZER_CH, BUZZER_TIMER, BUZZER_PIN);
    initSensors();
    initMotors();
    initADC();
    //gyro.gyro_ref = imu.surveybias(1000);
}


const int MODE_MAX = 0b0111;
const int MODE_MIN = 0;
void set_mode()
{
    int mode = 0;
    while (1)
    {
        led.set(mode+1);
        if(w_sens.val.fl + w_sens.val.l + w_sens.val.r + w_sens.val.fr > 3000){
            led.set(0b1111);
            gyro.gyro_ref = imu.surveybias(1000);
            get_main_task_1(mode);
            ct.control_flag = FALSE;
            break;
        }
        

        if (motion.vel > 0.05)
        {
            if (mode >= MODE_MAX)
            {
                mode = MODE_MIN;
            }
            else
            {
                mode++;
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        if (motion.vel < -0.05)
        {
            if (mode <= MODE_MIN)
            {
                mode = MODE_MAX;
            }
            else
            {
                mode--;
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        /*std::cout << "motion.vel : " << motion.vel << std::endl;
        printf("mode_led : %d\n", mode_led);
        std::cout << "mode : " << mode << std::endl;
        std::cout << "motion.rad : " << motion.rad << std::endl;*/
        //std::cout << "time : " << ct.time_count << std::endl;
        //printf("time : %d   BatteryVoltage : %f\n", ct.time_count, BatteryVoltage());
        printf(">FL : %4d,  >L : %4d,  >R : %4d,  >FR : %4d\n",w_sens.val.fl, w_sens.val.l, w_sens.val.r, w_sens.val.fr);
        //printf("motion.ang_vel : %f\n", motion.ang_vel);
        //printf("time : %d", ct.time_count);
        //printf("gyro_ref : %f\n", gyro.gyro_ref);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
