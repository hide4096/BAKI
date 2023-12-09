// #include "structs.hpp"
#include "include/Interrupt.hpp"
// #include <iostream>
// #include <string>
// #include <memory>
// #include <vector>

t_bool flag;
t_local_dir l_dir;
t_sens_dir s_dir;
t_wall_sens w_sens;
t_gyro gyro;
t_enc enc;
t_motion motion;
t_motion_dir m_dir;
t_motion_val m_val;
t_motor mot;
t_pid pid;
t_control ct;
t_wall wall;
t_map map;
t_pos mypos;
t_odom odom;

SemaphoreHandle_t on_logging;

#define MMPP mot.tire_diameter *M_PI / ENC_MAX

void init_structs()
{
    memset(&s_dir, 0, sizeof(s_dir));
    memset(&w_sens, 0, sizeof(w_sens));
    memset(&gyro, 0, sizeof(gyro));
    memset(&enc, 0, sizeof(enc));
    memset(&motion, 0, sizeof(motion));
    memset(&m_dir, 0, sizeof(m_dir));
    memset(&m_val, 0, sizeof(m_val));
    memset(&mot, 0, sizeof(mot));
    memset(&pid, 0, sizeof(pid));
    memset(&ct, 0, sizeof(ct));
    memset(&wall, 0, sizeof(wall));
    memset(&map, 0, sizeof(map));
    memset(&mypos, 0, sizeof(mypos));
    memset(&odom, 0, sizeof(odom));
    mot.tire_diameter = 0.0132;
    mot.tire_radius = 0.0066;

    on_logging = xSemaphoreCreateBinary();

    return;
}

void calc_target()
{ //  目標値を計算する

    /*std::cout << "m_val.tar.vel : " << m_val.tar.vel << std::endl;
    std::cout << "m_val.max.vel : " << m_val.max.vel << std::endl;
    std::cout << "motion.acc : " << motion.acc << std::endl;
    std::cout << "calc_target" << std::endl;*/

    m_val.tar.vel += (motion.acc) / 1000.0;

    if (m_val.tar.vel > m_val.max.vel)
    {
        m_val.tar.vel = m_val.max.vel;
    }

    // motion.len += m_val.tar.vel;
    // ct.I.tar.vel += m_val.tar.vel; // 目標積分値更新

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

    // ct.I.tar.ang_vel += m_val.tar.ang_vel; // 目標角速度積分値更新

    // std::cout << "motion.rad : " << motion.rad << std::endl;

    return;
}
void wall_ctl() //  壁制御
{
    // 左前壁センサ
    if (w_sens.val.fl > w_sens.th_wall.fl)
    {
        w_sens.is_wall.FL = TRUE;
    }
    else
    {
        w_sens.is_wall.FL = FALSE;
    }

    // 右前壁センサ
    if (w_sens.val.fr > w_sens.th_wall.fr)
    {
        w_sens.is_wall.FR = TRUE;
    }
    else
    {
        w_sens.is_wall.FR = FALSE;
    }

    // 左壁センサ
    if (w_sens.val.l > w_sens.th_wall.l)
    {
        w_sens.is_wall.L = TRUE;
    }
    else
    {
        w_sens.is_wall.L = FALSE;
    }
    // 右壁センサ
    if (w_sens.val.r > w_sens.th_wall.r)
    {
        w_sens.is_wall.R = TRUE;
    }
    else
    {
        w_sens.is_wall.R = FALSE;
    }

    if (w_sens.val.l > w_sens.th_control.l)
    {
        w_sens.error.l = w_sens.val.l - w_sens.ref.l;
        w_sens.is_control.L = TRUE;
    }
    else
    {
        w_sens.error.l = 0;
        w_sens.is_control.L = FALSE;
    }
    
    if (w_sens.val.r > w_sens.th_control.r)
    {
        w_sens.error.r = w_sens.val.r - w_sens.ref.r;
        w_sens.is_control.R = TRUE;
    }
    else
    {
        w_sens.error.r = 0;
        w_sens.is_control.R = FALSE;
    }

    if (w_sens.enable == TRUE && w_sens.val.fl + w_sens.val.fr <= (w_sens.th_wall.fl + w_sens.th_wall.fr) * 5.0)
    {

        if (w_sens.is_control.L == TRUE && w_sens.is_control.R == TRUE)
        {
            motion.wall_error = w_sens.error.r - w_sens.error.l;
        }
        else if (w_sens.is_control.L == FALSE && w_sens.is_control.R == TRUE)
        {
            motion.wall_error = w_sens.error.r;
        }
        else if (w_sens.is_control.L == TRUE && w_sens.is_control.R == FALSE)
        {
            motion.wall_error = -(w_sens.error.l);
        }
        else
        {
            motion.wall_error = 0;
        }

        m_val.I.wall_error += motion.wall_error / 1000.0;
        ct.P.wall_error = (ct.P.wall_error - motion.wall_error) * 1000.0;

        m_val.tar.wall_val = motion.wall_error * (ct.wall.Kp) + m_val.I.wall_error * (ct.wall.Ki) - ct.P.wall_error * (ct.wall.Kd);
        m_val.tar.ang_vel = m_val.tar.wall_val;

        ct.P.wall_error = motion.wall_error;
    }
    xSemaphoreGive(on_logging);

    // std::cout << "wall_ctl" << std::endl;
    return;
}
void FB_ctl()
{ // フィードバック制御
    if (ct.control_flag == TRUE)
    {
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

        /*ct.Duty_l = ct.V_l / ct.Vatt;
        ct.Duty_r = ct.V_r / ct.Vatt;*/

        ct.Duty_l = ct.V_l / ct.Vatt;
        ct.Duty_r = ct.V_r / ct.Vatt;

        // std::cout << "ct.Duty_l : " << ct.Duty_l << std::endl;
        // std::cout << "ct.Duty_r : " << ct.Duty_r << std::endl;

        setMotorSpeed(ct.Duty_r, ct.Duty_l, 0.0);
    }
    else
    {
        setMotorSpeed(0.0, 0.0, 0.0);
    }

    // std::cout << "FB_ctl" << std::endl;
    return;
}

void calc_dist()
{ //  走行距離を計算する

    // エンコーダの値を取得
    enc.data.l = -encL.readAngle();
    enc.data.r = encR.readAngle();

    enc.locate.l = enc.data.l;
    enc.locate.r = enc.data.r;

    // 差分を計算
    enc.diff_pulse.l = enc.locate.l - enc.p_locate.l;
    enc.diff_pulse.r = enc.locate.r - enc.p_locate.r;

    // 制御１周期分前の値を保持
    enc.p_locate.l = enc.locate.l;
    enc.p_locate.r = enc.locate.r;

    if (enc.diff_pulse.l > ENC_HALF)
        enc.diff_pulse.l -= ENC_MAX - 1;
    if (enc.diff_pulse.l < -ENC_HALF)
        enc.diff_pulse.l += ENC_MAX - 1;
    if (enc.diff_pulse.r > ENC_HALF)
        enc.diff_pulse.r -= ENC_MAX - 1;
    if (enc.diff_pulse.r < -ENC_HALF)
        enc.diff_pulse.r += ENC_MAX - 1;

    float len_L = enc.diff_pulse.l * MMPP;
    float len_R = enc.diff_pulse.r * MMPP;

    motion.len += (len_L + len_R) / 2.0;

    // std::cout << "motion.len : " << motion.len * 1000.0 << std::endl;

    m_dir.l.vel = len_L / 0.001; // 1ms
    m_dir.r.vel = len_R / 0.001;

    // std::cout << "m_dir.l.vel : " << m_dir.l.vel * 1000.0 << std::endl;
    // std::cout << "m_dir.r.vel : " << m_dir.r.vel *1 000.0 << std::endl;

    motion.vel = (m_dir.l.vel + m_dir.r.vel) / 2.0;

    // std::cout << "motion.vel : " << motion.vel << std::endl;

    m_val.I.vel += motion.vel; // 積分値更新

    ct.P.vel = motion.vel;

    // std::cout << "calc_dist" << std::endl;
    return;
}

void calc_ang()
{ //  角度を計算する
    float _yaw = 0.0;
    if(!imu.in_survaeybias){
        _yaw = imu.gyroZ() - gyro.gyro_ref;
    }

    motion.ang_vel = _yaw * (M_PI / 180.0);

    motion.rad += motion.ang_vel / 1000.0;

    ct.P.ang_vel = motion.ang_vel;

    m_val.I.ang_vel += motion.ang_vel; // 角速度積分値更新

    // std::cout << "motion.rad : " << motion.rad << std::endl;

    // std::cout << "calc_ang" << std::endl;
    return;
}

void reset_I_gain()
{
    m_val.I.vel = 0.0;
    m_val.I.ang_vel = 0.0;
    m_val.I.wall_error = 0.0;
    return;
}

void Interrupt(void *pvparam)
{ //  xtaskcreate

    while (1)
    {

        calc_target();
        wall_ctl();
        FB_ctl();
        calc_dist();
        calc_ang();

        ct.time_count++;

        // std::cout << "ct.time_count : " << ct.time_count << std::endl;

        vTaskDelay(1);
    }
}
