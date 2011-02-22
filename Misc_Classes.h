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
     void get_from_integer (int inp);
     void print ();
};

class Move
{
public:
     bool shoot;
     Direction dirn;
     Move ();
     void interpret_move (int user_move);
     void print ();
};

class Position
{
public:
     int x, y;
     
     void go_in_direction (Direction d);
     bool operator== (Position p);
     void print ();
};

#endif
