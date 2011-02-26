#include <iostream>

#include "Info.h"
#include "Tank.h"
#include "Arena.h"
#include "Map.h"

using namespace std;


Arena::Arena () 
{
     // 

     game_over_flag = false;
     this->Map.create_from_file (MAP_FILE);

     // Assuming 1 has its falcon in the upper half
     // Assuming 2 has its falcon in the lower half
     tank1.initialize_from (1, '1', this->Map.tank1_init_posn.x, this->Map.tank1_init_posn.y, 'F', MAP_SIZE/2, MAP_SIZE - 2);
     tank2.initialize_from (2, '2', this->Map.tank2_init_posn.x, this->Map.tank2_init_posn.y, 'E', MAP_SIZE/2, 1);
     
     DM1.DMinitializer (tank1.id, tank2.id);
     DM2.DMinitializer (tank2.id, tank1.id);
     
}

void Arena::print_scores ()
{
     // Print scores
     // The rest of the map is being displayed by Map

     this->Map.print_log(tank1.score, tank2.score, 'F');

#ifdef COUT_DEBUG
     cout << " Tank 1 : " << tank1.score << endl;
     cout << " Tank 2 : " << tank1.score << endl;
#endif
     
}

void Arena::move_bullets ()
{
     tank1.move_bullets ();
     tank2.move_bullets ();
}


void Arena::get_player_moves ()
{
     // Get each tank's next moves

     DM1.info.update_info (this->Map, tank1.curr_posn);
     DM2.info.update_info (this->Map, tank2.curr_posn);
     
     // 1 : Choice - Say, Aggressive
     tank1.get_next_move (DM1, 2);
     tank2.get_next_move (DM2, 2);
}

void Arena::execute_tank_moves ()
{
     // Execute Tanks' moves

     tank1.execute_next_move ();
     tank2.execute_next_move ();
}

     
void Arena::evaluate_static_interactions ()
{
     // Check for interactions of each tank with static stuff

     tank1.evaluate_static_interactions (Map);
     tank2.evaluate_static_interactions (Map);
     if (tank1.dead_flag || tank2.dead_flag)
          this->game_over_flag = true;
}

void Arena::evaluate_dynamic_interactions ()
{
     // Evaluate interactions between bullets and other tanks

     if (tank1.is_killed_by (tank2)){
          tank1.die_by_tank(tank2);
     }
     
     if (tank2.is_killed_by (tank1)){
          tank2.die_by_tank(tank1);
     }

     // Check for falcon being killed by enemy bullet
     if (tank1.falcon.is_killed_by (tank2)){
          tank1.falcon.set_dead_flag ();
     }

     if (tank2.falcon.is_killed_by (tank1)){
          tank2.falcon.set_dead_flag ();
     }
     
     // Check for falcon being killed by own bullet
     if (tank1.falcon.is_killed_by (tank1)){
          tank1.falcon.set_dead_flag ();
     }

     if (tank2.falcon.is_killed_by (tank2)){
          tank2.falcon.set_dead_flag ();
     }

     // Check bullet-bullet interactions
     tank1.check_bullet_interactions (tank2);
     tank2.check_bullet_interactions (tank1);

     if (tank1.dead_flag || tank2.dead_flag || tank1.falcon.dead_flag || tank2.falcon.dead_flag)
          this->game_over_flag = true;
}

void Arena::update_map ()
{
     // Update the Tanks' and Bullets' positions on the map

     tank1.update_bullets_on_map (Map);
     tank2.update_bullets_on_map (Map);

     tank1.update_on_map (Map);
     tank2.update_on_map (Map);
}

