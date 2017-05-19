#include <iostream>
#include "View/Ncurses/NcursesUI.h"
#include "Utils.h"

/**
 * @brief Passes game configuration to the UI
 * @param argc
 * @param argv
 * @throws Utils::ExceptionMessage on wrong number of user arguments
 */
void playPacman(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        throw Utils::ExceptionMessage("Usage: pacman MAPFILE [DIFFICULTY]");
    }

    UserConfig userConfig;
    userConfig.setMapFileName(argv[1]);

    if (argc == 3)
    {
        userConfig.setDifficultyLevel(argv[2]);
    }

    NcursesUI ui;
    ui.show(userConfig);
}

/**
 * @brief Starts the program and prints error messages to user
 * @param argc
 * @param argv
 * @return EXIT_SUCCESS game finished, EXIT_FAILURE error or game interrupted
 */
int main(int argc, char **argv)
{
    srand(static_cast<uint32_t>(time(NULL)));

    try
    {
        playPacman(argc, argv);
    } catch (const Utils::ExceptionMessage &e)
    {
        // Print the exception message
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
