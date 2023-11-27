#include "include/Base_task.hpp"
//#include "include/interupt.hpp"

Base_task::Base_task(){}

Base_task::~Base_task() {}

int Base_task::main_task_1() { return 0; }    //  方向定義をここで行う（仮）

int Base_task::search() { return 0; }

int Base_task::run() { return 0; }

int Base_task::stop() { return 0; }

int Base_task::turn_left() { return 0; }

int Base_task::turn_right() { return 0; }

int Base_task::back() { return 0; }

int Base_task::slalom() { return 0; }

int Base_task::log() { return 0; }

void Base_task::cp_param(std::shared_ptr<t_motion> m){  //  ポインタをコピー
    set_m = m;
}

void Base_task::cp_tar(std::shared_ptr<t_motion_val> v){
    set_v = v;
}

void Base_task::cp_pid(std::shared_ptr<t_control> c){
    set_c = c;
}

void Base_task::cp_wall_th(std::shared_ptr<t_wall_sens> s){
    set_s = s;
}












