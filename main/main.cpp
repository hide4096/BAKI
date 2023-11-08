#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"

extern "C" void app_main(void){
    initSensors();
    led.init();
    xTaskCreate([](void*){led.blink();}, "blink", 1024, NULL, 1, NULL);
    while(1);
}