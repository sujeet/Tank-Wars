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
     cout << "<html><head>" << endl;
     cout << "<style type='text/css'>\n\
    .wall {width: 10px; height: 10px; background: none repeat scroll 0% 0% #282B1F; margin: 0pt; padding: 0pt; float: left;}\n\
    .empty {-moz-border-radius:5px; -webkit-border-radius:5px; width: 10px; height: 10px; background: none repeat scroll 0% 0% none; margin: 0pt; padding: 0pt; float: left;}\n\
    .tank1 {-moz-border-radius:5px; -webkit-border-radius:5px; width: 10px; height: 10px; background: none repeat scroll 0% 0% green; margin: 0pt; padding: 0pt; float: left;}\n\
    .tank2 {-moz-border-radius:5px; -webkit-border-radius:5px; width: 10px; height: 10px; background: none repeat scroll 0% 0% blue; margin: 0pt; padding: 0pt; float: left;}\n\
    .bullet {-moz-border-radius:5px; -webkit-border-radius:5px; width:  5px; height:  5px; background: none repeat scroll 0% 0% black; margin: 2.5px; padding: 0pt; float: left;}\n\
    .gold {-moz-border-radius:3px; -webkit-border-radius:3px; width: 8px; height: 8px; background: none repeat scroll 0% 0% goldenRod; margin: 0pt; padding: 0pt; float: left; border-style: solid; border-width:1px;}\n\
    .dead {-moz-border-radius:5px; -webkit-border-radius:5px; width: 10px; height: 10px; background: none repeat scroll 0% 0% red; margin: 0pt; padding: 0pt; float: left;}\n\
</style>" << endl;
     cout << "</head><body onload = update_map_0()>" << endl;
     cout << "<div style='width: 500px; height: 500px; margin: 0pt; padding: 0pt; border: 0pt none; background: none repeat scroll 0% 0% #E7ECD6;' id='divboard'>" << endl;
     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               map >> letter;
               cout << "    <div id = '"<< i << "q" << j << "' class = 'cell'></div>" << endl;
          }
     }
     cout << "</div>" << endl;
     cout << "<span> Player one (green) score : <div id = 'player1_score'>foo</div> </span>" << endl;
     cout << "<span> Player one (green) score : <div id = 'player2_score'>foo</div> </span>" << endl;
     infile.open("foobar");
     int x, y, i = 0;
     char k;
     cout << "<script type='text/javascript'>" << endl;
     // cout << "var char_to_color_table = {}; \n\
     //          char_to_color_table['.'] = 'black'; \n\
     //          char_to_color_table['#'] = 'brown'; \n\
     //          char_to_color_table['G'] = 'yellow'; \n\
     //          char_to_color_table['D'] = 'white'; \n\
     //          char_to_color_table['2'] = 'blue'; \n\
     //          char_to_color_table['1'] = 'green'; \n\
     //          char_to_color_table['*'] = 'red';" << endl;
     cout << "var char_to_color_table = {}; \n\
              char_to_color_table['.'] = 'empty'; \n\
              char_to_color_table['#'] = 'wall'; \n\
              char_to_color_table['G'] = 'gold'; \n\
              char_to_color_table['D'] = 'dead'; \n\
              char_to_color_table['2'] = 'tank2'; \n\
              char_to_color_table['1'] = 'tank1'; \n\
              char_to_color_table['*'] = 'bullet';" << endl;
     cout << "function update_map_" << i << "() {" << endl;
     do {
          infile >> x >> y >> k;
          if (k != 'F') {
               cout << "    document.getElementById('" << x << "q" << y << "').className = char_to_color_table['" << k << "'];" << endl;
          }
          else {
               cout <<      "document.getElementById('player1_score').innerHTML = '" << x << "';" << endl;
               cout <<      "document.getElementById('player2_score').innerHTML = '" << y << "';" << endl;
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
