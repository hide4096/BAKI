#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"
#include <iostream>
#include <fstream>
#include "esp_chip_info.h"

extern "C" void app_main(void){
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("Chip: %s\tCores: %d\r\n",
        CONFIG_IDF_TARGET, chip_info.cores);

    initPeripherals();

    printf("Battery Voltage: %d\r\n",BatteryVoltage());

    //xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    //xTaskCreate([](void*){buzz.play();}, "buzz", 4096, NULL, 1, NULL);
    //xTaskCreate([](void*){sincurve();}, "sincurve", 8192, NULL, 1, NULL);
    //xTaskCreate([](void*){WallSensor();}, "WallSensor", 8192, NULL, 1, NULL);
   
    while (1){
        //printf(">Yaw:%.3f\n",imu.gyroZ());
        //printf(">encR:%d\n",encR.readAngle());
        //printf(">encL:%d\n",encL.readAngle());
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
    
}