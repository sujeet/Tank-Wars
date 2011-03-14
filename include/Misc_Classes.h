#ifndef MISC_CLASSES_H
#define MISC_CLASSES_H


class ID
{
public:
     int player_no;
     char tank_symbol;
     char falcon_symbol;
     char my_bunker;
};

class Direction 
{
public:
     int xdir, ydir;
     
     // Methods
     Direction ();
     Direction (int xdir, int ydir);
     Direction (int);
     void get_from_integer (int inp);
     Direction operator = (Direction dir);
     bool operator== (Direction dirn);
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
     bool is_valid ();
};

class Position
{
public:
     int x, y;
     
     // Methods
     Position ();
     Position (int x, int y);
     Position get_neighbour (Direction);
     void go_in_direction (Direction d);
     Position operator = (Position pos);
     bool operator== (Position p);
     void print ();
};

#endif
