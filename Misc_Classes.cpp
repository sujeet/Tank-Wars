#include <iostream>
#include <cstdlib>

#include "Misc_Classes.h"

#define DO_NOT_MOVE 10
#define MACHINE_GUN_SHOOT_ONCE_IN_THIS_MANY 5

using namespace std;

Direction::Direction()
{
     // By default goes up
     this->get_from_integer (0);
}

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
          // The following is used for unmovables
          // eg machine guns ect. (?)
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
