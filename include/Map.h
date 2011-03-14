#ifndef MAP_H

#define MAP_H

#include <fstream>
#include <vector>

#include "Misc_Classes.h"
#include "Constants.h"

class MapClass
{
private :
     std::ofstream log_file;

public :
     /* Variables indicating tank1 and tank2 init_posns */
     char map[MAP_SIZE][MAP_SIZE];
     Position tank1_init_posn;
     Position tank2_init_posn;

     /* Variables indicating falcon 1 nd 2 init_posns */
     Position falcon1_posn;
     Position falcon2_posn;

     /* Variables indicating machineguns' positions */
     std::vector <Position> machine_guns_posns;
     
     /* Constructor */
     MapClass();
     /* MapClass(MapClass map); */
     
     /* Method to initiate from a file */
     void create_from_file (std::string filename);
     
     /* Methods to access the elemnets */
     char get_element (int x_coord, int y_coord) const;
     char get_element (Position posn) const;

     /* Methods to check whether the given posn/coord has the symbol */
     bool is_symbol (int x_coord, int y_coord, char symbol) const;
     bool is_symbol (Position posn, char symbol) const;
     
     /* Methods to set the elements of map */
     void set_element(int x_coord, int y_coord, char data, bool print_log = true);
     void set_element(Position posn, char data, bool print_log = true);

     /* Function to print to log file */
     void print_log(int x, int y, char k);
     
     /* Assignment operator */
     MapClass & operator = (const MapClass &);
     
     /* Destructor */
     ~MapClass();
};
     
#endif
