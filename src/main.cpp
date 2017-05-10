#include <iostream>
#include "View/Ncurses/NcursesUI.h"
#include "UserConfig.h"

int main(int argc, char **argv)
{
    srand(static_cast<uint32_t>(time(NULL)));

    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: pacman MAPFILE [DIFFICULTY]" << std::endl;
        return EXIT_FAILURE;
    }

    UserConfig userConfig;
    userConfig.setMapFileName(argv[1]);

    NcursesUI ui;
    ui.show(userConfig);

    return EXIT_SUCCESS;
}
