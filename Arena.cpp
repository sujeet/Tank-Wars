#include "Tank.h"
#include "Arena.h"

#include <iostream>
using namespace std;


Arena::Arena () 
{
     game_over_flag = false;
     this->create_from_file ();
     tank1.initialize_from ('1', 13, 18);
     tank2.initialize_from ('2', 13, 20);
}

void Arena::print_map ()
{
     for (int i=0; i<50; i++){
          for (int j=0; j<50; j++){
               if (Map[i][j] == EMPTY) {
                    cout << char(EMPTY_DISPLAY);
               }
               else {
                    cout << Map[i][j];
               }
          }
          if (i == 2) {
               cout << "  Tank 1 : " << tank1.score;
          }
          if (i == 3) {
               cout << "  Tank 2 : " << tank2.score;
          }
          cout << endl;
     }
     cout << endl;
#ifdef COUT_DEBUG
     cout << " Tank 1 : " << tank1.score << endl;
     cout << " Tank 2 : " << tank1.score << endl;
#endif
     
}

void Arena::create_from_file ()
{
     infile.open ("backup_map.txt");
     for (int i=0; i<50; i++){
          for (int j=0; j<50; j++){
               infile >> Map[i][j];
          }
     }
     infile.close ();
}

void Arena::get_player_moves ()
{
     tank1.get_next_move ();
     tank2.get_next_move ();
}


void Arena::update_posns ()
{
     tank1.update ();
     tank2.update ();
}

     
void Arena::evaluate_tank_states ()
{
     tank1.evaluate_state (Map);
     tank2.evaluate_state (Map);
     if (tank1.dead_flag || tank2.dead_flag)
          this->game_over_flag = true;
}

void Arena::evaluate_interactions ()
{
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
#ifdef COUT_DEBUG
     cout << "Tank 1 : " << endl;
#endif
     tank1.update_on_map (Map);
#ifdef COUT_DEBUG
     cout << "Tank 2 : " << endl;
#endif
     tank2.update_on_map (Map);
     // tank1.mark_danger_zones (Map);
     // tank2.mark_danger_zones (Map);
}

