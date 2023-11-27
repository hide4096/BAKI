#include "include/Log_task.hpp"

Log_task::Log_task() : Base_task() {}

int Log_task::main_task_1() {
    std::cout << "main_task_1 : Log" << std::endl;
    return 0;
}

int Log_task::log() {
    std::cout << "log" << std::endl;
    return 0;
}

