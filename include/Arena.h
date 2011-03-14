#ifndef ARENA_H

#define ARENA_H

#include <fstream>
#include <iostream>
#include <vector>

#include "DecisionMaker1.h"
#include "DecisionMaker2.h"
#include "Constants.h"
#include "Tank.h"
#include "Map.h"

using namespace std;

class Arena
{
private:
     void initialize_machine_guns();

public:
     // Attributes
     MapClass Map;
     bool game_over_flag;
     Tank tank1, tank2;
     DecisionMaker1 DM1;
     DecisionMaker2 DM2;
     vector <Tank> machine_gun_list;
     int move_no;
     // Methods
     Arena ();
     void print_scores ();
     void print_result ();
     void terminate_with_error (error error_code, int faulty_tank_number);
     void get_machine_moves (bool bullets_only = false);
     void move_bullets ();
     void get_player_moves (bool bullets_only = false);
     void execute_tank_moves ();
     void evaluate_static_interactions ();
     void evaluate_dynamic_interactions ();
     void update_map ();
     void end_game (error error_code, int faulty_tank_number = -1); /* Faulty tank number is useful if error occurs. */

};
     
#endif
