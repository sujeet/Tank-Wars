class Direction 
{
public:
     int xdir, ydir;
};
     
class Position
{
public:
     int x, y;
};
     
class Arena
{
public:
     char Map[N+1][N+1];
     bool game_over_flag;
     Arena ();
     Tank tank1, tank2;
     ifstream infile;
     void print_map ();
     void create_from_file ();
     void get_player_moves ();
     void update ();
};

class Tank
{
public:
     class Bullet
     {
     public:
	  // Variables
	  Direction curr_dirn;
	  Position curr_posn;
	  bool disappear_flag;
	  
	  // Methods
	  Bullet ();
	  move ();
	  crashed_into_wall ();
	  crashed_into_gold ();
	  has_hit_tank ();
	  set_disappear_flag ();
	  update_map ();
     };

     // Variables
     int curr_gold_posn;
     Move curr_move;
     Direction curr_dirn, curr_bullet_dirn;
     bool dead_flag;
     int score;

     // Methods
     get_next_move ();
     update_posn ();
     move ();
     shoot_bullet ();
     evaluate_state ();
     incr_score (event);
     on_gold ();
     pick_up_gold ();
     crashed_into_wall ();
     die_by_wall_crash ();
     shot_by (Tank t);		// call t.bullet[i].has_hit_tank () , where bullet[i] is the bullet that did it
     crashed_tank (Tank t);
     die_by_tank_crash ();
     do_nothing ();
     set_dead_flag ();
     update_map ();
};
