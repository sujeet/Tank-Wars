#include <iostream>
#include "Misc_Classes.h"

using namespace std;

void Direction::print ()
{
     cout << "Direction : " << xdir << " " << ydir << endl;
}

void Direction::get_from_integer (int inp)
{
     switch (inp){
     case 0:
          this->xdir = -1;
          this->ydir = 0;
          break;
     case 1:
          this->xdir = 1;
          this->ydir = 0;
          break;
     case 2:
          this->xdir = 0;
          this->ydir = 1;
          break;
     case 3:
          this->xdir = 0;
          this->ydir = -1;
          break;
     }
     
}

Move::Move() 
{
     this->shoot = false;
}

void Move::interpret_move (int user_move)
{
     if (user_move / 4 == 1)
          this->shoot = true;
     else
          this->shoot = false;
     this->dirn.get_from_integer (user_move % 4);
}

void Move::print() 
{
     cout << "Shoot " << boolalpha << shoot << endl;
     this->dirn.print();
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

void Position::print ()
{
     cout << "Position : " << x << " " << y << endl;
}
