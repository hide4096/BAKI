#ifndef SEARCH_TASK_HPP
#define SEARCH_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "interupt.hpp"

class Search_task : public Base_task{
    public:
        Search_task();
        virtual int main_task_1() override;
        virtual int search() override;
        
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

#endif