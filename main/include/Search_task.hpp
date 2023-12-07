#ifndef SEARCH_TASK_HPP
#define SEARCH_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include "Base_task.hpp"
#include "structs.hpp"
#include "Interrupt.hpp"

class Search_task : public Base_task{
    public:
        Search_task();
        virtual int main_task_1() override;
        virtual int search() override;
        virtual int run() override;
        virtual int turn_left() override;
        virtual int turn_right() override;
        virtual int turn_half() override;
    
    protected:
        float local_rad;
};

#endif