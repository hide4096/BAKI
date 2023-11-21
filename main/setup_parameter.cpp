#include "structs.hpp"


t_motion m;
t_control c;

void setupParameter(t_motion *&param, t_control *&pid)
{
    param = &m; //mのアドレスを指定
    pid = &c;


    param->vel.tar = 0;
    param->acc = 0;
    param->ang_vel.tar = 0;
    param->ang_acc = 0;
    param->deg.tar = 0;

    pid->v.Kp = 0;
    pid->v.Ki = 0;
    pid->v.Kd = 0;
    pid->o.Kp = 0;
    pid->o.Ki = 0;
    pid->o.Kd = 0;
    pid->d.Kp = 0;
    pid->d.Ki = 0;
    pid->d.Kd = 0;
    pid->wall.Kp = 0;



}

