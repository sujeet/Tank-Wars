#ifndef ARENA_H

#define ARENA_H

#include "Tank.h"
#include <fstream>
#include <iostream>
using namespace std;

class Arena
{
public:
     // Attributes
     char Map[51][51];
     bool game_over_flag;
     Tank tank1, tank2;
     ifstream infile;
     // Methods
     Arena ();
     void print_map ();
     void create_from_file ();
     void get_player_moves ();
     void update_posns ();
     void evaluate_tank_states ();
     void evaluate_interactions ();
     void update_map ();
};
     
#endif
