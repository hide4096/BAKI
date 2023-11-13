#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"
#include <iostream>
#include <fstream>
#include "esp_chip_info.h"

extern "C" void app_main(void){
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("Chip: %s\tCores: %d\r\n",
        CONFIG_IDF_TARGET, chip_info.cores);

    initSensors();
    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
   
    while (1){
        printf("%1.2f\t%1.2f\t%1.2f\r",
            imu.accelX(),imu.accelY(),imu.accelZ());
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}