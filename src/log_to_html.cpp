#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "Constants.h"

using namespace std;

string insert_css ()
{
     ostringstream str_out;
     str_out << "<style type = text/css>                                                          " << endl
             << ".metacontainer {                                                                 " << endl
             << "    -moz-border-radius    :	10px;                                             " << endl
             << "    -webkit-border-radius :	10px;                                             " << endl
             << "    -moz-box-shadow       :	5px 5px 7px #555555;                              " << endl
             << "    -webkit-box-shadow    :	5px 5px 7px #555555;                              " << endl
             << "    width                 :	 " << (MAP_SIZE - 1)*10 + 420 << "px;             " << endl
             << "    height                :	 " << (MAP_SIZE - 1)*10 << "px;                   " << endl
             << "    margin                :	 0pt auto;                                        " << endl
             << "    padding               :	 20px;                                            " << endl
             << "    border                :	 0pt none;                                        " << endl
             << "    background            :	 none repeat scroll 0% 0% " << BKG_COLOUR << ";   " << endl
             << "}                                                                                " << endl
             << ".legend {                                                                        " << endl
             << "    width                 :	 200px;                                           " << endl
             << "    height                :	 480px;                                           " << endl
             << "    -moz-border-radius    :	10px;                                             " << endl
             << "    -webkit-border-radius :	10px;                                             " << endl
             << "    float                 :	 left;                                            " << endl
             << "    margin                :	 10px 10px 10px 0px;                              " << endl
             << "    background            :	 none repeat scroll 0% 0% " << EMPTY_COLOUR << "; " << endl
             << "}                                                                                " << endl
             << ".status {                                                                        " << endl
             << "    width                 :	 200px;                                           " << endl
             << "    -moz-border-radius    :	10px;                                             " << endl
             << "    -webkit-border-radius :	10px;                                             " << endl
             << "    float                 :	 right;                                           " << endl
             << "    margin                :	 10px 0 0;                                        " << endl
             << "    background            :	 none repeat scroll 0% 0% " << EMPTY_COLOUR << "; " << endl
             << "}                                                                                " << endl
             << ".control, .points {                                                              " << endl
             << "    width                 :	 200px;                                           " << endl
             << "    -moz-border-radius    :	10px;                                             " << endl
             << "    -webkit-border-radius :	10px;                                             " << endl
             << "    float                 :	 right;                                           " << endl
             << "    margin                :	 20px 0 0;                                        " << endl
             << "    background            :	 none repeat scroll 0% 0% " << EMPTY_COLOUR << "; " << endl
             << "}                                                                                " << endl
             << ".points table {                                                                  " << endl
             << "    font-size             :	 14px;                                            " << endl
             << "}                                                                                " << endl
             << ".point_number {                                                                  " << endl
             << "    text-align            :	 right;                                           " << endl
             << "}                                                                                " << endl
             << "button {                                                                         " << endl
             << "    width                 :	 100%;                                            " << endl
             << "}                                                                                " << endl
             << ".container{                                                                      " << endl
             << "    margin                :	 0pt;                                             " << endl
             << "    padding               :	 0pt;                                             " << endl
             << "    float                 :	 left;                                            " << endl
             << "    border                :	 0pt none;                                        " << endl
             << "    background            :	 none repeat scroll 0% 0% " << EMPTY_COLOUR << "; " << endl
             << "}                                                                                " << endl;

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
     
     map.open(filename);

     str_out << "<canvas id = 'container' class = 'container' width = '" << (MAP_SIZE-1)*10 << "' height = '" << (MAP_SIZE-1)*10 << "'>" << endl;
     str_out << "</canvas>" << endl;

     map.close();
     return str_out.str();
}

string insert_legend ()
{
      ostringstream str_out;
      str_out << "<div class='legend'>                                                                   " << endl
              << "<table style='width: 200px; border-spacing: 10px; color: " << TEXT_COLOUR << ";'>      " << endl
              << "    <tbody><tr>                                                                        " << endl
              << "        <th colspan='2'> Legend </th>                                                  " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << GOLD << "' height=10px width=10px></canvas>               " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Gold                                                                      " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << FALCON1 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player one falcon                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << TANK1 << "' height=10px width=10px></canvas>              " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player one tank                                                           " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << BULLET1 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player one bullet                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << BUNKER1 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player one bunker                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << FALCON2 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player two falcon                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << TANK2 << "' height=10px width=10px></canvas>              " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player two tank                                                           " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "                                                                                       " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << BULLET2 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player two bullet                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << BUNKER2 << "' height=10px width=10px></canvas>            " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Player two bunker                                                         " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << MACHINE_GUN << "' height=10px width=10px></canvas>        " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Machine Gun                                                               " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << MACHINE_GUN_BULLET << "' height=10px width=10px></canvas> " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Machine gun bullet                                                        " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "    </tr>                                                                              " << endl
              << "    <tr>                                                                               " << endl
              << "        <td>                                                                           " << endl
              << "            <canvas id='" << WALL << "' height=10px width=10px></canvas>               " << endl
              << "        </td>                                                                          " << endl
              << "        <td> Wall                                                                      " << endl
              << "        </td>                                                                          " << endl
              << "    </tr>                                                                              " << endl
              << "</tbody></table>                                                                       " << endl
              << "</div>                                                                                 " << endl;
      return str_out.str();
}
     

string insert_controls ()
{
      ostringstream str_out;
      str_out << "<div class ='control'>                                                                           " << endl
              << "<table style='width: 200px; border-spacing: 10px; color: " << TEXT_COLOUR << ";'>                " << endl
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
     
string insert_points_table ()
{
      ostringstream str_out;
      str_out << "<div class ='points'>                                                   " << endl
              << "<table style='width: 200px; color: " << TEXT_COLOUR << ";'>             " << endl
              << "    <tr>                                                                " << endl
              << "        <th colspan='3'> Points </th>                                   " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "        <td> Enemy falcon shot </td>                                    " << endl
              << "        <td> : &nbsp; </td>                                             " << endl
              << "        <td class='point_number'> " << ENEMY_FALCON_KILLED << "</td>    " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "        <td> Enemy tank shot </td>                                      " << endl
              << "        <td> : </td>                                                    " << endl
              << "        <td class='point_number'> " << ENEMY_KILLED << "</td>           " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "        <td> Alive at the end </td>                                     " << endl
              << "        <td> : </td>                                                    " << endl
              << "        <td class='point_number'> " << ALIVE_AT_THE_END << "</td>       " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "        <td> Enemy bunker shot </td>                                    " << endl
              << "        <td> : </td>                                                    " << endl
              << "        <td class='point_number'> " << DESTROYED_ENEMY_BUNKER << "</td> " << endl
              << "    </tr>                                                               " << endl
              << "    <tr>                                                                " << endl
              << "        <td> Picked up gold </td>                                       " << endl
              << "        <td> : </td>                                                    " << endl
              << "        <td class='point_number'> " << PICKED_UP_GOLD << "</td>         " << endl
              << "    </tr>                                                               " << endl
              << "</table>                                                                " << endl
              << "</div>                                                                  " << endl;

      return str_out.str();
}

string insert_status_notifier ()
{
      ostringstream str_out;
      str_out << "<div class ='status'>                                                                                            " << endl
              << "<table style='width: 200px; color: " << TEXT_COLOUR << ";'>                                                      " << endl
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
               str_out << "    fill_the_canvas(" << y*10 << ", " <<  x*10 << ", '" << k << "'); " << endl;
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
     str_out << "var pause = true;                                  " << endl
             << "var func_array = {};                               " << endl
             << "var function_counter = 1;                          " << endl
             << "var delay = " << DELAY << ";                       " << endl
             << "var delay_step = " << DELAY_STEP << ";             " << endl
             << "var min_delay = " << MIN_DELAY << ";               " << endl
             << "var max_delay = " << MAX_DELAY << ";               " << endl
             << "var x;                                             " << endl
             << "var y;                                             " << endl
             << "var canvas = document.getElementById('container'); " << endl
             << "var ctx = canvas.getContext('2d');                 " << endl;
     
     // Function to draw the blast when the bot is dead.
     str_out << "function drawStar(ctx,r, x, y, color, spikes){   " << endl
             << "    ctx.save();                                  " << endl
             << "    ctx.beginPath();                             " << endl
             << "    ctx.translate (x, y);                        " << endl
             << "    ctx.fillStyle = color;                       " << endl
             << "    ctx.moveTo(r,0);                             " << endl
             << "    for (var i=0;i<( 2*spikes - 1 );i++){        " << endl
             << "        ctx.rotate(Math.PI/spikes);              " << endl
             << "        if(i%2 == 0) {                           " << endl
             << "            ctx.lineTo((r/0.525731)*0.200811,0); " << endl
             << "        } else {                                 " << endl
             << "            ctx.lineTo(r,0);                     " << endl
             << "        }                                        " << endl
             << "    }                                            " << endl
             << "    ctx.closePath();                             " << endl
             << "    ctx.fill();                                  " << endl
             << "    ctx.restore();                               " << endl
             << "}                                                " << endl;

     // Function to fill out the canvas at appropriate places.
     str_out << "function fill_the_canvas (x, y, name)                   " << endl
             << "{                                                       " << endl
             << "   switch (name)                                        " << endl
             << "   {                                                    " << endl
             << "       case '" << DEAD << "' :                          " << endl
             << "           drawStar(ctx, 10, x + 5, y + 5, 'red', 7);   " << endl
             << "           drawStar(ctx, 6, x + 5, y + 5, 'yellow', 7); " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << WALL << "' :                          " << endl
             << "           ctx.fillStyle = '" << WALL_COLOUR << "';     " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << EMPTY << "' :                         " << endl
             << "           ctx.fillStyle = '" << EMPTY_COLOUR << "';    " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << GOLD << "' :                          " << endl
             << "           ctx.fillStyle = 'rgba(256, 220, 0, 0.5)';    " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           ctx.fillStyle = 'rgba(256, 220, 0, 1)';      " << endl
             << "           ctx.fillRect (x+2, y+2, 6, 6);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << BUNKER1 << "' :                       " << endl
             << "           ctx.fillStyle = 'rgba(0, 256, 0, 0.2)';      " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << BUNKER2 << "' :                       " << endl
             << "           ctx.fillStyle = 'rgba(256, 0, 0, 0.2)';      " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << TANK1 << "' :                         " << endl
             << "           ctx.fillStyle = 'rgba(0, 256, 0, 0.5)';      " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           ctx.fillStyle = 'rgba(0, 256, 0, 1)';        " << endl
             << "           ctx.fillRect (x+2, y+2, 6, 6);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << TANK2 << "' :                         " << endl
             << "           ctx.fillStyle = 'rgba(256, 0, 0, 0.5)';      " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           ctx.fillStyle = 'rgba(256, 0, 0, 1)';        " << endl
             << "           ctx.fillRect (x+2, y+2, 6, 6);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << MACHINE_GUN << "' :                   " << endl
             << "           ctx.fillStyle = 'rgba(0, 256, 256, 0.5)';    " << endl
             << "           ctx.fillRect (x, y, 10, 10);                 " << endl
             << "           ctx.fillStyle = 'rgba(0, 256, 256, 1)';      " << endl
             << "           ctx.fillRect (x+2, y+2, 6, 6);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << BULLET1 << "' :                       " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 0.5)';  " << endl
             << "           ctx.fillRect (x+3, y+3, 4, 4);               " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 1)';    " << endl
             << "           ctx.fillRect (x+4, y+4, 2, 2);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << BULLET2 << "' :                       " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 0.5)';  " << endl
             << "           ctx.fillRect (x+3, y+3, 4, 4);               " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 1)';    " << endl
             << "           ctx.fillRect (x+4, y+4, 2, 2);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << MACHINE_GUN_BULLET << "' :            " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 0.5)';  " << endl
             << "           ctx.fillRect (x+3, y+3, 4, 4);               " << endl
             << "           ctx.fillStyle = 'rgba(256, 256, 256, 1)';    " << endl
             << "           ctx.fillRect (x+4, y+4, 2, 2);               " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << FALCON1 << "' :                       " << endl
             << "           ctx.fillStyle = '" << FALCON1_COLOUR << "';  " << endl
             << "           ctx.beginPath();                             " << endl
             << "           ctx.arc(x+5, y+5, 5, 0, Math.PI*2, true);    " << endl
             << "           ctx.closePath();                             " << endl
             << "           ctx.fill();                                  " << endl
             << "           break;                                       " << endl
             << "                                                        " << endl
             << "       case '" << FALCON2 << "' :                       " << endl
             << "           ctx.fillStyle = '" << FALCON2_COLOUR << "';  " << endl
             << "           ctx.beginPath();                             " << endl
             << "           ctx.arc(x+5, y+5, 5, 0, Math.PI*2, true);    " << endl
             << "           ctx.closePath();                             " << endl
             << "           ctx.fill();                                  " << endl
             << "           break;                                       " << endl
             << "   }                                                    " << endl
             << "}                                                       " << endl;

     // Fill the legend with small canvases.
     str_out << "canvas = document.getElementById('" << GOLD << "');               " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << GOLD << "');                         " << endl
             << "canvas = document.getElementById('" << FALCON1 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << FALCON1 << "');                      " << endl
             << "canvas = document.getElementById('" << TANK1 << "');              " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << TANK1 << "');                        " << endl
             << "canvas = document.getElementById('" << BULLET1 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << BULLET1 << "');                      " << endl
             << "canvas = document.getElementById('" << BUNKER1 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << BUNKER1 << "');                      " << endl
             << "canvas = document.getElementById('" << FALCON2 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << FALCON2 << "');                      " << endl
             << "canvas = document.getElementById('" << TANK2 << "');              " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << TANK2 << "');                        " << endl
             << "canvas = document.getElementById('" << BULLET2 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << BULLET2 << "');                      " << endl
             << "canvas = document.getElementById('" << BUNKER2 << "');            " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << BUNKER2 << "');                      " << endl
             << "canvas = document.getElementById('" << MACHINE_GUN << "');        " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << MACHINE_GUN << "');                  " << endl
             << "canvas = document.getElementById('" << MACHINE_GUN_BULLET << "'); " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << MACHINE_GUN_BULLET << "');           " << endl
             << "canvas = document.getElementById('" << WALL << "');               " << endl
             << "ctx = canvas.getContext('2d');                                    " << endl
             << "fill_the_canvas (0, 0, '" << WALL << "');                         " << endl;
     
     // Set the canvas and ctx back.
     str_out << "canvas = document.getElementById('container'); " << endl
             << "ctx = canvas.getContext('2d');                 " << endl;
     
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

     // Now call the function to paint initially.
     str_out << "update_map_0 ();" << endl;

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
     html_file << "<body style='background:#aaaaaa;'>" << endl;
     html_file << "<div class = 'metacontainer'>" << endl;
     html_file << insert_legend ();
     html_file << make_divs ( (char*) MAP_FILE );
     html_file << insert_status_notifier();
     html_file << insert_controls();
     html_file << insert_points_table();
     html_file << "</div>" << endl;
     html_file << insert_js();

     html_file.close();
     return 0;
}
