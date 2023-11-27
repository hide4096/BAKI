#ifndef LOG_TASK_HPP
#define LOG_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "interupt.hpp"

class Log_task : public Base_task{
    public:
        Log_task();
        virtual int main_task_1() override;
        virtual int log() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

#endif