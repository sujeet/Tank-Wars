#include <queue>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

#include "Info.h"
#include "Constants.h"

using namespace std;


void Info::initializer(const ID mine, const ID enemy)
{
     // Initialize the Info object
     
     my_ID = mine;
     enemy_ID = enemy;
     shoot_enemy_tank_dirn.get_from_integer(0);
     shoot_falcon_dirn.get_from_integer(0);
     can_shoot_at_enemy_tank = false;
     can_shoot_at_enemy_falcon = false;
}


void Info::update_distances(MapClass &map,Position source)
{
     // This function does BREADTH FIRST TRAVERSAL on the Map and
     // stores the distances in the appropriate objects. The logic is
     // explained and you can change/add stuff to it if you want

     queue <Position> q;

     // visited : a 2D array which is used as a colour attribute in the BFT part
     vector< vector <int> > visited(MAP_SIZE - 1,vector <int>(MAP_SIZE - 1,0));

     // initial_move : a 2D array which stores the first moves to be
     // made from the source to reach that position in BFT time
     vector< vector <Move> > initial_move(MAP_SIZE - 1,vector <Move>(MAP_SIZE - 1));

     // distance : a 2D vector which stores the BFT distances of various position 
     vector< vector <int> > distance(MAP_SIZE - 1,vector <int>(MAP_SIZE - 1, -1));
     object_info temp_info_object, null_gold;

     Position temp, temp1;
     Direction d;
     char char_buffer, map_element;
     int x, y;

     x=source.x;
     y=source.y;
     visited[x][y] = 1;		// Set source to be visited
     distance[x][y] = 0;		// Distance from source to itself is 0

     // Gold and bunker vectors need to be cleared,
     // because each move we are rebuilding them.
     // That is because they can change from move to move.
     gold.clear ();
     enemy_bunker.clear ();

     // Initially pushing all the valid neighbors into the queue
     // the initial_move must be appropiately assigned values
     for(int i = 0; i<4; i++)
     {
          d.get_from_integer (i);
          temp = source;
          temp.go_in_direction (d);
          map_element = map.get_element (temp);

          if(map_element == enemy_ID.my_bunker || map_element == GOLD || map_element == EMPTY || map_element == BULLET1 || map_element == BULLET2 || map_element == enemy_ID.falcon_symbol){

               // Unless the position is empty or gold
               // dont enqueue the position.
               if (map_element == enemy_ID.falcon_symbol){
                    opp_falcon.shortest_distance = 1;
                    opp_falcon.initial_move.dirn = d;
                    opp_falcon.posn = temp;
               }
               else{
		   
	       
                    q.push(temp);
                    initial_move[temp.x][temp.y].dirn = d;  
                    visited[temp.x][temp.y] = 1;            //set the colour
                    distance[temp.x][temp.y] = 1;           //distance of the neighbours of source is 1.
               }
	       
          }
     }

// While queue is not empty bft proceeds
// This is the key BFT algo
     while(q.empty()==false)         
     {
          temp=q.front();     //temp is the first element in the queue
          q.pop();


          x = temp.x;
          y = temp.y;
          char_buffer = map.get_element(temp);
          //get element returns the symbol of the given position


          // Contains the info of the current node to be dequeued
          temp_info_object.shortest_distance = distance[temp.x][temp.y];
          temp_info_object.initial_move = initial_move[temp.x][temp.y];
          temp_info_object.posn = temp;


          // If the current position is GOLD push it into the
          // gold gold vector
          if(char_buffer == GOLD)
               gold.push_back(temp_info_object);

          if(char_buffer == enemy_ID.my_bunker)
               enemy_bunker.push_back(temp_info_object);
          // If the position is a tank or a falcon update the
          // corresponding objects. But the neighbours shouldn't be
          // pushed. so continue the process
          else if (char_buffer == enemy_ID.tank_symbol)       
          {
               opp_tank = temp_info_object;
          }
          else if (char_buffer == enemy_ID.falcon_symbol)
          {
               distance[x][y] = -1;
               opp_falcon = temp_info_object;
               continue;
               // We say continue because you can never reach
               // that place and go to a neighbour
          }
          else if( char_buffer ==  my_ID.falcon_symbol)
          {
               distance[x][y] = -1;
               my_falcon = temp_info_object;
               continue;
          }
          else if( char_buffer ==  WALL || char_buffer == my_ID.my_bunker || char_buffer == MACHINE_GUN)
          {
               distance[x][y] = -1;
               continue;
          }

          for(int i = 0; i<4; i++) // Going through current node's neighbours
          {
               d.get_from_integer (i);     
               temp1 = temp;
               temp1.go_in_direction (d); // temp1 is the neighbour

               // push the neighbours if they are not already visited
               if( visited[temp1.x][temp1.y] == 0 &&
                   !map.is_symbol (temp1, WALL) &&
                   !map.is_symbol (temp1, MACHINE_GUN) &&
                   !map.is_symbol (temp1, my_ID.my_bunker))
               {
                    q.push(temp1);
                    // the initial move is the same as its parents
                    // initial move 
                    initial_move[temp1.x][temp1.y] = initial_move[temp.x][temp.y];
                    visited[temp1.x][temp1.y] = 1;
                    distance[temp1.x][temp1.y] = 1 + distance[x][y];
                    // distance is one more than its parent
               }
          }
     }

// This null_gold object has been created to 
// equate nearest gold to null gold when 
// there is no gold in map
     null_gold.initial_move.dirn = Direction(0, 1);
     null_gold.shortest_distance = 10000;
     null_gold.initial_move.shoot = false;
     gold_available = true;

     if(gold.size())
     {
          nearest_gold = gold[0];
     }
     else
     {
          nearest_gold = null_gold;
          gold_available = false;
     }

// Test code to show the shortest distances to each position on
// the map

//      int i = 0, j = 0;
//      for(i = 0; i < MAP_SIZE - 1; i++)
//      {
//          for(j = 0; j < MAP_SIZE - 1; j++)
//          {
//              if(i != source.x || (j != source.y))
// 		  initial_move[i][j].dirn.print();
//              else 
// 		  cout << setw (2) << '9';//distance[i][j];
//          }

//          cout << endl << endl;
//      }

//          exit(0);

}

void Info::update_bullets(vector <Bullet> my_bullet_list, vector <Bullet> enemy_bullet_list)
{
    my_bullets.clear();
    enemy_bullets.clear();
    int size = my_bullet_list.size();
    bullet_info temp;
    int i;
    for(i = 0; i < size; i++)
    {
        temp.posn = my_bullet_list[i].curr_posn;
        temp.dirn = my_bullet_list[i].curr_dirn;
        my_bullets.push_back(temp);
    }
    size = enemy_bullet_list.size();
    for(i = 0; i < size; i++)
    {
        temp.posn = enemy_bullet_list[i].curr_posn;
        temp.dirn = enemy_bullet_list[i].curr_dirn;
        enemy_bullets.push_back(temp);
    }
} 

void Info::update_machine_gun_list(vector <Tank> machine_gun_list)
{
     int machine_gun_size = machine_gun_list.size();
     int j;
     bullet_info temp;
     machine_gun_position temp2;
     machine_guns.clear();
     machine_gun_bullets.clear();
     for(j = 0; j < machine_gun_size; j++) 
     {
          int bullets_size = machine_gun_list[j].bullet_list.size();
          int i;
          for(i = 0; i < bullets_size; i++)
          {
               temp.posn = machine_gun_list[j].bullet_list[i].curr_posn;
               temp.dirn = machine_gun_list[j].bullet_list[i].curr_dirn;
               machine_gun_bullets.push_back(temp);
          }
          temp2.posn = machine_gun_list[j].curr_posn;
          machine_guns.push_back(temp2);
     }
}

    

void Info::update_info (MapClass &map, 
                        Position source, 
                        vector <Bullet> given_my_bullet_list, 
                        vector <Bullet> given_enemy_bullet_list, 
                        vector <Tank> given_machine_gun_list)
{
     curr_posn = source;
     update_distances(map,source);
     update_shoot_variables (map);
     update_bullets(given_my_bullet_list, given_enemy_bullet_list);
     update_machine_gun_list(given_machine_gun_list);

}

bool Info::update_shoot_variables (MapClass &Map)
{
     int xdiff, ydiff;
     char m_symbol;
     Direction d;
     can_shoot_at_enemy_falcon = false;
     can_shoot_at_enemy_tank = false;
     Position my_posn, f_posn, e_posn;
     f_posn = this->opp_falcon.posn;
     e_posn = this->opp_tank.posn;

     xdiff = f_posn.x - curr_posn.x;
     ydiff = f_posn.y - curr_posn.y;

     if ((xdiff == 0) || (ydiff == 0))
     {
          if (xdiff == 0){
               if (ydiff < 0){
                    d.get_from_integer (LEFT);
               }
               else
                    d.get_from_integer (RIGHT);
          }
          else if (ydiff == 0) {
               if (xdiff < 0){
                    d.get_from_integer (UP);
               }
               else
                    d.get_from_integer (DOWN);
          } 
          my_posn = curr_posn;
          my_posn.go_in_direction (d);

          while (!(my_posn == f_posn)){
               m_symbol = Map.get_element (my_posn);

               if (m_symbol == WALL || m_symbol == GOLD || m_symbol == MACHINE_GUN){
                    can_shoot_at_enemy_falcon = false;
                    break;
               }
               my_posn.go_in_direction (d);
          }
          if (my_posn == f_posn){
               shoot_falcon_dirn = d;
               can_shoot_at_enemy_falcon = true;
          }
     }

     xdiff = e_posn.x - curr_posn.x;
     ydiff = e_posn.y - curr_posn.y;

     if (xdiff != 0 && ydiff != 0){
          return 1;
     }
     if (xdiff == 0){
          if (ydiff < 0){
               d.get_from_integer (LEFT);
          }
          else
               d.get_from_integer (RIGHT);
     }
     else if (ydiff == 0) {
          if (xdiff < 0){
               d.get_from_integer (UP);
          }
          else
          {
               d.get_from_integer (DOWN);
          }
     } 

     my_posn = curr_posn;
     my_posn.go_in_direction (d);

     while (!(my_posn == e_posn)){
          m_symbol = Map.get_element (my_posn);

          if (m_symbol == WALL || m_symbol == GOLD || m_symbol == MACHINE_GUN){
               can_shoot_at_enemy_tank = false;
               break;
          }
          my_posn.go_in_direction (d);
     }
     if (my_posn == e_posn){
          shoot_enemy_tank_dirn = d;
          can_shoot_at_enemy_tank = true;
     }

     return 1;
}

void Info::print_info()
{
     //cout<<nearest_gold.shortest_distance;
     //// 	       vector <object_info> gold;
     //cout << "My Falcon : " << endl;
     //my_falcon.print ();
     //cout << "OPP_FALCON : " << endl;
     //opp_falcon.print ();
     //cout << "OPP_TANK : " << endl;
     //opp_tank.print ();
     //cout << "Nearest_Gold : " << endl;
     //nearest_gold.print ();

}

object_info::object_info ()
{
     shortest_distance = -1;
}

void object_info::print ()
{
     //This function just prints the details of the object

     cout << "Shortest_Distance : " << shortest_distance << endl;
     cout << "INITIAL_MOVE : " ;
     initial_move.dirn.print();
     posn.print ();
}
