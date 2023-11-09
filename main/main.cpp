#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"

extern "C" void app_main(void){
    initSensors();
    /*led.init();
    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    while(1){
        vTaskDelay(1);
    };*/
    gyro.init(SPI2_HOST,IMU_CS);
    //gyro.read(0x00);
}