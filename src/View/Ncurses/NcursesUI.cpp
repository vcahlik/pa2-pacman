#include "NcursesUI.h"
#include "NcursesUtils.h"
#include "NcursesGameView.h"
#include "ViewConfig.h"
#include "../../Controller/GameController.h"

#include <ncurses.h>
#include <stdexcept>
#include <iostream>

void NcursesUI::show()
{
    try
    {
        initNcurses();
    }
    catch(std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    std::unique_ptr<Game> game(new Game("../examples/maps/1.pacmap"));
    std::unique_ptr<NcursesGameView> gameView(new NcursesGameView(game.get()));

    GameController controller(game.get(), gameView.get());
    controller.startGame();


    endNcurses();
}

void NcursesUI::displayGame()
{

}

void NcursesUI::initNcurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    refresh();

    if (!has_colors())
    {
        endwin();
        throw std::runtime_error("Terminal does not support colors");
    }

    start_color();
    NcursesUtils::initColors();
}

void NcursesUI::endNcurses()
{
    endwin();
}

const Color &NcursesUI::getColors() const
{
    return colors;
}
