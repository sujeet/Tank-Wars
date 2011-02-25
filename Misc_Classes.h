#ifndef MISC_CLASSES_H
#define MISC_CLASSES_H


enum event
{
     ENEMY_KILLED = 100, PICKED_UP_GOLD = 40
};

enum
{
     GOLD = 'G',
     WALL = '#',
     EMPTY = '.',
     EMPTY_DISPLAY = ' ',
     DEAD = 'D',
     BULLET = '*'
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
     void interpret_move (int user_move);
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
