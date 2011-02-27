#include <iostream>
#include <vector>

#include "Arena.h"
#include "Misc_Classes.h"
#include "Constants.h"

using namespace std;


void Arena::initialize_machine_guns()
{
     vector <Position>::iterator iter;
     iter = this->Map.machine_guns_posns.begin();

     while ( iter != this->Map.machine_guns_posns.end() ) {
          this->machine_gun_list.push_back( 
               Tank(
                    MACHINE_GUN,
                    MACHINE_GUN_BULLET,
                    *iter,
                    *iter) 
               );
          iter++;
     }
}

Arena::Arena () 
{
     // 

     game_over_flag = false;
     this->Map.create_from_file (MAP_FILE);

     // Assuming 1 has its falcon in the upper half
     // Assuming 2 has its falcon in the lower half
     
     tank1.initialize_from (1,
                            TANK1,
                            this->Map.tank1_init_posn,
                            FALCON1,
                            this->Map.falcon1_posn);
     tank2.initialize_from (2,
                            TANK2,
                            this->Map.tank2_init_posn,
                            FALCON2,
                            this->Map.falcon2_posn);

     DM1.DMinitializer (tank1.id, tank2.id);
     DM2.DMinitializer (tank2.id, tank1.id);

     this->initialize_machine_guns();

}

void Arena::print_scores ()
{
     // Print scores
     // The rest of the map is being displayed by Map

     this->Map.print_log(tank1.score, tank2.score, END_SCORE_CHAR);

#ifdef COUT_DEBUG
     cout << " Tank 1 : " << tank1.score << endl;
     cout << " Tank 2 : " << tank1.score << endl;
#endif
     
}

void Arena::get_machine_moves ()
{
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].get_machine_random_move();
     }
}
void Arena::move_bullets ()
{
     tank1.move_bullets ();
     tank2.move_bullets ();
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].move_bullets();
     }
}

void Arena::get_player_moves ()
{
     // Get each tank's next moves

     // DM1 and DM2 is the interface between the 
     // game engine and the bots.
     DM1.info.update_info (this->Map,
                           tank1.curr_posn,
                           tank1.bullet_list,
                           tank2.bullet_list,
                           machine_gun_list);

     DM2.info.update_info (this->Map,
                           tank2.curr_posn,
                           tank2.bullet_list,
                           tank1.bullet_list,
                           machine_gun_list);

     tank1.get_next_move (DM1.get_player_move(GREEDY));
     tank2.get_next_move (DM2.get_player_move(AGGRESSIVE));
}

void Arena::execute_tank_moves ()
{
     // Execute Tanks' moves

     tank1.execute_next_move ();
     tank2.execute_next_move ();
     
     // Execute machine gun's next moves
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].execute_next_move();
     }
}

     
void Arena::evaluate_static_interactions ()
{
     // Check for interactions of each tank with static stuff

     tank1.evaluate_static_interactions (Map);
     tank2.evaluate_static_interactions (Map);
     if (tank1.dead_flag || tank2.dead_flag) {
          this->game_over_flag = true;
     }

     // Now do the same for machine guns
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].evaluate_static_interactions (Map);
     }
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

     // Evaluate interactions between bullets of machine guns
     // and the tanks
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          if (tank1.is_killed_by(this->machine_gun_list[i])) {
               tank1.die_by_tank(this->machine_gun_list[i]);
          }
          if (tank2.is_killed_by(this->machine_gun_list[i])) {
               tank2.die_by_tank(this->machine_gun_list[i]);
          }
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

     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          tank1.check_bullet_interactions (this->machine_gun_list[i]);
          tank2.check_bullet_interactions (this->machine_gun_list[i]);
          this->machine_gun_list[i].check_bullet_interactions (tank1);
          this->machine_gun_list[i].check_bullet_interactions (tank2);
     }

     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          for (unsigned int j = i + 1; j < this->machine_gun_list.size(); j++) {
               this->machine_gun_list[i].check_bullet_interactions (this->machine_gun_list[j]);
               this->machine_gun_list[j].check_bullet_interactions (this->machine_gun_list[i]);
          }
     }

     // Check for game over flags
     if (tank1.dead_flag 
         || tank2.dead_flag 
         || tank1.falcon.dead_flag 
         || tank2.falcon.dead_flag) 
     {
          this->game_over_flag = true;
     }
     
}

void Arena::update_map ()
{
     // Update the Tanks' and Bullets' positions on the map

     tank1.update_bullets_on_map (Map);
     tank2.update_bullets_on_map (Map);

     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].update_bullets_on_map (Map);
     }

     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].update_on_map (Map);
     }

     tank1.update_on_map (Map);
     tank2.update_on_map (Map);
}

void Arena::end_game ()
{
     // Add stuff later
}

