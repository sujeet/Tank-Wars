#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
#include "Info.h"
#include "Map.h"
#define N 20

using namespace std;

void object_info::print ()
{
    cout << "Shortest_Distance : " << shortest_distance << endl;
    cout << "INITIAL_MOVE : " ;
    initial_move.dirn.print();
    posn.print ();
}


Info::Info(const ID mine, const ID enemy)
{
    my_ID.tank_symbol = mine.tank_symbol;
    my_ID.falcon_symbol = mine.falcon_symbol;
    enemy_ID.tank_symbol = enemy.tank_symbol;
    enemy_ID.falcon_symbol = enemy.falcon_symbol;
            
    weightage_table[0][0] = 5; 
    weightage_table[0][1] = 5; 
    weightage_table[0][2] = 5; 
    weightage_table[0][3] = 5; 
    weightage_table[1][0] = 5; 
    weightage_table[1][1] = 5; 
    weightage_table[1][2] = 5; 
    weightage_table[1][3] = 5; 
    weightage_table[2][0] = 5; 
    weightage_table[2][1] = 5; 
    weightage_table[2][2] = 5; 
    weightage_table[2][3] = 5; 
    weightage_table[3][0] = 5; 
    weightage_table[3][1] = 5; 
    weightage_table[3][2] = 5; 
    weightage_table[3][3] = 5; 
}

int Info::find_the_maximum( float real_weightage[4] )
{
    int max_value,i,max_posn;
    max_value=0;
    for( i=0;i<4;i++ )
    {
        if( real_weightage[i] > max_value )
        {
            max_value = real_weightage[i];
            max_posn=i;
        }
    }
    return max_posn;
}

Move Info::calculate_best_move( int mode )
{
    //a call to  am i in danger to be included.

    float real_weightage[4];
    Move moves[4];
    int i,j,maximum;


    real_weightage[GO_TO_GOLD] = 
        float ( weightage_table[mode][GO_TO_GOLD]) / float( nearest_gold.shortest_distance );
    moves[GO_TO_GOLD] = nearest_gold.initial_move;

    real_weightage[ATTACK_ENEMY_FALCON] = 
        float ( weightage_table[mode][ATTACK_ENEMY_FALCON]) / float( opp_falcon.shortest_distance );
    moves[ATTACK_ENEMY_FALCON] = opp_falcon.initial_move;

    real_weightage[ATTACK_ENEMY_TANK] = 
        float ( weightage_table[mode][ATTACK_ENEMY_TANK]) / float( opp_tank.shortest_distance );
    moves[ATTACK_ENEMY_TANK] = opp_tank.initial_move;

    real_weightage[DEFEND_MY_FALCON] = 
        float ( weightage_table[mode][DEFEND_MY_FALCON]) / float( my_falcon.shortest_distance );
    moves[DEFEND_MY_FALCON] = my_falcon.initial_move;
    
    maximum = 0;
    //maximum = find_the_maximum ( real_weightage );
    return moves[maximum];

}

/*This funtion does a breadth first traversal to find out the distances from the source to 
 * all important objects in the map.
 */

void Info::update_distances(MapClass &map,Position source)
{
    queue <Position> q;
    vector< vector <int> > visited(N+2,vector <int>(N+2,0));
    vector< vector <Move> > initial_move(N+2,vector <Move>(N+2));
    vector< vector <int> > distance(N+2,vector <int>(N+2));
    Position temp, temp3;
    Direction d;
    char char_buffer;
    int x, y;

    x=source.x;
    y=source.y;
    visited[source.x][source.y] = 1;
    distance[source.x][source.y] = 0;

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
            visited[temp.x][temp.y] = 1;
            distance[temp.x][temp.y] = 1;
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
        else if (char_buffer == enemy_ID.tank_symbol)
        {
            opp_tank = temp2;
            continue;
        }
        else if (char_buffer == enemy_ID.falcon_symbol)
        {
            opp_falcon = temp2;
            continue;
        }
        else if( char_buffer ==  my_ID.falcon_symbol)
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
    {
        nearest_gold = gold[0];
    }
    else
    {
        nearest_gold = null_gold;
    }
}

void Info::update_info (MapClass &map,Position source)
{
    update_distances(map,source);
    strategic_moves_array[AGGRESSIVE] = calculate_best_move(AGGRESSIVE);
    strategic_moves_array[DEFENSIVE] = calculate_best_move(DEFENSIVE);
    strategic_moves_array[GREEDY] = calculate_best_move(GREEDY);
    strategic_moves_array[CUSTOMISED] = calculate_best_move(CUSTOMISED);
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



int main()
{
    MapClass test_map;
    test_map.create_from_file("log_file");
    int i, j;
    char a;
    Position check;
    check.x=4;
    check.y=10;
    ID mine, enemy;
    mine.player_no = 1;
    mine.tank_symbol = '1';
    mine.falcon_symbol = 'M';

    enemy.player_no = 2;
    enemy.tank_symbol = '2';
    enemy.falcon_symbol = 'E';
    Info player1(mine, enemy);
    player1.update_info(test_map, check);
    player1.print_info();
    return 0;
}


