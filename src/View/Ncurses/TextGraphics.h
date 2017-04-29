#ifndef PACMAN_GRAPHICS_H
#define PACMAN_GRAPHICS_H

namespace TextGraphics
{
    namespace Player
    {
        const char * const MOUTH_CLOSED_LINE1 = " CCCC ";
        const char * const MOUTH_CLOSED_LINE2 = "CCCCCC";
        const char * const MOUTH_CLOSED_LINE3 = " CCCC ";

        const char * const MOUTH_OPEN_UP_LINE1 = "C    C";
        const char * const MOUTH_OPEN_UP_LINE2 = "CCCCCC";
        const char * const MOUTH_OPEN_UP_LINE3 = " CCCC ";

        const char * const MOUTH_OPEN_DOWN_LINE1 = " CCCC ";
        const char * const MOUTH_OPEN_DOWN_LINE2 = "CCCCCC";
        const char * const MOUTH_OPEN_DOWN_LINE3 = "C    C";

        const char * const MOUTH_OPEN_LEFT_LINE1 = " CCCC ";
        const char * const MOUTH_OPEN_LEFT_LINE2 = "   CCC";
        const char * const MOUTH_OPEN_LEFT_LINE3 = " CCCC ";

        const char * const MOUTH_OPEN_RIGHT_LINE1 = " CCCC ";
        const char * const MOUTH_OPEN_RIGHT_LINE2 = "CCC   ";
        const char * const MOUTH_OPEN_RIGHT_LINE3 = " CCCC ";
    }

    namespace Wall
    {
        const char * const NORMAL_LINE1 = "888888";
        const char * const NORMAL_LINE2 = "888888";
        const char * const NORMAL_LINE3 = "888888";
    }

}

#endif //PACMAN_GRAPHICS_H
