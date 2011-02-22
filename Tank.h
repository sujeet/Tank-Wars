#ifndef TANK_H

#define TANK_H

#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;


class Tank
{
public:
     class Bullet
     {
     public:
          // Variables
          Direction curr_dirn;
          Position curr_posn, prev_posn;
          bool disappear_flag;
	  
          // Methods
          Bullet ()
          {
               disappear_flag = false;
          }
          void move ();		// Change Bullet's position
          void check_for_crashes (MapClass & Map);  // Variables);
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

     // Variables
     char symbol;
     vector<Bullet> bullet_list;
     Move next_move;
     Position curr_posn, prev_posn;
     bool dead_flag;
     int score;
     
     
     // Methods
     Tank () { };
     void initialize_from (char symbol, int init_x, int init_y);
     void print_bullets ()
     {
          for (unsigned int i = 0; i < bullet_list.size (); i++){
               bullet_list[i].print () ;
          }
     }
	  
     void get_next_move ();
     void update ();
     void move ();			// Change Tank's position
     void shoot_bullet ();

     void evaluate_state (MapClass & Map);

     void incr_score (event e);
     void check_bullet_interactions (Tank t);

//      bool on_gold ();
     bool crashed_into_wall (MapClass & Map);	// Just set_dead_flag () as of now
     bool is_killed_by (Tank t);
     bool crashed_tank (Tank t); // Can be skipped as of now. Should
     // check if two tanks are crashing in
     // any manner
     void pick_up_gold_if_possible (MapClass & Map);
     void die_by_wall_crash ();
     void die_by_tank (Tank t);
     void do_nothing ();		// Comment out if not necessary. There just in case.
     void set_dead_flag ();		// Flag to denote that when all the
     // tanks' evaluations are done, die
     void update_on_map (MapClass & Map);		// Call bullet_list[i].update_map () and change own position on map, erase old position, and erase curr_gold_posn on the map if gold_flag is set
     void mark_danger_zones (MapClass & Map);
};

#endif
