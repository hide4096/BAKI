#ifndef TURN_TASK_HPP
#define TURN_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "Interrupt.hpp"

class Turn_task : public Base_task{
    public:
        Turn_task();
        virtual int main_task_1() override;
        virtual int turn_left() override;
        virtual int turn_right() override;
    
    protected:
        float local_rad;
        //t_local_dir Turn_flag;
};

#endif