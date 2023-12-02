#include "include/Turn_task.hpp"

Turn_task::Turn_task() : Base_task() {}

int Turn_task::main_task_1() {
    turn_left();
    //turn_right();
    std::cout << "main_task_1 : Turn" << std::endl;
    return 0;
}

int Turn_task::turn_left() {
    
    w_sens.enable = FALSE;
    motion.flag = LEFT;

    m_val.max.ang_vel = set_v->tar.ang_vel;
    motion.ang_acc = set_m->ang_acc;
    


    local_rad = motion.rad;
    while((set_v->tar.rad - (motion.rad - local_rad)) > (m_val.tar.ang_vel * m_val.tar.ang_vel) / (2.0 * set_m->ang_acc)){
        calc_target();
        calc_l = ((set_v->tar.rad - local_rad) - motion.rad);
        calc_r = (m_val.tar.ang_vel * m_val.tar.ang_vel) / (2.0 * set_m->ang_acc);
        std::cout << "calc_l : " << calc_l << std::endl;
        std::cout << "calc_r : " << calc_r << std::endl;
        std::cout << "motion.rad : " << motion.rad << std::endl;

    }

    std::cout << "##### deceleration #####" << std::endl;

    motion.ang_acc = -(set_m->ang_acc);
    while(set_v->tar.rad > (motion.rad - local_rad)){
        calc_target();
        std::cout << "motion.rad : " << motion.rad << std::endl;
    }

    
    std::cout << "turn_left" << std::endl;
    return 0;
}

int Turn_task::turn_right() {
    
    set_s->enable = FALSE;
    set_m->flag = LEFT;
    
    local_rad = set_m->deg;
    while((set_v->tar.deg - (set_m->deg - local_rad)) > (set_v->tar.ang_vel * set_v->tar.ang_vel) / (2.0 * set_m->ang_acc)){
        std::cout << "set_m->deg : " << set_m->deg << std::endl;

    }
    set_m->ang_acc = -(set_m->ang_acc);
    while(set_v->tar.deg > (set_m->deg - local_rad)){
        std::cout << "set_m->deg : " << set_m->deg << std::endl;
    }

    
    std::cout << "turn_right" << std::endl;
    return 0;
}