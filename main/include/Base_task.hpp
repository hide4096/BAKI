#ifndef BASE_TASK_HPP
#define BASE_TASK_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "structs.hpp"
//#include "Interrupt.hpp"
//#include "Set.hpp"

class Base_task{    // base class    タスクを作るときはこのクラスを継承する
    public:
        Base_task();
        virtual ~Base_task();
        virtual int main_task_1();
        virtual int search();
        virtual int run();
        virtual int stop();
        virtual int turn_left();
        virtual int turn_right();
        virtual int turn_half();
        virtual int back();
        virtual int slalom();
        virtual int log();
        void cp_tar(std::shared_ptr<t_motion_val> v);
        void cp_param(std::shared_ptr<t_motion> m);
        void cp_pid(std::shared_ptr<t_control> c);
        void cp_wall_th(std::shared_ptr<t_wall_sens> s);
        std::shared_ptr<t_motion> set_m;
        std::shared_ptr<t_motion_val> set_v;
        std::shared_ptr<t_control> set_c;
        std::shared_ptr<t_wall_sens> set_s;
        std::shared_ptr<t_motion_dir> set_d;
        std::shared_ptr<t_local_dir> set_l;


    protected:
        int m_mode;
        float tar_speed;
        float length;
        float calc_l;
        float calc_r;
        //float V_l;
        //float V_r;

        

};




#endif