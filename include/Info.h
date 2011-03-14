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

class machine_gun_position
{
    public:
    Position posn;
};

class bullet_info
{
    public:
    Position posn;
    Direction dirn;
};

class Info
{
     // Info object contains info reg a particular Tank 

public:
     Position curr_posn;
     void initializer (const ID , const ID);			// Constructor
     ID my_ID, enemy_ID;
     bool can_shoot_at_enemy_tank, can_shoot_at_enemy_falcon;
     Direction shoot_falcon_dirn, shoot_enemy_tank_dirn; 

     // Sets player info initially
     vector <object_info> gold;
     vector <object_info> enemy_bunker;
     vector <machine_gun_position> machine_guns;
     vector <bullet_info> my_bullets;
     vector <bullet_info> enemy_bullets;
     vector <bullet_info> machine_gun_bullets;
     vector <Bullet> my_bullet_list, enemy_bullet_list;
     vector <Tank> machine_gun_list;
     object_info my_falcon;
     object_info opp_falcon;
     object_info opp_tank; 
     object_info nearest_gold;
     bool gold_available;
     void update_bullets(vector <Bullet> my_bullets, vector <Bullet> enemy_bullets);
     void update_machine_gun_list(vector <Tank> machine_gun_list);


     bool update_shoot_variables (MapClass &); 
     void update_info (MapClass &, Position, vector <Bullet> , vector <Bullet> , vector <Tank> );
     void update_distances(MapClass &, Position);
     void print_info ();
/*      ~Info (){ */
/* 	  cout << "Bye bye\n"; */
/*      } */
     

};

#endif
