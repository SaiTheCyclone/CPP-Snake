#include "../settings.h"
#include "../utils.h"

#include <fstream>
#include <ncurses.h>
#include <string>
#include <string_view>

void startWin()
{
    initscr();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    raw();
    noecho();
    refresh();
}

WINDOW *createGameWin(int *winRatio)
{
    WINDOW *gameWin{ newwin(*winRatio, 2*(*winRatio), (LINES - *winRatio)/2, (COLS - 2*(*winRatio))/2) };
    box(gameWin, 0, 0);
    keypad(gameWin, true);
    wtimeout(gameWin, 100);
    wrefresh(gameWin);

    return gameWin;
}

void changeWinRatio(int argc, char *argv[], int *currentWinRatio)
{
    if (argc != 2) return;

    const std::string_view givenWinRatio{ argv[1] };

    if (!isCStrInteger(givenWinRatio)) return;
    else *currentWinRatio = std::stoi(static_cast<std::string>(givenWinRatio));
}
