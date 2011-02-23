#include "Tank.h"
#include "Arena.h"
#include "Map.h"

#include <iostream>
using namespace std;


Arena::Arena () 
{
     // 

     game_over_flag = false;
     this->Map.create_from_file ("backup_map.txt");
     tank1.initialize_from ('1', 33, 18);
     tank2.initialize_from ('2', 13, 20);
}

void Arena::print_scores ()
{
     // Print scores
     // The rest of the map is being displayed by Map

     cout << tank1.score << " " << tank2.score << " " << "F" << endl;
     // for (int i=0; i<MAP_SIZE - 1; i++){
     //      for (int j=0; j<MAP_SIZE - 1; j++){
     //           if ( Map.is_symbol(i, j, EMPTY) ) {
     //                cout << char(EMPTY_DISPLAY);
     //           }
     //           else {
     //                cout << Map.get_element(i, j);
     //           }
     //      }
     //      if (i == 2) {
     //           cout << "  Tank 1 : " << tank1.score;
     //      }
     //      if (i == 3) {
     //           cout << "  Tank 2 : " << tank2.score;
     //      }
     //      cout << endl;
     // }
     cout << endl;
#ifdef COUT_DEBUG
     cout << " Tank 1 : " << tank1.score << endl;
     cout << " Tank 2 : " << tank1.score << endl;
#endif
     
}

void Arena::get_player_moves ()
{
     // Get each tank's next moves

     tank1.get_next_move ();
     tank2.get_next_move ();
}

void Arena::execute_moves ()
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
     // Check bullet-bullet interactions
     tank1.check_bullet_interactions (tank2);
     tank2.check_bullet_interactions (tank1);

     if (tank1.dead_flag || tank2.dead_flag)
          this->game_over_flag = true;
}

void Arena::update_map ()
{
     // Update the Tanks' and Bullets' positions on the map

#ifdef COUT_DEBUG
     cout << "Tank 1 : " << endl;
#endif
     tank1.update_on_map (Map);

#ifdef COUT_DEBUG
     cout << "Tank 2 : " << endl;
#endif
     tank2.update_on_map (Map);
}

