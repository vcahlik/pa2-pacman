#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H


#include <cstdint>
#include <string>
#include <memory>
#include "GameMap.h"
#include "GameObjects/MovableObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Items/Item.h"
#include "GameObjects/Enemies/Enemy.h"
#include "GameObjects/Items/Coin.h"
#include "GameObjects/Enemies/Ghosts/Ghost.h"
#include "LevelConfig.h"
#include "GameTimer.h"
#include "GameObjects/Items/Cherry.h"
#include "GameObjects/Items/PowerUp.h"

/**
 * @brief Model part of the MVC architecture, the actual game
 */
class Game
{
public:
    enum class State
    {
        Running,
        LifeLost,
        GameOver,
        GameWon,
        Shutdown
    };

    /**
     * @brief Constructor, loads game map from file and prepares GameObjects
     * @param userConfig
     */
    explicit Game(const LevelConfig userConfig);

    const State getState() const;

    /**
     * @brief Basic logical point, run once every Controller cycle, performs all logic based on current State
     * @throws std::logic_error on unhandled State
     */
    void performCycle();

    const GameMap &getMap() const;

    Player &getPlayer();

    const Player &getPlayer() const;

    const std::vector<std::unique_ptr<Coin>> &getCoins() const;

    const std::vector<std::unique_ptr<Ghost>> &getGhosts() const;

    const std::vector<std::unique_ptr<PowerUp>> &getPowerUps() const;

    const uint32_t getRemainingLivesCount() const;

    void increaseScore(const uint32_t scored);

    const uint32_t getScore() const;

    /**
     * @brief Checks if cherry is present on the game board
     * @return
     */
    const bool isCherryPresent() const;

    /**
     * @brief Returns the cherry
     * @return
     * @throws std::runtime_error if cherry not present (aka. is nullptr)
     */
    const Cherry &getCherry() const;

    /**
     * @brief Attempts to frighten all ghosts
     */
    void frightenGhosts();

    const Difficulty &getDifficulty() const;

private:
    void performStateRunningCycle();

    void performStateLifeLostCycle();

    void performStateGameOverCycle();

    void performStateGameWonCycle();

    /**
     * @brief Calls performActions() on all game's GameObjects
     */
    void performObjectActions();

    /**
     * @brief Helper for performObjectActions(), calls performActions() on all GameObjects in a given container
     */
    void performContainerObjectsActions(std::vector<std::unique_ptr<GameObject>> &container);

    /**
     * @brief Processes all GameObjects which are in Removed state
     */
    void removeDeletedObjects();

    /**
     * @brief Removes all State::Removed items in a given Item container
     * @param itemsContainer
     */
    void removeDeletedItems(std::vector<std::unique_ptr<Item>> &itemsContainer);

    /**
     * @brief Resets the game after the player lost a life
     */
    void startWithNextLife();

    /**
     * @brief Initializes the game board with coins
     */
    void placeCoins();

    /**
     * @brief Initializes desired ghosts
     */
    void initGhosts();

    /**
     * @brief Initializes power ups
     */
    void placePowerUps();

    /**
     * @brief Takes care of releasing objects onto the game board
     */
    void performObjectGeneration();

    /**
     * @brief Gradually releases gosts from ghost house
     */
    void performGhostsRelease();

    /**
     * @brief Gradually places the cherry on game board
     */
    void performCherryGeneration();

    const bool ghostHouseEmpty() const;

    const GameMap map;
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<Coin>> coins; /**< @brief Storage of remaining coins */
    std::vector<std::unique_ptr<Ghost>> ghosts; /**< @brief Storage of all ghosts */
    std::vector<std::unique_ptr<PowerUp>> powerUps; /**< @brief Storage of remaining power ups */
    std::unique_ptr<Cherry> cherry; /**< @brief Home of the cherry, can be nullptr */

    uint32_t remainingLivesCount;

    uint32_t score;

    GameTimer timer;

    const Difficulty difficulty;

    bool inShutdownState;

};


#endif //PACMAN_GAME_H
