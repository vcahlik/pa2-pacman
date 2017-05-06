#ifndef PACMAN_SCREEN_H
#define PACMAN_SCREEN_H


#include <ncurses.h>

class Screen
{
public:
    explicit Screen(WINDOW *window);

    virtual void show() = 0;

protected:
    WINDOW *window;
};


#endif //PACMAN_SCREEN_H
