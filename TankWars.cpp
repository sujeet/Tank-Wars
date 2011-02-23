#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Arena.h"
#include "Tank.h"

#define TIMES 5000

using namespace std;


int main()
{
     int i;
     Arena arena;
     srand(time(NULL));
     for (i = 0; i < TIMES; i++){
#ifdef COUT_DEBUG
          cout << "Iteration no : " << i << endl;
#endif
          arena.get_player_moves ();

          // For each Tank, first, either shoot or move tank
          // (ie. update its curr_posn) Next, move bullets
          arena.execute_moves ();

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
               // cout << "Bye Bye!" << endl;
               break;
          }
     }

     return 0;
}
