#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Base_task.hpp"
#include "Search_task.hpp"
#include "Run_task.hpp" // 各タスクを追加
#include "Turn_task.hpp"
#include "Slalom_task.hpp"
#include "Log_task.hpp"
#include "Back_task.hpp"
#include "structs.hpp"


class Set { //set task
    public:
        void call_main_task_1(Base_task *task);
        void set_main_task_1(uint8_t _mode);
        void get_main_task_1(uint8_t _mode_num);
        void set_param(Base_task *task);
    private:
        uint8_t max_mode_num = 8;
        std::shared_ptr<t_motion> param;
        std::shared_ptr<t_motion_val> val;
        std::shared_ptr<t_control> ctl;
        std::shared_ptr<t_wall_sens> sens;
        std::shared_ptr<t_local_dir> dir;
        
};

#endif