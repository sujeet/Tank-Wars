#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
#include "Tank.h"
#define N 20

using namespace std;


class ID
{
     int player_no;
     char tank_symbol;
     char falcon_symbol;
};		  

class object_info
{
public:
     int shortest_distance;
     move initial_move;
     Position posn;
     void print ()
	  {
	       cout << "Shortest_Distance : " << shortest_distance << endl;
	       cout << "INITIAL_MOVE : " << initial_move << endl;
	       posn.print ();
	  }
};

class Info
{
     // Info object contains info reg a particular player 
     
public:
     Position curr_posn;
     Info ();			// Constructor
     // Sets player info initially
     vector <object_info> gold;
     object_info my_falcon;
     object_info opp_falcon;
     object_info opp_tank; 
     object_info nearest_gold;

     /*
      * in danger?
      *
      * */
     
     void update_info (MapClass & Map);
     void print_info ();
     
};






