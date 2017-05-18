#include "NcursesUI.h"
#include "NcursesUtils.h"
#include "NcursesGameView.h"
#include "ViewConfig.h"
#include "../../Controller/GameController.h"
#include "../../UserConfig.h"
#include "../../Utils.h"

#include <ncurses.h>
#include <stdexcept>
#include <iostream>

void NcursesUI::show(const UserConfig userConfig)
{
    try
    {
        console = NcursesUtils::initNcurses();
    }
    catch(const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    try
    {
        std::unique_ptr<Game> game(new Game(userConfig));
        std::unique_ptr<NcursesGameView> gameView(new NcursesGameView(game.get()));

        GameController controller(game.get(), gameView.get());
        controller.startGame();
    } catch (const Utils::ExceptionMessage &e)
    {
        NcursesUtils::endNcurses();
        throw e;
    }



    NcursesUtils::endNcurses();
}
