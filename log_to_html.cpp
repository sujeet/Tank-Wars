#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define MAP_SIZE 51

int main() 
{
     ifstream infile;
     ifstream map;
     map.open("map.txt");
     char letter;
     cout << "<html><head></head><body onload = update_map_0()>" << endl;
     cout << "<div style='width: 500px; height: 500px; margin: 0pt; padding: 0pt; border: 0pt none; background: none repeat scroll 0% 0% black;' id='divboard'>" << endl;
     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               map >> letter;
               cout << "    <div id = '"<< i << "q" << j << "' style='-moz-border-radius:5px; -webkit-border-radius:5px; width: 10px; height: 10px; background: none repeat scroll 0% 0% black; margin: 0pt; padding: 0pt; float: left;' class = 'cell'></div>" << endl;
          }
     }
     cout << "</div>" << endl;
     infile.open("foobar");
     int x, y, i = 0;
     char k;
     cout << "<script type='text/javascript'>" << endl;
     cout << "var char_to_color_table = {}; \
              char_to_color_table['.'] = 'black'; \
              char_to_color_table['#'] = 'brown'; \
              char_to_color_table['G'] = 'yellow'; \
              char_to_color_table['D'] = 'white'; \ 
              char_to_color_table['2'] = 'blue'; \ 
              char_to_color_table['1'] = 'green'; \
              char_to_color_table['*'] = 'red';" << endl;
     cout << "function update_map_" << i << "() {" << endl;
     do {
          infile >> x >> y >> k;
          if (x != -1) {
               cout << "    document.getElementById('" << x << "q" << y << "').style.background = char_to_color_table['" << k << "'];" << endl;
          }
          else {
               i++;
               cout << "    var t= setTimeout('update_map_" << i << "()', 200);" << endl;
               cout << "}" << endl;
               cout << "function update_map_" << i << "() {" << endl;
          }
     }
     while ( not infile.eof() );
     cout << "}" << endl;
     cout << "</script><button onclick = update_map_0()>sujeet</button></body></html>" << endl;
     return 0;
}
