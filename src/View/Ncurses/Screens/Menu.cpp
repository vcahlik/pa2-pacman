#include <ncurses.h>
#include <stdexcept>
#include "Menu.h"
#include "../Color.h"
#include "../NcursesUtils.h"

Menu::Menu(WINDOW *window, const uint32_t posX, const uint32_t posY)
    : window(window),
      posX(posX),
      posY(posY),
      selectedPosition(0)
{

}

void Menu::addOption(const uint32_t code, const std::string text)
{
    codes.push_back(code);
    texts.push_back(text);
}

void Menu::show() const
{
    if (codes.empty())
    {
        throw std::logic_error("show(): empty menu");
    }

    redraw();
}

void Menu::redraw() const
{
    // Show all labels
    for (uint32_t i = 0; i < codes.size(); ++i)
    {
        mvprintw(posY + i, posX, "  "); // Clear the "selected" symbol
        mvprintw(posY + i, posX + 2, texts.at(i).c_str()); // Show text label
    }

    // Show the "selected" symbol
    attron(COLOR_PAIR(NcursesUtils::colorCode(Color::Green)));
    mvprintw(posY + selectedPosition, posX, ">");
    attroff(COLOR_PAIR(NcursesUtils::colorCode(Color::Green)));

    refresh();
}

const uint32_t Menu::getUsersChoice()
{
    if (codes.empty())
    {
        throw std::logic_error("getUsersChoice(): empty menu");
    }

    while (true)
    {
        InputKey key = InputKey::UP;

        try
        {
            key = NcursesUtils::getPressedKey(window);
        } catch (NoUserInputException &)
        {
            continue;
        }

        switch (key)
        {
            case InputKey::UP:
                if (selectedPosition > 0)
                {
                    --selectedPosition;
                    redraw();
                }
                break;
            case InputKey::DOWN:
                if (selectedPosition + 1 < codes.size())
                {
                    ++selectedPosition;
                    redraw();
                }
                break;
            case InputKey::ENTER:
                return selectedPosition;
            default:
                break;
        }
    }
}
