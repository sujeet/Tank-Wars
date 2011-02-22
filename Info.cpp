#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
#include "Misc_Classes.h"
#include "Map.h"
#define N 20

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
     int shortest_distance;
     Move initial_move;
     Position posn;
     void print ()
	  {
	       cout << "Shortest_Distance : " << shortest_distance << endl;
	       cout << "INITIAL_MOVE : " ;
           initial_move.dirn.print();
	       posn.print ();
	  }
};

struct symbol_list
{
     char my_tank;
     char my_falcon;
     char enemy_tank;
     char enemy_falcon;
};

class Info
{
     vector <object_info> gold;
     object_info my_falcon;
     object_info opp_falcon;
     object_info opp_tank;
     object_info nearest_gold;

     struct symbol_list symbol;
public:

     Info(ID mine, ID enemy)
	  {
	       symbol.my_tank = mine.tank_symbol;
	       symbol.my_falcon = mine.falcon_symbol;
	       symbol.enemy_tank = enemy.tank_symbol;
	       symbol.enemy_falcon = enemy.falcon_symbol;
	  }
     /*This funtion does a breadth first traversal to find out the distances from the source to 
      * all important objects in the map.
      */
     void update_info(MapClass &map,Position source)
	  {
	       queue <Position> q;
	       vector< vector <int> > visited(N+2,vector <int>(N+2,0));
	       vector< vector <Move> > initial_move(N+2,vector <Move>(N+2));
	       vector< vector <int> > distance(N+2,vector <int>(N+2));
	       Position temp, temp3;
	       Direction d;
	       char char_buffer;
	       int x,y;
	       
	       x=source.x;
	       y=source.y;
	       visited[source.x][source.y]=1;
	       distance[source.x][source.y]=0;
	       // Initially pushing all the valid neighbors into the queue
           for(int i = 0; i<4; i++)
           {
               d.get_from_integer (i);
               temp = source;
               temp.go_in_direction (d);

               if(map.is_symbol (temp, GOLD) || map.is_symbol (temp, EMPTY))
               {
                   q.push(temp);
                   initial_move[temp.x][temp.y].dirn = d;
                   visited[temp.x][temp.y]=1;
                   distance[temp.x][temp.y]=1;
               }
           }
	       // While queue is not empty we are doing the bft part
	       // This is the key bft algo
           while(q.empty()==false)
           {
               temp=q.front();
               q.pop();
               x = temp.x;
               y = temp.y;
               char_buffer = map.get_element(temp);
               object_info temp2;
               temp2.shortest_distance = distance[temp.x][temp.y];
               temp2.initial_move = initial_move[temp.x][temp.y];
               temp2.posn = temp;
               if(char_buffer == GOLD)
                   gold.push_back(temp2);
               else if (char_buffer == symbol.enemy_tank)
               {
                   opp_tank = temp2;
                   continue;
               }
               else if (char_buffer == symbol.enemy_falcon)
               {
                   opp_falcon = temp2;
                   continue;
               }
               else if( char_buffer ==  symbol.my_falcon)
               {
                   my_falcon = temp2;
                   continue;
               }
               else if( char_buffer ==  WALL)
               {
                   continue;
               }


               for(int i = 0; i<4; i++) // Going through current node's neighbours
               {
                   d.get_from_integer (i);
                   temp3 = temp;
                   temp3.go_in_direction (d);

                   if(visited[temp3.x][temp3.y] == 0)
                   {
                       q.push(temp3);
                       initial_move[temp3.x][temp3.y].dirn = d;
                       visited[temp3.x][temp3.y] = 1;
                       distance[temp3.x][temp3.y] = 1 + distance[x][y];
                   }
               }
           }
	       struct object_info null_gold;
	       null_gold.shortest_distance = -1;
	       if(gold.size())
		    nearest_gold = gold[0];
	       else
		    nearest_gold = null_gold;
	  }
    
     void print_some_info()
	  {
	       cout<<nearest_gold.shortest_distance;
// 	       vector <object_info> gold;
	       cout << "My Falcon : " << endl;
	       my_falcon.print ();
	       cout << "OPP_FALCON : " << endl;
	       opp_falcon.print ();
	       cout << "OPP_TANK : " << endl;
	       opp_tank.print ();
	       cout << "Nearest_Gold : " << endl;
	       nearest_gold.print ();
	  }

};

int main()
{
    MapClass test_map;
    test_map.create_from_file("log_file");
    //ifstream log_file("log_file", ios::in);
    int i, j;
    char a;
    //char map[N+2][N+2];
     Position check;
     check.x=4;
     check.y=10;
    // for(i = N+1; i>=0; i--)
    // {
	//  for(j = 0; j<N+2; j++)
	//  {
	//       log_file>>a;
	//       map[j][i] = a;
	//       cout<<a;
	//  }
	//  cout<<endl;
    // }
    ID mine, enemy;
    mine.player_no = 1;
    mine.tank_symbol = '1';
    mine.falcon_symbol = 'M';

    enemy.player_no = 2;
    enemy.tank_symbol = '2';
    enemy.falcon_symbol = 'E';
     Info player1(mine, enemy);
     player1.update_info(test_map, check);
     player1.print_some_info();
     return 0;
}


