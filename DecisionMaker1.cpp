#include<iostream>
#include<cstdlib>

#include "DecisionMaker.h"
#include "Constants.h"

void DECISION_MAKER::set_weightage_table(int strategy,
                                        int go_to_nearest_gold_weight,
                                        int attack_enemy_falcon_weight,
                                        int attack_enemy_tank_weight,
                                        int defend_your_falcon_weight)
{
     // Sets the weightage table values as passed to the function
     // 
     // Strategy name            Value
     // AGGRESSIVE               0
     // DEFENSIVE                1
     // GREEDY                   2
     // CUSTOMISED               3
     //
     // Action Plan Name         Value
     // GO_TO_NEAREST_GOLD       0
     // ATTACK_ENEMY_FALCON      1
     // ATTACK_ENEMY_TANK        2
     // DEFEND_MY_FALCON         3
    
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
     // Here default weightage values are set which can be changed for better strategies
     // As of now, assume that the weightages are from 0 to 100.
     // go_to_nearest_gold_weight | attack_enemy_falcon_weight | attack_enemy_tank_weight | defend_your_falcon_weight
     set_weightage_table(AGGRESSIVE, 0, 50, 50, 0);
     set_weightage_table(DEFENSIVE, 20, 1, 5, 50);
     set_weightage_table(GREEDY, 1000, 15, 10, 0);
     set_weightage_table(CUSTOMISED, 0, 0, 100, 0);

     // These are just dummy values 
     set_difficulty_table(1, 1, 1, 1);

     // Initialize the info object so that it knows what is your character symbol,
     // player number etc
     info.initializer(my_id, enemy_id);
}

void DECISION_MAKER::fill_difficulty_table()
{
     // Here you can write the function which calculates the difficulty measure 
     // so as to fill in the difficulty table
     set_difficulty_table(info.nearest_gold.shortest_distance,
                          info.opp_falcon.shortest_distance,
                          info.opp_tank.shortest_distance,
                          info.my_falcon.shortest_distance);
}

Move DECISION_MAKER::return_best_move(int best_action_plan)
{
     // Returns a 'Move' object by calling appropriate move
     //      calculator depending upon action_plan arg passed

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
          cerr << " Error: Function return_best_move in DECISION_MAKER class got invalid argument = " << best_action_plan << endl;
          exit(-1);
     }
}

Move DECISION_MAKER::go_to_nearest_gold_move()
{
     // Description of the function that calculates  
     // the move to 'go to gold'
     if(info.gold_available)
     {
          return info.nearest_gold.initial_move;
     }
     else
     {
          return info.opp_tank.initial_move;
     }
}

Move DECISION_MAKER::attack_enemy_falcon_move()
{
     // Description of the function that calculates  
     // the move to 'attack enemy falcon'
    
     Move return_move;
     return_move.shoot = info.can_shoot_at_enemy_falcon;

     if (info.can_shoot_at_enemy_falcon){
         return_move.dirn = info.shoot_falcon_dirn;
     }
     else
     {
         return_move.dirn = info.opp_falcon.initial_move.dirn;
     }
     
     return return_move;
}

Move DECISION_MAKER::attack_enemy_tank_move()
{
    Move return_move;
    return_move.shoot = info.can_shoot_at_enemy_tank;

     if (info.can_shoot_at_enemy_tank){
         return_move.dirn = info.shoot_enemy_tank_dirn;
     }
     else
     {
         return_move.dirn = info.opp_tank.initial_move.dirn;
     }
     
     return return_move;
}

Move DECISION_MAKER::defend_my_falcon_move()
{
     // If I'm in the vicinity of my falcon, and so is he, then call attack_enemy_tank_move
     return info.my_falcon.initial_move;
}

int DECISION_MAKER::calculate_best_action_plan(int strategy)
{
//!!!!!!!!!!!!a call to  am i in danger to be included.

     float action_score[4];	// Other name?

     action_score[GO_TO_NEAREST_GOLD] = 
          float ( weightage_table[strategy][GO_TO_NEAREST_GOLD]) / float( difficulty_table[GO_TO_NEAREST_GOLD] );

     action_score[ATTACK_ENEMY_FALCON] = 
          float ( weightage_table[strategy][ATTACK_ENEMY_FALCON]) / float( difficulty_table[ATTACK_ENEMY_FALCON] );

     action_score[ATTACK_ENEMY_TANK] = 
          float ( weightage_table[strategy][ATTACK_ENEMY_TANK]) / float( difficulty_table[ATTACK_ENEMY_TANK] );

     action_score[DEFEND_MY_FALCON] = 
          float ( weightage_table[strategy][DEFEND_MY_FALCON]) / float( difficulty_table[DEFEND_MY_FALCON] );

     return find_the_maximum ( action_score );

}


int DECISION_MAKER::find_the_maximum( float* action_score )
{
     //given an array of floating point numbers returns the index corresponding to the maximum element
    
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

Move DECISION_MAKER::get_player_move(int choice)
{
     // Here you can fill your code
     // Make sure your difficulty table is filled each time if you are using
     // it.
     fill_difficulty_table();
     return return_best_move(calculate_best_action_plan(GREEDY));
}
