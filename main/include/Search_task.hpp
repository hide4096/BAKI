#ifndef SEARCH_TASK_HPP
#define SEARCH_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "Interrupt.hpp"
#include "esp_flash.h"
#include "esp_flash_spi_init.h"
#include "esp_partition.h"
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
//#include "adachi.hpp"

class Search_task : public Base_task{
    public:
        Search_task();
        virtual int main_task_1() override;
        virtual int search() override;
        virtual int run() override;
        virtual int run_half() override;
        virtual int turn_left() override;
        virtual int turn_right() override;
        virtual int turn_half() override;
        virtual int stop() override;
        void search_1();
        void init_map(int x, int y);
        void make_map(int x, int y, int mask);
        void set_wall(int x, int y);
        t_bool is_unknown(int x, int y);
        int get_priority(int x, int y, t_direction dir);
        int get_nextdir(int x, int y, int mask, t_direction *dir);
        void search_adachi(int gx, int gy);
        void InitMaze();
        static void logging(void*);
    
    protected:
        float local_rad;
        SemaphoreHandle_t log_stop = NULL;
        
};

#endif