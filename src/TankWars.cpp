#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Arena.h"
#include "Constants.h"

using namespace std;


int main()
{
     int i;
     Arena arena;
     srand(time(NULL));
     for (i = 0; i < TIMES; i++){
          arena.get_machine_moves ();
          arena.move_bullets ();
          arena.get_player_moves ();

          // For each Tank, first, either shoot or move tank
          // (ie. update its curr_posn)
          arena.execute_tank_moves ();

          // Now, check for tank picking up gold. If it crashes into
          // walls, set dead_flag.Then, check each bullet for crashes
          // and set disappear_flag if necessary
          arena.evaluate_static_interactions ();

          // See if each tank is being killed by any other tank. Check
          // if bullets collide with each other
          arena.evaluate_dynamic_interactions ();
          arena.update_map ();
          arena.print_scores ();
          if (arena.game_over_flag){
               arena.machine_gun_list.clear();
               break;
          }
     }
     cout << arena.tank1.score << " " << arena.tank2.score << endl;
     cout << endl << endl;
     cout << "##########[ Result ]#############" << endl;
     cout << "Tank 1 score : " << arena.tank1.score << endl;
     cout << "Tank 2 score : " << arena.tank2.score << endl;
     if (arena.tank2.score < arena.tank1.score) {
          cout << "          Tank 1 won." << endl;
     }
     else if (arena.tank1.score < arena.tank2.score) {
          cout << "          Tank 2 won." << endl;
     }
     else {
          cout << "The match was a tie." << endl;
     }
     cout << "#################################" << endl;
     cout << endl;
     
     return 0;
}
