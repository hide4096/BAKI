#ifndef SLALOM_TASK_HPP
#define SLALOM_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "interupt.hpp"

class Slalom_task : public Base_task{
    public:
        Slalom_task();
        virtual int main_task_1() override;
        virtual int slalom() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

#endif