#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <math.h>
#include "Base_task.hpp"
#include "Search_task.hpp"
#include "Run_task.hpp" // 各タスクを追加
#include "Turn_task.hpp"
#include "Slalom_task.hpp"
#include "Log_task.hpp"
#include "Back_task.hpp"
#include "structs.hpp"
#include "run.hpp"




void call_main_task_1(Base_task *task);
void set_main_task_1(uint8_t _mode);
void get_main_task_1(uint8_t _mode_num);
void set_param(Base_task *task);



        


#endif