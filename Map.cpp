#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Map.h"

using namespace std;

void MapClass::create_from_file (string filename) 
{
     ifstream infile;
     char letter;
     infile.open (filename.c_str());
     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               infile >> letter;
               this->set_element (i, j, letter, false);
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
          cout << x_coord << " " << y_coord << " " << data << endl;
     }
}

void MapClass::set_element (Position posn, char data, bool print_log) 
{
     this->set_element(posn.x, posn.y, data, print_log);
}
