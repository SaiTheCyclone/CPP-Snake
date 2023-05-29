#pragma once

#include <ncurses.h>

// Window Settings
#define DEFAULT_WIN_RATIO 20

// Controls
#define UP1 KEY_UP
#define DOWN1 KEY_DOWN
#define LEFT1 KEY_LEFT
#define RIGHT1 KEY_RIGHT

#define UP2 'w'
#define DOWN2 's'
#define LEFT2 'a'
#define RIGHT2 'd'

// Sprites
#define SNAKE_BODY '#'
#define FOOD_SPRITE '*'

// Direction Macros represented by Integers
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void startWin();
WINDOW *createGameWin(int *winRatio);
void changeWinRatio(int argc, char *argv[], int *currentWinRatio);
