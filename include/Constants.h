#ifndef CONSTANTS_H
#define CONSTANTS_H

// For Arena.cpp
#define DO_NOT_MOVE 10
#define TIMEOUT_LIMIT 500000    /* Half a second */
enum error
{
     NO_ERROR,
     TIMEOUT_ERROR,
     INVALID_MOVE_ERROR
};

// For Tank.cpp
enum event
{
     ENEMY_FALCON_KILLED	= 1000,
     ENEMY_KILLED		= 500,
     ALIVE_AT_THE_END		= 400,
     DESTROYED_ENEMY_BUNKER	= 65,
     PICKED_UP_GOLD		= 40,
     TIME_LIMIT_EXCEEDED	= -300,
     INVALID_MOVE		= -100
};

// For Info.h
#define GO_TO_NEAREST_GOLD 0
#define ATTACK_ENEMY_FALCON 1
#define ATTACK_ENEMY_TANK 2
#define DEFEND_MY_FALCON 3

#define AGGRESSIVE 0
#define DEFENSIVE 1 
#define GREEDY 2
#define CUSTOMIZED 3

// For log_to_html.cpp
#define MAP_SIZE 51

#define ASCII_CHARS 128
#define MAX_CLASS_NAME_LENGTH 10
#define DELAY 100
#define DELAY_STEP 30 
#define MIN_DELAY 5
#define MAX_DELAY 1000
#define END_SCORE_CHAR '$'

// Colour variables
#define GOLD_COLOUR               "goldenRod"
#define WALL_COLOUR               "#444444"
#define EMPTY_COLOUR              "black"
#define DEAD_COLOUR               "red"

#define TANK1_COLOUR              "#008000"
#define FALCON1_COLOUR            "#55ee55"
#define BULLET1_COLOUR            "black"

#define TANK2_COLOUR              "#ff00aa"
#define FALCON2_COLOUR            "#ff0044"
#define BULLET2_COLOUR            "black"

#define MACHINE_GUN_COLOUR        "blue"
#define MACHINE_GUN_BULLET_COLOUR "black"

#define TEXT_COLOUR               "#aaaaaa"
#define BKG_COLOUR                "black"

// For Misc_Classes.h
#define MACHINE_GUN_SHOOT_ONCE_IN_THIS_MANY 5
#define END_SCORE_CHAR '$'

// For map.h
#define GOLD                'G'
#define WALL                '#'
#define EMPTY               '.'
#define DEAD                'D'

#define TANK1               '1'
#define BUNKER1             'X'
#define FALCON1             'F'
#define BULLET1             'A'

#define TANK2               '2'
#define BUNKER2             'Y'
#define FALCON2             'E'
#define BULLET2             'B'

#define MACHINE_GUN         'M'
#define MACHINE_GUN_BULLET  'K'

// For TankWars.cpp
#define MAX_NUMBER_OF_MOVES 500
#define BULLET_SPEED 3

// For Everybody
#define  UP  0
#define  DOWN  1
#define  RIGHT 2
#define  LEFT  3

#define  GO_UP  0
#define  GO_DOWN  1
#define  GO_RIGHT 2
#define  GO_LEFT  3
#define  SHOOT_UP  4
#define  SHOOT_DOWN  5
#define  SHOOT_RIGHT 6
#define  SHOOT_LEFT  7

#define MAX_DIFFICULTY 10000

#endif
