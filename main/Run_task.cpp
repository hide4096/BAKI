#include "include/Run_task.hpp"


Run_task::Run_task() : Base_task() {}

int Run_task::main_task_1() {
    
    std::cout << "main_task_1 : Run" << std::endl;
    run();
    return 0;
    
    
}

int Run_task::run() {

    w_sens.enable = TRUE;

    std::cout << "set_v->tar.len : " << set_v->tar.len << std::endl;
    std::cout << "set_v->tar.vel : " << set_v->tar.vel << std::endl;
    std::cout << "set_m->acc : " << set_m->acc << std::endl;

    m_val.max.vel = set_v->max.vel;
    motion.acc = set_m->acc;
  
    while (((set_v->tar.len - 10) - motion.len) > 1000.0 * (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
        calc_target();
        calc_l = ((set_v->tar.len - 10) - motion.len);
        calc_r = 1000.0 * (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc));
        std::cout << "calc_l : " << calc_l << std::endl;
        std::cout << "calc_r : " << calc_r << std::endl;
        

    }

    std::cout << "##### deceleration #####" << std::endl;
    motion.acc = -(set_m->acc);

    while (set_v->tar.len > motion.len)
    {
        calc_target();
        if (m_val.tar.vel <= set_v->min.vel)
        {
            motion.acc = 0;
        }
        std::cout << "set_v->min.vel: " << set_v->min.vel << std::endl;

        
    }
    
    

    //tar_speed = interrupt.calc_target();
    std::cout << "set_m->len : " << length << std::endl;
    

    
    std::cout << "run" << std::endl;
    return 0;
}
