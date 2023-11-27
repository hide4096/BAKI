#include "include/Set.hpp"



std::vector<std::shared_ptr<Base_task>> setmode;    //  ポインタの配列を作成

void Set::set_main_task_1(uint8_t _mode){    //  使用可能な処理を登録（LEDで表現できる数の最大数を引数とする）
    

    setmode.push_back(std::make_shared<Search_task>());  //  ポインタを配列に追加（使用する処理の数だけ。最大数に気を付けて）
    setmode.push_back(std::make_shared<Run_task>());
    setmode.push_back(std::make_shared<Turn_task>());
    setmode.push_back(std::make_shared<Back_task>());
    setmode.push_back(std::make_shared<Slalom_task>());
    setmode.push_back(std::make_shared<Log_task>());
    
    std::cout << "setmode" << std::endl;
}


void Set::set_param(Base_task *task){

    param = std::make_shared<t_motion>();
    val = std::make_shared<t_motion_val>();
    ctl = std::make_shared<t_control>();
    sens = std::make_shared<t_wall_sens>();

    param->acc = 1.0;
    param->ang_acc = 0;
    val->tar.vel = 0.1;
    val->tar.ang_vel = 0;
    val->tar.deg = 0;
    val->tar.len = 90;
    val->max.vel = 0.3;
    val->max.ang_vel = 0;
    val->end.vel = 0;
    ctl->v.Kp = 0;
    ctl->v.Ki = 0;
    ctl->v.Kd = 0;
    ctl->o.Kp = 0;
    ctl->o.Ki = 0;
    ctl->o.Kd = 0;
    ctl->d.Kp = 0;
    ctl->d.Ki = 0;
    ctl->d.Kd = 0;
    ctl->wall.Kp = 0;
    ctl->wall.Ki = 0;
    ctl->wall.Kd = 0;
    sens->th_wall.fl = 0;
    sens->th_wall.fr = 0;
    sens->th_wall.l = 0;
    sens->th_wall.r = 0;
    sens->th_control.l = 0;
    sens->th_control.r = 0;

    ctl->I.tar.vel = 0;
    val->I.vel = 0;
    ctl->I.tar.ang_vel = 0;
    val->I.ang_vel = 0;
    ctl->I.tar.deg = 0;
    val->I.deg = 0;

    ctl->Vatt = 8.4;

    
    task->cp_param(param);
    task->cp_tar(val);
    task->cp_pid(ctl);
    task->cp_wall_th(sens);

    std::cout << "set_param" << std::endl;
}

void Set::call_main_task_1(Base_task *task){    //  ポインタを引数に取る
    
    task->main_task_1();    //  ポインタのメンバ関数を呼び出す（実行する関数の呼び出し
}

void Set::get_main_task_1(uint8_t _mode_num){
    set_main_task_1(max_mode_num);
    std::cout << "get_main_task_1" << std::endl;
    set_param(setmode[_mode_num].get());    //  パラメータを設定    main_task関数より先に呼ぶ
    call_main_task_1(setmode[_mode_num].get());    //  ポインタの配列の中から、引数で指定した番号のポインタを呼び出す
    
    return;
}