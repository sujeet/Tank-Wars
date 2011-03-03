#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Arena.h"
#include "Constants.h"

using namespace std;

void print_scores(const Arena & arena)
{
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
}

int main()
{
     Arena arena;
     srand(time(NULL));
     for (arena.move_no = 0; arena.move_no < TIMES; arena.move_no++){
          // Get the moves for the Machine guns
          arena.get_machine_moves ();

          // Move the bullets one step in their current direction
          arena.move_bullets ();

          // Get player moves - ie. Call DecisionMaker
          arena.get_player_moves ();

          // For each Tank, first, either shoot or move tank
          // (ie. update its curr_posn)
          arena.execute_tank_moves ();

          // Now, check each bullet for crashes and set
          // disappear_flag if necessary. Then, check for tank picking
          // up gold. If it crashes into walls, set dead_flag.
          arena.evaluate_static_interactions ();

          // See if each Tank is being killed by any other tank or
          // Machine gun. Check if bullets collide with each other
          arena.evaluate_dynamic_interactions ();

          // Update the MapClass with the current positions of all
          // objects
          arena.update_map ();

          // Print scores into the log file
          arena.print_scores ();

          // If the game is over
          if (arena.game_over_flag){
//               arena.machine_gun_list.clear();
               break;
          }
     }
     print_scores(arena);
     return 0;
}
