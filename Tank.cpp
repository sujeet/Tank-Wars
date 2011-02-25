#include <ctime>
#include <cstdlib>

#include "Tank.h"
#include "Map.h"

using namespace std;

void Tank::initialize_from (int given_player_no, char symbol, int init_x, int init_y, char falcon_symbol, int falcon_init_x, int falcon_init_y)
{
     // Initialize a tank's symbol and initial position
     this->symbol = symbol;
     this->curr_posn.x = init_x;
     this->curr_posn.y = init_y;
     this->prev_posn = this->curr_posn;

     this->falcon.symbol = falcon_symbol;
     this->falcon.posn.x = falcon_init_x;
     this->falcon.posn.y = falcon_init_y;
     

     this->id.player_no = given_player_no;
     this->id.tank_symbol = symbol;
     this->id.falcon_symbol = falcon_symbol;

     // Initialize Bullet Symbol
     if (symbol == '1'){
	  bullet_symbol = 'A';
     }
     else{
	  bullet_symbol = 'B';
     }
    
     
     dead_flag = false;
     score = 0;
}

void Tank::get_next_move (Info& info, int choice)
{

     // CHANGE THIS
//      this->next_move = info.strategic_moves_array[choice];
     // cerr << "shoot : " << boolalpha << this->next_move.shoot << endl;
     // cerr << "dirn  : " << this->next_move.dirn.xdir << " " << this->next_move.dirn.ydir << endl;
     

     // Call player function and get response
     // Just a random move returned as of now
     int temp;
#ifdef MOVE_DEBUG
     temp = MOVE_DEBUG;
#endif
#ifndef MOVE_DEBUG
     temp = rand () % 8;	
#endif
     this->next_move.interpret_move (temp);
}

void Tank::execute_next_move()
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

     // Move the bullets already shot by this tank 
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].move ();
     }
}

void Tank::move ()
{
     // Move Tank in the direction of the next move 

     this->prev_posn = this->curr_posn;
     this->curr_posn.go_in_direction (this->next_move.dirn);
//      this->curr_dirn = this->next_move.dirn;
}

void Tank::shoot_bullet ()
{
     // Shoot a new bullet in the direction given

     Bullet b;
     b.curr_dirn = this->next_move.dirn;
     b.curr_posn = this->curr_posn;
     b.prev_posn = b.curr_posn;
     b.symbol = this->bullet_symbol;
     this->bullet_list.push_back (b);
}

void Tank::evaluate_static_interactions (MapClass & Map)
{
     // Check if Tank is on a gold piece, or if it has crashed into a
     // wall and do the required. Do the same for its bullets

     unsigned int i;
     pick_up_gold_if_possible (Map);
     if (crashed_into_wall (Map)){
          die_by_wall_crash ();
     }

     // Check for bullet crashes
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].check_for_crashes (Map);
     }
     
}

bool Tank::is_killed_by (Tank t)
{
     // Check if Tank is killed by enemy tank t's bullets or has
     // crashed into it

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

     // TODO : Check for tank crossing later
     if (this->curr_posn == t.curr_posn){
          flag = true;
     }

     return flag;
}

void Tank::die_by_tank (Tank t)
{
     // Tank is dead; Will end the game after updating map
     this->dead_flag = true;
     t.incr_score(ENEMY_KILLED);
}

void Tank::pick_up_gold_if_possible (MapClass & Map)
{
     // Increment score, set curr_gold value for updating map later on
     if ( Map.is_symbol(curr_posn, GOLD) ){
          incr_score (PICKED_UP_GOLD);
     }
}

bool Tank::crashed_into_wall (MapClass & Map)
{
     // Increment score, set curr_gold value for updating map later on
     if ( Map.is_symbol(curr_posn, WALL) ){
          return true;
     }    
     return false;
}

void Tank::die_by_wall_crash ()
{
     // Die
     dead_flag = true;
}

void Tank::check_bullet_interactions (Tank t)
{
     // Check if any of Tank's bullets are colliding with t's bullets

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
     // Update score based on the event

     score += e;
}

void Tank::update_on_map (MapClass & Map)
{

#ifdef COUT_DEBUG
     cout << "Tank - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Tank - Curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif

     unsigned int i;
     
     // Update Tank's bullets' positions on the map
     for (i = 0; i < this->bullet_list.size (); i++) {
          bullet_list[i].update_on_map (Map);
     }

     bool flag = false;
     vector<Bullet>::iterator iter;

     // Delete Bullets that have crashed
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

     // Blank previous position on map
     Map.set_element (this->prev_posn, EMPTY);

     // Set current position on map
     if (this->dead_flag){
          Map.set_element (this->curr_posn, DEAD);
     }
     else
          Map.set_element (this->curr_posn, this->symbol);
}

void Tank::Bullet::move ()
{
     // Move Bullet forward

     this->prev_posn = this->curr_posn;
     this->curr_posn.go_in_direction (this->curr_dirn);
     
}

void Tank::Bullet::check_for_crashes (MapClass & Map)
{
     // Check if Bullet has collided with a GOLD piece or a WALL

     if ( Map.is_symbol(this->curr_posn, GOLD) 
          || Map.is_symbol(this->curr_posn, WALL) ){

          this->set_disappear_flag ();
     }
}

void Tank::Bullet::update_on_map (MapClass & Map)
{
     // Update Bullet on map

#ifdef COUT_DEBUG
     cout << "Bullet - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Bullet - curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif
     
     // Blank previous position
     Map.set_element (this->prev_posn, EMPTY);
     if (this->disappear_flag){
          // Map[curr_x][curr_y] = EMPTY;
          // the bullet died because it hit
          // something hence setting curr_coords
          // on the map as EMPTY is not correct

          // here, do something to delete the bullet
          // from the vector
     }
     // Set current position
     else {
          Map.set_element (this->curr_posn, this->symbol);
     }
}


void Tank::Falcon::set_dead_flag ()
{
     dead_flag = true;
}


bool Tank::Falcon::is_killed_by (Tank t)
{
     // Check if Falcon is killed by enemy tank t's bullets or has
     // been crashed into

     bool flag = false;
     unsigned int i;

     for (i = 0; i < t.bullet_list.size (); i++) {
          if (t.bullet_list[i].curr_posn == this->posn) {
               flag = true;
               break;
          }
     }

     if (flag)
          t.bullet_list[i].set_disappear_flag ();

     if (this->posn == t.curr_posn){
          flag = true;
     }

     return flag;
}

