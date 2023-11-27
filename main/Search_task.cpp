#include "include/Search_task.hpp"

Search_task::Search_task() : Base_task() {}

int Search_task::main_task_1() {
    run();
    turn_left();
    run();
    stop();
    std::cout << "main_task_1 : Search" << std::endl;
    return 0;
}

int Search_task::search() {
    std::cout << "search" << std::endl;
    return 0;
}
