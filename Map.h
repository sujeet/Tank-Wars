#ifndef MAP_H

#define MAP_H

#include <fstream>

#include "Misc_Classes.h"

class MapClass
{
private :
     char map[MAP_SIZE][MAP_SIZE];
     std::ofstream log_file;
public :
     /* Constructor */
     MapClass();
     
     /* Method to initiate from a file */
     void create_from_file (std::string filename);
     
     /* Methods to access the elemnets */
     char get_element (int x_coord, int y_coord) const;
     char get_element (Position posn) const;

     /* Methods to check whether the given pons/coord has the symbol */
     bool is_symbol (int x_coord, int y_coord, char symbol) const;
     bool is_symbol (Position posn, char symbol) const;
     
     /* Methods to set the elements of map */
     void set_element(int x_coord, int y_coord, char data, bool print_log = true);
     void set_element(Position posn, char data, bool print_log = true);

     /* Function to print to log file */
     void print_log(int x, int y, char k);
     
     /* Destructor */
     ~MapClass();
};
     
#endif
