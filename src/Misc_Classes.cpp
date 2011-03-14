#include <iostream>
#include <cstdlib>
#include<iomanip>

#include "Misc_Classes.h"
#include "Constants.h"


using namespace std;

Direction::Direction()
{
     // By default goes up
     this->get_from_integer (0);
}

Direction::Direction(int given_dirn)
{
     this->get_from_integer (given_dirn);
}

Direction::Direction(int xdir, int ydir)
{
    this->xdir = xdir;
    this->ydir = ydir;
}

bool Direction::operator== (Direction dirn)
{
     return (this->xdir == dirn.xdir && this->ydir == dirn.ydir);
}

void Direction::print ()
{
     switch((xdir + 4*ydir))
     {
         case -1:
             cout << setw (2) << 0;
             break;
         case 1:
             cout << setw (2) << 1;
             break;
         case -4:
             cout << setw (2) << 3;
             break;
         case 4:
             cout << setw (2) << 2;
             break;
     }
}

void Direction::get_from_integer (int inp)
{
     switch (inp){
     case UP:
          this->xdir = -1;
          this->ydir = 0;
          break;
     case DOWN:
          this->xdir = 1;
          this->ydir = 0;
          break;
     case RIGHT:
          this->xdir = 0;
          this->ydir = 1;
          break;
     case LEFT:
          this->xdir = 0;
          this->ydir = -1;
          break;
     case DO_NOT_MOVE:
	  this->xdir = 0;
	  this->ydir = 0;
	  break;
     }
}

Move::Move() 
{
     this->shoot = false;
}

Move::Move (int given_move)
{
     this->interpret_move (given_move);
}

Move::Move (bool shoot, int xdir, int ydir)
{
     this->shoot = shoot;
     this->dirn = Direction (xdir, ydir);
}

bool Move::is_valid ()
{
     // only the following combinations are valid.
     // 1, 0 | 0, 1 | -1, 0 | 0, -1
     int x = this->dirn.xdir;
     int y = this->dirn.ydir;
     if (x*x + y*y >= 2) {
          return false;
     }
     return true;
}

void Move::interpret_move (int user_move, bool is_machine_gun_move)
{
     if ( (not is_machine_gun_move) and (user_move / 4 == 1) ) {
          this->shoot = true;
     }
     else if ( (is_machine_gun_move) and (user_move / 4 == 1) ) {
          // Machine guns have 25% chance of shoooting
          int temp = rand() % MACHINE_GUN_SHOOT_ONCE_IN_THIS_MANY;
          if (!temp) {
               this->shoot = true;
          }
     }
     else {
          this->shoot = false;
     }

     if ( (is_machine_gun_move) and (this->shoot == false) ) {
// 	  this->dirn.get_from_integer (user_move % 4);
          this->dirn.get_from_integer (DO_NOT_MOVE);
     }
     else {
          this->dirn.get_from_integer (user_move % 4);
     }
}

void Move::print() 
{
     cout << "Shoot " << boolalpha << shoot << endl;
     this->dirn.print();
}

Position::Position ()
{
     x = y = 0;
}

Position::Position (int x, int y)
{
     this->x = x;
     this->y = y;
}

void Position::go_in_direction (Direction d)
{
     x += d.xdir;
     y += d.ydir;
}

bool Position::operator== (Position p)
{
     return ((this->x == p.x) && (this->y == p.y));
}

Position Position::get_neighbour (Direction d)
{
     Position temp = *this;
     temp.go_in_direction (d);
     return temp;
}


void Position::print ()
{
     cout << "Position : " << x << " " << y << endl;
}

Position Position::operator = (Position pos)
{
     this->x = pos.x;
     this->y = pos.y;
     return *this;
}

Move Move::operator = (Move mov)
{
     this->shoot = mov.shoot;
     this->dirn = mov.dirn;
     return *this;
}

Direction Direction::operator = (Direction dir)
{
     this->xdir = dir.xdir;
     this->ydir = dir.ydir;
     return *this;
}
