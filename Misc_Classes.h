#ifndef MISC_CLASSES_H
#define MISC_CLASSES_H


#define GOLD                'G'
#define WALL                '#'
#define EMPTY               '.'
#define DEAD                'D'

#define TANK1               '1'
#define FALCON1             'F'
#define BULLET1             'A'

#define TANK2               '2'
#define FALCON2             'E'
#define BULLET2             'B'

#define MACHINE_GUN         'M'
#define MACHINE_GUN_BULLET  'K'

enum event
{
     ENEMY_KILLED = 100, PICKED_UP_GOLD = 40
};

class Direction 
{
     // 0 : UP
     // 1 : DOWN
     // 2 ; RIGHT
     // 3 : LEFT
public:
     int xdir, ydir;
     
     // Methods
     Direction ();
     Direction (int xdir, int ydir);
     void get_from_integer (int inp);
     Direction operator = (Direction dir);
     void print ();
};

class Move
{
public:
     bool shoot;
     Direction dirn;
     Move ();
     Move operator = (Move mov);
     void interpret_move (int user_move, bool is_machine_gun_move = false);
     void print ();
};

class Position
{
public:
     int x, y;
     
     // Methods
     Position ();
     Position (int x, int y);
     void go_in_direction (Direction d);
     Position operator = (Position pos);
     bool operator== (Position p);
     void print ();
};

#endif
