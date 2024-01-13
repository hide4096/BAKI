#ifndef RUN_HPP
#define RUN_HPP

#include <iostream>
#include <string>
#include <memory>
#include "esp_flash.h"
#include "esp_flash_spi_init.h"
#include "esp_partition.h"
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "structs.hpp"
#include "Interrupt.hpp"

class runs
{
    public:
        runs();
        ~runs();
        int run_90();
        int run_half();
        int turn_left();
        int turn_right();
        int turn_half();
        int stop();
        void cp_tar(std::shared_ptr<t_motion_val> v);
        void cp_param(std::shared_ptr<t_motion> m);
        void cp_pid(std::shared_ptr<t_control> c);
        void cp_wall_th(std::shared_ptr<t_wall_sens> s);
    private:
        float local_rad;
        uint8_t len_count = 0;
        std::shared_ptr<t_motion> set_m;
        std::shared_ptr<t_motion_val> set_v;
        std::shared_ptr<t_control> set_c;
        std::shared_ptr<t_wall_sens> set_s;
        std::shared_ptr<t_motion_dir> set_d;
        std::shared_ptr<t_local_dir> set_l;

};

#endif