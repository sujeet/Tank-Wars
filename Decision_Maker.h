#ifndef DECISION_MAKER_H
#define DECISION_MAKER_H

#include<iostream>

#include "Info.h"
#include "Map.h"
/*
 * Various Strategies    -  Aggressive, Defensive, Greedy, Customised
 * Various Action plans  -  Pick up gold, attack enemy tank,
 *                          attack enemy falcon, defend your falcon
 */
class DecisionMaker
{
    int weightage_table[4][4];
    int difficulty_table[4];

    void set_weightage_table();
    void set_diffculty_table();

    int calculate_best_action_plan();

    Move return_aggressive_move();
    Move return_defensive_move();
    Move return_greedy_move();
    Move return_customised_move();

    Move return_best_move();
}

