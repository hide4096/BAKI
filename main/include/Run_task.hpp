#ifndef RUN_TASK_HPP
#define RUN_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "interrupt.hpp"

class Run_task : public Base_task{
    public:
        Run_task();
        virtual int main_task_1() override;
        virtual int run() override;
    
    protected:
        float vel;
        float ang_vel;
        float deg;
        
};

#endif