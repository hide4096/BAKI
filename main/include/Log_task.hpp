#ifndef LOG_TASK_HPP
#define LOG_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "Interrupt.hpp"
#include "esp_flash_spi_init.h"
#include "esp_partition.h"
#include "esp_log.h"
#include "esp_flash.h"
#include "spi_flash_mmap.h"

class Log_task : public Base_task{
    public:
        Log_task();
        virtual int main_task_1() override;
        virtual int log() override;
        void log_print();
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

#endif