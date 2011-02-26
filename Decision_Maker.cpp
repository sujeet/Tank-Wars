#include<iostream>
#include<cstdlib>
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

void DecisionMaker::DMinitializer(ID my_id, ID enemy_id)
{
    // Constructor for Decision maker.
    // Here default weightage values are set which can be changed for better strategies
    set_weightage_table(AGGRESSIVE, 20, 50, 50, 1);
    set_weightage_table(DEFENSIVE, 20, 5, 5, 50);
    set_weightage_table(GREEDY, 15, 15, 15, 0);
    set_weightage_table(CUSTOMISED, 40, 100, 75, 40);

    // These are just dummy values 
    set_diffculty_table(1, 1, 1, 1);

    // Initialize the info object so that it knows what is your character symbol,
    // player number etc
    info.initializer(my_id, enemy_id);
}

void DecisionMaker::fill_difficulty_table()
{
    // Here you can write the function which calculates the difficulty measure 
    // so as to fill in the difficulty table
    set_diffculty_table(info.nearest_gold.shortest_distance,
                        info.opp_falcon.shortest_distance,
                        info.opp_tank.shortest_distance,
                        info.my_falcon.shortest_distance);
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
    default:
        cerr << " Error: Function return_best_move in DecisionMaker class got invalid argument = " << best_action_plan << endl;
        exit(-1);
    }
}

Move DecisionMaker::go_to_gold_move()
{
    // Description of the function that calculates  
    // the move to 'go to gold'
    if(info.gold_available)
    {
        return info.opp_tank.initial_move;
    }
    else
    {
        return info.opp_tank.initial_move;
    }
}

Move DecisionMaker::attack_enemy_falcon_move()
{
    // Description of the function that calculates  
    // the move to 'attack enemy falcon'
    
    if(info.opp_falcon.shortest_distance == 2)
    {
        info.opp_falcon.initial_move.shoot = true;
        return info.opp_falcon.initial_move;
    }
    return info.opp_falcon.initial_move;
}

Move DecisionMaker::attack_enemy_tank_move()
{
    return info.opp_tank.initial_move;
}

Move DecisionMaker::defend_my_falcon_move()
{
    return info.my_falcon.initial_move;
}

int DecisionMaker::calculate_best_action_plan(int strategy)
{
//!!!!!!!!!!!!a call to  am i in danger to be included.

    float action_score[4];	// Other name?

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
    // Make sure your difficulty table is filled each time if you are using
    // it.
    fill_difficulty_table();
    return return_best_move(calculate_best_action_plan(choice));
}
