#ifndef DECISION_MAKER_1_H
#define DECISION_MAKER_1_H

#include<iostream>

#include "Info.h"
#include "Misc_Classes.h"
#include "Map.h"

/*
 * Various Strategies    -  Aggressive, Defensive, Greedy, Customised
 * Various Action plans  -  Pick up gold, attack enemy tank,
 *                          attack enemy falcon, defend your falcon
 */
class DecisionMaker1
{
public:
     /* Variables */
     int weightage_table[4][4];
     int difficulty_table[4];
     Info info;

     /* Methods */
     void DMinitializer(ID, ID);

     void set_weightage_table(int, int, int, int, int );
     void set_difficulty_table(int, int, int, int);
     void fill_difficulty_table();

     int calculate_best_action_plan(int );
     int find_the_maximum(float*);

     Move go_to_nearest_gold_move();
     Move attack_enemy_falcon_move();
     Move attack_enemy_tank_move();
     Move defend_my_falcon_move();

     // Make it just a one-step call for the user instead of him
     // having to say
     // return_best_move (calculate_best_action_plan (his_choice_of_strategy))?
     Move return_best_move(int );

     Move get_player_move(const Info my_info, const Info enemy_info, const MapClass &map);
};


#endif
