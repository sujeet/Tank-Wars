#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "Constants.h"

using namespace std;

string symbol_to_html_class (char symbol) 
{
     switch (symbol){
     case WALL               : return "wall"                  ; break;
     case EMPTY              : return "empty"                 ; break;
     case GOLD               : return "gold"                  ; break;

     case TANK1              : return "tank1"                 ; break;
     case TANK2              : return "tank2"                 ; break;
     case MACHINE_GUN        : return "machine_gun"           ; break;

     case BULLET1            : return "bullet1"               ; break;
     case BULLET2            : return "bullet2"               ; break;
     case MACHINE_GUN_BULLET : return "bullet3"               ; break;

     case DEAD               : return "dead"                  ; break;
     case FALCON1            : return "falcon1"               ; break;
     case FALCON2            : return "falcon2"               ; break;
     default                 :
          cerr << symbol << endl;
          exit (-1);
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
             << "    width                 :	 6px;                                               " << endl
             << "    height                :	 6px;                                               " << endl
             << "    background            :	 none repeat scroll 0% 0% " << FALCON1_COLOUR << "; " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    border-style          :	 solid;                                             " << endl
             << "    border-color          :	 black;                                             " << endl
             << "    border-width          :	 2px;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".falcon2 {                                                                         " << endl
             << "    width                 :	 6px;                                               " << endl
             << "    height                :	 6px;                                               " << endl
             << "    background            :	 none repeat scroll 0% 0% " << FALCON2_COLOUR << "; " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    border-style          :	 solid;                                             " << endl
             << "    border-color          :	 black;                                             " << endl
             << "    border-width          :	 2px;                                               " << endl
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
             << ".machine_gun {                                                                     " << endl
             << "    -moz-border-radius    :	3px;                                                " << endl
             << "    -webkit-border-radius :	3px;                                                " << endl
             << "    width                 :	 10px;                                              " << endl
             << "    height                :	 10px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% "<< MACHINE_GUN_COLOUR<<";" << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".bullet1 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	  4px;                                              " << endl
             << "    height                :	  4px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BULLET1_COLOUR << "; " << endl
             << "    margin                :	 3px;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".bullet2 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	  4px;                                              " << endl
             << "    height                :	  4px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BULLET2_COLOUR << "; " << endl
             << "    margin                :	 3px;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".bullet3 {                                                                         " << endl
             << "    -moz-border-radius    :	5px;                                                " << endl
             << "    -webkit-border-radius :	5px;                                                " << endl
             << "    width                 :	  4px;                                              " << endl
             << "    height                :	  4px;                                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BULLET3_COLOUR << "; " << endl
             << "    margin                :	 3px;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "   }                                                                               " << endl
             << ".gold {                                                                            " << endl
             << "    -moz-border-radius    :	3px;                                                " << endl
             << "    -webkit-border-radius :	3px;                                                " << endl
             << "    width                 :	 8px;                                               " << endl
             << "    height                :	 8px;                                               " << endl
             << "    background            :	 none repeat scroll 0% 0% " << GOLD_COLOUR << ";    " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "       border-style       :	 solid;                                             " << endl
             << "       border-color       :	 gold;                                              " << endl
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
             << ".metacontainer {                                                                   " << endl
             << "    -moz-border-radius    :	10px;                                               " << endl
             << "    -webkit-border-radius :	10px;                                               " << endl
             << "    -moz-box-shadow       :	5px 5px 7px #555555;                                " << endl
             << "    -webkit-box-shadow    :	5px 5px 7px #555555;                                " << endl
             << "    width                 :	 720px;                                             " << endl
             << "    height                :	 500px;                                             " << endl
             << "    margin                :	 0pt auto;                                          " << endl
             << "    padding               :	 20px;                                              " << endl
             << "    border                :	 0pt none;                                          " << endl
             << "    background            :	 none repeat scroll 0% 0% " << WALL_COLOUR << ";    " << endl
             << "}                                                                                  " << endl
             << ".status {                                                                          " << endl
             << "    width                 :	 200px;                                             " << endl
             << "    -moz-border-radius    :	10px;                                               " << endl
             << "    -webkit-border-radius :	10px;                                               " << endl
             << "    float                 :	 right;                                             " << endl
             << "    margin                :	 10px 0 0;                                          " << endl
             // << "    padding               :	 0pt;                                               " << endl
             // << "    border                :	 0pt none;                                          " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BKG_COLOUR << ";     " << endl
             << "}                                                                                  " << endl
             << ".control {                                                                         " << endl
             << "    width                 :	 200px;                                             " << endl
             << "    -moz-border-radius    :	10px;                                               " << endl
             << "    -webkit-border-radius :	10px;                                               " << endl
             << "    float                 :	 right;                                             " << endl
             << "    margin                :	 20px 0 0;                                          " << endl
             // << "    padding               :	 0pt;                                               " << endl
             // << "    border                :	 0pt none;                                          " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BKG_COLOUR << ";     " << endl
             << "}                                                                                  " << endl
             << "button {                                                                           " << endl
             << "    width                 :	 100%;                                              " << endl
             << "}                                                                                  " << endl
             << ".container{                                                                        " << endl
             << "    width                 :	 500px;                                             " << endl
             << "    height                :	 500px;                                             " << endl
             << "    margin                :	 0pt;                                               " << endl
             << "    padding               :	 0pt;                                               " << endl
             << "    float                 :	 left;                                              " << endl
             << "    border                :	 0pt none;                                          " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BKG_COLOUR << ";     " << endl
             << "}                                                                                  " << endl;

     // The following is the css for buttons.
     str_out << ".black {                                                                                                                " << endl
             << "	color                 : #d7d7d7;                                                                                     " << endl
             << "	border                : solid 1px #333;                                                                              " << endl
             << "	background            : #333;                                                                                        " << endl
             << "	background            : -webkit-gradient(linear, left top, left bottom, from(#666), to(#000));                       " << endl
             << "	background            : -moz-linear-gradient(top,  #666,  #000);                                                     " << endl
             << "	filter                :  progid:DXImageTransform.Microsoft.gradient(startColorstr='#666666', endColorstr='#000000'); " << endl
             << "}                                                                                                                       " << endl
             << ".black:hover {                                                                                       " << endl
             << "	background            : #000;                                                                                        " << endl
             << "	background            : -webkit-gradient(linear, left top, left bottom, from(#444), to(#000));                       " << endl
             << "	background            : -moz-linear-gradient(top,  #444,  #000);                                                     " << endl
             << "	filter                :  progid:DXImageTransform.Microsoft.gradient(startColorstr='#444444', endColorstr='#000000'); " << endl
             << "}                                                                                                                       " << endl
             << ".black:active {                                                                                      " << endl
             << "	color                 : #666;                                                                                        " << endl
             << "	background            : -webkit-gradient(linear, left top, left bottom, from(#000), to(#444));                       " << endl
             << "	background            : -moz-linear-gradient(top,  #000,  #444);                                                     " << endl
             << "	filter                :  progid:DXImageTransform.Microsoft.gradient(startColorstr='#000000', endColorstr='#666666'); " << endl
             << "}                                                                                                                       " << endl
             << "                                                                                                                        " << endl
             << ".button {                                                                                                               " << endl
             << "	display               : inline-block;                                                                                " << endl
             << "	zoom                  : 1; /* zoom and *display = ie7 hack for display:inline-block */                               " << endl
             << "	*display              : inline;                                                                                      " << endl
             << "	vertical-align        : baseline;                                                                                    " << endl
             << "	margin                : 0 2px;                                                                                       " << endl
             << "	outline               : none;                                                                                        " << endl
             << "	cursor                : pointer;                                                                                     " << endl
             << "	text-align            : center;                                                                                      " << endl
             << "	text-decoration       : none;                                                                                        " << endl
             << "	font                  : 14px/100% Arial, Helvetica, sans-serif;                                                      " << endl
             << "	padding               : 5px;                                                                                         " << endl
             << "	text-shadow           : 0 1px 1px rgba(0,0,0,.3);                                                                    " << endl
             << "	-webkit-border-radius : .5em;                                                                                        " << endl
             << "	-moz-border-radius    : .5em;                                                                                        " << endl
             << "	border-radius         : .5em;                                                                                        " << endl
             << "	-webkit-box-shadow    : 0 1px 2px rgba(0,0,0,.2);                                                                    " << endl
             << "	-moz-box-shadow       : 0 1px 2px rgba(0,0,0,.2);                                                                    " << endl
             << "	box-shadow            : 0 1px 2px rgba(0,0,0,.2);                                                                    " << endl
             << "}                                                                                                                       " << endl
             << ".button:hover {                                                                                       " << endl
             << "	text-decoration       : none;                                                                                        " << endl
             << "}                                                                                                                       " << endl
             << ".button:active {                                                                                      " << endl
             << "	position              : relative;                                                                                    " << endl
             << "	top                   : 1px;                                                                                         " << endl
             << "}                                                                                                                       " << endl;

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

string insert_controls ()
{
      ostringstream str_out;
      str_out << "<div class ='control'>                                                                           " << endl
              << "<table style = 'width: 200px; border-spacing : 10px'>                                            " << endl
              << "    <tr>                                                                                         " << endl
              << "        <th colspan='2'> Controls </th>                                                          " << endl
              << "    </tr>                                                                                        " << endl
              << "    <tr>                                                                                         " << endl
              << "        <td>                                                                                     " << endl
              << "            <button id='pause_button' class='button black' onclick='pause_game()'>               " << endl
              << "                Play                                                                             " << endl
              << "            </button>                                                                            " << endl
              << "        </td>                                                                                    " << endl
              << "    </tr>                                                                                        " << endl
              << "    <tr>                                                                                         " << endl
              << "        <td>                                                                                     " << endl
              << "            <button id='slow_button' class='button black' onclick='slow()'>                      " << endl
              << "                Slower                                                                           " << endl
              << "            </button>                                                                            " << endl
              << "        </td>                                                                                    " << endl
              << "    </tr>                                                                                        " << endl
              << "    <tr>                                                                                         " << endl
              << "        <td>                                                                                     " << endl
              << "            <button id='fast_button' class='button black' onclick='fast()'>                      " << endl
              << "                Faster                                                                           " << endl
              << "            </button>                                                                            " << endl
              << "        </td>                                                                                    " << endl
              << "    </tr>                                                                                        " << endl
              << "    <tr>                                                                                         " << endl
              << "        <td>                                                                                     " << endl
              << "            <button id='restart_button' class='button black' onclick='window.location.reload()'> " << endl
              << "                Restart                                                                          " << endl
              << "            </button>                                                                            " << endl
              << "        </td>                                                                                    " << endl
              << "    </tr>                                                                                        " << endl
              << "</table>                                                                                         " << endl
              << "</div>                                                                                           " << endl;

      return str_out.str();
}
     

string insert_status_notifier ()
{
      ostringstream str_out;
      str_out << "<div class ='status'>                                                                                            " << endl
              << "<table style = 'width : 200px'>                                                                                  " << endl
              << "    <tr>                                                                                                         " << endl
              << "        <th colspan='2'> Scores </th>                                                                            " << endl
              << "    </tr>                                                                                                        " << endl
              << "    <tr>                                                                                                         " << endl
              << "        <td> Player one : </td>                                                                                  " << endl
              << "        <td> <div id='player1_score' style = 'color : " << TANK1_COLOUR << "; font-weight: bold'> 0 </div> </td> " << endl
              << "    </tr>                                                                                                        " << endl
              << "    <tr>                                                                                                         " << endl
              << "        <td> Player two : </td>                                                                                  " << endl
              << "        <td> <div id='player2_score' style = 'color : " << TANK2_COLOUR << "; font-weight: bold'> 0 </div> </td> " << endl
              << "    </tr>                                                                                                        " << endl
              << "    <tr>                                                                                                         " << endl
              << "        <td>                                                                                                     " << endl
              << "           <span style = 'font-weight : bold'> Moves :</span>                                                    " << endl
              << "        </td>                                                                                                    " << endl
              << "        <td> <div id='number_of_moves'> 0 </div> </td>                                                           " << endl
              << "    </tr>                                                                                                        " << endl
              << "</table>                                                                                                         " << endl
              << "</div>                                                                                                           " << endl;

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

             << "char_to_color_table['" << EMPTY              << "'] = 'empty';       " << endl
             << "char_to_color_table['" << WALL               << "'] = 'wall';        " << endl 
             << "char_to_color_table['" << GOLD               << "'] = 'gold';        " << endl 
             << "char_to_color_table['" << DEAD               << "'] = 'dead';        " << endl 

             << "char_to_color_table['" << TANK1              << "'] = 'tank1';       " << endl  
             << "char_to_color_table['" << TANK2              << "'] = 'tank2';       " << endl
             << "char_to_color_table['" << MACHINE_GUN        << "'] = 'machine_gun'; " << endl

             << "char_to_color_table['" << BULLET1            << "'] = 'bullet1';     " << endl
             << "char_to_color_table['" << BULLET2            << "'] = 'bullet2';     " << endl
             << "char_to_color_table['" << MACHINE_GUN_BULLET << "'] = 'bullet3';     " << endl

             << "char_to_color_table['" << FALCON1            << "'] = 'falcon1';     " << endl
             << "char_to_color_table['" << FALCON2            << "'] = 'falcon2';     " << endl;

     // Now insert the function list
     str_out << insert_func_list();
     
     // Now the play function
     str_out << "function play()                                                                 " << endl
             << "{                                                                               " << endl
             << "   if (function_counter > max_number_of_funcs) {                                " << endl
             << "       return;                                                                  " << endl
             << "   }                                                                            " << endl
             << "   if (! pause) {                                                               " << endl
             << "       func_array[function_counter]();                                          " << endl
             << "       document.getElementById('number_of_moves').innerHTML = function_counter; " << endl
             << "       function_counter = function_counter + 1;                                 " << endl
             << "       var t = setTimeout ('play()', delay);                                    " << endl
             << "   }                                                                            " << endl
             << "   else {                                                                       " << endl
             << "       return;                                                                  " << endl
             << "   }                                                                            " << endl
             << "}                                                                               " << endl;

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

int main() 
{
     ofstream html_file;
     html_file.open(HTML_FILE);
     
     html_file << "<html>" << endl;
     html_file << "<head>" << endl;
     html_file << insert_css();
     html_file << "</head>" << endl;
     html_file << "<body>" << endl;
     html_file << "<div class = 'metacontainer'>" << endl;
     html_file << make_divs ( (char*) MAP_FILE );
     html_file << insert_status_notifier();
     html_file << insert_controls();
     html_file << "</div>" << endl;
     html_file << insert_js();

     html_file.close();
     return 0;
}
