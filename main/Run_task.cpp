#include "include/Run_task.hpp"


Run_task::Run_task() : Base_task() {}

int Run_task::main_task_1() {
    
    std::cout << "main_task_1 : Run" << std::endl;
    run();
    return 0;
    
    
}

int Run_task::run() {

    //Interupt interupt(this);
    set_s->enable = TRUE;

    std::cout << "set_v->tar.len : " << set_v->tar.len << std::endl;
    std::cout << "set_v->tar.vel : " << set_v->tar.vel << std::endl;
    std::cout << "set_m->acc : " << set_m->acc << std::endl;

    //interupt.calc_target();
  
    while (((set_v->tar.len - 10) - set_m->len) > 1000.0 * (((set_v->tar.vel)*(set_v->tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
        length = //interupt.calc_target();
        calc_l = ((set_v->tar.len - 10) - set_m->len);
        calc_r = 1000.0 * (((set_v->tar.vel)*(set_v->tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc));
        std::cout << "calc_l : " << calc_l << std::endl;
        std::cout << "calc_r : " << calc_r << std::endl;

    }

    set_m->acc = -(set_m->acc);

    while (set_v->tar.len > set_m->len)
    {
        //length = interupt.calc_target();
        if (set_v->tar.vel > set_v->end.vel)
        {
            set_m->acc = 0;
        }
        
    }
    

    //tar_speed = interupt.calc_target();
    std::cout << "set_m->len : " << length << std::endl;
    

    
    std::cout << "run" << std::endl;
    return 0;
}
