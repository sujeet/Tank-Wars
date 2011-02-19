#include <iostream>

#define N 25
#define MAPNAME "map.txt"
#define NUM_PLAYERS 2
#define MAXMOVES 60
#define ENDGAME -1

using namespace std;

int score[NUM_PLAYERS];

class Arena
{
public :
     char map[N+1][N+1];
public :
     void create_from_file(string filename);
     int update(int move1, int move2);
};

void Arena::create_from_file(string filename)
{
     fstream file;
     file.open(filename.c_str());
     for (int i = 0; i < N; i++) {
          file >> this->map[i];
     }
}

int Arena::update(int move1, int move2) 
{
     int xcoord, ycoord;
     
     position pos1;
     position pos2;
     pos1 = this->get_tank_one_position();
     pos2 = this->get_tank_two_position();
     this->map[pos1.x][pos1.y] = EMPTY;
     this->map[pos2.x][pos2.y] = Empty;

     switch (move1){
     case 5:
          xcoord = 0;
          ycoord = -1;
          break;
     case 6:
          xcoord = 0;
          ycoord = 1;
          break;          
     case 7:
          xcoord = -1;
          ycoord = 0;
          break;    
     case 8:
          xcoord = 1;
          ycoord = 0;
          break;    
     default:
          xcoord = 0;
          ycoord = 0;
     }

     new_xcoord = pos1.x + xcoord;
     new_ycoord = pos1.y + ycoord;

     switch (map[new_xcoord][new_ycoord]){
     case WALL:
          score[1] += OTHER_DIE;
          return ENDGAME;
     case TANK_2:
          score[0]
     map[pos1.x + xcoord][pos1.y + ycoord] = 
     
     
     switch (move2){
     case 5:
          xcoord = 0;
          ycoord = -1;
          break;
     case 6:
          xcoord = 0;
          ycoord = 1;
          break;          
     case 7:
          xcoord = -1;
          ycoord = 0;
          break;    
     case 8:
          xcoord = 1;
          ycoord = 0;
          break;    
     default:
          xcoord = 0;
          ycoord = 0;
     }

}


int main() 
{
     Arena arena;
     arena.create_from_file(MAPNAME);
     int move1, move2;
     // initialize the scores to zero
     for (int i = 0; i < NUM_PLAYERS; i++) {
          score[i] = 0;
     }
     // run the game, exit when time exceeds or game ends
     for (int i = 0; i < MAXMOVES; i++) {
          move1 = get_player_one_move();
          move2 = get_player_two_move();
          if (arena.update(move1, move2) == ENDGAME) {
               break;
          }
     }
     return 0;
}

          
          
