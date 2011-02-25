#include<iostream>
#include"Decision_Maker.h"

void DecisionMaker::set_weightage_table(int strategy, int go_to_gold_weight, int attack_enemy_falcon_weight, int attack_enemy_tank_weight, int defend_your_falcon_weight)
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
    // GO_TO_GOLD               0
    // ATTACK_ENEMY_FALCON      1
    // ATTACK_ENEMY_TANK        2
    // DEFEND_MY_FALCON         3
    
    this->weightage_table[strategy][GO_TO_GOLD] = go_to_gold_weight;
    this->weightage_table[strategy][ATTACK_ENEMY_FALCON] = attack_enemy_falcon_weight;
    this->weightage_table[strategy][ATTACK_ENEMY_TANK] = attack_enemy_tank_weight;
    this->weightage_table[strategy][DEFEND_MY_FALCON] = defend_your_falcon_weight;
}

void DecisionMaker::set_diffculty_table(int go_to_gold_difficulty, int attack_enemy_falcon_difficulty, int attack_enemy_tank_difficulty, int defend_your_falcon_difficulty)
{
    // Sets the difficulty table values
    difficulty_table[GO_TO_GOLD] = go_to_gold_difficulty;
    difficulty_table[ATTACK_ENEMY_FALCON] = attack_enemy_falcon_difficulty;
    difficulty_table[ATTACK_ENEMY_TANK] = attack_enemy_tank_difficulty;
    difficulty_table[DEFEND_MY_FALCON] = defend_your_falcon_difficulty;
}

Move DecisionMaker::return_best_move(int best_action_plan)
{
    // Returns a 'Move' object by calling appropriate move
    //      calculator depending upon action_plan arg passed

    switch(best_action_plan)
    {

    case GO_TO_GOLD:
        return go_to_gold_move();
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
    }
}

Move DecisionMaker::go_to_gold_move()
{
    // Description of the function that calculates  
    // the move to 'go to gold'
    
    return my_info.nearest_gold.initial_move;
}

Move DecisionMaker::attack_enemy_falcon_move()
{
    // Description of the function that calculates  
    // the move to 'attack enemy falcon'
    
    if(my_info.opp_falcon.shortest_distance == 2)
    {
        my_info.opp_falcon.initial_move.shoot = true;
        return my_info.opp_falcon.initial_move;
    }
    return my_info.opp_falcon.initial_move;
}

Move DecisionMaker::attack_enemy_tank_move()
{
    return my_info.opp_tank.initial_move;
}

Move DecisionMaker::defend_my_falcon_move()
{
    return my_info.my_falcon.initial_move;
}

int DecisionMaker::calculate_best_action_plan(int strategy)
{
//!!!!!!!!!!!!a call to  am i in danger to be included.

    float action_score[4];	// Other name?
    Move moves[4];
    int maximum;


    action_score[GO_TO_GOLD] = 
        float ( weightage_table[strategy][GO_TO_GOLD]) / float( difficulty_table[GO_TO_GOLD] );

    action_score[ATTACK_ENEMY_FALCON] = 
        float ( weightage_table[strategy][ATTACK_ENEMY_FALCON]) / float( difficulty_table[ATTACK_ENEMY_FALCON] );

    action_score[ATTACK_ENEMY_TANK] = 
        float ( weightage_table[strategy][ATTACK_ENEMY_TANK]) / float( difficulty_table[ATTACK_ENEMY_TANK] );

    action_score[DEFEND_MY_FALCON] = 
        float ( weightage_table[strategy][DEFEND_MY_FALCON]) / float( difficulty_table[DEFEND_MY_FALCON] );



    return find_the_maximum ( action_score );

}


int DecisionMaker::find_the_maximum( float* action_score )
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

Move DecisionMaker::get_player_move(int choice)
{
    // Here you can fill your code
    return return_best_move(calculate_best_action_plan(choice));
}
