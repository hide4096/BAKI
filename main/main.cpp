#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"

extern "C" void app_main(void){
    initSensors();
    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    while(1){
        vTaskDelay(1);
    };
    
}