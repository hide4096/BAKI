#include "Base_task.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

Base_task::Base_task(){}

Base_task::~Base_task() {}

int Base_task::main_task_1() { return 0; }

int Base_task::search() { return 0; }

int Base_task::run() { return 0; }

int Base_task::stop() { return 0; }

int Base_task::turn() { return 0; }

int Base_task::back() { return 0; }

int Base_task::slalom() { return 0; }

int Base_task::log() { return 0; }




Search_task::Search_task() : Base_task() {}

int Search_task::main_task_1() {
    run();
    turn();
    run();
    stop();
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Search_task::search() {
    std::cout << "search" << std::endl;
    return 0;
}

Run_task::Run_task(int mode) : Base_task() {}

int Run_task::main_task_1() {
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Run_task::run() {
    std::cout << "run" << std::endl;
    return 0;
}

Turn_task::Turn_task(int mode) : Base_task() {}

int Turn_task::main_task_1() {
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Turn_task::turn() {
    std::cout << "turn" << std::endl;
    return 0;
}

Back_task::Back_task(int mode) : Base_task() {}

int Back_task::main_task_1() {
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Back_task::back() {
    std::cout << "back" << std::endl;
    return 0;
}

Slalom_task::Slalom_task(int mode) : Base_task() {}

int Slalom_task::main_task_1() {
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Slalom_task::slalom() {
    std::cout << "slalom" << std::endl;
    return 0;
}

Log_task::Log_task(int mode) : Base_task() {}

int Log_task::main_task_1() {
    std::cout << "main_task_1" << std::endl;
    return 0;
}

int Log_task::log() {
    std::cout << "log" << std::endl;
    return 0;
}

void Set::call_main_task_1(Base_task *task){    //  ポインタを引数に取る
    task->main_task_1();    //  ポインタのメンバ関数を呼び出す（実行する関数の呼び出し）
}

std::vector<std::shared_ptr<Base_task>> setmode;    //  ポインタの配列を作成

void Set::set_main_task_1(uint8_t _mode){    //  使用可能な処理を登録（LEDで表現できる数の最大数を引数とする）
    uint8_t num = 0;
    

    setmode.push_back(std::make_shared<Search_task>(num));  //  ポインタを配列に追加（使用する処理の数だけ）
    setmode.push_back(std::make_shared<Run_task>(num));
    setmode.push_back(std::make_shared<Turn_task>(num));
    setmode.push_back(std::make_shared<Back_task>(num));
    setmode.push_back(std::make_shared<Slalom_task>(num));
    setmode.push_back(std::make_shared<Log_task>(num));
    
    std::cout << "setmode" << std::endl;
}


void Set::get_main_task_1(uint8_t _mode_num){
    Set set;
    set.set_main_task_1(max_mode_num);

    set.call_main_task_1(setmode[_mode_num].get());    //  ポインタの配列の中から、引数で指定した番号のポインタを呼び出す
    std::cout << "get_main_task_1" << std::endl;
}