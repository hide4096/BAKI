#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"
#include <iostream>
#include <fstream>
#include "esp_chip_info.h"
#include "include/Motor.hpp"
#include "include/adc.hpp"

extern "C" void app_main(void){
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("Chip: %s\tCores: %d\r\n",
        CONFIG_IDF_TARGET, chip_info.cores);

    initSensors();
    initPeripherals();
    initMotors();
    initadc();

    printf("Battery Voltage: %d\r\n",BatteryVoltage());

    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    xTaskCreate([](void*){buzz.play();}, "buzz", 4096, NULL, 1, NULL);
    //xTaskCreate([](void*){sincurve();}, "sincurve", 8192, NULL, 1, NULL);
    xTaskCreate([](void*){WallSensor();}, "WallSensor", 8192, NULL, 1, NULL);
   
    while (1){
        //printf("%1.2f\t%1.2f\t%1.2f\r",
        //    imu.accelX(),imu.accelY(),imu.accelZ());
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}