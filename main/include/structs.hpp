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
    RIGHT = 1,
    REAR = 2,
    LEFT = 3,
    UNDEFINED,
}t_local_dir;

typedef enum
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
}t_direction;

typedef enum
{
    NOWALL = 0,
    WALL = 1,
    UNKNOWN = 2,
}t_is_wall;

typedef struct 
{
    int f;  //front
    int fl; //front left
    int fr; //front right
    int l;  //left
    int r;  //right
    int b;  //back
    t_bool FL;
    t_bool FR;
    t_bool L;
    t_bool R;
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
    t_sens_dir is_wall; //wall true or false
    t_sens_dir is_control;  //control true or false
    t_bool enable;  //enable or disable
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
    t_sens_dir data;
    t_sens_dir locate;
    t_sens_dir p_locate;
    t_sens_dir diff_pulse;
    t_sens_dir diff_p_pulse;    
}t_enc;     //encoder data

typedef struct 
{
    float vel;  //velocity
    float ang_vel;  //angular velocity
    float deg;  //degree
    float rad;  //radian
    float error; //error
    float ang_error;    //angular error
    float acc;  //acceleration
    float ang_acc;  //angular acceleration
    float len;   //length
    float wall_val;
    float wall_error;   //wall error
    float alpha;    //相補フィルタ用
    t_local_dir flag;
}t_motion;  //motion parameter

typedef struct 
{
    t_motion r;    //right
    t_motion l;    //left
}t_motion_dir;  //motion direction


typedef struct 
{
    t_motion_dir p;    //past
    t_motion_dir n;    //new
    t_motion max;  //max
    t_motion min;  //min
    t_motion end;   //end
    t_motion tar;   //target
    t_motion sum;   //sum
    t_motion I;    //integral
}t_motion_val;    //motion value

typedef struct 
{
    float tire_diameter;
    float tire_radius;
    //float R;
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
    t_motion_val I;    //integral
    t_motion P;
    float Vatt;
    float V_l;
    float V_r;
    float Duty_l;
    float Duty_r;
    int time_count;
    t_bool control_flag;
}t_control; //control parameter


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
    unsigned char size[32][32];
}t_map;     //map data

typedef struct
{
    short x;
    short y;
    t_direction dir;
}t_pos;     //position data


typedef struct 
{
    float x_pos;
    float y_pos;
}t_odom;    //odometry data


extern t_bool flag;
extern t_local_dir l_dir;
extern t_sens_dir s_dir;
extern t_wall_sens w_sens;
extern t_gyro gyro;
extern t_enc enc;
extern t_motion motion;
extern t_motion_dir m_dir;
extern t_motion_val m_val;
extern t_motor mot;
extern t_pid pid;
extern t_control ct;
extern t_wall wall;
extern t_map map;
extern t_pos mypos;
extern t_odom odom;


#endif  //  STRUCTS_HPP
