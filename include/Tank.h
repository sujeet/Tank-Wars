#ifndef TANK_H

#define TANK_H

#include <iostream>
#include <vector>

#include "Map.h"

using namespace std;


class Bullet
{
public:
     // Variables
     char symbol;
     Direction curr_dirn;
     Position curr_posn, prev_posn;
     bool disappear_flag;
	  
     // Methods
     Bullet ()
     {
          disappear_flag = false;
     }
     void move ();		// Change Bullet's position
     void check_for_crashes (MapClass & Map); 
     bool destroyed_enemy_bunker (MapClass & Map); 
     void set_disappear_flag ()
     {
          disappear_flag = true;
     }
     void update_on_map (MapClass & Map);
     /* void mark_danger_zones (char Map[][MAP_SIZE]); */
     void print ()
     {
          curr_dirn.print ();
          cout << "Curr ";
          curr_posn.print ();
          cout << "Prev ";
          prev_posn.print ();
          cout << "Disappear_flag : " << disappear_flag << endl;
     }
	  
};

class Tank
{
public:

     class Falcon
     {
     public:
          // Variables
          bool dead_flag;
          char symbol;
          Position posn;

          // Methods
          Falcon (){
               dead_flag = false;
          }
	
          bool is_killed_by (Tank &t);
          bool crashed_tank (Tank t); // TODO
          void set_dead_flag ();
          void update_on_map (MapClass & Map);
     };
     
     // Variables
     char symbol;
     ID id;
     Falcon falcon;
     char bullet_symbol;
     vector<Bullet> bullet_list;
     Move next_move;
     Position curr_posn, prev_posn;
     bool dead_flag;
     int score;
     
     
     // Methods
     Tank () { };

     /* The following constructor is mainly used for machine guns */
     Tank (char symbol,
           char bullet_symbol,
           Position curr_posn,
           Position prev_posn,
           bool dead_flag = false);

     void initialize_from (int given_player_no,
                           char symbol,
                           Position init_posn,
                           char falcon_symbol,
                           Position falcon_posn);
     void print_bullets ()
     {
          for (unsigned int i = 0; i < bullet_list.size (); i++){
               bullet_list[i].print () ;
          }
     }
	  
     Tank operator=(const Tank copyate)
     {
         this->symbol = copyate.symbol;
         this->bullet_symbol = copyate.bullet_symbol;
         this->curr_posn = copyate.curr_posn;
         this->prev_posn = copyate.prev_posn;
         this->dead_flag = copyate.dead_flag;
         this->bullet_list = copyate.bullet_list;
         this->score = copyate.score;
         this->falcon = copyate.falcon;
         this->id = copyate.id;
         this->next_move = copyate.next_move;
         return *this;
     }

     void move_bullets ();
     void get_next_move (Move);
     void get_machine_random_move ();
     // get_dummy_move gets a move which neither shoots nor moves
     void get_dummy_move ();
     void execute_next_move ();
     void move ();			// Change Tank's position
     void shoot_bullet ();

     void evaluate_static_interactions (MapClass & Map);

     void incr_score (event e);
     void check_bullet_interactions (Tank t);

     /* bool on_gold (); */
     bool crashed_into_wall (MapClass & Map);	// Just set_dead_flag () as of now
     bool crashed_into_bunker (MapClass & Map);
     bool move_is_invalid ();   /* Checks the validity of next move */
     bool is_killed_by (Tank t);
     bool crashed_tank (Tank t); // Can be skipped as of now. Should
     // check if two tanks are crashing in
     // any manner
     void pick_up_gold_if_possible (MapClass & Map);

     //      void evaluate_dangers ();
     void evaluate_dangers ();
     void die_by_wall_crash ();
     void die_by_bunker_crash ();
     void die_by_tank (Tank &t);
     void do_nothing ();		// Comment out if not necessary. There just in case.
     void set_dead_flag ();		// Flag to denote that when all the
     // tanks' evaluations are done, die
     void update_bullets_on_map (MapClass & Map); // Call bullet_list[i].update_map ()
     void update_on_map (MapClass & Map); // Change own position on map, erase old position

     ~Tank()
     {
         bullet_list.clear();
     }
};

#endif
