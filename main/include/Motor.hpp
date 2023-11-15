#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void initMotors();
void setMotorSpeed(float spdR, float spdL,float fan);
void sincurve();

#endif