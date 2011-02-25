#ifndef INFO_H
#define INFO_H

#include<queue>
#include<vector>
#include<iostream>
#include<fstream>

#include "Misc_Classes.h"
#include "Map.h"

#define GO_TO_GOLD 0
#define ATTACK_ENEMY_FALCON 1
#define ATTACK_ENEMY_TANK 2
#define DEFEND_MY_FALCON 3

#define AGGRESSIVE 0
#define DEFENSIVE 1 
#define GREEDY 2
#define CUSTOMISED 3

using namespace std;


class ID
{
public:
     int player_no;
     char tank_symbol;
     char falcon_symbol;
};		  

class object_info
{
public:
     object_info ();
     int shortest_distance;
     Move initial_move;
     Position posn;
     void print ();
};

class Info
{
     // Info object contains info reg a particular player 

public:
     Position curr_posn;
     void initializer (const ID , const ID);			// Constructor
     ID my_ID, enemy_ID;
     Move strategic_moves_array[4];

     // Sets player info initially
     vector <object_info> gold;
     object_info my_falcon;
     object_info opp_falcon;
     object_info opp_tank; 
     object_info nearest_gold;
     int weightage_table[4][4] ;

     void update_info (MapClass &, Position );
     void update_distances(MapClass &, Position);
     int find_the_maximum(float*);
     void print_info ();
     Move calculate_best_move(int );

};

#endif
