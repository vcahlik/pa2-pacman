#include "NcursesUI.h"
#include "NcursesUtils.h"
#include "NcursesGameView.h"
#include "../../Controller/GameController.h"
#include "../../Utils.h"
#include <iostream>

void NcursesUI::show(const UserConfig userConfig)
{
    console = NcursesUtils::initNcurses();

    try
    {
        std::unique_ptr<Game> game = std::make_unique<Game>(userConfig);
        std::unique_ptr<NcursesGameView> gameView = std::make_unique<NcursesGameView>(game.get());
        GameController controller(game.get(), gameView.get());

        controller.startGame();
    } catch (const Utils::ExceptionMessage &e)
    {
        // End Ncurses if a terminating ExceptionMessage has been thrown
        NcursesUtils::endNcurses();
        throw e;
    }

    NcursesUtils::endNcurses();
}
