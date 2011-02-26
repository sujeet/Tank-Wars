#ifndef constants_h
#define constants_h

// For Arena.cpp
#define DO_NOT_MOVE 10


// For Info.h
#define GO_TO_GOLD 0
#define ATTACK_ENEMY_FALCON 1
#define ATTACK_ENEMY_TANK 2
#define DEFEND_MY_FALCON 3

#define AGGRESSIVE 0
#define DEFENSIVE 1 
#define GREEDY 2
#define CUSTOMISED 3

// For log_to_html.cpp
#define MAP_SIZE 51

#define ASCII_CHARS 128
#define MAX_CLASS_NAME_LENGTH 10
#define DELAY 200
#define DELAY_STEP 50 
#define MIN_DELAY 50
#define MAX_DELAY 1000
#define END_SCORE_CHAR '$'

// Colour variables
#define TANK1_COLOUR       "#008000"
#define TANK2_COLOUR       "#0000ff"
#define MACHINE_GUN_COLOUR "maroon"

#define BULLET1_COLOUR     "black"
#define BULLET2_COLOUR     "black"
#define BULLET3_COLOUR     "black"

#define BKG_COLOUR         "#E7ECD6"
#define GOLD_COLOUR        "goldenRod"
#define WALL_COLOUR        "#282B1F"

#define DEAD_COLOUR        "red"
#define FALCON1_COLOUR     "#55ee55"
#define FALCON2_COLOUR     "#7777ff"

// For Misc_Classes.h
#define MACHINE_GUN_SHOOT_ONCE_IN_THIS_MANY 5
#define END_SCORE_CHAR '$'

#define GOLD                'G'
#define WALL                '#'
#define EMPTY               '.'
#define DEAD                'D'

#define TANK1               '1'
#define FALCON1             'F'
#define BULLET1             'A'

#define TANK2               '2'
#define FALCON2             'E'
#define BULLET2             'B'

#define MACHINE_GUN         'M'
#define MACHINE_GUN_BULLET  'K'

// For TankWars.cpp
#define TIMES 5000

// For Everybody
#define  UP  0
#define  DOWN  1
#define  RIGHT 2
#define  LEFT  3

#endif
