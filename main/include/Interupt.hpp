#ifndef INTERUPT_HPP
#define INTERUPT_HPP

#include "Base_task.hpp"
//#include "Set.hpp"

class Interupt
{
    public:
        Interupt(Base_task* _task);
        ~Interupt();
        float calc_target(); //  目標値を計算する
        void wall_ctl();   //  壁制御
        void FB_ctl();    //  フィードバック制御
        void calc_dist();   //  距離を計算
        void calc_ang();    //  角度を計算
        
    private:
        std::shared_ptr<t_motion> param;
        std::shared_ptr<t_motion_val> val;
        std::shared_ptr<t_control> ctl;
        std::shared_ptr<t_wall_sens> sens;
        Base_task* task;

        float V_l = 0.0;
        float V_r = 0.0;
        float Duty_l = 0.0;
        float Duty_r = 0.0;
        float error = 0.0;
        float error_I = 0.0;
        float error_p = 0.0;
        float ang_error = 0.0;
        float ang_error_I = 0.0;
        float ang_error_p = 0.0;


};


#endif