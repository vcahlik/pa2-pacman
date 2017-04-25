#include "NcursesView.h"
#include "NcursesUtils.h"
#include "GameWindow.h"
#include "ViewConfig.h"

#include <ncurses.h>

void NcursesView::show()
{
    initscr();
    cbreak();
    refresh();


    GameWindow gameWindow("../examples/maps/1.pacmap", *this);
    gameWindow.takeControl();


    endwin();
}

void NcursesView::displayGame()
{

}
