#ifndef INFO_H
#define INFO_H

#include<queue>
#include<vector>
#include<iostream>
#include<fstream>

#include "Tank.h"
#include "Misc_Classes.h"
#include "Map.h"

using namespace std;

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
     bool can_shoot_at_enemy_tank, can_shoot_at_enemy_falcon;
      Direction shoot_falcon_dirn, shoot_enemy_tank_dirn; 

     // Sets player info initially
     vector <object_info> gold;
     vector <Bullet> my_bullet_list, enemy_bullet_list;
     vector <Tank> machine_gun_list;
     object_info my_falcon;
     object_info opp_falcon;
     object_info opp_tank; 
     object_info nearest_gold;
     bool gold_available;

      bool update_shoot_variables (MapClass &); 
     void update_info (MapClass &, Position, vector <Bullet> , vector <Bullet> , vector <Tank> );
     void update_distances(MapClass &, Position);
     void print_info ();
/*      ~Info (){ */
/* 	  cout << "Bye bye\n"; */
/*      } */
     

};

#endif
