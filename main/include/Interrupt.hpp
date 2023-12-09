#ifndef INTERRUPT_HPP
#define INTERRUPT_HPP

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include "structs.hpp"
#include "Base_task.hpp"
#include "Search_task.hpp"
#include "Run_task.hpp" // 各タスクを追加
#include "Turn_task.hpp"
#include "Slalom_task.hpp"
#include "Log_task.hpp"
#include "Back_task.hpp"
#include "peripheral.hpp"
#include <freertos/semphr.h>



void init_structs();
void Interrupt(void* pvparam);
void calc_target(); //  目標値を計算する
void wall_ctl();   //  壁制御
void FB_ctl();    //  フィードバック制御
void calc_dist();   //  距離を計算
void calc_ang();    //  角度を計
void reset_I_gain();    //  積分値をリセット

extern SemaphoreHandle_t on_logging;

#endif