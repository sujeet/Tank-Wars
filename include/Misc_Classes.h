#ifndef MISC_CLASSES_H
#define MISC_CLASSES_H


class ID
{
public:
     int player_no;
     char tank_symbol;
     char falcon_symbol;
};

class Direction 
{
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
     Move (int);
     Move (bool shoot, int xdir, int ydir);
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
