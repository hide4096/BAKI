#ifndef ADC_HPP
#define ADC_HPP

#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void initADC();

int BatteryVoltage();
void WallSensor();

#endif