//#include "structs.hpp"
#include "include/Interrupt.hpp"
//#include <iostream>
//#include <string>
//#include <memory>
//#include <vector>

#define PI 3.14159265359

t_bool flag;
t_local_dir l_dir;
t_sens_dir s_dir;
t_wall_sens w_sens;
t_gyro gy;
t_enc enc;
t_motion motion;
t_motion_dir m_dir;
t_motion_val m_val;
t_motor mot;
t_pid pid;
t_control ct;
t_wall wall;
t_map map;
t_odom odom;





void calc_target(){
    //task->set_m->acc = 0.1;

    std::cout << "m_val.tar.vel : " << m_val.tar.vel << std::endl;
    std::cout << "m_val.max.vel : " << m_val.max.vel << std::endl;
    std::cout << "motion.acc : " << motion.acc << std::endl;
    std::cout << "calc_target" << std::endl;

    m_val.tar.vel += (motion.acc) / 1000.0;

    if (m_val.tar.vel > m_val.max.vel)
    {
        m_val.tar.vel = m_val.max.vel;
    }

    motion.len += m_val.tar.vel;

    std::cout << "motion.len : " << motion.len << std::endl;

    std::cout << "m_val.tar.ang_vel : " << m_val.tar.ang_vel << std::endl;
    std::cout << "m_val.max.ang_vel : " << m_val.max.ang_vel << std::endl;
    std::cout << "motion.ang_acc : " << motion.ang_acc << std::endl;

    m_val.tar.ang_vel += (motion.ang_acc) / 1000.0;
    
    if (motion.flag == LEFT)
    {
       

        if (m_val.tar.ang_vel > m_val.max.ang_vel)
        {
            m_val.tar.ang_vel = m_val.max.ang_vel;
        }

        motion.rad += m_val.tar.ang_vel;
    }
    else if (motion.flag == RIGHT)
    {

        if (m_val.tar.ang_vel < m_val.max.ang_vel)
        {
            m_val.tar.ang_vel = m_val.max.ang_vel;
        }

    }

    std::cout << "motion.rad : " << motion.rad << std::endl;
    

    
    return;
}
void wall_ctl(){
    std::cout << "wall_ctl" << std::endl;
    return;
}
void FB_ctl(){
    
    motion.error = m_val.tar.vel - motion.vel;
    m_val.I.error += ct.I.tar.vel - m_val.I.vel;
    ct.P.error = ct.P.vel - motion.vel;

    ct.V_l += motion.error * (ct.v.Kp) + m_val.I.error * (ct.v.Ki) - ct.P.error * (ct.v.Kd);
    ct.V_r += motion.error * (ct.v.Kp) + m_val.I.error * (ct.v.Ki) - ct.P.error * (ct.v.Kd);

    motion.ang_error = m_val.tar.ang_vel - motion.ang_vel;
    m_val.I.ang_error += ct.I.tar.ang_vel - m_val.I.ang_vel;
    ct.P.ang_error = ct.P.ang_vel - motion.ang_vel;

    ct.V_l += motion.ang_error * (ct.o.Kp) + m_val.I.ang_error * (ct.o.Ki) - ct.P.ang_error * (ct.o.Kd);
    ct.V_r -= motion.ang_error * (ct.o.Kp) + m_val.I.ang_error * (ct.o.Ki) - ct.P.ang_error * (ct.o.Kd);

    ct.Duty_l = ct.V_l / ct.Vatt;
    ct.Duty_r = ct.V_r / ct.Vatt;

    std::cout << "FB_ctl" << std::endl;
    return;
}

void calc_dist(){

    std::cout << "calc_dist" << std::endl;
    return;
}

void calc_ang(){

    ct.P.ang_vel = motion.ang_vel;
    motion.ang_vel = imu.gyroZ() * PI / 180.0;
    m_val.I.ang_vel += motion.ang_vel;
    motion.rad += motion.ang_vel;
    std::cout << "calc_ang" << std::endl;
    return;
}

void Interupt(){    //  xtaskcreate

    while (1)
    {
        calc_target();
        wall_ctl();   
        FB_ctl();
        calc_dist();
        calc_ang();
    }
    
     
    
    std::cout << "Interupt constructor called" << std::endl;
}
