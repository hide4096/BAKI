//#include "structs.hpp"
#include "include/Interrupt.hpp"
//#include <iostream>
//#include <string>
//#include <memory>
//#include <vector>



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


#define MMPP mot.tire_diameter * M_PI / ENC_MAX


void calc_target(){ //  目標値を計算する

    /*std::cout << "m_val.tar.vel : " << m_val.tar.vel << std::endl;
    std::cout << "m_val.max.vel : " << m_val.max.vel << std::endl;
    std::cout << "motion.acc : " << motion.acc << std::endl;
    std::cout << "calc_target" << std::endl;*/

    m_val.tar.vel += (motion.acc) / 1000.0;

    if (m_val.tar.vel > m_val.max.vel)
    {
        m_val.tar.vel = m_val.max.vel;
    }

    //motion.len += m_val.tar.vel;
    ct.I.tar.vel += m_val.tar.vel; // 目標積分値更新

    /*std::cout << "motion.len : " << motion.len << std::endl;

    std::cout << "m_val.tar.ang_vel : " << m_val.tar.ang_vel << std::endl;
    std::cout << "m_val.max.ang_vel : " << m_val.max.ang_vel << std::endl;
    std::cout << "motion.ang_acc : " << motion.ang_acc << std::endl;*/

    m_val.tar.ang_vel += (motion.ang_acc) / 1000.0;
    
    if (motion.flag == LEFT)
    {
       

        if (m_val.tar.ang_vel > m_val.max.ang_vel)
        {
            m_val.tar.ang_vel = m_val.max.ang_vel;
        }

       // motion.rad += m_val.tar.ang_vel;
       
    }
    else if (motion.flag == RIGHT)
    {

        if (m_val.tar.ang_vel < m_val.max.ang_vel)
        {
            m_val.tar.ang_vel = m_val.max.ang_vel;
        }

    }

    ct.I.tar.ang_vel += m_val.tar.ang_vel;  // 目標角速度積分値更新

    //std::cout << "motion.rad : " << motion.rad << std::endl;
    

    
    return;
}
void wall_ctl(){    //  壁制御
    //std::cout << "wall_ctl" << std::endl;
    return;
}
void FB_ctl(){  //フィードバック制御
    
    // 速度制御
    motion.error = m_val.tar.vel - motion.vel;
    m_val.I.error += motion.error / 1000.0;
    ct.P.error = (ct.P.vel - motion.vel) * 1000.0;

    ct.V_l = motion.error * (ct.v.Kp) + m_val.I.error * (ct.v.Ki) - ct.P.error * (ct.v.Kd);
    ct.V_r = motion.error * (ct.v.Kp) + m_val.I.error * (ct.v.Ki) - ct.P.error * (ct.v.Kd);

    // 角速度制御
    motion.ang_error = m_val.tar.ang_vel - motion.ang_vel;
    m_val.I.ang_error += motion.ang_error / 1000.0;
    ct.P.ang_error = (ct.P.ang_vel - motion.ang_vel) * 1000.0;

    ct.V_l += motion.ang_error * (ct.o.Kp) + m_val.I.ang_error * (ct.o.Ki) - ct.P.ang_error * (ct.o.Kd);
    ct.V_r -= motion.ang_error * (ct.o.Kp) + m_val.I.ang_error * (ct.o.Ki) - ct.P.ang_error * (ct.o.Kd);

    ct.Duty_l = ct.V_l / ct.Vatt;
    ct.Duty_r = ct.V_r / ct.Vatt;

    setMotorSpeed(ct.Duty_l, ct.Duty_r, 0.0);

    

    //std::cout << "FB_ctl" << std::endl;
    return;
}

void calc_dist(){   //  走行距離を計算する


    // エンコーダの値を取得
    enc.enc_data.l = - encL.readAngle();
    enc.enc_data.r = encR.readAngle();


    enc.locate.l = enc.enc_data.l;
    enc.locate.r = enc.enc_data.r;

    // 差分を計算
    enc.diff_pulse.l = enc.locate.l - enc.p_locate.l;
    enc.diff_pulse.r = enc.locate.r - enc.p_locate.r;

    // 制御１周期分前の値を保持
    enc.p_locate.l = enc.locate.l;
    enc.p_locate.r = enc.locate.r;

    if(enc.diff_pulse.l > ENC_HALF) enc.diff_pulse.l -= ENC_MAX-1;
    if(enc.diff_pulse.l < -ENC_HALF) enc.diff_pulse.l += ENC_MAX-1;
    if(enc.diff_pulse.r > ENC_HALF) enc.diff_pulse.r -= ENC_MAX-1;
    if(enc.diff_pulse.r < -ENC_HALF) enc.diff_pulse.r += ENC_MAX-1;
    
    float len_L = enc.diff_pulse.l * MMPP;
    float len_R = enc.diff_pulse.r * MMPP;

    motion.len += (len_L + len_R) / 2.0;

    //std::cout << "motion.len : " << motion.len * 1000.0 << std::endl;

    m_dir.l.vel = (len_L / 1000.0) / 0.001; // 1ms
    m_dir.r.vel = (len_R / 1000.0) / 0.001;

    //std::cout << "m_dir.l.vel : " << m_dir.l.vel * 1000.0 << std::endl;
    //std::cout << "m_dir.r.vel : " << m_dir.r.vel *1 000.0 << std::endl;

    motion.vel = (m_dir.l.vel + m_dir.r.vel) / 2.0;

    //std::cout << "motion.vel : " << motion.vel << std::endl;

    m_val.I.vel += motion.vel; // 積分値更新

    ct.P.vel = motion.vel;
    
    //std::cout << "calc_dist" << std::endl;
    return;
}

void calc_ang(){    //  角度を計算する

   
    motion.ang_vel = (imu.gyroZ() - gy.gyro_ref) * (M_PI / 180.0);
    motion.rad += motion.ang_vel /1000.0;

    ct.P.ang_vel = motion.ang_vel;

    m_val.I.ang_vel += motion.ang_vel; // 角速度積分値更新

    //std::cout << "motion.rad : " << motion.rad << std::endl;

    //std::cout << "calc_ang" << std::endl;
    return;
}

void Interrupt(void* pvparam){    //  xtaskcreate

    while (1)
    {
        
        calc_target();
        wall_ctl();   
        FB_ctl();
        calc_dist();
        calc_ang();
        
        ct.time_count++;

        vTaskDelay(1);
    }
    
     
}