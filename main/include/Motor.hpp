#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <bdc_motor.h>
#include "driver/ledc.h"
#include "driver/gpio.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void initMotors();
void setMotorSpeed(float spdR, float spdL);
void sincurve();

#endif