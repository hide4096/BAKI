#include "include/Search_task.hpp"



Search_task::Search_task() : Base_task() {}

int Search_task::main_task_1() {
    gyro.gyro_ref = imu.surveybias(1000);
    motion.rad = 0.0;
    mypos.x = 0;
    mypos.y = 0;
    mypos.dir = NORTH;

    search_1();
    std::cout << "main_task_1 : Search" << std::endl;
    return 0;
}

int Search_task::search() {
    run_half();

    stop();
    turn_right();
    run_half();

    stop();
    turn_half();
    run_half();

    stop();
    turn_left();
    run_half();

    stop();
    turn_half();
    std::cout << "search" << std::endl;
    return 0;
}

int Search_task::run() {

    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;
  
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

int Search_task::run_half() {

    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;
  
    while ((((set_v->tar.len / 2) - 0.01) - motion.len) > 1000.0 * (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    motion.acc = -(set_m->acc);

    while ((set_v->tar.len / 2) > motion.len)
    {
        if (m_val.tar.vel <= set_v->min.vel)
        {
            motion.acc = 0;
            m_val.tar.vel = set_v->min.vel;
        }
        vTaskDelay(1);
        
    }
    
    //m_val.tar.vel = 0.0;
    motion.acc = 0.0;

    //ct.control_flag = FALSE;
    
    std::cout << "run" << std::endl;
    return 0;
}

int Search_task::turn_left() {    // 左旋回が正
    
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF
    motion.flag = LEFT; // 左旋回

    m_val.max.ang_vel = set_v->tar.ang_vel; // 目標（最大）角速度設定
    motion.ang_acc = set_m->ang_acc; // 角加速度設定

    m_val.I.error = 0.0;
    m_val.I.ang_error = 0.0;
    reset_I_gain(); // 積分値リセット
    
    //std::cout << "turn_left" << std::endl;
    int turn_count = 0;

    local_rad = motion.rad; // 現在の角度を保存
    
    while(M_PI / 2 > (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;

    //std::cout << "turn_left" << std::endl;
    return 0;
}

int Search_task::turn_right() {
    
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF
    motion.flag = RIGHT; // 右旋回

    m_val.max.ang_vel = -(set_v->tar.ang_vel); // 目標（最大）角速度設定
    motion.ang_acc = -(set_m->ang_acc); // 角加速度設定

    reset_I_gain(); // 積分値リセット
    
    //std::cout << "turn_left" << std::endl;
    int turn_count = 0;

    local_rad = motion.rad; // 現在の角度を保存
    
    while(-(M_PI / 2) < (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    
    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;

    //std::cout << "turn_right" << std::endl;
    return 0;
}

int Search_task::turn_half() {
    
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF
    motion.flag = LEFT; // 左旋回

    m_val.max.ang_vel = set_v->tar.ang_vel; // 目標（最大）角速度設定
    motion.ang_acc = set_m->ang_acc; // 角加速度設定

    m_val.I.error = 0.0;
    m_val.I.ang_error = 0.0;
    reset_I_gain(); // 積分値リセット
    
    //std::cout << "turn_left" << std::endl;
    int turn_count = 0;

    local_rad = motion.rad; // 現在の角度を保存
    
    while(M_PI > (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;
    
    //std::cout << "turn_left" << std::endl;
    return 0;
}

int Search_task::stop() {
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;
  
    while ((((set_v->tar.len / 2) - 0.01) - motion.len) > 1000.0 * (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    motion.acc = -(set_m->acc);

    while ((set_v->tar.len / 2) > motion.len)
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

void Search_task::search_1() {
    gyro.gyro_ref = imu.surveybias(1000);
    motion.rad = 0.0;

    search_adachi(8,11);

    std::cout << "search" << std::endl;
    return;
}

