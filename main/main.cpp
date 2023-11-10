#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/peripheral.hpp"
#include <iostream>
#include <fstream>

extern "C" void app_main(void){
    initSensors();
    /*led.init();
    vTaskDelay(1000/portTICK_PERIOD_MS);
    xTaskCreate([](void*){led.blink();}, "blink", 4096, NULL, 1, NULL);
    while(1){
        
        vTaskDelay(1);
    };*/
    gyro.init(SPI2_HOST,IMU_CS);
    while (1)
    {
        std::cout << std::left << gyro.accelX() << ",";
        std::cout << std::left << gyro.accelY() << ",";
        std::cout << std::left << gyro.accelZ() << ",";
        std::cout << std::left << gyro.gyroX() << ",";
        std::cout << std::left << gyro.gyroY() << ",";
        std::cout << std::left << gyro.gyroZ() << "," << std::endl;
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
    
}