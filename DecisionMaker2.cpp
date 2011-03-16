#include<iostream>
#include<cstdlib>

#include "DecisionMaker.h"
#include "Constants.h"

// IMPORTANT:
//   First thing you need to do is understand the various 
// information you get from the Info object. Things like 'your 
// closest distance from the enemy tank' can be obtained from the
// Info object.
//
// OPTIONAL: ( But may be VERY helpful)
//   After looking at all the information you can get from
// the Info class, you can try to use and build on our mathematical 
// model.
//
//   Our idea is to calculate the best move for a particular
// strategy (offensive or defensive etc.) by having some weightages
// for some predefined possible actions ( like collect gold, attack
// enemy etc ) and then decide which move will give you the best
// result.
//
//   You may want to play in different strategies at different
// times of the game, so set different weightages based on the
// circumstances if you want. So you can build upon this
// mathematical model if you want.
//
// CAUTION :
//
//   Do not change the prototypes of any of the functions we have
// provided in the header file.

Move DECISION_MAKER::get_player_move(Info my_info,
				     Info opp_info,
				     int my_score,
				     int enemy_score,
				     int total_moves_done)
{
     // Returns a Move

     // Simply say,
     // 
     // return Move (my_move)
     // 
     // where
     // |--------------+---------+----------+-------+---------+----------+------------+------------+-------------|
     // | my_move      | GO_LEFT | GO_RIGHT | GO_UP | GO_DOWN | SHOOT_UP | SHOOT_DOWN | SHOOT_LEFT | SHOOT_RIGHT |
     // | Actual value |       0 |        1 |     2 |       3 |        4 |          5 |          6 |           7 |
     // |--------------+---------+----------+-------+---------+----------+------------+------------+-------------|

     // Make sure your difficulty table is filled each time if you are using
     // it.
     this->my_info = my_info;
     this->opp_info = opp_info;
     fill_difficulty_table();

     /*************************************/
     /*   PUT YOUR CODE IN THIS FUNCTION  */
     /*************************************/
     // return Move (SHOOT_RIGHT);
     return get_best_move_for(calculate_best_action_plan(GREEDY));

}


/*************************************/
/*   PUT YOUR FUNCTIONS BELOW        */
/*************************************/

// You can change the below functions to your needs.
 
// The procedural flow of the below functions is 
// calculate_best_action_plan -> finds the most suitable action plan (attack enemy, pick up gold, etc)
// get_best_move_for() then calls the appropriate function which returns a move for the given action.

void DECISION_MAKER::set_weightage_table(int strategy,
                                         int go_to_nearest_gold_weight,
                                         int attack_enemy_falcon_weight,
                                         int attack_enemy_tank_weight,
                                         int defend_your_falcon_weight)
{
     // Sets the weightage table values as passed to the function

     // |------------+--------------------+---------------------+-------------------+------------------|
     // |            | GO_TO_NEAREST_GOLD | ATTACK_ENEMY_FALCON | ATTACK_ENEMY_TANK | DEFEND_MY_FALCON |
     // |------------+--------------------+---------------------+-------------------+------------------|
     // | AGGRESSIVE |                    |                     |                   |                  |
     // | DEFENSIVE  |                    |                     |                   |                  |
     // | GREEDY     |                    |                     |                   |                  |
     // | CUSTOMIZED |                    |                     |                   |                  |
     // |------------+--------------------+---------------------+-------------------+------------------|
     
     // |---------------+-------|
     // | Strategy name | Index |
     // |---------------+-------|
     // | AGGRESSIVE    |     0 |
     // | DEFENSIVE     |     1 |
     // | GREEDY        |     2 |
     // | CUSTOMIZED    |     3 |
     // |---------------+-------|
     
     // |---------------------+-------|
     // | Action Plan Name    | Index |
     // |---------------------+-------|
     // | GO_TO_NEAREST_GOLD  |     0 |
     // | ATTACK_ENEMY_FALCON |     1 |
     // | ATTACK_ENEMY_TANK   |     2 |
     // | DEFEND_MY_FALCON    |     3 |
     // |---------------------+-------|
    
     this->weightage_table[strategy][GO_TO_NEAREST_GOLD] = go_to_nearest_gold_weight;
     this->weightage_table[strategy][ATTACK_ENEMY_FALCON] = attack_enemy_falcon_weight;
     this->weightage_table[strategy][ATTACK_ENEMY_TANK] = attack_enemy_tank_weight;
     this->weightage_table[strategy][DEFEND_MY_FALCON] = defend_your_falcon_weight;
}

void DECISION_MAKER::set_difficulty_table(int go_to_nearest_gold_difficulty,
                                          int attack_enemy_falcon_difficulty,
                                          int attack_enemy_tank_difficulty,
                                          int defend_your_falcon_difficulty)
{
     // Sets the difficulty table values
     difficulty_table[GO_TO_NEAREST_GOLD] = go_to_nearest_gold_difficulty;
     difficulty_table[ATTACK_ENEMY_FALCON] = attack_enemy_falcon_difficulty;
     difficulty_table[ATTACK_ENEMY_TANK] = attack_enemy_tank_difficulty;
     difficulty_table[DEFEND_MY_FALCON] = defend_your_falcon_difficulty;
}

void DECISION_MAKER::DMinitializer(ID my_id, ID enemy_id)
{
     // Constructor for Decision maker.

     // Here default WEIGHTAGE VALUES are set which can be changed for better strategies
     // The weightages are from 0 to 100.

     // |---------------------------+----------------------------+--------------------------+---------------------------|
     // | GO_TO_NEAREST_GOLD_WEIGHT | ATTACK_ENEMY_FALCON_WEIGHT | ATTACK_ENEMY_TANK_WEIGHT | DEFEND_YOUR_FALCON_WEIGHT |
     // |---------------------------+----------------------------+--------------------------+---------------------------|

     set_weightage_table(AGGRESSIVE, 0, 50, 50, 0);
     set_weightage_table(DEFENSIVE, 20, 1, 5, 50);
     set_weightage_table(GREEDY, 100, 15, 10, 0);
     set_weightage_table(CUSTOMIZED, 0, 0, 100, 0);

     // These are just dummy values 
     set_difficulty_table(1, 1, 1, 1);

     // Initialize the info object so that it knows what your character symbol is,
     // player number etc
     my_info.initializer(my_id, enemy_id);
}

void DECISION_MAKER::fill_difficulty_table()
{
     // Here you can write the function which calculates the difficulty measure 
     // so as to fill in the difficulty table

     // By default, the difficulty of each action plan is set to be
     // the shortest distance needed to be covered to carry out the
     // action
     set_difficulty_table(my_info.nearest_gold.shortest_distance,
                          my_info.opp_falcon.shortest_distance,
                          my_info.opp_tank.shortest_distance,
                          my_info.my_falcon.shortest_distance);
}

Move DECISION_MAKER::get_best_move_for(int best_action_plan)
{
     // Returns a 'Move' object by calling appropriate move calculator
     // depending upon action_plan argument passed

     switch(best_action_plan)
     {
     case GO_TO_NEAREST_GOLD:
          return go_to_nearest_gold_move();
          break;
     case ATTACK_ENEMY_FALCON:
          return attack_enemy_falcon_move();
          break;
     case ATTACK_ENEMY_TANK:
          return attack_enemy_tank_move();
          break;
     case DEFEND_MY_FALCON:
          return defend_my_falcon_move();
          break;
     default:
          cerr << " Error: Function get_best_move_for in DECISION_MAKER class got invalid argument = " << best_action_plan << endl;
          exit(-1);
     }
}

Move DECISION_MAKER::go_to_nearest_gold_move()
{
     // Description of the function that calculates  
     // the move to 'go to gold'

     if(my_info.gold_available) 
     {
	  // If there are gold pieces on the map, go to the nearest gold piece
          return my_info.nearest_gold.initial_move;
     }
     else
     {
	  // Else, just go near the enemy tank
          return my_info.opp_tank.initial_move;
     }
}

Move DECISION_MAKER::attack_enemy_falcon_move()
{
     // Description of the function that calculates  
     // the move to 'attack enemy falcon'
    
     Move return_move;
     return_move.shoot = my_info.can_shoot_at_enemy_falcon;

     if (my_info.can_shoot_at_enemy_falcon){
	  return_move.dirn = my_info.shoot_falcon_dirn;
     }
     else
     {
	  return_move.dirn = my_info.opp_falcon.initial_move.dirn;
     }
     
     return return_move;
}

Move DECISION_MAKER::attack_enemy_tank_move()
{
     Move return_move;
     return_move.shoot = my_info.can_shoot_at_enemy_tank;

     if (my_info.can_shoot_at_enemy_tank){
	  return_move.dirn = my_info.shoot_enemy_tank_dirn;
     }
     else
     {
	  return_move.dirn = my_info.opp_tank.initial_move.dirn;
     }
     
     return return_move;
}

Move DECISION_MAKER::defend_my_falcon_move()
{
     // By default, just go back towards my falcon
     // If I'm in the vicinity of my falcon, and so is he, then call attack_enemy_tank_move
     return my_info.my_falcon.initial_move;
}

int DECISION_MAKER::calculate_best_action_plan(int strategy)
{
     // A simple function to calculate the scores for each of the
     // strategies possible

     // It returns the strategy with maximum score so that you make
     // the most effective move at each turn
     switch(strategy)
     {
     case AGGRESSIVE:
	  if(my_info.opp_tank.shortest_distance + 3 < my_info.opp_falcon.shortest_distance)
	       return ATTACK_ENEMY_TANK;
	  else 
	  {
	       return ATTACK_ENEMY_FALCON;
	  }
          break;
     case DEFENSIVE:
          if(opp_info.opp_tank.shortest_distance < opp_info.opp_falcon.shortest_distance)
	       return ATTACK_ENEMY_TANK;
          else
	       return DEFEND_MY_FALCON;
          break;
     case GREEDY:
     case CUSTOMIZED:
          float action_score[4];

          action_score[GO_TO_NEAREST_GOLD] = 
	       float ( weightage_table[strategy][GO_TO_NEAREST_GOLD]) / float( difficulty_table[GO_TO_NEAREST_GOLD] );

          action_score[ATTACK_ENEMY_FALCON] = 
	       float ( weightage_table[strategy][ATTACK_ENEMY_FALCON]) / float( difficulty_table[ATTACK_ENEMY_FALCON] );

          action_score[ATTACK_ENEMY_TANK] = 
	       float ( weightage_table[strategy][ATTACK_ENEMY_TANK]) / float( difficulty_table[ATTACK_ENEMY_TANK] );

          action_score[DEFEND_MY_FALCON] = 
	       float ( weightage_table[strategy][DEFEND_MY_FALCON]) / float( difficulty_table[DEFEND_MY_FALCON] );

          return find_the_maximum ( action_score );
          break;
     default :
          return DEFEND_MY_FALCON;
     }
    
}


int DECISION_MAKER::find_the_maximum( float* action_score )
{
     // Given an array of floating point numbers, returns the index
     // corresponding to the maximum element
    
     int max_value,i,max_posn;
     max_value=0;
     for( i=0;i<4;i++ )
     {
          if( action_score[i] > max_value )
          {
               max_value = action_score[i];
               max_posn=i;
          }
     }
     return max_posn;
}

