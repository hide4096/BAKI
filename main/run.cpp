#include "include/run.hpp"

runs::runs() {
    //std::cout << "run" << std::endl;
}
runs::~runs() {
    //std::cout << "~run" << std::endl;
}

void runs::cp_param(std::shared_ptr<t_motion> m){  //  ポインタをコピー
    set_m = m;
}

void runs::cp_tar(std::shared_ptr<t_motion_val> v){
    set_v = v;
}

void runs::cp_pid(std::shared_ptr<t_control> c){
    set_c = c;
}

void runs::cp_wall_th(std::shared_ptr<t_wall_sens> s){
    set_s = s;
}


int runs::run_90() {

    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定
    float end_vel = set_v->end.vel;

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;

	if (len_count == 7)
	{
		//set_v->tar.len = 45;
		m_val.tar.len = 0.045;
	}else{
		m_val.tar.len = set_v->tar.len;
	}
	
	
    while (((m_val.tar.len - 0.03) - motion.len) > (((m_val.tar.vel)*(m_val.tar.vel) - (end_vel)*(end_vel)) / (2.0 * 
    set_m->acc)))
    {
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    motion.acc = -(set_m->acc);

    while ((m_val.tar.len) > motion.len)
    {
        if (m_val.tar.vel <= set_v->max.vel)
        {
            motion.acc = 0;
            m_val.tar.vel = set_v->max.vel;
        }
        vTaskDelay(1);
        
    }
    
    m_val.tar.vel = set_v->tar.vel;
    motion.acc = 0.0;

    //ct.control_flag = FALSE;
    
    std::cout << "run" << std::endl;
    return 0;
}

int runs::run_half() {

    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    float end_vel = m_val.tar.vel;

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;
  
    while ((((set_v->tar.len / 2.) - 0.03) - motion.len) > (((m_val.tar.vel)*(m_val.tar.vel) - (end_vel)*(end_vel)) / (2.0 * set_m->acc)))
    {
        vTaskDelay(1);
    }

    //std::cout << "##### deceleration #####" << std::endl;
    //motion.acc = -(set_m->acc);

    while ((set_v->tar.len / 2) > motion.len)
    {
        if (m_val.tar.vel <= end_vel)
        {
            motion.acc = 0;
            m_val.tar.vel = end_vel;
        }
        vTaskDelay(1);
        
    }
    
    //m_val.tar.vel = 0.0;
    motion.acc = 0.0;

    //ct.control_flag = FALSE;
    
    std::cout << "run" << std::endl;
    return 0;
}

int runs::turn_left() {    // 左旋回が正

	vTaskDelay(100);
    
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

int runs::turn_right() {

	vTaskDelay(100);
    
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

int runs::turn_half() {

	vTaskDelay(100);
    
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

int runs::stop() {
    ct.control_flag = TRUE; // 制御ON
    w_sens.enable = FALSE; // 壁制御OFF

    m_val.max.vel = set_v->max.vel; // 目標（最大）速度設定
    motion.acc = set_m->acc; // 加速度設定

    reset_I_gain(); // 積分値リセット
    motion.len = 0.0;
  
    while ((((set_v->tar.len / 2) - 0.05) - motion.len) > (((m_val.tar.vel)*(m_val.tar.vel) - (set_v->end.vel)*(set_v->end.vel)) / (2.0 * 
    set_m->acc)))
    {
		if(w_sens.val.fl > 750 && w_sens.val.fr > 750){
			break;
		}
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
			if(w_sens.val.fl > 750 && w_sens.val.fr > 750){
			break;
		}
        }
        vTaskDelay(1);
        
    }
    
    m_val.tar.vel = 0.0;
    motion.acc = 0.0;

    ct.control_flag = FALSE;
    
    std::cout << "run" << std::endl;
    return 0;
}