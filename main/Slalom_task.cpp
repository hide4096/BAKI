#include "include/Slalom_task.hpp"

Slalom_task::Slalom_task() : Base_task() {}

int Slalom_task::main_task_1() {
    std::cout << "main_task_1 : Slalom" << std::endl;
    return 0;
}

int Slalom_task::slalom() {
    std::cout << "slalom" << std::endl;
    return 0;
}