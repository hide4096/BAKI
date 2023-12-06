#include "include/Set.hpp"



std::vector<std::shared_ptr<Base_task>> setmode;    //  ポインタの配列を作成

void set_main_task_1(uint8_t _mode){    //  使用可能な処理を登録（LEDで表現できる数の最大数を引数とする）
    

    setmode.push_back(std::make_shared<Search_task>());  //  ポインタを配列に追加（使用する処理の数だけ。最大数に気を付けて）
    setmode.push_back(std::make_shared<Run_task>());
    setmode.push_back(std::make_shared<Turn_task>());
    setmode.push_back(std::make_shared<Back_task>());
    setmode.push_back(std::make_shared<Slalom_task>());
    setmode.push_back(std::make_shared<Log_task>());
    
    std::cout << "setmode" << std::endl;
}


void set_param(Base_task *task){

    std::shared_ptr<t_motion> param = std::make_shared<t_motion>();
    std::shared_ptr<t_motion_val> val = std::make_shared<t_motion_val>();
    std::shared_ptr<t_control> ctl = std::make_shared<t_control>();
    std::shared_ptr<t_wall_sens> sens = std::make_shared<t_wall_sens>();

    param->acc = 0.0;
    param->ang_acc = 0.0;
    val->tar.vel = 0.0;
    val->tar.ang_vel = M_PI;
    val->tar.rad = M_PI / 2.0;
    val->tar.len = 90;
    val->max.vel = 0.0;
    val->max.ang_vel = 0.0;
    val->min.vel = 0.0;
    val->end.vel = 0.0;

    // 速度制御ゲイン
    ctl->v.Kp = ct.v.Kp = 1.0;   // 1.5 2.0
    ctl->v.Ki = ct.v.Ki = 300.0; // 400.0 300.0
    ctl->v.Kd = ct.v.Kd = 0.0;

    // 角速度制御ゲイン
    ctl->o.Kp = ct.o.Kp = 0.20; // 0.20
    ctl->o.Ki = ct.o.Ki = 80.0; // 80.0
    ctl->o.Kd = ct.o.Kd = 0.0;

    // 壁制御ゲイン
    ctl->wall.Kp = ct.wall.Kp = 0;
    ctl->wall.Ki = ct.wall.Ki = 0;
    ctl->wall.Kd = ct.wall.Kd = 0;


    // 壁センサ閾値
    sens->th_wall.fl = 0;
    sens->th_wall.fr = 0;
    sens->th_wall.l = 0;
    sens->th_wall.r = 0;
    sens->th_control.l = 0;
    sens->th_control.r = 0;

    ctl->Vatt = ct.Vatt = 8.4;

    
    task->cp_param(param);
    task->cp_tar(val);
    task->cp_pid(ctl);
    task->cp_wall_th(sens);

    std::cout << "set_param" << std::endl;
}

void call_main_task_1(Base_task *task){    //  ポインタを引数に取る
    
    task->main_task_1();    //  ポインタのメンバ関数を呼び出す（実行する関数の呼び出し
}

void get_main_task_1(uint8_t _mode_num){
    uint8_t max_mode_num = 8;

    set_main_task_1(max_mode_num);
    std::cout << "get_main_task_1" << std::endl;
    set_param(setmode[_mode_num].get());    //  パラメータを設定    main_task関数より先に呼ぶ
    call_main_task_1(setmode[_mode_num].get());    //  ポインタの配列の中から、引数で指定した番号のポインタを呼び出す
    
    return;
}