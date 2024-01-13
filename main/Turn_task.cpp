#include "include/Turn_task.hpp"

Turn_task::Turn_task() : Base_task() {}

int Turn_task::main_task_1() {
    //turn_check();
    //gyro.gyro_ref = imu.surveybias(1000);
    motion.rad = 0.0;
    //turn_left();
    //turn_right();
    //turn_half();
    turn_check();
    std::cout << "main_task_1 : Turn" << std::endl;
    return 0;
}

int Turn_task::turn_left() {    // 左旋回が正
    
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
    /*while((set_v->tar.rad - (motion.rad - local_rad)) > (m_val.tar.ang_vel * m_val.tar.ang_vel) / (2.0 * set_m->ang_acc)){
        turn_count++;
        printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }*/
    while(M_PI / 2 > (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    /*motion.ang_acc = -(set_m->ang_acc);

    while(set_v->tar.rad > (motion.rad - local_rad)){
        if (motion.ang_vel < set_v->min.ang_vel)
        {
            motion.ang_acc = 0.0;
            m_val.tar.ang_vel = set_v->min.ang_vel;
        }
        turn_count--;
        printf("turn_count : %d\n", turn_count);
        
        vTaskDelay(1);
    }*/
    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;


    /*while(motion.ang_vel >= 0.01 || motion.ang_vel <= -0.01){
        vTaskDelay(1);
    }*/
    
    //std::cout << "turn_left" << std::endl;
    return 0;
}

int Turn_task::turn_right() {
    
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF
    motion.flag = RIGHT; // 左旋回

    m_val.max.ang_vel = -(set_v->tar.ang_vel); // 目標（最大）角速度設定
    motion.ang_acc = -(set_m->ang_acc); // 角加速度設定

    reset_I_gain(); // 積分値リセット
    
    //std::cout << "turn_left" << std::endl;
    int turn_count = 0;

    local_rad = motion.rad; // 現在の角度を保存
    /*while((set_v->tar.rad - (motion.rad - local_rad)) > (m_val.tar.ang_vel * m_val.tar.ang_vel) / (2.0 * set_m->ang_acc)){
        turn_count++;
        printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }*/
    while(-(M_PI / 2) < (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    /*motion.ang_acc = -(set_m->ang_acc);

    while(set_v->tar.rad > (motion.rad - local_rad)){
        if (motion.ang_vel < set_v->min.ang_vel)
        {
            motion.ang_acc = 0.0;
            m_val.tar.ang_vel = set_v->min.ang_vel;
        }
        turn_count--;
        printf("turn_count : %d\n", turn_count);
        
        vTaskDelay(1);
    }*/
    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;


    /*while(motion.ang_vel >= 0.01 || motion.ang_vel <= -0.01){
        vTaskDelay(1);
    }*/

    //std::cout << "turn_right" << std::endl;
    return 0;
}

int Turn_task::turn_half() {
    
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
    /*while((set_v->tar.rad - (motion.rad - local_rad)) > (m_val.tar.ang_vel * m_val.tar.ang_vel) / (2.0 * set_m->ang_acc)){
        turn_count++;
        printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }*/
    while(M_PI > (motion.rad - local_rad)){
        turn_count++;
        //printf("turn_count : %d\n", turn_count);
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    ct.control_flag = FALSE;

    /*motion.ang_acc = -(set_m->ang_acc);

    while(set_v->tar.rad > (motion.rad - local_rad)){
        if (motion.ang_vel < set_v->min.ang_vel)
        {
            motion.ang_acc = 0.0;
            m_val.tar.ang_vel = set_v->min.ang_vel;
        }
        turn_count--;
        printf("turn_count : %d\n", turn_count);
        
        vTaskDelay(1);
    }*/
    m_val.tar.ang_vel = 0.0;
    motion.ang_acc = 0.0;


    /*while(motion.ang_vel >= 0.01 || motion.ang_vel <= -0.01){
        vTaskDelay(1);
    }*/
    
    //std::cout << "turn_left" << std::endl;
    return 0;
}

void Turn_task::turn_check() {
    std::cout << "turn_check" << std::endl;

    w_sens.enable = FALSE;
    ct.control_flag = TRUE; // 制御ON
    reset_I_gain(); // 積分値リセット
    //motion.flag = LEFT;

    //m_val.max.ang_vel = 0.0;
    //motion.ang_acc = 0.0;

    //m_val.tar.rad = 0.0;
    motion.rad = 0.0;
    motion.len = 0.0;

    while (1)
    {
        vTaskDelay(1);
    }
    
    return;
}   //  ターンチェック



