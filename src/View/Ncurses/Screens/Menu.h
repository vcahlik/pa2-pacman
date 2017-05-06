#ifndef PACMAN_MENU_H
#define PACMAN_MENU_H


#include <cstdint>
#include <vector>
#include <string>

class Menu
{
public:
    explicit Menu(WINDOW *window, const uint32_t posX, const uint32_t posY);

    void addOption(const uint32_t code, const std::string text);

    void show() const;

    const uint32_t getUsersChoice();

private:
    void redraw() const;

    WINDOW *window;
    uint32_t posX;
    uint32_t posY;

    std::vector<uint32_t> codes;
    std::vector<std::string> texts;

    uint32_t selectedPosition;
};


#endif //PACMAN_MENU_H
