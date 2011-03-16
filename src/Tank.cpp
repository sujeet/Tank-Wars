#include <ctime>
#include <cstdlib>

#include "Tank.h"
#include "Constants.h"

using namespace std;

Tank::Tank (char symbol,
            char bullet_symbol,
            Position curr_posn,
            Position prev_posn,
            bool dead_flag)
{
     this->symbol = symbol;
     this->bullet_symbol = bullet_symbol;
     this->curr_posn = curr_posn;
     this->prev_posn = prev_posn;
     this->dead_flag = dead_flag;
}

void Tank::initialize_from (int given_player_no,
                            char symbol,
                            Position init_posn,
                            char falcon_symbol,
                            Position falcon_posn)
{
     // Initialize a tank's symbol and initial position
     this->symbol = symbol;
     this->curr_posn = init_posn;
     this->prev_posn = this->curr_posn;

     this->falcon.symbol = falcon_symbol;
     this->falcon.posn = falcon_posn;
     

     this->id.player_no = given_player_no;
     this->id.tank_symbol = symbol;
     this->id.falcon_symbol = falcon_symbol;

     // Initialize Bullet Symbol and id's my_bunker
     if (symbol == TANK1){
          bullet_symbol = BULLET1;
          this->id.my_bunker = BUNKER1;
     }
     else{
          bullet_symbol = BULLET2;
          this->id.my_bunker = BUNKER2;
     }
    
     
     dead_flag = false;
     score = 0;
}

void Tank::get_next_move (Move move)
{

     this->next_move = move;
//      this->next_move.interpret_move (LEFT + rand () % 2 * 4);
     // cerr << "shoot : " << boolalpha << this->next_move.shoot << endl;
     // cerr << "dirn  : " << this->next_move.dirn.xdir << " " << this->next_move.dirn.ydir << endl;
     

     // Call player function and get response
     // Just a random move returned as of now
//      int temp;
//      temp = rand () % 8;	
     // this->next_move.interpret_move (temp);
}

void Tank::get_dummy_move ()
{
     this->next_move = Move (false, 0, 0);
}

void Tank::get_machine_random_move () 
{
     int temp;
     temp = rand() % 8;

//      // Testing code
//      temp = 4 + RIGHT;

     this->next_move.interpret_move (temp, true);
}

void Tank::move_bullets ()
{
     unsigned int i;
     // Move the bullets already shot by this tank 
     // Call bullet_list[i].move () for every bullet_list[i] in bullet_list
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].move ();
     }
}

void Tank::execute_next_move()
{
     // Call either this.move () or this.shoot_bullet ()
     if (this->next_move.shoot){
          this->shoot_bullet (); // Shoot and move new bullet
     }
     else{
          this->move ();
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
     // A new bullet has to move itself
     b.move ();
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
     if (crashed_into_bunker (Map)){
          die_by_bunker_crash ();
     }

     // Check for bullet crashes
     for (i = 0; i < this->bullet_list.size (); i++){
          this->bullet_list[i].check_for_crashes (Map);
          if (this->bullet_list[i].destroyed_enemy_bunker (Map) ) {
               incr_score (DESTROYED_ENEMY_BUNKER);
          }
     }
}

bool Tank::is_killed_by (Tank t)
{
     // Check if Tank is killed by enemy tank t's bullets or has
     // crashed into it

     bool flag = false;
     unsigned int i;
     Bullet b;

     for (i = 0; i < t.bullet_list.size (); i++) {
          b = t.bullet_list[i];
          if (b.curr_posn == this->curr_posn || (b.prev_posn == this->curr_posn && b.curr_posn == this->prev_posn)) {
               flag = true;
               break;
          }
     }

     if (flag){
          t.bullet_list[i].set_disappear_flag ();
     }

     // Check for Tank-Tank crossing 
     if (this->curr_posn == t.curr_posn || (this->curr_posn == t.prev_posn && this->prev_posn == t.curr_posn)){
          flag = true;
     }

     return flag;
}

void Tank::die_by_tank (Tank &t)
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
     if ( Map.is_symbol(curr_posn, WALL) ){
          return true;
     }    
     return false;
}

bool Tank::crashed_into_bunker (MapClass & Map)
{
     if ( Map.is_symbol(curr_posn, BUNKER1) ){
          return true;
     }    
     else if ( Map.is_symbol(curr_posn, BUNKER2) ){
          return true;
     }    
     return false;
}

// void Tank::evaluate_dangers (Tank t)
// {
//      if (crashed_into_wall (Map, true) || is_killed_by (t, true))
// }

void Tank::die_by_wall_crash ()
{
     // Die
     dead_flag = true;
}

void Tank::die_by_bunker_crash ()
{
     // Die
     dead_flag = true;
}

void Tank::check_bullet_interactions (Tank t)
{
     // Check if any of Tank's bullets are colliding with t's bullets
     // If so, just make its own bullet disappear
     // The other tank will take care of its own bullet

     Bullet my_b, enemy_b;
     unsigned int i, j;
     for (i = 0; i < this->bullet_list.size (); i++) {
          for (j = 0; j < t.bullet_list.size (); j++) {
               my_b = this->bullet_list[i]; 
               enemy_b = t.bullet_list[j];
               if (my_b.curr_posn == enemy_b.curr_posn || (my_b.prev_posn == enemy_b.curr_posn && my_b.curr_posn == enemy_b.prev_posn)){
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

void Tank::update_bullets_on_map (MapClass & Map)
{
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
}

void Tank::update_on_map (MapClass & Map)
{

#ifdef COUT_DEBUG
     cout << "Tank - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Tank - Curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif

     // Blank previous position on map
     if (Map.is_symbol(this->prev_posn, this->symbol))
          Map.set_element (this->prev_posn, EMPTY);

     // Set current position on map
     if (this->dead_flag){
          if (this->symbol == MACHINE_GUN) {
               switch (Map.get_element (this->curr_posn)) {
               case BULLET1 :
               case BULLET2 :
               case MACHINE_GUN_BULLET : Map.set_element (this->curr_posn, EMPTY); break;
               default : break;
               }
          }
          else {
               Map.set_element (this->curr_posn, DEAD);
          }
     }
     else
          Map.set_element (this->curr_posn, this->symbol);
}

void Bullet::move ()
{
     // Move Bullet forward

     this->prev_posn = this->curr_posn;
     this->curr_posn.go_in_direction (this->curr_dirn);
     
}

void Bullet::check_for_crashes (MapClass & Map)
{
     // Check if Bullet has collided with a GOLD piece or a WALL 

     if ( Map.is_symbol(this->curr_posn, GOLD) 
          || Map.is_symbol(this->curr_posn, MACHINE_GUN) 
          || Map.is_symbol(this->curr_posn, WALL) ){

          this->set_disappear_flag ();
     }
     
     // If own bunker is hit, simply treat it as wall,
     // that is, simply make the bullet vanish.
     if ( Map.is_symbol(this->curr_posn, BUNKER1)
          and (this->symbol == BULLET1) ) {
          this->set_disappear_flag ();
     }
     if ( Map.is_symbol(this->curr_posn, BUNKER2)
          and (this->symbol == BULLET2) ) {
          this->set_disappear_flag ();
     }
     if ( Map.is_symbol(this->curr_posn, BUNKER1)
          and (this->symbol == MACHINE_GUN_BULLET) ) {
          this->set_disappear_flag ();
     }
     if ( Map.is_symbol(this->curr_posn, BUNKER2)
          and (this->symbol == MACHINE_GUN_BULLET) ) {
          this->set_disappear_flag ();
     }
}

bool Bullet::destroyed_enemy_bunker (MapClass & Map) 
{
     if ( Map.is_symbol(this->curr_posn, BUNKER1)
          and (this->symbol == BULLET2) ) {
          this->set_disappear_flag ();
          return true;
     }
     if ( Map.is_symbol(this->curr_posn, BUNKER2)
          and (this->symbol == BULLET1) ) {
          this->set_disappear_flag ();
          return true;
     }
     return false;
}

void Bullet::update_on_map (MapClass & Map)
{
     // Update Bullet on map

#ifdef COUT_DEBUG
     cout << "Bullet - Prev posn : " << this->prev_posn.x << " " << this->prev_posn.y << endl;
     cout << "Bullet - curr posn : " << this->curr_posn.x << " " << this->curr_posn.y << endl;
#endif
     
     // Blank previous position
     if (Map.get_element (this->prev_posn) == this->symbol)
          Map.set_element (this->prev_posn, EMPTY);
     if (this->disappear_flag){
          if ( Map.is_symbol (this->curr_posn, BUNKER1)
               and (this->symbol == BULLET2) ) {
               Map.set_element (this->curr_posn, EMPTY);
          }
          if ( Map.is_symbol (this->curr_posn, BUNKER2)
               and (this->symbol == BULLET1) ) {
               Map.set_element (this->curr_posn, EMPTY);
          }
          
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


bool Tank::Falcon::is_killed_by (Tank &t)
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

     if ((flag) and (t.falcon.symbol != this->symbol)){
          t.incr_score (ENEMY_FALCON_KILLED);
     }
     
     return flag;
}

bool Tank::move_is_invalid () 
{
     return not this->next_move.is_valid();
}

//Tank::~Tank()
//{
//    this->bullet_list.clear();
//}


