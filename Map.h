#ifndef MAP_H

#define MAP_H

#include "Misc_Classes.h"

class MapClass
{
private :
public :
     char map[MAP_SIZE][MAP_SIZE];
     /* Method to initiate from a file */
     void create_from_file (std::string filename);
     
     /* Methods to access the elemnets */
     char get_element (int x_coord, int y_coord) const;
     char get_element (Position posn) const;

     /* Methods to check whether the given pons/coord has the symbol */
     bool is_symbol (int x_coord, int y_coord, char symbol) const;
     bool is_symbol (Position posn, char symbol) const;
     
     /* Methods to set the elements of map */
     void set_element(int x_coord, int y_coord, char data);
     void set_element(Position posn, char data);
};
     
#endif
