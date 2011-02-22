#include "Tank.h"
#include <ctime>
#include <cstdlib>

using namespace std;

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

void Move::interpret_move (int user_move)
{
     if (user_move / 4 == 1)
          this->shoot = true;
     else
          this->shoot = false;
     this->dirn.get_from_integer (user_move % 4);
     
}


void Tank::initialize_from (char symbol, int init_x, int init_y)
{
     this->symbol = symbol;
     this->curr_posn.x = init_x;
     this->curr_posn.y = init_y;
     this->prev_posn = this->curr_posn;
     
     dead_flag = false;
     score = 0;
}

void Tank::get_next_move ()
{
     // Call player function and get response
     int temp;
#ifdef MOVE_DEBUG
     temp = MOVE_DEBUG;
#endif
#ifndef MOVE_DEBUG
     temp = rand () % 4;	
#endif
     this->next_move.interpret_move (temp);
}

void Tank::update()
{
     // Call either this.move () or this.shoot_bullet ()
     // Call bullet_list[i].move () for every bullet_list[i] in bullet_list
     unsigned int i;
     if (this->next_move.shoot){
          this->shoot_bullet ();
     }
     else{
          this->move ();
     }
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].move ();
     }
}

void Tank::move ()
{
     this->prev_posn = this->curr_posn;
     this->curr_posn.go_in_direction (this->next_move.dirn);
//      this->curr_dirn = this->next_move.dirn;
}


void Tank::evaluate_state (char Map[][NUMBER])
{
     // Check if on_gold (), if crashed_into_wall ()
     // etc. and call their respective functions
     unsigned int i;
     pick_up_gold_if_possible (Map);
     if (crashed_into_wall (Map)){
          die_by_wall_crash ();
     }
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].check_for_crashes (Map);
     }
     
}


bool Tank::is_killed_by (Tank t)
{
     bool flag = false;
     unsigned int i;
     for (i = 0; i < t.bullet_list.size (); i++) {
          if (t.bullet_list[i].curr_posn == this->curr_posn) {
               flag = true;
               break;
          }
     }

     if (flag)
          t.bullet_list[i].set_disappear_flag ();

     // Check for tank crossing later
     if (this->curr_posn == t.curr_posn){
          flag = true;
     }
     return flag;
}

void Tank::die_by_tank (Tank t)
{
     this->dead_flag = true;
     t.incr_score(ENEMY_KILLED);
}


void Tank::pick_up_gold_if_possible (char Map[][NUMBER])
{
     // Increment score, set curr_gold value for updating map later on
     int map_x = this->curr_posn.x;
     int map_y = this->curr_posn.y;

     if (Map[map_x][map_y] == GOLD){
          incr_score (PICKED_UP_GOLD);
     }
}

bool Tank::crashed_into_wall (char Map[][NUMBER])
{
     // Increment score, set curr_gold value for updating map later on
     int map_x = this->curr_posn.x;
     int map_y = this->curr_posn.y;

     if (Map[map_x][map_y] == WALL){
          return true;
     }    
     return false;
}

void Tank::die_by_wall_crash ()
{
     dead_flag = true;
}

void Tank::shoot_bullet ()
{
     Bullet b;
     b.curr_dirn = this->next_move.dirn;
     b.curr_posn = this->curr_posn;
     b.prev_posn = b.curr_posn;
     this->bullet_list.push_back (b);
}

void Tank::check_bullet_interactions (Tank t)
{
     unsigned int i, j;
     for (i = 0; i < this->bullet_list.size (); i++) {
          for (j = 0; j < t.bullet_list.size (); j++) {
               if (this->bullet_list[i].curr_posn
                   == t.bullet_list[j].curr_posn){
                    this->bullet_list[i].set_disappear_flag ();
               }
          }
     }
}

void Tank::incr_score (event e)
{
     score += e;
}


void Tank::update_on_map (char Map[][NUMBER])
{
#ifdef COUT_DEBUG
     cout << "Tank - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Tank - Curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif


     int prev_x = this->prev_posn.x;
     int prev_y = this->prev_posn.y;
     int curr_x = this->curr_posn.x;
     int curr_y = this->curr_posn.y;
     unsigned int i;
     
     for (i = 0; i < this->bullet_list.size (); i++) {
          bullet_list[i].update_on_map (Map);
     }
//      cout << endl;
//      cout << "Before : " << endl;
//      this->print_bullets ();
//      for (i = 0; i < this->bullet_list.size (); i++) {
     bool flag = false;
     vector<Bullet>::iterator iter;
     while (1){
          iter = bullet_list.begin ();
          while (iter != bullet_list.end ()){
               if ((*iter).disappear_flag) {
                    flag = true;
                    break;
               }
               iter++;
          }
          if (flag){
               flag = false;
               bullet_list.erase(iter);
          }
          else{
               break;
          }
     }

//      cout << endl;
//      cout << "After : " << endl;
//      this->print_bullets ();
     Map[prev_x][prev_y] = EMPTY;
     if (this->dead_flag){
          Map[curr_x][curr_y] = DEAD;
     }
     else
          Map[curr_x][curr_y] = this->symbol ;
}

void Tank::Bullet::move ()
{
     this->prev_posn = this->curr_posn;
     this->curr_posn.go_in_direction (this->curr_dirn);
     
}

void Tank::Bullet::check_for_crashes (char Map[][NUMBER])
{
     int map_x = this->curr_posn.x;
     int map_y = this->curr_posn.y;
     
     if (Map[map_x][map_y] == GOLD || Map[map_x][map_y] == WALL){
          this->set_disappear_flag ();
     }
}

// void Tank::Bullet::mark_danger_zones (char Map[][NUMBER]) 
// {
//      int x_dir = this->curr_dirn.xdir;
//      int y_dir = this->curr_dirn.ydir;
//      int x_posn = this->curr_posn.x;
//      int y_posn = this->curr_posn.y;
//      for (int i = 0; i < BULLET_SPEED; i++) {
//           x_posn += x_dir;
//           y_posn += y_dir;
//           if (Map[x_posn][y_posn] == EMPTY) {
//                Map[x_posn][y_posn] = DANGER;
//           }
//      }
// }

void Tank::Bullet::update_on_map (char Map[][NUMBER])
{
#ifdef COUT_DEBUG
     cout << "Bullet - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Bullet - curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif
     int prev_x = this->prev_posn.x;
     int prev_y = this->prev_posn.y;
     int curr_x = this->curr_posn.x;
     int curr_y = this->curr_posn.y;
     
     Map[prev_x][prev_y] = EMPTY;
     if (this->disappear_flag){
          // Map[curr_x][curr_y] = EMPTY;
          // the bullet died because it hit
          // something hence setting curr_coords
          // on the map as EMPTY is not correct

          // here, do something to delete the bullet
          // from the vector
     }
     else {
          Map[curr_x][curr_y] = BULLET;
     }
}


