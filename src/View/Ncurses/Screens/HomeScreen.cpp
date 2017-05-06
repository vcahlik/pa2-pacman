#include <ncurses.h>
#include "HomeScreen.h"

HomeScreen::HomeScreen(WINDOW *window)
    : Screen(window),
      menu(window, 15, 8)
{

}

void HomeScreen::show()
{
    attron(A_BOLD);
    mvprintw(6, 15, "Welcome to pacman.");
    attroff(A_BOLD);
    menu.addOption(1, "New game");
    menu.addOption(2, "Quit");
    menu.show();
    uint32_t choice = menu.getUsersChoice();

    switch (choice)
    {
        case 1:

    }
}
