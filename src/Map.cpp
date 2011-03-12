#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "Map.h"

using namespace std;

MapClass::MapClass ()
{
     // Don't do anything here.
}

void MapClass::create_from_file (string filename) 
{
     ifstream infile;
     char letter;
     infile.open (filename.c_str());

     // Open the log file here, not in
     // the constructor.
     this->log_file.open(LOG_FILE);

     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               infile >> letter;
               if (letter == TANK1) {
                    this->tank1_init_posn = Position (i, j);
               }
               if (letter == TANK2) {
                    this->tank2_init_posn = Position (i, j);
               }
               if (letter == MACHINE_GUN) {
                    this->machine_guns_posns.push_back ( Position(i,j) );
               }
               if (letter == FALCON1) {
                    this->falcon1_posn = Position (i, j);
               }
               if (letter == FALCON2) {
                    this->falcon2_posn = Position (i, j);
               }
               // this->set_element (i, j, letter, false);
               this->set_element (i, j, letter);
          }
     }
     infile.close ();
}

char MapClass::get_element (int x_coord, int y_coord) const
{
     if ( (x_coord >= MAP_SIZE) 
          || (y_coord >= MAP_SIZE)
          || (x_coord < 0)
          || (y_coord < 0)
          ) {
          cerr << "ERROR : Tried to access map element out of bound." << endl;
          cerr << "    x : " << x_coord << endl;
          cerr << "    y : " << y_coord << endl;
          exit(-1);
     }
     else {
          return this->map[x_coord][y_coord];
     }
}

char MapClass::get_element (Position posn) const
{
     return this->get_element (posn.x, posn.y);
}

bool MapClass::is_symbol (int x_coord, int y_coord, char symbol) const
{
     return this->get_element(x_coord, y_coord) == symbol;
}

bool MapClass::is_symbol (Position posn, char symbol) const
{
     return this->get_element(posn) == symbol;
}

void MapClass::set_element (int x_coord, int y_coord, char data, bool print_log)
{
     if ( (x_coord >= MAP_SIZE) 
          || (y_coord >= MAP_SIZE)
          || (x_coord < 0)
          || (y_coord < 0)
          ) {
          cerr << "ERROR : Tried to access map element out of bound." << endl;
          cerr << "    x : " << x_coord << endl;
          cerr << "    y : " << y_coord << endl;
          exit(-1);
     }
     this->map[x_coord][y_coord] = data;
     if (print_log) {
          // The following code prints the "diff" into the logfile
          this->print_log(x_coord, y_coord, data);
     }
}

void MapClass::set_element (Position posn, char data, bool print_log) 
{
     this->set_element(posn.x, posn.y, data, print_log);
}

MapClass & MapClass::operator = (const MapClass & orig_map)
{
     this->tank1_init_posn = orig_map.tank1_init_posn;
     this->tank2_init_posn = orig_map.tank2_init_posn;
     this->falcon1_posn = orig_map.falcon1_posn;
     this->falcon2_posn = orig_map.falcon2_posn;
     this->machine_guns_posns = orig_map.machine_guns_posns;
     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               this->map[i][j] = orig_map.get_element (i, j);
          }
     }
     return *this;
}

MapClass::~MapClass ()
{
     this->log_file.close();
}

void MapClass::print_log(int x, int y, char k)
{
     this->log_file << x << " " << y << " " << k << endl;
}

     
