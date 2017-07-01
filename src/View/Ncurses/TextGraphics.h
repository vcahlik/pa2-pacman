#ifndef PACMAN_GRAPHICS_H
#define PACMAN_GRAPHICS_H

/**
 * @brief Storage of all the ascii "arts"
 */
namespace TextGraphics
{
    namespace Player
    {
        const char *const MOUTH_CLOSED_LINE1 = " CCCC ";
        const char *const MOUTH_CLOSED_LINE2 = "CCCCCC";
        const char *const MOUTH_CLOSED_LINE3 = " CCCC ";

        const char *const MOUTH_OPEN_UP_LINE1 = "C    C";
        const char *const MOUTH_OPEN_UP_LINE2 = "CCCCCC";
        const char *const MOUTH_OPEN_UP_LINE3 = " CCCC ";

        const char *const MOUTH_OPEN_DOWN_LINE1 = " CCCC ";
        const char *const MOUTH_OPEN_DOWN_LINE2 = "CCCCCC";
        const char *const MOUTH_OPEN_DOWN_LINE3 = "C    C";

        const char *const MOUTH_OPEN_LEFT_LINE1 = " CCCC ";
        const char *const MOUTH_OPEN_LEFT_LINE2 = "   CCC";
        const char *const MOUTH_OPEN_LEFT_LINE3 = " CCCC ";

        const char *const MOUTH_OPEN_RIGHT_LINE1 = " CCCC";
        const char *const MOUTH_OPEN_RIGHT_LINE2 = "CCC  ";
        const char *const MOUTH_OPEN_RIGHT_LINE3 = " CCCC";
    }

    namespace Wall
    {
        const char *const LINE1 = "888888";
        const char *const LINE2 = "888888";
        const char *const LINE3 = "888888";
    }

    namespace Teleport
    {
        const char *const LINE1 = " \\\\   ";
        const char *const LINE2 = "  \\\\  ";
        const char *const LINE3 = "   \\\\ ";
    }

    namespace SpawnPoint
    {
        const char *const LINE1 = "+----+";
        const char *const LINE2 = "|    |";
        const char *const LINE3 = "+----+";
    }

    namespace Ghost
    {
        const char *const LEFT_LINE1 = "/    \\";
        const char *const LEFT_LINE2 = "|O O |";
        const char *const LEFT_LINE3 = "vv  vv";

        const char *const RIGHT_LINE1 = "/    \\";
        const char *const RIGHT_LINE2 = "| O O|";
        const char *const RIGHT_LINE3 = "vv  vv";
    }

    const char *const COIN = " .";
    \

    const char *const POWERUP = " o";

    const char *const CHERRY_LINE1 = " ,";
    const char *const CHERRY_LINE2 = "@@";

}

#endif //PACMAN_GRAPHICS_H
