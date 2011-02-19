#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
# define N 20
#define GOLD 'G'
#define EMPTY '.'
#define WALL '#'

class Direction 
{
     // 0 : UP
     // 1 : DOWN
     // 2 ; RIGHT
     // 3 : LEFT
public:
     int xdir, ydir;
     void get_from_integer (int inp);
     void print ()
	  {
	       cout << "Direction : " << xdir << " " << ydir << endl;
	  }
};

class Position
{
public:
     int x, y;
     
     void go_in_direction (Direction d)
	  {
	       x += d.xdir;
	       y += d.ydir;
	  }
     bool operator== (Position p)
	  {
	       return ((this->x == p.x) && (this->y == p.y));
      }
     void print ()
	  {
	       cout << "Position : " << x << " " << y << endl;
	  }
     
     
};


struct refer
{
     int shortest_distance;
     int initial_move;
     Position pos;
};

int dir_array[][2] = { {0, 1}, {0, -1}, { 1, 0}, {-1, 0}};

struct symbol_list
{
    char my_tank;
    char my_falcon;
    char enemy_tank;
    char enemy_falcon;
};

class Info
{
    vector <refer> gold;
    refer my_falcon;
    refer opp_falcon;
    refer opp_tank;
    refer nearest_gold;

    struct symbol_list symbol;
    public:
    Info(char mytank, char myfalcon, char enemytank, char enemyfalcon)
    {
        symbol.my_tank = mytank;
        symbol.my_falcon = myfalcon;
        symbol.enemy_tank = enemytank;
        symbol.enemy_falcon = enemyfalcon;
    }
    /*This funtion does a breadth first traversal to find out the distances from the source to 
     * all important objects in the map.
     */
    void update_info(char map[N+2][N+2],Position source)
    {
        queue <Position> q;
        vector< vector <int> > visited(N+2,vector <int>(N+2,0));
        vector< vector <int> > initial_move(N+2,vector <int>(N+2));
        vector< vector <int> > distance(N+2,vector <int>(N+2));
        Position temp;
        char char_buffer;
        int x,y;
        x=source.x;
        y=source.y;
        visited[source.x][source.y]=1;
        distance[source.x][source.y]=0;
        // Initially pushing all the valid neighbors into the queue
        for(int i = 0; i<4; i++)
        {
            if(map[source.x + dir_array[i][0]][source.y + dir_array[i][1]]==GOLD 
                    || map[source.x + dir_array[i][0]][source.y + dir_array[i][1]]==EMPTY )
            {
                temp.x=x + dir_array[i][0];
                temp.y=y + dir_array[i][1];
                q.push(temp);
                initial_move[x + dir_array[i][0]][y + dir_array[i][1]]=2;
                visited[x + dir_array[i][0]][y + dir_array[i][1]]=1;
                distance[x + dir_array[i][0]][y + dir_array[i][1]]=1;
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
            char_buffer = map[x][y];
            refer temp2;
            temp2.shortest_distance=distance[temp.x][temp.y];
            temp2.initial_move=initial_move[temp.x][temp.y];
            temp2.pos=temp;
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
               

            for(int i = 0; i<4; i++)
            {
                if(visited[x + dir_array[i][0]][y + dir_array[i][1]]==0)
                {
                    temp.x=x + dir_array[i][0];
                    temp.y=y + dir_array[i][1];
                    q.push(temp);
                    initial_move[x + dir_array[i][0]][y + dir_array[i][1]]= initial_move[x][y];
                    visited[x + dir_array[i][0]][y + dir_array[i][1]]=1;
                    distance[x + dir_array[i][0]][y + dir_array[i][1]]=1 + distance[x][y];
                }
            }
        }
        struct refer null_gold;
        null_gold.shortest_distance = -1;
        if(gold.size())
            nearest_gold = gold[0];
        else
            nearest_gold = null_gold;
    }
    
    void print_some_info()
    {
        cout<<nearest_gold.shortest_distance;
    }

};

int main()
{
     ifstream log_file("log_file", ios::in);
     int i, j;
     char a;
     char map[N+2][N+2];
     Position check;
     check.x=2;
     check.y=1;
     for(i = N+1; i>=0; i--)
     {
	  for(j = 0; j<N+2; j++)
	  {
	       log_file>>a;
	       map[i][j] = a;
	       cout<<a;
	  }
	  cout<<endl;
     }
     Info player1('1', 'M', '2', 'E');
     player1.update_info(map, check);
     player1.print_some_info();
     log_file.close();
     return 0;
}


