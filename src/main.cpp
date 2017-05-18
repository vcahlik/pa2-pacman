#include <iostream>
#include "View/Ncurses/NcursesUI.h"
#include "Config.h"
#include "Utils.h"

void playPacman(int argc, char **argv)
{
    UserConfig userConfig;
    userConfig.setMapFileName(argv[1]);

    if (argc == 3)
    {
        userConfig.setDifficultyLevel(argv[2]);
    }

    NcursesUI ui;
    ui.show(userConfig);
}

int main(int argc, char **argv)
{
    srand(static_cast<uint32_t>(time(NULL)));

    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: pacman MAPFILE [DIFFICULTY]" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        playPacman(argc, argv);
    } catch (const Utils::ExceptionMessage &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
