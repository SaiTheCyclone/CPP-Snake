#include "../game-components.h"
#include "../settings.h"
#include "../utils.h"

#include <cstdlib>
#include <map>
#include <ncurses.h>
#include <vector>

void checkCollision(std::vector<std::vector<int>> snakeBodyXY,
    bool *loopCondition)
{
    for (std::size_t i{ 1 }; i < snakeBodyXY.size(); ++i)
    {
        if (not isOverlappingXY(snakeBodyXY[0], snakeBodyXY[i])) continue;

        *loopCondition = false;
        break;
    }
}

void drawSprites(WINDOW *window, int winRatio, std::vector<int> *foodXY,
    std::vector<std::vector<int>> *snakeBodyXY)
{
    // Drawing Food
    randomizeFoodCrdts(winRatio, foodXY, snakeBodyXY);
    mvwaddch(window, (*foodXY)[1], (*foodXY)[0], FOOD_SPRITE);

    // Drawing Snake
    for (std::size_t i{ 0 }; i < (*snakeBodyXY).size(); ++i)
        mvwaddch(window, (*snakeBodyXY)[i][1], (*snakeBodyXY)[i][0], SNAKE_BODY);
}

void increaseSnakeLength(std::vector<std::vector<int>> *snakeBodyXY,
    std::vector<int> foodXY, int direction)
{
    for (std::size_t i{ 0 }; i < (*snakeBodyXY).size(); ++i)
    {
        bool isOverlap{ foodXY[0] == (*snakeBodyXY)[i][0]
            && foodXY[1] == (*snakeBodyXY)[i][1] };

        if (!isOverlap) continue;

        std::vector<int> newCoordinatesXY{};
        switch (direction)
        {
        case UP:
            newCoordinatesXY = { (*snakeBodyXY).back()[0], (*snakeBodyXY).back()[1] + 1 };
            break;
        case DOWN:
            newCoordinatesXY = { (*snakeBodyXY).back()[0], (*snakeBodyXY).back()[1] - 1 };
            break;
        case LEFT:
            newCoordinatesXY = { (*snakeBodyXY).back()[0] + 1, (*snakeBodyXY).back()[1]};
            break;
        case RIGHT:
            newCoordinatesXY = { (*snakeBodyXY).back()[0] - 1, (*snakeBodyXY).back()[1]};
            break;
        default:
            break;
        }

        (*snakeBodyXY).push_back(newCoordinatesXY);
        break;
    }
}

void moveSnake(std::vector<std::vector<int>> *snakeBodyXY,
    std::vector<int> *snakeHeadXY, int direction, int winRatio)
{
    switch (direction)
    {
    case UP:
        --(*snakeHeadXY)[1];
        if ((*snakeHeadXY)[1] <= -1) (*snakeHeadXY)[1] = winRatio;
        break;
    case DOWN:
        ++(*snakeHeadXY)[1];
        if ((*snakeHeadXY)[1] >= winRatio) (*snakeHeadXY)[1] = -1;
        break;
    case LEFT:
        --(*snakeHeadXY)[0];
        if ((*snakeHeadXY)[0] <= -1) (*snakeHeadXY)[0] = 2 * winRatio;
        break;
    case RIGHT:
        ++(*snakeHeadXY)[0];
        if ((*snakeHeadXY)[0] >= 2 * winRatio) (*snakeHeadXY)[0] = -1;
        break;
    default: break;
    }

    (*snakeBodyXY).pop_back();
    (*snakeBodyXY).insert((*snakeBodyXY).cbegin(), *snakeHeadXY);
}

void playerControls(const int input, const int winRatio, int *direction,
    bool *loopCondition, std::vector<int> snakeHeadXY,
    std::vector<std::vector<int>> snakeBodyXY)
{
    if (input == 'q') *loopCondition = false;

    // Player isn't allowed to move snake if the head is entering the window
    // edges
    if (!(snakeHeadXY[0] < 2*winRatio && snakeHeadXY[1] < winRatio)) return;

    switch (input)
    {
    case UP1: [[fallthrough]];
    case UP2:
        *direction = UP;
        break;
    case DOWN1: [[fallthrough]];
    case DOWN2:
        *direction = DOWN;
        break;
    case LEFT1: [[fallthrough]];
    case LEFT2:
        *direction = LEFT;
        break;
    case RIGHT1: [[fallthrough]];
    case RIGHT2:
        *direction = RIGHT;
        break;
    case 'q':
        *loopCondition = false;
        break;
    default:
        break;
    }
}

void randomizeFoodCrdts(int winRatio, std::vector<int> *foodXY,
    std::vector<std::vector<int>> *snakeBodyXY)
{
    for (std::size_t i{ 0 }; i < (*snakeBodyXY).size(); ++i)
    {
        bool isOverlap{ (*foodXY)[0] == (*snakeBodyXY)[i][0]
            && (*foodXY)[1] == (*snakeBodyXY)[i][1] };

        if (isOverlap)
        {
            (*foodXY) = randomizeCoordinates(winRatio);
            i = 0;
        }
    }
}
