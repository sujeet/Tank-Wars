#ifndef ARENA_H

#define ARENA_H

#include "Tank.h"
#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

class Arena
{
public:
     // Attributes
     MapClass Map;
     bool game_over_flag;
     Tank tank1, tank2;
     Info info1, info2;
     ifstream infile;
     // Methods
     Arena ();
     void print_scores ();
     void get_player_moves ();
     void execute_moves ();
     void evaluate_static_interactions ();
     void evaluate_dynamic_interactions ();
     void update_map ();
};
     
#endif
