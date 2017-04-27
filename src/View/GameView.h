#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H


class GameView
{
public:
    virtual void show() = 0;

    virtual void redraw() = 0;

    virtual void end() = 0;

};


#endif //PACMAN_VIEW_H
