#ifndef STRUCTS_HPP
#define STRUCTS_HPP


typedef enum
{
    FALSE = 0,
    TRUE = 1,
}t_bool;

typedef enum
{
    FRONT = 0,
    LEFT = 1,
    RIGHT = 2,
    REAR = 3,
    UNKNOWN,
}t_local_dir;

typedef struct 
{
    int f;  //front
    int l;  //left
    int r;  //right
    int b;  //back
}t_sens_dir;    //sensor direction data

typedef struct 
{
    t_sens_dir val;  //sensor value
    t_sens_dir d_val;    //sensor value difference
    t_sens_dir p_val;    //sensor value past
    t_sens_dir error;    //sensor value error
    t_sens_dir ref;  //sensor value reference
    t_sens_dir th_wall;  //wall threshold value
    t_sens_dir th_control;   //control threshold value
    t_sens_dir wall; //wall true or false
    t_sens_dir control;  //control true or false
}t_wall_sens;  //wall sensor data

typedef struct 
{
    float gyro_yaw; //gyro yaw
    float gyro_yaw_new; //gyro yaw new
    float gyro_ref; //gyro reference
    float degree;
    float radian;
}t_gyro;    //gyro data

typedef struct 
{
    unsigned int angle;
    t_sens_dir locate;
    t_sens_dir p_locate;
    t_sens_dir diff_pulse;
    t_sens_dir diff_p_pulse;    
}t_enc;     //encoder data


typedef struct 
{
    float tire_diameter;
    float tire_radius;
    float R;
    float Kt;
    float Ke;
    float truque;
}t_motor;   //motor parameter

typedef struct 
{
    float Kp;   //proportional gain
    float Ki;   //integral gain
    float Kd;   //differential gain
}t_pid; //pid parameter

typedef struct 
{
    t_pid v;    //velocity pid
    t_pid o;    //omega pid
    t_pid d;    //degree pid
    t_pid wall; //wall pid
}t_control; //control parameter

typedef struct 
{
    float r;    //right
    float l;    //left
}t_motion_dir;  //motion direction


typedef struct 
{
    t_motion_dir p;    //past
    t_motion_dir n;    //new
    float sum;  //sum
    float max;  //max
    float tar;   //target
}t_motion_val;    //motion value


typedef struct 
{
    t_motion_val vel;  //velocity
    t_motion_val ang_vel;  //angular velocity
    t_motion_val deg;  //degree
    t_motion_val error; //error
    float acc;  //acceleration
    float ang_acc;  //angular acceleration
}t_motion;  //motion parameter

typedef struct 
{
    unsigned char north:2;
    unsigned char east:2;
    unsigned char south:2;
    unsigned char west:2;
    t_bool flag;
}t_wall;    //wall data

typedef struct 
{
    t_wall wall[32][32];
    unsigned char map[32][32];
}t_map;     //map data

typedef struct 
{
    float x;
    float y;
}t_odom;    //odometry data



#endif
