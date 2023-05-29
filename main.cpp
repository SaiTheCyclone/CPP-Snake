#include "include/game-components.h"
#include "include/settings.h"
#include "include/utils.h"

#include <iostream>
#include <ncurses.h>
#include <vector>

void gameLoop(WINDOW *gameWin, int winRatio)
{
    std::vector<int> snakeHeadXY{ winRatio, winRatio/2 };
    std::vector<std::vector<int>> snakeBodyXY{ snakeHeadXY, };
    std::vector<int> foodXY{ randomizeCoordinates(winRatio) };

    int direction{ RIGHT };

    bool playing{ true };
    while (playing)
    {
        // Game functions are in include/program/game-components.cpp
        mvwaddstr(gameWin, 0, 1, ((std::string)"Score: "
            + std::to_string(snakeBodyXY.size())).c_str());
        drawSprites(gameWin, winRatio, &foodXY, &snakeBodyXY);
        playerControls(wgetch(gameWin), winRatio, &direction, &playing,
            snakeHeadXY, snakeBodyXY);
        moveSnake(&snakeBodyXY, &snakeHeadXY, direction, winRatio);
        increaseSnakeLength(&snakeBodyXY, foodXY, direction);
        checkCollision(snakeBodyXY, &playing);
        wclear(gameWin);
        box(gameWin, 0, 0);
    }
}

int main(int argc, char *argv[])
{
    int winRatio{ DEFAULT_WIN_RATIO };
    changeWinRatio(argc, argv, &winRatio);
    startWin();

    WINDOW *gameWin{ createGameWin(&winRatio) };
    gameLoop(gameWin, winRatio);

    endwin();
    std::cout << "Game over!\n";
    return 0;
}
