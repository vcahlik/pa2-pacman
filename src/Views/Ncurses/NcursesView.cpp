#include "NcursesView.h"

#include <ncurses.h>

void NcursesView::show()
{
    initscr();

    printw("prdel");
    refresh();
    getch();

    Game game("../examples/maps/1.pacmap");

    endwin();
}