#include<queue>
#include<vector>
#include<iostream>
#include<fstream>

#include "Info.h"
#include "Map.h"

using namespace std;

object_info::object_info ()
{
     shortest_distance = -1;
}

void object_info::print ()
{
    //this function just prints the details of the object

    cout << "Shortest_Distance : " << shortest_distance << endl;
    cout << "INITIAL_MOVE : " ;
    initial_move.dirn.print();
    posn.print ();
}

void Info::initializer(const ID mine, const ID enemy)
{
    my_ID = mine;
    enemy_ID = enemy;
}

void Info::update_distances(MapClass &map,Position source)
{
   //this function does BREATH FRIST TRAVERSAL and stores the distances in the appropiate objects. The logic 
   //is explained and you can change/add stuff to it if you want
   


    queue <Position> q;

    // visited is a 2D array which is used as a colour attribute in the BFT part
    vector< vector <int> > visited(MAP_SIZE - 1,vector <int>(MAP_SIZE - 1,0));

    //initial_move is a 2D array which stores the first moves to be made from the source to reach that 
    //position in BFT time
    vector< vector <Move> > initial_move(MAP_SIZE - 1,vector <Move>(MAP_SIZE - 1));

    //distance is a 2D vector which stores the BFT distances of various position 
    vector< vector <int> > distance(MAP_SIZE - 1,vector <int>(MAP_SIZE - 1));

    
    Position temp, temp1;

    Direction d;
    char char_buffer;
    int x, y;

    x=source.x;
    y=source.y;
    visited[x][y] = 1;
    distance[x][y] = 0;
    
    gold.clear ();      //cleares the gold vector. Its necessary because the same code is called multiple 
                        //times.

    // Initially pushing all the valid neighbors into the queue
    // the initial_move must be appropiately assigned values
    
    for(int i = 0; i<4; i++)
    {
        d.get_from_integer (i);
        temp = source;
        temp.go_in_direction (d);

        if(map.is_symbol (temp, GOLD) || map.is_symbol (temp, EMPTY))   //unless the posn is empty or gold 
                                                                        //dont enqueue the position.
        {
            q.push(temp);
            initial_move[temp.x][temp.y].dirn = d;  
            visited[temp.x][temp.y] = 1;            //set the colour
            distance[temp.x][temp.y] = 1;           //distance of the neighbours of source is 1.
        }
    }

    // While queue is not empty bft proceeds
    // This is the key bft algo
    
    while(q.empty()==false)         
    {
        temp=q.front();     //temp is the first element in the queue
        q.pop();


        x = temp.x;
        y = temp.y;
        char_buffer = map.get_element(temp);        //get element returns the symbol of the given position

        object_info temp_info_object;                

        temp_info_object.shortest_distance = distance[temp.x][temp.y];     //this part is self explanatory
        temp_info_object.initial_move = initial_move[temp.x][temp.y];
        temp_info_object.posn = temp;


        if(char_buffer == GOLD)                 // if the current position is gold push it into the gold
                                                // gold vector        
            gold.push_back(temp_info_object);

        //if the position is a tank or a falcon update the corresponding objects. But the neighbours shouldnt 
      // be pushed. so continue the process

        else if (char_buffer == enemy_ID.tank_symbol)       
        {
            opp_tank = temp_info_object;
            continue;
        }
        else if (char_buffer == enemy_ID.falcon_symbol)
        {
            opp_falcon = temp_info_object;
            continue;
        }
        else if( char_buffer ==  my_ID.falcon_symbol)
        {
            my_falcon = temp_info_object;
            continue;
        }
        else if( char_buffer ==  WALL)
        {
            continue;
        }


        for(int i = 0; i<4; i++) // Going through current node's neighbours
        {
            d.get_from_integer (i);     
            temp1 = temp;
            temp1.go_in_direction (d);

            if(visited[temp1.x][temp1.y] == 0)
                //push the neighbours if they are not already visited
            {
                q.push(temp1);
                initial_move[temp1.x][temp1.y].dirn = d;
                //the initial move is the same as its parents
                                                                //initial move 
                visited[temp1.x][temp1.y] = 1;
                distance[temp1.x][temp1.y] = 1 + distance[x][y];
                //distance is one more than its parent
            }
        }
    }
    object_info null_gold;
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
}


/*This funtion does a breadth first traversal to find out the distances from the source to 
 * all important objects in the map.
 */


void Info::update_info (MapClass &map,Position source)
{
    update_distances(map,source);
    //strategic_moves_array[AGGRESSIVE] = calculate_best_move(AGGRESSIVE);
    //strategic_moves_array[DEFENSIVE] = calculate_best_move(DEFENSIVE);
    //strategic_moves_array[GREEDY] = calculate_best_move(GREEDY);
    //strategic_moves_array[CUSTOMISED] = calculate_best_move(CUSTOMISED);
    
}

void Info::print_info()
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
