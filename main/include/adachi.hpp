#include "structs.hpp"
//#include "Base_task.hpp"
//#include "Search_task.hpp"

//void search_adachi(int gx, int gy, Search_task* search_task);
class Adachi{
    public:
        void init_map(int x, int y);
        void make_map(int x, int y, int mask);
        void set_wall(int x, int y);
        t_bool is_unknown(int x, int y);
        int get_priority(int x, int y, t_direction dir);
        int get_nextdir(int x, int y, int mask, t_direction *dir);
        void search_adachi(int gx, int gy);
    private:
        
};
void InitMaze();

