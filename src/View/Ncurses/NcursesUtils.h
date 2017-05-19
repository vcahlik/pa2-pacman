#ifndef PACMAN_NCURSESUTILS_H
#define PACMAN_NCURSESUTILS_H


#include <ncurses.h>
#include "Color.h"
#include "../../InputKey.h"

/**
 * @brief Various helper methods for manipulation with the Ncurses library
 */
namespace NcursesUtils
{
    /**
     * @brief Initializes Ncurses
     * @return
     * @throws ExceptionMessage if terminal does not support colors
     */
    WINDOW *initNcurses();

    /**
     * @brief Ends Ncurses
     */
    void endNcurses();

    /**
     * @brief Creates a window and sets its input as non delay
     * @param height
     * @param width
     * @param posY
     * @param posX
     * @return
     */
    WINDOW *createWindow(uint32_t height, uint32_t width, uint32_t posY, uint32_t posX);

    /**
     * @brief Deletes a window
     * @param window
     */
    void destroyWindow(WINDOW *window);

    /**
     * @brief Informs Ncurses of the different Colors and their logical codes
     */
    void initColors();

    /**
     * @brief Returns the Color's logical code used by Ncurses
     * @param color
     * @return
     */
    const int16_t colorCode(const Color color);

    /**
     * @brief Converts Color to the Ncurses COLOR representation
     * @param color
     * @return
     * @throws std::logic_error on unhandled color
     */
    const int16_t toNcursesColor(const Color color);

    /**
     * @brief Returns user input from Ncurses
     * @param window
     * @return
     * @throws NoUserInputException on no input
     */
    const InputKey getPressedKey(WINDOW *window);

}


#endif //PACMAN_NCURSESUTILS_H
