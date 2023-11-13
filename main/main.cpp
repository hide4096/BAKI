#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"
#include <iostream>
#include <fstream>

extern "C" void app_main(void){
    initSensors();
    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    while(1){
        
        vTaskDelay(1);
    };*/
    while (1){
        printf("%1.2f\t%1.2f\t%1.2f\r",
            gyro.accelX(),gyro.accelY(),gyro.accelZ());
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}