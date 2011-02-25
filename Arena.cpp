#include <iostream>
#include <vector>

#include "Info.h"
#include "Tank.h"
#include "Arena.h"
#include "Map.h"

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
                            '1',
                            this->Map.tank1_init_posn.x,
                            this->Map.tank1_init_posn.y,
                            'F',
                            MAP_SIZE/2,
                            MAP_SIZE - 2);
     tank2.initialize_from (2,
                            '2',
                            this->Map.tank2_init_posn.x,
                            this->Map.tank2_init_posn.y,
                            'E',
                            MAP_SIZE/2,
                            1);

     this->initialize_machine_guns();

     info1.initializer (tank1.id, tank2.id);
     info2.initializer (tank2.id, tank1.id);
     
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

void Arena::get_moves ()
{
     this->get_machine_moves();
     this->get_player_moves();
}

void Arena::get_machine_moves ()
{
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].get_machine_random_move();
     }
}

void Arena::get_player_moves ()
{
     // Get each tank's next moves

     info1.update_info (this->Map, tank1.curr_posn);
     info2.update_info (this->Map, tank2.curr_posn);
     
     // 1 : Choice - Say, Aggressive
     tank1.get_next_move (info1, 2);
     tank2.get_next_move (info2, 2);
}

void Arena::execute_moves ()
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

     // Note that machine guns need not be updated on the map
     tank1.update_on_map (Map);
     tank2.update_on_map (Map);
     for (unsigned int i = 0; i < this->machine_gun_list.size(); i++) {
          this->machine_gun_list[i].update_on_map (Map);
     }
}

