#ifndef ARENA_H

#define ARENA_H

#include "Tank.h"
#include "Map.h"
#include "Decision_Maker.h"
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
     Info info1, info2;         // this might just be redundant
     DecisionMaker DM1, DM2;
     ifstream infile;
     ofstream log;
     // Methods
     Arena ();
     void print_scores ();
     void move_bullets ();
     void get_player_moves ();
     void execute_tank_moves ();
     void evaluate_static_interactions ();
     void evaluate_dynamic_interactions ();
     void update_map ();
};
     
#endif
