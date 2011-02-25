#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
#define MAP_SIZE 51
#define ASCII_CHARS 128
#define MAX_CLASS_NAME_LENGTH 10
#define DELAY 200
#define DELAY_STEP 50 
#define MIN_DELAY 50
#define MAX_DELAY 1000
#define END_SCORE_CHAR 'F'

// Colour variables
#define TANK1_COLOUR   "green"
#define TANK2_COLOUR   "blue"
#define BULLET1_COLOUR "black"
#define BULLET2_COLOUR "black"
#define BKG_COLOUR     "#E7ECD6"
#define GOLD_COLOUR    "goldenRod"
#define WALL_COLOUR    "#282B1F"
#define DEAD_COLOUR    "red"
#define FALCON1_COLOUR "maroon"
#define FALCON2_COLOUR "orange"

string symbol_to_html_class (char symbol) 
{
     switch (symbol){
     case '*' : return "bullet"                ; break;
     case '#' : return "wall"                  ; break;
     case '.' : return "empty"                 ; break;
     case '1' : return "tank1"                 ; break;
     case '2' : return "tank2"                 ; break;
     case 'A' : return "bullet1"               ; break;
     case 'B' : return "bullet2"               ; break;
     case 'D' : return "dead"                  ; break;
     case 'G' : return "gold"                  ; break;
     case 'E' : return "falcon1"               ; break;
     case 'F' : return "falcon2"               ; break;
     default  : return "Some thing went wrong" ;
     }
}

string insert_css ()
{
     ostringstream str_out;
     str_out << "<style type = text/css>                                                            " << endl;
     str_out << ".wall {                                                                            " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << WALL_COLOUR << ";    " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "}                                                                                  " << endl
             << ".empty {                                                                           " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% none;                     " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".falcon1 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << FALCON1_COLOUR << "; " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".falcon2 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << FALCON2_COLOUR << "; " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".tank1 {                                                                           " << endl
             << "    -moz-border-radius    :	3px;                                                " << endl
             << "    -webkit-border-radius :	3px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0%  " << TANK1_COLOUR << ";  " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".tank2 {                                                                           " << endl
             << "    -moz-border-radius    :	3px;                                                " << endl
             << "    -webkit-border-radius :	3px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << TANK2_COLOUR << ";   " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".bullet1 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	  5px;                                              " << endl
             << "    height                :	  5px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BULLET1_COLOUR << "; " << endl
             << "    margin                :	 2.5px;                                             " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".bullet2 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	  5px;                                              " << endl
             << "    height                :	  5px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BULLET2_COLOUR << "; " << endl
             << "    margin                :	 2.5px;                                             " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".gold {                                                                            " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	 8px;                                               " << endl
             << "    height                :	 8px;                                               " << endl
             << "    background            :	 none repeat scroll 0% 0% " << GOLD_COLOUR << ";    " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "       border-style       :	 solid;                                             " << endl
             << "    border-width          :	1px;                                                " << endl
             << "}                                                                                  " << endl
             << ".dead {                                                                            " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << DEAD_COLOUR << ";    " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "}                                                                                  " << endl
             << ".container{                                                                        " << endl
             << "    width                 :	 500px;                                             " << endl
             << "    height                :	 500px;                                             " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    border                :	 0pt none;                                          " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BKG_COLOUR << ";     " << endl
             << "}                                                                                  " << endl;
     str_out << "</style>" << endl;
     return str_out.str();
}

string make_divs (char * filename)
{
     ostringstream str_out;
     ifstream map;
     char letter;
     
     map.open(filename);

     str_out << "<div class='container'>" << endl;
     for (int i = 0; i < MAP_SIZE - 1; i++){
          for (int j = 0; j < MAP_SIZE - 1; j++){
               map >> letter;
               str_out << "    <div id = '"<< i << "q" << j << "' class = '" << symbol_to_html_class(letter) << "'></div>" << endl;
          }
     }
     str_out << "</div>" << endl;

     map.close();
     return str_out.str();
}
     
string status_notifier()
{
     ostringstream str_out;
     str_out << "<span> Player one (green) score : <div id = 'player1_score'>foo</div> </span>" << endl;
     str_out << "<span> Player two (blue) score : <div id = 'player2_score'>foo</div> </span>" << endl;
     return str_out.str();
}

string insert_func_list()
{
     ostringstream str_out;
     ifstream logfile;
     int x, y, i = 0;
     char k;

     logfile.open(LOG_FILE);

     str_out << "function update_map_" << i << "() {" << endl;
     do {
          logfile >> x >> y >> k;
          if (k != END_SCORE_CHAR) {
               str_out << "    document.getElementById('" << x << "q" << y << "').className = char_to_color_table['" << k << "'];" << endl;
          }
          else {
               str_out << "    document.getElementById('player1_score').innerHTML = '" << x << "';" << endl;
               str_out << "    document.getElementById('player2_score').innerHTML = '" << y << "';" << endl;
               i++;
               // str_out << "    var t= setTimeout('update_map_" << i << "()', 1);" << endl;
               str_out << "}" << endl;
               str_out << "function update_map_" << i << "() {" << endl;
          }
     }
     while ( not logfile.eof() );

     str_out << "}" << endl;

     str_out << "var max_number_of_funcs = " << i << ";" << endl;
     while ( i >= 0 ) {
          str_out << "func_array[" << i << "] = update_map_" << i << ";" << endl;
          i--;
     }
     logfile.close();
     return str_out.str();
}

string insert_js()
{
     ostringstream str_out;
     str_out << "<script type='text/javascript'>" << endl;

     // Global variabrles for js
     str_out << "var pause = true;                      " << endl
             << "var func_array = {};                   " << endl
             << "var function_counter = 0;              " << endl
             << "var delay = " << DELAY << ";           " << endl
             << "var delay_step = " << DELAY_STEP << "; " << endl
             << "var min_delay = " << MIN_DELAY << ";   " << endl
             << "var max_delay = " << MAX_DELAY << ";   " << endl
             << "var char_to_color_table = {};          " << endl

             << "char_to_color_table['.'] = 'empty';  " << endl
             << "char_to_color_table['#'] = 'wall';   " << endl 
             << "char_to_color_table['G'] = 'gold';   " << endl 
             << "char_to_color_table['D'] = 'dead';   " << endl 
             << "char_to_color_table['2'] = 'tank2';  " << endl  
             << "char_to_color_table['1'] = 'tank1';  " << endl
             << "char_to_color_table['A'] = 'bullet1';" << endl
             << "char_to_color_table['B'] = 'bullet2';" << endl
             << "char_to_color_table['E'] = 'falcon1';" << endl
             << "char_to_color_table['F'] = 'falcon2';" << endl;

     // Function for sleeping
     str_out << "function pausecomp(millis)        " << endl
             << "{                                 " << endl 
             << "    var date = new Date();        " << endl 
             << "    var curDate = null;           " << endl 
             << "    do { curDate = new Date(); }  " << endl 
             << "    while(curDate-date < millis); " << endl 
             << "}                                 " << endl;
     
     // Now insert the function list
     str_out << insert_func_list();
     
     // Now the play function
     str_out << "function play()                                                 " << endl
             << "{                                                               " << endl
             << "   if (function_counter > max_number_of_funcs) {                " << endl
             << "       return;                                                  " << endl
             << "   }                                                            " << endl
             << "   if (! pause) {                                               " << endl
             << "       func_array[function_counter]();                          " << endl
             << "       function_counter = function_counter + 1;                 " << endl
             << "       var t = setTimeout ('play()', delay);                    " << endl
             << "   }                                                            " << endl
             << "   else {                                                       " << endl
             << "       return;                                                  " << endl
             << "   }                                                            " << endl
             << "}                                                               " << endl;

     str_out << "function pause_game()                                                " << endl
             << "{                                                                    " << endl
             << "    pause = ! pause;                                                 " << endl
             << "    document.getElementById('pause_button').innerHTML = 'Play';      " << endl
             << "    if ( ! pause ) {                                                 " << endl
             << "        play();                                                      " << endl
             << "        document.getElementById('pause_button').innerHTML = 'Pause'; " << endl
             << "    }                                                                " << endl
             << "}                                                                    " << endl;

     str_out << "function fast()                                             " << endl
             << "{                                                           " << endl
             << "    if (delay >= min_delay) {                               " << endl
             << "        delay -= delay_step;                                " << endl
             << "    }                                                       " << endl
             << "}                                                           " << endl;
                                                                             
     str_out << "function slow()                                             " << endl
             << "{                                                           " << endl
             << "    if (delay <= max_delay) {                               " << endl
             << "        delay += delay_step;                                " << endl
             << "    }                                                       " << endl
             << "}                                                           " << endl;

     str_out << "</script>" << endl;

     return str_out.str();
}

string insert_control()
{
     ostringstream str_out;
     str_out << "<button id = 'pause_button' onclick = 'pause_game()'> " << endl
             << "  Play                                                " << endl
             << "</button>                                             " << endl
             << "<button id = 'slow_button' onclick = 'slow()'>        " << endl
             << "  Slower                                              " << endl
             << "</button>                                             " << endl
             << "<button id = 'fast_button' onclick = 'fast()'>        " << endl
             << "  Faster                                              " << endl
             << "</button>                                             " << endl;
     return str_out.str();
}

int main() 
{
     ofstream html_file;
     html_file.open(HTML_FILE);
     
     html_file << "<html>" << endl;
     html_file << "<head>" << endl;
     html_file << insert_css();
     html_file << "</head>" << endl;
     html_file << "<body>" << endl;
     html_file << make_divs (MAP_FILE);
     html_file << status_notifier();
     html_file << insert_js();
     html_file << insert_control();

     html_file.close();
     return 0;
}
