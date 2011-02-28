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

Direction::Direction(int xdir, int ydir)
{
    this->xdir = xdir;
    this->ydir = ydir;
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
          // The following is used for unmovables
          // eg machine guns etc. (?)
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

void Move::interpret_move (int user_move, bool is_machine_gun_move)
{
     if ( (not is_machine_gun_move) and (user_move / 4 == 1) ) {
          this->shoot = true;
     }
     else if ( (is_machine_gun_move) and (user_move / 4 == 1) ) {
          // Machine guns have 25% chance of shoooting
          int temp = rand() % MACHINE_GUN_SHOOT_ONCE_IN_THIS_MANY;
          if (temp == 1) {
               this->shoot = true;
          }
     }
     else {
          this->shoot = false;
     }
     if ( (is_machine_gun_move) and (this->shoot == false) ) {
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
