#define UP 72                        
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

#define WATER_BOMB 10
#define FIELD 0
#define WATER_ATTACK 444
#define ENEMY 44
#define WATER_BOMB_DELAY 2000

#define MONSTERS 1
#define DEFAULT_PLAYER_POS_X 1
#define DEFAULT_PLAYER_POS_Y 1
#define DEFAULT_MONSTER_POS_X 10
#define DEFAULT_MONSTER_POS_Y 19


typedef enum { false, true } bool;

// function`s proto types

int remove_character(int);
int move_character(int);
void show_character(int);
void gotoxy(int, int);
void remove_cursor(void);
void show_map(int[][21]);
void hide_water(int, int);
void show_water(int, int);
void water_attack(int, int);
void start_page(void);
void monster(void);
void ending_page(void);
void victory_page(void);

void new_monster(void);
void debug(void);
int debug_cnt = 0;
int move_sw;

// global variables

int pos_x;  // variable to move x
int pos_y; // variable to move y
int ATTACK_COUNT;		//enable number to attack
int ATTACK_DIS = 2;		// attack distance
short ready = false;
int pos_a_x;
int pos_a_y;

int victory = false;

// temp variable

int ATT_X;
int ATT_Y;
int KEY;
int mob_count;
int life = true;

int max_width;
int max_height;

// temp struct

struct monsterxy {

	int m_x;
	int m_y;
	short life;

} mob[MONSTERS];


int MAP[21][21] = {
	{4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 3},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7},
};