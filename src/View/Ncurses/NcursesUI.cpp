#include "NcursesUI.h"
#include "NcursesUtils.h"
#include "NcursesGameView.h"
#include "ViewConfig.h"
#include "../../Controller/GameController.h"
#include "Screens/HomeScreen.h"

#include <ncurses.h>
#include <stdexcept>
#include <iostream>

void NcursesUI::show()
{
    try
    {
        console = NcursesUtils::initNcurses();
    }
    catch(std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    HomeScreen mainMenu(console);
    mainMenu.show();


    std::unique_ptr<Game> game(new Game("../examples/maps/1.pacmap"));
    std::unique_ptr<NcursesGameView> gameView(new NcursesGameView(game.get()));

    GameController controller(game.get(), gameView.get());
    controller.startGame();

    NcursesUtils::endNcurses();
}
