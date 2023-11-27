//#include "structs.hpp"
#include "include/interupt.hpp"
//#include <iostream>
//#include <string>
//#include <memory>
//#include <vector>

#define PI 3.14159265359
//Set set;

Interupt::Interupt(Base_task* _task) : task(_task){

    //set.set_param(task);
    
    std::cout << "Interupt constructor called" << std::endl;
}
Interupt::~Interupt(){
    std::cout << "Interupt destructor called" << std::endl;
}
float Interupt::calc_target(){
    //task->set_m->acc = 0.1;

    std::cout << "task->set_v->tar.vel : " << task->set_v->tar.vel << std::endl;
    std::cout << "task->set_m->acc : " << task->set_m->acc << std::endl;
    std::cout << "calc_target" << std::endl;

    task->set_v->tar.vel += (task->set_m->acc) / 1000.0;

    if (task->set_v->tar.vel > task->set_v->max.vel)
    {
        task->set_v->tar.vel = task->set_v->max.vel;
    }

    task->set_m->len += task->set_v->tar.vel;

    return task->set_m->len;
}
void Interupt::wall_ctl(){
    std::cout << "wall_ctl" << std::endl;
    return;
}
void Interupt::FB_ctl(){
    
    error = task->set_v->tar.vel - task->set_m->vel;
    error_I += task->set_c->I.tar.vel - task->set_v->I.vel;
    error_p = task->set_c->P.vel - task->set_m->vel;

    V_l += error * (task->set_c->v.Kp) + error_I * (task->set_c->v.Ki) - error_p * (task->set_c->v.Kd);
    V_r += error * (task->set_c->v.Kp) + error_I * (task->set_c->v.Ki) - error_p * (task->set_c->v.Kd);

    ang_error = task->set_v->tar.ang_vel - task->set_m->ang_vel;
    ang_error_I = task->set_c->I.tar.ang_vel - task->set_v->I.ang_vel;
    ang_error_p = task->set_c->P.ang_vel - task->set_m->ang_vel;

    V_l += ang_error * (task->set_c->o.Kp) + ang_error_I * (task->set_c->o.Ki) - ang_error_p * (task->set_c->o.Kd);
    V_r -= ang_error * (task->set_c->o.Kp) + ang_error_I * (task->set_c->o.Ki) - ang_error_p * (task->set_c->o.Kd);

    Duty_l = V_l / task->set_c->Vatt;
    Duty_r = V_r / task->set_c->Vatt;

    std::cout << "FB_ctl" << std::endl;
    return;
}

void Interupt::calc_dist(){

    std::cout << "calc_dist" << std::endl;
    return;
}

void Interupt::calc_ang(){

    task->set_c->P.ang_vel = task->set_m->ang_vel;
    task->set_m->ang_vel = PI / 180.0;
    task->set_v->I.ang_vel += task->set_m->ang_vel;
    task->set_m->deg += task->set_m->ang_vel;
    std::cout << "calc_ang" << std::endl;
    return;
}

