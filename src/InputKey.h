#ifndef PACMAN_INPUTKEYS_H
#define PACMAN_INPUTKEYS_H


/**
 * @brief Keyboard keys
 */
enum class InputKey
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

/**
 * @brief No key has been pressed
 */
class NoUserInputException
{
};


#endif //PACMAN_INPUTKEYS_H
