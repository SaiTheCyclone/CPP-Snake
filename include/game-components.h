#pragma once

#include <map>
#include <ncurses.h>
#include <vector>

void checkCollision(std::vector<std::vector<int>> snakeBodyXY,
    bool *loopCondition);

void drawSprites(WINDOW *window, int winRatio, std::vector<int> *foodXY,
    std::vector<std::vector<int>> *snakeBodyXY);

void increaseSnakeLength(std::vector<std::vector<int>> *snakeBodyXY,
    std::vector<int> foodXY, int direction);

void moveSnake(std::vector<std::vector<int>> *snakeBodyXY,
    std::vector<int> *snakeHeadXY, int direction, int winRatio);

void playerControls(const int input, const int winRatio, int *direction,
    bool *loopCondition, std::vector<int> snakeHeadXY,
    std::vector<std::vector<int>> snakeBodyXY);

void randomizeFoodCrdts(int winRatio, std::vector<int> *foodXY,
    std::vector<std::vector<int>> *snakeBodyXY);
