#include "include/Run_task.hpp"


Run_task::Run_task() : Base_task() {}

int Run_task::main_task_1() {
    gyro.gyro_ref = imu.surveybias(1000);
    motion.rad = 0.0;
    run();
    std::cout << "main_task_1 : Run" << std::endl;
    return 0;
    
    
}

int Run_task::run() {

    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    reset_I_gain(); // 積分値リセット

    motion.len = 0.0; // 走行距離リセット
  
    while (((set_v->tar.len - 0.01) - motion.len) > 1000.0 * (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    motion.acc = -(set_m->acc);

    while (set_v->tar.len > motion.len)
    {
        if (m_val.tar.vel <= set_v->min.vel)
        {
            motion.acc = 0;
            m_val.tar.vel = set_v->min.vel;
        }
        vTaskDelay(1);
        
    }
    
    m_val.tar.vel = 0.0;
    motion.acc = 0.0;

    ct.control_flag = FALSE;
    
    std::cout << "run" << std::endl;
    return 0;
}
