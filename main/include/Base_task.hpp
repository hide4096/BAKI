#include "structs.hpp"

class Base_task{    // base class    タスクを作るときはこのクラスを継承する
    public:
        Base_task();
        virtual ~Base_task();
        virtual int main_task_1();
        virtual int search();
        virtual int run();
        virtual int stop();
        virtual int turn();
        virtual int back();
        virtual int slalom();
        virtual int log();

    protected:
        int m_mode;

};


class Search_task : public Base_task{
    public:
        Search_task();
        virtual int main_task_1() override;
        virtual int search() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

class Run_task : public Base_task{
    public:
        Run_task(int mode);
        virtual int main_task_1() override;
        virtual int run() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

class Turn_task : public Base_task{
    public:
        Turn_task(int mode);
        virtual int main_task_1() override;
        virtual int turn() override;
    
    protected:
        float deg;
        float ang_vel;
        float max_ang_vel;
        float end_ang_vel;
};

class Back_task : public Base_task{
    public:
        Back_task(int mode);
        virtual int main_task_1() override;
        virtual int back() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

class Slalom_task : public Base_task{
    public:
        Slalom_task(int mode);
        virtual int main_task_1() override;
        virtual int slalom() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

class Log_task : public Base_task{
    public:
        Log_task(int mode);
        virtual int main_task_1() override;
        virtual int log() override;
    
    protected:
        float vel;
        float acc;
        float ang_vel;
        float max_vel;
        float end_vel;
};

class Set { //set task
    public:
        void call_main_task_1(Base_task *task);
        void set_main_task_1(uint8_t _mode);
        void get_main_task_1(uint8_t _mode_num);
    private:
        uint8_t max_mode_num = 8;
};

