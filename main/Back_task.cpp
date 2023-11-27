#include "include/Back_task.hpp"

Back_task::Back_task() : Base_task() {}

int Back_task::main_task_1() {
    std::cout << "main_task_1 : Back" << std::endl;
    return 0;
}

int Back_task::back() {
    std::cout << "back" << std::endl;
    return 0;
}
