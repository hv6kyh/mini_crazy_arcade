#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "1.h"
#include <time.h>
#include <stdlib.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

// The following rules apply when using a two-dimensional array as a coordinate system
// Array[y][x]
// function(x,y)

int main(void) {

	clock_t current, last;		// variable to contain tics

	// play BGM
	sndPlaySoundA("C:\\ca.wav", SND_ASYNC | SND_LOOP);

	// Resizing the console window
	system("mode con lines=25 cols=43"); 

	// Calculate horizontal and vertical size (used as a constant)
	max_width = sizeof(MAP[0]) / sizeof(int);
	max_height = sizeof(MAP) / sizeof(MAP[0]);

	//start_page();

	// print map
	show_map(MAP);

	// Change text color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

	// charactor initializing
	pos_x = DEFAULT_PLAYER_POS_X;		// user character default coordination
	pos_y = DEFAULT_PLAYER_POS_Y;

	gotoxy(pos_x, pos_y);
	printf("○");

	for (int i = 0; i < MONSTERS; i++) {		// monsters initializing

		mob[i].m_x = DEFAULT_MONSTER_POS_X + i;
		mob[i].m_y = DEFAULT_MONSTER_POS_Y;

		mob[i].life = true;

	}

	mob_count = MONSTERS;


	for (int i = 0; i < MONSTERS; i++) {		// display monsters

		gotoxy(mob[i].m_x, mob[i].m_y);
		printf("@");

	}

	remove_cursor();

	while (life == true && mob_count > 0) {

		debug();

		if (_kbhit()) {		// When there is key input

			KEY = _getch();

			if (KEY == SPACE) {		// If the pressed key is a space

				pos_a_x = pos_x;
				pos_a_y = pos_y;

				current = clock();
				last = current - current;

				// set water bomb
				MAP[pos_y][pos_x] = WATER_BOMB;

				// set timer to explode
				while (difftime(last, current) < WATER_BOMB_DELAY) {

					// can move my character while the timer is running.
					if (_kbhit())
						show_character(remove_character(move_character(_getch())));

					// enemy also move
					else {
						move_sw = 1;
						monster();
						last = clock();
					}

				}

				// Water bomb burst when timer is over
				water_attack(pos_a_x, pos_a_y);

			}
			
			// Move my character if the pressed key is a non-space key (direction key)
			else
				show_character(remove_character(move_character(KEY)));

		}

		// Move the enemy character when there is no key input
		else {
			move_sw = 1;
			monster();
		}

	}

	if (mob_count == 0)		// Conditions to Win
		victory_page();
	else					// Conditions to Lose
		ending_page();

}

void show_character(int L) {

	gotoxy(pos_x, pos_y);

	if (MAP[pos_y][pos_x] == WATER_BOMB)
		printf("⊙");

	else
		printf("○");


	return;
}

int move_character(int K) {

	// If you contact with a monster defeat
	if (MAP[pos_y][pos_x] == ENEMY)
		life = false;

	switch (K) {

	case LEFT:
		
		// If the value of the array corresponding to the next coordinates to be moved is 0
		if (MAP[pos_y][pos_x - 1] == 0 && (pos_x - 1) > 0)
			pos_x -= 1;
		else
			return (0);

		break;

	case RIGHT:

		if (MAP[pos_y][pos_x + 1] == 0 && (pos_x + 1) < max_width - 1)
			pos_x += 1;
		else
			return (0);

		break;

	case UP:

		if (MAP[pos_y - 1][pos_x] == 0 && (pos_y - 1) > 0)
			pos_y -= 1;
		else
			return (0);

		break;

	case DOWN:

		if (MAP[pos_y + 1][pos_x] == 0 && (pos_y + 1) < max_height -1)
			pos_y += 1;
		else
			return (0);

		break;

	}

	return K;

}


int remove_character(int R) {

	switch (R) {

	case LEFT:

		gotoxy(pos_x + 1, pos_y);


		if (MAP[pos_y][pos_x +1 ] != WATER_BOMB)
			printf("　");

		break;

	case RIGHT:

		gotoxy(pos_x - 1, pos_y);

		if (MAP[pos_y][pos_x - 1] != WATER_BOMB)
			printf("　");

		break;

	case UP:


		gotoxy(pos_x, pos_y + 1);

		if (MAP[pos_y + 1][pos_x] != WATER_BOMB)
			printf("　");

		break;

	case DOWN:

		gotoxy(pos_x, pos_y - 1);

		if (MAP[pos_y - 1][pos_x] != WATER_BOMB)
			printf("　");

		break;

	default:
		break;

	}

	return R;

}

void gotoxy(int x, int y) {

	COORD Pos = { x*2  , y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}
void remove_cursor(void) {

	CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curInfo.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	return;

}

void show_map(int C[][21]) {

	int col, row;

	// Repeat as many columns
	for (col = 0; col < max_height; col++) {

		// Repeat as many rows
		for (row = 0; row < max_width; row++) {

			// Print characters according to the value of an array element
			switch (MAP[col][row]) {

			case 1:
				printf("■");
				break;

			case 2:
				printf("──");
				break;

			case 3:
				printf("│ ");
				break;

			case 4:
				printf("┌");
				break;

			case 5:
				printf(" ┐");
				break;

			case 6:
				printf("└");
				break;

			case 7:
				printf(" ┘");
				break;

			default:
				printf("　");
				break;

			}

			//printf("%d ", MAP[col][row]);

		}

		printf("\n");

	}

	return;

}

int is_edge(int att_x, int att_y) {

	int result = false;

	if (att_x < 0 || att_x > max_width || att_y < 0 || att_y > max_height)
		return true;

	
	if (MAP[att_y][att_x] == 2 || MAP[att_y][att_x] == 3)
		result = true;	
	
	return result;
}


void water_attack(int t_x, int t_y) {

	// att_x, att_y Coordinates of a water bomb
	int att_x;
	int att_y;

	// S_C : Show Count, H_C : Hide_Count
	int S_C = 1, H_C = 1;
	int D, i, att_sw = true;

	att_x = t_x;
	att_y = t_y;

	while (S_C <= ATTACK_DIS) {

		show_water(att_x, att_y);
		MAP[att_y][att_x] = WATER_ATTACK;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x - i, att_y) == true)
				att_sw = false;

		}

		// If the next direction of the stream is not the outline border
		if ( att_sw == true ) {
			att_x -= S_C;
			show_water(att_x, att_y);
			MAP[att_y][att_x] = WATER_ATTACK;
			att_x = t_x;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x + i, att_y) == true)
				att_sw = false;

		}

		if ( att_sw == true ) {
			att_x += S_C;
			show_water(att_x, att_y);
			MAP[att_y][att_x] = WATER_ATTACK;
			att_x = t_x;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x, att_y - i) == true)
				att_sw = false;

		}

		if ( att_sw == true ) {
			att_y -= S_C;
			show_water(att_x, att_y);
			MAP[att_y][att_x] = WATER_ATTACK;
			att_y = t_y;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if ( is_edge(att_x, att_y + i) == true )
				att_sw = false;

		}

		if (att_sw == true) {
			att_y += S_C;
			show_water(att_x, att_y);
			MAP[att_y][att_x] = WATER_ATTACK;
			att_y = t_y;
		}
		else
			att_sw = true;

		S_C++;
		Sleep(100);

	}

	// When a character is hit by a water bomb
	if (MAP[pos_y][pos_x] == WATER_ATTACK)
		life = false;

	for (D = 0; D < MONSTERS; D++) {

		if (MAP[mob[D].m_y][mob[D].m_x] == WATER_ATTACK) {		// If D monster dies, you will not get D monster.
			mob[D].life = false;
			mob_count--;

		}

	}

	while (H_C <= ATTACK_DIS) {

		hide_water(att_x, att_y);
		MAP[att_y][att_x] = 0;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x - i, att_y) == true)
				att_sw = false;

		}

		if (att_sw == true) {
			att_x -= H_C;
			hide_water(att_x, att_y);
			MAP[att_y][att_x] = 0;
			att_x = t_x;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x + i, att_y) == true)
				att_sw = false;

		}

		if (att_sw == true) {
			att_x += H_C;
			hide_water(att_x, att_y);
			MAP[att_y][att_x] = 0;
			att_x = t_x;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x, att_y - i) == true)
				att_sw = false;

		}

		if (att_sw == true) {
			att_y -= H_C;
			hide_water(att_x, att_y);
			MAP[att_y][att_x] = 0;
			att_y = t_y;
		}
		else
			att_sw = true;

		for (i = 1; i <= S_C; i++) {

			if (is_edge(att_x, att_y + i) == true)
				att_sw = false;

		}

		if (att_sw == true) {
			att_y += H_C;
			hide_water(att_x, att_y);
			MAP[att_y][att_x] = 0;
			att_y = t_y;
		}
		else
			att_sw = true;

		H_C++;

	}

	return;

}

void hide_water(int att_x, int att_y) {

	gotoxy(att_x, att_y);
	printf("　");

	return;
}

void show_water(int att_x, int att_y) {

	gotoxy(att_x, att_y);
	printf("●");

	return;
}

// Prompt message and terminate key input
void start_page() {

	printf("방향키로 이동하며 스페이스바로 물풍선 공격을 할 수 있습니다.\n물줄기에 맞거나 적 캐릭터에 닿으면 패배하게 됩니다.\n");

	while (1) {
		if (_kbhit()) {
			system("cls");
			break;
			return;
		}
	}

}


void monster() {

	int i, j;
	int k = 0;

	srand((unsigned)time(NULL));

	// When the mob count is not 0: If more than one monster is alive
	while (move_sw) {

		do {
			i = rand() % MONSTERS;			// Random Number Pulling
		} while ( mob[i].life == false );	//If you have already drawn a monster that has already died,

		j = rand() % 4;	// direction select

		switch (j) {

		case 0:

			if (MAP[mob[i].m_y][mob[i].m_x + 1] == 0 && (mob[i].m_x + 1) < max_width - 1) {
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("　");
				MAP[mob[i].m_y][mob[i].m_x] = 0;
				mob[i].m_x += 1;
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("@");
				MAP[mob[i].m_y][mob[i].m_x] = ENEMY;
			}

			else
				continue;

			break;

		case 1:

			if (MAP[mob[i].m_y][mob[i].m_x - 1] == 0 && (mob[i].m_x - 1) > 0) {
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("　");
				MAP[mob[i].m_y][mob[i].m_x] = 0;
				mob[i].m_x -= 1;
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("@");
				MAP[mob[i].m_y][mob[i].m_x] = ENEMY;
			}

			else
				continue;

			break;

		case 2:

			if (MAP[mob[i].m_y + 1][mob[i].m_x] == 0 && mob[i].m_y + 1 < max_height - 1 ) {
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("　");
				MAP[mob[i].m_y][mob[i].m_x] = 0;
				mob[i].m_y += 1;
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("@");
				MAP[mob[i].m_y][mob[i].m_x] = ENEMY;
			}

			else
				continue;

			break;

		case 3:

			if (MAP[mob[i].m_y - 1][mob[i].m_x] == 0 && mob[i].m_y - 1 > 0) {
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("　");
				MAP[mob[i].m_y][mob[i].m_x] = 0;
				mob[i].m_y -= 1;
				gotoxy(mob[i].m_x, mob[i].m_y);
				printf("@");
				MAP[mob[i].m_y][mob[i].m_x] = ENEMY;
			}

			else
				continue;

			break;

		}

		Sleep(100);

		move_sw = 0;

	}

	if (MAP[pos_y][pos_x] == ENEMY)
		life = false;

	return;

}


void ending_page() {

	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　돌 연 사　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　돌 연 사　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　돌 연 사　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　돌 연 사　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　돌 연 사　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　돌 연 사　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　돌 연 사　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	gotoxy(6, 15);		printf("press any key");

	while (1) {
		if (_kbhit()) {
			break;
			return;
		}
	}

}

void victory_page() {

	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　승  리  !!　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　승  리  !!　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　승 리 !!　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　승 리 !!　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　승 리 !!　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 7);		printf("　─∧∧　∧∧─");
	gotoxy(6, 8);		printf("");
	gotoxy(6, 9);		printf(">　　승 리 !!　　<");
	gotoxy(6, 10);		printf("");
	gotoxy(6, 11);		printf("　─∨^∨^∨^∨─");

	Sleep(200);
	system("cls");

	gotoxy(6, 8);		printf("　─∧∧　∧∧─");
	gotoxy(6, 9);		printf("");
	gotoxy(6, 10);		printf(">　　승 리 !!　　<");
	gotoxy(6, 11);		printf("");
	gotoxy(6, 12);		printf("　─∨^∨^∨^∨─");

	gotoxy(6, 15);		printf("press any key");

	while (1) {
		if (_kbhit()) {
			break;
			return;
		}
	}

}


void debug(void) {
	
	gotoxy(1, 23);
	
	printf("%s %d %s %d %s %s : %d\n", "(x,y) = (", pos_x, ",", pos_y,")\t", "mob_count", mob_count);
	//printf("%d, %d", sizeof(MAP)/sizeof(MAP[0]), sizeof(MAP[0]) / sizeof(int));

	return;
}