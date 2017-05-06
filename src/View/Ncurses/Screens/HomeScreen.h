#ifndef PACMAN_HOMESCREEN_H
#define PACMAN_HOMESCREEN_H


#include "Screen.h"
#include "Menu.h"

class HomeScreen
    : public Screen
{
public:
    explicit HomeScreen(WINDOW *window);

    virtual void show() override;

private:
    Menu menu;
};


#endif //PACMAN_HOMESCREEN_H
